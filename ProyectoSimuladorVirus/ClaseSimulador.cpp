#include "ClaseSimulador.h"
#include <iostream>




ClaseSimulador::ClaseSimulador()
{
}


ClaseSimulador::~ClaseSimulador()
{
}


void ClaseSimulador::llenarLista(double cantInfec, double infec, double rec, int tamano, int cantidad)
{
	poblacion.resize(tamano);

	for (int i = 0; i < tamano; i++) {
		poblacionInfectada[i].resize(tamano);
		for (int j = 0; j < tamano; j++) {
			poblacionInfectada[i][j] = 0;
		}
	}
	//list<pair<int, int>> posiciones;
	ClasePersona persona;
	persona.setProbaInf(infec);
	persona.setProbaRec(rec);//Como todas son iguales al inicio, esto entra directo.
	int contador = cantidad * (cantInfec / 100);//Cantidad de personas infectadas inicialmente
#pragma omp parallel num_threads(omp_get_max_threads()) private(persona) shared(contador,tamano,cantidad,posiciones)
	{
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
				//persona.setPosicion(generarPosRandom(tamano,posiciones));//Asigna una posicion random, se asegura de que no sea repetida
				poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = persona.getEstado();
				poblacion.push_back(persona);
				//cout << "Estado: " << persona.getEstado() << " X: " << persona.getPosicion().first << "Y: " << persona.getPosicion().second << endl;
			}
		}
	}
}

void ClaseSimulador::mover(int contSem)
{
	//int cont = 0; // Privado
	//int cantInfectados; //  privado
	//for (int i = 0; i < poblacion.size(); i++) { // nested for 
	//	for (int j = 0; j < poblacion.size(); j++) {
	//		if (!poblacion[i][j].empty()) { // si no está vacía se la mete
	//			if (poblacion[i][j].size() > 1) { // si hay más de uno en esa pos
	//				cont = 0;
	//				cantInfectados = contInfectados(poblacion[i][j]);
	//				while (cont < poblacion[i][j].size()) {
	//					for (list<ClasePersona>::iterator it = poblacion[i][j].begin(); it != poblacion[i][j].end(); it++) {
	//						if (it->getEstado() == 0) {
	//							for (int x = 0; x < cantInfectados; x++) { //
	//								if (infectar(*it)) {
	//									x = cantInfectados;
	//									it->modSemana();
	//								}
	//							}
	//						}
	//					}
	//				}
	//			}
	//			else { // Si hay solo uno
	//				if (poblacion[i][j].front().getEstado() == 1) { // Si esta enfermo
	//					if (poblacion[i][j].front().getSemana() == contSem) { // Y tiene el lim de semanas
	//						poblacion[i][j].front().setEstado(3);//se muere we
	//					}else {
	//						if (!curar(poblacion[i][j].front())) { // si no se cura
	//							poblacion[i][j].front().modSemana(); // Aumenta la semana de la persona
	//						}
	//					} 
	//				}
	//			}
	//		}
	//	}
	//}
}

bool ClaseSimulador::infectar(ClasePersona persona)
{
	double random = genRandom();
	if (random <= persona.probaInfectibilidad) {
		persona.setEstado(1);
		return true;
	}
	else {
		return false;
	}
}

bool ClaseSimulador::curar(ClasePersona persona)
{
	double random = genRandom();
	if (random <= persona.probaRecuperacion) {
		persona.setEstado(2);
		return true;
	}
	else {
		return false;
	}
}


double ClaseSimulador::genRandom() {
	default_random_engine gen;
	uniform_real_distribution<double> distribution(0,1);
	return distribution(gen);
}

int ClaseSimulador::contInfectados(list<ClasePersona> lista)
{
	int c = 0;
	for (list<ClasePersona>::iterator it = lista.begin(); it != lista.end(); it++) {
		if (it->estado == 1) {
			c++;
		}
	}
	return c;
}

/*int myints[] = {75,23,65,42,13};
  std::list<int> mylist (myints,myints+5);

  std::cout << "mylist contains:";
  for (std::list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';

  return 0;*/

pair<int, int> ClaseSimulador::generarPosRandom(int tam, list<pair<int,int>> repetidas)
{
	pair<int, int> pos;
	default_random_engine gen;
	uniform_int_distribution<int> distribution(0, tam-1);
	do {
		pos.first = distribution(gen);
		pos.second = distribution(gen);
	} while (true);
	
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
