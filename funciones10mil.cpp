#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <cwchar>
using namespace std;

#include "funciones10mil.h"

void mostrarNombreCombinaciones(string *vecNombreCombinaciones){
    int i;
    for(i=0;i<10;i++){
        cout<<vecNombreCombinaciones[i]<<endl;
    }
}

void ingresarNombreCombinaciones(string *vecNombreCombinaciones){
    vecNombreCombinaciones[0]={"SOPA :("};
    vecNombreCombinaciones[1]={"JUEGO DE 1"};
    vecNombreCombinaciones[2]={"JUEGO DE 5"};
    vecNombreCombinaciones[3]={"TRÍO 1"};
    vecNombreCombinaciones[4]={"TRÍO "};
    vecNombreCombinaciones[5]={"TRÍO++ "};
    vecNombreCombinaciones[6]={"TRÍO 1 AMPLIADO"};
    vecNombreCombinaciones[7]={"TRES PARES"};
    vecNombreCombinaciones[8]={"ESCALERA LARGA"};
    vecNombreCombinaciones[9]={"SEXTETO :D"};
}

void ingresarNombre(char *jugador1,char *apellido1){
    cin.ignore();
    cout<<"     NOMBRE JUGADOR: ";
    cin.getline(jugador1,20);
    cout<<"     APELLIDO JUGADOR: ";
    cin.getline(apellido1,20);
    system("pause");
}

void ingresarNombres(char *jugador_1, char *apellido_1, char *jugador_2, char *apellido_2){
    cin.ignore();
    cout<<"     NOMBRE JUGADOR 1: ";
    cin.getline(jugador_1,20);
    cout<<"     APELLIDO JUGADOR 1: ";
    cin.getline(apellido_1,20);
    cout<<endl;
    cout<<"     NOMBRE JUGADOR 2: ";
    cin.getline(jugador_2,20);
    cout<<"     APELLIDO JUGADOR 2: ";
    cin.getline(apellido_2,20);
    system("pause");
}
//aca se modifican los dados para probar
void tirarDados(int *vecDados, int tam, bool AZAR){
    if(AZAR){
        int i;
        for(i=0;i<tam;i++){
            vecDados[i]=(rand()%6)+1;
        }
    }
    else{
        vecDados[0]=1;
        vecDados[1]=1;
        vecDados[2]=1;
        vecDados[3]=1;
        vecDados[4]=1;
        vecDados[5]=1;
    }
}

void mostrarDados(int *dados, int tam){
    int i;
    for(i=0;i<tam;i++){
    cout<<"     "<< dados[i]<<"\t";
    }
    cout<<endl;
}

void funcionTurno(char *jugador1, char *apellido1, bool AZAR, int *vecRepetidos, string *vecNombreCombinaciones, int *scoreJugador1){
    system("cls");
    int i,cantTurnos, puntosTotal=0, puntosRonda;
    int contadorTurno=0;
    cout<<endl;
    cout<<"     INGRESAR CANTIDAD DE TURNOS: ";
    cin>>cantTurnos;
    for(i=0;i<cantTurnos;i++){
        system("cls");
        contadorTurno++;
        cout<<endl;
        cout<<"     JUGADOR: "<<jugador1<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal<<endl;//falta puntaje
        cout<<"     ----------------------------------------------------------------"<<endl;
        puntosRonda=funcionTirada(jugador1, apellido1, contadorTurno, AZAR, puntosTotal, vecRepetidos, vecNombreCombinaciones, scoreJugador1);
        puntosTotal+=puntosRonda;
        //funcion10000(puntosTotal);
        if(puntosRonda==10000){ //si saca sexteto
            scoreJugador1[0]=puntosRonda;
            scoreJugador1[1]=contadorTurno;
            return;
        }
        if(puntosTotal==10000){//gana el juego
            scoreJugador1[0]=puntosTotal;
            scoreJugador1[1]=contadorTurno;
            return;
        }
    }
    //aca cuando sale del for de turno muestra el mensaje de la puntacion ya que perdio porque no llego a 10000 y se le acabo los turnos
    system("cls");
    scoreJugador1[0]=puntosTotal;
    scoreJugador1[1]=contadorTurno;
    cout<<endl;
    cout<<"     ------------------------------------------"<<endl;
    cout<<"     ¡¡SE HAN ACABADO LOS TURNOS!!"<<endl;
    cout<<"     ------------------------------------------"<<endl;
    cout<<"     "<<jugador1<<" "<<apellido1<<" HA PERDIDO LA PARTIDA :("<<endl;
    cout<<"     SU PUNTAJE FINAL ES "<<scoreJugador1[0]<<endl;
    cout<<"     ------------------------------------------"<<endl;
    cout<<"     LE DESEO MEJOR SUERTE PARA LA PRÓXIMA"<<endl<<endl;

    system("pause");
}

