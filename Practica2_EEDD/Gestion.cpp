#include "Gestion.h"
#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

Gestion::Gestion()
{
    c_no_registrados = new Cola();
    c_registrados = new Cola();
    l_para_enviar1 = new Lista();
    l_para_enviar2 = new Lista();
    p_erroneos = new Pila();
    contador = 1;
    lista_selector = true;
}

Gestion::~Gestion()
{
    delete(c_no_registrados);
    delete(c_registrados);
    delete(l_para_enviar1);
    delete(p_erroneos);
}

///GETTERS
Cola* Gestion::get_c_registrados()
{
    return c_registrados;
}

Cola* Gestion::get_c_no_registrados()
{
    return c_no_registrados;
}

Lista* Gestion::get_l_para_enviar1()
{
    return l_para_enviar1;
}

Lista* Gestion::get_l_para_enviar2()
{
    return l_para_enviar2;
}

Pila* Gestion::get_p_erroneos()
{
    return p_erroneos;
}

void Gestion::cambiar_lista()
{
    if (lista_selector)
        lista_selector = false;
    else
        lista_selector = true;
}
void Gestion::encolar(Pedido* p)
{
    if (p->get_tipo_cliente() == NR)
        c_no_registrados->encolar(p);
    else
        c_registrados->encolar(p);
}

void Gestion::enlistar_inicial() ///mete los primeros 4 pedidos (en caso de haber 4) de las colas a la lista.
{
    int registrados=0;
    while (registrados !=6 && !c_registrados->es_vacia()){
        if (lista_selector){
            if (c_registrados->prim()->comprobar_pedido()){
                l_para_enviar1->add_prioridad(c_registrados->prim());
                cambiar_lista();
                registrados++;
            }
            else{
                p_erroneos->apilar_prioridad(c_registrados->prim());
            }
        }
        else{
            if (c_registrados->prim()->comprobar_pedido()){
                l_para_enviar2->add_prioridad(c_registrados->prim());
                cambiar_lista();
                registrados++;
            }
            else{
                p_erroneos->apilar_prioridad(c_registrados->prim());
            }
        }
        c_registrados->desencolar();

    }

    registrados=0;
    while (registrados!=2 && !c_no_registrados->es_vacia()){
        if (lista_selector){
            if (c_no_registrados->prim()->comprobar_pedido()){
                l_para_enviar1->add_prioridad(c_no_registrados->prim());
                cambiar_lista();
                registrados++;
            }
            else{
                p_erroneos->apilar_prioridad(c_no_registrados->prim());
            }
        }
        else{
            if (c_no_registrados->prim()->comprobar_pedido()){
                l_para_enviar2->add_prioridad(c_no_registrados->prim());
                cambiar_lista();
                registrados++;
            }
            else{
                p_erroneos->apilar_prioridad(c_no_registrados->prim());
            }
        }
        c_no_registrados->desencolar();

    }
}

