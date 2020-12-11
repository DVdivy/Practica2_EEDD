#pragma once
#include <stdlib.h>
#include <iostream>
#include "Pedido.h"
using namespace std;
class Nodo_arbol {
private:
	Pedido* pedido;
	Nodo_arbol* izq;
	Nodo_arbol* der;
public:
	Nodo_arbol();
	~Nodo_arbol();

	friend class ABB;
};
