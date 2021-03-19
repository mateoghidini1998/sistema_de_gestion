#ifndef EDITORIALES_H_INCLUDED
#define EDITORIALES_H_INCLUDED

void altaEditoriales() {
    class editoriales reg;
    if(reg.cargar()==true) {
        bool x;
        x = reg.guardarEnArchivo();
        if(x == true) {
                rlutil::setColor(rlutil::GREEN);
            cout<<"EL REGISTRO SE GUARDO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        } else {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR CORRECTAMENTE EL ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
        }

    }
    system("pause");
    system("cls");

}

void listarEditoriales() {

    FILE *f;

    system("cls");

    f = fopen(ArchivoEditoriales, "rb");

    if (f == NULL) {
            rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE (listar editoriales)"<<endl;
    rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return ;
    }

    int cont = 0;

    editoriales reg;
    while(fread(&reg,sizeof(editoriales),1,f)==1) {
        if(reg.getEstado() == true) {
            reg.mostrar();
            cout<<"---------------------------------------"<<endl;
        cont ++;
        }
    }

    if(cont == 0){
        rlutil::setColor(rlutil::RED);
        cout<<"NO HAY NINGUN REGISTRO CARGADO EN EL SISTEMA"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }

    system("pause");

}

int buscarPosEditorial(int codigo) {

    FILE *f;
    f = fopen(ArchivoEditoriales,"rb");
    if(f == NULL) {
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
        fclose(f);
        return -2;
    }

    editoriales aux;

    int pos=0;

    while(fread(&aux,sizeof(aux),1,f)==1) {
        if(codigo == aux.getCodigo() && aux.getEstado() == true) {
            fclose(f);
            return pos;
        }
        pos++;
    }

    fclose(f);
    return -1;

}

void bajaEditoriales() {
    editoriales aux;

    int codigo;

    cout<<"INGRESE EL CODIGO DE LA EDITORIAL A DAR DE BAJA"<<endl;
    cin>>codigo;

    system("cls");

    if(preguntar() == false)
        return;

        int pos = buscarPosEditorial(codigo);

    if(pos == -2){
        system("pause");
        system("cls");
        return;
    }


        if(pos == -1){
    rlutil::setColor(rlutil::RED);
    cout<<"NO SE ENCONTRO EL CODIGO DE LA EDITORIAL"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
    return;
        }

        if(aux.leerDeDisco(pos)==true && aux.getEstado() == true){
        aux.setEstado(false);
        aux.sobreEscribir(pos);
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL REGISTRO HA SIDO DADO DE BAJA EXITOSAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
        }
}

void menuEditoriales() {

    int opc;

    do {

        system("cls");
        cout<<"----------------------"<<endl;
        cout<<"---MENU EDITORIALES---"<<endl;
        cout<<"----------------------"<<endl;
        cout<<" 1) ALTA"<<endl;
        cout<<"----------------------"<<endl;
        cout<<" 2) BAJA"<<endl;
        cout<<"----------------------"<<endl;
        cout<<" 3) LISTADO"<<endl;
        cout<<"----------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"----------------------"<<endl;
        cout<<" >> ";
        cin>>opc;
        system("cls");

        switch(opc) {
        case 1:
            altaEditoriales();
            break;
        case 2:
            bajaEditoriales();
            break;
        case 3:
            listarEditoriales();
            break;
        case 0:

            break;
        default:
            rlutil::setColor(rlutil::RED);
            cout<<"INGRESE UNA OPCION EXISTENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            break;
        }

        system("cls");

    } while(opc != 0);


}

#endif // EDITORIALES_H_INCLUDED
