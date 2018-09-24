#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <omp.h>
#include "ClasePersona.h"
using namespace std;

#define _CRT_SECURE_NO_WARNINGS 1 // para deshabilitar errores por uso de funciones deprecated sobre CRT o consola
#pragma warning(disable : 4996)

ClasePersona persona;

int main(int argc, char* argv[]) {
	double inf, rec;
	cout << "Inserte la probabilidad de Infección: "<< endl;
	cin >> inf;
	cout << "Inserte la proba de Recuperación: " << endl;
	cin >> rec;

	persona.setProbaInf(inf);
	persona.setProbaRec(rec);

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
