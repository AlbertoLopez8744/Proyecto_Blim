#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

#define NUMREGISTROS 100
#define CONTENEDOR 4

class Promocion
{
private:
    char id[12];
    char nombre[35];
    char proveedor[35];
    char precio[10];

    int dispersion(const char llave[12]);
    long int buscarId(const string &);

public:
    Promocion(void);
    Promocion(const Promocion &);
    void setId(const string &);
    void setNombre(const string &);
    void setProveedor(const string &);
    void setPrecio(const string &);
    friend ostream &operator<<(ostream &, const Promocion &);

    bool agregar(const Promocion &);
    void mostrar(void);
    bool buscar(const string &, Promocion &);
    bool eliminar(const string &, Promocion &);
    bool modificar(const string &, const Promocion &);
    void mostrarIndice(void);
    Promocion pedirRegistro(void);
    bool contiene(const string &);
    void genera(void);
};

// constructor
Promocion::Promocion(void)
{
    for (int i = 0; i < sizeof(id); id[i++] = '\0')
        ;
    for (int i = 0; i < sizeof(nombre); nombre[i++] = '\0')
        ;
    for (int i = 0; i < sizeof(proveedor); proveedor[i++] = '\0')
        ;
    for (int i = 0; i < sizeof(precio); precio[i++] = '\0')
        ;
}

bool Promocion::contiene(const string &idABuscar)
{
    if (buscarId(idABuscar) == -1)
        return false;
    return true;
}

Promocion Promocion::pedirRegistro(void)
{
    Promocion registroARetornar;
    string cadena;

    cout << endl
         << "ID: ";
    fflush(stdin);
    getline(cin, cadena);
    while (contiene(cadena) || cadena.size() == 0)
    {
        cout << "Ese ID ya existe o la cadena es invalida: ";
        fflush(stdin);
        getline(cin, cadena);
    }
    registroARetornar.setId(cadena);

    cout << "Nombre: ";
    fflush(stdin);
    getline(cin, cadena);
    registroARetornar.setNombre(cadena);

    cout << "Provedor: ";
    fflush(stdin);
    getline(cin, cadena);
    registroARetornar.setProveedor(cadena);

    cout << "Precio: ";
    fflush(stdin);
    getline(cin, cadena);
    registroARetornar.setPrecio(cadena);

    return registroARetornar;
}

void Promocion::genera(void)
{
    Promocion promo;
    int contador = 0;
    ofstream archivo("dispersion2.txt", ios::out);
    if (!archivo)
        cout << "No se pudo crear el archivo" << endl;
    else
        for (int i = 0; i < NUMREGISTROS; i++)
        {
            // indica cuantos registros hay en el contenedor
            archivo.write((char *)&contador, sizeof(int));
            for (int j = 0; j < CONTENEDOR; j++)
                archivo.write((char *)&promo, sizeof(Promocion));
        }
    archivo.close();
}

int Promocion::dispersion(const char llave[12])
{
    // llena la el sobrante de la llave con espacios
    char llaveCopia[12];
    strcpy(llaveCopia, llave);
    if (strlen(llaveCopia) < 12)
        for (int i = strlen(llaveCopia); i < 12; i++)
            llaveCopia[i] = ' ';
    llaveCopia[12] = '\0';

    // realiza el algoritmo
    long sum = 0;
    int j = 0;
    while (j < 12)
    {
        sum = (sum + 100 * llaveCopia[j] + llaveCopia[j + 1]) % 20000;
        j += 2;
    }
    return (sum % 99); // retorna la posición donde se guardará el registros.
}

// retorna la posición donde se encontro el registro
long int Promocion::buscarId(const string &idABuscar)
{
    Promocion promo;
    int contador, posIndice;
    long int posByte;

    ifstream archivo("dispersion2.txt", ios::in);
    if (!archivo)
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return -1;
    }

    posIndice = dispersion(idABuscar.c_str());
    posByte = posIndice * ((sizeof(Promocion) * CONTENEDOR) + sizeof(int));
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&contador, sizeof(int));
    if (contador > 0)
    {
        for (int i = 0; i < CONTENEDOR; i++)
        {
            archivo.read((char *)&promo, sizeof(Promocion));
            if (strcmp(promo.id, idABuscar.c_str()) == 0)
            {
                posByte = (long)archivo.tellg() - sizeof(Promocion);
                archivo.close();
                return posByte;
            }
        }
    }

    archivo.close();
    return -1;
}

void Promocion::setId(const string &valorId)
{
    int longitud = valorId.size();
    longitud = (longitud < 12 ? longitud : 11);
    valorId.copy(id, longitud);
    id[longitud] = '\0';
}

