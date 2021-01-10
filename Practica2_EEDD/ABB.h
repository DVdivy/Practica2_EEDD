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

    bool es_menor(string s1, string s2); //devuelve true si s1 va antes alfabéticamente o si es igual que s2
    void color(int x);
public:
    ABB();
    ~ABB();
    void insertar(Pedido* p);
    string mostrar_arbol(int a, int b, int* c);

    void buscar_cliente(string cliente);
    void mostrar_datos_preorden();
    int altura();
    int unidades_producto(string descripcion);
    void mostrar_datos_VIP();
};
