#include "ABB.h"
#include "Nodo_a_bin.h"
#include <windows.h>
#include<iostream>

#define VERDE 2
#define BLANCO 7

using namespace std;
ABB::ABB() {
    //pedido = NULL;
    raiz = nullptr;
}

ABB::~ABB()
{
    delete raiz;
}

void ABB::color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

bool ABB::es_menor(string s1, string s2)
{
    for (int i=0; i<s1.length(); i++) {
        s1[i] = toupper(s1[i]);
    }
    for (int i=0; i<s2.length(); i++) {
        s2[i] = toupper(s2[i]);
    }
    if (s1 <= s2) return true;
    else return false;
}

void ABB::insertar(Pedido* p)
{
    if (raiz == nullptr)
    {
        raiz = new Nodo_a_bin();
        raiz->nombre = p->get_nombre_cliente();
        raiz->tarjeta = p->get_numero_tarjeta();
        raiz->tipo_cliente = p->get_tipo_cliente_string();
        raiz->lista_pedidos->add_prioridad(p);
    }
    else if (p->get_nombre_cliente() == raiz->nombre &&
             p->get_numero_tarjeta() == raiz->tarjeta &&
             p->get_tipo_cliente_string() == raiz->tipo_cliente)
    {
        raiz->lista_pedidos->add_prioridad(p);
    }
    else if (es_menor(p->get_nombre_cliente(), raiz->nombre))
    {
        raiz->arbol_izquierdo->insertar(p);
    }
    else
    {
        raiz->arbol_derecho->insertar(p);
    }
}

string ABB::mostrar_arbol(int contador, int flag, int* slash)
{
    string devolver = "";
    if (raiz != nullptr){
        if (raiz->arbol_derecho != nullptr){
            int flag_nueva = 2;
            int slash_nuevo[contador];
            for (int i = 0; i < contador - 1; i++){
                slash_nuevo[i] = slash[i];
            }
            slash_nuevo[contador - 1] = (flag_nueva != flag) ? 1 : 0;

            devolver += raiz->arbol_derecho->mostrar_arbol(contador + 1, flag_nueva, slash_nuevo);
        }
        for (int i = 0; i < contador; i++){
            if (i == contador - 1){
                devolver += "    " + (string)((flag == 1) ? "╚" : "╔") + "══>";
            }
            else if (slash[i] == 1){
                devolver += "    ║    ";
            }
            else{
                devolver += "         ";
            }
        }
        devolver += raiz->nombre + "\n";
        if (raiz->arbol_izquierdo != nullptr){
            int flag_nueva = 1;
            int slash_nuevo[contador - 1];
            for (int i = 0; i < contador - 1; i++){
                slash_nuevo[i] = slash[i];
            }
            slash_nuevo[contador - 1] = (flag_nueva != flag) ? 1 : 0;
            devolver += raiz->arbol_izquierdo->mostrar_arbol(contador + 1, flag_nueva, slash_nuevo);
        }
    }
    return devolver;
}

void ABB::buscar_cliente(string cliente)
{
    if (raiz == nullptr)
        return;
    else
       if (cliente == raiz->nombre) {
            color(VERDE);
            cout << " ╔════════════════════════════════════════════════════════════╗" << endl;
            cout << " ║Nombre del cliente: " << raiz->nombre << endl;
            cout << " ║Tipo del cliente: " << raiz->tipo_cliente << endl;
            cout << " ║Tarjeta de credito: " << raiz->tarjeta << endl << " ║";
            raiz->lista_pedidos->mostrar_lista_datos_pedido();
            cout << " \n ╚════════════════════════════════════════════════════════════╝" << endl;
            raiz->arbol_derecho->buscar_cliente(cliente);
            raiz->arbol_izquierdo->buscar_cliente(cliente);
            color(BLANCO);
       }
       else if (es_menor(cliente, raiz->nombre)) {
            raiz->arbol_izquierdo->buscar_cliente(cliente);
       }
       else {
            raiz->arbol_derecho->buscar_cliente(cliente);
       }

}
void ABB::mostrar_datos_preorden()
{
    if (raiz == nullptr)
        return;
    else {
        color(VERDE);
        cout << " ╔════════════════════════════════════════════════════════════╗" << endl;
        cout << " ║Nombre del cliente: " << raiz->nombre << endl;
        cout << " ║Tipo del cliente: " << raiz->tipo_cliente << endl;
        cout << " ║Tarjeta de credito: " << raiz->tarjeta << endl << " ║";
        raiz->lista_pedidos->mostrar_lista_datos_pedido();
        cout << " \n ╚════════════════════════════════════════════════════════════╝" << endl;
        raiz->arbol_izquierdo->mostrar_datos_preorden();
        raiz->arbol_derecho->mostrar_datos_preorden();
        color(BLANCO);
    }

}
int ABB::altura()
{
    if (raiz == nullptr)
        return 0;
    else if (raiz->arbol_izquierdo->raiz == nullptr) {
            if (raiz->arbol_derecho->raiz == nullptr)
                return 0;
            else
                return 1 + raiz->arbol_derecho->altura();
    }
    else if (raiz->arbol_derecho->raiz == nullptr)
        return 1 + raiz->arbol_izquierdo->altura();
    else
        return 1 + max(raiz->arbol_derecho->altura(), raiz->arbol_izquierdo->altura());

}
int ABB::unidades_producto(string descripcion)
{
    int contador;
    if (raiz == nullptr)
        return 0;
    else {
        Lista* lp = raiz->lista_pedidos;
        Lista* aux = new Lista();
        contador = 0;
        while (!lp->es_vacia()) {
            if(lp->prim()->get_descripcion_articulo() == descripcion)
                contador++;
            aux->add_der(lp->prim());
            lp->resto();
        }
        while (!aux->es_vacia()) {
            lp->add_der(aux->prim());
            aux->resto();
        }
        return contador + raiz->arbol_izquierdo->unidades_producto(descripcion) + raiz->arbol_derecho->unidades_producto(descripcion);
    }

}
void ABB::mostrar_datos_VIP()
{
    //Para recorrerlos alfabéticamente se recorre el arbol en inorden
    if (raiz == nullptr)
        return;
    else {
        raiz->arbol_izquierdo->mostrar_datos_VIP();
        if (raiz->tipo_cliente == "VIP") {
            color(VERDE);
            cout << " ╔════════════════════════════════════════════════════════════╗" << endl;
            cout << " ║Nombre del cliente: " << raiz->nombre << endl;
            cout << " ║Tipo del cliente: " << raiz->tipo_cliente << endl;
            cout << " ║Tarjeta de credito: " << raiz->tarjeta << endl << " ║";
            raiz->lista_pedidos->mostrar_lista_datos_pedido();
            cout << " \n ╚════════════════════════════════════════════════════════════╝" << endl;
            color(BLANCO);
        }
        raiz->arbol_derecho->mostrar_datos_VIP();
    }
}
