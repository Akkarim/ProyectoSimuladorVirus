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
	//EFE: Genera una matriz con los estados de cada persona
	//REQ: Un M coherente con la cantidad de personas
	//MOD: matrizEstado
	void llenarMatriz(int m,list<ClasePersona> poblacion);
	//EFE:
	//REQ:
	//MOD:
	void infectar(ClasePersona persona);
private:
	vector<vector<list<int>>> matrizEstados;

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
