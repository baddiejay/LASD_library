
namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & container){
  bool inserted = true;
  container.Traverse(
    [this, &inserted] (const Data& d) {
        inserted &= Insert(d);
        }
    );

  return inserted;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && container){
  bool inserted = true;
  container.Map(
    [this, &inserted] (const Data& d) {
        inserted &= Insert(std::move(d));
        }
    );

  return inserted;
}

template<typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & container) {
  bool removed = true;

  container.Traverse(
    [this, &removed] (const Data& d){ 
        removed &= Remove(d);
        }
    );

  return removed;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & container){
  bool inserted = false;

  container.Traverse(
    [this, &inserted] (const Data& d) {
        inserted |= Insert(d);
        }
    );

  return inserted;
}


template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && container){
  bool inserted = false;

  container.Map(
    [this, &inserted] (const Data& d) {
        inserted |= Insert(std::move(d));
        }
    );

  return inserted;

}

template<typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & container) {
  bool removed = false;

  container.Traverse(
    [this, &removed] (const Data& d){ 
        removed |= Remove(d);
        }
    );

  return removed;
}

/* ************************************************************************** */

}