int funcionTirada(char *jugador1, char *apellido1, int contadorTurno, bool AZAR, int puntosTotal, int *vecRepetidos, string *vecNombreCombinaciones, int *scoreJugador1){
    bool tirada=true, continuar;
    int dados[6], vecJugadas[8]={0}, vecPuntos[8]={0}, tam=6, puntosRonda=0, posGanador;
    int contarTirada=0;
    while(tirada){
        system("cls");
        contarTirada++;
        cout<<endl;
        cout<<"     JUGADOR: "<<jugador1<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal<<endl;//falta puntaje
        cout<<"     ---------------------------------------------------------------------"<<endl;
        cout<<"     Puntaje de la ronda= "<<puntosRonda<<endl;
        cout<<"     Lanzamiento: "<<contarTirada<<endl;
        cout<<"     ---------------------------------------------------------------------"<<endl;
        tirarDados(dados, tam, AZAR);
        cout<<"     DADOS"<<endl<<endl;
        mostrarDados(dados, tam);
        ordenarAscendente(dados, tam);
        cargarVecRepetidos(dados, 1 , 6, vecRepetidos);
        //mostrarDados(vecRepetidos, 6);
        posGanador=funcionJugadaObtenida(vecRepetidos, vecJugadas, vecPuntos, vecNombreCombinaciones);// Devuelve los ptos de la ronda y muestra la combinacion.
        //podria hacer un switch
        if(vecPuntos[posGanador]==10000){//gano ya que la tirada le dio 10000 pts
            system("cls");
            puntosRonda=10000;
            cout<<endl;
            cout<<"     ------------------------------------------"<<endl;
            cout<<"     DADOS"<<endl<<endl;
            mostrarDados(dados, tam);
            cout<<endl;
            cout<<"     SU COMBINACIÓN ES "<<vecNombreCombinaciones[vecJugadas[posGanador]]<<endl;
            cout<<"     OBTUVO "<<vecPuntos[posGanador]<<" !!!"<<endl<<endl;
            cout<<"     ------------------------------------------"<<endl<<endl;
            cout<<"         FELICITACIONES "<<jugador1<<" "<<apellido1<<"!!!!"<<endl;
            cout<<"         HAS GANADO LA PARTIDA EN EL TURNO "<<contadorTurno<<"!!!!"<<endl<<endl;
            cout<<"     ------------------------------------------"<<endl;
            //tirada=false;
            return puntosRonda;
        }
        else{
            if(vecPuntos[posGanador]==0) {//sopa
                puntosRonda=0; //si saca sopa pone en 0 los ptos de la ronda y no suma nada
                cout<<"     ¡¡¡PIERDE LOS PUNTOS DE LA RONDA!!!"<<endl<<endl;
                tirada=false;
                system("pause");
            }
            else {
                if((vecPuntos[posGanador]+puntosRonda+puntosTotal)>10000){
                    puntosRonda=0;
                    cout<<"     ¡¡¡SE PASO DE 10000 PIERDE EL TURNO!!!"<<endl<<endl;
                    cout<<"     TIENE QUE HACER 10000 JUSTO"<<endl<<endl;
                    system("pause");
                    return puntosRonda;
                }
                else{
                    puntosRonda+=vecPuntos[posGanador];
                    continuar=funcionContinuar(tirada);
                    if(!continuar){
                        if((puntosRonda+puntosTotal)==10000){
                            system("cls");
                            cout<<endl;
                            cout<<"     JUGADOR: "<<jugador1<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal<<endl;//falta puntaje
                            cout<<"     ---------------------------------------------------------------------"<<endl;
                            cout<<"     Puntaje de la ronda= "<<puntosRonda<<endl;
                            cout<<"     Lanzamiento: "<<contarTirada<<endl;
                            cout<<"     ---------------------------------------------------------------------"<<endl;
                            cout<<"     DADOS"<<endl<<endl;
                            mostrarDados(dados, tam);
                            cout<<endl;
                            cout<<"     SU COMBINACIÓN ES DE"<<vecNombreCombinaciones[vecJugadas[posGanador]]<<endl;
                            cout<<"     PUNTAJE DE LA RONDA "<<puntosRonda<<endl<<endl;
                            cout<<"     ------------------------------------------"<<endl<<endl;
                            cout<<"         ¡¡¡¡ 1 0 0 0 0 0 !!!!"<<endl;
                            cout<<"         FELICITACIONES "<<jugador1<<" "<<apellido1<<"!!!!"<<endl;
                            cout<<"         HAS GANADO LA PARTIDA EN EL TURNO "<<contadorTurno<<"!!!!"<<endl<<endl;
                            cout<<"     ------------------------------------------"<<endl;
                            //system("pause");
                            return puntosRonda;
                            tirada=false;
                        }
                        else{
                            tirada=false;
                        }
                    }
                }
            }
        }
    }
        return puntosRonda;
}

bool funcionContinuar(bool tirada){
    char continuar;
    bool seguir=true;

    while(seguir){

        cout<<"     ¿DESEA CONTINUAR (S/N)?";
        cin>>continuar;

        switch(continuar){
            case 's':
            case 'S':
                tirada=true;
                seguir=false;
                break;
            case 'n':
            case 'N':
                tirada=false;
                seguir=false;
                break;
            default:
                cout<<"     OPCIÓN INCORRECTA"<<endl;
                seguir=true;
                break;
        }
    }
    return tirada;
}

