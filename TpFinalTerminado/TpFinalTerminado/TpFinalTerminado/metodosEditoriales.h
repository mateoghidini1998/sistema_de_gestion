#ifndef METODOSEDITORIALES_H_INCLUDED
#define METODOSEDITORIALES_H_INCLUDED

const char ArchivoEditoriales [30] = {"editoriales.dat"};

class editoriales {

private:
    char nombre[35];
    int codigo;
    char pais [40];
    char ciudad [30];
    bool estado;

public:
    editoriales(){
        estado = true;
    };
    bool cargar();
    void mostrar();
    bool guardarEnArchivo();
    bool leerDeDisco(int pos);
    int getCodigo(){return codigo;}
    void setEstado(bool x){estado = x;}
    bool getEstado(){return estado;}
    void setCodigo(int a){codigo = a;}
    bool sobreEscribir(int);
    int guardarEnBackUp();
};

int editoriales::guardarEnBackUp(){
FILE *f;
f = fopen("editorialesBackUp.dat","ab");
int a;
a = fwrite(this,sizeof(editoriales),1,f);
fclose(f);
return a;

}

bool editoriales::leerDeDisco(int pos){
FILE *f;
f = fopen(ArchivoEditoriales,"rb");
if(f == NULL)
    return false;
fseek(f,pos*sizeof(editoriales),0);
if(fread(this,sizeof(editoriales),1,f)==true){
fclose(f);
    return true;
}
fclose(f);
return false;

}

bool editoriales::cargar() {
    FILE *f;
    editoriales aux;
    f = fopen(ArchivoEditoriales, "ab+");
    if(f == NULL){
            rlutil::setColor(rlutil::RED);
        cout<<"EL ARCHIVO NO SE PUDO ABRIR CORRECTAMENTE"<<endl;
    rlutil::setColor(rlutil::WHITE);
        return false;
    }
    cin.ignore();
    cout<<"INGRESE NOMBRE: ";
    cin.getline(nombre,35);
    system("cls");
    cout<<"INGRESE CODIGO: ";
    cin>>codigo;
    while(fread(&aux,sizeof(editoriales),1,f)==1) {
        while(aux.getCodigo() == codigo){
         system("cls");
         rlutil::setColor(rlutil::YELLOW);
         cout<<"INGRESE OTRO CODIGO, ESE YA ESTA EN USO"<<endl;
         rlutil::setColor(rlutil::WHITE);
            cin>>codigo;
            system("cls");
        }
    }
    fclose(f);
    system("cls");
    cin.ignore();
    cout<<"INGRESE PAIS: ";
    cin.getline(pais,40);
    system("cls");

    cout<<"INGRESE CIUDAD: ";
    cin.getline(ciudad,30);
    system("cls");
    return true;
}

void editoriales::mostrar() {
    cout<<"NOMBRE: "<<nombre<<endl;
    cout<<"CODIGO: "<<codigo<<endl;
    cout<<"PAIS: "<<pais<<endl;
    cout<<"CIUDAD: "<<ciudad<<endl;
}

bool editoriales::guardarEnArchivo(){
FILE *f;
f = fopen(ArchivoEditoriales,"ab");
if(f == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR EL ARCHIVO CORRECTAMENTE(guardarachivo)"<<endl;
rlutil::setColor(rlutil::WHITE);
    return false;
}

bool x;

x = fwrite(this,sizeof(editoriales),1,f);

fclose(f);

return x;

}

bool editoriales::sobreEscribir(int pos){
  FILE *f;
  f = fopen(ArchivoEditoriales,"rb+");
  if(f == NULL){
        rlutil::setColor(rlutil::RED);
    cout<<"NO SE PUDO ABRIR CORRECTAMENTE EL ARCHIVO(editoriales::reacitvar)"<<endl;
  rlutil::setColor(rlutil::WHITE);
    fclose(f);
    return false;
  }

  fseek(f, pos * sizeof(editoriales),0);
  fwrite(this,sizeof(editoriales),1,f);
  fclose(f);
  return true;
}


#endif // METODOSEDITORIALES_H_INCLUDED
