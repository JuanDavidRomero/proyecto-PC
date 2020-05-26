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
#include <stack>
#include "listas.cpp"

using namespace std;


struct sCelda{
    char* nombre;
    char fila;
    char columna;
    char* formula;
    float valorNumerico;
    bool calculado;
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
            (*(*(cel+i)+j)).calculado = false;
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
                arHoja<<(*(*(currentNode->dato.celdas+i)+j)).formula ;
                arHoja<<" ";
            }
            arHoja<<'\n';
        }
        currentNode = currentNode->sig;
    }
    arHoja.close();
}

void guardarArCalculado(Nodo<sHoja> *libro){
    sHoja call;
    Nodo<sHoja> *currentNode = libro;
    ofstream arHoja;
    char *nombre = new char[40];
    string nombres;
    cout<<"Digite el nombre del archivo que va a guardar"<<endl;
    cin.ignore(1);
    cin.getline(nombre, 40, '\n');
    strcat(nombre,"Calculado.txt");

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


    while(currentNode != NULL){

        for(int i = 0; i < currentNode->dato.filasH; i++){
            for(int j = 0; j < currentNode->dato.columnasH; j++){
                arHoja<<(*(*(currentNode->dato.celdas+i)+j)).valorNumerico ;
                arHoja<<" ";
            }
            arHoja<<'\n';
        }
        currentNode = currentNode->sig;
    }
    arHoja.close();
}

void imprimirHoja(sHoja &hoja)
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

void imprimirHojaValores(sHoja &hoja)
{
    cout<<"su hoja de calculo es la siguiente"<<endl;
    int cols = hoja.columnasH;
    int filas = hoja.filasH;

     for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if((*(*(hoja.celdas+i)+j)).valorNumerico != NULL)
            {
                cout<<"|"<<'\t'<<(*(*(hoja.celdas+i)+j)).valorNumerico<<'\t'<<"|";
            }
            else
            {
                cout<<"|"<<'\t'<<"NULL"<<'\t'<<"|";
            }
        }
        cout<<'\n';
    }
}


void leerLibroDeArchivo(Nodo<sHoja>* &libros, int &numHojas)
{
    char* nombre = new char[60];
    cout<<"Introduzca el nombre del archivo que desea leer (con .txt)"<<'\n';
    cin.ignore(1);
    cin.getline(nombre, 60, '\n');

    ifstream entrada;
    entrada.open(nombre, ios::in);

    char * linea= new char[100];
    char * pch;

    entrada.getline(linea,100,'\n');

    numHojas = atoi(linea);
    sHoja auxHoja;

    for(int i = 0; i < numHojas; i++)
    {
        auxHoja.idHoja = i;
        entrada.getline(linea,100,'\n');
        pch = strtok(linea, " ");
        auxHoja.columnasH = atoi(pch);
        pch = strtok(NULL, " ");
        auxHoja.filasH = atoi(pch);

        auxHoja.celdas = crearMatriz(auxHoja.filasH, auxHoja.columnasH);

        for(int y = 0; y < auxHoja.filasH; y++)
        {
            entrada.getline(linea,100,'\n');
            pch = strtok(linea, " ");
            for(int x = 0; x < auxHoja.columnasH; x++)
            {
                if(pch != NULL)
                {
                    strcpy((*(*(auxHoja.celdas +y)+x)).formula, pch);
                }
                pch = strtok(NULL, " ");
            }
        }
        insertList(libros, auxHoja);
    }
    cout<<'\n'<<"Hojas leidas del archivo: "<<'\n';
    Nodo<sHoja> *nodo = libros;
    while(nodo != NULL)
    {
        imprimirHoja(nodo->dato);
        nodo = nodo->sig;
    }

}