void ordenarAscendente(int *dados, int tam ){
    int i,j, posmin, aux;
    for(i=0;i<tam-1;i++){
        posmin=i;
        for(j=i+1;j<tam;j++){
            if(dados[j]<dados[posmin]) posmin=j;
        }
        aux=dados[i];
        dados[i]=dados[posmin];
        dados[posmin]=aux;
    }
}

int contarNumerosRepetidos(int *dados, int numero, int tam){
    int i, cant=0;
        for(i=0;i<tam;i++){
            if(dados[i]==numero) cant++;
            }
        return cant;
}

void cargarVecRepetidos(int *dados, int numero, int tam, int *vecRepetidos){
    int i, cantidad;

    for(i=0;i<tam;i++){
        cantidad=contarNumerosRepetidos( dados,  numero,  tam);
        vecRepetidos[i]=cantidad;
        //cout<<"El numero "<<i+1<<" se repite "<<vecRepetidos[i]<< " veces"<<endl;//para control
        numero++;
    }
}

int funcionJugadaObtenida(int *vecRepetidos, int *vecJugadas, int *vecPuntos, string *vecNombreCombinaciones){
    int i, posMaxi, contPares=0;
    for(i=0;i<8;i++){//vuelvo a poner en cero el vectorPuntos ya que sino no funcion y en el switch no va a poner en 0 cuando no tenga la jugada sino seria uno por uno.
        vecPuntos[i]=0;
    }
    for(i=0;i<8;i++){//vuelvo a poner en cero el vectorPuntos ya que sino no funcion y en el switch no va a poner en 0 cuando no tenga la jugada sino seria uno por uno.
        vecJugadas[i]=0;
    }
    //cout<<endl;
    for(i=1;i<=8;i++){
        switch(i){
            case 1: //jugadas nro 1, 3, 6 y 9.
                    if(vecRepetidos[0]==6) {
                        vecJugadas[0]=9;
                        vecPuntos[0]=10000;
                    }
                    if(vecRepetidos[0]==4||vecRepetidos[0]==5) {
                        vecJugadas[0]=6;
                        vecPuntos[0]=2000;
                        //cout<<" puntos 1: "<<vecPuntos[0];//para control
                    }
                    if(vecRepetidos[0]==3){
                        vecJugadas[0]=3;
                        vecPuntos[0]=1000;
                        //cout<<" puntos1 : "<<vecPuntos[0];//para control
                    }
                    if(vecRepetidos[0]==2){
                        vecJugadas[0]=1;
                        vecPuntos[0]=200;
                        contPares++;
                        //cout<<" puntos 1: "<<vecPuntos[0];//para control
                    }
                    if(vecRepetidos[0]==1){
                        vecJugadas[0]=1;
                        vecPuntos[0]=100;
                        //cout<<" puntos 1: "<<vecPuntos[0];//para control
                    }
            break;
            case 2: // jugadas nro 0, 4, 5, 7.
                    if(vecRepetidos[1]==6){
                        vecJugadas[1]=7;
                        vecPuntos[1]=1000;
                        //cout<<" puntos 2: "<<vecPuntos[1];//para control
                    }
                    if(vecRepetidos[1]==4||vecRepetidos[1]==5) {
                        vecJugadas[1]=5;
                        vecPuntos[1]=400;
                        //cout<<" puntos 2: "<<vecPuntos[1];//para control
                    }
                    if(vecRepetidos[1]==3){
                        vecJugadas[1]=4;
                        vecPuntos[1]=200;
                        //cout<<" puntos 2: "<<vecPuntos[1];//para control
                    }

                    if(vecRepetidos[1]==2){
                        vecJugadas[1]=0;
                        vecPuntos[1]=0;
                        contPares++;
                        //cout<<" puntos 2: "<<vecPuntos[1];//para control
                    }
                    if(vecRepetidos[1]==1){
                        vecJugadas[1]=0;
                        vecPuntos[1]=0;
                        //cout<<" puntos 2: "<<vecPuntos[1];//para control
                    }
            break;
            case 3: // jugadas nro 0, 4, 5, 7
                    if(vecRepetidos[2]==6){
                        vecJugadas[2]=7;
                        vecPuntos [2]=1000;
                        //cout<<" puntos 3: "<<vecPuntos[1];//para control
                    }
                    if(vecRepetidos[2]==4||vecRepetidos[2]==5) {
                        vecJugadas[2]=5;
                        vecPuntos [2]=600;
                        //cout<<" puntos 3: "<<vecPuntos[2];//para control
                    }
                    if(vecRepetidos[2]==3){
                        vecJugadas[2]=4;
                        vecPuntos [2]=300;
                        //cout<<" puntos 3: "<<vecPuntos[2];//para control
                    }

                    if(vecRepetidos[2]==2){
                        vecJugadas[2]=0;
                        vecPuntos [2]=0;
                        contPares++;
                        //cout<<" puntos 3: "<<vecPuntos[2];//para control
                    }
                    if(vecRepetidos[2]==1){
                        vecJugadas[2]=0;
                        vecPuntos [2]=0;
                        //cout<<" puntos 3: "<<vecPuntos[2];//para control
                    }
            break;
            case 4: // jugadas nro 0, 4, 5, 7
                    if(vecRepetidos[3]==6){
                        vecJugadas[3]=7;
                        vecPuntos [3]=1000;
                        //cout<<" puntos 4: "<<vecPuntos[3];//para control
                    }
                    if(vecRepetidos[3]==4||vecRepetidos[3]==5) {
                        vecJugadas[3]=5;
                        vecPuntos [3]=800;
                        //cout<<" puntos 4: "<<vecPuntos[3];//para control
                    }
                    if(vecRepetidos[3]==3){
                        vecJugadas[3]=4;
                        vecPuntos [3]=400;
                        //cout<<" puntos 4: "<<vecPuntos[3];//para control
                    }

                    if(vecRepetidos[3]==2){
                        vecJugadas[3]=0;
                        vecPuntos [3]=0;
                        contPares++;
                        //cout<<" puntos 4: "<<vecPuntos[3];//para control
                    }
                    if(vecRepetidos[3]==1){
                        vecJugadas[3]=0;
                        vecPuntos [3]=0;
                        //cout<<" puntos 4: "<<vecPuntos[3];//para control
                    }
            break;
            case 5: // jugadas nro 2, 4, 5, 7.
                    if(vecRepetidos[4]==6){
                        vecJugadas[4]=7;
                        vecPuntos [4]=1000;
                        //cout<<" puntos 5: "<<vecPuntos[4];//para control
                    }
                    if(vecRepetidos[4]==4||vecRepetidos[4]==5) {
                        vecJugadas[4]=5;
                        vecPuntos [4]=1000;
                        //cout<<" puntos 5: "<<vecPuntos[4];//para control
                    }
                    if(vecRepetidos[4]==3){
                        vecJugadas[4]=4;
                        vecPuntos [4]=500;
                        //cout<<" puntos 5: "<<vecPuntos[4];//para control
                    }
                    if(vecRepetidos[4]==2){
                        vecJugadas[4]=2;
                        vecPuntos [4]=100;
                        contPares++;
                        //cout<<" puntos 5: "<<vecPuntos[4];//para control
                    }
                    if(vecRepetidos[4]==1){
                        vecJugadas[4]=2;
                        vecPuntos [4]=50;
                        //cout<<" puntos 5: "<<vecPuntos[4];//para control
                    }
            break;
            case 6: // jugadas nro 0, 4, 5, 7.

                    if(vecRepetidos[5]==6){
                        vecJugadas[5]=7;
                        vecPuntos [5]=1000;
                        //cout<<" puntos 6: "<<vecPuntos[5];//para control
                    }
                    if(vecRepetidos[5]==4||vecRepetidos[5]==5) {
                        vecJugadas[5]=5;
                        vecPuntos [5]=1200;
                        //cout<<" puntos 6: "<<vecPuntos[5];//para control
                    }
                    if(vecRepetidos[5]==3){
                        vecJugadas[5]=4;
                        vecPuntos [5]=600;
                        //cout<<" puntos 6: "<<vecPuntos[5];//para control
                    }

                    if(vecRepetidos[5]==2){
                        vecJugadas[5]=0;
                        vecPuntos [5]=0;
                        contPares++;
                        //cout<<" puntos 6: "<<vecPuntos[5];//para control
                    }
                    if(vecRepetidos[5]==1){
                        vecJugadas[5]=0;
                        vecPuntos [5]=0;
                        //cout<<" puntos 6: "<<vecPuntos[5];//para control
                    }
            break;
            case 7://escalera
                    if(vecRepetidos[0]==1 && vecRepetidos[1]==1 && vecRepetidos[2]==1 && vecRepetidos[3]==1 && vecRepetidos[4]==1 &&vecRepetidos[5]==1){
                        vecJugadas[6]=8;
                        vecPuntos [6]=1500;
                        //cout<<" puntos 7: "<<vecPuntos[6];//para control
                    }
            break;
            case 8://TRES PARES
                    if(contPares==3){
                        vecJugadas[7]=7;
                        vecPuntos [7]=1000;
                        //cout<<" puntos 8: "<<vecPuntos[7];//para control
                    }
            break;
        }
    }
        posMaxi=definirJugadaGanadora(vecPuntos);
        ingresarNombreCombinaciones(vecNombreCombinaciones);
        //para control
        /*for(i=0;i<8;i++){//para control
           cout<<"vecPuntos  "<<vecPuntos[i]<<endl;
        }
        for(i=0;i<8;i++){//para control
           cout<<"vecJugadas  "<<vecJugadas[i]<<endl;
        }*/
        if(vecJugadas[posMaxi]==4 || vecJugadas[posMaxi]==5){
            cout<<"     SU COMBINACIÓN ES "<<vecNombreCombinaciones[vecJugadas[posMaxi]]<<"DE "<<posMaxi+1<<endl;
            cout<<"     PUNTAJE DEL LAMZAMIENTO "<<vecPuntos[posMaxi]<<endl<<endl;
        }
        else{
            cout<<"     SU COMBINACIÓN ES "<<vecNombreCombinaciones[vecJugadas[posMaxi]]<<endl;
            cout<<"     PUNTAJE DEL LAMZAMIENTO "<<vecPuntos[posMaxi]<<endl<<endl;
        }
    return posMaxi;

}

