#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Movie
{
public:
    char codigo[35], nombre[100], descripcion[200], time[15], publicObj[15];
    void Capturar();
    bool VerificarData(char codigo[35]);
    void Imprimir();
    void Buscar();
    void Eliminar();
    void Modificar();
} objeto;
void Movie::Capturar()
{
    do
    {
        cout << "\nCodigo: ";
        fflush(stdin);
        cin.getline(codigo, 35);
    }
        while(VerificarData(codigo));
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
        archivo<<codigo<<"|"<<nombre<<"|"<<descripcion<<"|"<<time<<"|"<<publicObj<<"*";
        archivo.close();
}
bool Movie::VerificarData(char codigo[35])
{
    char comp[35], prev[35];
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    if(!arc.good())
    cout<<"\nEl archivo no existe";
    else
    {
        while(!arc.eof())
        {
            arc.getline(prev, 35, '|');
            if(strcmp(prev, codigo)==0)
            {
                arc.close();
                cout << "Se encontraron coincidencias por favor intente con otro codigo";
                return true;
            }
            else
            {
                arc.getline(comp, 200, '|');
                arc.getline(comp, 200, '|');
                arc.getline(comp, 200, '|');
                arc.getline(comp, 200, '*');
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
    if(!Lectura.good())
    {
        cout<<"No existe el archivo\n";
        system("pause");
    }
    else
    {
        while(!Lectura.eof())
        {
            i=0;
            do
            {
                Lectura.read((char *)&codigo[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }
            while(codigo[i-1]!='|');
            codigo[i-1]='\0';
            i=0;
            do
            {
                Lectura.read((char *)&nombre[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }
            while(nombre[i-1]!='|');
            nombre[i-1]='\0';
            i=0;
            do
            {
                Lectura.read((char *)&descripcion[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }
            while(descripcion[i-1]!='|');
            descripcion[i-1]='\0';
            i=0;
            do
            {
                Lectura.read((char *)&time[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }
            while(time[i-1]!='|');
            time[i-1]='\0';
            i=0;
            do
            {
                Lectura.read((char *)&publicObj[i],1);
                if(Lectura.eof())
                    break;
                i++;
            }
            while(publicObj[i-1]!='*');
            publicObj[i-1]='\0';
            if(Lectura.eof())
                break;
            cout<<endl<<"Codigo: "<<codigo<<endl<<"Nombre: "<<nombre<<endl<<"Descripcion: "<<descripcion<<endl<<"Duracion: "<< time << endl << "Clasificacion: " << publicObj << endl;
            if(Lectura.eof())
                break;
        }
        system("pause");
    }
    Lectura.close();
}
void Movie::Buscar()
{
    char ref[35], comp[35], prev[35];
    int band=1;
    cout<<"\nEscribe el codigo de la Pelicula a buscar \n";
    fflush(stdin);
    cin.getline(ref, 35);
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    if(!arc.good())
        cout<<"\nEl archivo no existe";
    else
    {
        while(!arc.eof() && band==1)
        {
            arc.getline(prev, 35, '|');
            if(strcmp(prev, ref)==0)
            {
                cout<<"\nCodigo: "<<prev;
                arc.getline(comp, 100, '|');
                cout<<"\nNombre: "<<comp;
                arc.getline(comp, 200, '|');
                cout<<"\nDescripcion: "<<comp;
                arc.getline(comp, 15, '|');
                cout<<"\nDuracion: "<<comp;
                arc.getline(comp, 15, '*');
                cout<<"\nClasificaion: "<<comp<<endl;
                band=0;
            }
            else
            {
                arc.getline(comp, 200, '|');
                arc.getline(comp, 200, '|');
                arc.getline(comp, 200, '|');
                arc.getline(comp, 200, '*');
            }
        }
        if(band)
            cout<<"\nNo se encontro el Movie";
    }
    arc.close();
}
void Movie::Eliminar()
{
    int i;
    int opcion;
    char prodMod[10];
    bool b;
    int  resp;
    ifstream arc("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\Peliculas.txt");
    ofstream arcTemp("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\temporalauto.txt", ios::app);
    if (!arc.good())
        cout << "\n EL REGISTRO NO EXISTE \n ";
    else
    {
        cout << "\n Introduce el codigo a Eliminar  :  "<<endl;
        cin.getline(prodMod, 35);
        cout<<"¿Quiere eliminarlo?"<<endl;
        cout<<"1=si   2=no"<<endl;
        cin>>resp;
        if(resp == 2)
        {
        arc.close();
        arcTemp.close();
        remove("C:\\Visual Proyect\\Proyecto_Blim\\Peliculas\\temporalauto.txt");
        cout<<"No se Elimino"<<endl;
        return;
        }

        b = false;
        while (!arc.eof())
        {
            i = 0;
            do
            {
                arc.read((char *)&codigo[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (codigo[i - 1] != '|');
            codigo[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&nombre[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (nombre[i - 1] != '|' && !arc.eof());
            nombre[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&descripcion[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (descripcion[i - 1] != '|');
            descripcion[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&time[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (time[i - 1] != '|');
            time[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&publicObj[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (publicObj[i - 1] != '*');
            publicObj[i - 1] = '\0';
            if (arc.eof())
            break;
            if (strcmp(codigo, prodMod) == 0 && !b)
            {
                cout<<"Se encontro y elimino el registro"<<endl;
                b=1;
            }
            else
            {
            arcTemp << codigo << '|' << nombre << '|' << descripcion << '|' << time << '|' << publicObj << '*';
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
            i = 0;
            do
            {
                arc.read((char *)&codigo[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (codigo[i - 1] != '|');
            codigo[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&nombre[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (nombre[i - 1] != '|' && !arc.eof());
            nombre[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&descripcion[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (descripcion[i - 1] != '|');
            descripcion[i - 1] = '\0';
            if (arc.eof())
                break;
            i = 0;
            do
            {
                arc.read((char *)&time[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (time[i - 1] != '|');
            time[i - 1] = '\0';
            if (arc.eof())
                break;

            i = 0;
            do
            {
                arc.read((char *)&publicObj[i], 1);
                if (arc.eof())
                    break;
                i++;
            }
            while (publicObj[i - 1] != '*');
            publicObj[i - 1] = '\0';
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
                     << "   Que desea realiza ? " << endl
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
            arcTemp << codigo << '|' << nombre << '|' << descripcion << '|' << time << '|' << publicObj << '*';
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
        cout<<"\nIngresa el numero de la opcion: \n1.Capturar \n2.Imprimir todo \n3.Buscar \n4.Eliminar \n5.Modificar \n6.Salir\n";
        cin>>op;
        cin.ignore();
        switch(op)
        {
        case 1:
            objeto.Capturar();
            system("pause");
            system("cls");
            break;
        case 2:
            objeto.Imprimir();
            system("cls");
            break;
        case 3:
            objeto.Buscar();
            system("pause");
            system("cls");
            break;
        case 4:
            objeto.Eliminar();
            system("pause");
            system("cls");
            break;
        case 5:
            objeto.Modificar();
            system("pause");
            system("cls");
        }
    }
    while(op!=6);
    return;
}
