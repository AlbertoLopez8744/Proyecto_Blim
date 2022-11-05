#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>

using namespace std;
int orden = 0;
bool aux = false; // Nos servira para saber si nuestro contador esta en 0 o no
class Logg
{
public:
    char id[15];
    bool ad;
    void submit(char _id[15], bool _ad);
} userlog;
void Logg::submit(char _id[15], bool _ad)
{
    strcpy(this->id, _id);
    this->ad = _ad;
}

class ListaRepro
{
private:
    int indxContent = 0;
    char idUser[15];
    char idList[15], nameList[35], content[50][10];
    char delim = '\n';

public:
    void setList(char _idUser[15], char _idList[15], char _nameList[35]);
    void setContent(int space);
    void capturar(char _idUser[15]);
    void mostrar();
    void buscar();
    void Modificar();
    void Eliminar();
    void Mostrar_Indice();
    void Recovery();
    void ChangeCont();
} x;

class Indice
{
public:
    char idList[14];
    char idUser[15];
    char delim = '\n';
    long int pos;

} y;

int cont = 0;
void ListaRepro::Recovery()
{
    int temp;
    ifstream Archivo(".data\\CList.txt", ios::app);
    if (!Archivo.good())
    {
        cout << "\nEl archivo no existe...";
        ofstream Archivo(".data\\CList.txt", ios::app);
        Archivo << 0;
    }
    else
    {
        Archivo >> temp;
        cont = temp;
    }
    Archivo.close();
    long int tempPos;
    ifstream Top(".data\\IndListR.txt");
    if (!Top.good())
    {
    }
    else
    {
        for (int i = 0; i < cont; i++)
        {
            Top.read((char *)&y, sizeof(y));
            if (tempPos < y.pos)
            {
                tempPos = y.pos;
            }
        }
    }
    y.pos = tempPos;
    cout << y.pos << endl;
    Top.close();
}

void ListaRepro::ChangeCont()
{
    ofstream temporal(".data\\tmp.txt", ios::app);
    temporal << cont;
    temporal.close();
    remove(".data\\CList.txt");
    rename(".data\\tmp.txt", ".data\\CList.txt");
}

void ListaRepro::setList(char _idUser[15], char _idList[15], char _nameList[35])
{
    cout << _idUser << endl;
    strcpy(this->idUser, _idUser);
    strcpy(this->idList, _idList);
    strcpy(this->nameList, _nameList);
    cout << this->idUser << endl;
}

void ListaRepro::setContent(int space)
{
    char temp[50][10];
    for (int i = 0; i < space; i++)
    {
        cout << "Id #" << i + 1 << ": ";
        cin.getline(temp[i], 10);
        indxContent++;
    }
    for (int i = 0; i < space; i++)
    {
        strcpy(content[i], temp[i]);
    }
}

void ListaRepro::capturar(char _idUser[15])
{
    cout << _idUser << endl;
    indxContent = 0;
    int _space;
    char _idList[15], _nameList[35];
    cout << "    AGREGAR LISTA DE REPRODUCCION" << endl;
    cout << "------------------------------------" << endl;
    cout << "Id de la Lista:" << endl;
    cin.getline(_idList, 14);
    cout << "Dame el Nombre de la ListaRepro" << endl;
    cin.getline(_nameList, 35);
    setList(_idUser, _idList, _nameList);
    cout << "Cuantas id's agregara:" << endl;
    cin >> _space;
    cin.ignore();
    setContent(_space);
    cout << "------------------------------------" << endl;
    ofstream a(".data\\ListDatabase.txt", ios::app);
    // cout << y.pos << endl;
    if (cont)
    {
        y.pos = y.pos + sizeof(x);
    }
    else
    {
        y.pos = a.tellp();
    }
    // cout << y.pos << endl;
    a.write((char *)&x, sizeof(x));
    a.close();
    strcpy(y.idList, idList);
    strcpy(y.idUser, idUser);
    ofstream b(".data\\IndListR.txt", ios::app);
    b.write((char *)&y, sizeof(y));
    b.close();
    orden++;
    cont++;
    cout << "*********************************" << endl;
    cout << "       GUARDANDO CAMBIOS.....    " << endl
         << " POR FAVOR NO CIERRE EL PROGRAMA " << endl;
    cout << "*********************************" << endl;
}

