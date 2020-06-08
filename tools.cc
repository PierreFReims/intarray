#ifndef __TOOLS_CC__
#define __TOOLS_CC__

#include <iostream>
#include <fstream>
#include <string>

#include "tools.h"

void tools::sint_normalize(signed int &n, signed int vmin,
                           signed int vmax)
{
  if (n < vmin)
    n = vmin;
  else if (n > vmax)
    n = vmax;
}

void tools::print_warning(std::string msg)
{
  std::cerr << "WARNING : " << msg << "." << std::endl;
}

std::string tools::getline(std::istream &i)
{
  std::string S;
  std::getline(i, S);
  return S;
}

std::string proper_getline(std::istream &i)
{
  std::string S = tools::getline(i);
  while (S == "")
  {
    std::cerr << std::endl
              << "Veuillez saisir quelque chose : ";
    S = tools::getline(i);
  }
  return S;
}

jDate::jDate()
{
  jour = mois = annee = 0;
}

jDate::jDate(uint j, uint m, uint a)
{
  jour = j;
  mois = m;
  annee = a;
}

jDate::jDate(uint j, uint m, uint a, bool &valid)
{
  jour = j;
  mois = m;
  annee = a;
  valid = is_valid();
}

jDate::jDate(jDate &D)
{
  jour = D.jour;
  mois = D.mois;
  annee = D.annee;
}

std::ostream &operator<<(std::ostream &o, jDate &D)
{
  o << (D.jour < 10 ? "0" : "") << D.jour << "/";
  o << (D.mois < 10 ? "0" : "") << D.mois << "/";
  o << (D.annee < 10 ? "0" : "") << D.annee;
  return o;
}

std::istream &operator>>(std::istream &i, jDate &D)
{
  uint j, m, a;
  i >> j >> m >> a;
  D.set(j, m, a);
  return i;
}

std::ofstream &operator<<(std::ofstream &o, jDate &D)
{
  o << (D.jour < 10 ? "0" : "") << D.jour << "/";
  o << (D.mois < 10 ? "0" : "") << D.mois << "/";
  o << (D.annee < 10 ? "0" : "") << D.annee;
  return o;
}

std::ifstream &operator>>(std::ifstream &i, jDate &D)
{
  uint j, m, a;
  i >> j >> m >> a;
  D.set(j, m, a);
  return i;
}

jDate::~jDate()
{
}

jDate &jDate::operator=(jDate &D)
{
  jour = D.jour;
  mois = D.mois;
  annee = D.annee;
  return *this;
}

void jDate::get(uint &j, uint &m, uint &a)
{
  j = jour;
  m = mois;
  a = annee;
}

bool jDate::is_bissex()
{
  return ((annee % 400 == 0) ||
          ((annee % 100 != 0) && (annee % 4 == 0)));
}

uint jDate::nb_days_in_month()
{
  if ((mois == 1) || (mois == 3) || (mois == 5) || (mois == 7) || (mois == 8) ||
      (mois == 10) || (mois == 12))
    return 31;

  if ((mois == 4) || (mois == 6) || (mois == 9) || (mois == 11))
    return 30;

  if ((mois == 2) && (is_bissex()))
    return 29;

  return 28;
}

bool jDate::is_valid()
{
  if ((mois < 1) || (mois > 12))
    return false;
  if ((jour < 1) || (jour > nb_days_in_month()))
    return false;

  return true;
}

bool jDate::set(uint j, uint m, uint a)
{
  jour = j;
  mois = m;
  annee = a;
  return is_valid(); // means "return this->is_valid ()"
}

uint jDate::get_j()
{
  return jour;
}

uint jDate::get_m()
{
  return mois;
}

uint jDate::get_a()
{
  return annee;
}

void jDate::set_j(uint j)
{
  jour = j;
}

void jDate::set_m(uint m)
{
  mois = m;
}

void jDate::set_a(uint a)
{
  annee = a;
}

AdressePostale::AdressePostale()
{
  numero = rue = comp = cp = ville = "";
  cedex = false;
  cedex_num = 0;
}

AdressePostale::AdressePostale(std::string &numero, std::string &rue,
                               std::string &comp, std::string &cp,
                               std::string &ville, bool cedex,
                               uint cedex_num)
{
  this->numero = numero;
  this->rue = rue;
  this->comp = comp;
  this->cp = cp;
  this->ville = ville;
  this->cedex = cedex;
  this->cedex_num = cedex_num;
}

