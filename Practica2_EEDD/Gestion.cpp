#include "Gestion.h"
#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

Gestion::Gestion()
{
    c_no_registrados = new Cola();
    c_registrados = new Cola();
    l_para_enviar = new Lista();
    p_erroneos = new Pila();
    contador = 1;
}

Gestion::~Gestion()
{
    delete(c_no_registrados);
    delete(c_registrados);
    delete(l_para_enviar);
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

Lista* Gestion::get_l_para_enviar()
{
    return l_para_enviar;
}

Pila* Gestion::get_p_erroneos()
{
    return p_erroneos;
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
    while (registrados !=3 && !c_registrados->es_vacia()){
        if (c_registrados->prim()->comprobar_pedido()){
            l_para_enviar->add_prioridad(c_registrados->prim());
            registrados++;
        }
        else{
            p_erroneos->apilar_prioridad(c_registrados->prim());
        }
        c_registrados->desencolar();
    }

    registrados=0;
    while (registrados!=1 && !c_no_registrados->es_vacia()){
        if (c_no_registrados->prim()->comprobar_pedido()){
            l_para_enviar->add_prioridad(c_no_registrados->prim());
            registrados++;
        }
        else{
            p_erroneos->apilar_prioridad(c_no_registrados->prim());
        }
        c_no_registrados->desencolar();
    }
}

void Gestion::enlistar() ///añade los pedidos segun los criterios establecidos por la practica
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
                        l_para_enviar->add_prioridad(p_erroneos->cima());

                        cout
                        << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        << p_erroneos->cima()->get_descripcion_articulo()
                        << ", del cliente "
                        << p_erroneos->cima()->get_nombre_cliente()
                        << ")"
                        << endl;

                        p_erroneos->desapilar();
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
                        l_para_enviar->add_prioridad(c_no_registrados->prim());

                        cout
                        << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        << c_no_registrados->prim()->get_descripcion_articulo()
                        << ", del cliente "
                        << c_no_registrados->prim()->get_nombre_cliente()
                        << ")"
                        << endl;

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
                    l_para_enviar->add_prioridad(p_erroneos->cima());

                    cout
                    << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                    << p_erroneos->cima()->get_descripcion_articulo()
                    << ", del cliente "
                    << p_erroneos->cima()->get_nombre_cliente()
                    << ")"
                    << endl;

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
                        l_para_enviar->add_prioridad(c_registrados->prim());

                        cout
                        << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        << c_registrados->prim()->get_descripcion_articulo()
                        << ", del cliente "
                        << c_registrados->prim()->get_nombre_cliente()
                        << ")"
                        << endl;

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

void Gestion::enviar_pedido() ///eliminar el primer pedido de l_para_enviar y añade un nuevo pedido a la lista
{
    l_para_enviar->resto();
    /*if (!p_erroneos->es_vacia() || !c_no_registrados->es_vacia() || !c_registrados->es_vacia()){
        enlistar();
    }*/
}

void Gestion::mostrar_datos() { ///muestra todos los datos
    cout << "----<COLA DE NO REGISTRADOS>----";
    c_no_registrados->mostrar_cola();
    cout << endl << "----<COLA DE REGISTRADO>----";
    c_registrados->mostrar_cola();
    cout << endl << "----<LISTA DE LISTO PARA ENVIAR>----";
    l_para_enviar->mostrar_lista();
    cout << endl << "----<PILA DE ERRONEOS>----";
    p_erroneos->mostrar_pila();
}

void Gestion::simula_tiempo() ///funcion principal del programa, establece el orden en que se invocan las funciones y simula el paso del tiempo
{
    int minutos_gestion=0;
    int minutos=0;

    cout << "\n\n\n############ Asi se encuentra la"
    << " estructura al inicio de la ejecucion ############"
    << endl;

    mostrar_datos();

    cout << "############ Introducimos los primeros 4"
    << " pedidos a la lista de pedidos para enviar ############"
    << endl;

    if(!c_registrados->es_vacia() || !c_no_registrados->es_vacia())
        enlistar_inicial();
    mostrar_datos();

    cout
    << "############ A partir de aqui se van introduciendo los pedido a la lista"
    << " de listos para enviar segun los pedidos van estando preparados ############"
    << endl;

    while (!l_para_enviar->es_vacia() || !c_no_registrados->es_vacia() || !c_registrados->es_vacia() || !p_erroneos->es_vacia()){ ///comienza la simulacion del paso del tiempo
        minutos_gestion++;
        minutos++;
        if (l_para_enviar->es_vacia()) {
            cout << "Los pedidos son todos erroneos, enviando a la lista el primero de la pila de erroneos" << endl;
            enlistar();
        }
        else {
            Pedido* p;
            if (minutos == 1) {
                p = l_para_enviar->prim();
                l_para_enviar->resto(); //Enviar el pedido a "Enviando...", para que no se cuele otro pedido.

                cout
                << "\nPREPARANDO ENVIO:\nEl pedido requiere "
                << p->get_tiempo()
                << " minutos."
                << endl;
            }
            if (minutos < p->get_tiempo()) {
                cout
                << "Han pasado: "
                << minutos
                << " minutos desde el envio del ultimo pedido. El proximo pedido necesita: "
                << p->get_tiempo()
                << endl;
            }

            if (minutos == p->get_tiempo()){
                cout
                << "HAN PASADO "
                << minutos
                << " MINUTOS, PEDIDO ENVIADO."
                << "\n\n############ Esta es la estructura despues de haber enviado el pedido ############"
                << endl;
            }

            if (minutos_gestion % 2 == 0) {
                enlistar();
            }

            if (minutos == p->get_tiempo()) {
                //l_para_enviar->resto(); //enviamos pedido
                mostrar_datos();
                minutos=0;
            }
        }
    }
}
