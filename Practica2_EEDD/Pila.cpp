#include "Pila.h"
#include <iostream>
#include <stdio.h>
using namespace std;
Pila::Pila() {
	primero = nullptr;
}

Pila::~Pila()
{
	while (!es_vacia()) {
		desapilar();
	}
}

void Pila::apilar(Pedido* p)
{
	Nodo* aux = new Nodo();
	aux->pedido = p;
	aux->sig = primero;
	primero = aux;
}

void Pila::ordenar_pila()
{
    Pila* registrados= new Pila();
    Pila* no_registrados= new Pila();
    while (!es_vacia()){
        if (cima()->get_tipo_cliente()==NR){
            no_registrados->apilar(cima());
            desapilar();
        }
        else{
            registrados->apilar(cima());
            desapilar();
        }
    }
    while (!no_registrados->es_vacia()){
        apilar(no_registrados->cima());
        no_registrados->desapilar();
    }
    while (!registrados->es_vacia()){
        apilar(registrados->cima());
        registrados->desapilar();
    }
}

void Pila::desapilar()
{
	if (!es_vacia()) {
		Nodo* aux = new Nodo();
		aux = primero;
		primero = aux->sig;
		aux->sig = nullptr;
		delete(aux);
	}
	else
		cout << "La pila esta vacia. No se puede desapilar." << endl;
}

Pedido* Pila::cima()
{
	if (!es_vacia())
		return primero->pedido;
	else
		return NULL;
}

bool Pila::es_vacia()
{
	return primero == nullptr;
}

void Pila::mostrar_pila()
{
	if (es_vacia())
		cout << endl << "La pila esta vacia. No se puede mostrar" << endl << endl << endl;
	else {
		int c = 1;
		Nodo* p = new Nodo();
		p = primero;
		while (p != nullptr) {
			cout << endl << "Pedido " << c << ": " << p->pedido->mostrar_pedido() << endl;
			p = p->sig;
			c++;
		}
		cout << endl;
	}
}
