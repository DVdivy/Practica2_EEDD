#include "Nodo.h"
Nodo::Nodo() {
	pedido = NULL;
	sig = nullptr;
}

Nodo::~Nodo() {
	delete sig;
}