#ifndef EMPLEADOS_H_INCLUDED
#define EMPLEADOS_H_INCLUDED

bool preguntar() {

    char a;
    rlutil::setColor(rlutil::YELLOW);
    cout<<"¿ESTA SEGURO DE QUE DESEA DAR DE BAJA ESTE REGISTRO?(y/n)"<<endl;
    rlutil::setColor(rlutil::WHITE);
    cin>>a;
    while(a != 'y' && a != 'n') {
        system("pause");
        system("cls");
        cout<<"DEBE INGRESAR Y O N: "<<endl;
        cout<<" >> ";
        cin>>a;
    }

    if(a == 'n') {
        system("cls");
        return false;
    }

    return true;

}

char const archivoEmpleados[30] = {"empleados.dat"};

class FECHA {
private:
    int dia,mes,anio;
public:
    void setDia(int a) {
        dia = a;
    }
    void setMes(int a) {
        mes = a;
    }
    void setAnio(int a) {
        anio = a;
    }
    int getDia() {
        return dia;
    }
    int getMes() {
        return mes;
    }
    int getAnio() {
        return anio;
    }
    void cargarFECHA();
};

class empleado {
private:
    int dni;
    char nombre[20];
    char apellido[20];
    float sueldo;
    bool estado;
    char direccion[50];
    int telefono;
    char email[30];
    class FECHA fechaAntiguedad;
public:

    empleado() {
        estado = true;
    }
    int getDia() {
        return fechaAntiguedad.getDia();
    }
    int getMes() {
        return fechaAntiguedad.getMes();
    }
    int getAnio() {
        return fechaAntiguedad.getAnio();
    }
    void setDia(int a) {
        fechaAntiguedad.setDia(a);
    }
    void setMes(int a) {
        fechaAntiguedad.setMes(a);
    }
    void setAnio(int a) {
        fechaAntiguedad.setAnio(a);
    }
    bool cargar();
    void mostrar();
    void setSueldo();
    bool guardarEnArchivo();
    int getDni();
    void setEstado(bool);
    bool getEstado();
    bool sobreEscribir(int);
    void mostrarNombre() {
        cout<<nombre<<" "<<apellido<<endl;
    }
    FECHA getFechaAntiguedad() {
        return fechaAntiguedad;
    }
    bool leerDeDisco(int dni);
    int guardarEnBackUp();
};

void altaempleados() {
    empleado reg;
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
        system("cls");
    }
}

void listarEmpleados() {

    FILE *f;
    f = fopen(archivoEmpleados,"rb");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(listar empleados)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return;
    }

    empleado reg;

    int cont=0;
    while(fread(&reg,sizeof(empleado),1,f)==1) {
        if(reg.getEstado()==true) {
            reg.mostrar();
            cout<<"---------------------------------------"<<endl;
            cont++;
        }
    }

    if(cont == 0) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO HAY NINGUN EMPLEADO CARGADO EN EL SISTEMA"<<endl;
        rlutil::setColor(rlutil::WHITE);
    }

    fclose(f);

    system("pause");
    system("cls");
}

int buscarPosDni(int dni) {

    FILE *f;
    f = fopen(archivoEmpleados,"rb");
    if(f == NULL) {
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
        fclose(f);
        return -2;
    }

    empleado aux;

    int pos=0;

    while(fread(&aux,sizeof(aux),1,f)==1) {
        if(dni == aux.getDni() && aux.getEstado()==true) {
            fclose(f);
            return pos;
        }
        pos++;
    }

    fclose(f);
    return -1;

}

void bajaEmpleado() {

    empleado aux;

    int dni;

    cout<<"INGRESE NUMERO DE DNI DE EMPLEADO A DAR DE BAJA: ";
    cin>>dni;

    if(preguntar() == false) {
        return;
    }

    system("cls");
    int pos = buscarPosDni(dni);

    if(pos == -2){
        system("pause");
        system("cls");
        return;
    }

    if(pos == -1){
     rlutil::setColor(rlutil::RED);
    cout<<"NO SE HA ENCONTRADO EL DNI INGRESADO"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
    return;
    }

    if(aux.leerDeDisco(pos)==true) {
        aux.setEstado(false);
        aux.sobreEscribir(pos);
        rlutil::setColor(rlutil::GREEN);
        cout<<"EL EMPLEADO HA SIDO DADO DE BAJA EXITOSAMENTE"<<endl;
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

void modificacionSueldo() {

    int dni;
    cout<<"INGRESE DNI A BUSCAR: ";
    cin>>dni;
    system("cls");

    int pos = buscarPosDni(dni);
    empleado aux;
    float Nsueldo;
    if(aux.leerDeDisco(pos)==true) {
        aux.setSueldo();
        if(aux.sobreEscribir(pos)==true) {
            rlutil::setColor(rlutil::GREEN);
            cout<<"SE MODIFICO EL SUELDO EXITOSAMENTE"<<endl;
            rlutil::setColor(rlutil::WHITE);
            system("pause");
            system("cls");
            return;
        }
    }

    rlutil::setColor(rlutil::RED);
    cout<<"NO SE ENCONTRO EL DNI INGRESADO"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");

}

bool verificarDni(int dni) {

    FILE *f;
    f = fopen(archivoEmpleados, "ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    empleado aux;
    while(fread(&aux,sizeof(empleado),1,f) == 1) {
        if(aux.getDni() == dni) {
            fclose(f);
            return false;
        }
    }

    fclose(f);
    return true;
}

void empleados() {

    int opc;

    bool x = true;

    while(x != false) {
        cout<<"------------------------"<<endl;
        cout<<"-----MENU EMPLEADOS-----"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 1) ALTA"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 2) BAJA"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 3) LISTADO"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 4) MODIFICACION (SUELDO)"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"------------------------"<<endl;
        cout<<" >> ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            altaempleados();
            break;
        case 2:
            bajaEmpleado();
            break;
        case 3:
            listarEmpleados();
            break;
        case 4:
            modificacionSueldo();
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
}


#endif // EMPLEADOS_H_INCLUDED
