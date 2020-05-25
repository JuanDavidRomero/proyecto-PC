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
#include <unistd.h>
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

struct infoU{
    char * nombres;
    char * apellidos;
    char * ciudad;
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

void editarHoja(sHoja &hoja, int count)
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
            *(colChars + strlen(resp) - strlen(resp+i)) = '\0';


            col = calcularNumeroColumna(colChars);
            cout<<"Escogio la columna: "<<col<< " de lo que se leyo: "<< colChars<<'\n';

            cout<<"Celda: "<<calcularNombreColumna(col)<<fil+1<<  "   real:  "<<(*(*(hoja.celdas+fil)+col)).nombre<<'\n';

            int val =0;
            while(val==0){
                cout<<"Digite el valor que quiere ingresar"<<'\n';
                cin.getline((*(*(hoja.celdas+fil)+col)).formula,30,'\n');

                for(int i =0;i<strlen((*(*(hoja.celdas+fil)+col)).formula);i++){
                    if(i == strlen((*(*(hoja.celdas+fil)+col)).formula)-1 )
                        val++;

                    if(  *((*(*((hoja.celdas)+fil)+col)).formula) != '=' &&  *((*(*((hoja.celdas)+fil)+col)).formula + i) == '+' ){
                        cout<<"el valor dijitado es incorrecto"<<endl;
                        cout<<"recuerde colocar el '=' antes de colocar una formula"<<endl;
                        i = strlen((*(*(hoja.celdas+fil)+col)).formula)-1;
                    }
                }
            }
            cout<<"Valor guardado: "<<(*(*(hoja.celdas+fil)+col)).formula<<'\n';


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
            strcpy((*(*(cel+i)+j)).formula, "-");
            (*(*(cel+i)+j)).valorNumerico = 0;
        }
        cout<<endl;
    }

    return cel;
}



void addHoja(sHoja &hoja, int count){
    cout<<"Cuantas columnas tendra su hoja de calculo?"<<endl;
    cin >> hoja.columnasH;
    cout<<"Cuantas filas tendra su hoja de calculo?"<<endl;
    cin >> hoja.filasH;
    sCelda** cels = crearMatriz(hoja.filasH, hoja.columnasH);
    hoja.celdas = cels;

    cout<<"Desea entrar en el modo de edicion de su hoja? (s/n)"<<'\n';
    char r = 'n';
    cin>>r;

    if(r == 's')
    {
        editarHoja(hoja, count);
    }
}

void guardarAr(Nodo<sHoja> *libro){
    sHoja call;
    Nodo<sHoja> *currentNode = libro;
    ofstream arHoja;
    char *nombre = new char[40];
    string nombres;
    cout<<"Digite el nombre del archivo que va a guardar"<<endl;
    cin.ignore(1);
    cin.getline(nombre, 40, '\n');
    strcat(nombre,".txt");

    nombres.assign(nombre,strlen(nombre));
    cout<<nombres<< " guardado"<<endl;
    arHoja.open(nombres.c_str(), ios::out);
    int numHojas = 0;
    while(currentNode != NULL)
    {
        numHojas++;
        currentNode = currentNode->sig;
    }
    currentNode = libro;

    arHoja<<numHojas<<'\n';

    while(currentNode != NULL){
        arHoja<<currentNode->dato.columnasH<<" "<<currentNode->dato.filasH<<endl;

        for(int i = 0; i < currentNode->dato.filasH; i++){

            for(int j = 0; j < currentNode->dato.columnasH; j++){
                    if((*(*(currentNode->dato.celdas+i)+j)).valorNumerico == 0)
                    {
                        arHoja<<(*(*(currentNode->dato.celdas+i)+j)).formula ;
                    }
                    else{
                        arHoja<<(*(*(currentNode->dato.celdas+i)+j)).valorNumerico;
                    }
                arHoja<<" ";
            }
            arHoja<<'\n';
        }
        currentNode = currentNode->sig;
    }
    arHoja.close();
}

void leerLibroDeArchivo()
{
    char* nombre = new char[60];
    cout<<"Introduzca el nombre del archivo que desea leer (con .txt)"<<'\n';
    cin.getline(nombre, 60, '\n');

    ifstream entrada;
    entrada.open(nombre, ios::in);

    while(!entrada.eof())
    {
        char* linea = new char[100];

    }

}

void imprimirHoja(sHoja &hoja, int count)
{
    cout<<"su hoja de calculo es la siguiente"<<endl;
    int cols = hoja.columnasH;
    int filas = hoja.filasH;

     for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout<<"|"<<'\t'<<(*(*(hoja.celdas+i)+j)).formula<<'\t'<<"|";
        }
        cout<<'\n';
    }
}



