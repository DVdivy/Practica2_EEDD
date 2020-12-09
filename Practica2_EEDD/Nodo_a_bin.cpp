#include "Nodo_a_bin.h"
#include "ABB.h"
Nodo_a_bin::Nodo_a_bin() {
	//pedido = NULL;
	num = NULL;
	arbol_izquierdo = new ABB();
	arbol_derecho = new ABB();
}

Nodo_a_bin::~Nodo_a_bin() {
	delete arbol_derecho;
	delete arbol_izquierdo;
}
