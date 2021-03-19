#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

void recaudacion(){

float acum = 0;

empleado auxE;
ventas auxV;

FILE *e , *v;
e = fopen(archivoEmpleados,"rb");
if(e == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO";
rlutil::setColor(rlutil::WHITE);
    fclose(e);
    return;
}
v = fopen(archivoVentas,"rb");
if(v == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO";
rlutil::setColor(rlutil::WHITE);
    fclose(v);
    return;
}

while(fread(&auxE,sizeof(empleado),1,e)==1){
    acum = 0;
    fseek(v,0,0);
    while(fread(&auxV,sizeof(ventas),1,v)==1){
        if(auxV.getDni() == auxE.getDni()){
            acum += auxV.getTotal();
        }
    }
    if(acum!=0 && auxE.getEstado()== true){
    auxE.mostrarNombre();
    cout<<"TOTAL: "<<acum<<endl;
    cout<<"----------------------"<<endl;
    }
}

fclose(e);
fclose(v);

system("pause");
system("cls");

}

void librosVendidos(){

int acum = 0;

ventas auxV;

FILE *v, *l;
v = fopen(archivoVentas,"rb");

if(v == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO";
rlutil::setColor(rlutil::WHITE);
    fclose(v);
    return;
}
l = fopen(archivoLibros,"rb");
if(l == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO";
rlutil::setColor(rlutil::WHITE);
    fclose(l);
    return;
}

libros libro;

while(fread(&libro,sizeof(libros),1,l)==1){
        acum = 0;
        fseek(v,0,0);
    while(fread(&auxV,sizeof(ventas),1,v)==1){
        if(auxV.getCodigoL() == libro.getCodigo()){
            acum += auxV.getCant();
        }
    }
    if(acum != 0 && libro.getEstado()==true){
    libro.mostrarNombre();
    cout<<"CANTIDAD VENDIDOS: "<<acum<<endl;
    cout<<"-------------------------"<<endl;
    }

}

fclose(l);
fclose(v);

system("pause");
system("cls");

}

int devolverAutor(int codigoL){

FILE *f;
f = fopen(archivoLibros,"rb");
if(f == NULL){
        fclose(f);
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO DE AUTORES"<<endl;
        rlutil::setColor(rlutil::WHITE);
    exit(-1);
}

libros aux;
while(fread(&aux,sizeof(libros),1,f)==1){
    if(aux.getCodigo() == codigoL){
            fclose(f);
            return aux.getCodigoAutor();
    }
}

}

void ventasAutor(){

FILE *a, *v;
a = fopen(archivoAutores,"rb");
if(a == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
rlutil::setColor(rlutil::WHITE);
    fclose(a);
    return;
}
v = fopen(archivoVentas,"rb");
if(a == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE"<<endl;
rlutil::setColor(rlutil::WHITE);
    fclose(v);
    return;
}

autor reg;
ventas aux;

int cont;
while(fread(&reg,sizeof(autor),1,a)==1){
    cont = 0;
    fseek(v,0,0);
    while(fread(&aux,sizeof(ventas),1,v)==1){
        if(reg.getCodigo()==devolverAutor(aux.getCodigoL())){
            cont += aux.getCant();
        }
    }
    if(cont != 0){
        reg.mostrarNombre();
        cout<<"CANTIDAD DE LIBROS VENDIDOS: "<<cont<<endl;
        cout<<"----------------------"<<endl;
}
}

fclose(a);
fclose(v);

system("pause");
system("cls");

}

bool compararAntiguedad(class FECHA masViejoActual, class FECHA empleado2){

if(empleado2.getAnio() < masViejoActual.getAnio())
    return true;
if(empleado2.getAnio() > masViejoActual.getAnio())
    return false;
if(empleado2.getMes() < masViejoActual.getMes())
    return true;
if(empleado2.getMes() > masViejoActual.getMes())
    return false;
if(empleado2.getDia() < masViejoActual.getMes())
    return true;
if(empleado2.getDia() > masViejoActual.getMes())
    return false;
}

void mayorAntiguedad(){

FILE *f;
f = fopen(archivoEmpleados,"rb");
if(f == NULL){
    rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO"<<endl;
    rlutil::setColor(rlutil::WHITE);
    fclose(f);
    return;
}

empleado aux, masViejo;

int cont = 0;

while(fread(&aux,sizeof(aux),1,f)==1){

    if(cont==0 && aux.getEstado()==true){
        masViejo = aux;
    }

    if(cont>0){

        if(compararAntiguedad(masViejo.getFechaAntiguedad(),aux.getFechaAntiguedad())==true && aux.getEstado()==true){
            masViejo = aux;
        }

    }

    cont++;
}

fclose(f);

if(cont == 0){
        rlutil::setColor(rlutil::RED);
        cout<<"NO HAY NINGUN EMPLEADO REGISTRADO"<<endl;
rlutil::setColor(rlutil::WHITE);
fclose(f);
return;
}

cout<<"EMPLEADO CON MAYOR ANTIGUEDAD: "<<endl;

masViejo.mostrar();

system("pause");
system("cls");

}

void menuReportes(){
int opc;

    bool x = true;

    while(x != false) {
        cout<<"-------------------------"<<endl;
        cout<<"------MENU REPORTES------"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 1) RECAUDACION POR EMPLEADO"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 2) VENDIDOS POR LIBRO"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 3) VENTAS POR AUTOR"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 4) EMPLEADO CON MAYOR ANTIGUEDAD"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" 0) VOLVER"<<endl;
        cout<<"-------------------------"<<endl;
        cout<<" >> ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            recaudacion();
            break;
        case 2:
            librosVendidos();
            break;
        case 3:
            ventasAutor();
            break;
        case 4:
            mayorAntiguedad();
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


#endif // REPORTES_H_INCLUDED
