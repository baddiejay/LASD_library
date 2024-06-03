namespace lasd {

/* ************************************************************************** */

//**************** HASHABLE *********************
template <>
class Hashable<int> {
    public:
        unsigned long operator()(const int & dat) const noexcept {
            return dat * dat;
        }
};

template<>
class Hashable<std::string> {
    public:
    //DJB2
        unsigned long operator()(const std::string& data) const noexcept {
            unsigned long hash = 5381;
            
    	    for (char c : data) {
               hash = ((hash << 5) + hash) + c; // hash * 33 + c
            }
            
            return hash;
        }
};

template<>
class Hashable<double> {
    public:
        unsigned long operator()(const double& dat) const noexcept {
            unsigned long intgpart = floor(dat);
            unsigned long fracpart = pow(2, 24) * (dat - intgpart);
            return (intgpart * fracpart);
        }
};

//**************** HASHTABLE *********************

template <typename Data>
HashTable<Data>::HashTable(const HashTable &right) {
    tableSize = right.tableSize;
    size = right.size;
    a = right.a;
    b = right.b;
}

template <typename Data>
HashTable<Data>::HashTable(HashTable &&right) noexcept{
    std::swap(tableSize, right.tableSize);
    std::swap(size, right.size);
    std::swap(a, right.a);
    std::swap(b, right.b);
}

template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable &right) {
    tableSize = right.tableSize;
    size = right.size;
    a = right.a;
    b = right.b;
    return *this;
}

template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable &&right) noexcept {
    std::swap(tableSize, right.tableSize);
    std::swap(size, right.size);
    std::swap(a, right.a);
    std::swap(b, right.b);
    return *this;
}

/* ************************************************************************** */

}