void generarR(Nodo<sHoja> *libro){
    string reclamar;


    if(libro == NULL)
        cout<<"No ha cargado ningun libro al sistema"<<endl;
    else{
        if(!(*(*((libro->dato).celdas))).calculado)
        {
            cout<<"No ha calculado el libro cargado al sistema."<<'\n';
        }
        else
        { //Ya sabemos que se pueden generar los reportes

            ifstream entrada;
            char *nombre = new char[40];
            string nombres;
            cout<<"Por favor indique el nombre del archivo que contiene los destinatarios de los reportes"<<endl;
            cin.ignore(1);
            cin.getline(nombre, 40, '\n');
            strcat(nombre,".txt");
            nombres.assign(nombre,strlen(nombre));
            entrada.open(nombres.c_str(), ios::in);
            char* linea = new char[100];
            entrada.getline(linea, 100, '\n');

            int numDes = atoi(linea);
            infoU usuario;

            for(int i = 0; i < numDes; i++)
            {
                usuario.nombres = new char[100];
                usuario.apellidos = new char[30];
                usuario.ciudad = new char[30];

                entrada.getline(linea, 100, '\n');
                strcpy(usuario.nombres, linea);

                entrada.getline(linea, 100, '\n');
                strcpy(usuario.apellidos, linea);

                entrada.getline(linea, 100, '\n');
                strcpy(usuario.ciudad, linea);

                Nodo<sHoja>* auxL = libro;
                int h = 0;

                string nombre;  //Se genera el nombre del archivo para el usuario
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
                        cout<<nombres<<endl;
                        nombre.assign(nombres,strlen(nombres));
                        cout<<nombre<<endl;
                        ofstream reporte(nombre.c_str(), ios::out);
                while(auxL != NULL)
                {
                    h++;
                    cout<<"Hoja numero: "<<h<<'\n';
                    cout<<endl;
                    cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                    cout<<"SUPER CALCULOS S.A."<<endl;
                    cout<<usuario.nombres<<" "<<usuario.apellidos<<endl;
                    cout<<usuario.ciudad<<endl;
                    cout<<"Después de un análisis detallado de cada movimiento de efectivo realizado en la semana "<< (*((auxL->dato).celdas + 0)+(auxL->dato).columnasH-1)->valorNumerico<<" se obtuvieron los siguientes datos: "<<endl;
                    cout<<'\t'<<"Unidades producidas "<< (*((auxL->dato).celdas + (auxL->dato).filasH-1)+(auxL->dato).columnasH-1)->valorNumerico<<endl;
                    cout<<'\t'<<"Unidades vendidas "<<(*((auxL->dato).celdas + 0)+0)->valorNumerico<<endl;
                    cout<<'\t'<<"Utilidad Operacional "<<(*((auxL->dato).celdas + (auxL->dato).filasH-1)+0)->valorNumerico<<endl;
                    cout<<'\t'<<"Utilidad Neta "<<((*((auxL->dato).celdas + ((auxL->dato).filasH-1)/2)+((auxL->dato).columnasH-1)/2))->valorNumerico<<endl;
                    cout<<"Cordial Saludo "<<endl;
                    cout<<endl;
                    cout<<"Departamento de Finanzas. "<<endl;
                    cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
                    cout<<endl;

                    cout<<"Desea guardar este reporte?"<<endl;
                    cin >>reclamar;
                    if(reclamar == "si"){

                        reporte<<"Reporte de hoja #"<<h<<endl;
                        reporte<<"------------------------------------------------------------------------------------------------------------"<<endl;
                        reporte<<"------------------------------------------------------------------------------------------------------------"<<endl;
                        reporte<<"SUPER CALCULOS S.A."<<endl;
                        reporte<<usuario.nombres<<" "<<usuario.apellidos<<endl;
                        reporte<<usuario.ciudad<<endl;
                        reporte<<"Después de un análisis detallado de cada movimiento de efectivo realizado en la semana "<< (*((auxL->dato).celdas + 0)+(auxL->dato).columnasH-1)->valorNumerico<<" se obtuvieron los siguientes datos: "<<endl;
                        reporte<<'\t'<<"Unidades producidas"<< (*((auxL->dato).celdas + (auxL->dato).filasH-1)+(auxL->dato).columnasH-1)->valorNumerico<<endl;
                        reporte<<'\t'<<"Unidades vendidas"<<(*((auxL->dato).celdas + 0)+0)->valorNumerico<<endl;
                        reporte<<'\t'<<"Utilidad Operacional"<<(*((auxL->dato).celdas + (auxL->dato).filasH-1)+0)->valorNumerico<<endl;
                        reporte<<'\t'<<"Utilidad Neta"<<((*((auxL->dato).celdas + ((auxL->dato).filasH-1)/2)+((auxL->dato).columnasH-1)/2))->valorNumerico<<endl;
                        reporte<<"Cordial Saludo"<<endl;
                        reporte<<endl;
                        reporte<<"Departamento de Finanzas."<<endl;
                        reporte<<"------------------------------------------------------------------------------------------------------------"<<endl;
                        reporte<<endl;
                        reporte<<endl;
                        //falta guardar(cout pero en txt)
                    }


                    auxL = auxL->sig;
                }
                reporte.close();
            }
            entrada.close();




        }



    }


}

