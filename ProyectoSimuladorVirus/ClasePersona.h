#pragma once
#include <utility>
using namespace std;

class ClasePersona
{
public:
	double probaInfectibilidad;
	double probaRecuperacion;
	int estado;
	pair<int, int> posicion;

	ClasePersona();
	~ClasePersona();

	//EFE: Set de recuperación e infección
	void setProbaInf(double inf);
	void setProbaRec(double rec);
	/*
	0-Sano
	1-Enfermo
	2-Inmune
	3-did
	*/
	void setEstado(int status);
	int getEstado();

	//EFE: Retorna posicion
	void setPosicion(pair<int, int>);
	pair<int, int> getPosicion();

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
