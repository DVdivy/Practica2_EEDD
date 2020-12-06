#pragma once
#include "Lista.h"
#include "Cola.h"
#include "Pila.h"
#include "Pedido.h"

class Gestion
{
private:
	Cola* c_registrados;
	Cola* c_no_registrados;
	Lista* l_para_enviar;
	Pila* p_erroneos;
	int contador;
public:
	Gestion();
	~Gestion();

	void encolar(Pedido* p);
	void enlistar_inicial();
	void enlistar();
	void simula_tiempo();


	///GETTERS
	Cola* get_c_registrados();
	Cola* get_c_no_registrados();
	Lista* get_l_para_enviar();
	Pila* get_p_erroneos();
};

