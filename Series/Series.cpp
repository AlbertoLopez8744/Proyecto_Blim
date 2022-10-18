#include <stdlib.h>
#include "iostream"
#include "fstream"
#include "cstring"

using namespace std;

class Series
{
public:
    char codigo[10], nombre[100], temporadas[15], capitulos[15], descripcion[200], publicObj[15];
    // public:
    void Agregar();
    void Mostrar();
    void Modificar();
    void Eliminar();
    void Buscar();
    void menu();
    void Recovery();
    void ChangeCont();
} pr;

int dim1, dim2, dim3, dim4, dim5, dim6, opc = 0;
int cont = 0;
void Series::Recovery()
{
    int temp;
    ifstream Archivo("Cont.txt", ios::app);
    if (!Archivo.good())
    {
        cout << "\nEl archivo no existe...";
        ofstream Archivo("Cont.txt", ios::app);
        Archivo << 0;
        return;
    }
    else
    {
        Archivo >> temp;
        cont = temp;
    }
    Archivo.close();
}
void Series::ChangeCont()
{
    ofstream temporal("temporal.txt", ios::app);
    temporal << cont;
    temporal.close();
    remove("Cont.txt");
    rename("temporal.txt", "Cont.txt");
}

void Series::Agregar()
{

    cout << "ESCRIBE EL CODIGO DE LA SERIE: ";
    cin.getline(codigo, 10);
    cout << "ESCRIBE EL NOMBRE DE LA SERIE: ";
    cin.getline(nombre, 100);
    cout << "ESCRIBE LA DESCRIPCION DE LA SERIE: ";
    cin.getline(descripcion, 200);
    cout << "ESCRIBE EL NUMERO DE TEMPORADAS: ";
    cin.getline(temporadas, 15);
    cout << "ESCRIBE EL NUMERO DE CAPITULOS: ";
    cin.getline(capitulos, 15);
    cout << "ESCRIBE EL PUBLICO OBJETIVO: ";
    cin.getline(publicObj, 15);
    ofstream Archivo("Series.txt", ios::app);
    dim1 = strlen(codigo);
    dim2 = strlen(nombre);
    dim3 = strlen(descripcion);
    dim4 = strlen(temporadas);
    dim5 = strlen(capitulos);
    dim6 = strlen(publicObj);
    Archivo.write((char *)&dim1, sizeof(int));
    Archivo.write((char *)&codigo, dim1);
    Archivo.write((char *)&dim2, sizeof(int));
    Archivo.write((char *)&nombre, dim2);
    Archivo.write((char *)&dim3, sizeof(int));
    Archivo.write((char *)&descripcion, dim3);
    Archivo.write((char *)&dim4, sizeof(int));
    Archivo.write((char *)&temporadas, dim4);
    Archivo.write((char *)&dim5, sizeof(int));
    Archivo.write((char *)&capitulos, dim5);
    Archivo.write((char *)&dim6, sizeof(int));
    Archivo.write((char *)&publicObj, dim6);

    Archivo.close();
    cont++;
}
void Series::Mostrar()
{
    system("cls");

    ifstream archivo("Series.txt");
    if (!archivo.good())
    {
        cout << "\nEl archivo no existe...";
    }
    else
    {
        int i = 0;
        while (!archivo.eof() && i < cont)
        {
            archivo.read((char *)&dim1, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&codigo, dim1);
            codigo[dim1] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim2, sizeof(int));
            archivo.read((char *)&nombre, dim2);
            nombre[dim2] = '\0';
            archivo.read((char *)&dim3, sizeof(int));
            archivo.read((char *)&descripcion, dim3);
            descripcion[dim3] = '\0';
            archivo.read((char *)&dim4, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&temporadas, dim4);
            temporadas[dim4] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim5, sizeof(int));
            archivo.read((char *)&capitulos, dim5);
            capitulos[dim5] = '\0';
            archivo.read((char *)&dim6, sizeof(int));
            archivo.read((char *)&publicObj, dim6);
            publicObj[dim6] = '\0';
            cout << "Codigo: " <<  codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl<< endl;
            i++;
        }
    }
    archivo.close();
}

