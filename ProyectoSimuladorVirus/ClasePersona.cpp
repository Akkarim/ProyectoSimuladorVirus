#include "ClasePersona.h"

ClasePersona::ClasePersona()
{
}
ClasePersona::~ClasePersona()
{
}

void ClasePersona::setEstado(int status) {
	this->estado = status;
}

int ClasePersona::getEstado() {
	return this->estado;
}

void ClasePersona::setPosicion(pair<int, int> pos) {
	this->posicion = pos;
}

pair<int, int> ClasePersona::getPosicion() {
	return this->posicion;
}

void ClasePersona::setProbaInf(double inf){
	this->probaInfectibilidad = inf;
}

void ClasePersona::setProbaRec(double rec) {
	this->probaRecuperacion = rec;
}

void ClasePersona::setSemana(int sem) {
	this->semana = sem;
}
int ClasePersona::getSemana() {
	return this->semana;
}

void ClasePersona::modSemana() {
	if (this->semana < 0) {
		this->semana = 1;
	}
	else {
		this->semana++;
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