void ListaRepro::mostrar()
{
    ifstream a(".data\\ListDatabase.txt");
    if (!a.good())
        cout << "No existe el archivo";
    else
    {
        cout << "LISTAS DE REPRODUCCION EXISTENTES" << endl
             << "----------------------------------" << endl;
        while (!a.eof())
        {
            a.read((char *)&x, sizeof(x));
            if (a.eof())
                break;
            if (strcmp(x.idUser, userlog.id) == 0 || userlog.ad == true)
            {
                if (userlog.ad == true)
                    cout << "UserID: " << x.idUser << endl;
                cout << "ID:" << x.idList << endl
                     << "Nombre: " << x.nameList << endl;
                for (int i = 0; i < indxContent; i++)
                {
                    cout << "#" << i + 1 << ": " << x.content[i] << endl;
                }
                cout << "------------------------------------" << endl;
            }
        }
    }
    a.close();
}

void ListaRepro::buscar()
{
    char idListbus[14];
    int band = 0;
    ifstream b(".data\\IndListR.txt");
    if (!b.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "\tBUSCAR" << endl
             << "----------------------------------" << endl;
        cout << "\nID de Lista de Reproduccion a buscar!" << endl;
        cin.getline(idListbus, 14);
        while (!b.eof())
        {
            b.read((char *)&y, sizeof(y));
            if (b.eof())
            {
                break;
            }
            if (strcmp(y.idUser, userlog.id) == 0 || userlog.ad == true)
            {
                if (strcmp(y.idList, idListbus) == 0)
                {
                    ifstream a(".data\\ListDatabase.txt");
                    a.seekg(y.pos, ios::beg);
                    a.read((char *)&x, sizeof(x));
                    cout << "  Lista de Reproduccion encontrada" << endl
                         << "------------------------------------" << endl;
                    cout << "ID:" << x.idList << endl
                         << "Nombre: " << x.nameList << endl;
                    for (int i = 0; i < indxContent; i++)
                    {
                        cout << "#" << i + 1 << ": " << x.content[i] << endl;
                    }
                    cout << "------------------------------------" << endl;
                    a.close();
                    band = 1;
                    break;
                }
            }
        }
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO.....";
        }
    }
    b.close();
}

