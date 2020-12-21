#include "Nodo_a_bin.h"
#include "ABB.h"
Nodo_a_bin::Nodo_a_bin() {
	//pedido = NULL;
	nombre = "";
	tarjeta = "";
	lista_pedidos = new Lista();
	arbol_izquierdo = new ABB();
	arbol_derecho = new ABB();
}

Nodo_a_bin::~Nodo_a_bin() {
    delete lista_pedidos;
	delete arbol_derecho;
	delete arbol_izquierdo;
}
