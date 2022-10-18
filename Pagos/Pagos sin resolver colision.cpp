#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

#define NUMREGISTROS 100

class Pago
{
    private:
        char id[ 12 ];
        char tarjeta[ 35 ];
        char fecha[ 35 ];
        char cantidad[ 10 ];

        int dispersion( const char llave[ 12 ] );
        long int buscarId( const string & );
    public:
        Pago( void ); //constructor
        //Pago( const Promocion & );
        void setId( const string & );
        void setTarjeta( const string & );
        void setFecha( const string & );
        void setCantidad( const string & );
        friend ostream &operator<<( ostream &, const Pago & );

        bool agregar( const Pago & );
        void mostrar( void );
        bool buscar( const string &, Pago & );
        bool eliminar( const string &, Pago & );
        bool modificar( const string &, const Pago & );
        void mostrarIndice( void );
        Pago pedirRegistro( void );
        bool contiene( const string & );
        void genera( void );
};


// constructor
Pago::Pago( void )
{
    for( int i = 0; i < sizeof( id ); id[ i++ ] = '\0' );
    for( int j = 0; j < sizeof( tarjeta ); tarjeta[ j++ ] = '\0' );
    for( int k = 0; k < sizeof( fecha ); fecha[ k++ ] = '\0' );
    for( int i = 0; i < sizeof( cantidad ); cantidad[ i++ ] = '\0' );
}

void Pago::genera( void )
{
    Pago pago;
    ofstream archivo( "dispersion.txt", ios::out );
    if( !archivo )
        cout << "No se pudo crear el archivo" << endl;
    else
        for( int i = 0; i < NUMREGISTROS; i++ )
            archivo.write( ( char * ) &pago, sizeof( Pago ) );
    archivo.close();
}

bool Pago::contiene( const string &idABuscar )
{
    if( buscarId( idABuscar ) == -1 )
        return false;
    return true;
}

Pago Pago::pedirRegistro( void )
{
    Pago registroARetornar;
    string cadena;

    cout << endl << "ID: ";
    fflush( stdin );
    getline( cin, cadena );
    while( contiene( cadena ) )
    {
        cout << "Ese ID ya existe: ";
        fflush( stdin );
        getline( cin, cadena );
    }
    registroARetornar.setId( cadena );

    cout << "Numero de tarjeta: ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setTarjeta( cadena );

    cout << "Fecha: ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setFecha( cadena );

    cout << "Cantidad a pagar: ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setCantidad( cadena );

    return registroARetornar;
}

int Pago::dispersion( const char llave[ 12 ] )
{
    // llena el sobrante de la llave con espacios
    char llaveCopia[ 12 ];
    strcpy( llaveCopia, llave );
    if( strlen( llaveCopia ) < 12 )
        for( int i = strlen( llaveCopia ); i < 12; i++ )
            llaveCopia[ i ] = ' ';
    llaveCopia[ 12 ] = '\0';

    // realiza el algoritmo
    int sum = 0;
    int j = 0;
    while( j < 12 )
    {
        sum = ( sum + 100 * llaveCopia[ j ] + llaveCopia[ j + 1 ] )  % 20000;
        j += 2;
    }
    return ( sum % 99 ); // retorna la posición donde se guardará el registros.
}

long int Pago::buscarId( const string &idABuscar )
{
    Pago pago;
    int posIndice;
    long int posByte;

    ifstream archivo( "dispersion.txt", ios::in );
    if( !archivo )
    {
        archivo.close();
        return -1;
    }
    else
    {
        posIndice = dispersion( idABuscar.c_str() );
        posByte = posIndice * sizeof( Pago );
        archivo.seekg( posByte, ios::beg );
        archivo.read( ( char * ) &pago, sizeof( Pago ) );
        if( strcmp( pago.id, idABuscar.c_str() ) == 0 )
        {
            archivo.close();
            return posByte;
        }
    }
    archivo.close();
    return -1;
}

void Pago::setId( const string &valorId )
{
    int longitud = valorId.size();
    longitud = ( longitud < 12 ? longitud : 11 );
    valorId.copy( id, longitud );
    id[ longitud ] = '\0';
}

void Pago::setTarjeta( const string &valorTarjeta )
{
    int longitud = valorTarjeta.size();
    longitud = ( longitud < 35 ? longitud : 34 );
    valorTarjeta.copy( tarjeta, longitud );
    tarjeta[ longitud ] = '\0';
}

void Pago::setFecha( const string &valorFecha )
{
    int longitud = valorFecha.size();
    longitud = ( longitud < 35 ? longitud : 34 );
    valorFecha.copy( fecha, longitud );
    fecha[ longitud ] = '\0';
}

void Pago::setCantidad( const string &valorCantidad )
{
    int longitud = valorCantidad.size();
    longitud = ( longitud < 10 ? longitud : 9 );
    valorCantidad.copy( cantidad, longitud );
    cantidad[ longitud ] = '\0';
}

ostream &operator<<( ostream &salida, const Pago &pago )
{
    salida << "ID:        " << pago.id << endl
            << "Producto:  " << pago.tarjeta << endl
            << "Proveedor: " << pago.fecha << endl
            << "Precio:    " << pago.cantidad << endl;

    return salida;
}

