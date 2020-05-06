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


struct celda{
    char fila;
    char columna;
    char *valor;
};

struct hoja{
    int filasH;
    int columnasH;
    int idHoja;
    celda** celdas;

};

void addHoja(hoja anadir){
    cout<<"cuantas filas tendra su hoja de calculo?"<<endl;
    cin >> anadir.filasH;
    cout<<"cuantas columnas tendra su hoja de calculo?"<<endl;
    cin >> anadir.columnasH;
}

void generarR(){}

void reclamarR(){}

int main() {
    hoja anadir;
    celda infoC;
    anadir.idHoja = 0;
    char opcion;
    bool fin= true;
    while(fin == true){
        cout<<"SUPER CALCULOS S.A."<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"1. Ingresar nueva hoja de calculo"<<endl;
        cout<<"2. Generar reporte"<<endl;
        cout<<"3. Reclamar reporte"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<endl;
        cout<<"Seleccione el número de la opción que desea: ";
        cin >>opcion;
        switch (opcion){
            case '1':
                anadir.idHoja++;
                addHoja(anadir);
                break;
            case '2':
                generarR();
                break;
            case 'C':
            case 'c':
                reclamarR();
                break;
            case '3':
                fin = false;
                break;
            default:
                break;
        }
    }
}
