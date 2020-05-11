//
//  listas.hpp
//  proyecto PC
//
//  Created by David Romero on 4/05/20.
//  Copyright © 2020 Arct. All rights reserved.
//

#ifndef listas_hpp
#define listas_hpp

#include <stdio.h>

template<typename T>
struct Nodo{
    T *dato;
    Nodo *sig;
};

template<typename T>
void crearlista(Nodo<T> *&list, T *dato);

#endif
