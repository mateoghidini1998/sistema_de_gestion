#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDE

const char backupEmpleados[30] = {"empleadosBackUp.dat"}, backupLibros[30] = {"librosBackUp.dat"};
const char backupVentas[30] = {"ventasBackUp.dat"}, backUpAutores[30] = {"autoresBackUp.dat"};
const char backUpEditoriales[30] = {"editorialesBackUp.dat"};

void recuperarRegistros() {
    char a;
    rlutil::setColor(rlutil::YELLOW);
    cout<<"¿ESTA SEGURO DE QUE DESEA RECUPERAR LOS REGISTROS ELIMINADOS?(y/n)"<<endl;
    rlutil::setColor(rlutil::WHITE);
    cin>>a;
    if(a != 'y' && a != 'n') {
        system("cls");
        cout<<"DEBE INGRESAR Y O N"<<endl;
        system("pause");
        system("cls");
        return;
    }

    if(a == 'n') {
        return;
    }

    FILE *f;
    f = fopen(archivoEmpleados, "ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (EMPLEADOS)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return;
    }

    empleado regE;

    int cont=0;

    while(fread(&regE,sizeof(empleado),1,f)==1) {
        if(regE.getEstado()==false) {
            regE.setEstado(true);
            if(regE.sobreEscribir(cont)==false) {
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDIERON REACTIVAR LOS REGISTROS EXITOSAMENTE(1)"<<endl;
                rlutil::setColor(rlutil::WHITE);
                fclose(f);
                return;
            }
        }
        cont++;
    }

    fclose(f);

    f = fopen(archivoLibros,"ab+");

    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (libros)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        fclose(f);
        return;
    }

    libros regL;

    cont = 0;

    while(fread(&regL,sizeof(libros),1,f)==1) {
        if(regL.getEstado()==false) {
            regL.setEstado(true);
            if(regL.sobreEscribir(cont)==false) {
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDIERON REACTIVAR LOS REGISTROS EXITOSAMENTE(2)"<<endl;
                rlutil::setColor(rlutil::WHITE);
                fclose(f);
                return;
            }
        }
        cont++;
    }

    fclose(f);

    f = fopen(archivoVentas,"ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (ventas)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        fclose(f);
        return;
    }

    ventas regV;

    cont = 0;

    while(fread(&regV,sizeof(ventas),1,f)==1) {
        if(regV.getEstado()==false) {
            regV.setEstadoNuevo(true);
            if(regV.sobreEscribir(cont)==false) {
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDIERON REACTIVAR LOS REGISTROS EXITOSAMENTE(3)"<<endl;
                rlutil::setColor(rlutil::WHITE);
                fclose(f);
                return;
            }
        }
        cont++;
    }

    autor aut;

    cont = 0;

    f = fopen(archivoAutores,"ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO (AUTORES)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return;
    }

    while(fread(&aut,sizeof(autor),1,f)==1) {
        if(aut.getEstado()==false) {
            aut.setEstado(true);
            if(aut.sobreEscribir(cont)==false) {
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDIERON REACTIVAR LOS REGISTROS EXITOSAMENTE(4)"<<endl;
                rlutil::setColor(rlutil::WHITE);
                fclose(f);
                return;
            }
        }
        cont++;
    }
    fclose(f);

    f = fopen(ArchivoEditoriales,"ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO (EDITORIALES)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return;
    }

    editoriales edit;

    cont = 0;

    while(fread(&edit,sizeof(edit),1,f)==1) {
        if(edit.getEstado()==false) {
            edit.setEstado(true);
            if(edit.sobreEscribir(cont)==false) {
                rlutil::setColor(rlutil::RED);
                cout<<"NO SE PUDIERON REACTIVAR LOS REGISTROS EXITOSAMENTE(4)"<<endl;
                rlutil::setColor(rlutil::WHITE);
                fclose(f);
                return;
            }
        }
        cont++;
    }
    fclose(f);

    system("cls");
    rlutil::setColor(rlutil::GREEN);
    cout<<"LOS ARCHIVOS SE HAN RECUPERADO DE FORMA EXITOSA"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
}

void reiniciarBackUps() {

    FILE *f;
    f = fopen(backupEmpleados,"wb");
    fclose(f);
    f = fopen(backupLibros,"wb");
    fclose(f);
    f = fopen(backupVentas,"wb");
    fclose(f);
    f = fopen(backUpAutores,"wb");
    fclose(f);
    f = fopen(backUpEditoriales,"wb");
    fclose(f);

}

