#ifndef METODOSVENTAS_H_INCLUDED
#define METODOSVENTAS_H_INCLUDED

char const archivoVentas[20]= {"ventas.dat"};

class ventas {
private:
    int codigoVenta;
    int dni_vendedor;
    int cantidad;
    int codigo_producto;
    float total; //(precio * cant);
    bool estado;
    class FECHA fechaVenta;
public:
    ventas() {
        estado=true;
    }
    void setDia(int a) {
        fechaVenta.setDia(a);
    }
    void setMes(int a) {
        fechaVenta.setMes(a);
    }
    void setAnio(int a) {
        fechaVenta.setAnio(a);
    }
    int getDia() {
        return fechaVenta.getDia();
    }
    int getMes() {
        return fechaVenta.getMes();
    }
    int getAnio() {
        return fechaVenta.getAnio();
    }
    void mostrarFecha();
    bool cargar();
    int getStock();
    bool guardarVentas();
    int guardarEnBackUp();
    void bajaVentas();
    void mostrar();
    int getCodigo();
    void setEstadoNuevo(bool);
    bool getEstado() {
        return estado;
    }
    bool leerDeDisco(int pos);
    bool sobreEscribir(int);
    int getDni() {
        return dni_vendedor;
    }
    float getTotal() {
        return total;
    }
    int getCodigoL() {
        return codigo_producto;
    }
    int getCant() {
        return cantidad;
    }
};

int ventas::guardarEnBackUp(){
FILE *f;
f = fopen("ventasBackUp.dat","ab");
int a;
a = fwrite(this,sizeof(ventas),1,f);
fclose(f);
return a;
}

bool ventas::leerDeDisco(int pos) {
    FILE *f;
    f = fopen(archivoVentas,"rb");
    if(f == NULL)
        return false;
    fseek(f,pos*sizeof(ventas),0);
    if(fread(this,sizeof(ventas),1,f)==true) {
        fclose(f);
        return true;
    }
    fclose(f);
    return false;

}

bool verficarExistenciaLibro(int);

bool ventas::sobreEscribir(int pos) {
    FILE *f;
    f = fopen(archivoVentas,"rb+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO(ventas::reactivar)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }

    fseek(f, pos * sizeof(ventas),0);
    fwrite(this,sizeof(ventas),1,f);
    fclose(f);
    return true;

}

bool verificarStock(int cantingresada, int codigo) {
    libros aux;
    aux.leerDeDisco(codigo-1);
    if(cantingresada>aux.getStock()) {
        rlutil::setColor(rlutil::RED);
        cout<<"LA CANTIDAD DE VENTAS INGRESADAS ES MAYOR AL STOCK"<<endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    } else {
        return true;
    }
    rlutil::setColor(rlutil::RED);
    cout<<"no existe el codigo"<<endl;
    rlutil::setColor(rlutil::WHITE);
    return false;
}

int devolverCodigoVenta() {

    int cont = 1;
    FILE *p;
    ventas aux;
    p=fopen(archivoVentas, "ab+");
    while(fread(&aux,sizeof(ventas),1,p)==1) {
        cont++;
    }
    fclose(p);
    return cont;

}

bool devolverExistenciaEmpleado(int dni_vendedor) {
    FILE *f;
    f = fopen(archivoEmpleados,"rb");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }
    empleado auxEmp;
    while(1==fread(&auxEmp,sizeof(empleado),1,f)) {
        if(auxEmp.getDni() == dni_vendedor && auxEmp.getEstado() == true) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;

}

bool restarStockLibro(float *precio, int codigoLibro, int cantidad) {
    FILE *f;
    f=fopen(archivoLibros,"rb+");
    if(f==NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }
    libros reg;
    int pos=0;
    while(fread(&reg, sizeof(libros),1,f)==1) {
        if(codigoLibro == reg.getCodigo()) {
            *precio = reg.getPrecio();
            reg.restarStock(cantidad);
            fseek(f,pos * sizeof(libros),0);
            fwrite(&reg,sizeof(libros),1,f);
            fclose(f);
            return true;
        }
        pos++;
    }
    fclose(f);
    return false;
}

bool ventas::cargar() {
    codigoVenta=devolverCodigoVenta();
    cout<<"INGRESAR DNI DE VENDEDOR: ";
    cin>>dni_vendedor;
    if(devolverExistenciaEmpleado(dni_vendedor)==false) {
        rlutil::setColor(rlutil::RED);
        cout<<"EL DNI INGRESADO NO EXISTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        return false;
    }
    int codigo;
    cout<<"INGRESE CODIGO DE PRODUCTO: ";
    cin>>codigo;
    if(verficarExistenciaLibro(codigo)==false) {
        return false;
    }
    codigo_producto = codigo;
    cout<<"INGRESE CANTIDAD VENDIDA: ";
    cin>>cantidad;
    while(cantidad<=0) {
        rlutil::setColor(rlutil::YELLOW);
        cout<<"LA CANTIDAD TIENE QUE SER MAYOR QUE 0"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        cout<<"INGRESE CANTIDAD VENDIDA: ";
        cin>>cantidad;
    }
    if(verificarStock(cantidad,codigo_producto)==false) {
        return false;
    }
    float a;
    if(restarStockLibro(&a, codigo, cantidad)== false) {
        return false;
    }

    struct fecha fechaActual;

    fechaActual = fechaHoy();

    fechaVenta.setDia(fechaActual.dia);

    fechaVenta.setMes(fechaActual.mes);

    fechaVenta.setAnio(fechaActual.anio);

    total = cantidad * a;
    return true;
}

void ventas::mostrar() {
    cout<<"CODIGO DE VENTA: "<<codigoVenta<<endl;
    cout<<"DNI VENDEDOR: "<<dni_vendedor<<endl;
    cout<<"CODIGO DE PRODUCTO: "<<codigo_producto<<endl;
    cout<<"CANTIDAD: "<<cantidad<<endl;
    cout<<"TOTAL: $"<<total<<endl;
    cout<<"FECHA DE VENTA (DD/MM/AA): "<<fechaVenta.getDia()<<"/"<<fechaVenta.getMes()<<"/"<<fechaVenta.getAnio()<<endl;
}

bool ventas::guardarVentas() {
    FILE *f;
    f = fopen(archivoVentas,"ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    bool x = fwrite(this,sizeof(ventas),1,f);

    fclose(f);

    return x;

    system("pause");
    system("cls");

}

bool verficarExistenciaLibro(int codigo) {

    FILE *f;
    f = fopen(archivoLibros,"rb+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    libros aux;

    while(fread(&aux,sizeof(libros),1,f)==1) {
        if(aux.getCodigo()==codigo && aux.getEstado() == true) {
            fclose(f);
            return true;
        }
    }
    rlutil::setColor(rlutil::RED);
    cout<<"NO EXISTE ESE CODIGO DE PRODUCTO"<<endl;
    rlutil::setColor(rlutil::WHITE);
    fclose(f);
    return false;

}

int ventas::getCodigo() {
    return codigoVenta;
}

void ventas::setEstadoNuevo(bool x) {
    estado=x;
}
#endif // METODOSVENTAS_H_INCLUDED
