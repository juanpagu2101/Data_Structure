#include <string.h>
#include <iostream>
#define MAX_SIZE 1123
using namespace std;

struct Divipola
{
    string Codigo;
    string Nombre;
    string Latitud;
    string Longitud;
    
};

struct distancia
{
    string Codigo;
    double distanciakm;
};

struct SistemaCiudades // estructura para la lista de sistema de ciudades
{
    string aglomeracion;
    string FuncionCiudades;
    string cod_dept;
    string nom_mpio;
    string divipola;
    string anio;
    string personas;
    string hectareas;
};

struct ciudadescapitales
{
    string funcionCiudades;
    string cod_dept;
    string nom_mpio;
    string divipola;
};

struct Municipios_Ciudades
{
    string Nombre_Aglomeracion;
    string Nombre;
    string Divipola;
    string Personas;
    string Hectareas;
};

struct Aglomeracion
{
    string Nombre;
    Municipios_Ciudades Ciudad_Principal;
    list<Municipios_Ciudades> Ciudades_Componentes;
    double **Distancias;
    double **Distancias_Menores;
    string **Nodos_Anteriores;
};
