#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <cwchar>
using namespace std;

#include "funciones10mil.h"

int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "spanish");
    system("title G A M E  1 0 0 0 0");
    system("color C0");//la C cambia el fondo y el 0 cambia la letra
    //tamaño letra
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=0;
    cfi.dwFontSize.Y=36;
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_NORMAL;
    std:wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


    string vecNombreCombinaciones[10];
    char jugador1[20], apellido1[20], jugador_1[20], apellido_1[20], jugador_2[20], apellido_2[20];
    int opc, vecRepetidos[6], scoreJugador1[2]={0};
    int vecRepetidos_2[6], scoreJugador_1[2]={0},scoreJugador_2[2]={0};
    bool AZAR=true;

    while(true){
        system("cls");
        cout<<"                      "<<endl;
        cout<<"       ¡¡¡1 0 0 0 0 !!!"<<endl;
        cout<<"     ---------------------"<<endl;
        cout<<"     1. MODO UN JUGADOR"<<endl;
        cout<<"     2. MODO DOS JUGADORES"<<endl;
        cout<<"     3. MOSTRAR PUNTACIÓN MÁS ALTA"<<endl;
        cout<<"     4. REGLAS DEL JUEGO "<<endl;//AGREGAR LAS REGLAS
        cout<<"     0. FIN DEL PROGRAMA"<<endl;
        cout<<"     ---------------------"<<endl;
        cout<<"     ELIJA UNA OPCIÓN: ";
        cin>>opc;
        system("cls");

        switch(opc){
                case 1: cout<<endl;
                        cout<<"     MODO UN JUGADOR "<<endl<<endl;
                        ingresarNombre(jugador1,apellido1);
                        funcionTurno(jugador1, apellido1, AZAR, vecRepetidos, vecNombreCombinaciones, scoreJugador1);/*FUNCION PRINCIPAL. dentro la funcionTirada. genera el espacio de
                        visualizacion. Calcula y muestra los puntajes y el nombre de la combinacion*/

                        break;
                case 2: cout<<endl;
                        cout<<"     MODO DOS JUGADOR: "<<endl<<endl;
                        ingresarNombres(jugador_1,apellido_1,jugador_2,apellido_2);
                        funcionTurno2(jugador_1, apellido_1, jugador_2, apellido_2, AZAR, vecRepetidos_2, vecNombreCombinaciones, scoreJugador_1, scoreJugador_2);

                        break;
                case 3:
                        cout<<endl;
                        if(scoreJugador1[1]==0&&scoreJugador_1[1]==0){
                            cout<<"     NO SE REGISTRON PARTIDAS"<<endl;
                            break;
                        }
                        if(scoreJugador1[0]==0){//si el vector esta vacio es porque no se juego en modo un jugador
                            cout<<"     MODO DOS JUGADORES"<<endl;
                            if(scoreJugador_1[0]>scoreJugador_2[0]){//poner bandera ganador en el modo 2 jug para saber quien gano
                                cout<<"     El score del ganador "<<jugador_1<<" "<<apellido_1<<" es: "<<scoreJugador_1[0]<< " en el turno: "<<scoreJugador_1[1]<<endl;
                            }
                            else{
                                cout<<"     El score del ganador "<<jugador_2<<" "<<apellido_2<<" es: "<<scoreJugador_2[0]<< " en el turno: "<<scoreJugador_2[1]<<endl;
                            }
                        }
                        else{
                            if(scoreJugador_2[0]==0){
                                cout<<"     MODO UN JUGADOR "<<endl<<endl;
                                cout<<"     El score de "<<jugador1<<" "<<apellido1<<" es: "<<scoreJugador1[0]<< " en el turno: "<<scoreJugador1[1]<<endl;
                            }
                            else{
                                cout<<"     MODO UN JUGADOR "<<endl;
                                cout<<"     El score de "<<jugador1<<" "<<apellido1<<" es: "<<scoreJugador1[0]<< " en el turno: "<<scoreJugador1[1]<<endl;
                                cout<<"     -------------------------------------------------------"<<endl<<endl;
                                cout<<"     MODO DOS JUGADORES"<<endl;
                                if(scoreJugador_1[0]>scoreJugador_2[0]){//poner bandera ganador en el modo 2 jug para saber quien gano
                                    cout<<"     El score del ganador "<<jugador_1<<" "<<apellido_1<<" es: "<<scoreJugador_1[0]<< " en el turno: "<<scoreJugador_1[1]<<endl;
                                }
                                else{
                                    cout<<"     El score del ganador "<<jugador_2<<" "<<apellido_2<<" es: "<<scoreJugador_2[0]<< " en el turno: "<<scoreJugador_2[1]<<endl;
                                }
                            }
                        }
                        break;
                case 4:
                        funcionReglas();
                        break;

                case 0:
                        cout<<"                                     "<<endl<<endl;
                        cout<<"     ¡¡¡QUE TENGA UN EXCELENTE DÍA!!!"<<endl<<endl;
                        return 0;
                        break;
                default:
                        cout<<"     OPCIÓN INCORRECTA"<<endl;
                        break;
        }
        system("pause");
    }
    return 0;
}
