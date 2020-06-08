#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <iostream>

template <class T>
class array {
 private :
  uint len;
  uint alloc;
  T* data;
 protected :
  void realloc (uint new_size);
 public :
  array ();
  array (uint alloc); // set len to zero
  array (uint len, uint alloc);
  array (array &A);
  ~array ();

  template <class U> array<U>& operator= (array<U>& A); 

  template <class U> 
    friend std::ostream& operator<< (std::ostream &o, array<U>& A);

  uint length ();
  T& get (uint index);
  void set (uint index, T& value);
  void add (T& value);
};

#include "array.cc"

#endif
