#include <iostream>
#include <string.h>
#include <string>
#include <typeinfo>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../container/container.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>    // std::shuffle

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../vector/vector.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

using std::cout;
using std::endl;
using std::cin;
using std::string;

namespace lasd
{

    std::string chars {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?"};
    std::random_device rd;
    std::mt19937 generator(rd());
    std::string rand_str (int length)
    {
      std::string output (chars);
      std::shuffle(output.begin(), output.end(), generator);
      return output.substr(0, length);
    }

  
  template<typename Data>
  Data getIndexOf(Vector<Data>& v, int index)
  {
    return v[index];
  }

  void riempi(Vector<std::string>& v)
  {
       for(unsigned int i=0; i < v.Size(); i++)
       {
         v[i] =  rand_str(v.Size());
       }
  }
  
  template<typename Data>
  void riempi(Vector<Data>& v)
  {
    Data dataRandom;
    srand ((unsigned int)time(NULL));
    //std::string type_name();

    for(unsigned int i = 0; i < v.Size(); i++)
    {
       dataRandom = (Data)(rand() % 10000) / 10;
       v[i] = dataRandom;
    }
  }

  template<typename Data>
  void riempi(List<Data>& list, unsigned int dim)
  {
    Data dataRandom;
    srand ((unsigned int)time(NULL));

    for(unsigned int i = 0; i < dim; i++)
    {
       dataRandom = (Data)(rand() % 10000) / 10;
       list.InsertAtBack(dataRandom);
    }
  }

  void riempi(List<std::string>& list, unsigned int dim)
  {
    for(unsigned int i=0; i < dim; i++)
    {
      list.InsertAtBack(rand_str(dim - 1));
    }
  }

  template <typename Data, typename Value>
Value FoldPreOrder(const lasd::PreOrderTraversableContainer<Data> & con, typename lasd::TraversableContainer<Data>::FoldFun<Value> fun, const Value & inival) {
 
   return con.PreOrderFold(fun, inival);

}

template <typename Data>
Data FoldAdd(const Data & dat, const Data & acc) {
  return (acc + dat);
}

template <typename Data>
float FoldMultiply(const Data & dat, const Data & acc) {
  return (acc * dat);
}

std::string FoldStringConcatenate(const std::string & dat, const std::string & acc) {
  std::string newstr = acc;
  newstr.append(dat);
  return newstr;
}

//*******************************************QUEUE

template<typename Data>
  void riempi(QueueVec<Data>& v, unsigned int dim)
  {
        Data dataRandom;
        srand ((unsigned int)time(NULL));

        for(unsigned int i = 0; i < dim; i++)
        {
           dataRandom = (Data)(rand() % 10000) / 10;
           v.Enqueue(dataRandom);
        }
  }
  
  void riempiString(QueueVec<string>& v, unsigned int dim)
  {
    for(unsigned int i=0; i < dim; i++)
    {
       v.Enqueue(rand_str(5));
    }
  }
  
  template<typename Data>
  void riempi(QueueLst<Data>& v, unsigned int dim)
  {
        Data dataRandom;
        srand ((unsigned int)time(NULL));
        for(unsigned int i = 0; i < dim; i++)
        {
           dataRandom = (Data)(rand() % 10000) / 10;
           v.Enqueue(dataRandom);
        }
  }
  
  void riempiString(QueueLst<string>& v, unsigned int dim)
  {
    for(unsigned int i=0; i < dim; i++)
    {
       v.Enqueue(rand_str(5));
    }
  }

void MenuQueue(int dato, int sceltaVettList, int n)
  {
    lasd::QueueVec<int>    queuevec_int;
    lasd::QueueVec<double> queuevec_double;
    lasd::QueueVec<float>  queuevec_float;
    lasd::QueueVec<string> queuevec_string;

    lasd::QueueLst<int>    queuelst_int;
    lasd::QueueLst<double> queuelst_double;
    lasd::QueueLst<float>  queuelst_float;
    lasd::QueueLst<string> queuelst_string;
    if(sceltaVettList == 1) //Caso Vettore
    {
        if(dato == 1)
        {
          riempi(queuevec_int, n);
        }
        if(dato == 2)
        {
          riempi(queuevec_double, n);
        }
        if(dato == 3)
        {
          riempi(queuevec_float, n);
        }
        if(dato == 4)
        {
          riempiString(queuevec_string, n);
        }
      }
    if(sceltaVettList == 2) //Caso Lista
    {
      if(dato == 1)
      {
        riempi(queuelst_int, n);
      }
      if(dato == 2)
      {
        riempi(queuelst_double, n);
      }
      if(dato == 3)
      {
        riempi(queuelst_float, n);
      }
      if(dato == 4)
      {
        riempiString(queuelst_string, n);
      }
  }
    int scelta = -1;
    while( scelta != 0)
    {
      if(sceltaVettList == 1)
        cout << "Benvenuto nello QueueVec - Menu" << endl;
      if(sceltaVettList == 2)
        cout << "Benvenuto nello QueueLst - Menu" << endl;

      cout << "1) Push " << endl;
      cout << "2) Pop " << endl;
      cout << "3) TopNPop" << endl;
      cout << "4) Top" << endl;
      cout << "5) Test Vuotezza" << endl;
      cout << "6) Dimensione Stack" << endl;
      cout << "7) Svuota Stack" << endl;
      cout << "0) Per uscire dal programma" << endl;
      cin  >> scelta;

      if(sceltaVettList == 1)
      {
        if(scelta == 1 && dato == 1)
        {
          int num = 0;
          cout << "Che elemento vuoi inserire nella Queue?" << endl;
          cin  >> num;
          queuevec_int.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 2)
        {
          double num = 0;
          cout << "Che elemento vuoi inserire nello Queue?" << endl;
          cin  >> num;
          queuevec_double.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 3)
        {
          float num = 0;
          cout << "Che elemento vuoi inserire nello Queue?" << endl;
          cin  >> num;
          queuevec_float.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 4)
        {
          std::string num;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          queuevec_string.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 2 && dato == 1)
        {
          cout << "Pop eseguito con successo" << endl;
          queuevec_int.Dequeue();
        }
        if(scelta == 2 && dato == 2)
        {
          cout << "Pop eseguito con successo" << endl;
          queuevec_double.Dequeue();
        }
        if(scelta == 2 && dato == 3)
        {
          cout << "Pop eseguito con successo" << endl;
          queuevec_float.Dequeue();
        }
        if(scelta == 2 && dato == 4)
        {
          cout << "Pop eseguito con successo" << endl;
          queuevec_string.Dequeue();
        }
        if(scelta == 3 && dato == 1)
        {
          cout << "Elemento Rimosso: " << queuevec_int.HeadNDequeue() << endl;
        }
        if(scelta == 3 && dato == 2)
        {
          cout << "Elemento Rimosso: " << queuevec_double.HeadNDequeue() << endl;
        }
        if(scelta == 3 && dato == 3)
        {
          cout << "Elemento Rimosso: " << queuevec_float.HeadNDequeue() << endl;
        }
        if(scelta == 3 && dato == 4)
        {
          cout << "Elemento Rimosso: " << queuevec_string.HeadNDequeue() << endl;
        }
        if(scelta == 4 && dato == 1)
        {
          cout << "Elemento : " << queuevec_int.Head() << endl;
        }
        if(scelta == 4 && dato == 2)
        {
          cout << "Elemento : " << queuevec_double.Head() << endl;
        }
        if(scelta == 4 && dato == 3)
        {
          cout << "Elemento : " << queuevec_float.Head() << endl;
        }
        if(scelta == 4 && dato == 4)
        {
          cout << "Elemento : " << queuevec_string.Head() << endl;
        }
        bool vuoto  = 0;
        if(scelta == 5 && dato == 1)
        {
          vuoto = queuevec_int.Empty();
        }
        if(scelta == 5 && dato == 2)
        {
          vuoto = queuevec_double.Empty();
        }
        if(scelta == 5 && dato == 3)
        {
          vuoto = queuevec_float.Empty();
        }
        if(scelta == 5 && dato == 4)
        {
          vuoto = queuevec_string.Empty();
        }
        if(scelta == 5)
        {
          if( vuoto == 1)
            cout << "StackVec vuoto" << endl;
          if( vuoto == 0)
            cout << "StackVec non vuoto" << endl;
        }
        unsigned long dimensione = 0;
        if(scelta ==6 && dato == 1)
        {
          dimensione = queuevec_int.Size();
        }
        if(scelta ==6 && dato == 2)
        {
          dimensione = queuevec_double.Size();
        }
        if(scelta ==6 && dato == 3)
        {
          dimensione = queuevec_float.Size();
        }
        if(scelta ==6 && dato == 4)
        {
          dimensione = queuevec_string.Size();
        }
        if(scelta == 6)
          cout << "Dimensione QueueVec: " << dimensione << endl;
        if(scelta == 7 && dato == 1)
          queuevec_int.Clear();
        if(scelta == 7 && dato == 2)
          queuevec_double.Clear();
        if(scelta == 7 && dato == 3)
          queuevec_float.Clear();
        if(scelta == 7 && dato == 4)
          queuevec_string.Clear();
        if(scelta == 7)
          cout << "QueueVec svuotato" << endl;
      }
      if(sceltaVettList == 2)
      {
        if(scelta == 1 && dato == 1)
        {
          int num = 0;
          cout << "Che elemento vuoi inserire nella Queue?" << endl;
          cin  >> num;
          queuelst_int.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 2)
        {
          double num = 0;
          cout << "Che elemento vuoi inserire nello Queue?" << endl;
          cin  >> num;
          queuelst_double.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 3)
        {
          float num = 0;
          cout << "Che elemento vuoi inserire nello Queue?" << endl;
          cin  >> num;
          queuelst_float.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 4)
        {
          std::string num;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          queuelst_string.Enqueue(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 2 && dato == 1)
        {
          cout << "Pop eseguito con successo" << endl;
          queuelst_int.Dequeue();
        }
        if(scelta == 2 && dato == 2)
        {
          cout << "Pop eseguito con successo" << endl;
          queuelst_double.Dequeue();
        }
        if(scelta == 2 && dato == 3)
        {
          cout << "Pop eseguito con successo" << endl;
          queuelst_float.Dequeue();
        }
        if(scelta == 2 && dato == 4)
        {
          cout << "Pop eseguito con successo" << endl;
          queuelst_string.Dequeue();
        }
        if(scelta == 3 && dato == 1)
        {
          cout << "Elemento Rimosso: " << queuelst_int.HeadNDequeue() << endl;
        }
        if(scelta == 3 && dato == 2)
        {
          cout << "Elemento Rimosso: " << queuelst_double.HeadNDequeue() << endl;
        }
        if(scelta == 3 && dato == 3)
        {
          cout << "Elemento Rimosso: " << queuelst_float.HeadNDequeue() << endl;
        }
        if(scelta == 3 && dato == 4)
        {
          cout << "Elemento Rimosso: " << queuelst_string.HeadNDequeue() << endl;
        }
        if(scelta == 4 && dato == 1)
        {
          cout << "Elemento : " << queuelst_int.Head() << endl;
        }
        if(scelta == 4 && dato == 2)
        {
          cout << "Elemento : " << queuelst_double.Head() << endl;
        }
        if(scelta == 4 && dato == 3)
        {
          cout << "Elemento : " << queuelst_float.Head() << endl;
        }
        if(scelta == 4 && dato == 4)
        {
          cout << "Elemento : " << queuelst_string.Head() << endl;
        }
        bool vuoto = 0;
        if(scelta == 5 && dato == 1)
        {
          vuoto = queuelst_int.Empty();
        }
        if(scelta == 5 && dato == 2)
        {
          vuoto = queuelst_double.Empty();
        }
        if(scelta == 5 && dato == 3)
        {
          vuoto = queuelst_float.Empty();
        }
        if(scelta == 5 && dato == 4)
        {
          vuoto = queuelst_string.Empty();
        }
        if(scelta == 5)
        {
          if( vuoto == 1)
            cout << "StackVec vuoto" << endl;
          if( vuoto == 0)
            cout << "StackVec non vuoto" << endl;
        }
        unsigned long dimensione = 0;
        if(scelta ==6 && dato == 1)
        {
          dimensione = queuelst_int.Size();
        }
        if(scelta ==6 && dato == 2)
        {
          dimensione = queuelst_double.Size();
        }
        if(scelta ==6 && dato == 3)
        {
          dimensione = queuelst_float.Size();
        }
        if(scelta ==6 && dato == 4)
        {
          dimensione = queuelst_string.Size();
        }
        if(scelta == 6)
          cout << "Dimensione QueueVec: " << dimensione << endl;
        if(scelta == 7 && dato == 1)
          queuelst_int.Clear();
        if(scelta == 7 && dato == 2)
          queuelst_double.Clear();
        if(scelta == 7 && dato == 3)
          queuelst_float.Clear();
        if(scelta == 7 && dato == 4)
          queuelst_string.Clear();
        if(scelta == 7)
          cout << "QueueVec svuotato" << endl;
      }
    }

  }

//*******************************************STACK

template<typename Data>
  void riempi(StackVec<Data>& v, unsigned int dim)
  {
        Data dataRandom;
        srand ((unsigned int)time(NULL));

        for(unsigned int i = 0; i < dim; i++)
        {
           dataRandom = (Data)(rand() % 10000) / 10;
           v.Push(dataRandom);
        }
}

void riempiString(StackVec<string>& v, unsigned int dim)
  {
    for(unsigned int i=0; i < dim; i++)
    {
       v.Push(rand_str(5));
    }
}

template<typename Data>
  void riempi(StackLst<Data>& v, unsigned int dim)
  {
        Data dataRandom;
        srand ((unsigned int)time(NULL));
        for(unsigned int i = 0; i < dim; i++)
        {
           dataRandom = (Data)(rand() % 10000) / 10;
           v.Push(dataRandom);
        }
  }
  
void riempiString(StackLst<string>& v, unsigned int dim)
  {
    for(unsigned int i=0; i < dim; i++)
    {
       v.Push(rand_str(5));
    }
  }

void MenuStack(int dato, int sceltaVettList, int n)
  {
    lasd::StackVec<int>    stackvec_int;
    lasd::StackVec<double> stackvec_double;
    lasd::StackVec<float>  stackvec_float;
    lasd::StackVec<string> stackvec_string;

    lasd::StackLst<int>    stacklst_int;
    lasd::StackLst<double> stacklst_double;
    lasd::StackLst<float>  stacklst_float;
    lasd::StackLst<string> stacklst_string;

    if(sceltaVettList == 1) //Caso Vettor    if(dato == 1)
    {
      {
        riempi(stackvec_int, n);
      }
      if(dato == 2)
      {
        riempi(stackvec_float, n);
      }
      if(dato == 3)
      {
        riempiString(stackvec_string, n);
      }
    }
    if(sceltaVettList == 2) //Caso Lista
    {
      if(dato == 1)
      {
        riempi(stacklst_int, n);
      }
      if(dato == 2)
      {
        riempi(stacklst_float, n);
      }
      if(dato == 3)
      {
        riempiString(stacklst_string, n);
      }
    }

    //Inizia il Menu di Stack
    int scelta = -1;
    while( scelta != 0)
    {
      cout << endl;
      if(sceltaVettList == 1)
        cout << "StackVec - Menu" << endl;
      if(sceltaVettList == 2)
        cout << "StackLst - Menu" << endl;

      cout << "1) Push " << endl;
      cout << "2) Pop " << endl;
      cout << "3) TopNPop" << endl;
      cout << "4) Top" << endl;
      cout << "5) Test Vuotezza" << endl;
      cout << "6) Dimensione Stack" << endl;
      cout << "7) Svuota Stack" << endl;
      cout << "0) Per uscire dal programma" << endl;
      cin  >> scelta;

      if(sceltaVettList == 1)
      {
        if(scelta == 1 && dato == 1)
        {
          int num = 0;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          stackvec_int.Push(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 2)
        {
          float num = 0;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          stackvec_float.Push(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 3)
        {
          std::string num;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          stackvec_string.Push(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 2 && dato == 1)
        {
          cout << "Pop eseguito con successo" << endl;
          stackvec_int.Pop();
        }
        if(scelta == 2 && dato == 2)
        {
          cout << "Pop eseguito con successo" << endl;
          stackvec_float.Pop();
        }
        if(scelta == 2 && dato == 3)
        {
          cout << "Pop eseguito con successo" << endl;
          stackvec_string.Pop();
        }
        if(scelta == 3 && dato == 1)
        {
          cout << "Elemento Rimosso: " << stackvec_int.TopNPop() << endl;
        }
        if(scelta == 3 && dato == 2)
        {
          cout << "Elemento Rimosso: " << stackvec_float.TopNPop() << endl;
        }
        if(scelta == 3 && dato == 3)
        {
          cout << "Elemento Rimosso: " << stackvec_string.TopNPop() << endl;
        }
        if(scelta == 4 && dato == 1)
        {
          cout << "Elemento : " << stackvec_int.Top() << endl;
        }
        if(scelta == 4 && dato == 2)
        {
          cout << "Elemento : " << stackvec_float.Top() << endl;
        }
        if(scelta == 4 && dato == 3)
        {
          cout << "Elemento : " << stackvec_string.Top() << endl;
        }
        bool vuoto = 0;
        if(scelta == 5 && dato == 1)
        {
          vuoto = stackvec_int.Empty();
        }
        if(scelta == 5 && dato == 2)
        {
          vuoto = stackvec_float.Empty();
        }
        if(scelta == 5 && dato == 3)
        {
          vuoto = stackvec_string.Empty();
        }
        if(scelta == 5)
        {
          if( vuoto == 1)
            cout << "StackVec vuoto" << endl;
          if( vuoto == 0)
            cout << "StackVec non vuoto" << endl;
        }
        unsigned long dimensione = 0;
        if(scelta ==6 && dato == 1)
        {
          dimensione = stackvec_int.Size();
        }
        if(scelta ==6 && dato == 2)
        {
          dimensione = stackvec_float.Size();
        }
        if(scelta ==6 && dato == 3)
        {
          dimensione = stackvec_string.Size();
        }
        if(scelta == 6)
          cout << "Dimensione StackVec: " << dimensione << endl;
        if(scelta == 7 && dato == 1)
          stackvec_int.Clear();
        if(scelta == 7 && dato == 2)
          stackvec_float.Clear();
        if(scelta == 7 && dato == 3)
          stackvec_string.Clear();
        if(scelta == 7)
          cout << "StackVec svuotato" << endl;
     }
      if(sceltaVettList == 2)
      {
        if(scelta == 1 && dato == 1)
        {
          int num = 0;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          stacklst_int.Push(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 2)
        {
          float num = 0;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          stacklst_float.Push(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 1 && dato == 3)
        {
          std::string num;
          cout << "Che elemento vuoi inserire nello Stack?" << endl;
          cin  >> num;
          stacklst_string.Push(num);
          cout << "Push effettuato" << endl;
        }
        if(scelta == 2 && dato == 1)
        {
          cout << "Pop eseguito con successo" << endl;
          stacklst_int.Pop();
        }
        if(scelta == 2 && dato == 2)
        {
          cout << "Pop eseguito con successo" << endl;
          stacklst_float.Pop();
        }
        if(scelta == 2 && dato == 3)
        {
          cout << "Pop eseguito con successo" << endl;
          stacklst_string.Pop();
        }
        if(scelta == 3 && dato == 1)
        {
          cout << "Elemento Rimosso: " << stacklst_int.TopNPop() << endl;
        }
        if(scelta == 3 && dato == 2)
        {
          cout << "Elemento Rimosso: " << stacklst_float.TopNPop()<< endl;
        }
        if(scelta == 3 && dato == 3)
        {
          cout << "Elemento Rimosso: " << stacklst_string.TopNPop() << endl;
        }
        if(scelta == 4 && dato == 1)
        {
          cout << "Elemento : " << stacklst_int.Top() << endl;
        }
        if(scelta == 4 && dato == 2)
        {
          cout << "Elemento : " << stacklst_float.Top()<< endl;
        }
        if(scelta == 4 && dato == 3)
        {
          cout << "Elemento : " << stacklst_string.Top()<< endl;
        }
        bool vuoto = 0;
        if(scelta == 5 && dato == 1)
        {
          vuoto = stacklst_int.Empty();
        }
        if(scelta == 5 && dato == 2)
        {
          vuoto = stacklst_float.Empty();
        }
        if(scelta == 5 && dato == 3)
        {
          vuoto = stacklst_string.Empty();
        }
        if(scelta == 5)
        {
          if( vuoto == 1)
            cout << "StackVec vuoto" << endl;
          if( vuoto == 0)
            cout << "StackVec non vuoto" << endl;
        }
        unsigned long dimensione = 0;
        if(scelta ==6 && dato == 1)
        {
          dimensione = stacklst_int.Size();
        }
        if(scelta ==6 && dato == 2)
        {
          dimensione = stackvec_float.Size();
        }
        if(scelta ==6 && dato == 3)
        {
          dimensione = stacklst_string.Size();
        }
        if(scelta == 6)
          cout << "Dimensione StackVec: " << dimensione << endl;
        if(scelta == 7 && dato == 1)
          stacklst_int.Clear();
        if(scelta == 7 && dato == 2)
          stacklst_float.Clear();
        if(scelta == 7 && dato == 3)
          stacklst_string.Clear();
        if(scelta == 7)
          cout << "StackVec svuotato";
      }
    }
}

void MenuUtente()
  {
    int sceltaStruttura = 0;
    int sceltaVettList  = 0;
    int tipo = 0;
    int n = 0;
    cout << endl;
    std::cout << "Benvenuto nel test personale dell'esercizio 1 di LASD" << std::endl;
    cout << "Scegli cosa utilizzare: " << endl;
    cout << "1) Stack" << endl;
    cout << "2) Queue" << endl;
    cin  >> sceltaStruttura;
    cout << endl;
    cout << "Scegli tra Vettori o Liste" << endl;
    cout << "1) Vettore" << endl;
    cout << "2) Lista" << endl;
    cin  >> sceltaVettList;
    cout << endl;
    cout << "Che tipo di dato vuoi utilizzare?" << endl;
    cout << "1) Int" << endl;
    cout << "2) Double" << endl;
    cout << "3) Float" << endl;
    cout << "4) String" << endl;
    cin  >> tipo;
    cout << endl;
    cout << "Quanti elementi vuoi inserire nella struttura?" << endl;
    cin  >> n;
    cout << endl;
    
    if(sceltaStruttura == 1)
      MenuStack(tipo, sceltaVettList, n);
    if(sceltaStruttura == 2)
      MenuQueue(tipo, sceltaVettList, n);
}

//***********************VETTORE E LISTA
void Menu() {
        int scelta, type = 0;
        int index = 0;
        int x = -1;
        int n = 0; //dimensione struttura

	std::cout << std::endl;
        //Scelta struttura da utilizzare Lista o Vettore
        std::cout << "Benvenuto nel test personale dell'esercizio 1 di LASD" << std::endl;
        std::cout << "Scegli una struttura da utillizzare: " << std::endl << "1) Vettore" << std::endl << "2) Lista" << std::endl;
        std::cin  >>  scelta;
        std::cout << std::endl;
        std::cout << "Che tipo di dati vuoi utilizzare? "<< std::endl << "1) Int" << std::endl << "2) Float" << std::endl << "3) String" << std::endl;
        std::cin  >> type;
        std::cout << std::endl;
        std::cout << "Inserisci la sua dimensione " << std::endl;
        std::cin  >> n;

        Vector<int>         v1(n);
        Vector<float>       v3(n);
        Vector<std::string> v4(n);
        List<int>           l1;
        List<float>         l3;
        List<std::string>   l4;

        if( scelta == 1) // Scelta Vettore
        {
          if(type == 1) // INT
          {
              riempi(v1);
          }
          if(type == 2)// FLOAT
          {
              riempi(v3);
          }
          if(type == 3)// STRING
          {
              riempi(v4);
          }
        }
        if( scelta == 2) // Scelta Lista
        {
          if(type == 1) // INT
          {
              riempi(l1, n);
          }
          if(type == 2)// FLOAT
          {
              riempi(l3, n);
          }
          if(type == 3)// STRING
          {
              riempi(l4, n);
          }
        }

        if( scelta == 1)
          while( x != 0)
          {
            std::cout << std::endl;
            std::cout << "Scegli la funzionalità da testare:" << std::endl;
            std::cout << "1)Ottieni il primo elemento" << std::endl;
            std::cout << "2)Ottieni l'elemento nella posizione scelta" << std::endl;
            std::cout << "3)Ottieni l'ultimo elemento" << std::endl;
            std::cout << "4)Stampa tutto il vettore" << std::endl;
            std::cout << "5)Vuoi cercare un elemento all'interno del vettore?" << std::endl;
            std::cout << "6)Funzioni applicabili con FOLD al tuo tipo: somma(int), prodotto(float), concatenazione(string)" << std::endl;
            std::cout << "7)Funzioni applicabili con MAP al tuo tipo: 2n(int), n^2(float), uppercase(string)" << std::endl;
            std::cout << "0)Se vuoi uscire dal programma"<< std::endl;
            std::cin  >> x;
	    std::cout << std::endl;
	    
            if(type == 1 && x == 1)
            {
              int first;
              first = v1.Front();
              std::cout<<"Primo elemento[0] = " << first << std::endl;
            }
            if(type == 2 && x == 1)
            {
              float first;
              first = v3.Front();
              std::cout<<"Primo elemento[0] = " << first << std::endl;
            }
            if(type == 3 && x == 1)
            {
              std::string first;
              first = v4.Front();
              std::cout<<"Primo elemento[0] = " << first << std::endl;
            }
            if(x == 2)
            {
                std::cout << "Inserisci la posizione da mostrare (partendo da 0) ";
                std::cin >> index;
            }
            if(type == 1 && x == 2)
            {
              int first;
              first = getIndexOf(v1,index);
              std::cout<<"Elemento["<<index<<"]"<< " = " << first << std::endl;
            }
            if(type == 2 && x == 2)
            {
              float first;
              first = getIndexOf(v3,index);
              std::cout<<"Elemento["<<index<<"]"<< " = " << first << std::endl;
            }
            if(type == 3 && x == 2)
            {
              std::string first;
              first = getIndexOf(v4,index);
              std::cout<<"Elemento["<<index<<"]"<< " = " << first << std::endl;
            }
            if(type == 1 && x == 3)
            {
              int first;
              first = v1.Back();
              std::cout<<"Ultimo elemento["<< v1.Size() - 1 << "] = " << first << std::endl;
            }
            if(type == 2 && x == 3)
            {
              float first;
              first = v3.Back();
              std::cout<<"Ultimo elemento["<< v3.Size() - 1 << "] = " << first << std::endl;
            }
            if(type == 3 && x == 3)
            {
              std::string first;
              first = v4.Back();
              std::cout<<"Ultimo elemento["<< v4.Size() - 1 << "] = " << first << std::endl;
            }
            //PRINT VETTORE
            if(x == 4)
              std::cout << "Ecco il vettore:" << std::endl;
            if(type == 1 && x == 4)
            {
              v1.PreOrderTraverse([](const int& dat){std::cout << dat << std::endl;});
            }
            if(type == 2 && x == 4)
            {
              v3.PreOrderTraverse([](const float& dat){std::cout << dat<< std::endl;});
            }
            if(type == 3 && x == 4)
            {
              v4.PreOrderTraverse([](const std::string& dat){std::cout << dat<< std::endl;});
            }
            //EXIST ELEMENT
            if(x == 5)
            {
              std::cout << "Che elemento vuoi ricercare all'interno del vettore?" << std::endl;
            }
            bool exist;
            if(type == 1 && x == 5)
            {
              int search_element;
              std::cin  >> search_element;
              exist = v1.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 2 && x == 5)
            {
              float search_element;
              std::cin  >> search_element;
              exist = v3.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 3 && x == 5)
            {
              std::string search_element;
              std::cin  >> search_element;
              exist = v4.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            //BEGIN FUNZIONI FOLD VECTOR
            if(type == 1 &&  x == 6)
            {
              std::cout << "La somma di tutti i valori nel container è " << FoldPreOrder(v1, &FoldAdd<int>, 0) << std::endl;
            }
            if(type == 2 && x == 6)
            {
              std::cout << "Il prodotto di tutti i valori nel container è " << (float)FoldPreOrder(v3, &FoldMultiply<float>, (float)1) << std::endl;
            }
            if(type == 3 && x == 6)
            {
	      std::cout << "Il risultato della concatenazione delle stringhe nel container è " << FoldPreOrder(v4, &FoldStringConcatenate, std::string("")) << std::endl;
            }
            // END FUNZIONI FOLD VECTOR

            //Passo 7)
            if(x == 7 && type == 1)
            {
                v1.PreOrderMap([](int& dat){
                dat=dat*2;
                });
                std::cout << "Funzione 2n (INT) applicata alla tua struttura" << std::endl;
            }
            if( x == 7 && type == 2)
            {
                v3.PreOrderMap([](float& dat){
                dat=dat*dat;
                });
                std::cout << "Funzione n^2 (FLOAT) applicata alla tua struttura" << std::endl;
            }
            if( x == 7 && type == 3)
            {
                v4.PreOrderMap([](std::string& dat)
                {
                  for (char& c : dat)
                  {
                    c = toupper(c);
                  }
                });
                std::cout << "Funzione uppercase applicata alla struttura" << std::endl;
            }
          }

        if(scelta == 2)
        {
          while( x != 0)
          {
            std::cout << std::endl;
            std::cout << "Benvenuto nel menu delle funzioni della lista, puoi utilizzare le seguenti funzionalità:" << std::endl;
            std::cout << "1)Ottieni il primo elemento" << std::endl;
            std::cout << "2)Ottieni l'elemento nella posizione scelta" << std::endl;
            std::cout << "3)Ottieni l'ultimo elemento" << std::endl;
            std::cout << "4)Stampa tutta la lista" << std::endl;
            std::cout << "5)Vuoi cercare un elemento all'interno della lista?" << std::endl;
            std::cout << "6)Funzioni FOLD applicabili al tuo tipo: somma(int), prodotto(float), concatenazione(string) " << std::endl;
            std::cout << "7)Funzioni MAP applicabili al tuo tipo: 2n(int), n^2(float), uppercase(string)" << std::endl;
            std::cout << "0)Se vuoi uscire dal programma"<< std::endl;
            std::cin  >> x;
	    std::cout << std::endl;
	    
            if(type == 1 && x == 1)
            {
              std::cout << l1.Front() << std::endl;
            }
            if(type == 2 && x == 1)
            {
              std::cout << l3.Front() << std::endl;
            }
            if(type == 3 && x == 1)
            {
              std::cout << l4.Front() << std::endl;
            }

            if(x==2)
            {
              std::cout << "Inserisci la posizione da mostrare (partendo da 0) " << std::endl;
              std::cin  >> index;
            }
            if(type == 1 && x == 2)
            {
              std::cout << l1[index] << std::endl;
            }
            if(type == 2 && x == 2)
            {
              std::cout << l3[index] << std::endl;
            }
            if(type == 3 && x == 2)
            {
              std::cout << l4[index] << std::endl;
            }

            if(type == 1 && x == 3)
            {
              std::cout << l1.Back() << std::endl;
            }
            if(type == 2 && x == 3)
            {
              std::cout << l3.Back() << std::endl;
            }
            if(type == 3 && x == 3)
            {
              std::cout << l4.Back() << std::endl;
            }


            if(type == 1 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              std::cout << "HEAD -> ";
              l1.PreOrderMap([](int& dat){std::cout << dat << " -> ";});
              std::cout << "NULL" << std::endl;
            }
            if(type == 2 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              std::cout << "HEAD -> ";
              l3.PreOrderMap([](float& dat){std::cout << dat << " -> ";});
              std::cout << "NULL" << std::endl;
            }
            if(type == 3 && x == 4)
            {
              std::cout << "Ecco la lista stampata" << std::endl;
              std::cout << "HEAD -> ";
              l4.PreOrderMap([](std::string& dat){std::cout << dat << " -> ";});
              std::cout << "NULL" << std::endl;
            }
            //EXIST ELEMENT
            if(x == 5)
            {
              std::cout << "Che elemento vuoi ricercare all'interno della Lista?" << std::endl;
            }
            bool exist;
            if(type == 1 && x == 5)
            {
              int search_element;
              std::cin  >> search_element;
              exist = l1.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 2 && x == 5)
            {
              float search_element;
              std::cin  >> search_element;
              exist = l3.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            if(type == 3 && x == 5)
            {
              std::string search_element;
              std::cin  >> search_element;
              exist = l4.Exists(search_element);
              if(exist)
                std::cout << "Elemento " << search_element << " esiste" << std::endl;
              else
                std::cout << "Elemento " << search_element << " non esiste" << std::endl;
            }
            //BEGIN FUNZIONI FOLD LIST
            if(type == 1 &&  x == 6)
            {
              std::cout << "La somma di tutti i valori nel container è " << FoldPreOrder(l1, &FoldAdd<int>, 0) << std::endl;
            }
            if(type == 2 && x == 6)
            {
              std::cout << "Il prodotto di tutti i valori nel container è " << (float)FoldPreOrder(l3, &FoldMultiply<float>, (float)1) << std::endl;
            }
            if(type == 3 && x == 6)
            {
	      std::cout << "Il risultato della concatenazione delle stringhe nel container è " << FoldPreOrder(l4, &FoldStringConcatenate, std::string("")) << std::endl;
            }
            // END FUNZIONI FOLD LIST
            if(x == 7 && type == 1)
            {
                l1.PreOrderMap([](int& dat){
                dat=dat*2;
                });
                std::cout << "Funzione 2n (INT) applicata alla tua struttura" << std::endl << std::endl;
            }
            if( x == 7 && type == 2)
            {
                l3.PreOrderMap([](float& dat){
                dat=dat*dat;
                });
                std::cout << "Funzione n^2 (FLOAT) applicata alla tua struttura" << std::endl << std::endl;
            }
            if( x == 7 && type == 3)
            {
                l4.PreOrderMap([](std::string& dat)
                {
                  for (char& c : dat)
                  {
                    c = toupper(c);
                  }
                });
                std::cout << "Funzione uppercase applicata alla struttura" << std::endl << std::endl;
            }
        }
      }
    }
}
