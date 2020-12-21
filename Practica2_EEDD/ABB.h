#pragma once
#include <stdlib.h>
#include "Pedido.h"
using namespace std;

class Nodo_a_bin;

class ABB
{
private:
    //Pedido* pedido;
    Nodo_a_bin* raiz;

public:
    ABB();
    ~ABB();
    void insertar(Pedido* p);
    void mostrar_arbol(int);

    void buscar_cliente(string cliente);
    void mostrar_datos_preorden();
    int altura();
    int unidades_producto(string descripcion);
    void mostrar_datos_VIP();
};