void ListaRepro::Modificar()
{
    char idListmod[15];
    int band = 0;
    int opc;
    ifstream indice(".data\\IndListR.txt");
    ifstream datos(".data\\ListDatabase.txt");
    ofstream c(".data\\temp.txt", ios::app);
    ofstream d(".data\\tempind.txt", ios::app);
    if (!indice.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "             MODIFICAR" << endl
             << "----------------------------------" << endl;
        cout << "\nID de Lista de Reproduccion a modificar!" << endl;
        cin.getline(idListmod, 14);
        while (!indice.eof())
        {
            indice.read((char *)&y, sizeof(y));
            datos.read((char *)&x, sizeof(x));
            if (indice.eof())
            {
                break;
            }
            if (strcmp(y.idUser, userlog.id) == 0 || userlog.ad == true)
            {
                if (strcmp(y.idList, idListmod) == 0 && band == 0)
                {
                    cout << " Lista de Reproduccion a Modificar" << endl
                         << "------------------------------------" << endl;
                    cout << "ID:" << x.idList << endl
                         << "Nombre: " << x.nameList << endl;
                    for (int i = 0; i < indxContent; i++)
                    {
                        cout << "#" << i + 1 << ": " << x.content[i] << endl;
                    }
                    cout << "Deseas modificarlo\n"
                         << "1.-Si   2.-No" << endl
                         << "Digite la opcion->";
                    cin >> opc;
                    cout << "------------------------------------" << endl;
                    cin.ignore();
                    band = 1;
                    if (opc == 1)
                    {
                        int mod;
                        cout << "------------------------------------" << endl;
                        cout << "Que quiere modificar:" << endl
                             << "1.-Nombre   2.- Contenido(" << indxContent << ")" << endl
                             << "Digite la opcion-> ";
                        cin >> mod;
                        cout << "------------------------------------" << endl;
                        cin.ignore();
                        if (mod == 1)
                        {
                            char _nameList[35];
                            cout << "Dame el nuevo Nombre de la Lista de Reroduccion" << endl;
                            cin.getline(_nameList, 35);
                            x.setList(x.idUser, x.idList, _nameList);
                        }
                        else if (mod == 2)
                        {
                            do
                            {
                                cout << "------------------------------------" << endl;
                                cout << "Que Deseas hacer :" << endl
                                     << "1.- Insertar   2.- Modificar 3.- Eliminar 4.-Salir" << endl
                                     << "Digite la opcion-> ";
                                cin >> mod;
                                cout << "------------------------------------" << endl;
                                cin.ignore();
                                switch (mod)
                                {
                                case 1:
                                {
                                    char temp[10];
                                    if (indxContent == 10)
                                    {
                                        cout << "No se pueden ingresar mas ID's" << endl;
                                    }
                                    else
                                    {
                                        cout << "Cual es el Nuevo ID: ";
                                        cin.getline(temp, 10);
                                        strcpy(content[indxContent], temp);
                                        indxContent++;
                                    }
                                }
                                break;
                                case 2:
                                {
                                    if (!indxContent)
                                    {
                                        cout << "NO HAY DATOS" << endl;
                                    }
                                    else
                                    {
                                        int line;
                                        char temp[10];
                                        for (int i = 0; i < indxContent; i++)
                                        {
                                            cout << "pos[" << i << "] = " << x.content[i] << endl;
                                        }
                                        cout << "------------------------------------" << endl;
                                        cout << "Que posicion desea modificar: ";
                                        cin >> line;
                                        cin.ignore();
                                        cout << "ID nueva: ";
                                        cin.getline(temp, 10);
                                        strcpy(content[line], temp);
                                    }
                                }
                                break;
                                case 3:
                                {
                                    if (!indxContent)
                                    {
                                        cout << "NO HAY DATOS" << endl;
                                    }
                                    else
                                    {
                                        int line;
                                        for (int i = 0; i < indxContent; i++)
                                        {
                                            cout << "pos[" << i << "] = " << x.content[i] << endl;
                                        }
                                        cout << "------------------------------------" << endl;
                                        cout << "Que posicion desea Eliminar: ";
                                        cin >> line;
                                        cin.ignore();
                                        if (indxContent < 10)
                                        {
                                            for (int i = line; i < indxContent; i++)
                                            {
                                                strcpy(content[i], content[i + 1]);
                                            }
                                        }
                                        indxContent--;
                                    }
                                }
                                break;
                                }
                            } while (mod != 4);
                        }
                    }
                }
            }
            c.write((char *)&x, sizeof(x));
            strcpy(y.idList, idList);
            d.write((char *)&y, sizeof(y));
        } // while archivo
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO.....";
        }
    } // else
    d.close();
    c.close();
    indice.close();
    datos.close();
    cout << "*********************************" << endl;
    cout << "       GUARDANDO CAMBIOS.....    " << endl
         << " POR FAVOR NO CIERRE EL PROGRAMA " << endl;
    cout << "*********************************" << endl;
    remove(".data\\IndListR.txt");
    rename(".data\\tempind.txt", ".data\\IndListR.txt");
    remove(".data\\ListDatabase.txt");
    rename(".data\\temp.txt", ".data\\ListDatabase.txt");
}

