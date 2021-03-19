#ifndef METODOSEMPLEADOS_H_INCLUDED
#define METODOSEMPLEADOS_H_INCLUDED

int empleado::guardarEnBackUp(){
FILE *f;
f = fopen("empleadosBackUp.dat","ab");
int a;
a = fwrite(this,sizeof(empleado),1,f);
fclose(f);
return a;
}

bool empleado::leerDeDisco(int pos){

if(pos == -1)
    return false;

FILE *f;
f = fopen(archivoEmpleados,"rb");
if(f == NULL)return false;
fseek(f,pos * sizeof(empleado),0);
if(fread(this,sizeof(empleado),1,f)==true){
fclose(f);
return true;
}
fclose(f);
return false;

}

struct fecha {
    int dia, mes, anio;
};

struct fecha fechaHoy() {
    struct fecha diaActual;
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    diaActual.anio=tmPtr->tm_year+1900;
    diaActual.mes=tmPtr->tm_mon+1;
    diaActual.dia=tmPtr->tm_mday;
    return diaActual;
}

bool compararFechas(FECHA fechaIngresada, struct fecha fechaActual) {
    if(fechaIngresada.getAnio() > fechaActual.anio)
        return false;
    if(fechaIngresada.getAnio() < fechaActual.anio)
        return true;
    if(fechaIngresada.getMes() > fechaActual.mes)
        return false;
    if(fechaIngresada.getMes() < fechaActual.mes)
        return true;
    if(fechaIngresada.getDia() <= fechaActual.dia) {
        return true;
    } else {
        return false;
    }
}

bool empleado::cargar() {
    system("cls");
    cout<<"INGRESE NOMBRE DEL EMPLEADO: ";
    cin>>nombre;
    system("cls"); //CAMBIAR
    cout<<"INGRESE APELLIDO: ";
    cin>>apellido;
    system("cls"); //CAMBIAR
    cout<<"INGRESE DNI: ";
    cin>>dni;
    system("cls");
    if(verificarDni(dni)== false) {
            rlutil::setColor(rlutil::YELLOW);
        cout<<"ESE DNI YA EXISTE"<<endl;
    rlutil::setColor(rlutil::WHITE);
    system("pause");
    system("cls");
        return false;
    }
    cout<<"INGRESE FECHA DE CONTRATACION"<<endl;
    int a;
    cout<<"DIA: ";
    cin>>a;
    if(a < 1 && a > 31) {
            rlutil::setColor(rlutil::YELLOW);
        cout<<"EL DIA DEBE SER MAYOR A 1 Y MENOR A 31"<<endl;
    rlutil::setColor(rlutil::WHITE);
        return false;
    }
    setDia(a);
    cout<<"MES: ";
    cin>>a;
    setMes(a);
    if(a < 1 && a > 12) {
            rlutil::setColor(rlutil::YELLOW);
        cout<<"EL MES DEBE ESTAR ENTRE 1 Y 12"<<endl;
    rlutil::setColor(rlutil::WHITE);
        return false;
    }
    cout<<"AÑO: ";
    cin>>a;
    setAnio(a);
    struct fecha aux;
    aux = fechaHoy();
    if(compararFechas(fechaAntiguedad, aux)== false){
            rlutil::setColor(rlutil::RED);
     cout<<"LA FECHA DE CONTRATACION NO PUEDE SER MAYOR A LA DEL DIA ACTUAL"<<endl;
    rlutil::setColor(rlutil::WHITE);
     system("pause");
     system("cls");
     return false;
    }
    system("cls");
    cout<<"INGRESE SUELDO: ";
    cin>>sueldo;
    system("cls");
    while(sueldo <= 0) {
        system("cls");
        rlutil::setColor(rlutil::RED);
        cout<<"EL SUELDO NO PUEDE SER MENOR O IGUAL A 0"<<endl;
        rlutil::setColor(rlutil::WHITE);
        cout<<"INGRESE SUELDO: ";
        cin>>sueldo;
    }
    cout<<"INGRESE TELEFONO: ";
    cin>>telefono;
    system("cls");
    cout<<"INGRESE EMAIL: ";
    cin>>email;
    system("cls");
    cout<<"INGRESE DIRECCION: ";
    cin>>direccion;

    system("cls");
    return true;

}

void empleado::mostrar() {
    cout<<"NOMBRE DEL EMPLEADO: ";
    cout<<nombre<<endl; //CAMBIAR
    cout<<"APELLIDO: ";
    cout<<apellido<<endl; //CAMBIAR
    cout<<"DNI: ";
    cout<<dni<<endl;
    cout<<"SUELDO: ";
    cout<<sueldo<<endl;
    cout<<"TELEFONO: "<<telefono<<endl;
    cout<<"EMAIL: "<<email<<endl;
    cout<<"DIRECCION: "<<direccion<<endl;
    cout<<"FECHA DE CONTRATACION: "<<endl;
    cout<<getDia()<<"/"<<getMes()<<"/"<<getAnio()<<endl;
}

void empleado::setSueldo() {
    cout<<"INGRESE NUEVO SUELDO: ";
    float nuevosueldo;
    cin>>nuevosueldo;
    sueldo = nuevosueldo;
    system("cls");
}

bool empleado::guardarEnArchivo() {
    FILE *f;
    f = fopen(archivoEmpleados,"ab+");
    if(f == NULL) {
            rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(guardarachivo)"<<endl;
    rlutil::setColor(rlutil::WHITE);
        fclose(f);
        system("pause");
        return false;
    }
    bool x;
    x = fwrite(this,sizeof(empleado),1,f);
    fclose(f);
    return x;
}

int empleado::getDni() {
    return dni;
}

void empleado::setEstado(bool x) {
    estado = x;
}

bool empleado::getEstado() {
    return estado;
}

bool empleado::sobreEscribir(int pos) {
    FILE *f;
    f = fopen(archivoEmpleados,"rb+");
    if(f == NULL) {
            rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO(empleado::reactivar)"<<endl;
    rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }
    fseek(f, pos * sizeof(empleado),0);
    if(fwrite(this,sizeof(empleado),1,f)==true){
    fclose(f);
    return true;
    }
    fclose(f);
    return false;
}

#endif // METODOSEMPLEADOS_H_INCLUDED
