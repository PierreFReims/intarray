#ifndef __JFILE_CC__
#define __JFILE_CC__

#include <iostream>
#include <fstream>


#include "jfile.h"
#include "jstr.h"


jfile::jfile ()
{
  //fname = NULL;
  output = NULL;
  input = NULL;
  mode = 0;
  data = NULL;
  cursor = 0;
  alloc = 0;
  len = 0;
  eof = true;
}

jfile::jfile (const char *fname, const char mode)
{
  open (fname, mode, jfile::DEFAULT_BUFFER_LEN);
}

jfile::jfile (const char *fname, const char mode, uint buffer_len)
{
  open (fname, mode, buffer_len);
}

/* private */
void jfile::open (const char *fname, const char mode, uint buffer_len)
{
  if ((mode < 0) || (mode > 2))
    {
      //mode = 0; // pas possible avec mode comme paramètre const
      tools::print_warning ("jfile::open : unknown mode (1).");
    }
  this->mode = mode;
  switch (mode) {
  case jfile::MODE_READ :
    output = NULL;
    input = new std::ifstream (fname, std::ios::in | std::ios::binary);
    //input->open (fname, std::ios::in);
    break;
  case jfile::MODE_WRITE :
    output = new std::ofstream (fname, std::ios::out | std::ios::binary);
    input = NULL;
    break;
  case jfile::MODE_APPEND :
    output = new std::ofstream (fname, std::ios::out | std::ios::binary | std::ios::app);
    input = NULL;
    break;
  default :
    tools::print_warning ("jfile::open : unknown mode (2).");
  }
  data = new char[buffer_len];
  alloc = buffer_len;
  len = buffer_len;
  cursor = 0;
  eof = false;
  if (mode == jfile::MODE_READ)
    {
      //istream& read (char* s, streamsize n);

      input->read (data, buffer_len);
      if (!input)
	len = input->gcount (); //si on a pu lire moins de buffer_len caracteres...
      else
	len = buffer_len;
      if (len == 0)
	eof = true;
    }
}

void jfile::close ()
{
  if ((mode >= jfile::MODE_WRITE) && (cursor > 0))
    output->write (data, cursor);

  if (mode >= jfile::MODE_WRITE)
    output->close ();
  else
    input->close ();

  input = NULL;
  output = NULL;

  //if (fname != NULL)
  //delete[] fname;

  if (data != NULL)
    delete[] data;
}


jfile::~jfile ()
{
  if ((input != NULL) || (output != NULL)) // close () has not been called before
    close ();                              // or *this has not been opened before 
}

jfile& jfile::operator= (jfile& F)
{
  clonerefs (F);
  return (*this);
}

jfile::jfile (jfile& F)
{
  data = NULL; /* fname = NULL; */ input = NULL; output = NULL;
  clonerefs (F);
}

void jfile::clonerefs (jfile& F)
{
  //if (fname != NULL)
    //delete[] fname;

  if (data != NULL)
    delete[] data;

  if (input != NULL)
    input->close ();

  if (output != NULL)
    output->close ();

  //fname = F.fname;
  output = F.output;
  input = F.input;
  mode = F.mode;
  data = F.data;
  cursor = F.cursor;
  alloc = F.alloc;
  len = F.len;
  eof = F.eof;
}

/* return the number of actually read bytes */
int jfile::read (char *buffer, int len)
{
#ifdef DEBUG
  if ((len <= 0) || (mode != jfile::MODE_READ))
    {
      tools::print_warning ("jfile::read : bad jfile mode");
      return 0;
    }
#endif
  // étape 1 : copier vers buffer ce qui est déjà dans data */
  int nb_in_buffer = len - cursor;
  int nb_done = ((len <= nb_in_buffer) ? len : nb_in_buffer);
  if (nb_done > 0) tools::UNSAFE_buffer_copy (data + cursor, buffer, nb_done);
  cursor += nb_done; buffer += nb_done;
  if (nb_done == len) return len;

  // étape 2 : on copie la plus grande partie possible de ce qu'il reste
  // dont la taille est multiple d'un cluster, avec read directement
  int to_read = len - nb_done;
  to_read -= (to_read % jfile::CLUSTER_LEN);
  if (to_read > 0)
    {
      input->read (buffer, to_read);
      int nb = input->gcount ();
      if (nb == 0)
	eof = true;
      if (nb < to_read)
	return nb + nb_done;
      else
	{
	  nb_done += to_read;
	  buffer += to_read;
	}
    }
  
  // étape 3 : le data est à nouveau rempli et on copie vers le buffer
  // ce qu'il reste à y copier
  int last = len - nb_done;
  // cursor = 0; // pas nécessaire
  input->read (data, alloc);
  if (input->gcount() == 0)
    eof = true;
  if (len < last) last = len;
  tools::UNSAFE_buffer_copy (data, buffer, last);
  cursor = last;
  return nb_done + last;
}

