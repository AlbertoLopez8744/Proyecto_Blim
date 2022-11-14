#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

#define NUMREGISTROS 100
#define CONTENEDOR 4

class Pago
{
private:
    char id[12];
    char tarjeta[35];
    char fecha[35];
    char cantidad[10];

    int dispersion(const char llave[12]);
    long int buscarId(const string &);

public:
    Pago(void);
    Pago(const Pago &);
    void setId(const string &);
    void setTarjeta(const string &);
    void setFecha(const string &);
    void setCantidad(const string &);
    friend ostream &operator<<(ostream &, const Pago &);

    bool agregar(const Pago &);
    void mostrar(void);
    bool buscar(const string &, Pago &);
    bool eliminar(const string &, Pago &);
    bool modificar(const string &, const Pago &);
    void mostrarIndice(void);
    Pago pedirRegistro(void);
    bool contiene(const string &);
    void genera(void);
    void AdminPay();
};

// constructor
Pago::Pago(void)
{
    for (int i = 0; i < sizeof(id); id[i++] = '\0')
        ;
    for (int i = 0; i < sizeof(tarjeta); tarjeta[i++] = '\0')
        ;
    for (int i = 0; i < sizeof(fecha); fecha[i++] = '\0')
        ;
    for (int i = 0; i < sizeof(cantidad); cantidad[i++] = '\0')
        ;
}

bool Pago::contiene(const string &idABuscar)
{
    if (buscarId(idABuscar) == -1)
        return false;
    return true;
}

Pago Pago::pedirRegistro(void)
{
    Pago registroARetornar;
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

    cout << "Tarjeta: ";
    fflush(stdin);
    getline(cin, cadena);
    registroARetornar.setTarjeta(cadena);

    cout << "Fecha: ";
    fflush(stdin);
    getline(cin, cadena);
    registroARetornar.setFecha(cadena);

    cout << "Cantidad: ";
    fflush(stdin);
    getline(cin, cadena);
    registroARetornar.setCantidad(cadena);

    return registroARetornar;
}

void Pago::genera(void)
{
    Pago pago;
    int contador = 0;
    ofstream archivo(".data\\Pagos.txt", ios::out);
    if (!archivo)
        cout << "No se pudo crear el archivo" << endl;
    else
        for (int i = 0; i < NUMREGISTROS; i++)
        {
            // indica cuantos registros hay en el contenedor
            archivo.write((char *)&contador, sizeof(int));
            for (int j = 0; j < CONTENEDOR; j++)
                archivo.write((char *)&pago, sizeof(Pago));
        }
    archivo.close();
}

int Pago::dispersion(const char llave[12])
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
long int Pago::buscarId(const string &idABuscar)
{
    Pago pago;
    int contador, posIndice;
    long int posByte;

    ifstream archivo(".data\\Pagos.txt", ios::in);
    if (!archivo)
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return -1;
    }

    posIndice = dispersion(idABuscar.c_str());
    posByte = posIndice * ((sizeof(Pago) * CONTENEDOR) + sizeof(int));
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&contador, sizeof(int));
    if (contador > 0)
    {
        for (int i = 0; i < CONTENEDOR; i++)
        {
            archivo.read((char *)&pago, sizeof(Pago));
            if (strcmp(pago.id, idABuscar.c_str()) == 0)
            {
                posByte = (long)archivo.tellg() - sizeof(Pago);
                archivo.close();
                return posByte;
            }
        }
    }

    archivo.close();
    return -1;
}

void Pago::setId(const string &valorId)
{
    int longitud = valorId.size();
    longitud = (longitud < 12 ? longitud : 11);
    valorId.copy(id, longitud);
    id[longitud] = '\0';
}

void Pago::setTarjeta(const string &valorTarjeta)
{
    int longitud = valorTarjeta.size();
    longitud = (longitud < 35 ? longitud : 34);
    valorTarjeta.copy(tarjeta, longitud);
    tarjeta[longitud] = '\0';
}

