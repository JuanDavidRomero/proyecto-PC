//
//  main.cpp
//  proyecto PC
//
//  Created by David Romero on 23/04/20.
//  Copyright � 2020 Arct. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cmath>
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

struct sLibro{
    Nodo<sHoja> lista;
    char* nombreLibro;
    int cantHojas;
};

char* calcularNombreColumna(int col) //Col va de 0 a 18277
{
    int c = col+1;
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

    for(int i = 0; i < strlen(nom); i++)
    {
        if(*(nom+i) != ' ')
        {
            nom = nom+i;
            break;
        }
    }
    return nom;
}

int calcularNumeroColumna(char* col) //La respuesta ira de 0 a 18277
{
    int resp = 0;
    int length = strlen(col);
    if(length < 2)
    {
        resp = -1;
    }

    for(int i = length-1; i >= 0; i--)
    {
        resp += (col[ length - i - 1] - 64) *  pow(26, i);
    }

    return resp;
}

void editarHoja(sHoja* hoja)
{
    char s = 's';
    while(s == 's' )
    {
        cout<< "Digite el nombre de la celda (ej: ABC321) que quiere modificar"<<'\n';
        char* resp = new char[10];
        cin.ignore(1);
        cin.getline(resp, 10, '\n');

        cout<<"Se leyo: "<<resp<<'\n';

        int col = 0;
        int fil = 0;

        if(resp[0] >= 65 && resp[0] <= 90)//El usuario escogio buscar por el nombre de la celda
        {
            int i = 0;
            for(i = 0; i < strlen(resp); i++)
            {
                if(!(resp[i] >= 65 && resp[i] <= 90))
                {
                    break; //Encontro la posici�n del primer caracter que no es una letra
                }
            }

            char* filChar = (resp+i);
            fil = atoi(filChar);
            cout<<"Escogio la fila: "<<fil<<'\n';
            fil--;


            char* colChars = new char[strlen(resp) - strlen(resp+i)];
            for(int j = 0; j<i; j++)
            {
                colChars[j] = resp[j];
            }


            col = calcularNumeroColumna(colChars);
            cout<<"Escogio la columna: "<<col<< " de lo que se leyo: "<< colChars<<'\n';

            cout<<"Celda: "<<calcularNombreColumna(col)<<fil+1<<  "   real:  "<<(*(*(hoja->celdas+fil)+col)).nombre<<'\n';

            int val =0;
            while(val==0){
                cout<<"Digite el valor que quiere ingresar"<<'\n';
                cin.getline((*(*(hoja->celdas+fil)+col)).formula,30,'\n');

                for(int i =0;i<strlen((*(*(hoja->celdas+fil)+col)).formula);i++){
                    if(i == strlen((*(*(hoja->celdas+fil)+col)).formula)-1 )
                        val++;

                    if(  *((*(*((hoja->celdas)+fil)+col)).formula) != '=' &&  *((*(*((hoja->celdas)+fil)+col)).formula + i) == '+' ){
                        cout<<"el valor dijitado es incorrecto"<<endl;
                        cout<<"recuerde colocar el '=' antes de colocar una formula"<<endl;
                        i = strlen((*(*(hoja->celdas+fil)+col)).formula)-1;
                    }
                }
            }
            cout<<"Valor guardado: "<<(*(*(hoja->celdas+fil)+col)).formula<<'\n';


        }
        else
        {
            cout<<"Formato invalido. Vuelva a intentar"<<'\n';
            s = 'r';
        }

        if(s == 'r')
        {
            s = 's';
        }
        else{
            cout<<"Desea editar otra celda? (s/n)"<<'\n';
            cin>>s;
        }
    }
}

sCelda** crearMatriz(int f, int c)
{
    sCelda** cel = new sCelda*[c];

    for(int i = 0; i < f; i++)
    {
        *(cel+i)= new sCelda[c];
    }

    for(int i = 0; i < f; i++){

        for(int j = 0; j < c; j++)
        {
            (*(*(cel+i)+j)).columna = j;
            (*(*(cel+i)+j)).fila = i;

            (*(*(cel+i)+j)).nombre = calcularNombreColumna(j);
            char* nomFila = new char[3];
            sprintf(nomFila,"%d", i+1);
            //itoa(i+1, nomFila, 10);
            strcat((*(*(cel+i)+j)).nombre, nomFila);
            cout<<"|"<<(*(*(cel+i)+j)).nombre<<"|";

            (*(*(cel+i)+j)).formula = new char[30];
            strcpy((*(*(cel+i)+j)).formula, "  ");
        }
        cout<<endl;
    }

    return cel;
}



void addHoja(sHoja* hoja){
    cout<<"Cuantas columnas tendra su hoja de calculo?"<<endl;
    cin >> hoja->columnasH;
    cout<<"Cuantas filas tendra su hoja de calculo?"<<endl;
    cin >> hoja->filasH;
    sCelda** cels = crearMatriz(hoja->filasH, hoja->columnasH);
    hoja->celdas = cels;

    cout<<"Desea entrar en el modo de edici�n de su hoja? (s/n)"<<'\n';
    char r = 'n';
    cin>>r;

    if(r == 's')
    {
        editarHoja(hoja);
    }
}

void guardarAr(sHoja* hoja){
    ofstream arHoja;
    char *nombre = new char[40];
    string nombres;
    cout<<"Digite el nombre del archivo que va a guardar"<<endl;
    cin.ignore(1);
    cin.getline(nombre, 40, '\n');
    strcat(nombre,".txt");

    nombres.assign(nombre,strlen(nombre));
    cout<<nombres<<endl;
    arHoja.open(nombres.c_str(), ios::out);
    for(int i = 0; i < hoja->filasH; i++){
        for(int j = 0; j < hoja->columnasH; j++){
            arHoja<<"|"<<'\t'<<(*(*(hoja->celdas+i)+j)).formula<<'\t'<<"|";
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
            cout<<"|"<<'\t'<<(*(*(hoja->celdas+i)+j)).formula<<'\t'<<"|";
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
    sLibro* libro;
    sHoja* hoja1 = NULL;
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
        cout<<"Seleccione el n�mero de la opci�n que desea: ";
        cin >>opcion;
        switch (opcion){
            case '1':
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
