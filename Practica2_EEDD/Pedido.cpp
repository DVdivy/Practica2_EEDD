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
bool Pedido::comprobar_nombre()
{
    if (nombre_cliente.size()==0)
        return false;
    for (int i=0 ; i < nombre_cliente.size() ; i++){
        if (!((nombre_cliente[i]>=65 && nombre_cliente[i] <=90) || (nombre_cliente[i]>=97 && nombre_cliente[i]<=122) || nombre_cliente[i]==' '))
            return false;
    }
    return true;
}

bool Pedido::comprobar_direccion()
{
    if (direccion.size()==0)
        return false;
    if (!(direccion[direccion.size()-1] >='0' && direccion[direccion.size()-1] <='9'))
        return false;
    for (int i=0; i<direccion.size(); i++)
        if (!((direccion[i]>=65 && direccion[i] <=90) || (direccion[i]>=97 && direccion[i]<=122) || direccion[i]==' ' || (direccion[i]>='0' && direccion[i]<='9')))
            return false;
    return true;
}

bool Pedido::comprobar_numero_tarjeta()
{
    if (numero_tarjeta.size()!=12)
        return false;

    for (int i=0 ; i < numero_tarjeta.size() ; i++){
        if (!(numero_tarjeta[i]>=48 && numero_tarjeta[i] <=57))
            return false;
    }
    return true;
}

bool Pedido::comprobar_tiempo()
{
    if (tiempo>=1 && tiempo<=10)
            return true;
    return false;
}
///se comprueba que el pedido cumple TODOS los criterios
bool Pedido::comprobar_pedido()
{
    if ((comprobar_nombre() && comprobar_direccion() && comprobar_numero_tarjeta() && comprobar_tiempo()))
        return true;
    return false;
}

void Pedido::arreglar_pedido() ///pide cambiar datos del pedido hasta que no haya datos erroneos
{
    string eleccion;
    bool correcto = false;
    bool salir;
    while (!comprobar_pedido()){
        cout << "Estos son los datos del pedido erroneo, modifiquelos para que sea valido: " << endl;
        cout << "1 Descripcion: " << descripcion_articulo << endl;
        cout << "2 Nombre: " << nombre_cliente << endl;
        cout << "3 Direccion: " << direccion << endl;
        cout << "4 Tipo de cliente: " << get_tipo_cliente_string() << endl;
        cout << "5 Numero de tarjeta: " << numero_tarjeta << endl;
        cout << "6 Tiempo: " << tiempo << endl;
        cout << "Elija el numero del campo que desea cambiar (elija 0 si no desea cambiar nada mas): " << endl;
        while (!correcto){
            cin >> eleccion;
            salir = false;
            for (int i=0 ; i<eleccion.size() && !salir; i++){
                if (!(eleccion[i]>='0' && eleccion[i] <='9')){
                    cout << "Eleccion no valida, introduzca la eleccion de nuevo: " << endl;
                    correcto = false;
                    salir = true;
                }
                else if (stoi(eleccion)<0 || stoi(eleccion)>6) {
                    cout << "Numero no valido, introduzca la eleccion de nuevo: " << endl;
                    correcto = false;
                    salir = true;
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
            {
                string _descripcion;
                cout << "Introduzca la nueva descripcion (no hay restricciones): " << endl;
                cin.ignore();
                getline(cin,_descripcion);
                set_descripcion_articulo(_descripcion);
                correcto=false;
                break;
            }
        case 2:
            {
                string _nombre;
                cout << "Introduzca el nuevo nombre (solo letras y espacios): " << endl;
                cin.ignore();
                getline(cin,_nombre);
                set_nombre_cliente(_nombre);
                correcto=false;
                break;
            }
        case 3:
            {
                string _direccion;
                cout << "Introduzca la nueva direccion (Solo puede contener letras numeros y espacios): " << endl;
                cin.ignore();
                getline(cin,_direccion);
                set_direccion(_direccion);
                correcto=false;
                break;
            }
        case 4:
            {
                string _tipo;
                cout << "Introduzca el nuevo tipo de cliente (no hay restricciones): " << endl; //si pone algo sin sentido se considera NR
                cin.ignore();
                getline(cin,_tipo);
                set_tipo_cliente(_tipo);
                correcto=false;
                break;
            }
        case 5:
            {
                string _numero;
                cout << "Introduzca el nuevo numero de tarjeta (12 numeros): " << endl;
                cin.ignore();
                getline(cin,_numero);
                set_numero_tarjeta(_numero);
                correcto=false;
                break;
            }
        case 6:
            {
                int _tiempo;
                cout << "Introduzca el nuevo tiempo (numero del 1 al 10, incluidos): " << endl;
                cin >> _tiempo;
                set_tiempo(_tiempo);
                correcto=false;
                break;
            }

        default:
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

string Pedido::mostrar_pedido()
{
	return "\nDescricpion del articulo: " + descripcion_articulo +
		"\nNombre del cliente: " + nombre_cliente +
		"\nDireccion: " + direccion +
		"\nTipo de cliente: " + get_tipo_cliente_string() +
		"\nNumero de tarjeta: " + numero_tarjeta +
		"\nTiempo: " + to_string(tiempo);
}

string Pedido::mostrar_pedido_datos_pedido()
{
	return "\nDescricpion del articulo: " + descripcion_articulo +
		"\nDireccion: " + direccion +
		"\nTiempo: " + to_string(tiempo);
}
