#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <omp.h>
#include "ClasePersona.h"
#include "ClaseSimulador.h"
using namespace std;

#define _CRT_SECURE_NO_WARNINGS 1 // para deshabilitar errores por uso de funciones deprecated sobre CRT o consola
#pragma warning(disable : 4996)

ClasePersona persona;
ClaseSimulador simulador;
int main(int argc, char* argv[]) {

	double probaInfeccion, probaRecuperacion, cantPersonasInfectadas;
	int cantSemanas, tics, tamMatriz, cantPersonas;

	cout << "Ingrese la Cantidad de personas: " << endl;
	cin >> cantPersonas;

	cout << "Pontencia Infecciosa: " << endl;
	cin >> probaInfeccion;

	cout << "Probabilidad de Recuperacion: " << endl;
	cin >> probaRecuperacion;

	cout << "Semanas antes de morir we: " << endl;
	cin >> cantSemanas;

	cout << "Porcentage de personas originalmente infectdas: " << endl;
	cin >> cantPersonasInfectadas;

	cout << "Ingrese el tamano de la Matriz de infeccion: \n1) 100x100\n2)500x500\n3)1000x1000" << endl;
	int c;
	cin >> c;
	switch (c) {
	case 1:
		tamMatriz = 100;
		break;
	case 2:
		tamMatriz = 500;
		break;
	case 3:
		tamMatriz = 1000;
		break;
	default:
		cout << "Vea Yogurt, métame un número válido. " << endl;
	}

	cout << "Cantidad de tics: " << endl;
	cin >> tics;

	int cantHilos = omp_get_max_threads();

	cout << "Se va a trabajar con " << cantHilos << "hilos" << endl;

	simulador.llenarLista(cantPersonasInfectadas, probaInfeccion, probaRecuperacion, tamMatriz, cantPersonas);
	
	for (int i = 0; i < tics; i++) {
		cout << "Tic: " << i << endl;
		simulador.mover();
		cout << "-------------------------------------------------" << endl;
		simulador.revisar(cantSemanas);
	}



	int x;
	cin >> x;
	return 0;
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
