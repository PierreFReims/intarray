#ifndef __JFILE_H__
#define __JFILE_H__

#include <iostream>
#include <fstream>

#include "tools.h"
#include "jstr.h"

class jfile {

 private :
  //char* fname; //VDQP
  std::ofstream* output;
  std::ifstream* input;
  char mode;
  char *data;
  int cursor;
  int alloc;
  int len;
  bool eof;
  static const int CLUSTER_LEN = 4096;
  static const int DEFAULT_BUFFER_LEN = 65536;

  void open (const char *fname, const char mode, uint buffer_len);
  void clonerefs (jfile& F);
 public :
  static const char MODE_READ = ((char) 0);
  static const char MODE_WRITE = ((char) 1);
  static const char MODE_APPEND = ((char) 2);
  
  jfile ();
  jfile (const char *fname, const char mode);
  jfile (const char *fname, const char mode, uint buffer_len);
  void close ();
  ~jfile ();
  jfile& operator= (jfile& F);
  jfile (jfile& F);

  /* return the number of actually read bytes */
  int read (char *buffer, int len);
  /* return the number of actually written bytes */
  int write (char *buffer, int len);

  inline void newline ();

  inline char read_char ();

  /* regular char = ni espace, ni (char) 13, ni (char) 10 */
  inline char read_next_regular_char ();
  
  inline void write_char (char c);

  integ4 read_integ4 ();
  void write_integ4 (integ4 n);
  integ3 read_integ3 ();
  void write_integ3 (integ3 n);
  integ2 read_integ2 ();
  void write_integ2 (integ2 n);

  void write_int_text (int n, jstr buffer);
  int read_int_text ();
  
  bool at_end ();
};

inline char jfile::read_char ()
{
#ifdef DEBUG
  if (mode > jfile::MODE_READ)
    {
      tools::print_warning ("jfile::read_char : bad jfile mode");
      return ((char) 0);
    }
#endif
  char c = data[cursor];
  cursor++;
#ifdef DEBUG
  if (cursor > alloc)
    {
      tools::print_warning ("jfile::read_char : buffer out of bounds");
      return ((char) 0);
    }
#endif
  if (cursor == alloc)
    {
      cursor = 0;
      input->read (data, alloc);
      len = input->gcount ();
      if (len == 0)
	eof = true;
    }
  return c;
}

/* regular char = ni espace, ni (char) 13, ni (char) 10 */
inline char jfile::read_next_regular_char ()
{
  char c;
  do
    {
      c = read_char ();
    }
  while (!(at_end ()) && ((c == ' ') || (c == ((char) 13)) || (c == ((char) 10))));
  return c;
}
  
inline void jfile::write_char (char c)
{
#ifdef DEBUG
  if (mode < jfile::MODE_WRITE)
    {
      tools::print_warning ("jfile::write_char : bad jfile mode");
      return;
    }
  if (cursor > alloc)
    {
      tools::print_warning ("jfile::write_char : buffer out of bounds");
      return;
    }
#endif
  if (cursor == alloc)
    {
      output->write (data, alloc);
      /* #ifdef DEBUG
      int nb = output->gcount ();
      if (nb < alloc)
	{
	  tools::print_warning ("jfile::write_char : can not write enough bytes");
	  return;
	}
	#endif */
      cursor = 0;
    }
  data[cursor] = c;
  cursor++;
}

inline void jfile::newline ()
{
  write_char ((char) 10);
}

//#include "jfile.cc"

#endif
