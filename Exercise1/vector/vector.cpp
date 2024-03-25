
namespace lasd {

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const unsigned long newsize){
  //Initialising the vector with empty elements with curly brackets
  elements = new Data[newsize] {};
  size = newsize;
}

template <typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& mc){
  //Scan the container and populate my array cell by cell
  //MappableContainer doesn't have operator[], but I can use the map function
  size = mc.Size();
  elements = new Data[size];
  unsigned long i = 0;
  
  mc.Map([this, &i] (const Data& data) {elements[i++] = data;});
}

template <typename Data>
Vector<Data>::Vector(MutableMappableContainer<Data>&& mmc) noexcept{
  //Since it is mutable I can modify it then better build by move.
  size = mmc.Size();
  elements = new Data[size];
  unsigned long i = 0;
  
  mmc.Map([this, &i] (const Data& data) {elements[i++] = std::move(data);});
}

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& v){
  elements = new Vector[v.size];

  //First element, last element and where to put it. The more expensive the copy, the larger the container. Linear on size
  std::copy(v.elements,v.elements + v.size, elements);
  size = v.size;
}

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& v) noexcept{
  //exchange the value of the former with the value contained in the latter. Two constant-time operations independent of container size. 
  //Having pointer pointing to the beginning and the size I can access the whole structure with pointer arithmetic
  std::swap(elements,v.elements);
  std::swap(size,v.size);
}

template <typename Data>
Vector<Data>::~Vector(){
  delete [] elements;
}

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& v){
  //Creating a new Vector using the copy constructor
  Vector<Data>* tmp = new Vector<Data>(v);
  //Swapping data between this object and my new vector
  std::swap(*tmp,*this);
  //After the exchange this contains the data in v so I can delete tmp and return this
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
  //Deleting what's inside the vector
  delete[] elements;
  //Setting the pointer to null
  elements = nullptr;
  size = 0;
}

template <typename Data>
void Vector<Data>::Resize(const unsigned long new_dim){
  //Allocate new vector, make the copy and deallocate the old one or even decrease it given the new vector size I want
  if(new_dim == 0)
    Clear();
  else if(size != new_dim){
    Data* tmp = new Data[new_dim]{};
    //In this new vector I have to copy all the elements of the previous one. If I am shortening the vector I have to stop until I have space
    unsigned long limit = (size < new_dim) ? size : new_dim;
    for(unsigned long i = 0; i < limit; i++)
      std::swap(tmp[i],elements[i]);
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
    //Repeat until I find an element that violates my condition. I repeat until I find an element smaller than the pivot
    do{
      j--;
    } while (pivot < elements[i]);  //As soon as I find an element smaller than the pivot I switch to the other index
    do{
      j--;
    } while (pivot > elements[i]); //As soon as I find an element larger than the pivot I switch to the other index
    if(i < j){
      std::swap(elements[i],elements[j]);    
    }
  //When i > j the loops end since the index are crossed and no more elements remains
  } while (i < j);
  
  return j;
}
/* ************************************************************************** */

}
