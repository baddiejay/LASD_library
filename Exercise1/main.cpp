#include <iostream>
#include "zlasdtest/test.hpp"
#include "vector/vector.hpp"
#include "list/list.hpp"
#include "zmytest/test.hpp"

using namespace lasd;

int main()
{
  int scelta = - 1;
  while(scelta != 0)
  {
    std::cout << std::endl;
    std::cout << "Laboratorio di algoritmi e strutture dati ES1 - Coppola Chiara - Matricola: N86004819" << std::endl;
    std::cout << "1) Test Professore Mogavero" << std::endl;
    std::cout << "2) Test personale Vettore e Lista" << std::endl;
    std::cout << "3) Test personale Stack e Coda" << std::endl;
    std::cout << "0) Per uscire dal programma" << std::endl;
    std::cin  >> scelta;
    if(scelta == 1)
      lasdtest();
    if(scelta == 2) 
      Menu();
    if(scelta == 3)
      MenuUtente();
  }


  return 0;
}