void Pago::setFecha(const string &valorFecha)
{
    int longitud = valorFecha.size();
    longitud = (longitud < 35 ? longitud : 34);
    valorFecha.copy(fecha, longitud);
    fecha[longitud] = '\0';
}

void Pago::setCantidad(const string &valorCantidad)
{
    int longitud = valorCantidad.size();
    longitud = (longitud < 12 ? longitud : 11);
    valorCantidad.copy(cantidad, longitud);
    cantidad[longitud] = '\0';
}

ostream &operator<<(ostream &salida, const Pago &pago)
{
    salida << "ID:        " << pago.id << endl
           << "Producto:  " << pago.tarjeta << endl
           << "Proveedor: " << pago.fecha << endl
           << "Precio:    " << pago.cantidad << endl;

    return salida;
}

bool Pago::agregar(const Pago &nuevoPago)
{
    Pago pago;
    string cadena;
    int posIndice, contador;
    long int posByte;
    string idString = nuevoPago.id;

    if (contiene(idString))
        return false;

    fstream archivo(".data\\Pagos.txt", ios::in | ios::out);
    posIndice = dispersion(nuevoPago.id);
    cout << "Se guardara en la posicion indice: " << posIndice << endl;
    posByte = posIndice * (sizeof(Pago) * CONTENEDOR + sizeof(int));
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
            archivo.read((char *)&pago, sizeof(Pago));
            if (pago.id[0] == '\0')
            {
                archivo.seekg((long)archivo.tellg() - sizeof(Pago), ios::beg);
                archivo.write((char *)&nuevoPago, sizeof(Pago));
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

void Pago::mostrar(void)
{
    Pago pago;
    int contador;
    long int posByte;

    ifstream archivo(".data\\Pagos.txt", ios::in);
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
                    archivo.read((char *)&pago, sizeof(Pago));
                    if (pago.id[0] != '\0'){
                        cout << "ID: " << pago.id << endl
                        << "Tarjeta: " << pago.tarjeta << endl
                        << "Fecha vencimiento: " << pago.fecha << endl
                        << "Monto: " << pago.cantidad << endl;
                    }
                }
            }
            else
                archivo.seekg(sizeof(Pago) * CONTENEDOR, ios::cur);
        }
    }
    archivo.close();
}

bool Pago::buscar(const string &idABuscar, Pago &pagoEncontrado)
{
    long int posByte;

    if (!contiene(idABuscar))
        return false;

    ifstream archivo(".data\\Pagos.txt", ios::in);
    if (!archivo)
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return false;
    }

    posByte = buscarId(idABuscar);
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&pagoEncontrado, sizeof(Pago));
    archivo.close();
    return true;
}

bool Pago::modificar(const string &idAModificar, const Pago &pagoNuevo)
{
    Pago registroLimpio, pago;
    int posIndiceAntiguo, posIndiceNuevo, contador;
    long int posByteAntiguo, posByteNuevo;

    if (!contiene(idAModificar))
        return false;

    fstream archivo(".data\\Pagos.txt", ios::in | ios::out);
    if (!archivo)
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posIndiceAntiguo = dispersion(idAModificar.c_str());
    posByteAntiguo = buscarId(idAModificar);
    posIndiceNuevo = dispersion(pagoNuevo.id);
    posByteNuevo = posIndiceNuevo * (sizeof(Pago) * CONTENEDOR + sizeof(int));

    if (posByteAntiguo == posByteNuevo)
    {
        archivo.seekg(posByteAntiguo, ios::beg);
        archivo.write((char *)&pagoNuevo, sizeof(Pago));
    }
    else
    {
        // quita el registro antiguo y resta uno al contador del contenedor
        archivo.seekg(posByteAntiguo, ios::beg);
        archivo.write((char *)&registroLimpio, sizeof(Pago));
        posByteAntiguo = posIndiceAntiguo * (sizeof(Pago) * CONTENEDOR + sizeof(int));
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
                archivo.read((char *)&pago, sizeof(Pago));
                if (pago.id[0] == '\0') // si el lugar no esta ocupado
                {
                    archivo.seekg((long)archivo.tellg() - sizeof(Pago), ios::beg);
                    archivo.write((char *)&pagoNuevo, sizeof(Pago));
                    archivo.close();
                    return true;
                }
            }
        }
        else // el contenedor esta lleno
            return false;
    }
} // fin funcion modificar