void Promocion::setNombre(const string &valorNombre)
{
    int longitud = valorNombre.size();
    longitud = (longitud < 35 ? longitud : 34);
    valorNombre.copy(nombre, longitud);
    nombre[longitud] = '\0';
}

void Promocion::setProveedor(const string &valorProveedor)
{
    int longitud = valorProveedor.size();
    longitud = (longitud < 35 ? longitud : 34);
    valorProveedor.copy(proveedor, longitud);
    proveedor[longitud] = '\0';
}

void Promocion::setPrecio(const string &valorPrecio)
{
    int longitud = valorPrecio.size();
    longitud = (longitud < 12 ? longitud : 11);
    valorPrecio.copy(precio, longitud);
    precio[longitud] = '\0';
}

ostream &operator<<(ostream &salida, const Promocion &promocion)
{
    salida << "ID:        " << promocion.id << endl
           << "Producto:  " << promocion.nombre << endl
           << "Proveedor: " << promocion.proveedor << endl
           << "Precio:    " << promocion.precio << endl;

    return salida;
}

bool Promocion::agregar(const Promocion &nuevaPromocion)
{
    Promocion promo;
    string cadena;
    int posIndice, contador;
    long int posByte;
    string idString = nuevaPromocion.id;

    if (contiene(idString))
        return false;

    fstream archivo("dispersion2.txt", ios::in | ios::out);
    posIndice = dispersion(nuevaPromocion.id);
    cout << "Se guardara en la posicion indice: " << posIndice << endl;
    posByte = posIndice * (sizeof(Promocion) * CONTENEDOR + sizeof(int));
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&contador, sizeof(int)); // lee el numero de registros en el contador
    if (contador < CONTENEDOR)                    // si el contenedor no esta lleno
    {
        // aumenta el contador y lo escribe
        contador++;
        archivo.seekg(posByte, ios::beg);
        archivo.write((char *)&contador, sizeof(int));

        // escribe el nuevo registro en el contenedor
        for (int i = 0; i < CONTENEDOR; i++)
        {
            archivo.read((char *)&promo, sizeof(Promocion));
            if (promo.id[0] == '\0')
            {
                archivo.seekg((long)archivo.tellg() - sizeof(Promocion), ios::beg);
                archivo.write((char *)&nuevaPromocion, sizeof(Promocion));
                archivo.close();
                return true;
            }
        }
    }
    else
        cout << endl
             << "No hay mas espacio para este registro" << endl;
    archivo.close();
    return false;
}

void Promocion::mostrar(void)
{
    Promocion promo;
    int contador;
    long int posByte;

    ifstream archivo("dispersion2.txt", ios::in);
    if (!archivo)
        cout << "No existe el archivo" << endl;
    else
    {
        cout << endl;
        for (int i = 0; i < NUMREGISTROS; i++)
        {
            archivo.read((char *)&contador, sizeof(int));
            if (contador > 0)
            {
                for (int j = 0; j < CONTENEDOR; j++)
                {
                    archivo.read((char *)&promo, sizeof(Promocion));
                    if (promo.id[0] != '\0')
                        cout << promo << endl;
                }
            }
            else
                archivo.seekg(sizeof(Promocion) * CONTENEDOR, ios::cur);
        }
    }
    archivo.close();
}

bool Promocion::buscar(const string &idABuscar, Promocion &promocionEncontrada)
{
    long int posByte;

    if (!contiene(idABuscar))
        return false;

    ifstream archivo("dispersion2.txt", ios::in);
    if (!archivo)
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return false;
    }

    posByte = buscarId(idABuscar);
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&promocionEncontrada, sizeof(Promocion));
    archivo.close();
    return true;
}

