#pragma once
#include <vector>
#include <list>
#include <omp.h>
#include "ClasePersona.h"
#include <chrono>
#include <random>
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
	void llenarLista(double cantInfec, double infec, double rec, int tamano, int cantidad);

	//EFE:
	//REQ:
	//MOD:
	void mover();

	//EFE:
	//REQ:
	//MOD:
	void revisar(int contSem);

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

	double genRandom();

	int contInfectados(list<ClasePersona> lista);

private:
	
	vector<vector<int>> poblacionInfectada; //Matriz con la cantidad de enfermos por posición
	list<ClasePersona> poblacion; //Lista con todas las personas.
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