int definirJugadaGanadora(int *vecPuntos){
    int posMaxi, i;
    cout<<endl;
    for(i=0;i<8;i++){
    //cout<<"VECTOR PUNTOS "<<vecPuntos[i]<<endl;//para control
    }
    posMaxi=maximoVector(vecPuntos);
   // cout<<"MAXIMO PUNTOS"<<vecPuntos[posMaxi]<<endl;//para control

    return posMaxi;
}

int maximoVector(int *vecPuntos){
    int i, posMaxi=0;
    for(i=1;i<8;i++){
        if(vecPuntos[i]>vecPuntos[posMaxi]) {
                posMaxi=i;
        }
    }
    return posMaxi;
}

void funcionReglas(){
    cout<<endl;
    cout<<"     ------------------------------------------------------------------------"<<endl;
    cout<<"     MODO UN JUGADOR"<<endl<<endl;
    cout<<"     EL OBJETIVO ES LLEGAR A HACER 10000 PUNTOS ANTES DE QUE SE ACABEN LAS "<<endl;
    cout<<"     RONDAS ESTABLECIDAS."<<endl;
    cout<<"     POR CADA LANZAMIENTO USTED PODRÁ VER LA COMBINACIÓN GANADORA Y LOS "<<endl;
    cout<<"     PUNTOS OBTENIDOS DE ESE TIRO Y PODRÁ DECIDIR SI CONTINUAR O NO. SI"<<endl;
    cout<<"     CONTINÚA, LOS PUNTOS DEL PRÓXIMO LANZAMIENTO SE IRÁN SUMANDO A LOS "<<endl;
    cout<<"     PUNTOS DE LA RONDA. ESTO SUCEDERÁ HASTA QUE DECIDA PLANTARSE O QUE "<<endl;
    cout<<"     OBTENGA SOPA. AQUÍ EL RIESGO DE CONTINUAR LANZANDO."<<endl;
    cout<<"     SOPA: AQUELLAS JUGADAS EN DONDE OBTIENE 0 PUNTOS. AL SACAR ESTA JUGADA "<<endl;
    cout<<"     PERDERÁ LOS PUNTOS DE LA RONDA OBTENIDOS HASTA EL MOMENTO Y CAMBIARÁ "<<endl;
    cout<<"     DE TURNO."<<endl;
    cout<<"     SI SE PLANTA SE SUMARÁN LOS PUNTOS DE LA RONDA A LOS PUNTOS TOTALES DEL "<<endl;
    cout<<"     JUEGO Y CAMBIARÁ DE TURNO. "<<endl;
    cout<<"     EL JUEGO TERMINA CUANDO HACE 10000 PUNTOS EXACTOS O QUE SE TERMINEN LOS "<<endl;
    cout<<"     TURNOS. SI SE PASA DEL PUNTAJE FINAL SE PERDERÁ EL TURNO Y CONTINUARÁ"<<endl;
    cout<<"     CON LOS PUNTOS TOTALES HASTA EL MOMENTO."<<endl<<endl;
    cout<<"     BUEN JUEGO!"<<endl;
    cout<<"     ------------------------------------------------------------------------"<<endl;
    //MODIFICAR!!
    cout<<"     MODO DOS JUGADORES"<<endl<<endl;
    cout<<"     EL OBJETIVO ES LLEGAR A HACER 10000 PUNTOS ANTES DE QUE SE ACABEN LAS "<<endl;
    cout<<"     RONDAS ESTABLECIDAS."<<endl;
    cout<<"     AQUEL JUGADOR EN ALCANZAR ESE PUNTAJE PRIMERO GANARÁ EL JUEGO. PERO EN "<<endl;
    cout<<"     CASO DE LLEGAR EN LA MISMA RONDA SERÁ EMPATE."<<endl;

    cout<<"     CADA JUGADOR EN CADA LANZAMIENTO PODRÁ VER LA COMBINACIÓN GANADORA "<<endl;
    cout<<"     Y LOS PUNTOS OBTENIDOS DE ESE TIRO Y PODRÁ DECIDIR SI CONTINUAR LANZANDO "<<endl;
    cout<<"     O NO. SI CONTINÚA, LOS PUNTOS DEL PRÓXIMO LANZAMIENTO SE IRÁN SUMANDO A "<<endl;
    cout<<"     LOS PUNTOS DE LA RONDA. ESTO SUCEDERÁ HASTA QUE DECIDA PLANTARSE O QUE "<<endl;
    cout<<"     OBTENGA SOPA."<<endl;

    cout<<"     SOPA: AQUELLAS JUGADAS EN DONDE OBTIENE 0 PUNTOS. AL SACAR ESTA JUGADA "<<endl;
    cout<<"     PERDERÁ LOS PUNTOS DE LA RONDA OBTENIDOS HASTA EL MOMENTO Y CAMBIARÁ "<<endl;
    cout<<"     DE TURNO. AQUÍ EL RIESGO DE CONTINUAR LANZANDO."<<endl;

    cout<<"     SI SE PLANTA SE SUMARÁN LOS PUNTOS DE LA RONDA A LOS PUNTOS TOTALES DEL "<<endl;
    cout<<"     JUEGO Y CAMBIARÁ DE TURNO. "<<endl;

    cout<<"     EL JUEGO TERMINA CUANDO UN JUGADOR HACE 10000 PUNTOS EXACTOS O QUE SE "<<endl;
    cout<<"     TERMINEN LOS TURNOS. SI SE PASA DEL PUNTAJE FINAL SE PERDERÁ EL TURNO Y "<<endl;
    cout<<"     CONTINUARÁ CON LOS PUNTOS TOTALES HASTA EL MOMENTO. "<<endl;

    cout<<"     EN CASO DE QUE SE TERMINEN LOS TURNOS Y NINGUNO HAYA CONSEGUIDO LOS "<<endl;
    cout<<"     10000 PUNTOS ENTONCES EL GANADOR SERÁ AQUEL QUE ALLÁ QUEDADO CON EL "<<endl;
    cout<<"     PUNTAJE MAYOR. "<<endl<<endl;
    cout<<"     BUEN JUEGO!"<<endl;
}
///////////////////////////////////////////////////////////////////////////////////////////
void funcionTurno2(char *jugador_1, char *apellido_1, char *jugador_2, char *apellido_2, bool AZAR, int *vecRepetidos_2, string *vecNombreCombinaciones, int *scoreJugador_1, int *scoreJugador_2){
system("cls");
    int i,cantTurnos, puntosTotal=0, puntosTotal2=0, puntosRonda, puntosRonda2;
    int contadorTurno=0;
    bool jugador1win=false;
    cout<<endl;
    cout<<"     INGRESAR CANTIDAD DE TURNOS: ";
    cin>>cantTurnos;
    for(i=0;i<cantTurnos;i++){
        contadorTurno++;
        system("cls");
        //nro de turno, proximo turno de, puntaje parcial de ambos jugadores.
        cout<<endl;
        cout<<"     TURNO NRO: "<<contadorTurno<<endl;
        cout<<"     LANZA EL JUGADOR: "<<jugador_2<<endl;
        cout<<"     ---------------------------------"<<endl;
        cout<<"     PUNTAJES PARCIALES"<<endl;
        cout<<"     PUNTAJE "<<jugador_1<<": "<<puntosTotal<<endl;
        cout<<"     PUNTAJE "<<jugador_2<<": "<<puntosTotal2<<endl;
        cout<<"     ---------------------------------"<<endl;
        system("pause");
        system("cls");
        cout<<endl;
        cout<<"     JUGADOR: "<<jugador_1<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal<<endl;//falta puntaje
        cout<<"     ----------------------------------------------------------------"<<endl;
        puntosRonda=funcionTirada2(jugador_1, apellido_1, contadorTurno, AZAR, puntosTotal, vecRepetidos_2, vecNombreCombinaciones, scoreJugador_1);
        puntosTotal+=puntosRonda;

        if(puntosRonda==10000){ //si saca sexteto jugador 1
            jugador1win=true;
            scoreJugador_1[0]=puntosRonda;
            scoreJugador_1[1]=contadorTurno;
            }
        if(puntosTotal==10000){//llega a 10000 jugador 1
            jugador1win=true;
            scoreJugador_1[0]=puntosTotal;
            scoreJugador_1[1]=contadorTurno;
        }
    system("pause");
    system("cls");
        cout<<endl;
        cout<<"     TURNO NRO: "<<contadorTurno<<endl;
        cout<<"     LANZA EL JUGADOR: "<<jugador_2<<endl;
        cout<<"     ---------------------------------"<<endl;
        cout<<"     PUNTAJES PARCIALES"<<endl;
        cout<<"     PUNTAJE "<<jugador_1<<": "<<puntosTotal<<endl;
        cout<<"     PUNTAJE "<<jugador_2<<": "<<puntosTotal2<<endl;
        cout<<"     ---------------------------------"<<endl;
        if(jugador1win) cout<<"     EL JUGADOR "<<jugador_1<<" GANARÁ SI NO LOGRA SACAR 10000 EN LA SIGUIENTE RONDA"<<endl;
        system("pause");
        system("cls");
        cout<<endl;
        cout<<"     JUGADOR: "<<jugador_2<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal2<<endl;//falta puntaje
        cout<<"     ----------------------------------------------------------------"<<endl;
        puntosRonda2=funcionTirada2(jugador_2, apellido_2, contadorTurno, AZAR, puntosTotal2, vecRepetidos_2, vecNombreCombinaciones, scoreJugador_2);
        puntosTotal2+=puntosRonda2;
        system("pause");
        if(puntosRonda2==10000){ //si saca sexteto jugador 2
            if(jugador1win){//empatan ya que jugador 1 tambien saco sexteto
                system("cls");
                cout<<"         ¡ ¡ ¡ EMPATE ! ! !"<<endl;
                cout<<"             TURNO: "<<contadorTurno<<endl;
                cout<<"     ---------------------------------"<<endl;
                cout<<"     PUNTAJE "<<jugador_1<<" "<<apellido_1<<": "<<puntosTotal<<endl;
                cout<<"     PUNTAJE "<<jugador_2<<" "<<apellido_2<<": "<<puntosTotal2<<endl;
                cout<<"     ---------------------------------"<<endl;
                cout<<"     BUEN JUEGO!"<<endl;
                scoreJugador_1[0]=puntosTotal;
                scoreJugador_1[1]=contadorTurno;
                scoreJugador_2[0]=puntosRonda2;
                scoreJugador_2[1]=contadorTurno;
                system("pause");
                return;
            }
            else{
                system("cls"); //gana jugador 2
                cout<<"      ¡ ¡ ¡ FELICITACIONES "<<jugador_2<<" "<<apellido_2<<" ! ! !"<<endl;
                cout<<"      HAS GANADO LA PARTIDA EN EL TURNO "<<contadorTurno<<endl;
                cout<<"     ------------------------------------------------------------"<<endl;
                cout<<"     PUNTAJE "<<jugador_1<<" "<<apellido_1<<": "<<puntosTotal<<endl;
                cout<<"     PUNTAJE "<<jugador_2<<" "<<apellido_2<<": "<<puntosTotal2<<endl;
                cout<<"     ------------------------------------------------------------"<<endl;
                cout<<"     BUEN JUEGO!"<<endl;
                scoreJugador_2[0]=puntosRonda2;
                scoreJugador_2[1]=contadorTurno;
                scoreJugador_1[1]=contadorTurno;//lo pongo para la condicion de la puntacion mas alta
                system("pause");
                return;
            }
        }
        if(puntosTotal2==10000){//llega a 10000 jugador 2
            if(jugador1win){//empatan ya que jugador 1 tambien llego a 10000
                system("cls");
                cout<<"         ¡ ¡ ¡ EMPATE ! ! !"<<endl;
                cout<<"             TURNO: "<<contadorTurno<<endl;
                cout<<"     ---------------------------------"<<endl;
                cout<<"     PUNTAJE "<<jugador_1<<" "<<apellido_1<<": "<<puntosTotal<<endl;
                cout<<"     PUNTAJE "<<jugador_2<<" "<<apellido_2<<": "<<puntosTotal2<<endl;
                cout<<"     ---------------------------------"<<endl;
                cout<<"     BUEN JUEGO!"<<endl;
                scoreJugador_1[0]=puntosTotal;
                scoreJugador_1[1]=contadorTurno;
                scoreJugador_2[0]=puntosRonda2;
                scoreJugador_2[1]=contadorTurno;
                system("pause");
                return;
            }
            else{
                system("cls"); //gana jugador 2
                cout<<"      ¡ ¡ ¡ FELICITACIONES "<<jugador_2<<" "<<apellido_2<<" ! ! !"<<endl;
                cout<<"      HAS GANADO LA PARTIDA EN EL TURNO "<<contadorTurno<<endl;
                cout<<"     ------------------------------------------------------------"<<endl;
                cout<<"     PUNTAJE "<<jugador_1<<" "<<apellido_1<<": "<<puntosTotal<<endl;
                cout<<"     PUNTAJE "<<jugador_2<<" "<<apellido_2<<": "<<puntosTotal2<<endl;
                cout<<"     ------------------------------------------------------------"<<endl;
                cout<<"     BUEN JUEGO!"<<endl;
                scoreJugador_2[0]=puntosRonda2;
                scoreJugador_2[1]=contadorTurno;
                scoreJugador_1[1]=contadorTurno;//lo pongo para la condicion de la puntacion mas alta
                system("pause");
                return;
            }
        }

        if(jugador1win){//si entra aca es porque el jugador 2 no logro 10000 en el turno y gana jugador 1
            system("cls");
            cout<<"      ¡ ¡ ¡ FELICITACIONES "<<jugador_1<<" "<<apellido_1<<" ! ! !"<<endl;
            cout<<"      HAS GANADO LA PARTIDA EN EL TURNO "<<contadorTurno<<endl;
            cout<<"     ------------------------------------------------------------"<<endl;
            cout<<"     PUNTAJE "<<jugador_1<<" "<<apellido_1<<": "<<puntosTotal<<endl;
            cout<<"     PUNTAJE "<<jugador_2<<" "<<apellido_2<<": "<<puntosTotal2<<endl;
            cout<<"     ------------------------------------------------------------"<<endl;
            cout<<"     BUEN JUEGO!"<<endl;
            scoreJugador_1[0]=puntosRonda2;
            scoreJugador_1[1]=contadorTurno;
            system("pause");
            return;
        }
    }
    // SALE DEL FOR. se acaban los turnos compara el puntaje e informa el mayor puntaje con el ganador
    system("cls");
    scoreJugador_1[0]=puntosTotal;
    scoreJugador_1[1]=contadorTurno;
    scoreJugador_2[0]=puntosTotal2;
    scoreJugador_2[1]=contadorTurno;
    cout<<endl;
    cout<<"     ------------------------------------------"<<endl;
    cout<<"     ¡¡SE HAN ACABADO LOS TURNOS!!"<<endl;
    cout<<"     ------------------------------------------"<<endl;
    cout<<"     PUNTAJE "<<jugador_1<<" "<<apellido_1<<": "<<scoreJugador_1[0]<<endl;
    cout<<"     PUNTAJE "<<jugador_2<<" "<<apellido_2<<": "<<scoreJugador_2[0]<<endl;
    cout<<"     ------------------------------------------"<<endl;
    if(scoreJugador_1[0]>scoreJugador_2[0]){
        cout<<"     EL GANADOR ES: "<<jugador_1<<" "<<apellido_1<<endl;
    }
    else{
        if(scoreJugador_1[0]<scoreJugador_2[0]){
            cout<<"     EL GANADOR ES: "<<jugador_2<<" "<<apellido_2<<endl;
        }
        else{
            cout<<"     ¡EMPATARON!"<<endl;
        }
    }

    system("pause");
}

