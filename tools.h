#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <iostream>
#include <fstream>
#include <string>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char byte;

typedef int integ4;
typedef int integ3;
typedef short integ2;

namespace tools {
  std::string getline (std::istream& i);
  std::string proper_getline (std::istream &i);
  bool is_valid_email (std::string email);
  void print_warning (std::string msg);
  void sint_normalize (signed int& n, signed int vmin, 
		       signed int vmax);
  inline integ4 bytes_to_integ4 (byte a, byte b, byte c, byte d);
  inline void integ4_to_4bytes (integ4 n, byte& a, byte& b, byte& c, byte& d);
  inline void UNSAFE_buffer_copy (char* src, char* dst, int len);
}

class jDate {
 private :
  uint jour; // [1-31]
  uint mois; // [1-12]
  uint annee;
 protected :
  bool is_bissex ();
  uint nb_days_in_month ();
 public :
  jDate ();
  jDate (uint j, uint m, uint a);
  jDate (uint j, uint m, uint a, bool& valid);
  jDate (jDate& d);
  ~jDate ();
  jDate& operator= (jDate& d);
  void get (uint& j, uint &m, uint &a);
  bool set (uint j, uint m, uint a);
  uint get_j ();
  uint get_m ();
  uint get_a ();
  void set_j (uint j);
  void set_m (uint m);
  void set_a (uint a);
  friend std::ostream& operator<< (std::ostream& o, jDate& d);
  friend std::istream& operator>> (std::istream& i, jDate& d);
  friend std::ofstream& operator<< (std::ofstream& o, jDate& d);
  friend std::ifstream& operator>> (std::ifstream& i, jDate& d);
  bool is_valid ();
};


class AdressePostale {
 private :
  std::string numero;
  std::string rue;
  std::string comp;
  std::string cp; //5 chiffres
  std::string ville;
  bool cedex;
  uint cedex_num;
 public :
  AdressePostale ();
  AdressePostale (std::string& numero, std::string& rue,
		  std::string& comp, std::string& cp,
		  std::string& ville, bool cedex,
		  uint cedex_num);
  AdressePostale (std::string& numero, std::string& rue,
		  std::string& comp, std::string& cp,
		  std::string& ville, bool cedex,
		  uint cedex_num,
		  bool& valid);
  AdressePostale (AdressePostale& A);
  ~AdressePostale ();
  void get (std::string& numero, std::string& rue,
	    std::string& comp, std::string& cp,
	    std::string& ville, bool& cedex,
	    uint& cedex_num);
  bool set (std::string& numero, std::string& rue,
	    std::string& comp, std::string& cp,
	    std::string& ville, bool cedex,
	    uint cedex_num);
  std::string get_numero ();
  std::string get_rue ();
  std::string get_comp ();
  std::string get_cp ();
  std::string get_ville ();
  bool has_cedex ();
  uint get_cedex_num ();
  void set_numero (std::string num);
  void set_rue (std::string rue);
  void set_comp (std::string comp);
  void set_cp (std::string cp);
  void set_ville (std::string ville);
  void set_cedex_bool (bool has_cedex);
  void set_cedex_num (uint cedex_num);
  AdressePostale& operator= (AdressePostale &A);
  friend std::ostream& operator<< (std::ostream& o, AdressePostale &A); 
  friend std::istream& operator>> (std::istream& i, AdressePostale &A); 
  friend std::ofstream& operator<< (std::ofstream& o, AdressePostale &A); 
  friend std::ifstream& operator>> (std::ifstream& i, AdressePostale &A); 
  bool is_valid (); // not implemented yet. return true
};

inline void tools::UNSAFE_buffer_copy (char* src, char* dst, int len)
{
  for (int i = 0; i < len; i++)
    {
      dst[i] = src[i];
      dst++; src++;
    }
}

inline integ4 tools::bytes_to_integ4 (byte a, byte b, byte c, byte d)
{
  integ4 n = (a << 24) | (b << 16) | (c << 8) | d;
  return n;
}

inline void tools::integ4_to_4bytes (integ4 n, byte& a, byte& b, byte& c, byte& d)
{
  d = n & 255;
  c = (n >> 8) & 255;
  b = (n >> 16) & 255;
  a = (n >> 24) & 255;
}

//#include "tools.cc"

#endif
