#ifndef AUTORES_H_INCLUDED
#define AUTORES_H_INCLUDED

void altaAutor() {
    autor reg;
    if(reg.cargar()==true) {
        bool x;
        x = reg.guardarEnArchivo();
        if(x == true) {
            rlutil::setColor(rlutil::GREEN);
            cout<<"EL REGISTRO SE GUARDO CORRECTAMENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
        } else {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR EL ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
        }
    }
    system("cls");
}

void listarAutor() {
    FILE *f;
    f = fopen(archivoAutores,"rb");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(listar autores)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return;
    }

    autor reg;

    int cont=0;
    while(fread(&reg,sizeof(autor),1,f)==1) {
        if(reg.getEstado()==true) {
            reg.mostrar();
            cout<<"---------------------------------------"<<endl;
            cont++;
        }
    }

    if(cont == 0) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO HAY NINGUN AUTOR CARGADO EN EL SISTEMA"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }

    fclose(f);

    system("pause");
    system("cls");
}

int buscarPosAutor(int codigo) {

    FILE *f;
    f = fopen(archivoAutores,"rb");
    if(f == NULL) {
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
        fclose(f);
        return -2;
    }

    autor aux;

    int pos=0;

    while(fread(&aux,sizeof(aux),1,f)==1) {
        if(codigo == aux.getCodigo() && aux.getEstado()==true) {
            fclose(f);
            return pos;
        }
        pos++;
    }

    fclose(f);
    return -1;

}

void bajaAutor() {

    autor aux;

    int codigo;

    cout<<"INGRESE EL CODIGO DEL AUTOR A DAR DE BAJA: ";
    cin>>codigo;

    system("cls");

    if(preguntar() == false) {
        return;
    }

    int pos = buscarPosAutor(codigo);

    if(pos == -2){
        system("pause");
        system("cls");
        return;
    }


    if(pos == -1) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE HA ENCONTRADO EL CODIGO INGRESADO"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }

    if(aux.leerDeDisco(pos)==true && aux.getEstado()==true) {
        aux.setEstado(false);
        aux.sobreEscribir(pos);
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL AUTOR HA SIDO DADO DE BAJA EXITOSAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }
}

bool verificarCodigo(int codigo) {

    FILE *f;
    f = fopen(archivoAutores, "ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    autor aux;
    while(fread(&aux,sizeof(autor),1,f) == 1) {
        if(aux.getCodigo() == codigo) {
            fclose(f);
            return false;
        }
    }

    fclose(f);
    return true;
}

void menuautor() {

    int opc;

    bool x = true;

    while(x != false) {
        system("cls");
        cout<<"-------------------------"<<endl;
        cout<<"-------MENU AUTORES------"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 1) ALTA"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 2) BAJA"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 3) LISTADO"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" >> ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            altaAutor();
            break;
        case 2:
            bajaAutor();
            break;
        case 3:
            listarAutor();
            break;
        case 0:
            x = false;
            break;
        default:
            rlutil::setColor(rlutil::RED);
            cout<<"INGRESE UNA OPCION EXISTENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            break;
        }
    }
}



#endif // AUTORES_H_INCLUDED