int funcionTirada2(char *jugador1, char *apellido1, int contadorTurno, bool AZAR, int puntosTotal, int *vecRepetidos, string *vecNombreCombinaciones, int *scoreJugador1){
    bool tirada=true, continuar;
    int dados[6], vecJugadas[8]={0}, vecPuntos[8]={0}, tam=6, puntosRonda=0, posGanador;
    int contarTirada=0;
    while(tirada){
        system("cls");
        contarTirada++;
        cout<<endl;
        cout<<"     JUGADOR: "<<jugador1<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal<<endl;//falta puntaje
        cout<<"     ---------------------------------------------------------------------"<<endl;
        cout<<"     Puntaje de la ronda= "<<puntosRonda<<endl;
        cout<<"     Lanzamiento: "<<contarTirada<<endl;
        cout<<"     ---------------------------------------------------------------------"<<endl;
        tirarDados(dados, tam, AZAR);
        cout<<"     DADOS"<<endl<<endl;
        mostrarDados(dados, tam);
        ordenarAscendente(dados, tam);
        cargarVecRepetidos(dados, 1 , 6, vecRepetidos);
        //mostrarDados(vecRepetidos, 6);
        posGanador=funcionJugadaObtenida(vecRepetidos, vecJugadas, vecPuntos, vecNombreCombinaciones);// Devuelve los ptos de la ronda y muestra la combinacion.

        if(vecPuntos[posGanador]==10000){//gano ya que la tirada le dio 10000 pts
            system("cls");
            puntosRonda=10000;
            cout<<endl;
            cout<<"     ------------------------------------------"<<endl;
            cout<<"     DADOS"<<endl<<endl;
            mostrarDados(dados, tam);
            cout<<endl;
            cout<<"     SU COMBINACIÓN ES "<<vecNombreCombinaciones[vecJugadas[posGanador]]<<endl;
            cout<<"     OBTUVO "<<vecPuntos[posGanador]<<" !!!"<<endl;
            cout<<"     ------------------------------------------"<<endl<<endl;
            cout<<"         FELICITACIONES "<<jugador1<<" "<<apellido1<<"!!!!"<<endl;
            cout<<"         HAS OBTENIDO 10000 EN EL TURNO "<<contadorTurno<<"!!!!"<<endl<<endl;
            cout<<"     ------------------------------------------"<<endl;
            return puntosRonda;
        }
        else{
            if(vecPuntos[posGanador]==0) {//sopa
                puntosRonda=0; //si saca sopa pone en 0 los ptos de la ronda y no suma nada
                cout<<"     ¡¡¡PIERDE LOS PUNTOS DE LA RONDA!!!"<<endl<<endl;
                tirada=false;
                system("pause");
            }
            else {
                if((vecPuntos[posGanador]+puntosRonda+puntosTotal)>10000){
                    puntosRonda=0;
                    cout<<"     ¡¡¡SE PASO DE 10000 PIERDE EL TURNO!!!"<<endl<<endl;
                    cout<<"     TIENE QUE HACER 10000 JUSTO"<<endl<<endl;
                    system("pause");
                    return puntosRonda;
                }
                else{
                    puntosRonda+=vecPuntos[posGanador];
                    continuar=funcionContinuar(tirada);
                    if(!continuar){
                        if((puntosRonda+puntosTotal)==10000){
                            system("cls");
                            cout<<endl;
                            cout<<"     JUGADOR: "<<jugador1<<"\t| TURNO: "<<contadorTurno<<"\t| PUNTAJE= "<<puntosTotal<<endl;//falta puntaje
                            cout<<"     ---------------------------------------------------------------------"<<endl;
                            cout<<"     Puntaje de la ronda= "<<puntosRonda<<endl;
                            cout<<"     Lanzamiento: "<<contarTirada<<endl;
                            cout<<"     ---------------------------------------------------------------------"<<endl;
                            cout<<"     DADOS"<<endl<<endl;
                            mostrarDados(dados, tam);
                            cout<<endl;
                            cout<<"     SU COMBINACIÓN ES DE "<<vecNombreCombinaciones[vecJugadas[posGanador]]<<endl;
                            cout<<"     PUNTAJE DE LA RONDA "<<puntosRonda<<endl;
                            cout<<"     ------------------------------------------"<<endl<<endl;
                            cout<<"         FELICITACIONES "<<jugador1<<" "<<apellido1<<"!!!!"<<endl;
                            cout<<"         HAS OBTENIDO 10000 EN EL TURNO "<<contadorTurno<<"!!!!"<<endl<<endl;
                            cout<<"     ------------------------------------------"<<endl;
                            //system("pause");
                            return puntosRonda;
                            tirada=false;
                        }
                        else{
                            tirada=false;
                        }
                    }
                }
            }
        }
    }
        return puntosRonda;
}