void generarR(Nodo<sHoja> *hoja, infoU usuario){
    string reclamar;
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
        usuario.nombres = new char[100];
        usuario.apellidos = new char[30];
        usuario.ciudad = new char[30];
        cout<<"dijite el nombre del titular"<<endl;
        cin.getline(usuario.nombres, 30,'\n');
        cout<<"dijite los apellidos del titular"<<endl;
        cin.getline(usuario.apellidos, 30,'\n');
        cout<<"dijite ciudad"<<endl;
        cin.getline(usuario.ciudad,30,'\n');


        cout<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"SUPER CALCULOS S.A."<<endl;
        cout<<usuario.nombres<<" "<<usuario.apellidos<<endl;
        cout<<usuario.ciudad<<endl;
        cout<<"Después de un análisis detallado de cada movimiento de efectivo realizado en la semana <Súperior derecha> se obtuvieron los siguientes datos: "<<endl;
        cout<<'\t'<<"Unidades producidas <inferior derecha>"<<endl;
        cout<<'\t'<<"Unidades vendidas <Súper ior izquierda>"<<endl;
        cout<<'\t'<<"Utilidad Operacional <inferior izquierda>"<<endl;
        cout<<'\t'<<"Utilidad Neta <(filas/2, columnas/2)>"<<endl;
        cout<<"Cordial Saludo"<<endl;
        cout<<endl;
        cout<<"Departamento de Finanzas."<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<endl;


    }
    entrada.close();
    cout<<"desea guardar su reporte?"<<endl;
    cin >>reclamar;
    if(reclamar == "si"){
        string nombre;
        int nn=0;
        char *primero, *segundo, *token, *nombres, *apellidos;
        primero = new char[30];
        nombres = new char[30];
        segundo = new char[30];
        apellidos = new char[30];

        strcpy(nombres, usuario.nombres);
        strcpy(apellidos, usuario.apellidos);
        for(int i = 0; i<2; i++){
            if(i==0){
                for(int y = 0; y<strlen(usuario.nombres);y++){
                    if(*(usuario.nombres +y) == ' '){
                        cout<<"entra nombre"<<endl;
                        token = strtok(nombres, " ");
                        nn++;
                    }
                    if((y ==strlen(usuario.nombres)-1)&&(nn<1)){
                        i++;
                    }
                }
            }
            if(i==1){
                for(int y = 0; y<strlen(usuario.apellidos);y++){
                    if(*(usuario.apellidos+y) == ' '){
                        token = strtok(apellidos, " ");
                        nn++;
                    }
                    if((y ==strlen(usuario.apellidos)-1)&&(nn<1)){
                        i++;
                    }
                }
            }
            cout<<usuario.nombres<<" "<<usuario.apellidos<<endl;

            int j = 0;
            if(nn < 1){
                j=2;
            }
            for(; j<2 ; j++){
                if(j == 0)
                    strcpy(primero, token);
                if(j==1)
                    strcpy(segundo, token);
                token = strtok(NULL, " ");
            }
            if(i==0){
                strcat(primero,segundo);
                strcpy(nombres, primero);
            }
            if(i==1){
                strcat(primero,segundo);
                strcpy(apellidos, primero);
            }
        }
        strcat(nombres, apellidos);
        strcat(nombres, ".txt");
        strcpy(primero, nombres);
        cout<<nombres<<endl;
        nombre.assign(nombres,strlen(nombres));
        cout<<nombre<<endl;
        ofstream reporte(nombre.c_str(), ios::out);
        reporte<<"reporte generado"<<endl;
        reporte<<"------------------------------------------------------------------------------------------------------------"<<endl;
        reporte<<"SUPER CALCULOS S.A."<<endl;
        reporte<<usuario.nombres<<" "<<usuario.apellidos<<endl;
        reporte<<usuario.ciudad<<endl;
        reporte<<"Después de un análisis detallado de cada movimiento de efectivo realizado en la semana <Súperior derecha> se obtuvieron los siguientes datos: "<<endl;
        reporte<<'\t'<<"Unidades producidas <inferior derecha>"<<endl;
        reporte<<'\t'<<"Unidades vendidas <Súper ior izquierda>"<<endl;
        reporte<<'\t'<<"Utilidad Operacional <inferior izquierda>"<<endl;
        reporte<<'\t'<<"Utilidad Neta <(filas/2, columnas/2)>"<<endl;
        reporte<<"Cordial Saludo"<<endl;
        reporte<<endl;
        reporte<<"Departamento de Finanzas."<<endl;
        reporte<<"------------------------------------------------------------------------------------------------------------"<<endl;
        reporte<<endl;
        //falta guardar(cout pero en txt)
    }
}

void reclamarR(){}

int main() {
    string nueva = "si";
    infoU usuario;
    Nodo<sHoja> *libros = NULL;
    sHoja hoja1 ;
    sHoja* aux = NULL;
    int id = 0, numHojas = 0, numLibros = 0;
    char opcion;
    bool fin= true;
    while(fin == true){
        cout<<"SUPER CALCULOS S.A."<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"1. Ingresar nueva hoja de calculo"<<endl;
        cout<<"2. Editar hoja de calculo"<<endl;
        cout<<"3. reportes"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<endl;
        cout<<"Seleccione el numero de la opcion que desea: ";
        cin >>opcion;
        switch (opcion){
            case '1':
                while(nueva == "si"){
                    hoja1.idHoja= numHojas+1;
                    addHoja(hoja1, numHojas);
                    imprimirHoja(hoja1, numHojas);
                    insertList(libros, hoja1);
                    cout<<"¿quiere agregar una nueva hoja de calculo?"<<endl;
                    cin>>nueva;
                    numHojas++;
                    aux=NULL;
                }
                guardarAr(libros+numLibros);
                numLibros++;
                break;
            case '2':
                editarHoja(hoja1, numHojas);
            case '3':
                generarR(libros, usuario);
                break;
            case '4':
                fin = false;
                break;
            default:
                break;
        }
    }
}
