
namespace lasd {

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const unsigned long newsize){
  //Inizializzo gli elementi a vuoto con le parentesi graffe
  elements = new Data[newsize] {};
  size = newsize;
}

template <typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& mc){
  //Mappable non ha l'operatore [], posso però usare la map
  size = mc.Size();
  elements = new Data[size];
  unsigned long i = 0;
  
  mc.Map([this, &i] (const Data& data) {elements[i++] = data;});
}

template <typename Data>
Vector<Data>::Vector(MutableMappableContainer<Data>&& mmc) noexcept{
  //Mappable non ha l'operatore [], posso però usare la map
  size = mmc.Size();
  elements = new Data[size];
  unsigned long i = 0;
  
  mmc.Map([this, &i] (const Data& data) {elements[i++] = std::move(data);});
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& v){
  elements = new Vector[v.size];
  //primo elemento, ultimo elemento e dove lo devo mettere. Copia tanto più costosa quanto è grande il contenitore. Lineare sulla dimensione
  std::copy(v.elements,v.elements + v.size, elements);
  size = v.size;
}

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& v) noexcept{
  //scambio il valore del primo con quello contenuto nel secondo. Due operazioni a tempo costante indipendenti dalla dimensione del container
  std::swap(elements,v.elements);
  std::swap(size,v.size);
}

template <typename Data>
Vector<Data>::~Vector(){
  delete [] elements;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& v){
  //Copio in un contenitore vector già esistente il contenuto di un altro
  Vector<Data>* tmp = new Vector<Data>(v);
  //Scambio dei dati tra il nuovo vettore e me stesso
  std::swap(*tmp,*this);
  //Dopo lo scambio contiene i dati presenti in v
  delete tmp;
  return *this;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data> && v) noexcept{
  std::swap(elements,v.elements);
  std::swap(size,v.size);
  return *this;
}

template <typename Data>
bool inline Vector<Data>::operator==(const Vector<Data>& v) const noexcept{
  if(size != v.size())
    return false;
  for(unsigned long i = 0; i < size; i++){
    if(elements[i] != v[i])
      return false;
  }
    return true;
}

template <typename Data>  
bool inline Vector<Data>::operator!=(const Vector<Data>& v) const noexcept{
  return !(*this == v);
}

template <typename Data>
void Vector<Data>::Clear() noexcept{
  //Cancella il contenuto di elements
  delete[] elements;
  //Setta il puntatore a null
  elements = nullptr;
  //imposta la size a 0
  size = 0;
}

template <typename Data>
void Vector<Data>::Resize(const unsigned long new_dim){
  if(new_dim == 0)
    Clear();
  else if(size != new_dim){
    Data* tmp = new Data[new_dim]{};
    //In questo nuovo vettore devo copiare tutti gli elementi del precedente. Se sto accorciando il vettore mi devo fermare fino a che ho spazio
    unsigned long limit = (size < new_dim) ? size : new_dim;
    for(unsigned long i = 0; i < limit; i++)
      std::swap(tmp[i],elements[i]);
    //swap dei puntatori così che tmp diventi il mio elemets
    std::swap(tmp,elements); 
    size = new_dim;
    delete[] tmp;
  }
}

template <typename Data>
const Data& Vector<Data>::operator[](const unsigned long pos) const{
  if(pos < size)
    return elements[pos];
  else
    throw std::out_of_range("Trying to access at index " + std::to_string(pos) + " of an array of size " + std::to_string(size));
}

template <typename Data>
Data& Vector<Data>::operator[](const unsigned long pos){
  if(pos < size)
    return elements[pos];
  else
    throw std::out_of_range("Trying to access at index " + std::to_string(pos) + " of an array of size " + std::to_string(size));
}

template <typename Data>
const Data& Vector<Data>::Front() const{
  if(size != 0)
    return elements[0];
  else
    throw std::length_error("Trying to access the front of an empty array");
}

template <typename Data>
Data& Vector<Data>::Front(){
  if(size != 0)
    return elements[0];
  else
    throw std::length_error("Trying to access the front of an empty array");
}

template <typename Data>
const Data& Vector<Data>::Back() const{
  if(size != 0)
    return elements[size - 1];
  else
    throw std::length_error("Trying to access the back of an empty array");
}

template <typename Data>
Data& Vector<Data>::Back(){
  if(size != 0)
    return elements[size - 1];
  else
    throw std::length_error("Trying to access the back of an empty array");
}

template <typename Data>
void Vector<Data>::Sort() noexcept{
  if(size > 1)
    quickSort(0, size - 1);
}

template <typename Data>
void Vector<Data>::quickSort(unsigned long p, unsigned long r) noexcept{
  if(p < r) {
    unsigned long q = partition(p,r);
    quickSort(p,q);
    quickSort(q+1,r);
  }
}

template <typename Data>
unsigned long Vector<Data>::partition(unsigned long p, unsigned long r) noexcept{
  Data pivot = elements[p];
  
  unsigned long i = p-1;
  unsigned long j = r+1;
  
  do{
    //Ripeto fino a che non trovo un elemento che viola la mia condizione. Ripeto fino a che non trovo un elemento più piccolo del pivot
    do{
      j--;
    } while (pivot < elements[i]);  //Appena trovo un elements più piccolo del pivot passo all'altro indice
    do{
      j--;
    } while (pivot > elements[i]); //Appena trovo un elements più grande del pivot passo all'altro indice
    if(i < j){
      std::swap(elements[i],elements[j]);    
    }
  } while (i < j);
  
  return j;
}
/* ************************************************************************** */

}
