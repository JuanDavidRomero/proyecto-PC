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


struct sCelda{
    char fila;
    char columna;
    char* valor;
};

struct sHoja{
    int filasH;
    int columnasH;
    int idHoja;
    sCelda** celdas;

};


sCelda** crearMatriz(int f, int c)
{

    sCelda** cel = new sCelda*[c];

    for(int i = 0; i < c; i++)
    {
        *(cel+i)= new sCelda[f];
    }

    for(int i = 0; i < c; i++)
    {
        for(int j = 0; j < f; j++)
        {
            (*(*(cel+i)+j)).columna = i;
            (*(*(cel+i)+j)).fila = j;
            (*(*(cel+i)+j)).valor = new char[30];
            *((*(*(cel+i)+j)).valor) = 'h';

        }
    }

    return cel;

}


void addHoja(sHoja* hoja){
    cout<<"cuantas columnas tendra su hoja de calculo?"<<endl;
    cin >> hoja->columnasH;
    cout<<"cuantas filas tendra su hoja de calculo?"<<endl;
    cin >> hoja->filasH;
    sCelda** cels = crearMatriz(hoja->filasH, hoja->columnasH);
    hoja->celdas = cels;
}

void imprimirHoja(sHoja* hoja)
{
    int cols = hoja->columnasH;
    int filas = hoja->filasH;

     for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < filas; j++)
        {
            cout<<(*(*(hoja->celdas+i)+j)).valor<<'\t';
        }
        cout<<'\n';
    }
}

void generarR(){}

void reclamarR(){}

int main() {
    sHoja* hoja1;
    sCelda infoC;
    hoja1->idHoja = 0;
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
                hoja1->idHoja++;
                addHoja(hoja1);
                break;
            case '2':
                generarR();
                break;
            case '3':
                imprimirHoja(hoja1);
                reclamarR();
                break;
            case '4':
                fin = false;
                break;
            default:
                break;
        }
    }
}
