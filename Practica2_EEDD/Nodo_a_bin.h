#pragma once
#include <stdlib.h>
#include <iostream>
#include "Pedido.h"
using namespace std;

class ABB;

class Nodo_a_bin {
private:
	//Pedido* pedido;
	int num;
	ABB* arbol_izquierdo;
	ABB* arbol_derecho;
public:
	Nodo_a_bin();
	~Nodo_a_bin();
	friend class ABB;
};