void celdasStack(stack<sCelda*> s, sCelda** celdas) //Funcion recursiva
{
    stack<sCelda*> saux;
    while(!s.empty())
    {
        char* form = new char[30];
        strcpy(form, s.top()->formula);


        if(*form == '=')
        {
            form = form +1; // Omite el =
            char* tok;
            tok = strtok(form, "+");

            while(tok != NULL)
            {
                if(*tok >= 48 && *tok <= 57) //Es un valor numeico
                {
                    s.top()->valorNumerico += atoi(tok);
                }
                else if(*tok >= 65 && *tok <= 90)
                {
                    char* auxC = tok;
                    int pos = 0;
                    while(*auxC >= 65 && *auxC <= 90) // A3 + C3
                    {
                        pos++;
                        auxC = auxC+1;
                    }
                    int fila = atoi(auxC);
                    fila--;
                    *(tok + pos) = '\0';
                    int columna = calcularNumeroColumna(tok); //Aqui ya tenemos el numero de la columna y el numero de la fila

                    cout<<"Celda: "<<columna<<","<<fila<<"  "<<(*(*(celdas+fila)+columna)).calculado<<'\n';
                    if((*(*(celdas+fila)+columna)).calculado)
                    {
                        cout<<"Calculado: "<<s.top()->formula<<'\n';
                        s.top()->valorNumerico += (*(*(celdas+fila)+columna)).valorNumerico;
                        s.top()->calculado = true;
                    }
                    else
                    {
                        cout<<s.top()->formula<<'\n';
                        s.top()->valorNumerico= 0;
                        s.top()->calculado = false; //Asi sabemos que no se pudo resolver
                        saux.push(s.top());

                        break;
                    }
                }
                tok = strtok(NULL, "+");
            }

        }
        else if(*form == '-')
        {
            s.top()->valorNumerico = 0;
            s.top()->calculado = true;
        }
        else //Es un numero
        {
            s.top()->valorNumerico = atoi(form);
            s.top()->calculado = true;
        }

        s.pop();
    }

    if(!saux.empty())
    {
        celdasStack(saux, celdas);
    }
}

