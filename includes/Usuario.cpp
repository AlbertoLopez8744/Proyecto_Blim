#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string.h>
#include "Peliculas.cpp"
#include "Series.cpp"
#include "ListasRep.cpp"

using namespace std;
bool typeLog;
void menuUser();
void menuAdmin();
class Logged
{
public:
    char id[15];
    char userName[30];
    char password[35];
    bool t;
    char delim = '\n';
    void submit(char *, char *, char *, bool);
} userLog;

void Logged::submit(char *_id, char *_user, char *_password, bool _t)
{
    strcpy(this->id, _id);
    strcpy(this->userName, _user);
    strcpy(this->password, _password);
    this->t = _t;
}

class Users
{

private:
    char id[15];
    char userName[30];
    char password[35];
    char delim = '\n';

public:
    bool admin = false;
    void setters(char *_id, char *_user, char *_password);
    void setUser(char *_user);
    void setPass(char *_password);
    string getUser();
    bool checkUser(char *user);
    bool checkID(char *_id);
    void Agregar();
    void Mostrar();
    void Modificar();
    void Buscar();
    void Eliminar();
    bool checkLog();
    void LogIn();
    void menuAdmin();
    void menuUser();
} OrdCom;

void Users::setters(char *_id, char *_user, char *_password)
{
    strcpy(this->id, _id);
    strcpy(this->userName, _user);
    strcpy(this->password, _password);
}
void Users::setUser(char *_user)
{
    strcpy(this->userName, _user);
}
void Users::setPass(char *_password)
{
    strcpy(this->password, _password);
}
string Users::getUser()
{
    return OrdCom.userName;
}
bool Users::checkUser(char *user)
{
    bool band = false;
    string buffer1;
    string buffer2;
    buffer1 = user;
    ifstream archivo(".data\\users.txt", ios::in);
    if (!archivo.good())
    {
        cout << "No se encontro el archivo" << endl;
    }
    else
    {
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            buffer2 = userName;
            if (archivo.eof())
            {
                break;
            }
            if (buffer1 == buffer2)
            {
                cout << "Se encontraron coincidencias" << endl;
                band = true;
            }
        }
    }
    archivo.close();
    return band;
}
bool Users::checkID(char *_id)
{
    bool band = false;
    string buffer1;
    string buffer2;
    buffer1 = _id;
    ifstream archivo(".data\\users.txt", ios::in);
    if (!archivo.good())
    {
        cout << "No se encontro el archivo" << endl;
    }
    else
    {
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            buffer2 = id;
            if (archivo.eof())
            {
                break;
            }
            if (buffer1 == buffer2)
            {
                cout << "Se encontraron coincidencias" << endl;
                band = true;
            }
        }
    }
    archivo.close();
    return band;
}
void Users::Agregar()
{
    char buffer[15];
    char buffer1[30];
    char buffer2[35];
    bool verifyA = false, verifyB = false;
    cout << "GENERAR USUARIO NUEVO" << endl;
    do
    {
        cout << "ID: ";
        cin.getline(buffer, 15);
        verifyA = checkID(buffer);
        if (verifyA)
        {
            cout << "ID repetido intente con otro..." << endl;
        }
    } while (verifyA);
    do
    {
        cout << "Username: ";
        cin.getline(buffer1, 30);
        verifyB = checkUser(buffer1);
        if (verifyB)
        {
            cout << "Username repetido intente con otro..." << endl;
        }
    } while (verifyB);
    cout << "Password: ";
    cin.getline(buffer2, 35);
    setters(buffer, buffer1, buffer2);
    OrdCom.admin = false;
    ofstream archivo;
    archivo.open(".data\\users.txt", ios::app);
    archivo.write((char *)&OrdCom, sizeof(OrdCom));
    archivo.close();
}
void Users::Mostrar()
{

    ifstream archivo;
    archivo.open(".data\\users.txt", ios::in);
    if (!archivo.good())
    {
        cout << "\n El archivo no existe....." << endl;
    }
    else
    {
        cout << "USUARIOS EXISTENTES" << endl;
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            if (archivo.eof())
            {
                break;
            }
            cout << "ID: " << id << endl;
            cout << "Usuario: " << userName << endl;
            cout << "Password: " << password << endl;
            cout << "" << endl;
        }
        archivo.close();
    }
}
void Users::Modificar()
{
    char valor[15];
    ifstream archivo(".data\\users.txt");
    if (!archivo.good())
    {
        cout << "\n El archivo no existe....." << endl;
    }
    else
    {
        cout << "MODIFICAR USUARIO" << endl;
        if (typeLog)
        {
            cout << "Ingrese el ID a modificar: ";
            cin.getline(valor, 15);
        }
        else
        {
            strcpy(valor, userLog.id);
        }
        ofstream archivo2(".data\\Utemporal.txt", ios::app);
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            if (archivo.eof())
            {
                break;
            }
            if (strcmp(id, valor) == 0)
            {
                strcpy(OrdCom.id, valor);
                char buffer[35];
                cout << "Usuario: " << userName << endl;
                if (!typeLog)
                {
                    cout << "Ingrese su password: ";
                    cin.getline(buffer, 35);
                }
                else
                {
                    strcpy(buffer, password);
                }
                if (strcmp(buffer, password) == 0)
                {
                    int opc = 0;
                    while (opc != 3)
                    {
                        cout << "Que desea modificar" << endl
                             << "1) Username\t2)Password" << endl
                             << "3) Cancelar" << endl
                             << "Ingrese una opcion: ";
                        cin >> opc;
                        cin.ignore();
                        switch (opc)
                        {
                        case 1:
                        {
                            char aux[30];
                            bool verify = false;
                            do
                            {
                                cout << "Nuevo Username: ";
                                cin.getline(aux, 30);
                                verify = checkUser(aux);
                                if (verify)
                                {
                                    cout << "Username repetido intente con otro..." << endl;
                                }
                            } while (verify);
                            setUser(aux);
                        }
                        break;
                        case 2:
                        {
                            char aux[35];
                            char aux2[35];
                            bool verify = false;
                            do
                            {
                                cout << "Nuevo Password: ";
                                cin.getline(aux, 35);
                                cout << "Confirmar Password: ";
                                cin.getline(aux2, 35);
                                if (strcmp(aux, aux2) == 0)
                                {
                                    verify = true;
                                }
                                else
                                {
                                    cout << "Los passwords no coinciden\nIntente nuevamente" << endl;
                                }
                            } while (!verify);

                            setPass(aux);
                        }
                        break;
                        default:
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Se acabaron los intentos" << endl;
                    archivo2.close();
                    remove(".data\\Utemporal.txt");
                    return;
                }
                ofstream archivo(".data\\users.txt", ios::app);
                archivo2.write((char *)&OrdCom, sizeof(OrdCom));
            }
            else
            {
                archivo2.write((char *)&OrdCom, sizeof(OrdCom));
            }
        }
        archivo.close();
        archivo2.close();
        remove(".data\\users.txt");
        rename(".data\\Utemporal.txt", ".data\\users.txt");
    }
}
void Users::Eliminar()
{
    char valor[15];
    int opcion = 0;
    ifstream archivo(".data\\users.txt");
    if (!archivo.good())
    {
        cout << "\n El archivo no existe....." << endl;
    }
    else
    {
        cout << "ELIMINAR USUARIO" << endl;
        cout << "Ingrese el ID a eliminar: ";
        cin.getline(valor, 15);
        ofstream archivo2(".data\\Utemporal.txt", ios::app);
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            if (archivo.eof())
            {
                break;
            }
            if (strcmp(id, valor) == 0)
            {
                cout << "\tUsuario Encontrada" << endl;
                cout << "ID: " << id << endl;
                cout << "Fecha: " << userName << endl;
                cout << "Password: " << password << endl;
                cout << "DESEAS ELIMINAR?\n1.- SI\n0.- NO\n>: ";
                cin >> opcion;
                cin.ignore();
                if (opcion == 1)
                {
                }
                else
                {
                    archivo2.write((char *)&OrdCom, sizeof(OrdCom));
                }
            }
            else
            {
                archivo2.write((char *)&OrdCom, sizeof(OrdCom));
            }
        }
        archivo.close();
        archivo2.close();
        remove(".data\\users.txt");
        char oldname[] = ".data\\Utemporal.txt";
        char newname[] = ".data\\users.txt";
        rename(oldname, newname);
    }
}
void Users::Buscar()
{
    char valor[15];
    bool find = false;
    ifstream archivo(".data\\users.txt", ios::in);
    if (!archivo.good())
    {
        cout << "\n El archivo no existe....." << endl;
    }
    else
    {
        cout << "BUSCAR USUARIO" << endl;
        cout << "Ingrese el ID a buscar: ";
        cin.getline(valor, 15);
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            if (archivo.eof())
            {

                break;
            }
            if (strcmp(id, valor) == 0)
            {
                find = true;
                cout << "\tUsuario Encontrada" << endl;
                cout << "ID: " << id << endl;
                cout << "Fecha: " << userName << endl;
                cout << "Password: " << password << endl;
            }
        }
        if (!find)
        {
            cout << "Usuario no encontrada" << endl;
        }
    }
    archivo.close();
}
bool Users::checkLog()
{
    char valor[30];
    bool find = false;
    ifstream archivo(".data\\users.txt", ios::in);
    if (!archivo.good())
    {
        cout << "\n El archivo no existe....." << endl;
    }
    else
    {
        cout << "INICIAR SESION" << endl;
        cout << "Username: ";
        cin.getline(valor, 30);
        while (!archivo.eof())
        {
            archivo.read((char *)&OrdCom, sizeof(OrdCom));
            if (archivo.eof())

                break;
            if (strcmp(userName, valor) == 0)
            {
                find = true;
                char buffer[35];
                cout << "Password: ";
                cin.getline(buffer, 35);
                if (strcmp(password, buffer))
                {
                    cout << "INVALID PASSWORD" << endl;
                    return false;
                }

                // cout<<this->admin<<"  "<<OrdCom.admin<<endl;
                if (this->admin)
                {
                    userLog.submit(this->id, this->userName, this->password, true);
                    typeLog = true;
                }
                else if (!this->admin)
                {
                    userLog.submit(this->id, this->userName, this->password, false);
                    typeLog = false;
                }
                system("pause");
            }
        }
        if (!find)
        {
            cout << "Usuario no encontrada" << endl;
        }
    }
    archivo.close();
    return find;
}
void Users::LogIn()
{
    int opc = 0;
    do
    {
        bool log = false;
        log = OrdCom.checkLog();
        if (log)
        {
            // cout<<"Debug: Inicio de Sesion exitoso"<<endl;
            if (!typeLog)
                OrdCom.menuUser();
            if (typeLog)
                OrdCom.menuAdmin();
            return;
        }
        else if (!log)
        {
            cout << "Desea intentar nuevamente?" << endl
                 << "1) Si           2)No" << endl
                 << "-> ";
            cin >> opc;
            cin.ignore();
            if (opc == 2)
            {
                return;
            }
        }
        // OrdCom.Mostrar();
    } while (opc != 2);
}
void Users::menuAdmin()
{
    int op;
    do
    {
        system("cls");
        cout << "MENU DE ADMIN" << endl;
        cout << "1.-Agregar" << endl;
        cout << "2.-Imprimir Usuarios" << endl;
        cout << "3.-Modificar " << endl;
        cout << "4.-Eliminar" << endl;
        cout << "5.-Buscar " << endl;
        cout << "6.-Peliculas" << endl;
        cout << "7.-Series" << endl;
        cout << "8.-Listas de reproduccion" << endl;
        cout << "9.-Historiales de usuario" << endl;
        cout << "10.-Pagos" << endl;
        cout << "11.-Facturas" << endl;
        cout << "12.-Cerrar Sesion " << endl;
        cout << "Ingresa la opcion->";
        cin >> op;
        cin.ignore();
        switch (op)
        {
        case 1:
            system("cls");
            OrdCom.Agregar();
            system("pause");
            break;
        case 2:
            system("cls");
            OrdCom.Mostrar();
            system("pause");
            break;
        case 3:
            system("cls");
            OrdCom.Modificar();
            system("pause");
            break;
        case 4:
            system("cls");
            OrdCom.Eliminar();
            system("pause");
            break;
        case 5:
            system("cls");
            OrdCom.Buscar();
            system("pause");
            break;
        case 6:
            system("cls");
            movies.adminMovies();
            system("pause");
            break;
        case 7:
            system("cls");
            serie.adminSeries();
            system("pause");
            break;
        case 8:
            system("cls");
            cout<<userLog.id<<endl;
            listR.menuL(userLog.id,true);
            system("pause");
            break;
        }
    } while (op != 12);
    return;
}

void Users::menuUser()
{
    int op;
    do
    {
        system("cls");
        cout << "BIENVENIDO " << userLog.userName << endl;
        cout << "1.-Ver Peliculas" << endl;
        cout << "2.-Ver Series" << endl;
        cout << "3.-Listas de Reproduccion " << endl;
        cout << "4.-Historial" << endl;
        cout << "5.-Buscar " << endl;
        cout << "6.-Configuracion cuenta" << endl;
        cout << "7.-Cerrar Sesion " << endl;
        cout << "Ingresa la opcion->";
        cin >> op;
        cin.ignore();
        switch (op)
        {
        case 1:
            system("cls");
            movies.userMovies();
            break;
        case 2:
            system("cls");
            serie.userSeries();
            break;
        case 3:
            system("cls");
            listR.menuL(userLog.id,false);
            //cout << "ESTAMOS TRABAJANDO EN ELLO <3" << endl;
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "ESTAMOS TRABAJANDO EN ELLO <3" << endl;
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "ESTAMOS TRABAJANDO EN ELLO <3" << endl;
            system("pause");
            break;
        case 6:
            system("cls");
            OrdCom.Modificar();
            system("pause");
            break;
        }
    } while (op != 7);
    return;
}