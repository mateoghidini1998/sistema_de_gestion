#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

void nuevaventa() {
    ventas reg;
    bool x = reg.cargar();
    if(x == false) {
        system("pause");
        system("cls");
        return;
    }
    x = reg.guardarVentas();
    if(x == false) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO GUARDAR EL REGISTRO CORRECTAMENTE EN EL ARCHIVO"<<endl;
        rlutil::setColor(rlutil::WHITE);
    } else {
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL REGISTRO SE GUARDO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }
    system("pause");
    system("cls");
}

void listarVentas() {
    FILE *f;
    f = fopen(archivoVentas,"rb");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(listar empleados)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return;
    }

    ventas reg;
    int cont=0;
    libros aux;
    while(fread(&reg,sizeof(ventas),1,f)==1) {
        if(reg.getEstado()==true) {
            cont++;
            reg.mostrar();
            cout<<"---------------------------------------"<<endl;
        }
    }

    if(cont == 0) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE REGISTRO NINGUNA VENTA"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }
    fclose(f);
    system("pause");
    system("cls");

}

bool verificarExistenciaVenta(int codigo){
FILE *f;
f = fopen(archivoVentas,"rb");
if(f == NULL)
    return false;

    ventas aux;
    while(fread(&aux,sizeof(ventas),1,f)==1){
        if(aux.getCodigo()==codigo && aux.getEstado()==true)
            return true;
    }

    return false;

}

void cancelarventas() {

    int codigo;
    cout<<"INGRESE CODIGO DE LA VENTA: ";
    cin>>codigo;

    if(verificarExistenciaVenta(codigo)==false){
    rlutil::setColor(rlutil::RED);
    cout<<"NO SE ENCONTRO EL CODIGO DEL PRODUCTO"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
    return;
    }

    system("cls");

    if(preguntar() == false)
        return;

    ventas aux;

    if(aux.leerDeDisco(codigo-1)==true){
        aux.setEstadoNuevo(false);
        aux.sobreEscribir(codigo-1);
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL REGISTRO SE DIO DE BAJA EXITOSAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }
    rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO DAR DE BAJA CORRECTAMENTE EL REGISTRO"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
        system("cls");
}

void menuVentas() {
    int opc;

    bool x = true;

    while(x != false) {
        cout<<"------------------------"<<endl;
        cout<<"------MENU VENTAS-------"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 1) NUEVA VENTA"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 2) CANCELAR VENTA"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 3) LISTADO"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" >> ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            nuevaventa();
            break;
        case 2:
            cancelarventas();
            break;
        case 3:
            listarVentas();
            break;
        case 0:
            x = false;
            break;

        default:
            system("cls");
            rlutil::setColor(rlutil::YELLOW);
            cout<<"INGRESE UNA OPCION EXISTENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            break;
        }
    }



}

#endif // VENTAS_H_INCLUDED
