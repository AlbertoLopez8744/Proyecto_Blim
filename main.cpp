#include <iostream>
#include "includes/Usuario.cpp"
using namespace std;

void Recovery(){
    listR.Recovery();
}

int main(){
    Recovery();
    system("cls");
    bool out = false;
    do
    {
        cout<<"\tBIENVENIDO A BLIM"<<endl
        <<"1) Iniciar sesion"<<endl
        <<"2) Registrarse"<<endl
        <<"3) Salir"<<endl;
        cout<<"Opcion-> ";
        int opc;
        cin>>opc;cin.ignore();
        if(opc==1){
            OrdCom.LogIn();
        }else if(opc==2){
            OrdCom.Agregar();
        }else if(opc>3){
            cout<<"OPCION INVALIDA"<<endl;
        }else if(opc==3){
            cout<<"SALIENDO"<<endl;
            out = true;
        }
        system("pause");
        system("cls");
    } while (!out);
    return 0;
}