#ifndef FUNCIONES10MIL_H_INCLUDED
#define FUNCIONES10MIL_H_INCLUDED

int scoreJugador1(int);
void ingresarNombre(char *jugador1,char *apellido1);
void ingresarNombres(char *jugador_1, char *apellido_1,char *jugador_2, char *apellido_2);
void tirarDados(int *vecDados, int tam, bool AZAR);
void mostrarDados(int *dados, int tam);
void funcionTurno(char *jugador1, char *apellido1, bool AZAR, int *vecRepetidos, string *vecNombreCombinaciones, int *scoreJugador1);
int funcionTirada(char *jugador1, char *apellido1, int contadorTurno, bool AZAR, int puntosTotal, int *vecRepetidos, string *vecNombreCombinaciones, int *scoreJugador1);
bool funcionContinuar(bool tirada);
void ordenarAscendente(int *dados, int tam );
int contarNumerosRepetidos(int *dados, int numero, int tam);
void cargarVecRepetidos(int *dados, int numero, int tam, int *vecRepetidos);
int funcionJugadaObtenida(int *vecRepetidos, int *vecJugadas, int *vecPuntos, string *vecNombreCombinaciones);
int definirJugadaGanadora(int *vecPuntos);
int maximoVector(int *vecPuntos);
void ingresarNombreCombinaciones(string *vecNombreCombinaciones);
void mostrarNombreCombinaciones(string *vecNombreCombinaciones);
void funcionReglas();

//funciones modo dos jugadores
void funcionTurno2(char *jugador_1, char *apellido_1, char *jugador_2, char *apellido_2, bool AZAR, int *vecRepetidos_2, string *vecNombreCombinaciones, int *scoreJugador_1, int *scoreJugador_2);
int funcionTirada2(char *jugador1, char *apellido1, int contadorTurno, bool AZAR, int puntosTotal, int *vecRepetidos, string *vecNombreCombinaciones, int *scoreJugador1);

#endif // FUNCIONES10MIL_H_INCLUDED
