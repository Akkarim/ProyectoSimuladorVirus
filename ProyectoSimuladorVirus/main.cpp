#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <ctime>
#include "ClasePersona.h"
#include "ClaseSimulador.h"
using namespace std;

#define _CRT_SECURE_NO_WARNINGS 1 // para deshabilitar errores por uso de funciones deprecated sobre CRT o consola
#pragma warning(disable : 4996)
#pragma warning(disable : 4199)


ClasePersona persona;
ClaseSimulador simulador;

int main(int argc, char* argv[]) {

	double probaInfeccion, probaRecuperacion, cantPersonasInfectadas;
	int cantSemanas, tics, tamMatriz, cantPersonas;

	cout << "Ingrese la Cantidad de Personas: " << endl;
	cin >> cantPersonas;

	cout << "Pontencia Infecciosa: " << endl;
	cin >> probaInfeccion;

	cout << "Probabilidad de Recuperacion: " << endl;
	cin >> probaRecuperacion;

	cout << "Semanas antes de morir o sanar: " << endl;
	cin >> cantSemanas;

	cout << "Porcentage de personas originalmente infectadas: " << endl;
	cin >> cantPersonasInfectadas;

	int c;
	do {
		cout << "Ingrese el tamano de la Matriz de infeccion: \n1) 100x100\n2)500x500\n3)1000x1000" << endl; //intentar iterar esto
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
			cout << "Error \n Por favor ingrese un numero valido. " << endl;
		}
	} while (c > 3);
	cout << "Cantidad de tics: " << endl;
	cin >> tics;

	char r;
	cout << "¿Desea ver la disposicion de la matriz? (s/n) " << endl;
	cin >> r;

	int cantHilos = omp_get_max_threads();

	ofstream bit("bitacora.txt");

	bit << "FELIPE CARMONA B51558 & LUIS CARVAJAL B31494\nDatos iniciales:\n- Cantidad de Personas: " << cantPersonas <<
		"\n- Probabilidad de infección: " << probaInfeccion << "%" << "\n- Probabilidad de Recuperación: " << probaRecuperacion << "%" <<
		"\n - Semanas: " << cantSemanas << "\n- Porcentaje de personas originalmente infectadas: " << cantPersonasInfectadas <<"%"<<
		"\n - Cantidad de personas originalmente infectadas: "<<cantPersonas*(cantPersonasInfectadas/100)<<
		"\n- Tamaño de la Matriz (cuadrada): " << tamMatriz << "\n- Cantidad de tics: " << tics << "\n- Cantidad de Hilos: " << cantHilos << endl;
	
	if (r == 's') {
		bit << "-----------------Datos de la Matriz-------------------  " << endl;
	}
	unsigned t0, t1;
	t0 = clock();
	
	simulador.llenarLista(cantPersonasInfectadas, probaInfeccion, probaRecuperacion, tamMatriz, cantPersonas, bit, r);

	
	
	bit << "-----------------Datos de los TICS-------------------  " << endl;
	
	for (int i = 0; i < tics; i++) {
		simulador.mover();
		cout << "-------------------------------------------------" << endl;
		bit << "-------------------------------------------------" << endl;
		cout << "Tic: " << i << endl;
		bit << "Tic: " << i << endl;
		simulador.revisar(cantSemanas, bit, r);
	}

	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;

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
