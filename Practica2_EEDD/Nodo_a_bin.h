#pragma once
#include <stdlib.h>
#include <iostream>
#include "Pedido.h"
#include "Lista.h"
using namespace std;

class ABB;

class Nodo_a_bin {
private:
	string nombre;
	string tarjeta;
	string tipo_cliente;
	Lista* lista_pedidos;

	ABB* arbol_izquierdo;
	ABB* arbol_derecho;

public:
	Nodo_a_bin();
	~Nodo_a_bin();
	friend class ABB;
};
