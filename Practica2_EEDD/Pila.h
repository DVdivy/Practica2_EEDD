#pragma once
#include "Nodo.h"
class Pila {
private:
	Nodo* primero;
public:
	Pila();
	~Pila();
	void apilar(Pedido* p);
	void apilar_prioridad(Pedido* p);
	void desapilar();
	Pedido* cima();
	bool es_vacia();
	void mostrar_desc_pila();
	void mostrar_pila();
};
