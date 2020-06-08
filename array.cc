#include "array.h"

#ifndef __ARRAY_CC_
#define __ARRAY_CC_

#include <iostream>
#include <string>

template <class T>
array<T>::array (array<T> &A)
{
  len = A.len;
  alloc = A.len;
  data = new T[A.len];
  for (int i = 0; i < A.len; i++)
    data[i] = A.data[i];
}

template <class T>
void array<T>::set (uint index, T& value)
{
  if (index >= this->alloc)
    realloc (index * 2);
  
  if (index >= len)
    len = index + 1;

  data[index] = value;
}

template <class T>
void array<T>::add (T& value)
{
  set (len, value);
}

template <class T>
array<T>::array ()
{
  len = alloc = 0;
  data = NULL;
}

template <class T>
array<T>::array (uint alloc)
{
  this->alloc = alloc;
  this->len = 0;
  data = new T[alloc];
}

template <class T>
array<T>::array (uint len, uint alloc)
{
  this->alloc = alloc;
  this->len = len;
  data = new T[alloc];
}

template <class T>
void array<T>::realloc (uint new_size)
{
  T* newdata = new T[new_size];
  for (uint i = 0; i < len; i++)
    newdata[i] = data[i];
  delete[] data;
  data = newdata;
  alloc = new_size;
}

template <class T>
array<T>::~array ()
{
  delete[] data;
}

template <class T>
std::ostream& operator<< (std::ostream &o, array<T>& A)
{
  o << "[ ";
  //for (uint i = 0; i <= A.len - 2; i++)
  for (uint i = 0; i + 2 <= A.len; i++)
    {
      o << A.get (i) << " ; ";
    }
  if (A.len > 0)
    o << A.get (A.len - 1);
  o << " ]";
  return o;
}

template <class T>
uint array<T>::length ()
{
  return this->len;
}

template <class T>
T& array<T>::get (uint index)
{
  return this->data[index];
}

#endif
