#include "ClaseSimulador.h"



ClaseSimulador::ClaseSimulador()
{
}


ClaseSimulador::~ClaseSimulador()
{
}

void ClaseSimulador::llenarListaPersonas(double infec, double rec, int estado, int tamano, int cantidad)
{
	list<pair<int, int>> posiciones;
	ClasePersona persona;
	persona.setEstado(estado);
	persona.setProbaInf(infec);
	persona.setProbaRec(rec);//Como todas son iguales al inicio, esto entra directo.
	for (int i = 0; i < cantidad; i++) {
		persona.setPosicion(generarPosRandom(tamano,posiciones));//Asigna una posicion random, se asegura de que no sea repetida
		poblacion.push_back(persona);
	}
}

void ClaseSimulador::llenarMatriz(int m, list<ClasePersona> poblacion)
{

}

void ClaseSimulador::infectar(ClasePersona persona)
{
}

void ClaseSimulador::curar(ClasePersona persona)
{
}

pair<int, int> ClaseSimulador::generarPosRandom(int tam, list<pair<int, int>> &existentes)
{
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
