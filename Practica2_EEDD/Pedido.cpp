#include "Pedido.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;


Pedido::Pedido()
{
	tiempo=rand()%10+1;
}

Pedido::Pedido(string _descripcion_articulo, string _nombre_cliente, string _direccion, Tipo_cliente _tipo_cliente, string _numero_tarjeta)
{
	descripcion_articulo = _descripcion_articulo;
	nombre_cliente = _nombre_cliente;
	direccion = _direccion;
	tipo_cliente = _tipo_cliente;
	numero_tarjeta = _numero_tarjeta;
	tiempo = rand()%10+1;
}

Pedido::Pedido(string _descripcion_articulo, string _nombre_cliente, string _direccion, string _tipo_cliente, string _numero_tarjeta)
{
	descripcion_articulo = _descripcion_articulo;
	nombre_cliente = _nombre_cliente;
	direccion = _direccion;
	set_tipo_cliente(_tipo_cliente);
	numero_tarjeta = _numero_tarjeta;
	tiempo = rand()%10+1;
}

Pedido::Pedido(string _descripcion_articulo, string _nombre_cliente, string _direccion, string _tipo_cliente, string _numero_tarjeta, int _tiempo)
{
	descripcion_articulo = _descripcion_articulo;
	nombre_cliente = _nombre_cliente;
	direccion = _direccion;
	set_tipo_cliente(_tipo_cliente);
	numero_tarjeta = _numero_tarjeta;
	tiempo = _tiempo;
}

///Comprobaciones de que los datos siguen ciertos criterios
bool Pedido::comprobar_nombre(string _nombre_cliente)
{
    if (_nombre_cliente.size()==0)
        return false;
    for (int i=0 ; i < _nombre_cliente.size() ; i++){
        if (!((_nombre_cliente[i]>=65 && _nombre_cliente[i] <=90) || (_nombre_cliente[i]>=97 && _nombre_cliente[i]<=122) || _nombre_cliente[i]==' '))
            return false;
    }
    return true;
}

bool Pedido::comprobar_direccion(string _direccion)
{
    if (_direccion.size()==0)
        return false;
    if (!(_direccion[_direccion.size()-1] >='0' && _direccion[_direccion.size()-1] <='9'))
        return false;
    for (int i=0; i<_direccion.size(); i++)
        if (!((_direccion[i]>=65 && _direccion[i] <=90) || (_direccion[i]>=97 && _direccion[i]<=122) || _direccion[i]==' ' || (_direccion[i]>='0' && _direccion[i]<='9')))
            return false;
    return true;
}

bool Gestion::comprobar_numero_tarjeta(string _numero_tarjeta)
{
    if (_numero_tarjeta.size()!=12)
        return false;

    for (int i=0 ; i < _numero_tarjeta.size() ; i++){
        if (!(_numero_tarjeta[i]>=48 && _numero_tarjeta[i] <=57))
            return false;
    }
    return true;
}

bool Pedido::comprobar_tiempo(int _tiempo)
{
    if (_tiempo>=1 && _tiempo<=10)
            return true;
    return false;
}
///se comprueba que el pedido cumple TODOS los criterios
bool Gestion::comprobar_pedido(Pedido* p)
{
    if ((comprobar_nombre(p->get_nombre_cliente()) && comprobar_direccion(p->get_direccion()) && comprobar_numero_tarjeta(p->get_numero_tarjeta()) && comprobar_tiempo(p->get_tiempo())))
        return true;
    return false;
}

