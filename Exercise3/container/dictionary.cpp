
namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & container){
  bool inserted = true;
  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
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
  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //La move trasforma un lvalue in rvalue
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

  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //Differenza di significato tra &= e =
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

  //Qui (come nel caso del long di size) ha senso catturare per riferimento o meglio la copia?
  //La move trasforma un lvalue in rvalue
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
