#include <iostream>
#include <string>

#include "tools.h"
#include "array.h"
#include "personne.h"

int main ()
{
  jDate D(30, 10, 2013);

  std::string num = "49B";
  std::string rue = "rue de chez Petronille";
  std::string comp = "";
  std::string cp = "33000";
  std::string ville = "BORDEAUX"; 
  
  AdressePostale adr(num, 
		     rue, comp, cp, ville,
		     false,
		     (uint) 0);
  
  std::string nom = "FSRWGTGRDS";
  std::string prenom = "Petronille";
  std::string nsecu = "200000000000000";
  std::string ntel = "0000000000"; 
  std::string email = "petronille@FSRWGTGRDS.net";

  Personne P (nom, prenom, D, nsecu, adr, ntel, email);
  Personne P2 (P);
  nsecu = ("100000000000000");

  P2.set_nsecu (nsecu);

  array<Personne> A(20);
  A.add (P);
  std::cout << A << std::endl;

  if (!P2.has_valid_nsecu ())
    std::cerr << "Numero de secu non valide." << std::endl;
  return 0;
}


