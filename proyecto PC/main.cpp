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

using namespace std;

void addHoja(){
    cout <<"hola waposssss santi es dios"<<endl;
}

void generarR(){}

void reclamarR(){}

int main() {
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
                addHoja();
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
