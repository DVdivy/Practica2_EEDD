#pragma once
#include "Lista.h"
#include "Cola.h"
#include "Pila.h"
#include "Pedido.h"
#include "ABB.h"

enum Tipo_mensaje{INICIAL, PRIMEROS_PEDIDOS, COMIENZA_EL_PROCESO, TODOS_ERRONEOS};

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
	bool enviando1;
	bool enviando2;
	int minutos_gestion;
	Tipo_mensaje tipo_mensaje;

	void color(int x);
	void mensaje(Tipo_mensaje m);
	void cabecera(int minutos_gestion);
	void progreso(int tiempo_general, int minutos1, int minutos2, Pedido* p, Pedido* p2);
	void pedido_insertado(Pedido* p);
public:
	Gestion();
	~Gestion();

	void encolar(Pedido* p);
	void cambiar_lista();
	void enlistar_inicial();
	void enlistar(Lista* lista_dada);
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

