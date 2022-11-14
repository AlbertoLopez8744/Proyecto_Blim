#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string.h>
#include "Pagos.cpp"
#include "Peliculas.cpp"
#include "Series.cpp"
#include "ListasRep.cpp"
#include "HistorialUsuario.cpp"
int cl = 10;
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
    void setID(char *_id);
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
    void ver(bool tipo);
    void userMovies();
    void userSeries();
    void userPagos();
    void menuAdmin();
    void menuUser();
    void getHistorial(char _id[15]);
    void showHistorial();
    char *cifrar(char *, int);
    char *descifrar(char *, int);
} OrdCom;
char *Users::cifrar(char *t, int clave)
{
    int size = strlen(t);
    // cout<<"SIZE: " <<size <<endl
    //<< "Sin: "<< t << endl;
    for (int i = 0; i < size; i++)
    {
        t[i] += clave;
    }
    // cout<<"Con: "<< t;
    // system("pause");

    return t;
}
char *Users::descifrar(char *t, int clave)
{
    return cifrar(t, -clave);
}
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
void Users::setID(char *_id)
{
    // cout << _id <<endl;
    strcpy(this->id, _id);
    // cout << this->id <<endl;
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
            descifrar(userName, cl);
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
            descifrar(id, cl);
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
    cifrar(buffer, cl);
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
    cifrar(buffer1, cl);
    cout << "Password: ";
    cin.getline(buffer2, 35);
    cifrar(buffer2, cl);
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
            descifrar(id, cl);
            cout << "ID: " << id << endl;
            descifrar(userName, cl);
            cout << "Usuario: " << userName << endl;
            descifrar(password, cl);
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
            setID(descifrar(id, cl));
            setUser(descifrar(userName, cl));
            setPass(descifrar(password, cl));
            if (archivo.eof())
            {
                break;
            }
            if (strcmp(id, valor) == 0)
            {
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
                    bool modic = false;
                    bool modic1 = false;
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
                            setUser(cifrar(aux, cl));
                            modic = true;
                            modic1 = true;
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

                            setPass(cifrar(aux, cl));
                            modic = true;
                        }
                        break;
                        case 3:
                            if (modic == false)
                            {
                                setUser(cifrar(userName, cl));
                                setPass(cifrar(password, cl));
                                modic1 = true;
                            }
                            break;
                        default:

                            break;
                        }
                    }
                    // cout << "Valor: " << valor << endl;
                    setID(cifrar(valor, cl));
                    if (modic1 == false)
                    {
                        setUser(cifrar(userName, cl));
                    }
                }
                else
                {
                    cout << "Se acabaron los intentos" << endl;
                    archivo2.close();
                    remove(".data\\Utemporal.txt");
                    return;
                }
                cout << "Debug: " << userName << " / " << password << endl;
                ofstream archivo(".data\\users.txt", ios::app);
                archivo2.write((char *)&OrdCom, sizeof(OrdCom));
            }
            else
            {
                setID(cifrar(id, cl));
                setUser(cifrar(userName, cl));
                setPass(cifrar(password, cl));
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
            descifrar(id, cl);
            if (archivo.eof())
            {
                break;
            }
            if (strcmp(id, valor) == 0)
            {
                cout << "\tUsuario Encontrada" << endl;
                cout << "ID: " << id << endl;
                descifrar(userName, cl);
                cout << "Fecha: " << userName << endl;
                descifrar(password, cl);
                cout << "Password: " << password << endl;
                cout << "DESEAS ELIMINAR?\n1.- SI\n0.- NO\n>: ";
                cin >> opcion;
                cin.ignore();
                if (opcion == 1)
                {
                }
                else
                {
                    cifrar(id, cl);
                    cifrar(userName, cl);
                    cifrar(password, cl);
                    archivo2.write((char *)&OrdCom, sizeof(OrdCom));
                }
            }
            else
            {
                cifrar(id, cl);
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
            descifrar(id, cl);
            if (archivo.eof())
            {

                break;
            }
            if (strcmp(id, valor) == 0)
            {
                find = true;
                cout << "\tUsuario Encontrada" << endl;
                cout << "ID: " << id << endl;
                descifrar(userName, cl);
                cout << "Fecha: " << userName << endl;
                descifrar(password, cl);
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
            descifrar(id, cl);
            descifrar(userName, cl);
            if (archivo.eof())

                break;
            if (strcmp(userName, valor) == 0)
            {
                find = true;
                char buffer[35];
                cout << "Password: ";
                cin.getline(buffer, 35);
                descifrar(password, cl);
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
    Pago adminPay;
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
        cout << "11.-Cerrar Sesion " << endl;
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
            cout << userLog.id << endl;
            listR.menuL(userLog.id, true);
            system("pause");
            break;
        case 9:
        {
            int h;
            system("cls");
            do
            {    
                h = historial.hAdmin();
                if (h == 3)
                {
                    OrdCom.showHistorial();
                    system("pause");
                }
            } while (h);
            
        }
        break;
        case 10:
            system("cls");
            adminPay.AdminPay();
            break;
        }
    } while (op != 11);
    return;
}

void Users::menuUser()
{
    Pago userPay;
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
        cout << "6.-Pago" << endl;
        cout << "7.-Configuracion cuenta" << endl;
        cout << "8.-Cerrar Sesion " << endl;
        cout << "Ingresa la opcion->";
        cin >> op;
        cin.ignore();
        switch (op)
        {
        case 1:
            system("cls");
            OrdCom.userMovies();
            break;
        case 2:
            system("cls");
            OrdCom.userSeries();
            break;
        case 3:
            system("cls");
            listR.menuL(userLog.id, false);
            // cout << "ESTAMOS TRABAJANDO EN ELLO <3" << endl;
            system("pause");
            break;
        case 4:
            system("cls");
            OrdCom.getHistorial(userLog.id);
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
        case 7:
            system("cls");
            userPay.AdminPay();
            system("Pause");
        }
    } while (op != 8);
    return;
}

