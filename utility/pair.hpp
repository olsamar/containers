#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft{
    template <class T1, class T2> 
    struct pair {

    public:
        typedef T1 first_type;
        typedef T2 second_type;
    
        T1 first;
        T2 second;

        // CONSTRUCTORS:
        // default (1)	
        pair() : first(), second() {}
        // copy (2)	
        template<class U, class V> 
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
        // initialization (3)	
        pair (const first_type& a, const second_type& b) : first(a), second(b) {}
    };

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y){
        return pair<T1,T2>(x,y);
    }
};

#endif