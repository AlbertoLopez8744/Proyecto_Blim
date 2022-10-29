#include <stdlib.h>
#include "iostream"
#include "fstream"
#include "cstring"

using namespace std;

class Series
{
public:
    char codigo[10], nombre[100], temporadas[15], capitulos[15], descripcion[200], publicObj[15];
    char delim = '\n';
    bool checkID(char *);
    void Agregar();
    void Mostrar();
    void Modificar();
    void Eliminar();
    void Buscar();
    void menu();
    void setters(char *, char *, char *, char *, char *, char *);
} serie;

int opc = 0;

bool Series::checkID(char *_codigo)
{
    bool band = false;
    string buffer1;
    string buffer2;
    buffer1 = _codigo;
    ifstream arc(".data\\Series.txt");
    if (!arc.good())
    {
        // cout << "\nEl archivo no existe";
    }
    else
    {
        while (!arc.eof())
        {
            arc.read((char *)&serie, sizeof(serie));
            buffer2 = codigo;
            if (arc.eof())
                break;
            if (buffer1 == buffer2)
            {
                cout << "Se encontraron coincidencias por favor intente con otro codigo" << endl;
                band = true;
            }
        }
    }
    arc.close();
    return band;
}
void Series::setters(char *_codigo, char *_nombre, char *_temporadas, char *_capitulos, char *_descripcion, char *_publicObj)
{
    strcpy(this->codigo, _codigo);
    strcpy(this->nombre, _nombre);
    strcpy(this->descripcion, _descripcion);
    strcpy(this->temporadas, _temporadas);
    strcpy(this->capitulos, _capitulos);
    strcpy(this->publicObj, _publicObj);
}
void Series::Agregar()
{
    bool verified = false;
    char _codigo[10], _nombre[100], _temporadas[15], _capitulos[15], _descripcion[200], _publicObj[15];
    do
    {

        cout << "ESCRIBE EL CODIGO DE LA SERIE: ";
        cin.getline(_codigo, 10);
        verified = checkID(_codigo);
    } while (verified);
    cout << "ESCRIBE EL NOMBRE DE LA SERIE: ";
    cin.getline(_nombre, 100);
    cout << "ESCRIBE LA DESCRIPCION DE LA SERIE: ";
    cin.getline(_descripcion, 200);
    cout << "ESCRIBE EL NUMERO DE TEMPORADAS: ";
    cin.getline(_temporadas, 15);
    cout << "ESCRIBE EL NUMERO DE CAPITULOS: ";
    cin.getline(_capitulos, 15);
    cout << "ESCRIBE EL PUBLICO OBJETIVO: ";
    cin.getline(_publicObj, 15);
    setters(_codigo, _nombre, _temporadas, _capitulos, _descripcion, _publicObj);
    ofstream Archivo(".data\\Series.txt", ios::app);
    Archivo.write((char *)&serie, sizeof(serie));

    Archivo.close();
}
void Series::Mostrar()
{
    system("cls");

    ifstream archivo(".data\\Series.txt");
    if (!archivo.good())
    {
        cout << "\nEl archivo no existe...";
    }
    else
    {
        while (!archivo.eof())
        {
            archivo.read((char *)&serie, sizeof(serie)); // dim1 contiene el tama o de la cadena que se quiere leer
            if (archivo.eof())
                break;
            cout << "Codigo: " << codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl
                 << endl;
        }
    }
    archivo.close();
}
void Series::Modificar()
{
    int band = 0;
    char codigo2[10];

    ifstream archivo(".data\\Series.txt");
    ofstream temporal(".data\\temporal.txt", ios::app);
    if (!archivo.good())
    {
        cout << "\nEl archivo no existe...";
    }
    else
    {
        cout << "escribe el codigo del producto: ";
        cin.getline(codigo2, 10);
        while (!archivo.eof())
        {
            archivo.read((char *)&serie, sizeof(serie)); // dim1 contiene el tama o de la cadena que se quiere leer
            if (archivo.eof())
                break;
            if (strcmp(codigo2, codigo) == 0)
            {
                cout << "Codigo: " << codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl
                     << endl;
                cout << "DESEA MODIFICAR?\n1.SI\n0.NO\n>: ";
                cin >> opc;
                cin.ignore();
                if (opc == 1)
                {
                    int opcion = 0;
                    cout << endl
                         << "Codigo : " << codigo << endl
                         << "Nombre : " << nombre << endl
                         << "Descripcion : " << descripcion << endl
                         << "#Temporadas #" << temporadas << endl
                         << "#Capitulos #" << capitulos << endl
                         << "Clasificacion : " << publicObj << endl
                         << "   Que desea realizar ? " << endl
                         << "(1) Modificar Nombre: " << endl
                         << "(2) Modificar Descripcion: " << endl
                         << "(3) Modificar # Temporadas: " << endl
                         << "(4) Modificar # Capitulos" << endl
                         << "(5) Modificar Clasificacion: " << endl
                         << "(6) Regresar: " << endl
                         << "Elige la opcion a realizar: ";
                    cin >> opcion;
                    cin.ignore();
                    switch (opcion)
                    {

                    case 1: //////Nombre
                        cout << "ESCRIBE EL NOMBRE DE LA SERIE: ";
                        cin.getline(nombre, 100);
                        break;
                    case 2: /// Descripcion
                        cout << "ESCRIBE LA DESCRIPCION DE LA SERIE: ";
                        cin.getline(descripcion, 200);
                        break;
                    case 3: /// Temporadas
                        cout << "ESCRIBE EL NUMERO DE TEMPORADAS: ";
                        cin.getline(temporadas, 15);
                        break;
                    case 4: /// Capitulos
                        cout << "ESCRIBE EL NUMERO DE CAPITULOS: ";
                        cin.getline(capitulos, 15);
                        break;
                    case 5: /// Clasificacion
                        cout << "ESCRIBE EL PUBLICO OBJETIVO: ";
                        cin.getline(publicObj, 15);
                        break;
                    default:
                        cout << "\n No se encontro la opcion ";
                    }
                }
            }
            temporal.write((char *)&serie, sizeof(serie));
        }
    }
    temporal.close();
    archivo.close();
    remove(".data\\Series.txt");
    rename(".data\\temporal.txt", ".data\\Series.txt");
}

