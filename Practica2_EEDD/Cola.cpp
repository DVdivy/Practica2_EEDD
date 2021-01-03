#include "Cola.h"
Cola::Cola() {
	primero = nullptr;
	ultimo = nullptr;
}

Cola::~Cola() {
	while (!es_vacia())
	{
		desencolar();
	}
}

void Cola::encolar(Pedido* p) {
	Nodo* aux = new Nodo();
	aux->pedido = p;
	if(!es_vacia())
		ultimo->sig = aux;
	aux->sig = nullptr;
	ultimo = aux;
	if (primero == nullptr)
		primero = aux;
}

void Cola::desencolar() {
	if (!es_vacia()) {
		Nodo* aux = new Nodo();
		aux = primero;
		primero = aux->sig;
		aux->sig = nullptr;
		delete(aux);
		if (es_vacia())
			ultimo = nullptr;
	}
	else
		cout << "La cola esta vacia. No se puede eliminar" << endl;
}

Pedido* Cola::prim() {
	if (!es_vacia()) {
		return primero->pedido;
	}
	else
		return NULL;
}

bool Cola::es_vacia() {
	return primero == nullptr;
}

void Cola::mostrar_desc_cola(){
    if (es_vacia())
		cout << endl << "La cola esta vacia. No se puede mostrar" << endl;
	else {
		int c = 1;
		Nodo* p = new Nodo();
		p = primero;
		while (p != nullptr) {
			cout << endl << "Pedido "<< c << ": " << p->pedido->get_descripcion_articulo();
			p = p->sig;
			c++;
		}
		cout << endl;
	}
}

void Cola::mostrar_cola(){
	if (es_vacia())
		cout << endl << "La cola esta vacia. No se puede mostrar" << endl;
	else {
		int c = 1;
		Nodo* p = new Nodo();
		p = primero;
		while (p != nullptr) {
			cout << endl << endl << "Pedido "<< c << ": " << p->pedido->mostrar_pedido();
			p = p->sig;
			c++;
		}
		cout << endl;
	}
}
