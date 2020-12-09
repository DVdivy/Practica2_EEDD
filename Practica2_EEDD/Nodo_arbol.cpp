#include "Nodo_arbol.h"
Nodo::Nodo() {
	pedido = NULL;
	izq = nullptr;
	der = nullptr;
}

Nodo::~Nodo() {
	delete izq;
	delete der;
}
