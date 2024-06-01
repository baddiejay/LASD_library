
namespace lasd {

/* ************************************************************************** */


template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
    table = Vector<Data>(tableSize);
    flags = Vector<char>(tableSize);
    
    initEmptyFlags();
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const unsigned long size) {
    tableSize = std::pow(2, std::ceil(log2((size < 128) ? 128 : size)));
    table = Vector<Data>(tableSize);
    flags = Vector<char>(tableSize);
    
    initEmptyFlags();
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> & container) : HashTableOpnAdr(container.Size()) {
    container.Traverse([this] (const Data& newData){
        Insert(newData);
    });
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> && container) noexcept : HashTableOpnAdr(container.Size()) {
    container.Map([this] (Data& newData){
        Insert(std::move(newData));
    });
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long size, const TraversableContainer<Data> & container) : HashTableOpnAdr(size){
    container.Traverse([this] (const Data& newData){
        Insert(newData);
    });
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long newSize, MappableContainer<Data> && container) noexcept : HashTableOpnAdr(size){
    container.Map([this] (Data& newData){
        Insert(std::move(newData));
    });
}

//COPY CONSTRUCTOR
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& hashTable) : HashTable<Data>(hashTable){ 
    if(tableSize > 0){
        table = Vector<Data>(hashTable.table);
        flags = Vector<char>(hashTable.flags);
    } //altrimenti restano a valori di default come già inizializzati
}

//MOVE CONSTRUCTOR
template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& hashTable) noexcept : HashTable<Data>(std::move(hashTable)){
    std::swap(table, hashTable.table);
    std::swap(flags, hashTable.flags);
}

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& hashTable) noexcept {
    if (this != &hashTable) { // Controllo di auto-assegnazione
        HashTable<Data>::operator=(std::move(hashTable)); // Assegnazione dei membri della classe base
        std::swap(table, hashTable.table); // Scambio delle risorse
        std::swap(flags, hashTable.flags);
    }
    return *this;
}

template <typename Data>
HashTableOpnAdr<Data> & HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data> & hashTable) {
    HashTableOpnAdr<Data> * tmp = new HashTableOpnAdr(hashTable);
    std::swap(*this,*tmp);
    delete tmp;
    return *this;
}

template<typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& hashTable) const noexcept {
    if (size!=hashTable.size) {
        return false;
    } else {
        for (unsigned long i=0; i<tableSize; i++) {
            if (flags[i]=='P') {  //Le celle marcate con P sono quelle dove effettivamente il dato è presente
                if (!hashTable.Exists(table[i])) {
                    return false;
                }
            }
        }
        return true;
    }
}

template<typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& table) const noexcept {
    return !(*this == table);
}

template<typename Data>
void HashTableOpnAdr<Data>::Resize(const unsigned long newSize) {
    if (newSize!=0){
        unsigned long newTableSize = (newSize <= 128)? 128 : std::pow(2, std::ceil(log2(newSize)));
        HashTableOpnAdr<Data> * tmp = new HashTableOpnAdr(newTableSize);
        
        for (unsigned long i=0; i<tableSize; i++) {
            if (flags[i]=='P') {
                tmp->Insert(table[i]);
            }
        }
        std::swap(*this,*tmp);
        
        delete tmp;
    } else {
        Clear();
        Resize(128);
    }
}

template<typename Data>
void HashTableOpnAdr<Data>::Clear() {
    initEmptyFlags();
    size = 0;
}

template<typename Data>
unsigned long HashTableOpnAdr<Data>::HashKey(const Data& data, unsigned long i) const noexcept {    
    return (HashKey(data) + (((i*i) + i)/2)) % tableSize;
}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& data)  {
    if (Exists(data)){
        return false;
    } else {
        unsigned long index = FindEmpty(data);

        table[index] = data;
        flags[index] = 'P';
        size++;

        if (size >= (tableSize/2)) {
            Resize(tableSize*2);
        }

        return true;
    }
}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& data) {
    if (Exists(data)){
        return false;
    } else {
        unsigned long index = FindEmpty(data);

        table[index] = std::move(data);
        flags[index] = 'P';
        size++;

        if (size >= (tableSize/2)) {
            Resize(tableSize*2);
        }

        return true;
    }    
}

template<typename Data>
unsigned long HashTableOpnAdr<Data>::FindEmpty(const Data& data) const noexcept {
    unsigned long i=0;

    while (true) {
        unsigned long emptyIndex = (HashKey(data, i)) % tableSize;

        if (flags[emptyIndex] == 'E' || flags[emptyIndex] == 'D') {
            return emptyIndex;
        }

        i++;
    }
}

template<typename Data>
unsigned long HashTableOpnAdr<Data>::Find(const Data& data) const noexcept {
    for (unsigned long i=0; i<tableSize; i++) {
        unsigned long findIndex = (HashKey(data, i));
        if (flags[findIndex] == 'P' && table[findIndex] == data) {
            return findIndex;
        }
    }

    return tableSize+1;
}

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& data) {
    unsigned long index = Find(data);
    
    if (index==tableSize+1) {
        return false;
    }

    flags[index] = 'D';
    size--;
    if (size < (tableSize/4)) {
        Resize(tableSize/2);
    }

    return true;

}


template<typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
    unsigned long index = Find(data);

    return (index!=tableSize+1);
}

/* ************************************************************************** */

}