bool Pago::eliminar(const string &idAEliminar, Pago &pagoEliminado)
{
    Pago pago;
    int posIndice, posByte, contador;

    if (!contiene(idAEliminar))
        return false;

    fstream archivo(".data\\Pagos.txt", ios::in | ios::out);
    if (!archivo)
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posIndice = dispersion(idAEliminar.c_str());
    posByte = buscarId(idAEliminar);

    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&pagoEliminado, sizeof(Pago));
    archivo.seekg(posByte, ios::beg);
    archivo.write((char *)&pago, sizeof(Pago));

    posByte = posIndice * (sizeof(Pago) * CONTENEDOR + sizeof(int));
    archivo.seekg(posByte, ios::beg);
    archivo.read((char *)&contador, sizeof(int));
    contador--;
    archivo.seekg(posByte, ios::beg);
    archivo.write((char *)&contador, sizeof(int));
    archivo.close();
    return true;
}

void Pago::AdminPay()
{
    Pago pago, pagoBuscar, pagoModificar, pagoEliminar, registroAgregar;
    string idABuscar, idAModificar, idAEliminar;
    char opcion, op;
    system("cls");

    do
    {
        cout << endl <<"\t\tBienvenido al menu de Pagos" << endl;
        cout << "Seleccione una opcion" << endl
             << "1. Agregar" << endl
             << "2. Mostrar" << endl
             << "3. Buscar" << endl
             << "4. Modificar" << endl
             << "5. Eliminar" << endl
             << "6. Salir" << endl
             << endl;
        cin >> opcion;
        switch (opcion)
        {
        case '1':
            registroAgregar = pago.pedirRegistro();
            if (pago.agregar(registroAgregar))
                cout << "Pago agregado con exito" << endl;
            else
                cout << "No se agrego el pago" << endl;
            break;

        case '2':
            system("cls");
            pago.mostrar();
            break;

        case '3':
            cout << "Ingrese el ID del pago a buscar: ";
            fflush(stdin);
            getline(cin, idABuscar);
            if (pago.buscar(idABuscar, pagoBuscar))
                cout << endl
                     << pagoBuscar << endl;
            else
                cout << "No existe registro del pago" << endl;
            break;

        case '4':
            cout << "Ingrese el ID del pago a buscar: ";
            fflush(stdin);
            getline(cin, idAModificar);
            if (pago.buscar(idAModificar, pagoBuscar))
            {
                cout << endl
                     << pagoBuscar << endl;
                cout << "Desea modificarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if (op == '1')
                {
                    pagoModificar = pago.pedirRegistro();
                    if (pago.modificar(idAModificar, pagoModificar))
                        cout << endl
                             << "Pago modificado con exito" << endl;
                    else
                        cout << endl
                             << "No se pudo modificar" << endl;
                }
            }
            else
                cout << "No existe el registro" << endl;
            break;

        case '5':
            cout << "Ingrese el ID del pago a eliminar: ";
            fflush(stdin);
            getline(cin, idAEliminar);
            if (pago.buscar(idAEliminar, pagoBuscar))
            {
                cout << endl
                     << pagoBuscar << endl;
                cout << "Desea eliminarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if (op == '1')
                    if (pago.eliminar(idAEliminar, pagoEliminar))
                        cout << endl
                             << pagoEliminar << endl
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
