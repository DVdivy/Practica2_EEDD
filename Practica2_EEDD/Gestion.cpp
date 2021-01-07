#include "Gestion.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>


using namespace std;

Gestion::Gestion()
{
    c_no_registrados = new Cola();
    c_registrados = new Cola();
    l_para_enviar1 = new Lista();
    l_para_enviar2 = new Lista();
    p_erroneos = new Pila();
    a_clientes = new ABB();
    contador = 1;
    lista_selector = true;
    enviando1 = false;
    enviando2 = false;
    minutos_gestion = 0;
}

Gestion::~Gestion()
{
    delete(c_no_registrados);
    delete(c_registrados);
    delete(l_para_enviar1);
    delete(l_para_enviar2);
    delete(p_erroneos);
    delete(a_clientes);
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
    while (registrados !=3 && !c_registrados->es_vacia()){
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
    while (registrados!=1 && !c_no_registrados->es_vacia()){
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

void Gestion::enlistar(Lista* lista_dada) ///añade los pedidos segun los criterios establecidos por la practica
{
    bool enlistado=false;
    while (!enlistado && !(p_erroneos->es_vacia() && c_no_registrados->es_vacia() && c_registrados->es_vacia())){
        switch (contador){
            case 4:
                //{
                if (p_erroneos->es_vacia())
                    contador++;
                else{
                    if (p_erroneos->cima()->get_tipo_cliente()!= NR){
                        color(4);
                        p_erroneos->cima()->arreglar_pedido();
                        color(7);
                        lista_dada->add_prioridad(p_erroneos->cima());

                        pedido_insertado(p_erroneos->cima());

                        //cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        //<< p_erroneos->cima()->get_descripcion_articulo() << ", del cliente "
                        //<< p_erroneos->cima()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<<<"
                        //<< endl;

                        p_erroneos->desapilar();
                        cambiar_lista();
                        contador=1;
                        enlistado=true;
                    }
                    else
                        contador++;
                }
                break;
                //}
            case 5:
                //{
                if (c_no_registrados->es_vacia())
                    contador++;
                else{
                    if (c_no_registrados->prim()->comprobar_pedido()){
                        lista_dada->add_prioridad(c_no_registrados->prim());

                        pedido_insertado(c_no_registrados->prim());

                        //cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        //<< c_no_registrados->prim()->get_descripcion_articulo() << ", del cliente "
                        //<< c_no_registrados->prim()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<<<"
                        //<< endl;

                        cambiar_lista();
                        contador=1;
                        enlistado=true;
                    }
                    else
                        p_erroneos->apilar_prioridad(c_no_registrados->prim());
                    c_no_registrados->desencolar();
                }
                break;
                //}
            case 6:
                //{
                if (!p_erroneos->es_vacia()){
                    color(4);
                    p_erroneos->cima()->arreglar_pedido();
                    color(7);
                    lista_dada->add_prioridad(p_erroneos->cima());

                    pedido_insertado(p_erroneos->cima());

                    //cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                    //<< p_erroneos->cima()->get_descripcion_articulo() << ", del cliente "
                    //<< p_erroneos->cima()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<<<<"
                    //<< endl;

                    cambiar_lista();
                    p_erroneos->desapilar();
                    enlistado=true;
                }
                contador=1;
                break;
                //}
            default:
                //{
                if (c_registrados->es_vacia())
                    contador=4;
                else{
                    if (c_registrados->prim()->comprobar_pedido()){
                        lista_dada->add_prioridad(c_registrados->prim());


                        pedido_insertado(c_registrados->prim());

                        //cout << "\t\t>>>>>>>>>>>>>>>> Insertado nuevo pedido a la lista ("
                        //<< c_registrados->prim()->get_descripcion_articulo() << ", del cliente "
                        //<< c_registrados->prim()->get_nombre_cliente() << ")<<<<<<<<<<<<<<<<<"
                        //<< endl;

                        cambiar_lista();
                        contador++;
                        enlistado=true;
                    }
                    else
                        p_erroneos->apilar_prioridad(c_registrados->prim());
                    c_registrados->desencolar();
                }
                break;
                //}
        }
    }
}

void Gestion::color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void Gestion::mostrar_datos() { ///muestra todos los datos
    color(6);
    cout << endl << "----<COLA DE NO REGISTRADO>----";
    color(14);
    c_no_registrados->mostrar_desc_cola();
    color(5);
    cout << endl << "----<COLA DE REGISTRADO>----";
    color(13);
    c_registrados->mostrar_desc_cola();
    color(1);
    cout << endl << "----<LISTA DE LISTO PARA ENVIAR 1>----";
    color(9);
    l_para_enviar1->mostrar_lista_desc();
    color(3);
    cout << endl << "----<LISTA DE LISTO PARA ENVIAR 2>----";
    color(11);
    l_para_enviar2->mostrar_lista_desc();
    color(4);
    cout << endl << "----<PILA DE ERRONEOS>----";
    color(12);
    p_erroneos->mostrar_desc_pila();
    color(7);
}

void Gestion::mensaje(Tipo_mensaje m) {
    switch(m){
    case INICIAL:
        cout
        << "\n\n\n############ Asi se encuentra la"
        << " estructura al inicio de la ejecucion ############"
        << endl;
        break;
    case PRIMEROS_PEDIDOS:
        cout
        << "############ Introducimos los primeros 4"
        << " pedidos a la lista de pedidos para enviar ############"
        << endl;
        break;
    case COMIENZA_EL_PROCESO:
        cout
        << "############ A partir de aqui se van introduciendo los pedido a la lista"
        << " de listos para enviar segun los pedidos van estando preparados ############"
        << endl << endl;
        break;
    case TODOS_ERRONEOS:
        cout << "Los pedidos son todos erroneos, enviando a la lista el primero de la pila de erroneos" << endl;
        break;
    case DESPUES_DE_ENVIAR_PEDIDO:
        cout << "\n############ Esta es la estructura despues de haber enviado el pedido ############"<< endl;
    }
}
void Gestion::cabecera(int tiempo_general) {
    color(10);
    cout << "╔══════════════╦══════════════╗" << endl;
    cout << "║    LISTA 1   ║    LISTA 2   ║" << endl;
    if (tiempo_general % 2 == 1)
        cout << "╠══════════════╩══════════════╣" << endl;
    else
        cout << "╠══════════════╬══════════════╣" << endl;
    color(7);
}

void Gestion::pedido_insertado(Pedido* p) {
    cout << "║      PEDIDO INSERTADO       ║" << "Minuto " << minutos_gestion << endl;
    cout << "║      " << p->get_descripcion_articulo();
    //const char* str = (const char*)p->get_descripcion_articulo();
    for (int i=0; i<22-p->get_descripcion_articulo().length()+1; i++) {
        cout << " ";
    }
    cout << "║" << endl;
    cout << "╠══════════════╦══════════════╣" << endl;
}

void Gestion::progreso(int tiempo_general, int minutos1, int minutos2, Pedido* p1, Pedido* p2) {
    if(minutos1 == 0)
        cout << "║    ENVIADO   ";
    else if (!enviando1 && l_para_enviar1->es_vacia())
        cout << "║  ----------  ";
    else if(float(minutos1) / p1->get_tiempo() != 1)
        cout << "║    "<< int(float(minutos1)/p1->get_tiempo() * 100) << "%       ";

    if (minutos2 == 0)
        cout << "║    ENVIADO   ║" << "Minuto " << minutos_gestion << endl;
    else if (!enviando2 && l_para_enviar2->es_vacia())
        cout << "║  ----------  ║" << "Minuto " << minutos_gestion << endl;
    else if (float(minutos2) / p2->get_tiempo() != 1)
        cout << "║    "<< int(float(minutos2)/p2->get_tiempo() * 100) << "%       ║" << "Minuto " << minutos_gestion << endl;
    if (tiempo_general % 2 == 1)
        cout << "╠══════════════╩══════════════╣" << endl;
    else
        cout << "╠══════════════╬══════════════╣" << endl;
}

void Gestion::simula_tiempo() ///funcion principal del programa, establece el orden en que se invocan las funciones y simula el paso del tiempo
{
    minutos_gestion=0;
    int minutos1=0;
    int minutos2=0;
    enviando1 = false;
    enviando2 = false;
    mensaje(INICIAL);
    mostrar_datos();
    mensaje(PRIMEROS_PEDIDOS);

    if(!c_registrados->es_vacia() || !c_no_registrados->es_vacia())
        enlistar_inicial();

    mostrar_datos();
    mensaje(COMIENZA_EL_PROCESO);

    cabecera(minutos_gestion);
    Pedido* p;
    Pedido* p2;
    while (enviando1 || enviando2
           || !l_para_enviar1->es_vacia() || !l_para_enviar2->es_vacia()
           || !c_no_registrados->es_vacia() || !c_registrados->es_vacia()
           || !p_erroneos->es_vacia()){ ///comienza la simulacion del paso del tiempo

        minutos_gestion++;
        minutos1++;
        minutos2++;
        if (l_para_enviar1->es_vacia() && l_para_enviar2->es_vacia() && !enviando1 && !enviando2) {
            mensaje(TODOS_ERRONEOS);
            if (lista_selector)
                enlistar(l_para_enviar1);
            else
                enlistar(l_para_enviar2);
        }
        else {

            if (!l_para_enviar1->es_vacia() || enviando1){
                if (minutos1 == 1) {
                    p = l_para_enviar1->prim();
                    l_para_enviar1->resto(); //Enviar el pedido a "Enviando...", para que no se cuele otro pedido.
                    enviando1 = true;
                }

                if (minutos_gestion % 2 == 0) {
                    if (lista_selector)
                        enlistar(l_para_enviar1);
                    else
                        enlistar(l_para_enviar2);
                }

                if (minutos1 == p->get_tiempo()) {
                    minutos1=0;
                    a_clientes->insertar(p); //Metiendo el cliente en el arbol
                    enviando1 = false;

                }
            }
            if (!l_para_enviar2->es_vacia() || enviando2){
                if (minutos2 == 1) {
                    p2 = l_para_enviar2->prim();
                    l_para_enviar2->resto(); //Enviar el pedido a "Enviando...", para que no se cuele otro pedido.
                    enviando2 = true;
                }
                if (minutos_gestion % 2 == 0) {
                    if (lista_selector)
                        enlistar(l_para_enviar1);
                    else
                        enlistar(l_para_enviar2);
                }

                if (minutos2 == p2->get_tiempo()) {
                    minutos2=0;
                    a_clientes->insertar(p2); //Metiendo el cliente en el arbol
                    enviando2 = false;
                }
            }

            progreso(minutos_gestion, minutos1, minutos2, p, p2);
            if ((minutos1 == 0 || minutos2 == 0)) {
                mostrar_datos();
                if (!l_para_enviar1->es_vacia() || !l_para_enviar2->es_vacia() || enviando1 || enviando2)
                    cabecera(minutos_gestion);
            }


        }
    }
    a_clientes->mostrar_arbol(0);
    opciones_arbol();
}

void Gestion::opciones_arbol()
{
    bool correcto = false;
    bool salir;
    bool fin_programa = false;
    while(!fin_programa) {
        string eleccion;
        cout << "Seleccione una de las siguientes opciones:" << endl;
        cout << "1: Buscar un cliente en el abb de envíos, dado su nombre, y mostrar los datos de todos los pedidos del mismo." << endl;
        cout << "2: Mostrar los datos de los clientes y sus pedidos recorriendo el abb de envíos en preorden." << endl;
        cout << "3: Calcular la altura del abb de envíos creado." << endl;
        cout << "4: Calcular cuantas unidades de un producto se han vendido, dada la descripción del mismo." << endl;
        cout << "5: Mostrar los datos de clientes VIP del abb de envíos, ordenados alfabéticamente por el nombre del cliente." << endl;
        cout << "6: Salir del sistema." << endl;
        while (!correcto){
            cin >> eleccion;
            salir = false;
            for (int i=0 ; i<eleccion.size() && !salir; i++){
                if (!(eleccion[i]>='0' && eleccion[i] <='9')){
                    cout << "Opcion no valida, introduzca la eleccion de nuevo: " << endl;
                    correcto = false;
                    salir = true;
                }
                else if (stoi(eleccion)<0 || stoi(eleccion)>6) {
                    cout << "Numero no valido, introduzcalo de nuevo: " << endl;
                    correcto = false;
                    salir = true;
                }
                else
                    correcto=true;
            }
        }

        switch (stoi(eleccion)) {
            case 1:
                {
                string nombre;
                cout << "Escriba el nombre del cliente que quiere buscar: " << endl;
                cin.ignore();
                getline(cin, nombre);
                a_clientes->buscar_cliente(nombre);
                correcto = false;
                break;
                }

            case 2:
                a_clientes->mostrar_datos_preorden();
                correcto = false;
                break;
            case 3:
                cout << "La altura del arbol es: " << a_clientes->altura() << endl << endl;
                a_clientes->altura();
                correcto = false;
                break;
            case 4:
                {
                string descripcion;
                cout << "Escriba la descripcion del producto que quiere buscar: " << endl;
                cin.ignore();
                getline(cin, descripcion);
                cout << "Se han vendido " << a_clientes->unidades_producto(descripcion) << " unidades." << endl << endl;
                correcto = false;
                break;
                }
            case 5:
                a_clientes->mostrar_datos_VIP();
                correcto = false;
                break;
            case 6:
                correcto = false;
                fin_programa = true;
                cout << "FIN DEL PROGRAMA." << endl;
                break;
            default:
                correcto = false;
        }
    }
}