void Pedido::arreglar_pedido(Pedido* p) ///pide cambiar datos del pedido hasta que no haya datos erroneos
{
    string eleccion;
    bool correcto=false;
    while (!comprobar_pedido(p)){
        cout << "Estos son los datos del pedido erroneo, modifiquelos para que sea valido: " << endl;
        cout << "1 Descripcion: " << p->get_descripcion_articulo() << endl;
        cout << "2 Nombre: " << p->get_nombre_cliente() << endl;
        cout << "3 Direccion: " << p->get_direccion() << endl;
        cout << "4 Tipo de cliente: " << p->get_tipo_cliente_string() << endl;
        cout << "5 Numero de tarjeta: " << p->get_numero_tarjeta() << endl;
        cout << "6 Tiempo: " << p->get_tiempo() << endl;
        cout << "Elija el numero del campo que desea cambiar (elija 0 si no desea cambiar nada mas): " << endl;
        while (!correcto){
            cin >> eleccion;
            for (int i=0 ; i<eleccion.size();i++){
                if (!(eleccion[i]>='0' && eleccion[i] <='9')){
                    cout << "Eleccion no valida, introduzca la eleccion de nuevo: " << endl;
                    correcto=false;
                    break;
                }
                else
                    correcto=true;
            }
        }
        switch(stoi(eleccion)){
        case 0:
            correcto=false;
            break;
        case 1:
            {string descripcion;
            cout << "Introduzca la nueva descripcion (no hay restricciones): " << endl;
            cin >> descripcion;
            p->set_descripcion_articulo(descripcion);}
            correcto=false;
            break;
        case 2:
            {string nombre;
            cout << "Introduzca el nuevo nombre (solo letras y espacios): " << endl;
            cin >> nombre;
            p->set_nombre_cliente(nombre);}
            correcto=false;
            break;
        case 3:
            {string direccion;
            cout << "Introduzca la nueva direccion (Solo puede contener letras numeros y espacios): " << endl;
            cin >> direccion;
            p->set_direccion(direccion);}
            correcto=false;
            break;
        case 4:
            {string tipo;
            cout << "Introduzca el nuevo tipo de cliente (no hay restricciones): " << endl; //si pone algo sin sentido se considera NR
            cin >> tipo;
            p->set_tipo_cliente(tipo);}
            correcto=false;
            break;
        case 5:
            {string numero;
            cout << "Introduzca el nuevo numero de tarjeta (12 numeros): " << endl;
            cin >> numero;
            p->set_numero_tarjeta(numero);}
            correcto=false;
            break;
        case 6:
            {int tiempo;
            cout << "Introduzca el nuevo tiempo (numero del 1 al 10, incluidos): " << endl;
            cin >> tiempo;
            p->set_tiempo(tiempo);}
            correcto=false;
            break;
        default:
            cout << "El numero introducido no es valido." << endl;
            correcto=false;
        }
    }
}

string Pedido::get_descripcion_articulo() const
{
	return descripcion_articulo;
}

string Pedido::get_nombre_cliente() const
{
	return nombre_cliente;
}

string Pedido::get_direccion() const
{
	return direccion;
}

Tipo_cliente Pedido::get_tipo_cliente() const
{
	return tipo_cliente;
}

string Pedido::get_tipo_cliente_string() const
{
	switch (tipo_cliente) {
	case VIP:
		return "VIP";
	case NVIP:
		return "NVIP";
	case NR:
		return "NR";
	}
}

string Pedido::get_numero_tarjeta() const
{
	return numero_tarjeta;
}

int Pedido::get_tiempo() const
{
	return tiempo;
}

void Pedido::set_descripcion_articulo(string _descripcion_articulo)
{
	descripcion_articulo = _descripcion_articulo;
}

void Pedido::set_nombre_cliente(string _nombre_cliente)
{
	nombre_cliente = _nombre_cliente;
}

void Pedido::set_direccion(string _direccion)
{
	direccion = _direccion;
}

void Pedido::set_tipo_cliente(string _tipo_cliente)
{
	if (_tipo_cliente == "VIP")
		tipo_cliente = VIP;
	else if (_tipo_cliente == "NVIP")
		tipo_cliente = NVIP;
	else
		tipo_cliente = NR;
}

void Pedido::set_numero_tarjeta(string _numero_tarjeta)
{
	numero_tarjeta = _numero_tarjeta;
}

void Pedido::set_tiempo(int _tiempo)
{
    tiempo = _tiempo;
}


Pedido* Pedido::leer_pedido() ///recibe los datos del usuario y los almacena.
{
    string input;
    string parametros_pedido[6];
    cout << "Introduce los datos del pedido" << "\nFormato(Descripcion del articulo//Nombre del cliente//Direccion//Tipo de cliente//Numero de tarjeta//Tiempo): ";
    cin.ignore();
    getline(cin,input);

    const char* cadena = input.c_str();
    ///Devuelve el primer token
    char* next_token = NULL;
    char* token = strtok_s((char*)cadena, "//", &next_token);

    ///Va cogiendo los tokens
    for (int i = 0; i < 6; i++) {
        parametros_pedido[i] = token;
        token = strtok_s(NULL, "//", &next_token);
    }
    return new Pedido(parametros_pedido[0], parametros_pedido[1], parametros_pedido[2], parametros_pedido[3], parametros_pedido[4], stoi(parametros_pedido[5]));
}

void Pedido::enviar_pedido() ///eliminar el primer pedido de l_para_enviar y añade un nuevo pedido a la lista
{
    l_para_enviar->resto();
    if (!p_erroneos->es_vacia() || !c_no_registrados->es_vacia() || !c_registrados->es_vacia()){
        enlistar();
    }
}

string Pedido::mostrar_pedido()
{
	return "\nDescricpion del articulo: " + descripcion_articulo +
		"\nNombre del cliente: " + nombre_cliente +
		"\nDireccion: " + direccion +
		"\nTipo de cliente: " + get_tipo_cliente_string() +
		"\nNumero de tarjeta: " + numero_tarjeta +
		"\nTiempo: " + to_string(tiempo);
}
