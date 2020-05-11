//
//  listas.cpp
//  proyecto PC
//
//  Created by David Romero on 4/05/20.
//  Copyright © 2020 Arct. All rights reserved.
//

#include "listas.hpp"

template<typename T>
void insertList(Nodo<T> *&list, T *dato){
    Nodo<T> *Nnode = new Nodo<T>;
    Nnode->dato = dato;
    
    Nodo<T> *aux = list;
    while(aux->sig != NULL && list != NULL){
        aux = aux->sig;
    }
    if(list == NULL)
        list = Nnode;
    else
        aux->sig = Nnode;

    Nnode->sig = NULL;
}
