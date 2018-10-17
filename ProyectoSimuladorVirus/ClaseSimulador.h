#pragma once
#include <vector>
#include <list>
#include <omp.h>
#include "ClasePersona.h"
#include <chrono>
#include <fstream>
#include <random>
#include <time.h>
#include <stdlib.h> 
//#include <Billy>

using namespace std;

class ClaseSimulador
{
public:
	ClaseSimulador();
	~ClaseSimulador();

	//EFE: Genera una matriz con los estados de cada persona
	//REQ: Un M coherente con la cantidad de personas
	//MOD: matrizEstado
	void inicializar(double cantInfec, double infec, double rec, int tamano, int cantidad, ofstream& bit, char r);

	//EFE: Mueve y realiza la revisón la contidad de veces que el usuario indique
	//REQ: Cantidad valida de tics y cantidad de semanas, además de los elementos para la creación de la bitácora.
	//MOD: vector de personas(población) y matriz de estados.
	void ejecutar(int tics, int contSem, ofstream& bit, char r);

	//EFE:
	//REQ:
	//MOD:
	void mover();

	//EFE:
	//REQ:
	//MOD:
	void revisar(int contSem, ofstream& bit, char r);

	//EFE:
	//REQ:
	//MOD:
	bool infectar(ClasePersona persona);
	//EFE:
	//REQ:
	//MOD:
	bool curar(ClasePersona persona);

	//EFE:
	//REQ:
	//MOD:
	pair<int,int> generarPosRandom(int tam);

	//EFE: Cambia la pocision de una persona hacia arriba
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void arriba(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia abajo
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void abajo(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia la derecha
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void derecha(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia la izquierda
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void izquierda(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia la diagonal inferior derecha
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void diaDerAbajo(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia la diagonal superior derecha
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void diaDerArriba(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia la diagonal inferior izquierda
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void diaIzqAbajo(ClasePersona &persona);

	//EFE: Cambia la pocision de una persona hacia la diagonal superior derecha
	//REQ: Persona valida
	//MOD: Matriz de Poblacion Infectada y la posicion de la persona
	void diaIzqArriba(ClasePersona &persona);

	double genRandom();

private:
	int enfermos = 0;
	pair<int, int> posAnt, posAux;
	vector<vector<int>> poblacionInfectada; //Matriz con la cantidad de enfermos por posición
	vector<ClasePersona> poblacion; //Lista con todas las personas.
};

//End of file with a Cow (Bettsy)
//                               __.----.___
//   ||            ||  (\(__)/)-'||      ;--` ||
//  _||____________||___`(QQ)'___||______;____||_
//  -||------------||----)  (----||-----------||-
//  _||____________||___(o  o)___||______;____||_
//  -||------------||----`--'----||-----------||-
//   ||            ||       `|| ||| || ||     ||jgs
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

