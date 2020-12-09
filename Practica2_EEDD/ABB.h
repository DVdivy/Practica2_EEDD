#pragma once
#include <stdlib.h>
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
    void insertar(int n);
    void mostrar_arbol(int);
};
