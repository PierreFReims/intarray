#ifndef __JSTR_H__
#define __JSTR_H__

#include <iostream>

class jstr {
 private :
  uint len;
  uint alloc;
  char* data;
 protected :
  void realloc (uint new_size);
 public :
  jstr ();
  jstr (uint alloc); // set len to zero
  jstr (uint len, uint alloc);
  jstr (jstr &J);
  ~jstr ();

  jstr& operator= (jstr& J); 

  friend std::ostream& operator<< (std::ostream &o, jstr& J);
  friend std::istream& operator>> (std::istream &i, jstr& J);

  uint length ();
  char get (uint index);
  void set (uint index, char c);
  void add (char c);

  char* get_data (); // use with caution
  void reverse ();
  void from_int (int n); // int_to_jstr C function translated into C++
};

#endif
