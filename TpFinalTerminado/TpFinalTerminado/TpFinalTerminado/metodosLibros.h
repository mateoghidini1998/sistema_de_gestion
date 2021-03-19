#ifndef METODOSLIBROS_H_INCLUDED
#define METODOSLIBROS_H_INCLUDED
#include <iostream>
using namespace std;

const char archivoLibros [30] = {"libros.dat"};

class libros{
private:
    int autor;
    int codigo;
    int stock;
    float precio;
    char titulo[45];
    int editorial;
    bool estado;
public:
    libros(){
    estado = true;
    }
    bool cargar();
    void mostrar();
    float getPrecio();
    int getStock();
    void restarStock(int);
    bool guardarEnArchivo();
    bool leerDeDisco(int pos);//CODIGO - 1
    int getCodigo(){return codigo;}
    void setEstado(bool x){estado = x;}
    bool getEstado(){return estado;}
    void setPrecio(int a){precio = a;}
    bool sobreEscribir(int);
    void setStock(int a){stock = a;}
    void mostrarNombre(){cout<<titulo<<endl;}
    int getCodigoAutor(){return autor;}
    int guardarEnBackUp();
    int getEditorial(){return editorial;}
};

int libros::guardarEnBackUp(){
FILE *f;
f = fopen("librosBackUp.dat","ab");
int a;
a = fwrite(this,sizeof(libros),1,f);
fclose(f);
return a;
}

bool libros::leerDeDisco(int pos){

if(pos == -1)
    return false;

FILE *f;
f = fopen(archivoLibros,"rb");
if(f == NULL)return false;
fseek(f,pos * sizeof(libros),0);
if(fread(this,sizeof(libros),1,f)==true){
fclose(f);
return true;
}
fclose(f);
return false;

}

bool verificarAutor(int);

bool verificarEditorial(int);

int devolverCodigo(){

int cont = 1;
    FILE *f;
    libros aux;
    f = fopen(archivoLibros, "ab+");
    while(fread(&aux,sizeof(libros),1,f)==1) {
        cont ++;
    }
    fclose(f);
    return cont;
}

bool libros::cargar() {

    codigo = devolverCodigo();
    cin.ignore();
    cout<<"INGRESE TITULO: ";
    cin.getline(titulo,45);
    system("cls");
    cout<<"INGRESE CODIGO DE AUTOR: ";
    cin>>autor;
    if(verificarAutor(autor)==false){
        system("cls");
        rlutil::setColor(rlutil::RED);
        cout<<"ESE CODIGO DE AUTOR NO EXISTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }
    system("cls");
    cout<<"INGRESE EDITORIAL: ";
    cin>>editorial;
    if(verificarEditorial(editorial)==false){
        system("cls");
        rlutil::setColor(rlutil::RED);
        cout<<"ESE CODIGO DE EDITORIAL NO EXISTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }
    system("cls");
    cout<<"INGRESE PRECIO: ";
    cin>>precio;
    while(precio <= 0){
            system("cls");
            rlutil::setColor(rlutil::YELLOW);
        cout<<"INGRESE PRECIO MAYOR A 0: ";
        rlutil::setColor(rlutil::WHITE);
    cin>>precio;
    }
    system("cls");
    cout<<"INGRESE STOCK: ";
    cin>>stock;
    system("cls");
    while(stock<=0) {
            rlutil::setColor(rlutil::YELLOW);
        cout<<"INGRESE UN STOCK MAYOR A 0: ";
    rlutil::setColor(rlutil::WHITE);
        cin>>stock;
        system("cls");
    }

    system("cls");

    return true;

}

bool libros::guardarEnArchivo(){

FILE *f;
f = fopen(archivoLibros,"ab");
if(f == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(guardarachivo)"<<endl;
rlutil::setColor(rlutil::WHITE);
    fclose(f);
    return false;
}

bool x;

x = fwrite(this,sizeof(libros),1,f);

fclose(f);

return x;

}

void libros::mostrar() {

    cout<<"CODIGO: "<<codigo<<endl;
    cout<<"TITULO: "<<titulo<<endl;
    cout<<"AUTOR: "<<autor<<endl;
    cout<<"EDITORIAL: "<<editorial<<endl;
    cout<<"PRECIO: "<<precio<<endl;
    cout<<"STOCK: "<<stock<<endl;

}

float libros::getPrecio(){

return precio;

}

int libros::getStock(){

return stock;

}

void libros::restarStock(int a){
    stock = stock - a;
}

bool libros::sobreEscribir(int pos){

  FILE *f;
  f = fopen(archivoLibros,"rb+");
  if(f == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO(empleado::reactivar)"<<endl;
  rlutil::setColor(rlutil::WHITE);
    fclose(f);
    return false;
  }

  fseek(f, pos * sizeof(libros),0);
  fwrite(this,sizeof(libros),1,f);
  fclose(f);
  return true;

}


#endif // METODOSLIBROS_H_INCLUDED