bool Promocion::modificar(const string &idAModificar, const Promocion &promocionNueva)
{
    Promocion registroLimpio, promo;
    int posIndiceAntiguo, posIndiceNuevo, contador;
    long int posByteAntiguo, posByteNuevo;

    if (!contiene(idAModificar))
        return false;

    fstream archivo("dispersion2.txt", ios::in | ios::out);
    if (!archivo)
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posIndiceAntiguo = dispersion(idAModificar.c_str());
    posByteAntiguo = buscarId(idAModificar);
    posIndiceNuevo = dispersion(promocionNueva.id);
    posByteNuevo = posIndiceNuevo * (sizeof(Promocion) * CONTENEDOR + sizeof(int));

    if (posByteAntiguo == posByteNuevo)
    {
        archivo.seekg(posByteAntiguo, ios::beg);
        archivo.write((char *)&promocionNueva, sizeof(Promocion));
    }
    else
    {
        // quita el registro antiguo y resta uno al contador del contenedor
        archivo.seekg(posByteAntiguo, ios::beg);
        archivo.write((char *)&registroLimpio, sizeof(Promocion));
        posByteAntiguo = posIndiceAntiguo * (sizeof(Promocion) * CONTENEDOR + sizeof(int));
        archivo.seekg(posByteAntiguo, ios::beg);
        archivo.read((char *)&contador, sizeof(int));
        contador--;
        archivo.seekg(posByteAntiguo, ios::beg);
        archivo.write((char *)&contador, sizeof(int));

        // intenta meter el nuevo registro en la nueva posicion
        archivo.seekg(posByteNuevo, ios::beg);
        archivo.read((char *)&contador, sizeof(int));
        if (contador < CONTENEDOR)
        {
            // aumenta el contador y lo escribe
            contador++;
            archivo.seekg(posByteNuevo, ios::beg);
            archivo.write((char *)&contador, sizeof(int));

            // escribe el nuevo registro en el contenedor
            for (int i = 0; i < CONTENEDOR; i++)
            {
                archivo.read((char *)&promo, sizeof(Promocion));
                if (promo.id[0] == '\0') // si el lugar no esta ocupado
                {
                    archivo.seekg((long)archivo.tellg() - sizeof(Promocion), ios::beg);
                    archivo.write((char *)&promocionNueva, sizeof(Promocion));
                    archivo.close();
                    return true;
                }
            }
        }
        else // el contenedor esta lleno
            return false;
    }
} // fin funcion modificar

bool Promocion::eliminar(const string &idAEliminar, Promocion &destinoEliminado)
{
    Promocion promo;
    int posIndice, posByte, contador;

    if (!contiene(idAEliminar))
        return false;

    fstream archivo("dispersion2.txt", ios::in | ios::out);
    if (!archivo)
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posIndice = dispersion(idAEliminar.c_str());
    posByte = buscarId(idAEliminar);

    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&destinoEliminado, sizeof(Promocion));
    archivo.seekg(posByte, ios::beg);
    archivo.write((char *)&promo, sizeof(Promocion));

    posByte = posIndice * (sizeof(Promocion) * CONTENEDOR + sizeof(int));
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&contador, sizeof(int));
    contador--;
    archivo.seekg(posByte, ios::beg);
    archivo.write((char *)&contador, sizeof(int));
    archivo.close();
    return true;
}

int main(void)
{
    Promocion promocion, promocionBuscar, promocionModificar, promocionEliminar, registroAgregar;
    string idABuscar, idAModificar, idAEliminar;
    char opcion, op;

    promocion.genera();
    system("cls");

    do
    {
        cout << "\n\n\t\tBienvenido al menu Promociones\n\n";
        cout << "Seleccione una opcion" << endl
             << "1. Agregar" << endl
             << "2. Mostrar" << endl
             << "3. Buscar" << endl
             << "4. Modificar" << endl
             << "5. Eliminar" << endl
             << "6. Salir" << endl
             << endl;
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case '1':
            registroAgregar = promocion.pedirRegistro();
            if (promocion.agregar(registroAgregar))
                cout << "Cliente agregado con exito" << endl;
            else
                cout << "No se agrego la promocion" << endl;
            break;

        case '2':
            system("cls");
            promocion.mostrar();
            break;

        case '3':
            cout << "Ingrese el ID de la promocion a buscar: ";
            getline(cin, idABuscar);
            if (promocion.buscar(idABuscar, promocionBuscar))
                cout << endl
                     << promocionBuscar << endl;
            else
                cout << "No existe el registro" << endl;
            break;

        case '4':
            cout << "Ingrese el ID de la promocion a modificar: ";
            getline(cin, idAModificar);
            if (promocion.buscar(idAModificar, promocionBuscar))
            {
                cout << endl
                     << promocionBuscar << endl;
                cout << "Desea modificarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;cin.ignore();
                if (op == '1')
                {
                    promocionModificar = promocion.pedirRegistro();
                    if (promocion.modificar(idAModificar, promocionModificar))
                        cout << endl
                             << "Promocion modificada con exito" << endl;
                    else
                        cout << endl
                             << "No se pudo modificar" << endl;
                }
            }
            else
                cout << "No existe el registro" << endl;
            break;

        case '5':
            cout << "Ingrese el ID de la promocion a eliminar: ";
            getline(cin, idAEliminar);
            if (promocion.buscar(idAEliminar, promocionBuscar))
            {
                cout << endl
                     << promocionBuscar << endl;
                cout << "Desea eliminarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if (op == '1')
                    if (promocion.eliminar(idAEliminar, promocionEliminar))
                        cout << endl
                             << promocionEliminar << endl
                             << "SE ELIMINO CORRECTAMENTE" << endl;
                    else
                        cout << "NO SE PUDO ELIMINAR" << endl;
            }
            else
                cout << "No existe el registro" << endl;
            break;
        }
        cout << endl;
        system("Pause");
        system("cls");
    } while (opcion != '6');
}