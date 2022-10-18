#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
class Movie
{
public:
    char codigo[35], nombre[100], descripcion[200], time[15], publicObj[15];
    char delim = '\n';
    void Capturar();
    bool VerificarData(char codigo[35]);
    void Imprimir();
    void Buscar();
    void Eliminar();
    void Modificar();
} movies;
void Movie::Capturar()
{
    do
    {
        cout << "\nCodigo: ";
        fflush(stdin);
        cin.getline(codigo, 35);
    } while (VerificarData(codigo));
    cout << "\nNombre: ";
    fflush(stdin);
    cin.getline(nombre, 100);
    cout << "\nDescripcion: ";
    fflush(stdin);
    cin.getline(descripcion, 200);
    cout << "\nTime: ";
    fflush(stdin);
    cin.getline(time, 15);
    cout << "\nClasificacion: ";
    fflush(stdin);
    cin.getline(publicObj, 15);
    ofstream archivo("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt", ios::app);
    archivo.write((char *)&movies, sizeof(movies));
    archivo.close();
}
bool Movie::VerificarData(char codigo[35])
{
    char prev[35];
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    if (!arc.good())
        cout << "\nEl archivo no existe";
    else
    {
        while (!arc.eof())
        {
            arc.read((char *)&movies, sizeof(movies));
            if (arc.eof())
                break;
            if (strcmp(prev, codigo) == 0)
            {
                arc.close();
                cout << "Se encontraron coincidencias por favor intente con otro codigo";
                return true;
            }
        }
    }
    arc.close();
    return false;
}
void Movie::Imprimir()
{
    int i;
    ifstream Lectura("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    if (!Lectura.good())
    {
        cout << "No existe el archivo\n";
        system("pause");
    }
    else
    {
        cout << "PELICULAS EXISTENTES" << endl;
        while (!Lectura.eof())
        {
            Lectura.read((char *)&movies, sizeof(movies));
            if (Lectura.eof())
                break;
            cout << endl
                 << "Codigo: " << codigo << endl
                 << "Nombre: " << nombre << endl
                 << "Descripcion: " << descripcion << endl
                 << "Duracion: " << time << endl
                 << "Clasificacion: " << publicObj << endl;
        }
        system("pause");
    }
    Lectura.close();
}
void Movie::Buscar()
{
    char ref[35], prev[35];
    int band = 1;
    cout << "\nEscribe el codigo de la Pelicula a buscar \n";
    fflush(stdin);
    cin.getline(ref, 35);
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    if (!arc.good())
        cout << "\nEl archivo no existe";
    else
    {
        while (!arc.eof() && band == 1)
        {
            arc.read((char *)&movies, sizeof(movies));
            if (arc.eof())
                break;
            if (strcmp(prev, ref) == 0)
            {
                cout << "\nCodigo: " << codigo;
                cout << "\nNombre: " << nombre;
                cout << "\nDescripcion: " << descripcion;
                cout << "\nDuracion: " << time;
                cout << "\nClasificaion: " << publicObj << endl;
                band = 0;
            }
        }
        if (band)
            cout << "\nNo se encontro el Movie";
    }
    arc.close();
}
void Movie::Eliminar()
{
    int i;
    int opcion;
    char prodMod[10];
    bool b;
    int resp;
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    ofstream arcTemp("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\temporalauto.txt", ios::app);
    if (!arc.good())
        cout << "\n EL REGISTRO NO EXISTE \n ";
    else
    {
        cout << "\n Introduce el codigo a Eliminar  :  " << endl;
        cin.getline(prodMod, 35);
        b = false;
        while (!arc.eof())
        {
            arc.read((char *)&movies, sizeof(movies));
            if (strcmp(codigo, prodMod) == 0 && !b)
            {
                cout << "Se encontro una coincidencia" << endl;
                cout << "\nCodigo: " << codigo;
                cout << "\nNombre: " << nombre;
                cout << "\nDescripcion: " << descripcion;
                cout << "\nDuracion: " << time;
                cout << "\nClasificaion: " << publicObj << endl;
                cout << "¿Quiere eliminarlo?" << endl;
                cout << "1=si   2=no" << endl;
                cin >> resp;
                cin.ignore();
                if (resp == 2)
                {
                    arcTemp.write((char *)&movies, sizeof(movies));
                }
                else
                {
                    cout << "Se ha eliminado correctamente" << endl;
                    b = true;
                }
            }
            else
            {
                arcTemp.write((char *)&movies, sizeof(movies));
            }
        }
        arc.close();
        arcTemp.close();
        if (!b)
            cout << "\n No se encontro arhcivo ";
        remove("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
        rename("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\temporalauto.txt", "C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    }
}
void Movie::Modificar()
{
    int i;
    int opcion;
    char prodMod[10];
    bool b;
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    ofstream arcTemp("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\temporalauto.txt", ios::app);
    if (!arc.good())
        cout << "\n EL REGISTRO NO EXISTE \n ";
    else
    {
        cout << "\n Introduce el codigo a modificar :  ";
        cin.getline(prodMod, 35);
        b = false;
        while (!arc.eof())
        {
            arc.read((char*)&movies, sizeof(movies));
            if (arc.eof())
                break;
            if (strcmp(codigo, prodMod) == 0 && !b)
            {
                cout << endl
                     << "Codigo : " << codigo << endl
                     << "Nombre : " << nombre << endl
                     << "Descripcion : " << descripcion << endl
                     << "Duracion : " << time << endl
                     << "Clasificacion : " << publicObj << endl
                     << "   Que desea realizar ? " << endl
                     << "(1) Modificar Codigo: " << endl
                     << "(2) Modificar Nombre: " << endl
                     << "(3) Modificar Descripcion: " << endl
                     << "(4) Modificar Duracion: " << endl
                     << "(5) Modificar Clasificacion: " << endl
                     << "(6) Regresar: " << endl
                     << "Elige la opcion a realizar: ";
                cin >> opcion;
                cin.ignore();
                switch (opcion)
                {
                case 1: ///////codigo
                    cout << "\n Codigo : ";
                    cin.getline(codigo, 35);
                    break;
                case 2: //////nombre
                    cout << "\n Nombre : ";
                    cin.getline(nombre, 100);
                    break;
                case 3: /// Descripcion
                    cout << "\n Descripcion : ";
                    cin.getline(descripcion, 200);
                    break;
                case 4: /// Duracion
                    cout << "\n Duracion : ";
                    cin.getline(time, 15);
                    break;
                case 5: /// Clasificacion
                    cout << "\n Clasificacion : ";
                    cin.getline(publicObj, 15);
                    break;
                case 6:
                    b = true;
                    break;
                default:
                    cout << "\n No se encontro la opcion ";
                }
                if (opcion != 6 && opcion > 0 && opcion < 7)
                    b = true;
            }
            arcTemp.write((char*)&movies, sizeof(movies));
        }
        arc.close();
        arcTemp.close();
        if (!b)
            cout << "\n No se encontro arhcivo ";
        remove("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
        rename("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\temporalauto.txt", "C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    }
}
void menuAdminMovies()
{
    int op;
    do
    {
        cout << "\nIngresa el numero de la opcion: \n1.Capturar \n2.Imprimir todo \n3.Buscar \n4.Eliminar \n5.Modificar \n6.Salir\n";
        cin >> op;
        cin.ignore();
        switch (op)
        {
        case 1:
            movies.Capturar();
            system("pause");
            system("cls");
            break;
        case 2:
            movies.Imprimir();
            system("cls");
            break;
        case 3:
            movies.Buscar();
            system("pause");
            system("cls");
            break;
        case 4:
            movies.Eliminar();
            system("pause");
            system("cls");
            break;
        case 5:
            movies.Modificar();
            system("pause");
            system("cls");
        }
    } while (op != 6);
    return;
}
