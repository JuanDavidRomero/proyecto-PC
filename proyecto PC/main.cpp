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
    char* nombre;
    char fila;
    char columna;
    char* formula;
    float valorNumerico;
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

    for(int i = 0; i < f; i++)
    {
        *(cel+i)= new sCelda[c];
    }

    for(int i = 0; i < f; i++){

        for(int j = 0; j < c; j++){
            (*(*(cel+i)+j)).columna = j;
            (*(*(cel+i)+j)).fila = i;
            (*(*(cel+i)+j)).formula = new char[30];
            cout<<"dijite el valor de la casilla "<< i <<"/"<< j<<endl;
            if(i==0&&j==0)
                cin.ignore(1);
            cin.getline((*(*(cel+i)+j)).valor,30,'\n');

            int c = j+1;
            char * nom = new char[4];

            char p = '0';
            char s = '0';
            char t = '0';

            int a = 0;
            int b = 0;


            a = (c-1)/26;
            b = (c-1)%26;
            t = b + 65;
            c = a;

            a = (c-1)/26;
            b = (c-1)%26;
            s = b + 65;
            c = a;

            a = (c-1)/26;
            b = (c-1)%26;
            p = b + 65;
            c = a;

            if(p<65)
                p = ' ';
            if(s<65)
                s = ' ';
            if(t<65)
                t = ' ';

            *(nom+0) = p;
            *(nom+1) = s;
            *(nom+2) = t;
            *(nom+3) = '\0';
            cout<<nom<<'\n';

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
    char *nombre = new char[40];
    string nombres;
    cout<<"dijite el nombre del archivo que va a guardar"<<endl;
    cin.getline(nombre, 40, '\n');
    strcat(nombre,".txt");

    nombres.assign(nombre,strlen(nombre));
    cout<<nombres<<endl;
    arHoja.open(nombres.c_str(), ios::out);
    for(int i = 0; i < hoja->filasH; i++){
        for(int j = 0; j < hoja->columnasH; j++){
            arHoja<<"|"<<'\t'<<(*(*(hoja->celdas+i)+j)).valor<<'\t'<<"|";
        }
        arHoja<<'\n';
    }
    arHoja.close();
}

void imprimirHoja(sHoja* hoja)
{
    cout<<"su hoja de calculo es la siguiente"<<endl;
    int cols = hoja->columnasH;
    int filas = hoja->filasH;

     for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout<<"|"<<'\t'<<(*(*(hoja->celdas+i)+j)).valor<<'\t'<<"|";
        }
        cout<<'\n';
    }

    guardarAr(hoja);
}



void generarR(){
    ifstream entrada;
    char *nombre = new char[40];
    string nombres;
    cout<<"por favor indique el nombre del archivo al que desea generar reporte"<<endl;
    cin.ignore(1);
    cin.getline(nombre, 40, '\n');
    strcat(nombre,".txt");
    nombres.assign(nombre,strlen(nombre));
    entrada.open(nombres.c_str(), ios::in);
    if(entrada.fail())
        cout<<"el archivo no se pudo abrir o no existe"<<endl;
    else{
        cout<<"si entro"<<endl;
    }
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