bool cargarBackUpEmpleados() {
    FILE *e;
    e = fopen(archivoEmpleados,"ab+");
    if(e == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (EMPLEADOS)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    empleado aux;

    while(fread(&aux,sizeof(empleado),1,e)==1) {
        if(aux.guardarEnBackUp()!=1) {
            rlutil::setColor(rlutil::RED);
            cout<<"HUBO UN PROBLEMA GUARDANDO UNO DE LOS REGISTROS (libros)"<<endl;
            rlutil::setColor(rlutil::WHITE);
            fclose(e);
            system("pause");
            system("cls");
            return false;
        }
    }

    fclose(e);
    return true;
}

bool cargarBackUpVentas() {
    FILE *v;
    v = fopen(archivoVentas,"ab+");
    if(v == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (ventas)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    ventas venta;

    while(fread(&venta,sizeof(ventas),1,v)==1) {
        if(venta.guardarEnBackUp()!=1) {
            rlutil::setColor(rlutil::RED);
            cout<<"HUBO UN PROBLEMA GUARDANDO UNO DE LOS REGISTROS (ventas)"<<endl;
            rlutil::setColor(rlutil::WHITE);
            fclose(v);
            system("pause");
            system("cls");
            return false;
        }
    }

    fclose(v);
    return true;
}

bool cargarBackUpLibros() {
    FILE *l;
    l = fopen(archivoLibros,"ab+");
    if(l==NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (libros)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    libros libro;
    while(fread(&libro,sizeof(libros),1,l)==1) {
        if(libro.guardarEnBackUp()!= 1) {
            rlutil::setColor(rlutil::RED);
            cout<<"HUBO UN PROBLEMA GUARDANDO UNO DE LOS REGISTROS (libros)"<<endl;
            rlutil::setColor(rlutil::WHITE);
            fclose(l);
            system("pause");
            system("cls");
            return false;
        }
    }
    fclose(l);
    return true;
}

bool cargarBackUpAutores() {
    FILE *a;
    a = fopen(archivoAutores, "rb");
    if(a == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (autores)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    autor auxAut;

    while(fread(&auxAut,sizeof(autor),1,a)==1) {
        if(auxAut.guardarEnBackUp()!=1) {
            rlutil::setColor(rlutil::RED);
            cout<<"HUBO UN PROBLEMA GUARDANDO UNO DE LOS REGISTROS (autor)"<<endl;
            rlutil::setColor(rlutil::WHITE);
            return false;
        }
    }

    fclose(a);
    return true;
}

bool cargarBackUpEditoriales() {
    FILE *edit;
    edit = fopen(ArchivoEditoriales,"ab+");
    if(edit == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO (editorial)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }

    editoriales aux1;

    while(fread(&aux1,sizeof(editoriales),1,edit)==1) {
        if(aux1.guardarEnBackUp()!=1) {
            rlutil::setColor(rlutil::RED);
            cout<<"HUBO UN PROBLEMA GUARDANDO UNO DE LOS REGISTROS (editoriales)"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            return false;
        }
    }

    fclose(edit);
    return true;
}

void cargarBackUps() {

    char q;
    rlutil::setColor(rlutil::YELLOW);
    cout<<"¿ESTA SEGURO DE QUE DESEA CARGAR LOS BACK UPS?(y/n)"<<endl;
    cout<<"ACLARACION: ESTO BORRARA SUS BACK UPS ANTERIORES"<<endl;
    rlutil::setColor(rlutil::WHITE);
    cin>>q;
    while(q != 'y' && q != 'n') {
        system("cls");
        cout<<"DEBE INGRESAR Y O N"<<endl;
        cin>>q;
        system("cls");
        return;
    }

    if(q == 'n') {
        system("cls");
        return;
    }

    reiniciarBackUps();

    if(cargarBackUpEmpleados()==false)
        return;

    if(cargarBackUpLibros()==false)
        return;

    if(cargarBackUpVentas()==false)
        return;

    if(cargarBackUpAutores()==false)
        return;

    if(cargarBackUpEditoriales()==false)
        return;

    rlutil::setColor(rlutil::GREEN);
    cout<<"SE REALIZARON LOS BACK UPS CORRECTAMENTE"<<endl;
    rlutil::setColor(rlutil::WHITE);

    system("pause");
    system("cls");

}

void reiniciarArchivos(int a) {

if(a == 0){

    char a;
    rlutil::setColor(rlutil::YELLOW);
    cout<<"¿ESTA SEGURO DE QUE DESEA ELIMINAR TODOS LOS REGISTROS?(y/n)"<<endl;
    rlutil::setColor(rlutil::WHITE);
    cin>>a;
    while(a != 'y' && a != 'n') {
        system("cls");
        cout<<"DEBE INGRESAR Y O N"<<endl;
        cin>>a;
        system("cls");
    }

    if(a == 'n') {
        system("cls");
        return;
    }

    system("cls");

}

    FILE *f;
    f = fopen(archivoEmpleados,"wb");
    fclose(f);
    f = fopen(archivoLibros,"wb");
    fclose(f);
    f = fopen(archivoVentas,"wb");
    fclose(f);
    f = fopen(archivoAutores,"wb");
    fclose(f);
    f = fopen(ArchivoEditoriales,"wb");
    fclose(f);

}

bool cargarArchivosEmpleados(){

FILE *b;

    b = fopen(backupEmpleados,"rb");
    if(b == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(b);
        system("pause");
        system("cls");
        return false;
    }

    empleado aux;

    bool x;

    while(fread(&aux,sizeof(empleado),1,b)==1) {
        x = aux.guardarEnArchivo();
        if(x == false) {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR UN REGISTRO CORRECTAMENTE EN UN ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            fclose(b);
            return false;
        }
    }

    fclose(b);
    return true;

}

bool cargarArchivosLibros(){

FILE *b;

    b = fopen(backupLibros,"rb");
    if(b == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(b);
        return false;
    }

    bool x;

    libros aux2;

    while(fread(&aux2,sizeof(aux2),1,b)==1) {
        x = aux2.guardarEnArchivo();
        if(x == false) {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR UN REGISTRO CORRECTAMENTE EN UN ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            fclose(b);
            return false;
        }
    }

    fclose(b);
    return true;

}

bool cargarArchivosVentas(){

FILE *b;

    b = fopen(backupVentas,"rb");
    if(b == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(b);
        return false;
    }

    ventas aux3;

    bool x;

    while(fread(&aux3,sizeof(aux3),1,b)==1) {
        x = aux3.guardarVentas();
        if(x == false) {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR UN REGISTRO CORRECTAMENTE EN UN ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            fclose(b);
            return false;
    }
    }

    fclose(b);
    return true;

}

bool cargarArchivosAutores(){

FILE *b;

    b = fopen(backUpAutores, "rb");
    if(b == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(b);
        return false;
    }

    bool x;

    autor aut;

    while(fread(&aut,sizeof(autor),1,b)==1) {
        x = aut.guardarEnArchivo();
        if(x == false) {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR UN REGISTRO CORRECTAMENTE EN UN ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            fclose(b);
            return false;
    }
    }

    fclose(b);
    return true;

}

bool cargarArchivosEditoriales(){

FILE *b;

    b = fopen(backUpEditoriales,"rb");
    if(b == NULL){
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
        fclose(b);
        system("pause");
        system("cls");
        return false;
    }
    editoriales Editaux;

    bool x;

    while(fread(&Editaux,sizeof(editoriales),1,b)==1) {
        x = Editaux.guardarEnArchivo();
        if(x == false) {
            rlutil::setColor(rlutil::RED);
            cout<<"NO SE PUDO GUARDAR UN REGISTRO CORRECTAMENTE EN UN ARCHIVO"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            fclose(b);
            return false;
    }}

    fclose(b);
    return true;

}

void reiniciarSistema() {

    char a;
    rlutil::setColor(rlutil::YELLOW);
    cout<<"¿ESTA SEGURO DE QUE DESEA ELIMINAR TODOS LOS REGISTROS (INCLUIDOS BACK UPS)?(y/n)"<<endl;
    rlutil::setColor(rlutil::WHITE);
    cin>>a;
    while(a != 'y' && a != 'n') {
        system("cls");
        cout<<"DEBE INGRESAR Y O N"<<endl;
        cin>>a;
        system("cls");
    }

    if(a == 'n') {
        system("cls");
        return;
    }

    reiniciarArchivos(1);
    reiniciarBackUps();
    rlutil::setColor(rlutil::GREEN);
    cout<<"BORRADOS TODOS LOS REGISTROS EXITOSAMENTE"<<endl;
    rlutil::setColor(rlutil::WHITE);

    system("pause");
    system("cls");
}

void cargarDesdeBackUp() {

    char a;
    rlutil::setColor(rlutil::YELLOW);
    cout<<"¿ESTA SEGURO DE QUE DESEA CARGAR TODOS LOS DATOS DESDE LOS BACK UPS?(y/n)"<<endl;
    rlutil::setColor(rlutil::WHITE);
    cin>>a;
    while(a != 'y' && a != 'n') {
        system("cls");
        cout<<"DEBE INGRESAR Y O N"<<endl;
        cin>>a;
        system("cls");
        return;
    }

    if(a == 'n') {
            system("cls");
        return;
    }

    reiniciarArchivos(1);

    if(cargarArchivosEmpleados()==false)
        return;

    if(cargarArchivosLibros()==false)
        return;

    if(cargarArchivosVentas()==false)
        return;

    if(cargarArchivosAutores()==false)
        return;

    if(cargarArchivosEditoriales()==false)
        return;

    rlutil::setColor(rlutil::GREEN);
    cout<<"SE CARGARON LOS REGISTROS EXITOSAMENTE"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
}

void configuracion() {

    int opc;

    do {
        cout<<"--------------------------"<<endl;
        cout<<"-------CONFIGURACION------"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" 1) RECUPERAR REGISTROS"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" 2) REALIZAR BACK UPS"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" 3) CARGAR DESDE BACK UPS"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" 4) REINICIAR SISTEMA"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" 5) REINICIAR ARCHIVOS"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"--------------------------"<<endl;
        cout<<" >> ";
        cin>>opc;
        system("cls");

        switch(opc) {

        case 1:
            recuperarRegistros();
            break;
        case 2:
            cargarBackUps();
            break;
        case 3:
            cargarDesdeBackUp();
            break;
        case 4:
            reiniciarSistema();
            break;
        case 5:
            reiniciarArchivos(0);
            break;
            case 0:

            break;
        default:
            rlutil::setColor(rlutil::YELLOW);
            cout<<"INGRESE UNA OPCION EXISTENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            break;
        }
    } while(opc != 0);

}

#endif // CONFIGURACION_H_INCLUDED
