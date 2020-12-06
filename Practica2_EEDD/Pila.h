#pragma once
#include "Nodo.h"
class Pila {
private:
	Nodo* primero;
public:
	Pila();
	~Pila();
	void apilar(Pedido* p);
	void ordenar_pila();
	void desapilar();
	Pedido* cima();
	bool es_vacia();
	void mostrar_pila();
};
