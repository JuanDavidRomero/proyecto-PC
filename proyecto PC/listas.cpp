//
//  listas.cpp
//  proyecto PC
//
//  Created by David Romero on 4/05/20.
//  Copyright © 2020 Arct. All rights reserved.
//

#include "listas.hpp"

template<typename T>
void insertList(Nodo<T> *&list, T dato){
    Nodo<T> *Nnode = new Nodo<T>;
    Nnode->dato = dato;

    Nodo<T> *aux1 = list;
    Nodo<T> *aux2;
    Nnode->sig = aux1;

    while((aux1!= NULL)){
        aux2 = aux1;
        aux1 = aux1->sig;
    }
    if(list == NULL)
        list = Nnode;
    else
        aux2->sig = Nnode;
    Nnode->sig = aux1;
}