bool Pago::agregar( const Pago &nuevoPago )
{
    int posIndice;
    long int posByte;
    string idString = nuevoPago.id;

    if( contiene( idString ) )
        return false;

    posIndice = dispersion( nuevoPago.id );
    cout << "Se guardara en la posicion indice: " << posIndice << endl;
    fstream archivo( "dispersion.txt", ios::in | ios::out );
    posByte = posIndice * sizeof( Pago );
    archivo.seekg( posByte, ios::beg );
    archivo.write( ( char * ) &nuevoPago, sizeof( Pago ) );

    archivo.close();
    //return false;
}

void Pago::mostrar( void )
{
    Pago pago;
    ifstream archivo( "dispersion.txt", ios::in );
    if( !archivo )
        cout << "No existe el archivo" << endl;
    else
        for( int i = 0; i < NUMREGISTROS; i++ )
        {
            archivo.read( ( char * ) &pago, sizeof( Pago ) );
            if( !( pago.id[ 0 ] == '\0' ) )
                cout << endl << pago << endl;
        }
    archivo.close();
}

bool Pago::buscar( const string &idABuscar, Pago &pagoEncontrado )
{
    int posIndice;
    long int posByte;

    if( !contiene( idABuscar ) )
        return false;

    ifstream archivo( "dispersion.txt", ios::in );
    if( !archivo )
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return false;
    }

    posByte = buscarId( idABuscar );
    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &pagoEncontrado, sizeof( Pago ) );
    archivo.close();
    return true;
}

bool Pago::modificar( const string &idAModificar, const Pago &pagoNuevo )
{
    Pago pago;
    long int posByteAnterior, posByteNuevo;
    int posRegAnterior;

    if( !contiene( idAModificar ) )
        return false;

    fstream archivo( "dispersion.txt", ios::in | ios::out );
    if( !archivo )
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posRegAnterior = dispersion( pagoNuevo.id );
    posByteNuevo = posRegAnterior * sizeof( Pago );

    posByteAnterior = buscarId( idAModificar );

    archivo.seekp( posByteAnterior, ios::beg );
    archivo.write( ( char * ) &pago, sizeof( Pago) );
    archivo.seekp( posByteNuevo, ios::beg );
    archivo.write( ( char * ) &pagoNuevo, sizeof( Pago) );
    archivo.close();
    return true;
}

bool Pago::eliminar( const string &idAEliminar, Pago &destinoEliminado )
{
    Pago pago;
    if( !contiene( idAEliminar ) )
        return false;

    fstream archivo( "dispersion.txt", ios::in | ios::out );
    if( !archivo )
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    long int posByte = buscarId( idAEliminar );
    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &destinoEliminado, sizeof(  Pago) );
    archivo.seekg( posByte, ios::beg );
    archivo.write( ( char * ) &pago, sizeof(  Pago) );
    archivo.close();
    return true;
}


int main( void )
{
    Pago pago, pagoBuscar, pagoModificar, pagoEliminar, registroAgregar;
    string idABuscar, idAModificar, idAEliminar;
    char opcion, op;

    pago.genera();

    system( "cls" );

    do{
        cout<<"\n\n\t\tBienvenido al menu de pagos (no aceptamos colisiones)\n\n";
        cout<<"Seleccione una opcion" << endl
            << "1. Agregar"   << endl
            << "2. Mostrar"   << endl
            << "3. Buscar"    << endl
            << "4. Modificar" << endl
            << "5. Eliminar"  << endl
            << "6. Salir"     << endl
            << endl;
        cin >> opcion;
        switch( opcion )
        {
          case '1':
            registroAgregar = pago.pedirRegistro();
            if( pago.agregar( registroAgregar ) )
            {
                cout << "Pago agregado con exito" << endl;
            }else
            {
                cout << "No se agrego el pago" << endl;
            }
            break;

          case '2':
            system( "cls" );
            pago.mostrar();
            break;

          case '3':
            cout << "Ingrese el ID del pago a buscar: ";
            fflush( stdin );
            getline( cin, idABuscar );
            if( pago.buscar( idABuscar, pagoBuscar ) )
                cout << endl << pagoBuscar << endl;
            else
                cout << "No existe el pago" << endl;
            break;

          case '4':
            cout << "Ingrese el ID del pago a modificar: ";
            fflush( stdin );
            getline( cin, idAModificar );
            if( pago.buscar( idAModificar, pagoBuscar ) )
            {
                cout << endl << pagoBuscar << endl;
                cout << "Desea modificarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if( op == '1' )
                {
                    pagoModificar = pago.pedirRegistro();
                    if( pago.modificar( idAModificar, pagoModificar ) )
                        cout << endl << "Pago modificado con exito" << endl;
                    else
                        cout << endl << "No se pudo modificar" << endl;
                }
            }
            else
                cout << "No existe el registro" << endl;
            break;

          case '5':
            cout << "Ingrese el ID del pago a eliminar: ";
            fflush( stdin );
            getline( cin, idAEliminar );
            if( pago.buscar( idAEliminar, pagoBuscar ) )
            {
                cout << endl << pagoBuscar << endl;
                cout << "Desea eliminarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if( op == '1' )
                    if( pago.eliminar( idAEliminar, pagoEliminar ) )
                        cout << endl << pagoEliminar << endl << "SE ELIMINO CORRECTAMENTE" << endl;
                    else
                        cout << "NO SE PUDO ELIMINAR" << endl;
            }
            else
                cout << "No existe el registro" << endl;
            break;
        }
        cout << endl;
        system("Pause");
        system( "cls" );
    }while(opcion != '6');
}
