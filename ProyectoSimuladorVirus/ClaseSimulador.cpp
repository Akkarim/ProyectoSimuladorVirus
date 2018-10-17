#include "ClaseSimulador.h"
#include <iostream>



ClaseSimulador::ClaseSimulador()
{
}


ClaseSimulador::~ClaseSimulador()
{
}


void ClaseSimulador::llenarLista(double cantInfec, double infec, double rec, int tamano, int cantidad, ofstream& bit, char r)
{
	poblacionInfectada.resize(tamano);
	//poblacion.resize(cantidad);
	for (int i = 0; i < tamano; i++) {
		poblacionInfectada[i].resize(tamano,-1);
	}
	ClasePersona persona;
	int contador = cantidad*(cantInfec/100);//Cantidad de personas infectadas inicialmente
	int cantPorHilo = cantidad / omp_get_max_threads();
#pragma omp parallel for num_threads(omp_get_max_threads()) private(persona) shared(contador,tamano,cantidad,infec,rec)
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
				persona.setProbaInf(infec / 100);
				persona.setProbaRec(rec / 100);
				persona.setPosicion(generarPosRandom(tamano));//Asigna una posicion random, se asegura de que no sea repetida
				if(persona.getEstado()==1){ 
					poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second]=1;//Si la persona está enferma se marca en la matriz.
				}else{
					poblacionInfectada[persona.getPosicion().first][persona.getPosicion().second]=0;//Se pone un cero para mostrar que esa posición está ocupada.
				}
				poblacion.push_back(persona);
				if (r == 's') {
					//cout << "Estado: " << persona.getEstado() << " X: " << persona.getPosicion().first << "Y: " << persona.getPosicion().second << endl;
					//bit << "Estado: " << persona.getEstado() << " X: " << persona.getPosicion().first << "Y: " << persona.getPosicion().second << endl;
				}
			}
		}
}

