#include "Gestion.h"
#include <windows.h>
#include <time.h>

int main() {
    srand(time(NULL));//Para que los tiempos aleatorios de los pedidos sean diferentes cada vez que se ejecuta el programa.
    string eleccion;
    bool correcto=false;

    Gestion* gestion = new Gestion();

    cout << "Elija como desea hacer la simulacion." << endl;
    cout << "Introduzca \"1\" si desea crear sus propios productos" << endl;
    cout << "Introduzca cualquier otro numero si desea utilizar 12 productos aleatorios." << endl;
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

    switch (stoi(eleccion)){
        case 1:
            int total_vueltas;
            cout << "determine cuantos objetos va a introducir (un entero entre 10 y 20)?" << endl;
            cin >> total_vueltas;
            for(int vueltas_dadas=0 ; vueltas_dadas<total_vueltas ; vueltas_dadas++){
                gestion->encolar(gestion->leer_pedido());
            }
            break;
        default:
            ///se instancias varios pedidos
            Pedido* p1 = new Pedido ("Martillo",    "Andres",   "Jose Zorrilla 7",  Tipo_cliente::VIP,              "780044545667");
            Pedido* p2 = new Pedido ("Libro",       "Carlos",   "Perez Galdos 12",  Tipo_cliente::NVIP,             "78001345667");
            Pedido* p3 = new Pedido ("Taladro",     "Julio",    "Calle Estrella 17",Tipo_cliente::NVIP,             "780678345667");
            Pedido* p4 = new Pedido ("Mesa",        "Div9y",     "Calle Sol 71",     Tipo_cliente::NR,              "780453745667");
            Pedido* p5 = new Pedido ("PS5",         "Padilla",  "Calle Luna 2",     Tipo_cliente::VIP,              "780044545667");
            Pedido* p6 = new Pedido ("XBOX",        "Gsus",     "Calle Espacio 3",  Tipo_cliente::NVIP,             "780013456676");
            Pedido* p7 = new Pedido ("Cerveza",     "Edu",      "Calle Grande 7",   Tipo_cliente::NVIP,             "780678345667");
            Pedido* p8 = new Pedido ("PC",          "Hugo",     "Calle Blanca 9",   Tipo_cliente::NR,               "780453745667");
            Pedido* p9 = new Pedido ("Pala",        "Alex",     "Calle Satelite 8", Tipo_cliente::VIP,              "780044545667");
            Pedido* p10 = new Pedido("Deportivas",  "Mario",   "Calle Estrecha 10",Tipo_cliente::NVIP,              "78001345667");
            Pedido* p11 = new Pedido("Cantimplora", "Ana",      "Calle Oscura 7",   Tipo_cliente::NVIP,             "780678345667");
            Pedido* p12 = new Pedido("Auriculares", "Alfredo",  "Calle Jon 1",      Tipo_cliente::NR,               "780453745667");
            ///se añaden a las colas que correspondan
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
            break;
    }
    gestion->simula_tiempo();
    return 0;
}