AdressePostale::AdressePostale(std::string &numero, std::string &rue,
                               std::string &comp, std::string &cp,
                               std::string &ville, bool cedex,
                               uint cedex_num,
                               bool &valid)
{
  this->numero = numero;
  this->rue = rue;
  this->comp = comp;
  this->cp = cp;
  this->ville = ville;
  this->cedex = cedex;
  this->cedex_num = cedex_num;
  valid = is_valid();
}

AdressePostale::AdressePostale(AdressePostale &A)
{
  numero = A.numero;
  rue = A.rue;
  comp = A.comp;
  cp = A.cp;
  ville = A.ville;
  cedex = A.cedex;
  cedex_num = A.cedex_num;
}

AdressePostale::~AdressePostale()
{
}

bool AdressePostale::is_valid()
{
  //not implemented yet
  return true;
}

void AdressePostale::get(std::string &numero, std::string &rue,
                         std::string &comp, std::string &cp,
                         std::string &ville, bool &cedex,
                         uint &cedex_num)
{
  numero = this->numero;
  rue = this->rue;
  comp = this->comp;
  cp = this->cp;
  ville = this->ville;
  cedex = this->cedex;
  cedex_num = this->cedex_num;
}

bool AdressePostale::set(std::string &numero, std::string &rue,
                         std::string &comp, std::string &cp,
                         std::string &ville, bool cedex,
                         uint cedex_num)
{
  this->numero = numero;
  this->rue = rue;
  this->comp = comp;
  this->cp = cp;
  this->ville = ville;
  this->cedex = cedex;
  this->cedex_num = cedex_num;
  return is_valid();
}

std::string AdressePostale::get_numero()
{
  return numero;
}

std::string AdressePostale::get_rue()
{
  return rue;
}

std::string AdressePostale::get_comp()
{
  return comp;
}

std::string AdressePostale::get_cp()
{
  return cp;
}

std::string AdressePostale::get_ville()
{
  return ville;
}

bool AdressePostale::has_cedex()
{
  return cedex;
}

uint AdressePostale::get_cedex_num()
{
  return cedex_num;
}

void AdressePostale::set_numero(std::string num)
{
  numero = num;
}

void AdressePostale::set_rue(std::string rue)
{
  this->rue = rue;
}

void AdressePostale::set_comp(std::string comp)
{
  this->comp = comp;
}

void AdressePostale::set_cp(std::string cp)
{
  this->cp = cp;
}

void AdressePostale::set_ville(std::string ville)
{
  //virer cette ligne delete this->ville;
  this->ville = ville;
}

void AdressePostale::set_cedex_bool(bool has_cedex)
{
  cedex = has_cedex;
}

void AdressePostale::set_cedex_num(uint cedex_num)
{
  this->cedex_num = cedex_num;
}

AdressePostale &AdressePostale::operator=(AdressePostale &A)
{
  numero = A.numero;
  rue = A.rue;
  comp = A.comp;
  cp = A.cp;
  ville = A.ville;
  cedex = A.cedex;
  cedex_num = A.cedex_num;
  return (*this);
}

std::ostream &operator<<(std::ostream &o, AdressePostale &A)
{
  o << A.numero << " " << A.rue << std::endl;
  o << A.comp << std::endl;
  o << A.cp << " " << A.ville;
  if (A.cedex)
  {
    o << "cedex";
    if (A.cedex_num > 0)
      o << " " << A.cedex_num;
  }
  return o;
}

std::istream &operator>>(std::istream &i, AdressePostale &A)
{
  std::ostream &o = std::cout; //video
  o << "Entrez le numéro : ";
  A.numero = tools::getline(std::cin);
  o << std::endl
    << "Entrez la rue :";
  A.rue = tools::getline(std::cin);
  o << std::endl
    << "Entrez le complément d'adresse : ";
  A.comp = tools::getline(std::cin);
  o << std::endl
    << "Entrez le code postal :";
  A.cp = tools::getline(std::cin);
  o << std::endl
    << "Entrez la ville :";
  A.ville = tools::getline(std::cin);
  o << std::endl
    << "Y'a-t-il un cedex ? (o/n)";
  char has_cedex;
  std::cin >> has_cedex;
  if (has_cedex == 'o')
  {
    A.cedex = true;
    o << std::endl
      << "Entrez le numéro de cedex (0 s'il n'y en a pas) : ";
    std::cin >> A.cedex_num;
  }
  else
    A.cedex = false;
  return i;
}

/*
std::ofstream& operator<< (std::ofstream& o, AdressePostale &A); 

std::ifstream& operator>> (std::ifstream& i, AdressePostale &A); 
*/

#endif
