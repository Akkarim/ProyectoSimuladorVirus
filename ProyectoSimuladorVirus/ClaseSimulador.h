#pragma once
#include <vector>
#include <list>
#include "ClasePersona.h"

using namespace std;

class ClaseSimulador
{
public:
	ClaseSimulador();
	~ClaseSimulador();
	//EFE: Llena una lista con todas las personas, osea genera la poblacion.
	//REQ: Probabilidades válidas, al igual que la cantidad y además el tamaño de la matriz a trabajar para generar posiciones.
	//MOD: población.
	void llenarListaPersonas(double infec, double rec, int estado, int tamano,int cantidad);

	//EFE: Genera una matriz con los estados de cada persona
	//REQ: Un M coherente con la cantidad de personas
	//MOD: matrizEstado
	void llenarMatriz(int m,list<ClasePersona> poblacion);

	//EFE:
	//REQ:
	//MOD:
	void infectar(ClasePersona persona);
	//EFE:
	//REQ:
	//MOD:
	void curar(ClasePersona persona);

	//EFE:
	//REQ:
	//MOD:
	pair<int,int> generarPosRandom(int tam, list<pair<int,int>> &existentes);
private:
	vector<vector<list<int>>> matrizEstados;
	list<ClasePersona> poblacion;
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
