#include <iostream>
#include <string>

#include "personne.h"

void Personne::set_naissance (jDate& D)
{
  date_naissance = D;
}

void Personne::set_naissance_jma (uint j, uint m, uint a)
{
  jDate D(j, m, a);
  set_naissance (D);
}

Personne::Personne ()
{
  nom = prenom = nsecu = ntel = email = "";
}

Personne::Personne (Personne& P)
{
  set (P.nom, P.prenom, P.date_naissance, P.nsecu, P.adr, P.ntel, P.email);
}

Personne::Personne (std::string& nom, std::string& prenom, jDate& naissance,
		    std::string& nsecu, AdressePostale& adr,
		    std::string& ntel, std::string& email)
{
  this->nom = nom; this->prenom = prenom; this->date_naissance = naissance;
  this->nsecu = nsecu; this->adr = adr; this->ntel = ntel; this->email = email;
}

Personne::~Personne ()
{
  
}

Personne& Personne::operator= (Personne& P)
{
  set (P.nom, P.prenom, P.date_naissance, P.nsecu, P.adr, P.ntel, P.email);
  return (*this);
}

uint Personne::get_genre ()
{
  if (nsecu == "")
    return 1;

  if (nsecu[0] == '1')
    return 1; // homme
  else if (nsecu[0] == '2')
    return 2; // femme
  else
    return 2; // arbitraire
}

std::ostream& operator<< (std::ostream& o, Personne& P)
{
  uint genre = P.get_genre ();
  if (genre == 1)
    o << "Monsieur ";
  else
    o << "Madame ou Mademoiselle ";
  o << P.prenom << " " << P.nom << std::endl;
  if (genre == 1)
    o << "ne le ";
  else
    o << "nee le ";
  o << P.date_naissance << std::endl;
  o << "Numero de securite sociale : " << P.nsecu << std::endl;
  o << "Adresse postale : " << std::endl;
  o << P.adr << std::endl;
  o << "Numero de telephone : " << P.ntel << std::endl;
  o << "e-mail : " << P.email << std::endl;
  return o;
}

std::istream& operator>> (std::istream& i, Personne& P)
{
  do 
    {
      std::cout << "Entrez le nom : ";
      i >> P.nom;
    }
  while (!P.has_valid_nom ());
  
  do
    {
      std::cout << std::endl << "Entrez le prenom : ";
      i >> P.prenom;
    }
  while (!P.has_valid_prenom ());

  do
    {
      std::cout << std::endl << "Entrez la date de naissance : ";
      i >> P.date_naissance;
    }
  while (!P.has_valid_naissance ());

  do
    {
      std::cout << std::endl << "Entrez le numero de securite sociale : ";
      i >> P.nsecu;
    }
  while (!P.has_valid_nsecu ());

  do
    {
      std::cout << std::endl << "Entrez l'adresse postale : ";
      i >> P.adr;
    }
  while (!P.has_valid_adr ());

  do
    {
      std::cout << std::endl << "Entrez le numero de telephone : ";
      i >> P.ntel;
    }
  while (!P.has_valid_ntel ());

  do
    {
      std::cout << std::endl << "Entrez l'adresse e-mail : ";
      i >> P.email;
    }
  while (!P.has_valid_email ());
  return i;
}

//friend std::ofstream& operator<< (std::ofstream& o, Personne& P);
//friend std::ifstream& operator>> (std::ifstream& i, Personne& P);

std::string& Personne::get_nom ()
{
  return nom;
}

void Personne::set_nom (std::string& nom)
{
  this->nom = nom;
}

std::string& Personne::get_prenom ()
{
  return prenom;
}

void Personne::set_prenom (std::string& prenom)
{
  this->prenom = prenom; 
}
 
jDate& Personne::get_naissance ()
{
  return date_naissance;
}

void Personne::get_naissance_jma (uint& j, uint& m, uint& a)
{
  j = date_naissance.get_j();
  m = date_naissance.get_m();
  a = date_naissance.get_a();
}

std::string& Personne::get_nsecu ()
{
  return nsecu;
}
void Personne::set_nsecu (std::string& nsecu)
{
  this->nsecu = nsecu;
}

AdressePostale& Personne::get_adr ()
{
  return adr;
}

void Personne::set_adr (AdressePostale& adr)
{
  this->adr = adr;
}

std::string& Personne::get_ntel ()
{
  return ntel;
}

void Personne::set_ntel (std::string& ntel)
{
  this->ntel = ntel;
}

std::string& Personne::get_email ()
{
  return email;
}

void Personne::set_email (std::string& email)
{
  this->email = email;
}

void Personne::get (std::string& nom, std::string& prenom, jDate& naissance,
	  std::string& nsecu, AdressePostale& adr,
	  std::string& ntel, std::string& email)
{
  nom = this->nom; prenom = this->prenom; naissance = date_naissance;
  nsecu = this->nsecu; adr = this->adr; ntel = this->ntel;
  email = this->email;
}
  
bool Personne::set (std::string& nom, std::string& prenom, jDate& naissance,
		    std::string& nsecu, AdressePostale& adr,
		    std::string& ntel, std::string& email)
{
  this->nom = nom; this->prenom = prenom; date_naissance = naissance;
  this->nsecu = nsecu; this->adr = adr; this->ntel = ntel; this->email = email;
  return is_valid ();
}

bool Personne::is_valid ()
{
  return (has_valid_nom () && has_valid_prenom () && 
	  has_valid_naissance () &&
	  has_valid_nsecu () && has_valid_adr () && 
	  has_valid_ntel () && has_valid_email ());
}

bool Personne::has_valid_nom ()
{
  return true; // not implemented yet
}

bool Personne::has_valid_prenom ()
{
  return true; // not implemented yet
}

bool Personne::has_valid_naissance ()
{
  return true; // not implemented yet
}

bool Personne::has_valid_nsecu ()
{
  if (nsecu =="")
    return false;
  
  if ((nsecu[0] != '1') && (nsecu[0] != '2'))
    return false;

  if (nsecu.length () != 15)
    return false;

  for (int i = 1; i < 15; i++)
    {
      if ((nsecu[i] < '0') || (nsecu[i] > '9'))
	return false;
    }
  
  return true;
}

bool Personne::has_valid_adr ()
{
  return true; // not implemented yet
}

bool Personne::has_valid_ntel ()
{
  return true; // not implemented yet
}

bool Personne::has_valid_email ()
{
  return tools::is_valid_email (email);
}

bool tools::is_valid_email (std::string email)
{
  if (email[0] == '@') std::cerr << "Une ligne a supprimer du code..." << std::endl;
  return true; //not implemented yet
}