/* return the number of actually written bytes */
int jfile::write (char *buffer, int len)
{
#ifdef DEBUG
  if ((len <= 0) || (mode < jfile::MODE_WRITE))
    {
      tools::print_warning ("jfile::write : bad jfile mode");
      return 0;
    }
#endif
  // step 1
  int nb_to_buffer = alloc - cursor;
  int nb_done = (len <= nb_to_buffer ? len : nb_to_buffer);
  if (nb_done > 0) tools::UNSAFE_buffer_copy (buffer, data + cursor, nb_done);
  cursor += nb_done;
  if (cursor == alloc)
    {
      output->write (data, alloc);
      /* int nb = output->gcount ();
	 if (nb < alloc) return nb; */
      cursor = 0; buffer += nb_done;
    }
  if (nb_done == len) return len;
 
  //step 2
  int to_write = len - nb_done;
  to_write -= (to_write % jfile::CLUSTER_LEN);
  if (to_write > 0)
    {
      output->write (buffer, to_write);
      /* int nb = output->gcount ();
      if (nb < to_write)
	return nb + nb_done;
      else
      { */
      nb_done += to_write;
      buffer += to_write;
	  /* } */
    }

  //step 3
  int last = len - nb_done;
  if (last == 0) return len;
  tools::UNSAFE_buffer_copy (buffer, data, last);
  cursor = last;
  return len;
}

integ4 jfile::read_integ4 ()
{
  byte a, b, c, d;
  a = read_char ();
  b = read_char ();
  c = read_char ();
  d = read_char ();
  return tools::bytes_to_integ4 (a, b, c, d);
}

void jfile::write_integ4 (integ4 n)
{
  byte a, b, c, d;
  tools::integ4_to_4bytes (n, a, b, c, d);
  write_char (a);
  write_char (b);
  write_char (c);
  write_char (d);
}

integ3 jfile::read_integ3 ()
{
  byte a, b, c;
  a = read_char ();
  b = read_char ();
  c = read_char ();
  return ((a << 16) | (b << 8) | c);
}

void jfile::write_integ3 (integ3 n)
{
  byte a, b, c;
  a = n >> 16;
  b = (n >> 8) & 255;
  c = n & 255;
  write_char (a);
  write_char (b);
  write_char (c);
}

integ2 jfile::read_integ2 ()
{
  byte a, b;
  a = read_char ();
  b = read_char ();
  return ((a << 8) | b);
}


void jfile::write_integ2 (integ2 n)
{
  byte a, b;
  a = n >> 8;
  b = n & 255;
  write_char (a);
  write_char (b);
}

void jfile::write_int_text (int n, jstr buffer)
{
  buffer.from_int (n);
  char* jdata = buffer.get_data ();
  for (uint i = 0; i < buffer.length (); i++)
    {
      // std::cerr << jdata[i] << ".."; // VDQP
      write_char (jdata[i]);
    }
  //std::cerr << std::endl; 
}

int jfile::read_int_text ()
{
#ifdef DEBUG
  if (at_end ())
    {
      tools::print_warning ("jfile::read_int_text : end of file");
      return 0;
    }
#endif
  int r = 0;
  char c = read_next_regular_char ();
  while ((c != ' ') && (c != ((char) 10)) && (c != ((char) 13)))
    {
#ifdef DEBUG
      if ((c < '0') || (c > '9'))
	{
	  tools::print_warning ("jfile::read_int_text : not numeric character");
	  c = '0'; //arbitraire
	}
#else
      if ((c < '0') || (c > '9'))
	return 0;
#endif
      r *= 10;
      r += (((int) c) - '0');
      c = read_char ();
    }
  return r;
}


bool jfile::at_end ()
{
#ifdef DEBUG
  if (cursor > alloc)
    {
      tools::print_warning ("jfile::at_end : bad cursor value"); 
      return true;
    }
#endif
  return (eof || (cursor == len));
}

#endif // end of file