void ClaseSimulador::mover()
{
	default_random_engine gen;
	int random;
	int distribucion = poblacion.size() / omp_get_max_threads();

#pragma omp parallel for num_threads(omp_get_max_threads()) private(random) shared(gen)
	for (int i = 0; i < poblacion.size();i++){
			if (poblacion[i].getPosicion().first == 0 && poblacion[i].getPosicion().second == 0) { //Esquina Superior Izquierda
				uniform_int_distribution<int> distribution(0, 2);
				random = distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(poblacion[i]);
				}
				else if (random == 1) {//Abajo
#pragma omp critical
					abajo(poblacion[i]);
				}
				else if (random == 2) { //Diagonal Abajo Derecha
#pragma omp critical
					diaDerAbajo(poblacion[i]);
				}
			}
			else if (poblacion[i].getPosicion().first == 0 && poblacion[i].getPosicion().second == poblacionInfectada.size() - 1) { //Esquina Superior Derecha
				uniform_int_distribution<int> distribution(0, 2);
				random = (int)distribution(gen);
				if (random == 0) {//Izquierda
#pragma omp critical
					izquierda(poblacion[i]);
				}
				else if (random == 1) {//Abajo
#pragma omp critical
					abajo(poblacion[i]);
				}
				else if (random == 2) { //Diagonal Abajo Izquierda
#pragma omp critical
					diaIzqAbajo(poblacion[i]);
				}
			}
			else if (poblacion[i].getPosicion().first == poblacionInfectada.size() - 1 && poblacion[i].getPosicion().second == 0) { //Esquina Inferior Izquierda
				uniform_int_distribution<int> distribution(0, 2);
				random = (int)distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(poblacion[i]);
				}
				else if (random == 1) {//Arriba
#pragma omp critical
					arriba(poblacion[i]);
				}
				else { //Diagonal Arriba Derecha
#pragma omp critical
					diaDerArriba(poblacion[i]);
				}
			}
			else if (poblacion[i].getPosicion().first == poblacionInfectada.size() - 1 && poblacion[i].getPosicion().second == poblacionInfectada.size() - 1) { //Esquina Inferior Derecha
				uniform_int_distribution<int> distribution(0, 2);
				random = (int)distribution(gen);
				if (random == 0) {//Izquierda
#pragma omp critical
					izquierda(poblacion[i]);
				}
				else if (random == 1) {//Arriba
#pragma omp critical
					arriba(poblacion[i]);
				}
				else if (random == 2) { //Diagonal Arriba Izquierda
#pragma omp critical
					diaIzqArriba(poblacion[i]);
				}
			}
			else if (poblacion[i].getPosicion().first == 0) { //Arriba
				uniform_int_distribution<int> distribution(0, 4);
				random = (int)distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(poblacion[i]);
				}
				else if (random == 1) {//Izquierda
#pragma omp critical
					izquierda(poblacion[i]);
				}
				else if (random == 2) {//Abajo
#pragma omp critical
					abajo(poblacion[i]);
				}
				else if (random == 3) {//Diagonal Abajo Izquierda
#pragma omp critical
					diaIzqAbajo(poblacion[i]);
				}
				else if (random == 4) {//Diagonal Abajo Derecha
#pragma omp critical
					diaDerAbajo(poblacion[i]);
				}
			}
			else if (poblacion[i].getPosicion().second == 0) { //Izquierda
				uniform_int_distribution<int> distribution(0, 4);
				random = (int)distribution(gen);
				if (random == 0) {//Derecha
#pragma omp critical
					derecha(poblacion[i]);
				}
				else if (random == 1) {//Arriba
#pragma omp critical
					arriba(poblacion[i]);
				}
				else if (random == 2) {//Abajo
#pragma omp critical
				abajo(poblacion[i]);
				}
				else if (random == 3) {//Diagonal Arriba Derecha
#pragma omp critical
				diaDerArriba(poblacion[i]);
				}
				else {//Diagonal Abajo Derecha
#pragma omp critical
				diaDerAbajo(poblacion[i]);
				}
			}
			else if (poblacion[i].getPosicion().first == poblacionInfectada.size() - 1) { //Abajo
			uniform_int_distribution<int> distribution(0, 4);
			random = (int)distribution(gen);
			if (random == 0) {//Izquierda
#pragma omp critical
				izquierda(poblacion[i]);
			}
			else if (random == 1) {//Arriba
#pragma omp critical
				arriba(poblacion[i]);
			}
			else if (random == 2) {//Derecha
#pragma omp critical
				derecha(poblacion[i]);
			}
			else if (random == 3) {//Diagonal Arriba Izquierda
#pragma omp critical
				diaIzqArriba(poblacion[i]);
			}
			else {//Diagonal Arriba Derecha
#pragma omp critical
				diaDerArriba(poblacion[i]);
			}
			}
			else if (poblacion[i].getPosicion().second == poblacionInfectada.size() - 1) { //Derecha
			uniform_int_distribution<int> distribution(0, 4);
			random = (int)distribution(gen);
			if (random == 0) {//Abajo
#pragma omp critical
				abajo(poblacion[i]);
			}
			else if (random == 1) {//Arriba
#pragma omp critical
				arriba(poblacion[i]);
			}
			else if (random == 2) {//Izquierda
#pragma omp critical
				izquierda(poblacion[i]);
			}
			else if (random == 3) {//Diagonal Abajo izquierda
#pragma omp critical
				diaIzqAbajo(poblacion[i]);
			}
			else {//Diagonal Arriba Izquierda
#pragma omp critical
				diaIzqArriba(poblacion[i]);
			}
			}
			else {
			uniform_int_distribution<int> distribution(0, 7);
			random = (int)distribution(gen);
			if (random == 0) {//Arriba
#pragma omp critical
				arriba(poblacion[i]);
			}
			else if (random == 1) {//Abajo
#pragma omp critical
				abajo(poblacion[i]);
			}
			else if (random == 2) {//Izquierda
#pragma omp critical
				izquierda(poblacion[i]);
			}
			else if (random == 3) {//Derecha
#pragma omp critical
				derecha(poblacion[i]);
			}
			else if (random == 4) {//Diagonal Abajo Derecha
#pragma omp critical
				diaDerAbajo(poblacion[i]);
			}
			else if (random == 5) {//Diagonal Abajo Izquierda
#pragma omp critical
				diaIzqAbajo(poblacion[i]);
			}
			else if (random == 6) {//Diagonal Arriba Derecha
#pragma omp critical
				diaDerArriba(poblacion[i]);
			}
			else {//Diagonal Arriba Izquierda
#pragma omp critical
				diaDerAbajo(poblacion[i]);
			}
			}/*
#pragma omp critical
			cout << "Estado: " << poblacion[i].getEstado() << " X: " << poblacion[i].getPosicion().first << "Y: " << poblacion[i].getPosicion().second << "Impreso por el hilo: " << omp_get_thread_num << endl;*/
		}
}


