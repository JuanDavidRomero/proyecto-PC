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
    if(list != NULL){
        while(aux->sig != NULL){
            aux = aux->sig;
        }
    }
    if(list == NULL){
        list = Nnode;
        aux = list;
    }
    else
        aux->sig = Nnode;

    Nnode->sig = NULL;
}