void Users::userMovies()
{
    int op;
    do
    {
        cout << endl
             << "MENU PELICULAS" << endl
             << "[1] CATALOGO" << endl
             << "[2] BUSCAR" << endl
             << "[3] VER" << endl
             << "[4] SALIR" << endl
             << "-> ";
        cin >> op;
        cin.ignore();
        switch (op)
        {
        case 1:
            movies.Imprimir();
            system("pause");
            system("cls");
            break;
        case 2:
            movies.Buscar();
            system("pause");
            system("cls");
            break;
        case 3:
            OrdCom.ver(true);
            system("pause");
            system("cls");
            break;
        }
    } while (op != 4);
    return;
}

void Users::userSeries()
{
    do
    {
        cout << "\n\n\t\tMENU SERIES \n\n";
        cout << "\n\tSELECCIONE LA OPCION DESEADA" << endl
             << "[1] CATALOGO" << endl
             << "[2] BUSCAR" << endl
             << "[3] VER" << endl
             << "[4] SALIR" << endl
             << "-> ";
        cin >> opc;
        cin.ignore();
        switch (opc)
        {
        case 1:
            serie.Mostrar();
            break;
        case 2:
            serie.Buscar();
            break;
        case 3:
            OrdCom.ver(false);
            break;
        default:
            cout << "OPCION INCORRECTA...." << endl;
        }
        system("Pause");
        system("cls");
    } while (opc != 4);
    return;
}

void Users::ver(bool tipo)
{
    int opc;
    char _tipo;
    cout << "Que deseas hacer?" << endl
         << "[ 1 ] Ingresar ID a ver" << endl
         << "[ 2 ] Mostrar catalogo" << endl
         << "[ 3 ] Salir" << endl
         << "-> ";
    cin >> opc;
    cin.ignore();
    if (opc == 3)
    {
        return;
    }
    char watch[10];
    if (opc == 2)
    {
        if (tipo)
        {
            movies.Imprimir();
        }
        else
        {
            serie.Mostrar();
        }
    }
    cout << "Ingresa ID: ";
    cin.getline(watch, 10);
    if (tipo)
    {
        if (movies.checkID(watch) == false)
        {
            cout << "El ID no existe" << endl;
            return;
        }
        _tipo = 'M';
    }
    else
    {
        if (serie.checkID(watch) == false)
        {
            cout << "El ID no existe" << endl;
            return;
        }
        _tipo = 'S';
    }
    historial.setContent(userLog.id, watch, _tipo);
}

void Users::getHistorial(char _id[15])
{
    int band = 0;
    ifstream a(".data\\datos.bin");
    if (!a.good())
    {
        cout << "No existe el archivo" << endl;
    }
    else
    {
        while (!a.eof())
        {
            a.read((char *)&historial, sizeof(historial));
            if (a.eof())
            {
                break;
            }
            if (strcmp(historial.userID, _id) == 0)
            {
                cout << "  HISTORIAL DEL ID #" << historial.userID << endl
                     << "------------------------------------" << endl;
                cout << "N : Tipo / ID --> Nombre" << endl;
                for (int i = 0; i < historial.indxContent; i++)
                {
                    cout << "#" << i + 1 << ": " << historial.tipo[i] << " / " << historial.content[i] << " --> ";
                    if (historial.tipo[i] == 'S')
                    {
                        cout << serie.getSerie(historial.content[i]) << endl;
                    }
                    else if (historial.tipo[i] == 'M')
                    {
                        cout << movies.getMovie(historial.content[i]) << endl;
                    }
                }
                cout << "------------------------------------" << endl;
                band = 1;
                break;
            }
        }
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO....." << endl;
        }
    }
    a.close();
}

void Users::showHistorial()
{
    ifstream a(".data\\datos.bin");
    if (!a.good())
        cout << "No existe el archivo" << endl;
    else
    {
        cout << "HISTORIALES EXISTENTES" << endl
             << "----------------------------------" << endl;
        while (!a.eof())
        {
            a.read((char *)&historial, sizeof(historial));
            if (a.eof())
                break;
            cout << "ID:" << historial.userID << endl;
            cout << "N : Tipo / ID --> Nombre" << endl;
            for (int i = 0; i < historial.indxContent; i++)
            {
                cout << "#" << i + 1 << ": " << historial.tipo[i] << " / " << historial.content[i] << " --> ";
                if (historial.tipo[i] == 'S')
                {
                    cout << serie.getSerie(historial.content[i]) << endl;
                }
                else if (historial.tipo[i] == 'M')
                {
                    cout << movies.getMovie(historial.content[i]) << endl;
                }
            }
            cout << "------------------------------------" << endl;
        }
    }
    a.close();
}