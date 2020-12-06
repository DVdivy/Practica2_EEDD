#pragma once
#include "Nodo.h"
class Cola
{
private:
	Nodo* primero;
	Nodo* ultimo;
public:
	Cola();
	~Cola();
	void encolar(Pedido* p);
	void desencolar();
	Pedido* prim();
	bool es_vacia();
	void mostrar_cola();
};