void ListaRepro::Eliminar()
{
    char idListeli[15];
    int band = 0;
    int opc, cont1 = 0, cont2 = 0;
    long int tempPos;
    ifstream b(".data\\IndListR.txt");
    if (!b.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "             ELIMINAR             " << endl
             << "----------------------------------" << endl;
        cout << " ID de Lista de Reproduccion a eliminar!" << endl;
        cin.getline(idListeli, 14);
        while (!b.eof())
        {
            b.read((char *)&y, sizeof(y));
            cont1++;
            if (b.eof())
            {
                break;
            }
            if (strcmp(y.idUser, userlog.id) == 0 || userlog.ad == true)
            {
                if (strcmp(y.idList, idListeli) == 0)
                {
                    ifstream a(".data\\ListDatabase.txt");
                    a.seekg(y.pos, ios::beg);
                    a.read((char *)&x, sizeof(x));
                    if (a.eof())
                        break;
                    cout << "  Lista de Reproduccion a Eliminar  " << endl
                         << "------------------------------------" << endl;
                    cout << "ID:" << x.idList << endl
                         << "Nombre: " << x.nameList << endl;
                    for (int i = 0; i < indxContent; i++)
                    {
                        cout << "#" << i + 1 << ": " << x.content[i] << endl;
                    }
                    cout << "Deseas eliminarla" << endl
                         << "1.-Si   2.-No" << endl
                         << "Digite la opcion-> ";
                    cin >> opc;
                    band = 1;
                    tempPos = y.pos;
                    a.close();
                    break;
                } // if de comparacion
            }
        } // while
        b.close();
        if (opc == 1)
        {
            ifstream indice(".data\\IndListR.txt");
            ifstream datos(".data\\ListDatabase.txt");
            while (!indice.eof())
            {
                indice.read((char *)&y, sizeof(y));
                datos.read((char *)&x, sizeof(x));
                if (indice.eof())
                {
                    break;
                }
                if (strcmp(y.idUser, userlog.id) == 0 || userlog.ad == true)
                {
                    if (strcmp(y.idList, idListeli))
                    {
                        cont2++;
                        ofstream c(".data\\temp.txt", ios::app);
                        c.write((char *)&x, sizeof(x));
                        strcpy(y.idList, idList);
                        if (tempPos < y.pos)
                        {
                            y.pos = y.pos - sizeof(x);
                        }
                        ofstream d(".data\\tempind.txt", ios::app);
                        d.write((char *)&y, sizeof(y));
                        d.close();
                        c.close();
                    }
                }
            } // while archivo
            indice.close();
            datos.close();
            remove(".data\\IndListR.txt");
            rename(".data\\tempind.txt", ".data\\IndListR.txt");
            remove(".data\\ListDatabase.txt");
            rename(".data\\temp.txt", ".data\\ListDatabase.txt");
        } // if
        else
        {
        }
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO.....";
        }
        cont--;
    } // else
    cout << "*********************************" << endl;
    cout << "       GUARDANDO CAMBIOS.....    " << endl
         << " POR FAVOR NO CIERRE EL PROGRAMA " << endl;
    cout << "*********************************" << endl;
}

void ListaRepro::Mostrar_Indice()
{
    ifstream a(".data\\IndListR.txt");
    if (!a.good())
        cout << "No existe el archivo";
    else
    {
        while (!a.eof())
        {
            a.read((char *)&y, sizeof(y));
            if (a.eof())
                break;
            cout << "          Lista de Indices          " << endl
                 << "------------------------------------" << endl;
            cout << "Indice:" << y.idList << endl
                 << "Posicion en elArchivo: " << y.pos << endl
                 << endl;
        }
    }
    a.close();
}

void menuL(char _id[15], bool _ad)
{
    cout << _id << endl;
    userlog.submit(_id, _ad);
    int opc;
    do
    {
        system("cls");
        cout << "   Menu de Lista de Reproduccion    " << endl
             << "------------------------------------" << endl;
        cout << "Selecciona una de la siguientes opciones:" << endl
             << "1.- Agregar" << endl
             << "2.- Buscar" << endl
             << "3.- Mostrar todas listas" << endl
             << "4.- Modificar" << endl
             << "5.- Eliminar" << endl
             << "6.- Mostrar Indice" << endl
             << "7.- Salir" << endl
             << "Digite la opcion-> ";
        cin >> opc;
        cin.ignore();
        cout << "------------------------------------" << endl;
        switch (opc)
        {
        case 1:
            x.capturar(userlog.id);
            break;
        case 2:
            x.buscar();
            break;
        case 3:
            x.mostrar();
            break;
        case 4:
            x.Modificar();
            break;
        case 5:
            x.Eliminar();
            break;
        case 6:
            x.Mostrar_Indice();
            break;
        }
        x.ChangeCont();
        if(opc != 7)
            system("Pause");
    } while (opc != 7);
}