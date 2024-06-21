
namespace lasd {

/* ************************************************************************** */

template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr(){
    delete[] table;
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
    table = new List<Data>[tableSize] {};
}


template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long size) {
    //Whatever the size, I want a power of 2. If the size is smaller than 128 I return 128   
    tableSize = std::pow(2, std::ceil(log2((size <= 128) ? 128 : size)));
    table = new List<Data>[tableSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data> & container) : HashTableClsAdr(container.Size()){
    InsertAll(container);
    /*
    container.Traverse([this] (const Data& newData){
        Insert(newData);
    });
    */
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data> && container) noexcept : HashTableClsAdr(container.Size()){
    InsertAll(std::move(container));
    /*
    container.Traverse([this] (Data& newData){
        Insert(std::move(newData));
    });
    */
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const unsigned long size, const TraversableContainer<Data> & container) : HashTableClsAdr(size){
    InsertAll(container);
    /*
    container.Traverse([this] (const Data& newData){
        Insert(newData);
    });
    */
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long size, MappableContainer<Data> && container) noexcept : HashTableClsAdr(size){
    InsertAll(std::move(container));
    /*
    container.Traverse([this] (Data& newData){
        Insert(std::move(newData));
    });
    */
}

//COPY CONSTRUCTOR
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& hashTable) : HashTable<Data>(hashTable) {
    if (tableSize > 0) {
        table = new lasd::List<Data>[tableSize] {};
        std::copy(hashTable.table, hashTable.table + tableSize, table);
    } else {
        table = nullptr;
    }
}

//MOVE CONSTRUCTOR
template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& hashTable) noexcept : HashTable<Data>(std::move(hashTable)){
    std::swap(table, hashTable.table);
}

template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& hashTable) noexcept {
    if (this != &hashTable) { 
        HashTable<Data>::operator=(std::move(hashTable)); 
        std::swap(table, hashTable.table);
    }
    return *this;
}

template <typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data> & hashTable) {
    if (this != &hashTable) { 
        HashTableClsAdr<Data> tmp(hashTable);
        std::swap(*this, tmp); 
    }
    return *this;
    /*
    if (this != &hashTable) { // Controllo di auto-assegnazione
        HashTableClsAdr<Data> * tmp = new HashTableClsAdr(hashTable);
        std::swap(*this, tmp);
        delete tmp;
    }
    return *this;
    */
    /*
    **VERSIONE STUDIO**
    if (this != &hashTable) { // Controllo di auto-assegnazione
        HashTable<Data>::operator=(hashTable); // Assegnazione dei membri della classe base
        
        lasd::List<Data>* newTable = new lasd::List<Data>[hashTable.tableSize] {};
        for (ulong i = 0; i < hashTable.tableSize; ++i) {
            newTable[i] = hashTable.table[i];
        }

        delete[] table; // Deallocazione della vecchia memoria
        table = newTable; // Assegnazione del nuovo array
    }
    return *this;*/
   
}

template<typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& hashTable) const noexcept {
    if (size != hashTable.size){
        return false;
    } else {
        bool equals = true;

        for (unsigned long i = 0; i < tableSize; i++) {
            table[i].Traverse(
              [&hashTable, &equals](const Data& dat) {
                 if (!hashTable.Exists(dat)) {
                    equals = false; // Element not found in the other hash table
                 }
              }
            );
            if(!equals) {
              return false; // If even one of the lists does not match, the hashtables are not equal
            }
	}
	
        return true; // If I exit the loop all calls to Exists are successful
    }
} 


template<typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& hashTable) const noexcept {
    return !(*this == hashTable);
}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) {
    if (table[HashKey(data)].Insert(data)) {
        size++;
        return true;
    } 
    
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) {
    if (table[HashKey(data)].Insert(std::move(data))) {
        size++;
        return true;
    } 
    
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& data){
    if (table[HashKey(data)].Remove(data)) {
        size--;
        return true;
    } 
    
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
    return table[HashKey(data)].Exists(data);
}

template<typename Data>
void HashTableClsAdr<Data>::Resize(const unsigned long newSize) {
    if (newSize!=0){
	unsigned long newTableSize = (newSize <= 128)? 128 : std::pow(2, std::ceil(log2(newSize)));
        HashTableClsAdr<Data> * tmp = new HashTableClsAdr(newTableSize);
        
        for (unsigned long i=0; i<tableSize; i++) {
            table[i].Traverse([tmp] (const Data& newData){
                tmp->Insert(newData);
            });
        }
        
        std::swap(*this,*tmp);
        delete tmp;
    } else {
        Clear();
        Resize(128);
    }
}

template<typename Data>
void HashTableClsAdr<Data>::Clear(){
    for (unsigned long i = 0; i < tableSize; i++) {
        if (table[i].Size()!=0) {
            table[i].Clear();
        }
    }

    size = 0;
}

/* ************************************************************************** */

}
