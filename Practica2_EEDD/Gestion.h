#pragma once
#include "Lista.h"
#include "Cola.h"
#include "Pila.h"
#include "Pedido.h"
#include "ABB.h"

class Gestion
{
private:
	Cola* c_registrados;
	Cola* c_no_registrados;
	Lista* l_para_enviar1;
	Lista* l_para_enviar2;
	Pila* p_erroneos;
	ABB* a_clientes;
	int contador;
	bool lista_selector;
public:
	Gestion();
	~Gestion();

	void encolar(Pedido* p);
	void cambiar_lista();
	void enlistar_inicial();
	void enlistar(Lista* lista_dada);
	void enviar_pedido();
	void mostrar_datos();
	void simula_tiempo();
	void opciones_arbol();


	///GETTERS
	Cola* get_c_registrados();
	Cola* get_c_no_registrados();
	Lista* get_l_para_enviar1();
	Lista* get_l_para_enviar2();
	Pila* get_p_erroneos();
};

