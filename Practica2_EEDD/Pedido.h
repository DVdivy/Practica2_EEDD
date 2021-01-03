#pragma once
#include <string>
using namespace std;

enum Tipo_cliente {VIP,NVIP,NR};

class Pedido
{
private:
	string descripcion_articulo;
	string nombre_cliente;
	string direccion;
	Tipo_cliente tipo_cliente;
	string numero_tarjeta;
	int tiempo;
public:
	Pedido(); ///Constructor vacio con tiempo aleatorio
	Pedido(string descripcion_articulo, string nombre_cliente, string direccion,
		Tipo_cliente tipo_cliente, string numero_tarjeta); //Constructor con parametros (el tipo del cliente es Tipo_cliente)
	Pedido(string descripcion_articulo, string nombre_cliente, string direccion,
		string tipo_cliente, string numero_tarjeta); //Constructor con parametros (el tipo del cliente es string)
	Pedido(string descripcion_articulo, string nombre_cliente, string direccion,
		string tipo_cliente, string numero_tarjeta, int tiempo); //Constructor añadiendo ademas el tiempo

    void arreglar_pedido();
    bool comprobar_nombre();
	bool comprobar_direccion();
	bool comprobar_numero_tarjeta();
	bool comprobar_tiempo();
	bool comprobar_pedido();

	///GETTERS
	string get_descripcion_articulo() const;
	string get_nombre_cliente() const;
	string get_direccion() const;
	Tipo_cliente get_tipo_cliente() const;
	string get_tipo_cliente_string() const;
	string get_numero_tarjeta() const;
	int get_tiempo() const;

	///SETTERS
	void set_descripcion_articulo(string _descripcion_articulo);
	void set_nombre_cliente(string _nombre_cliente);
	void set_direccion(string _direccion);
	void set_tipo_cliente(string _tipo_cliente);
	void set_numero_tarjeta(string _numero_tarjeta);
    void set_tiempo(int _tiempo);
	///TO_STRING
	string mostrar_pedido();
	string mostrar_pedido_datos_pedido();
};

