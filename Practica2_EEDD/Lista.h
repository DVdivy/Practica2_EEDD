#pragma once
#include "Nodo.h"
class Lista
{
private:
	Nodo* primero;
	Nodo* ultimo;
	int longitud;
public:
	Lista();
	~Lista();
	void add_izq(Pedido* p);
	void add_der(Pedido* p);
	void resto();
	void eult();
	Pedido* prim();
	Pedido* ult();
	bool es_vacia();
	void mostrar_lista();
};