void Series::Eliminar()
{
    int band = 0;
    char codigo2[10];

    ifstream archivo(".data\\Series.txt");
    if (!archivo.good())
    {
        cout << "\nEl archivo no existe...";
    }
    else
    {
        cout << "CODIGO QUE QUIERES ELIMINAR: ";
        cin.getline(codigo2, 10);
        while (!archivo.eof() && !band)
        {
            archivo.read((char *)&serie, sizeof(serie)); // dim1 contiene el tama o de la cadena que se quiere leer
            if (archivo.eof())
                break;
            if (strcmp(codigo2, codigo) == 0)
            {
                cout << "Codigo: " << codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl
                     << endl;
                band = 1;
                cout << "DESEAS ELIMINAR?\n1.- SI\n0.- NO\n>: ";
                cin >> opc;
                cin.ignore();
            } // condicion

        } // ciclo
        archivo.close();

        if (opc == 1)
        {
            int i = 0;
            ifstream archivo(".data\\Series.txt");
            ofstream temporal(".data\\temporal.txt", ios::app);
            while (!archivo.eof())
            {
                archivo.read((char *)&serie, sizeof(serie));
                if (archivo.eof())
                    break;
                if (strcmp(codigo2, codigo) != 0)
                {
                    temporal.write((char *)&serie, sizeof(serie));
                } // condicion
                i++;
            } // ciclo while
            temporal.close();
            archivo.close();
            remove(".data\\Series.txt");
            rename(".data\\temporal.txt", ".data\\Series.txt");
        } // condicional de la opcion
    }     //
}

void Series::Buscar()
{
    char codigo2[10];
    int band = 0;
    system("cls");

    ifstream archivo(".data\\Series.txt");
    if (!archivo.good())
    {
        cout << "\nEl archivo no existe...";
    }
    else
    {
        cout << "escribe el codigo del producto que quieres buscar: ";
        cin.getline(codigo2, 10);
        while (!archivo.eof() && !band)
        {
            archivo.read((char *)&serie, sizeof(serie)); // dim1 contiene el tama o de la cadena que se quiere leer
            if (archivo.eof())
                break;
            if (strcmpi(codigo2, codigo) == 0)
            {
                cout << "Codigo: " << codigo << "\nNombre: " << nombre << "\nDescripcion: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl
                     << endl;
                band = 1;
            }
        }
        if (!band)
            cout << "NO SE ENCUENTRA EL PRODUCTO..." << endl;
    }
    archivo.close();
}
void adminSeries()
{
    cout << "\n\n\t\tMENU SERIES ADMIN\n\n";
    do
    {
        cout << "\n\tSELECCIONE LA OPCION DESEADA\n1.- AGREGAR\n2.- MOSTRAR\n3.- BUSCAR\n4.- MODIFICAR\n5.- ELIMINAR\n6.- SALIR\n>: ";
        cin >> opc;
        cin.ignore();
        switch (opc)
        {
        case 1:
            serie.Agregar();
            break;
        case 2:
            serie.Mostrar();
            break;
        case 3:
            serie.Buscar();
            break;
        case 4:
            serie.Modificar();
            break;
        case 5:
            serie.Eliminar();
            break;
        case 6:
            cout << "Datos guardados y cerrando......" << endl;
            break;
        default:
            cout << "OPCION INCORRECTA...." << endl;
        }
        system("Pause");
        system("cls");
    } while (opc != 6);
    return;
}

void userSeries()
{
    cout << "\n\n\t\tMENU SERIES ADMIN\n\n";
    do
    {
        cout << "\n\tSELECCIONE LA OPCION DESEADA\n1.- AGREGAR\n2.- MOSTRAR\n3.- BUSCAR\n4.- MODIFICAR\n5.- ELIMINAR\n6.- SALIR\n>: ";
        cin >> opc;
        cin.ignore();
        switch (opc)
        {
        case 1:
            serie.Agregar();
            break;
        case 2:
            serie.Mostrar();
            break;
        case 3:
            serie.Buscar();
            break;
        case 4:
            serie.Modificar();
            break;
        case 5:
            serie.Eliminar();
            break;
        case 6:
            cout << "Datos guardados y cerrando......" << endl;
            break;
        default:
            cout << "OPCION INCORRECTA...." << endl;
        }
        system("Pause");
        system("cls");
    } while (opc != 6);
    return;
}
