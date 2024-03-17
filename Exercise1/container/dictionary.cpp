
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const MappableContainer<Data> & container){
  bool inserted = false;

  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //Differenza di significato tra &= e =
  container.Map([this, &inserted] (const Data& d) {inserted &= Insert(d);});

  return inserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MutableMappableContainer<Data> && container){
  bool inserted = false;

  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //La move trasforma un lvalue in rvalue
  container.Map([this, &inserted] (const Data& d) {inserted &= Insert(std::move(d));});

  return inserted;
}

template<typename Data>
bool DictionaryContainer<Data>::RemoveAll(const MappableContainer<Data> & container) {
  bool removed = false;

  container.Map([this, &removed] (const Data& d){ removed &= Remove(d);});

  return removed;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const MappableContainer<Data> & container){
  bool inserted = false;

  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //Differenza di significato tra &= e =
  container.Map([this, &inserted] (const Data& d) {inserted |= Insert(d);});

  return inserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MutableMappableContainer<Data> && container){
  bool inserted = false;

  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //La move trasforma un lvalue in rvalue
  container.Map([this, &inserted] (const Data& d) {inserted |= Insert(std::move(d));});

  return inserted;
}

template<typename Data>
bool DictionaryContainer<Data>::RemoveSome(const MappableContainer<Data> & container) {
  bool removed = false;

  container.Map([this, &removed] (const Data& d){ removed |= Remove(d);});

  return removed;
}

/* ************************************************************************** */

}
