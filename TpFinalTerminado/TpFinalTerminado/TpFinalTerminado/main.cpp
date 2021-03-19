#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <locale.h>
#include <cstdio>

using namespace std;

#include "rlutil.h"
#include "empleados.h"
#include "metodosEmpleados.h"
#include "metodosEditoriales.h"
#include "editoriales.h"
#include "metodosAutores.h"
#include "autores.h"
#include "metodosLibros.h"
#include "libros.h"
#include "metodosVentas.h"
#include "ventas.h"
#include "configuracion.h"
#include "reportes.h"

void MenuPpal();

int main() {

    setlocale(LC_ALL,"spanish");
    rlutil::setBackgroundColor(rlutil::MAGENTA);

    int opc;

    bool x = true;

    while(x!=false) {

        system("cls");
        MenuPpal();
        cin>>opc;
        system("cls");

        switch(opc) {
        case 1:
            empleados();
            break;
        case 2:
            menulibros();
            break;
        case 3:
            menuVentas();
            break;
        case 4:
            menuReportes();
            break;
        case 5:
            menuautor();
            break;
        case 6:
            menuEditoriales();
            break;
            case 7:
            configuracion();
            break;

        case 0:
            x = false;
            break;
        default:
            rlutil::setColor(rlutil::YELLOW);
            cout<<"INGRESE UNA OPCION EXISTENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
}

void MenuPpal() {

    cout<<"------------------------"<<endl;
    cout<<"-----MENU PRINCIPAL-----"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 1) EMPLEADOS"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 2) LIBROS"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 3) VENTAS"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 4) REPORTES"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 5) AUTORES"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 6) EDITORIALES"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 7) CONFIGURACION"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" 0) SALIR DEL PROGRAMA"<<endl;
    cout<<"------------------------"<<endl;
    cout<<" >> ";

}
