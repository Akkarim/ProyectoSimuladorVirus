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
	bool rev = true; //Esta variable es para revison de errores

	double probaInfeccion, probaRecuperacion, cantPersonasInfectadas;
	int cantSemanas, tics, tamMatriz, cantPersonas;
	char r;
	do {
		cout << "Ingrese la Cantidad de Personas: " << endl;
		cin >> cantPersonas;
		if (cantPersonas < 50) {
			cout << "La cantidad de personas debe ser igual o mayor a 50" << endl;
			rev = false;
		}
		cout << "Pontencia Infecciosa: " << endl;
		cin >> probaInfeccion;
		if (probaInfeccion<1||probaInfeccion>100) {
			cout << "La probabilidad debe ser entre 1 y 100" << endl;
			rev = false;
		}
		cout << "Probabilidad de Recuperacion: " << endl;
		cin >> probaRecuperacion;
		if (probaRecuperacion<1 || probaRecuperacion>100) {
			cout << "La probabilidad debe ser entre 1 y 100" << endl;
			rev = false;
		}
		cout << "Semanas antes de morir o sanar: " << endl;
		cin >> cantSemanas;
		if (cantSemanas<1) {
			cout<<"La cantidad de semanas debe ser mayor a uno"<<endl;
			rev = false;
		}
		cout << "Porcentage de personas originalmente infectadas: " << endl;
		cin >> cantPersonasInfectadas;
		if (cantPersonasInfectadas<1 || cantPersonasInfectadas>100) {
			cout << "El porcentaje debe ser entre 1 y 100" << endl;
			rev = false;
		}
		int c;
		cout << "Ingrese el tamano de la Matriz de infeccion: \n1) 100x100\n2)500x500\n3)1000x1000\n4)35x35(datos prueba)" << endl; //intentar iterar esto
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
		case 4:
			tamMatriz = 35;
			break;
		default:
			cout << "Error \n Por favor ingrese un numero valido. " << endl;
			rev = false;
		}
		
		cout << "Cantidad de tics: " << endl;
		cin >> tics;
		if (tics < cantSemanas) {
			cout<<"La cantidad de tics debe ser mayor al limite de semanas"<<endl;
			rev = false;
		}
		cout << "¿Desea ver la disposicion de la matriz? (s/n) " << endl;
		cin >> r;

	} while (!rev);
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
	
	simulador.inicializar(cantPersonasInfectadas, probaInfeccion, probaRecuperacion, tamMatriz, cantPersonas, bit, r);

	
	
	bit << "-----------------Datos de los TICS-------------------  " << endl;
	simulador.ejecutar(tics, cantSemanas, bit, r);

	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Tiempo Total de Ejecución: " << time << endl;
	bit << "Tiempo Total de Ejecución: " << time << endl;

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
