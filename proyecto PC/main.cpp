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
#include <fstream>
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

    for(int i = 0; i < c; i++){
        
        for(int j = 0; j < f; j++){
            (*(*(cel+i)+j)).columna = i;
            (*(*(cel+i)+j)).fila = j;
            (*(*(cel+i)+j)).valor = new char[30];
            cout<<"dijite el valor de la casilla "<< (*(*(cel+i)+j)).fila <<"/"<< (*(*(cel+i)+j)).columna<<endl;
            if(i==0&&j==0)
                cin.ignore(1);
            cin.getline((*(*(cel+i)+j)).valor,30,'\n');

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

void guardarAr(sHoja* hoja){
    ofstream arHoja;
    string nombre;
    cout<<"dijite el nombre del archivo que va a guardar"<<endl;
    getline(cin,nombre);
    arHoja.open(nombre.c_str(), ios::out);
    for(int i = 0; i < hoja->columnasH; i++){
        for(int j = 0; j < hoja->filasH; j++){
            arHoja<<"|"<<'\t'<<(*(*(hoja->celdas+i)+j)).valor<<'\t'<<"|";
        }
        arHoja<<'\n';
    }
}

void imprimirHoja(sHoja* hoja)
{
    cout<<"su hoja de calculo es la siguiente"<<endl;
    int cols = hoja->columnasH;
    int filas = hoja->filasH;

     for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < filas; j++)
        {
            cout<<"|"<<'\t'<<(*(*(hoja->celdas+i)+j)).valor<<'\t'<<"|";
        }
        cout<<'\n';
    }
    
    guardarAr(hoja);
}



void generarR(){
    cout<<"por favor indique el nombre del archivo al que desea generar reporte"<<endl;
    
}

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
                imprimirHoja(hoja1);
                break;
            case '2':
                generarR();
                break;
            case '3':
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