void ClaseSimulador::revisar(int cantSemana, ofstream& bit){ //Se muere a la semana 20
	int c = 0;
#pragma omp parallel for num_threads(4) private(c) shared(cantSemana)
	for (int i = 0; i < poblacion.size(); i++) {
		c = poblacionInfectada[poblacion[i].getPosicion().first][poblacion[i].getPosicion().second];
		if (poblacion[i].getEstado() == 0 && c > 0) { // Esta sano y hay infectaos
			while (c > 0 ) {
				if (infectar(poblacion[i])) {
					poblacion[i].setEstado(1);
					poblacion[i].modSemana(); // semana masmas
					poblacionInfectada[poblacion[i].getPosicion().first][poblacion[i].getPosicion().second] += 1;
					c = 0;
				}
				else {
					c--; //:D
				}
			}
		}
		else if(poblacion[i].getEstado() == 1){
			if (poblacion[i].getSemana() == cantSemana) { //si llegó a la cita de la caja
				if (curar(poblacion[i])) {
					poblacion[i].setEstado(2);
					poblacionInfectada[poblacion[i].getPosicion().first][poblacion[i].getPosicion().second] -= 1;
				}
				else {
					poblacion[i].setEstado(3);
					poblacionInfectada[poblacion[i].getPosicion().first][poblacion[i].getPosicion().second] -= 1;
				}
			}
			else {
				poblacion[i].modSemana();
			}
		}
	}
	int enfermos = 0;
	int sanos = 0;
	int inmunes = 0;
	int muertos = 0;
	for (int i = 0; i < poblacion.size(); i++) {
		if (poblacion[i].getEstado()==0) {
			sanos++;
		}else if(poblacion[i].getEstado() == 1){
			enfermos++;
		}else if(poblacion[i].getEstado() == 2){
			inmunes++;
		}else if (poblacion[i].getEstado() == 3) {
			muertos++;
		}
	}
	cout << "Cantidad de personas suceptibles: " << sanos << endl;
	bit << "Sanos: " << sanos << endl;
	cout << "Porcentaje de personas suceptibles: " << (sanos * 0,1) << "%" << endl;
	bit << "Porcentaje de personas suceptibles: " << (sanos * 0,1) << "%" << endl;

	cout << "Cantidad de personas enfermas: " << enfermos << endl;
	bit << "Cantidad de personas enfermas: " << enfermos << endl;
	cout << "Porcentaje de personas enfermas:" << (enfermos * 0,1) << "%" << endl;
	bit << "Porcentaje de personas enfermas:" << (enfermos*0,1) <<"%"<< endl;

	cout << "Cantidad de personas inmunes: " << inmunes << endl;
	bit << "Cantidad de personas inmunes: " << inmunes << endl;
	cout << "Porcentajes de personas inmunes: " << (inmunes*100)<< "%"<<endl;
	bit << "Porcentajes de personas inmunes: " << (inmunes * 0,1) << endl;

	cout << "Cantidad de personas muertas: " << muertos << endl;
	bit << "Cantidad de personas muertas: " << muertos << endl;
	cout << "Porcentaje de personas muertas: " << (muertos*0,1) <<"%"<< endl;
	bit << "Porcentaje de personas muertas: " << (muertos * 0,1) << "%" << endl;
}

bool ClaseSimulador::infectar(ClasePersona persona)
{
	double random = genRandom();
	if (random <= persona.probaInfectibilidad) {
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
		return true;
	}else {
		//persona.modSemana(); //semanas másmás
		return false;
	}
}

double ClaseSimulador::genRandom() {
	//default_random_engine gen(time(NULL));
	//uniform_real_distribution<double> distribution(0,1);
	//double perra = 0.0;
	//for (int i = 0; i < 4; i++) {
	//	perra = distribution(gen);
	//}
	//return perra;
	return rand() / (RAND_MAX + 1.);
}

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
	posAux.first = persona.getPosicion().first-1;
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
	posAux.first = persona.getPosicion().first+1;
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
	posAux.second = persona.getPosicion().second+1;
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
	posAux.second = persona.getPosicion().second-1;
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
