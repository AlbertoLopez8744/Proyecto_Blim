#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>

using namespace std;
int orden = 0;
bool aux = false; // Nos servira para saber si nuestro contador esta en 0 o no

class Historial
{
private:
    int indxContent = 0;
    char idUser[15], nameList[35], content[10][10];
    char delimitador = '\n';

public:
    void setList(char _idUser[15], char _nameList[35]);
    void setContent(int space);
    void capturar();
    void mostrar();
    void buscar();
    void Modificar();
    void Eliminar();
    void Recovery();
    void ChangeCont();
} x;

int cont = 0;
void Historial::Recovery()
{
    int temp;
    ifstream Archivo("Cont.bin", ios::binary);
    if (!Archivo.good())
    {
        cout << "\nEl archivo no existe...";
        ofstream Archivo("Cont.bin", ios::binary);
        Archivo << 0;
    }
    else
    {
        Archivo >> temp;
        cont = temp;
    }
    Archivo.close();
}

void Historial::ChangeCont()
{
    ofstream temporal("temporal.bin", ios::binary);
    temporal << cont;
    temporal.close();
    remove("Cont.bin");
    rename("temporal.bin", "Cont.bin");
}

void Historial::setList(char _idUser[15], char _nameList[35])
{
    strcpy(idUser, _idUser);
    strcpy(nameList, _nameList);
}

void Historial::setContent(int space)
{
    char temp[10][10];
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

void Historial::capturar()
{
    ifstream b("datos.bin");
    ofstream a("tempdatos.bin", ios::binary);
    for (int i = 0; i < cont; i++)
    {
        b.read((char *)&x, sizeof(x));
        a.write((char *)&x, sizeof(x));
    }
    indxContent = 0;
    int _space;
    char _idUser[15], _nameList[35];

    cout << "    AGREGAR LISTA DE REPRODUCCION" << endl;
    cout << "------------------------------------" << endl;
    cout << "Id de la Lista:" << endl;
    cin.getline(_idUser, 14);
    cout << "Dame el Nombre de la Historial" << endl;
    cin.getline(_nameList, 35);
    setList(_idUser, _nameList);
    cout << "Cuantas id's agregara:" << endl;
    cin >> _space;
    cin.ignore();
    setContent(_space);
    cout << "------------------------------------" << endl;
    a.write((char *)&x, sizeof(x));
    a.close();
    b.close();
    remove("datos.bin");
    rename("tempdatos.bin", "datos.bin");
    cont++;
    cout << "*********************************" << endl;
    cout << "       GUARDANDO CAMBIOS.....    " << endl
         << " POR FAVOR NO CIERRE EL PROGRAMA " << endl;
    cout << "*********************************" << endl;
}

void Historial::mostrar()
{
    ifstream a("datos.bin");
    if (!a.good())
        cout << "No existe el archivo"<<endl;
    else
    {
        cout << "LISTAS DE REPRODUCCION EXISTENTES" << endl
             << "----------------------------------" << endl;
        while (!a.eof())
        {
            a.read((char *)&x, sizeof(x));
            if (a.eof())
                break;
            cout << "ID:" << x.idUser << endl
                 << "Nombre: " << x.nameList << endl;
            for (int i = 0; i < indxContent; i++)
            {
                cout << "#" << i + 1 << ": " << x.content[i] << endl;
            }
            cout << "------------------------------------" << endl;
        }
    }
    a.close();
}

void Historial::buscar()
{
    char idUserbus[14];
    int band = 0;
    ifstream a("datos.bin");
    if (!a.good())
    {
        cout << "No existe el archivo"<<endl;
    }
    else
    {
        cout << "\tBUSCAR" << endl
             << "----------------------------------" << endl;
        cout << "\nID de Lista de Reproduccion a buscar!" << endl;
        cin.getline(idUserbus, 14);
        while (!a.eof())
        {
            a.read((char *)&x, sizeof(x));
            if (a.eof())
            {
                break;
            }
            if (strcmp(x.idUser, idUserbus) == 0)
            {
                cout << "  Lista de Reproduccion encontrada" << endl
                     << "------------------------------------" << endl;
                cout << "ID:" << x.idUser << endl
                     << "Nombre: " << x.nameList << endl;
                for (int i = 0; i < indxContent; i++)
                {
                    cout << "#" << i + 1 << ": " << x.content[i] << endl;
                }
                cout << "------------------------------------" << endl;
                band = 1;
                break;
            }
        }
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO....."<<endl;
        }
    }
    a.close();
}