void Series::Modificar()
{
    int band = 0;
    char codigo2[10];

    ifstream archivo("Series.txt");
    if (!archivo.good())
    {
        cout << "\nEl archivo no existe...";
    }
    else
    {
        cout << "escribe el codigo del producto: ";
        cin.getline(codigo2, 10);
        while (!archivo.eof() && !band)
        {
            archivo.read((char *)&dim1, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&codigo, dim1);
            codigo[dim1] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim2, sizeof(int));
            archivo.read((char *)&nombre, dim2);
            nombre[dim2] = '\0';
            archivo.read((char *)&dim3, sizeof(int));
            archivo.read((char *)&descripcion, dim3);
            descripcion[dim3] = '\0';
            archivo.read((char *)&dim4, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&temporadas, dim4);
            temporadas[dim4] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim5, sizeof(int));
            archivo.read((char *)&capitulos, dim5);
            capitulos[dim5] = '\0';
            archivo.read((char *)&dim6, sizeof(int));
            archivo.read((char *)&publicObj, dim6);
            publicObj[dim6] = '\0';

            if (strcmp(codigo2, codigo) == 0)
            {
                cout << "Codigo: " <<  codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl<< endl;
                band = 1;
                cout << "DESEA MODIFICAR?\n1.SI\n0.NO\n>: ";
                cin >> opc;
                cin.ignore();
            } // condicion

        } // ciclo
        archivo.close();

        if (opc == 1)
        {
            int i = 0;
            ifstream archivo("Series.txt");
            ofstream temporal("temporal.txt", ios::app);
            while (!archivo.eof() && i < cont)
            {
                archivo.read((char *)&dim1, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
                archivo.read((char *)&codigo, dim1);
                codigo[dim1] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
                archivo.read((char *)&dim2, sizeof(int));
                archivo.read((char *)&nombre, dim2);
                nombre[dim2] = '\0';
                archivo.read((char *)&dim3, sizeof(int));
                archivo.read((char *)&descripcion, dim3);
                descripcion[dim3] = '\0';
                archivo.read((char *)&dim4, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
                archivo.read((char *)&temporadas, dim4);
                temporadas[dim4] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
                archivo.read((char *)&dim5, sizeof(int));
                archivo.read((char *)&capitulos, dim5);
                capitulos[dim5] = '\0';
                archivo.read((char *)&dim6, sizeof(int));
                archivo.read((char *)&publicObj, dim6);
                publicObj[dim6] = '\0';

                if (strcmp(codigo2, codigo) == 0)
                {
                    cout << "ESCRIBE EL CODIGO DE LA SERIE: ";
                    cin.getline(codigo, 10);
                    cout << "ESCRIBE EL NOMBRE DE LA SERIE: ";
                    cin.getline(nombre, 100);
                    cout << "ESCRIBE LA DESCRIPCION DE LA SERIE: ";
                    cin.getline(descripcion, 200);
                    cout << "ESCRIBE EL NUMERO DE TEMPORADAS: ";
                    cin.getline(temporadas, 15);
                    cout << "ESCRIBE EL NUMERO DE CAPITULOS: ";
                    cin.getline(capitulos, 15);
                    cout << "ESCRIBE EL PUBLICO OBJETIVO: ";
                    cin.getline(publicObj, 15);
                    dim1 = strlen(codigo);
                    dim2 = strlen(nombre);
                    dim3 = strlen(descripcion);
                    dim4 = strlen(temporadas);
                    dim5 = strlen(capitulos);
                    dim6 = strlen(publicObj);
                } // condicion
                temporal.write((char *)&dim1, sizeof(int));
                temporal.write((char *)&codigo, dim1);
                temporal.write((char *)&dim2, sizeof(int));
                temporal.write((char *)&nombre, dim2);
                temporal.write((char *)&dim3, sizeof(int));
                temporal.write((char *)&descripcion, dim3);
                temporal.write((char *)&dim4, sizeof(int));
                temporal.write((char *)&temporadas, dim4);
                temporal.write((char *)&dim5, sizeof(int));
                temporal.write((char *)&capitulos, dim5);
                temporal.write((char *)&dim6, sizeof(int));
                temporal.write((char *)&publicObj, dim6);
                i++;
            } // ciclo while

            temporal.close();
            archivo.close();
            remove("Series.txt");
            rename("temporal.txt", "Series.txt");
        } // condicional de la opcion

    } // else
}

