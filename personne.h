#ifndef __PERSONNE_H__
#define __PERSONNE_H__

#include <iostream>
#include <fstream>
#include <string>

#include "tools.h"

class Personne {
 private :
  std::string nom;
  std::string prenom;
  jDate date_naissance;
  std::string nsecu;
  AdressePostale adr;
  std::string ntel;
  std::string email;
 protected :
  uint get_genre (); //1, homme -- 2, femme
 public :
  Personne ();
  Personne (Personne& P);
  Personne (std::string& nom, std::string& prenom, jDate& naissance,
	    std::string& nsecu, AdressePostale& adr,
	    std::string& ntel, std::string& email);
  ~Personne ();
  Personne& operator= (Personne& P);
  
  friend std::ostream& operator<< (std::ostream& o, Personne& P);
  friend std::istream& operator>> (std::istream& i, Personne& P);
  //friend std::ofstream& operator<< (std::ofstream& o, Personne& P);
  //friend std::ifstream& operator>> (std::ifstream& i, Personne& P);

  std::string& get_nom ();
  void set_nom (std::string& nom);
  std::string& get_prenom ();
  void set_prenom (std::string& prenom);
  jDate& get_naissance ();
  void get_naissance_jma (uint& j, uint& m, uint& a);
  void set_naissance (jDate& D);
  void set_naissance_jma (uint j, uint m, uint a);
  std::string& get_nsecu ();
  void set_nsecu (std::string& nsecu);
  AdressePostale& get_adr ();
  void set_adr (AdressePostale& adr);
  std::string& get_ntel ();
  void set_ntel (std::string& ntel);
  std::string& get_email ();
  void set_email (std::string& email);

  void get (std::string& nom, std::string& prenom, jDate& naissance,
	    std::string& nsecu, AdressePostale& adr,
	    std::string& ntel, std::string& email);
  
  bool set (std::string& nom, std::string& prenom, jDate& naissance,
	    std::string& nsecu, AdressePostale& adr,
	    std::string& ntel, std::string& email);

  bool has_valid_nom ();
  bool has_valid_prenom ();
  bool has_valid_naissance ();
  bool has_valid_nsecu ();
  bool has_valid_adr();
  bool has_valid_ntel ();
  bool has_valid_email ();
  bool is_valid ();
};

#endif
