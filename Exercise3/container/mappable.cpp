
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun fun){
    PreOrderMap(fun);
}

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun fun){
    PostOrderMap(fun);
}

template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFun fun){
    InOrderMap(fun);
}

template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFun fun){
    BreadthMap(fun);
}

/* ************************************************************************** */

}