void Series::Eliminar()
{
    int band = 0;
    char codigo2[10];

    ifstream archivo("Series.txt");
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
            archivo.read((char *)&dim1, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&codigo, dim1);
            codigo[dim1] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim2, sizeof(int));
            archivo.read((char *)&nombre, dim2);
            nombre[dim2] = '\0';
            archivo.read((char *)&dim3, sizeof(int));
            archivo.read((char *)&descripcion, dim3);
            descripcion[dim3] = '\0';
            archivo.read((char *)&dim4, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&temporadas, dim4);
            temporadas[dim4] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim5, sizeof(int));
            archivo.read((char *)&capitulos, dim5);
            capitulos[dim5] = '\0';
            archivo.read((char *)&dim6, sizeof(int));
            archivo.read((char *)&publicObj, dim6);
            publicObj[dim6] = '\0';
            if (strcmp(codigo2, codigo) == 0)
            {
                cout << "Codigo: " <<  codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl<< endl;
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
            ifstream archivo("Series.txt");
            ofstream temporal("temporal.txt", ios::app);
            while (!archivo.eof() && i < cont)
            {
                archivo.read((char *)&dim1, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
                archivo.read((char *)&codigo, dim1);
                codigo[dim1] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
                archivo.read((char *)&dim2, sizeof(int));
                archivo.read((char *)&nombre, dim2);
                nombre[dim2] = '\0';
                archivo.read((char *)&dim3, sizeof(int));
                archivo.read((char *)&descripcion, dim3);
                descripcion[dim3] = '\0';
                archivo.read((char *)&dim4, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
                archivo.read((char *)&temporadas, dim4);
                temporadas[dim4] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
                archivo.read((char *)&dim5, sizeof(int));
                archivo.read((char *)&capitulos, dim5);
                capitulos[dim5] = '\0';
                archivo.read((char *)&dim6, sizeof(int));
                archivo.read((char *)&publicObj, dim6);
                publicObj[dim6] = '\0';

                if (strcmp(codigo2, codigo) != 0)
                {
                    temporal.write((char *)&dim1, sizeof(int));
                    temporal.write((char *)&codigo, dim1);
                    temporal.write((char *)&dim2, sizeof(int));
                    temporal.write((char *)&nombre, dim2);
                    temporal.write((char *)&dim3, sizeof(int));
                    temporal.write((char *)&descripcion, dim3);
                    temporal.write((char *)&dim4, sizeof(int));
                    temporal.write((char *)&temporadas, dim4);
                    temporal.write((char *)&dim5, sizeof(int));
                    temporal.write((char *)&capitulos, dim5);
                    temporal.write((char *)&dim6, sizeof(int));
                    temporal.write((char *)&publicObj, dim6);
                } // condicion
                i++;
            } // ciclo while

            temporal.close();
            archivo.close();
            remove("Series.txt");
            rename("temporal.txt", "Series.txt");
            cont--;
        } // condicional de la opcion

    } //
}

void Series::Buscar()
{
    char codigo2[10];
    int band = 0;
    system("cls");

    ifstream archivo("Series.txt");
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
            archivo.read((char *)&dim1, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&codigo, dim1);
            codigo[dim1] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim2, sizeof(int));
            archivo.read((char *)&nombre, dim2);
            nombre[dim2] = '\0';
            archivo.read((char *)&dim3, sizeof(int));
            archivo.read((char *)&descripcion, dim3);
            descripcion[dim3] = '\0';
            archivo.read((char *)&dim4, sizeof(int)); // dim1 contiene el tama o de la cadena que se quiere leer
            archivo.read((char *)&temporadas, dim4);
            temporadas[dim4] = '\0'; // asignar fin de cadena al arreglo usuario para que no imprima basura
            archivo.read((char *)&dim5, sizeof(int));
            archivo.read((char *)&capitulos, dim5);
            capitulos[dim5] = '\0';
            archivo.read((char *)&dim6, sizeof(int));
            archivo.read((char *)&publicObj, dim6);
            publicObj[dim6] = '\0';
            if (strcmpi(codigo2, codigo) == 0)
            {
                cout << "Codigo: " <<  codigo << "\nNombre: " << nombre << "\nDescripcio: " << descripcion << "\nTemporadas:  " << temporadas << "\nCapitulos: " << capitulos << "\nPublico Objetivo: " << publicObj << endl<< endl;
                band = 1;
            }
        }
        if (!band)
            cout << "NO SE ENCUENTRA EL PRODUCTO..." << endl;
    }
    archivo.close();
}
int main()
{
    pr.Recovery();
    cout << "\n\n\t\tBIENVENIDO AL MENU PRODUCTOS\n\n";
    do
    {
        cout << "\n\tSELECCIONE LA OPCION DESEADA\n1.- AGREGAR\n2.- MOSTRAR\n3.- BUSCAR\n4.- MODIFICAR\n5.- ELIMINAR\n6.- SALIR\n>: ";
        cin >> opc;
        cin.ignore();
        switch (opc)
        {
        case 1:
            pr.Agregar();
            break;
        case 2:
            pr.Mostrar();
            break;
        case 3:
            pr.Buscar();
            break;
        case 4:
            pr.Modificar();
            // empleado.Datos();
            break;
        case 5:
            if (!cont)
            {
                cout << "No hay datos" << endl;
            }
            else
            {
                pr.Eliminar();
            }
            break;
        case 6:
            cout << "Datos guardados y cerrando......" << endl;
            break;
        default:
            cout << "OPCION INCORRECTA...." << endl;
        }
        pr.ChangeCont();
        system("Pause");
    } while (opc != 6);
}