void Historial::Modificar()
{
    char idUsermod[15];
    int band = 0;
    int opc;
    ifstream datos("datos.bin");
    ofstream c("temp.bin", ios::binary);
    if (!datos.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "             MODIFICAR" << endl
             << "----------------------------------" << endl;
        cout << "\nID de Lista de Reproduccion a modificar!" << endl;
        cin.getline(idUsermod, 14);
        while (!datos.eof())
        {
            datos.read((char *)&x, sizeof(x));
            if (datos.eof())
            {
                break;
            }
            if (strcmp(x.idUser, idUsermod) == 0 && band == 0)
            {
                cout << " Lista de Reproduccion a Modificar" << endl
                     << "------------------------------------" << endl;
                cout << "ID:" << x.idUser << endl
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
                        x.setList(x.idUser, _nameList);
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
            c.write((char *)&x, sizeof(x));
        } // while archivo
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO....."<<endl;
        }
    } // else
    c.close();
    datos.close();
    cout << "*********************************" << endl;
    cout << "       GUARDANDO CAMBIOS.....    " << endl
         << " POR FAVOR NO CIERRE EL PROGRAMA " << endl;
    cout << "*********************************" << endl;
    remove("datos.bin");
    rename("temp.bin", "datos.bin");
}

void Historial::Eliminar()
{
    char idUsereli[15];
    bool band = false;
    long int tempPos;
    ifstream a("datos.bin");
    ofstream temp("tempData.bin", ios::binary);

    if (!a.good())
    {
        cout << "No existe el archivo"<<endl;
    }
    else
    {
        cout << "             ELIMINAR             " << endl
             << "----------------------------------" << endl;
        cout << " ID de Lista de Reproduccion a eliminar!" << endl;
        cin.getline(idUsereli, 14);
        while (!a.eof())
        {
            int opc = 0;
            a.read((char *)&x, sizeof(x));
            if (a.eof())
            {
                break;
            }
            if (strcmp(x.idUser, idUsereli) == 0)
            {
                if (a.eof())
                    break;
                cout << "  Lista de Reproduccion a Eliminar  " << endl
                     << "------------------------------------" << endl;
                cout << "ID:" << x.idUser << endl
                     << "Nombre: " << x.nameList << endl;
                for (int i = 0; i < indxContent; i++)
                {
                    cout << "#" << i + 1 << ": " << x.content[i] << endl;
                }
                cout << "Deseas eliminarla" << endl
                     << "1.-Si   2.-No" << endl
                     << "Digite la opcion-> ";
                cin >> opc;
                band = true;

            } // if de comparacion
            if (opc == 1)
            {
                cont--;
            }
            else
            {
                temp.write((char *)&x, sizeof(x));
            }
        } // while

        if (!band)
        {
            cout << "\n NO EXISTE REGISTRO....."<<endl;
        }
    } // else
    a.close();
    temp.close();
    remove("datos.bin");
    rename("tempData.bin","datos.bin");
    cout << "*********************************" << endl;
    cout << "       GUARDANDO CAMBIOS.....    " << endl
         << " POR FAVOR NO CIERRE EL PROGRAMA " << endl;
    cout << "*********************************" << endl;
}

int main()
{
    x.Recovery();
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
             << "6.- Salir" << endl
             << "Digite la opcion-> ";
        cin >> opc;
        cin.ignore();
        cout << "------------------------------------" << endl;
        switch (opc)
        {
        case 1:
            x.capturar();
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
        }
        x.ChangeCont();
        _sleep(600);
        system("Pause");
    } while (opc != 6);
    return 0;
}