void Gestion::enlistar(Lista* lista_dada) ///a�ade los pedidos segun los criterios establecidos por la practica
{
    bool enlistado=false;
    while (!enlistado && !(p_erroneos->es_vacia() && c_no_registrados->es_vacia() && c_registrados->es_vacia())){
        switch (contador){
            case 4:
                if (p_erroneos->es_vacia())
                    contador++;
                else{
                    if (p_erroneos->cima()->get_tipo_cliente()!= NR){
                        p_erroneos->cima()->arreglar_pedido();
                        lista_dada->add_prioridad(p_erroneos->cima());
                        cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista (" << p_erroneos->cima()->get_descripcion_articulo() << ", del cliente "
                        << p_erroneos->cima()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<<<" << endl;
                        p_erroneos->desapilar();
                        cambiar_lista();
                        contador=1;
                        enlistado=true;
                    }
                    else
                        contador++;
                }
                break;
            case 5:
                if (c_no_registrados->es_vacia())
                    contador++;
                else{
                    if (c_no_registrados->prim()->comprobar_pedido()){
                        lista_dada->add_prioridad(c_no_registrados->prim());

                        cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        << c_no_registrados->prim()->get_descripcion_articulo() << ", del cliente "
                        << c_no_registrados->prim()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<<<" << endl;
                        cambiar_lista();
                        contador=1;
                        enlistado=true;
                    }
                    else
                        p_erroneos->apilar(c_no_registrados->prim());
                    c_no_registrados->desencolar();
                }
                break;
            case 6:
                if (!p_erroneos->es_vacia()){
                    p_erroneos->cima()->arreglar_pedido();
                    lista_dada->add_prioridad(p_erroneos->cima());

                    cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                    << p_erroneos->cima()->get_descripcion_articulo() << ", del cliente "
                    << p_erroneos->cima()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<<<<" << endl;
                    cambiar_lista();
                    p_erroneos->desapilar();
                    enlistado=true;
                }
                contador=1;
                break;
            default:
                if (c_registrados->es_vacia())
                    contador=4;
                else{
                    if (c_registrados->prim()->comprobar_pedido()){
                        lista_dada->add_prioridad(c_registrados->prim());

                        cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        << c_registrados->prim()->get_descripcion_articulo() << ", del cliente "
                        << c_registrados->prim()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<" << endl;
                        cambiar_lista();
                        contador++;
                        enlistado=true;
                    }
                    else
                        p_erroneos->apilar(c_registrados->prim());
                    c_registrados->desencolar();
                }
                break;
        }
    }
}

void Gestion::enviar_pedido() ///eliminar el primer pedido de l_para_enviar1 y a�ade un nuevo pedido a la lista
{
    l_para_enviar1->resto();
    /*if (!p_erroneos->es_vacia() || !c_no_registrados->es_vacia() || !c_registrados->es_vacia()){
        enlistar();
    }*/
}

void Gestion::mostrar_datos() { ///muestra todos los datos
    cout << "----<COLA DE NO REGISTRADOS>----";
    c_no_registrados->mostrar_cola();
    cout << endl << "----<COLA DE REGISTRADO>----";
    c_registrados->mostrar_cola();
    cout << endl << "----<LISTA DE LISTO PARA ENVIAR 1>----";
    l_para_enviar1->mostrar_lista();
    cout << endl << "----<LISTA DE LISTO PARA ENVIAR 2>----";
    l_para_enviar2->mostrar_lista();
    cout << endl << "----<PILA DE ERRONEOS>----";
    p_erroneos->mostrar_pila();
}

void Gestion::simula_tiempo() ///funcion principal del programa, establece el orden en que se invocan las funciones y simula el paso del tiempo
{
    int minutos_gestion1=0;
    int minutos1=0;
    int minutos2=0;
    cout << "\n\n\n############ Asi se encuentra la"
    << " estructura al inicio de la ejecucion ############" << endl;

    mostrar_datos();

    cout << "############ Introducimos los primeros 4"
    << " pedidos a la lista de pedidos para enviar ############" << endl;

    if(!c_registrados->es_vacia() || !c_no_registrados->es_vacia())
        enlistar_inicial();
    mostrar_datos();

    cout << "############ A partir de aqui se van introduciendo los pedido a la lista"
    << " de listos para enviar segun los pedidos van estando preparados ############" << endl;

    while (!l_para_enviar1->es_vacia() || !c_no_registrados->es_vacia() || !c_registrados->es_vacia() || !p_erroneos->es_vacia()){ ///comienza la simulacion del paso del tiempo
        minutos_gestion1++;
        minutos1++;
        minutos2++;
        if (l_para_enviar1->es_vacia()) {
            cout << "Los pedidos son todos erroneos, enviando a la lista el primero de la pila de erroneos" << endl;
            if (lista_selector)
                enlistar(l_para_enviar1);
            else
                enlistar(l_para_enviar2);
        }
        else {
            Pedido* p;
            if (minutos1 == 1) {
                p = l_para_enviar1->prim();
                l_para_enviar1->resto(); //Enviar el pedido a "Enviando...", para que no se cuele otro pedido.

                cout << "\nPREPARANDO ENVIO:\nEl pedido requiere "
                << p->get_tiempo() << " minutos." << endl;
            }
            if (minutos1 < p->get_tiempo()) {
                cout << "Han pasado: " << minutos1
                << " minutos desde el envio del ultimo pedido. El proximo pedido necesita: " << p->get_tiempo() << endl;
            }

            if (minutos1 == p->get_tiempo()){
                cout << "HAN PASADO " << minutos1 << " MINUTOS, PEDIDO ENVIADO."
                << "\n\n############ Esta es la estructura despues de haber enviado el pedido ############" << endl;
            }

            if (minutos_gestion1 % 2 == 0) {
                if (lista_selector)
                    enlistar(l_para_enviar1);
                else
                    enlistar(l_para_enviar2);
            }

            if (minutos1 == p->get_tiempo()) {
                //l_para_enviar1->resto(); //enviamos pedido
                mostrar_datos();
                minutos1=0;
            }
        }
    }
}
