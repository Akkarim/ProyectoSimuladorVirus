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
	poblacionInfectada.resize(tamano);
	for (int i = 0; i < tamano; i++) {
		poblacionInfectada[i].resize(tamano);
		for (int j = 0; j < tamano; j++) {
				poblacionInfectada[i][j] = -1;
		}
	}
	ClasePersona persona;
	int contador = cantidad * (cantInfec / 100);//Cantidad de personas infectadas inicialmente
	int cantPorHilo = cantidad / omp_get_max_threads();
#pragma omp parallel num_threads(omp_get_max_threads()) private(persona) shared(contador,tamano,cantidad)
	{
		persona.setProbaInf(infec);
		persona.setProbaRec(rec);//Como todas son iguales al inicio, esto entra directo.
		for (int i = 0; i < cantPorHilo; i++) {
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
				if(persona.getEstado()==1){ 
					poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second]=1;//Si la persona está enferma se marca en la matriz.
				}else{
					poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second]=0;//Se pone un cero para mostrar que esa posición está ocupada.
				}
				poblacion.push_back(persona);
				cout << "Estado: " << persona.getEstado() << " X: " << persona.getPosicion().first << "Y: " << persona.getPosicion().second << endl;
			}
		}
	}
}

void ClaseSimulador::mover()
{
	default_random_engine gen;
	int random;
	list<ClasePersona> miLista;
	int distribucion = poblacion.size() / omp_get_max_threads();
	list<ClasePersona>::iterator personaAsignada = poblacion.begin();
#pragma omp parallel num_threads(omp_get_max_threads()) private(random,miLista) shared(gen,personaAsignada,distribucion)
	{
	
#pragma omp critical
		{
			for (int i = 0; i < distribucion;i++) {
				miLista.push_back(*personaAsignada);
				personaAsignada++;
			}
		}

		for (list<ClasePersona>::iterator it = miLista.begin(); it != miLista.end(); it++) {
			if (it->getPosicion().first == 0 && it->getPosicion().second == 0) { //Esquina Superior Izquierda
				uniform_int_distribution<int> distribution(0, 3);
				random = distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(*it);
				}
				else if (random == 1) {//Abajo
#pragma omp critical
					abajo(*it);
				}
				else { //Diagonal Abajo Derecha
#pragma omp critical
					diaDerAbajo(*it);
				}
			}
			else if (it->getPosicion().first == 0 && it->getPosicion().second == poblacionInfectada.size() - 1) { //Esquina Superior Derecha
				uniform_int_distribution<int> distribution(0, 3);
				random = (int)distribution(gen);
				if (random == 0) {//Izquierda
#pragma omp critical
					izquierda(*it);
				}
				else if (random == 1) {//Abajo
#pragma omp critical
					abajo(*it);
				}
				else { //Diagonal Abajo Izquierda
#pragma omp critical
					diaIzqAbajo(*it);
				}
			}
			else if (it->getPosicion().first == poblacionInfectada.size() - 1 && it->getPosicion().second == 0) { //Esquina Inferior Izquierda
				uniform_int_distribution<int> distribution(0, 3);
				random = (int)distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(*it);
				}
				else if (random == 1) {//Arriba
#pragma omp critical
					arriba(*it);
				}
				else { //Diagonal Arriba Derecha
#pragma omp critical
					diaDerArriba(*it);
				}
			}
			else if (it->getPosicion().first == poblacionInfectada.size() - 1 && it->getPosicion().second == poblacionInfectada.size() - 1) { //Esquina Inferior Derecha
				uniform_int_distribution<int> distribution(0, 3);
				random = (int)distribution(gen);
				if (random == 0) {//Izquierda
#pragma omp critical
					izquierda(*it);
				}
				else if (random == 1) {//Arriba
#pragma omp critical
					arriba(*it);
				}
				else { //Diagonal Arriba Izquierda
#pragma omp critical
					diaIzqArriba(*it);
				}
			}
			else if (it->getPosicion().first == 0) { //Izquierda
				uniform_int_distribution<int> distribution(0, 5);
				random = (int)distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(*it);
				}
				else if (random == 1) {//Arriba
#pragma omp critical
					arriba(*it);
				}
				else if (random == 2) {//Abajo
#pragma omp critical
					abajo(*it);
				}
				else if (random == 3) {//Diagonal Arriba Derecha
#pragma omp critical
					diaDerArriba(*it);
				}
				else {//Diagonal Abajo Derecha
#pragma omp critical
					diaDerAbajo(*it);
				}
			}
			else if (it->getPosicion().second == 0) { //Arriba
				uniform_int_distribution<int> distribution(0, 5);
				random = (int)distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(*it);
				}
				else if (random == 1) {//Izquierda
#pragma omp critical
					izquierda(*it);
				}
				else if (random == 2) {//Abajo
#pragma omp critical
				abajo(*it);
				}
				else if (random == 3) {//Diagonal Abajo Izquierda
#pragma omp critical
				diaIzqAbajo(*it);
				}
				else {//Diagonal Abajo Derecha
#pragma omp critical
				diaDerAbajo(*it);
				}
			}
			else if (it->getPosicion().first == poblacionInfectada.size() - 1) { //Derecha
			uniform_int_distribution<int> distribution(0, 5);
			random = (int)distribution(gen);
			if (random == 0) {//Izquierda
#pragma omp critical
				izquierda(*it);
			}
			else if (random == 1) {//Arriba
#pragma omp critical
				arriba(*it);
			}
			else if (random == 2) {//Abajo
#pragma omp critical
				abajo(*it);
			}
			else if (random == 3) {//Diagonal Arriba Izquierda
#pragma omp critical
				diaIzqArriba(*it);
			}
			else {//Diagonal Abajo Izquierda
#pragma omp critical
				diaIzqAbajo(*it);
			}
			}
			else if (it->getPosicion().second == poblacionInfectada.size() - 1) { //Abajo
			uniform_int_distribution<int> distribution(0, 5);
			random = (int)distribution(gen);
			if (random == 0) {//Derecha
#pragma omp critical
				derecha(*it);
			}
			else if (random == 1) {//Arriba
#pragma omp critical
				arriba(*it);
			}
			else if (random == 2) {//Izquierda
#pragma omp critical
				izquierda(*it);
			}
			else if (random == 3) {//Diagonal Arriba Derecha
#pragma omp critical
				diaDerArriba(*it);
			}
			else {//Diagonal Arriba Izquierda
#pragma omp critical
				diaDerAbajo(*it);
			}
			}
			else {
			uniform_int_distribution<int> distribution(0, 8);
			random = (int)distribution(gen);
			if (random == 0) {//Arriba
#pragma omp critical
				arriba(*it);
			}
			else if (random == 1) {//Abajo
#pragma omp critical
				abajo(*it);
			}
			else if (random == 2) {//Izquierda
#pragma omp critical
				izquierda(*it);
			}
			else if (random == 3) {//Derecha
#pragma omp critical
				derecha(*it);
			}
			else if (random == 4) {//Diagonal Abajo Derecha
#pragma omp critical
				diaDerAbajo(*it);
			}
			else if (random == 5) {//Diagonal Abajo Izquierda
#pragma omp critical
				diaIzqAbajo(*it);
			}
			else if (random == 6) {//Diagonal Arriba Derecha
#pragma omp critical
				diaDerArriba(*it);
			}
			else {//Diagonal Arriba Izquierda
#pragma omp critical
				diaDerAbajo(*it);
			}
			}
		}

