
namespace lasd {

/* ************************************************************************** */

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const{
    Traverse(
        [fun, &acc](const Data& dat){
            acc = fun(dat, acc);
        }
    );

    return acc;
}

template <typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& data) const noexcept{
    bool exists = false;
    Traverse(
        [data, &exists](const Data & dat){
            exists |= (dat == data);
        }
    );
    return exists;
}

//********************PRE ORDER *************************

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PreOrderTraverse(
        [fun, &acc](const Data& dat){
            acc = fun(dat, acc);
        }
    );

    return acc;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const{
    PreOrderTraverse(fun);
}

//********************POST ORDER *************************

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PostOrderTraverse(
        [fun, &acc](const Data& dat){
            acc = fun(dat, acc);
        }
    );

    return acc;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const{
    PostOrderTraverse(fun);
}

//********************IN ORDER *************************

template <typename Data>
template <typename Accumulator>
Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    InOrderTraverse(
        [fun, &acc](const Data& dat){
            acc = fun(dat, acc);
        }
    );

    return acc;
}

template <typename Data>
inline void InOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const{
    InOrderTraverse(fun);
}

//********************BREADTH ORDER *************************

template <typename Data>
template <typename Accumulator>
Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    BreadthTraverse(
        [fun, &acc](const Data& dat){
            acc = fun(dat, acc);
        }
    );

    return acc;
}

template <typename Data>
inline void BreadthTraversableContainer<Data>::Traverse(TraverseFun fun) const{
    BreadthTraverse(fun);
}

/* ************************************************************************** */

}
