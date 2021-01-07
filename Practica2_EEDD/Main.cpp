#include "Gestion.h"
#include "ABB.h"
#include <windows.h>
#include <time.h>
#include <fstream>

Pedido* leer_pedido() ///recibe los datos del usuario y los almacena
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

Pedido* leer_pedido_dado(string input) ///recibe los datos del usuario y los almacena.
{
    string parametros_pedido[6];
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


void leer_fichero(Gestion* gestion)
{
    ifstream arch;
    arch.open("pedidos.txt", ios::in);
    if (arch.fail()){
        cout << "error al abrir el archivo." << endl;
        exit(1);
    }
    int n_lineas=0;
    while(arch.good()){
        if(arch.get()=='\n')
            n_lineas++;
    }

    ifstream archivo_entrada("pedidos.txt");
    string linea;
    for (int contador = 0; contador < n_lineas; contador++){
        getline(archivo_entrada,linea);
        gestion->encolar(leer_pedido_dado(linea));
        cout << linea << endl;
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, 0, 0);

    /*ABB* arbol = new ABB();

    Pedido* p1 = new Pedido ("Martillo",    "Andres",   "Jose Zorrilla 7",  "NVIP",              "780044545667", 2);
    Pedido* p2 = new Pedido ("Libro",       "Carlos",   "Perez Galdos 12",  Tipo_cliente::NR,             "780013456674");
    Pedido* p3 = new Pedido ("Taladro",     "Julio",    "Calle Estrella 17",Tipo_cliente::NVIP,             "780678345667");
    Pedido* p4 = new Pedido ("Mesa",        "Div9y",     "Calle Sol 71",     Tipo_cliente::NR,              "780453745667");
    Pedido* p5 = new Pedido ("PS5",         "Padilla",  "Calle Luna 2",     "VIP",              "780044545667", 1);
    Pedido* p6 = new Pedido ("XBOX",        "Gsus",     "Calle Espacio 3",  Tipo_cliente::VIP,             "780013456676");
    Pedido* p7 = new Pedido ("Cerveza",     "Edu",      "Calle Grande 7",   Tipo_cliente::VIP,             "780678345667");
    Pedido* p8 = new Pedido ("PC",          "Hugo",     "Calle Blanca 9",   Tipo_cliente::NR,               "780453745667");
    Pedido* p9 = new Pedido ("Pala",        "Alex",     "Calle Satelite 8", Tipo_cliente::VIP,              "780044545667");
    Pedido* p10 = new Pedido("Deportivas",  "Mario",   "Calle Estrecha 10",Tipo_cliente::NVIP,              "78001345667");
    Pedido* p11 = new Pedido("Cantimplora", "Ana",      "Calle Oscura 7",   Tipo_cliente::NVIP,             "780678345667");
    Pedido* p12 = new Pedido("Auriculares", "Alfredo",  "Calle Jon 1",      Tipo_cliente::NR,               "780453745667");

    arbol->insertar(p1);
    arbol->insertar(p2);
    arbol->insertar(p3);
    arbol->insertar(p4);
    arbol->insertar(p5);
    arbol->insertar(p6);
    arbol->insertar(p7);
    arbol->insertar(p8);
    arbol->insertar(p9);
    arbol->insertar(p10);
    arbol->insertar(p11);
    arbol->insertar(p12);

    arbol->mostrar_arbol(0);*/
    srand(time(NULL));//Para que los tiempos aleatorios de los pedidos sean diferentes cada vez que se ejecuta el programa.
    string eleccion;
    bool correcto=false;
    bool salir;
    Gestion* gestion = new Gestion();

    cout << "Elija como desea hacer la simulacion." << endl;
    cout << "Introduzca \"1\" si desea crear sus propios productos" << endl;
    cout << "Introduzca \"2\" si desea leer los pedidos del fichero \"pedidos.txt\": " << endl;
    cout << "Introduzca cualquier otro numero si desea utilizar 12 productos aleatorios." << endl;
    while (!correcto){
        cin >> eleccion;
        salir = false;
        for (int i=0 ; i<eleccion.size() && !salir; i++){
            if (!(eleccion[i]>='0' && eleccion[i] <='9')){
                cout << "Eleccion no valida, introduzca la eleccion de nuevo: " << endl;
                correcto = false;
                salir = true;
            }
            else
                correcto=true;
        }
    }

    switch (stoi(eleccion)){
        case 1:
            int total_vueltas;
            cout << "determine cuantos objetos va a introducir (un entero entre 10 y 20)" << endl;
            cin >> total_vueltas;
            for(int vueltas_dadas=0 ; vueltas_dadas<total_vueltas ; vueltas_dadas++){
                gestion->encolar(leer_pedido());
            }
            break;
        case 2:
            leer_fichero(gestion);
            break;
        default:
            ///se instancias varios pedidos
            Pedido* p1 = new Pedido ("Martillo",    "Andres",   "Jose Zorrilla 7",  Tipo_cliente::NVIP,     "780044545667");
            Pedido* p2 = new Pedido ("Libro",       "Carlos",   "Perez Galdos 12",  Tipo_cliente::NR,       "780013456674");
            Pedido* p3 = new Pedido ("Martillo",    "Julio",    "Calle Estrella 17",Tipo_cliente::NVIP,     "780678345667");
            Pedido* p4 = new Pedido ("Mesa",        "Div9y",    "Calle Sol 71",     Tipo_cliente::NR,       "780453745667");
            Pedido* p5 = new Pedido ("PS5",         "Padilla",  "Calle Luna 2",     Tipo_cliente::VIP,      "780044545667");
            Pedido* p6 = new Pedido ("Ordenador Portatil",        "Gsus",     "Calle Espacio 3",  Tipo_cliente::VIP,      "780013456676");
            Pedido* p7 = new Pedido ("Martillo",    "divy",     "Calle Grande 7",   Tipo_cliente::VIP,      "780678345667");
            Pedido* p8 = new Pedido ("PC",          "Hugo",     "Calle Blanca 9",   Tipo_cliente::NR,       "780453745667");
            Pedido* p9 = new Pedido ("Pala",        "Alex",     "Calle Satelite 8", Tipo_cliente::VIP,      "780044545667");
            Pedido* p10 = new Pedido("Deportivas",  "Mario",    "Calle Estrecha 10",Tipo_cliente::NVIP,     "78001345667");
            Pedido* p11 = new Pedido("Cantimplora", "Ana",      "Calle Oscura 7",   Tipo_cliente::NVIP,     "780678345667");
            Pedido* p12 = new Pedido("Auriculares", "Alfredo",  "Calle Jon 1",      Tipo_cliente::NR,       "780453745667");
            Pedido* p13 = new Pedido("Estuche",     "Daniel",   "Calle Juela 13",   Tipo_cliente::NVIP,     "456967345345");
            Pedido* p14 = new Pedido("Coche",       "Alberto",  "Calle Juela 3",    Tipo_cliente::VIP,      "456934573453");
            Pedido* p15 = new Pedido("Patinete",    "Ruben",    "Federico Monpou 7",Tipo_cliente::VIP,      "867834532457");
            Pedido* p16 = new Pedido("Switch",      "Marcos",   "Calle Bisbal 13",  Tipo_cliente::NR,       "654523452356");
            Pedido* p17 = new Pedido("PS5",         "Miriam",   "Calle Guapa 17",   Tipo_cliente::NR,       "156345634634");
            Pedido* p18 = new Pedido("I9",          "Gabriel",  "Calle Malasa�a 1", Tipo_cliente::NVIP,     "235745785672");
            Pedido* p19 = new Pedido("Pelota",      "Pedro",    "Calle Cita 32",    Tipo_cliente::VIP,      "535745721462");
            Pedido* p20 = new Pedido("Galletas",    "Julio",    "Calle Vacia 2",    Tipo_cliente::NR,      "535745721462");

            ///se a�aden a las colas que correspondan
            gestion->encolar(p1);
            gestion->encolar(p2);
            gestion->encolar(p3);
            gestion->encolar(p4);
            gestion->encolar(p5);
            gestion->encolar(p6);
            gestion->encolar(p7);
            gestion->encolar(p8);
            gestion->encolar(p9);
            gestion->encolar(p10);
            gestion->encolar(p11);
            gestion->encolar(p12);
            gestion->encolar(p13);
            gestion->encolar(p14);
            gestion->encolar(p15);
            gestion->encolar(p16);
            gestion->encolar(p17);
            gestion->encolar(p18);
            gestion->encolar(p19);
            gestion->encolar(p20);
            break;
    }
    gestion->simula_tiempo();
    return 0;
}