#pragma omp single
		cout << "Estos son despues de mover: " << endl;

		for (list<ClasePersona>::iterator it = miLista.begin(); it != miLista.end(); it++) {
#pragma omp critical
			cout << "Estado: " << it->getEstado() << " X: " << it->getPosicion().first << "Y: " << it->getPosicion().second << "Impreso por el hilo: "<<omp_get_thread_num<<endl;
		}
	}

}

void ClaseSimulador::revisar(int contSem){
	//int est;
	//for(list<ClasePersona>::iterator it = poblacion[i][j].begin(); it != poblacion[i][j].end(); it++){
	//	est = it->getEstado();
	//	if(est==1){
	//		if(it->semana<contSem){
	//			curar(*it);
	//		}else{
	//			it->setEstado(2);
	//			poblacionInfectada[it->getPosicion().first][it->getPosicion().second] -= 1;
	//		}
	//	}else if(est==0){
	//		for(int i=0; i<poblacionInfectada[it->getPosicion().first][it->getPosicion().second]; i++){
	//			if(infectar(*it)){
	//				i = poblacionInfectada[it->getPosicion().first][it->getPosicion().second];
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
		persona.modSemana();
		poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1; 
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
		poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] -= 1;
		return true;
	}else {
		persona.modSemana();
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

pair<int, int> ClaseSimulador::generarPosRandom(int tam)
{
	pair<int, int> pos;
	default_random_engine gen;
	uniform_int_distribution<int> distribution(0, tam-1);
	do {
		pos.first = distribution(gen);
		pos.second = distribution(gen);
	} while (poblacionInfectada[pos.first][pos.second]==0||poblacionInfectada[pos.first][pos.second]==1);
	
	return pos;
}

void ClaseSimulador::arriba(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first + 1;
	posAux.second = persona.getPosicion().second;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::abajo(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first - 1;
	posAux.second = persona.getPosicion().second;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::derecha(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first;
	posAux.second = persona.getPosicion().second + 1;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::izquierda(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first;
	posAux.second = persona.getPosicion().second - 1;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::diaDerAbajo(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first + 1;
	posAux.second = persona.getPosicion().second - 1;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::diaDerArriba(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first - 1;
	posAux.second = persona.getPosicion().second + 1;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::diaIzqAbajo(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first + 1;
	posAux.second = persona.getPosicion().second + 1;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
}

void ClaseSimulador::diaIzqArriba(ClasePersona &persona){
	posAnt = persona.getPosicion();
	posAux.first = persona.getPosicion().first - 1;
	posAux.second = persona.getPosicion().second - 1;
	persona.setPosicion(posAux);
	if (persona.getEstado() == 1) {
		if (poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] == -1) {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] = 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
		else {
			poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second] += 1;
			poblacionInfectada[posAnt.first][posAnt.second] -= 1;
		}
	}
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
