#include "ABB.h"
#include "Nodo_a_bin.h"
#include<iostream>
using namespace std;
ABB::ABB() {
    //pedido = NULL;
    raiz = nullptr;
}

ABB::~ABB()
{
    delete raiz;
}

void ABB::insertar(int n)
{
    if (raiz == nullptr)
    {
        raiz = new Nodo_a_bin();
        raiz->num = n;
    }
    else if (n <= raiz->num)
    {
        raiz->arbol_izquierdo->insertar(n);
    }
    else
    {
        raiz->arbol_derecho->insertar(n);
    }
}

void ABB::mostrar_arbol(int contador = 0)
{
    if (raiz == nullptr)
        return;
    else {
        raiz->arbol_derecho->mostrar_arbol(contador + 1);
        for (int i = 0; i < contador; i++) {
            cout << "   ";
        }
        cout << raiz->num << endl;
        raiz->arbol_izquierdo->mostrar_arbol(contador + 1);


    }
}