void calcularLibro(Nodo<sHoja>*libro, int numHojas)
{
    cout<<"Entro a calcular"<<'\n';
    Nodo<sHoja>*auxL = libro;
    for(int h = 0; h < numHojas; h++)
    {
        stack<sCelda*> celdasNR;
        sCelda** celdas = (auxL->dato).celdas;
        for(int i = 0; i < ((auxL->dato)).columnasH; i++)
        {
            for(int j = 0; j < ((auxL->dato)).filasH; j++)
            {
                //Accedimos a una celda especifica}
                char* form = new char[30];
                strcpy(form, (*(*(celdas+i)+j)).formula);


                if(*form == '=')
                {
                    form = form +1; // Omite el =
                    char* tok;
                    tok = strtok(form, "+");

                    while(tok != NULL)
                    {
                        if(*tok >= 48 && *tok <= 57) //Es un valor numeico
                        {
                            (*(*(celdas+i)+j)).valorNumerico += atoi(tok);
                        }
                        else if(*tok >= 65 && *tok <= 90)
                        {
                            char* auxC = tok;
                            int pos = 0;
                            while(*auxC >= 65 && *auxC <= 90) // A1
                            {
                                pos++;
                                auxC= auxC+1;
                            }
                            int fila = atoi(auxC);
                            fila--;
                            *(tok + pos) = '\0';
                            int columna = calcularNumeroColumna(tok); //Aqui ya tenemos el numero de la columna y el numero de la fila

                            if((*(*(celdas+fila)+columna)).calculado)
                            {
                                (*(*(celdas+i)+j)).valorNumerico += (*(*(celdas+fila)+columna)).valorNumerico;
                                (*(*(celdas+i)+j)).calculado = true;
                            }
                            else
                            {
                                (*(*(celdas+i)+j)).valorNumerico = 0;
                                (*(*(celdas+i)+j)).calculado = false;//Asi sabemos que no se pudo resolver
                                celdasNR.push((*(celdas+i)+j));

                                break;
                            }
                        }

                        tok = strtok(NULL, "+");

                    }

                }
                else if(*form == '-')
                {
                    (*(*(celdas+i)+j)).valorNumerico = 0;
                    (*(*(celdas+i)+j)).calculado = true;
                }
                else //Es un numero
                {
                    (*(*(celdas+i)+j)).valorNumerico = atoi(form);
                    (*(*(celdas+i)+j)).calculado = true;
                }

                cout<<(*(*(celdas+i)+j)).valorNumerico<<" ";
            }
            cout<<'\n';
        }

        celdasStack(celdasNR, celdas);

        imprimirHojaValores((auxL->dato));

        cout<<'\n'<<'\n';
        auxL = auxL->sig;
    }
}

int main() {
    string nueva = "si";
    infoU usuario;
    Nodo<sHoja> *libro = NULL;
    sHoja hoja1 ;
    sHoja* aux = NULL;
    Nodo<sHoja>* auxL = NULL;
    int numHoj = 0;
    int id = 0, numHojas = 0;
    char opcion;
    bool fin= true;
    while(fin == true){
        cout<<"SUPER CALCULOS S.A."<<endl;
        cout<<"------------------------------"<<endl;
        cout<<"1. Ingresar nuevo libro de calculo"<<endl;
        cout<<"2. Leer libro de archivo de texto"<<endl;
        cout<<"3. Editar hoja de calculo"<<endl;
        cout<<"4. Calcular libro"<<endl;
        cout<<"5. Generar Reportes"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<"------------------------------"<<endl;
        cout<<endl;
        cout<<"Seleccione el numero de la opcion que desea: ";
        cin >>opcion;
        switch (opcion){
            case '1':
                libro = NULL;
                while(nueva == "si"){
                    hoja1.idHoja= numHojas+1;
                    addHoja(hoja1, numHojas);
                    imprimirHoja(hoja1);
                    insertList(libro, hoja1);
                    cout<<"¿quiere agregar una nueva hoja de calculo?"<<endl;
                    cin>>nueva;
                    numHojas++;
                    aux=NULL;
                }
                guardarAr(libro);
                nueva = "si";
                break;
            case '2':
                libro = NULL;
                leerLibroDeArchivo(libro, numHojas);
                break;
            case '3':
                cout<<"Su libro tiene "<<numHojas<< " hojas. Que hoja desea editar?"<<'\n';

                cin>>numHoj;
                auxL = libro;
                for(int i = 0; i < numHoj-1; i++)
                {
                    auxL = auxL->sig;
                }
                editarHoja(auxL->dato, numHojas);
                guardarAr(libro);
                break;
            case '4':
                calcularLibro(libro, numHojas);
                guardarArCalculado(libro);
                break;
            case '5':
                generarR(libro);
                break;
            case '6':
                fin = false;
                break;
            default:
                break;
        }
    }
}
