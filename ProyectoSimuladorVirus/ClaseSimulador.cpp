#include "ClaseSimulador.h"
#include <iostream>




ClaseSimulador::ClaseSimulador()
{
}


ClaseSimulador::~ClaseSimulador()
{
}


void ClaseSimulador::llenarMatriz(double cantInfec, double infec, double rec, int tamano, int cantidad)
{
	poblacion.resize(tamano);

	for (int i = 0; i < tamano; i++) {
		poblacion[i].resize(tamano);
	}
	list<pair<int, int>> posiciones;

	ClasePersona persona;
#pragma omp parallel num_threads(omp_get_max_threads()) private(persona) shared(infec,rec,tamano,cantidad)
	{

		int contador = cantidad * (cantInfec / 100);//Cantidad de personas infectadas inicialmente
		persona.setProbaInf(infec);
		persona.setProbaRec(rec);//Como todas son iguales al inicio, esto entra directo.

		for (int i = 0; i < cantidad; i++) {
			if (contador > 0) {
				persona.setEstado(1);
				contador--;
			}
			else {
				persona.setEstado(0);
			}
#pragma omp critical 
			{
				persona.setPosicion(generarPosRandom(tamano));//Asigna una posicion random, se asegura de que no sea repetida
				poblacion[persona.getPosicion().first][persona.getPosicion().second].push_back(persona);
				cout << "Estado: " << persona.getEstado() << " X: " << persona.getPosicion().first << "Y: " << persona.getPosicion().second << endl;
			}
		}
	}
}

void ClaseSimulador::mover()
{

}

void ClaseSimulador::infectar(ClasePersona persona)
{
}

void ClaseSimulador::curar(ClasePersona persona)
{
}

pair<int, int> ClaseSimulador::generarPosRandom(int tam)
{
	pair<int, int> pos;
	default_random_engine gen;
	uniform_int_distribution<int> distribution(0, tam-1);
	do {
		pos.first = distribution(gen);
		pos.second = distribution(gen);
	} while (!poblacion[pos.first][pos.second].empty());
	
	return pos;
}

//End of file with a Cow (Bettsy)
//                               __.----.___
//   ||            ||  (\(__)/)-'||      ;--` ||
//  _||____________||___`(QQ)'___||______;____||_
//  -||------------||----)  (----||-----------||-
//  _||____________||___(o  o)___||______;____||_
//  -||------------||----`--'----||-----------||-
//   ||            ||       `|| ||| || ||     ||jgs
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
