#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define f 40
using namespace std;




void co(int, int);
const char *nombe_archivo = "examen_2.dat";
const char *nom_temporal = "tempo13.dat";

struct Empleado
{
    int codigo;
    char nombre[f];
    char apellido[f];
    char puesto[f];
    int sueldo;
    int bonificacion;
    int total;
};
void eliminar();

void ingresar_usu();
void mostrar_usu();
void ctrl();
void modificar_usu();
void buscar();

int main()
{
    ctrl();
}

void ctrl()
{
    int a, b, c;
    do
    {  
        cout << (" 1. Insertar  Empleado\n");    
        cout << (" 2. Ver Empleados\n");       
        cout << (" 3. Eliminar datos\n");       
        cout << (" 4. Buscar datos\n");       
        cout << (" 5. Modificar datos\n");   
        cout << (" 6. Salir \n");
        cout << ("Ingrese opcion:\n ");
        cin >> a;
        switch (a)
        {
        case 1:
            system("cls");
            ingresar_usu();
            break;
        case 2:
            system("cls");
            mostrar_usu();
            break;
        case 3:
            system("cls");
            eliminar();
            break;
        case 4:
            system("cls");
            buscar();
            break;

        case 5:
            system("cls");
            modificar_usu();
            break;
        }
    } while (a != 6);
}

void ingresar_usu()
{
    char continuar;
    FILE *archivo = fopen(nombe_archivo, "ab"); // ab
    Empleado emple;
        string nombre,apellido, puesto;
    do
    {
        system("cls");
        fflush(stdin);

        emple.codigo = 0;
        emple.codigo = emple.codigo + 1;
        
        cout << "Ingrese nombre:\n ";
        getline(cin, nombre);
        strcpy(emple.nombre, nombre.c_str());

        cout << "Ingrese apellido:\n ";
        getline(cin, apellido);
        strcpy(emple.apellido, apellido.c_str());

    
        cout << "Ingrese puesto: \n";
        getline(cin, puesto);
        strcpy(emple.puesto, puesto.c_str());

     
        cout << "sueldo base:\n ";
        cin >> emple.sueldo;
        cin.ignore();

        
        cout << "Bonificacion: ";
        cin >> emple.bonificacion;
        cin.ignore();
        emple.total = emple.sueldo + emple.bonificacion;

        fwrite(&emple, sizeof(Empleado), 1, archivo);

        
        cout << "Desea Agregar otro Empleado s/n : \n";
        cin >> continuar;
    } while ((continuar == 's') || (continuar == 'S'));
    fclose(archivo);
    system("cls");
}
///////////////////////////////////////////////////////////////////////////////////////
void modificar_usu(){
	
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		char respuesta[f];
		string nombre,apellido,puesto;	
    	Empleado emple;
    
		cout << "Ingrese el Codigo del Empleado que desea Modificar: ";
    		cin >> id;
    		cin.ignore();
    		fseek ( archivo, id * sizeof(Empleado), SEEK_SET );  // esto es lo que permite modificar en la pocision
	
        
		cout<<"Ingrese el Nombre:";
		getline(cin,nombre);
    	strcpy(emple.nombre, nombre.c_str()); 
    	
			
		cout<<"Ingrese el Apellido:";
		getline(cin,apellido);
		strcpy(emple.apellido, apellido.c_str()); 
		
					
		cout<<"Ingrese el Puesto:";
		getline(cin,puesto);
		strcpy(emple.puesto, puesto.c_str()); 
		
		
		cout<<"Ingrese el sueldo:";
		cin>>emple.sueldo;
	    cin.ignore();
		
		cout<<"Ingrese el bonificacion:";
		cin>>emple.bonificacion;
		cin.ignore();
		
		 emple.total = emple.sueldo + emple.bonificacion;
		
		fwrite( &emple, sizeof(Empleado), 1, archivo );
		
	fclose(archivo);
	 mostrar_usu();
		system("PAUSE");
}
///////////////////////////////////////////////////////////////////////////////////////
void mostrar_usu()
{
    system("cls");
    FILE *archivo = fopen(nombe_archivo, "rb");
    if (!archivo)
    {
        archivo = fopen(nombe_archivo, "w+b");
    }

    Empleado emple;
    int registro = 0;
    fread(&emple, sizeof(Empleado), 1, archivo);
    

    do
    {
        cout << "_________________________________________________________________________________" << endl;
        cout<<"Codigo Empleado:            "<<registro<<endl;
		cout<<"Nombre:        "<<emple.nombre<<endl;
		cout<<"Apellido:      "<<emple.apellido <<endl;
		cout<<"Puesto:        "<<emple.puesto <<endl;
		cout<<"Sueldo:        "<<emple.sueldo <<endl;
		cout<<"Bonificacion   "<<emple.bonificacion <<endl;
		cout<<"TOTAL:         "<<emple.total << endl;
		cout << "_________________________________________________________________________________" << endl;
        fread(&emple, sizeof(Empleado), 1, archivo);
        registro += 1;

    } while (feof(archivo) == 0);

    cout << endl;

    fclose(archivo);
    getch();
}

void buscar()
{

   FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que registro desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Empleado), SEEK_SET );
	
	Empleado emple;
    
    fread(&emple, sizeof(Empleado), 1, archivo);

    cout << "Codigo: " <<pos<< endl;
    cout << "Nombre: " << emple.nombre << endl;
    cout << "Apellido: " << emple.apellido << endl;
    cout << "puesto: " << emple.puesto << endl;
    cout << "Sueldo Base: " << emple.sueldo << endl;
    cout << "Bonificacion: " << emple.bonificacion << endl;
    cout << "Total: " << emple.total << endl;
    cout << endl;

    fclose(archivo);
    system("PAUSE");
}


void eliminar()
{
    Empleado emple;
    FILE *temporal = fopen(nom_temporal, "w+b");
    FILE *archivo = fopen(nombe_archivo, "r+b");
    int id;
    cout << "Ingrese el Codigo del empleado que desea eliminar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Empleado), SEEK_SET);
    emple.codigo = -1;
    fwrite(&emple, sizeof(Empleado), 1, archivo);
    fclose(archivo);

    archivo = fopen(nombe_archivo, "r+b");

    fread(&emple, sizeof(Empleado), 1, archivo);
    temporal = fopen(nom_temporal, "a+b");
    do
    {
        if (emple.codigo == -1)
        {
            cout << "Archivo eliminado";
        }
        if (emple.codigo >= 0)
        {
            fwrite(&emple, sizeof(Empleado), 1, temporal);
        }
        fread(&emple, sizeof(Empleado), 1, archivo);
    } while (feof(archivo) == 0);
    fclose(temporal);
    fclose(archivo);

    archivo = fopen(nombe_archivo, "w");
    fclose(archivo);

    temporal = fopen(nom_temporal, "r+b");

    fread(&emple, sizeof(Empleado), 1, temporal);
    archivo = fopen(nombe_archivo, "a+b");
    do
    {
        fwrite(&emple, sizeof(Empleado), 1, archivo);
        fread(&emple, sizeof(Empleado), 1, temporal);
    } while (feof(temporal) == 0);
    fclose(archivo);
    fclose(temporal);

    temporal = fopen(nom_temporal, "w");
    fclose(temporal);

    mostrar_usu();
}
