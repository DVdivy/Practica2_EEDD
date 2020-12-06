#pragma once
#include <stdlib.h>
#include <iostream>
#include "Pedido.h"
using namespace std;
class Nodo {
private:
	Pedido* pedido;
	Nodo* sig;
public:
	Nodo();
	~Nodo();
	friend class Pila;
	friend class Cola;
	friend class Lista;
};