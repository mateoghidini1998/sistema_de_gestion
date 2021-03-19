#ifndef METODOSAUTORES_H_INCLUDED
#define METODOSAUTORES_H_INCLUDED

char const archivoAutores[30] = {"autores.dat"};

class autor {
private:

    int codigo;
    char nombre[20];
    char apellido[20];
    char nacionalidad[40];
    char generoP [20];
    bool estado;

public:

    autor() {
        estado = true;
    }
    bool cargar();
    void mostrar();
    bool guardarEnArchivo();
    bool sobreEscribir(int);
    bool leerDeDisco(int pos);
    int guardarEnBackUp();
    void setEstado(bool);
    bool getEstado();
    int getCodigo();
    void mostrarNombre() {
        cout<<nombre<<" "<<apellido<<endl;
    }
};

int autor::guardarEnBackUp(){
FILE *f;
f = fopen("autoresBackUp.dat","ab");
int a;
a = fwrite(this,sizeof(autor),1,f);
fclose(f);
return a;

}

bool autor::leerDeDisco(int pos) {
    FILE *f;
    f = fopen(archivoAutores,"rb");
    if(f == NULL)
        return false;
    fseek(f,pos*sizeof(autor),0);
    if(fread(this,sizeof(autor),1,f)==true) {
        fclose(f);
        return true;
    }
    fclose(f);
    return false;

}

bool verificarCodigo(int);

bool autor::cargar() {
    cout<<"INGRESE NOMBRE DEL AUTOR: ";
    cin>>nombre;
    cout<<"INGRESE APELLIDO: ";
    cin>>apellido;
    cout<<"INGRESE CODIGO: ";
    cin>>codigo;
    if(verificarCodigo(codigo)== false) {
        rlutil::setColor(rlutil::YELLOW);
        cout<<"ESE CODIGO YA EXISTE"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        system("cls");
        return false;
    }
    cin.ignore();
    cout<<"INGRESE NACIONALIDAD: ";
    cin.getline(nacionalidad,40);
    cout<<"INGRESE EL GENERO PRINCIPAL: ";
    cin>>generoP;
    system("cls");
    return true;
}

void autor::mostrar() {
    cout<<"CODIGO: ";
    cout<<codigo<<endl;
    cout<<"NOMBRE DEL AUTOR: ";
    cout<<nombre<<endl;
    cout<<"APELLIDO: ";
    cout<<apellido<<endl;
    cout<<"NACIONALIDAD: ";
    cout<<nacionalidad<<endl;
    cout<<"GENERO PRINCIPAL: ";
    cout<<generoP<<endl;
}

bool autor::guardarEnArchivo() {

    FILE *f;
    f = fopen(archivoAutores,"ab+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(guardarachivo)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        system("pause");
        fclose(f);
        return false;
    }

    bool x;

    x = fwrite(this,sizeof(autor),1,f);
    fclose(f);

    return x;

}

int autor::getCodigo() {
    return codigo;
}

void autor::setEstado(bool x) {
    estado = x;
}

bool autor::getEstado() {
    return estado;
}

bool autor::sobreEscribir(int pos) {

    FILE *f;
    f = fopen(archivoAutores,"rb+");
    if(f == NULL) {
        rlutil::setColor(rlutil::RED);
        cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO(autor::reactivar)"<<endl;
        rlutil::setColor(rlutil::WHITE);
        fclose(f);
        return false;
    }

    fseek(f, pos * sizeof(autor),0);
    fwrite(this,sizeof(autor),1,f);
    fclose(f);
    return true;

}



#endif // METODOSAUTORES_H_INCLUDED
