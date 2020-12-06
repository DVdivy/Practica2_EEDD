#include "Lista.h"

Lista::Lista()
{
	primero = nullptr;
	ultimo = nullptr;
	longitud = 0;
}

Lista::~Lista()
{
	while (!es_vacia()) {
		resto();
	}
}

void Lista::add_izq(Pedido* p)
{
	Nodo* aux = new Nodo();
	aux->pedido = p;
	aux->sig = primero;
	primero = aux;
	if (ultimo == nullptr)
		ultimo = aux;
	longitud++;
}

void Lista::add_der(Pedido* p)
{
	Nodo* aux = new Nodo();
	aux->pedido = p;
	if (!es_vacia())
		ultimo->sig = aux;
	aux->sig = nullptr;
	ultimo = aux;
	if (primero == nullptr)
		primero = aux;
	longitud++;
}

void Lista::resto()
{
	if (es_vacia()) {
		cout << "La lista esta vacia. No se puede eliminar" << endl;
	}
	else {
		Nodo* aux = new Nodo();
		aux = primero;
		primero = aux->sig;
		aux->sig = nullptr;
		delete(aux);
		if (es_vacia())
			ultimo = nullptr;
		longitud--;
	}
}

void Lista::eult()
{
	if (es_vacia()) {
		cout << "La lista esta vacia. No se puede eliminar" << endl;
	}
	else {
		Nodo* p = new Nodo();
		Nodo* aux = new Nodo();
		p = primero;
		if (p->sig == nullptr) {
			primero = nullptr;
			ultimo = nullptr;
			delete(p);
		}
		else {
			while (p->sig->sig != nullptr)
				p = p->sig;
			aux = p->sig;
			ultimo = p;
			p->sig = nullptr;
			delete(aux);
		}
		longitud--;
	}
}

Pedido* Lista::prim()
{
	if (!es_vacia())
		return primero->pedido;
	else
		return NULL;
}

Pedido* Lista::ult()
{
	if (!es_vacia())
		return ultimo->pedido;
	else
		return NULL;
}

bool Lista::es_vacia()
{
	return longitud == 0;
}

void Lista::mostrar_lista()
{
	if (es_vacia())
		cout << endl << "La lista esta vacia, no se puede mostrar" << endl;
	else {
		int c = 1;
		Nodo* p = new Nodo();
		p = primero;
		while (p != nullptr) {
			cout << endl << endl <<"Pedido " << c << ": " << p->pedido->mostrar_pedido();
			p = p->sig;
			c++;
		}
		cout << endl;
	}
}
