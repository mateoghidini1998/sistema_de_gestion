#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

bool verficarExistenciaLibro(int codigo);

void altalibros() {
    system("cls");
    class libros reg;
    if(reg.cargar()==false) {
        return;
    }
    bool x;
    x = reg.guardarEnArchivo();
    if(x == true) {
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL REGISTRO SE GUARDO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
    } else {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO GUARDAR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }

    system("pause");
    system("cls");

}

void listarLibros() {

    FILE *f;

    system("cls");

    f = fopen(archivoLibros, "rb");

    if (f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE (listar libros)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return;
    }
    int cont=0;
    libros reg;
    int pos;
    editoriales aux;
    while(fread(&reg,sizeof(libros),1,f)==1) {
        if(reg.getEstado() == true) {
            reg.mostrar();
            pos = buscarPosEditorial(reg.getEditorial());
            aux.leerDeDisco(pos);
            aux.mostrar();
            cout<<"---------------------------------------"<<endl;
            cont ++;
        }
    }

    if(cont == 0) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO HAY NINGUN PRODUCTO CARGADO EN EL SISTEMA"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }
    system("pause");
    system("cls");
}

void bajaLibros() {

    system("cls");

    libros aux;

    int codigo;

    cout<<"INGRESE EL CODIGO DEL LIBRO A DAR DE BAJA: ";
    cin>>codigo;

    system("cls");

    if(verficarExistenciaLibro(codigo)==false) {
        system("pause");
        system("cls");
        return;
    }

    if(preguntar() == false)
        return;
    system("cls");

    if(aux.leerDeDisco(codigo-1)==true) {
        aux.setEstado(false);
        aux.sobreEscribir(codigo-1);
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL REGISTRO HA SIDO DADO DE BAJA EXITOSAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }
    rlutil::setColor(rlutil::RED);
        cout<<"ESE REGISTRO YA HA SIDO DADO DE BAJA"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
}

void modificarLibros() {

    system("cls");

    int codigo;
    float Nstock;

    libros aux;

    cout<<"INGRESE EL CODIGO DE LIBRO QUE DESEA MODIFICAR"<<endl;
    cin>>codigo;

    system("cls");

    if(verficarExistenciaLibro(codigo)==false) {
        system("pause");
        system("cls");
        return;
    }

    if(aux.leerDeDisco(codigo-1)==true && aux.getEstado() == true){
    cout<<"INGRESE NUEVO STOCK: ";
    cin>>Nstock;
    aux.setStock(Nstock);
    aux.sobreEscribir(codigo-1);
    rlutil::setColor(rlutil::GREEN);
    cout<<"EL REGISTRO SE MODIFICO EXITOSAMENTE"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
    return;
    }
}

bool verificarAutor(int codigo) {
    FILE *f;
    f = fopen(archivoAutores, "ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE (libros::verificarAutor)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    autor aux;

    while(fread(&aux,sizeof(autor),1,f)==1) {
        if(aux.getCodigo() == codigo && aux.getEstado() == true) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;

}

bool verificarEditorial(int editorial) {
    FILE *f;
    f = fopen(ArchivoEditoriales,"rb");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMNTE EL ARCHIVO"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    editoriales aux;
    while(fread(&aux,sizeof(editoriales),1,f)==1) {
        if(aux.getCodigo()==editorial && aux.getEstado()==true) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;

}

void menulibros() {

    int opc;

    bool x = true;

    while(x != false) {

        cout<<"-------------------------"<<endl;
        cout<<"-------MENU LIBROS-------"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 1) ALTA"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 2) BAJA"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 3) LISTADO"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 4) MODIFICACION STOCK"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" >> ";
        cin>>opc;

        switch(opc) {

        case 1:
            altalibros();
            break;
        case 2:
            bajaLibros();
            break;
        case 3:
            listarLibros();
            break;
        case 4:
            modificarLibros();
            break;
        case 0:
            x = false;
            break;
        default:
            system("cls");
            rlutil::setColor(rlutil::RED);
            cout<<"INGRESE UNA OPCION EXISTENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            break;

        }
    }
}

#endif // LIBROS_H_INCLUDED
