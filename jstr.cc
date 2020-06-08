#include <iostream>
//#include <string>

#include "jstr.h"
#include "tools.h"

jstr::jstr (jstr &A)
{
  len = A.len;
  alloc = A.len;
  data = new char[A.len];
  for (uint i = 0; i < A.len; i++)
    data[i] = A.data[i];
}


void jstr::set (uint index, char c)
{
  if (index >= this->alloc)
    realloc (index * 2);
  
  if (index >= len)
    len = index + 1;

  data[index] = c;
}


void jstr::add (char c)
{
  set (len, c);
}


jstr::jstr ()
{
  len = alloc = 0;
  data = NULL;
}


jstr::jstr (uint alloc)
{
  this->alloc = alloc;
  this->len = 0;
  data = new char[alloc];
}


jstr::jstr (uint len, uint alloc)
{
  this->alloc = alloc;
  this->len = len;
  data = new char[alloc];
}


void jstr::realloc (uint new_size)
{
  char* newdata = new char[new_size];
  for (uint i = 0; i < len; i++)
    newdata[i] = data[i];
  delete[] data;
  data = newdata;
  alloc = new_size;
}


jstr::~jstr ()
{
  delete[] data;
}


std::ostream& operator<< (std::ostream &o, jstr& A)
{
  for (uint i = 0; i < A.len; i++)
    {
      o << A.get (i);
    }
  return o;
}

std::istream& operator>> (std::istream &i, jstr& J)
{
  J.len = 0;
  if ((J.alloc == 0) || (J.data == NULL))
    {
      if (J.data != NULL)
	delete[] J.data;
      J.data = new char[80];
      J.alloc = 80;
    }
  char c;
  /*
  do
    {
      c = std::cin.get ();
    }
  while (c == '\n');
  */
  c = std::cin.get ();
  while (c != '\n')
    {
      J.add(c);
      c = std::cin.get ();
    }
  return i;
}

uint jstr::length ()
{
  return this->len;
}


char jstr::get (uint index)
{
#ifdef DEBUG
  if (index >= len)
    {
      tools::print_warning ("JSTR::get : array out of bounds");
      return this->data[0];
    }
#endif
  return this->data[index];
}

char* jstr::get_data ()
{
  return data;
}

void jstr::reverse ()
{
  int end = (len - 2) / 2;
  for (int i = 0; i <= end; i++)
    {
      // échanger les caractères numéro i et numéro j->len - 1 - i
      char tmp = data[i];
      data[i] = data[len - 1 - i];
      data[len - 1 - i] = tmp;
    }
}

void jstr::from_int (int n)
{
  len = 0;
  if (n == 0)
    set (0, '0');
  else
    {
      while (n != 0)
	{
	  add ((n % 10) + '0');
	  n /= 10;
	}
      reverse ();
    }
}
