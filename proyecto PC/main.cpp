//
//  main.cpp
//  proyecto PC
//
//  Created by David Romero on 23/04/20.
//  Copyright © 2020 Arct. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "listas.cpp"

using namespace std;


struct datosHoja{
    int filasH;
    int columnasH;
    int nHoja;
    
};

struct celdas{
    char fila;
    char columna;
    char *valor;
};

void addHoja(datosHoja anadir){
    cout<<"cuantas filas tendra su hoja de calculo"<<endl;
    cin >> anadir.filasH;
    cout<<"cuantas columnas tendra su hoja de calculo"<<endl;
    cin >> anadir.columnasH;
}

void generarR(){}

void reclamarR(){}

int main() {
    datosHoja anadir;
    celdas infoC;
    anadir.nHoja = 0;
    char opcion;
    bool fin= true;
    while(fin == true){
        cout<<"SUPER CALCULOS S.A."<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"A = ingresar nueva hoja de calculo"<<endl;
        cout<<"B = generar reporte"<<endl;
        cout<<"C = reclamar reporte"<<endl;
        cout<<"E = salir"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<endl;
        cout<<"seleccione"<<endl;
        cin >>opcion;
        switch (opcion){
            case 'A':
            case 'a':
                anadir.nHoja++;
                addHoja(anadir);
                break;
            case 'B':
            case 'b':
                generarR();
                break;
            case 'C':
            case 'c':
                reclamarR();
                break;
            case 'E':
            case 'e':
                fin = false;
                break;
            default:
                break;
        }
    }
}
