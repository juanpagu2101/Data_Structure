#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <clocale>
#include <list>
#include "main.h"
#include "funciones.cpp"
#include <vector>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
//#define V 1123
using namespace std;

string aMayuscula(string cadena)
{
    for (int i = 0; i < cadena.length(); i++)
        cadena[i] = toupper(cadena[i]);
    return cadena;
}

int main()
{
    setlocale(LC_CTYPE, "");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    int tamgrf = 1123;
    string Entrada;

    list<Divipola> Departamentos;
    list<Divipola> Municipios;
    list<Divipola> Poblaciones;
    list<SistemaCiudades> SClista;
    list<ciudadescapitales> ciudadesCapitales;
    list<Aglomeracion> Aglomeraciones;
    list<Municipios_Ciudades> Ciudades_Uninodales;
    list<distancia> Ldistancias;
    string linea;
    string codigodepto;
    string codigoMunicipio;
    bool Salir = false;
    char delimitador = ',';
    bool comandoEncontrado = false;
    do
    {
        comandoEncontrado = false;

        cout << "$";

        getline(cin, Entrada);

        // Vector para guardar los comandos de entrada
        vector<string> tokens;

        // stringstream class check1
        stringstream check1(Entrada);

        string intermediate;

        // Tokenizando la entrada por los espacios' '
        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        // Buscando si el comando ingresado esta en el menu de comandos
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "carga_divipola")

            {
                if (tokens[i + 1] == "DIVIPOLA_CentrosPoblados.csv")
                {
                    Cargar_divipola(Departamentos, Municipios, Poblaciones);
                    if (Departamentos.empty() == 0)
                    {
                        cout << endl;
                        cout << "\tSe cargaron correctamente " << Departamentos.size() << " departamentos, " << Municipios.size() << " municipios y " << Poblaciones.size() << " centros poblados desde " << endl;
                        cout << "\tDIVIPOLA_CentrosPoblados.csv" << endl;
                        cout << endl;
                    }
                    if (Departamentos.empty() == 1)
                    {
                        cout << endl;
                        cout << "\tNo se pudo cargar correctamente la informaci�n desde DIVIPOLA_CentrosPoblados.csv" << endl;
                        cout << endl;
                    }
                }
                else
                {
                    cout << endl;
                    cout << "\tNo se ha encontrado el archivo indicado" << endl;
                    cout << "\tDijite ayuda para solucionar su problema" << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_departamentos")
            {
                if (Departamentos.empty())
                {
                    cout << endl;
                    cout << "\tNo hay departamentos cargados en memoria." << endl;
                    cout << endl;
                }
                else
                {
                    Listar_Departamentos(Departamentos, Municipios, Poblaciones);
                }
                comandoEncontrado = true;
            }

            else if (tokens[i] == "listar_municipios")
            {
                codigodepto = tokens[i + 1]; // aca recoge el valor del codigo ejemplo listar_municipios 45 este recoge el 45 para luego ser buscado

                if (Existencia_Departamento_Municipio(codigodepto, Departamentos) == false)
                {
                    cout << endl;
                    cout << "\tNo hay municipios cargados en memoria para ese departamento." << endl;
                    cout << endl;
                }
                else
                {
                    Listar_Municipios_Poblaciones(codigodepto, Municipios);
                }

                comandoEncontrado = true;
            }
            else if (tokens[i] == "listar_poblaciones")
            {
                codigoMunicipio = tokens[i + 1]; // aca recoge el valor del codigo ejemplo listar_poblaciones 45 este recoge el 45 para luego ser buscado

                if (Existencia_Departamento_Municipio(codigoMunicipio, Municipios) == false)
                {
                    cout << endl;
                    cout << "\tNo hay centros poblados cargados en memoria para ese municipio." << endl;
                    cout << endl;
                }
                else
                {
                    Listar_Municipios_Poblaciones(codigoMunicipio, Poblaciones);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "info_sumaria")
            {
                codigodepto = tokens[i + 1];
                if (Existencia_Departamento_Municipio(codigodepto, Departamentos) == false)
                {
                    cout << endl;
                    cout << "\tNo hay informacion cargada en memoria para ese departamento." << endl;
                    cout << endl;
                }
                else
                {
                    Nombre_Departamento(Departamentos, codigodepto);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "carga_SC")
            {
                if (tokens[i + 1] == "Datos-ICM-2019.csv")
                {
                    cargar_SC(SClista,Municipios);
                    if (SClista.empty() == 0)
                    {
                        cout << endl;
                        cout << "\tSe cargaron correctamente " << SClista.size() << " registros desde Datos-ICM-2019.csv" << endl;
                        cout << endl;
                    }
                    if (SClista.empty() == 1)
                    {
                        cout << endl;
                        cout << "\tLa carga no ha sido exitosa" << endl;
                        cout << endl;
                    }
                }
                else
                {
                    cout << endl;
                    cout << "\tNo se ha encontrado el archivo indicado" << endl;
                    cout << "\tDijite ayuda para solucionar su problema" << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "esta_en_sistema")
            {
                string cadena;
                codigoMunicipio = tokens[i + 1]; // aca recoge el valor del codigo ejemplo esta_en_sistema 45 este recoge el 45 para luego ser buscado
                if (Existencia_Departamento_Municipio(codigoMunicipio, Municipios) == false)
                {
                    cout << endl;
                    cout << "\tNo hay informacion cargada en memoria para ese municipio." << endl;
                    cout << endl;
                }
                else
                {
                    estaEnSistema(codigoMunicipio, SClista, Municipios);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "capital_menor")
            {
                capitalesmenores(SClista, ciudadesCapitales);
                if (!ciudadesCapitales.empty())
                {
                    cout << endl;
                    cout << "\tSe crearon " << ciudadesCapitales.size() << " ciudades capitales menores de cien mil habitantes" << endl;
                    cout << endl;
                }
                else
                {
                    cout << endl;
                    cout << "\tNo se pueden crear las ciudades capitales menores de cien mil habitantes a partir del sistema de ciudades cargado en memoria" << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "reporte")
            {

                if (!SClista.empty())
                {
                    reporte(SClista);
                }
                else
                {
                    cout << endl;
                    cout << "\tNo se puede generar el reporte porque no hay datos cargados en memoria" << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }

            else if (tokens[i] == "aglomeracion")
            {
                Crear_Aglomeraciones(SClista, Aglomeraciones);
                if (Aglomeraciones.empty())
                {
                    cout << endl;
                    cout << "\tNo se pueden crear las aglomeraciones urbanas a partir del Sistema de Ciudades cargado en memoria." << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "uninodal")
            {
                Crear_Uninodales(SClista, Ciudades_Uninodales);
                if (!Ciudades_Uninodales.empty())
                {
                    cout << endl;
                    cout << "\tSe crearon " << Ciudades_Uninodales.size() << " ciudades uninodales." << endl;
                    cout << endl;
                }
                else
                {
                    cout << endl;
                    cout << "\tNo se pueden crear las ciudades uninodales a partir del Sistema de Ciudades cargado en memoria." << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "codificar_archivoicm.bin")
            {
                if (codificar() == 0)
                {
                    cout << endl;
                    cout << "\tSe puedo codificar los municipios clasificaciones y datos del SC codificados y almacenados en codificado.icmbin" << endl;
                    cout << endl;
                }
                else if (codificar() == 1)
                {
                    cout << endl;
                    cout << "\tNo se pudo abrir el archivo de indice de ciudades" << endl;
                    cout << endl;
                }
                else if (codificar() == 2)
                {
                    cout << endl;
                    cout << "\tNo se pueden guardar los municipios del indice de ciudades modernas (ICM) en codificado.icmbin" << endl;
                    cout << endl;
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "decodificar_archivoicm.bin")
            {
                if (decodificar() == 0)
                {
                    cout << endl;
                    cout << "\tDatos del ICM decodificados desde codificado.icmbin y cargadas en memoria con el archivo codificado.ic" << endl;
                    cout << endl;
                }
                else if (decodificar() == 1)
                {
                    cout << endl;
                    cout << "\tNo se pueden cargar los datos desde codificado.icmbin" << endl;
                    cout << endl;
                }
                else if (decodificar() == 2)
                {
                    cout << endl;
                    cout << "\tEl archivo ya esta decodificado" << endl;
                    cout << endl;
                }

                comandoEncontrado = true;
            }
            else if (tokens[i] == "distancia")
            {
                string aglomeracion;
                aglomeracion = tokens[i + 1];
                if (Existencia_Aglomeracion(aglomeracion, SClista) == false)
                {
                    cout << endl;
                    cout << "\tNo hay informacion cargada en memoria para esa aglomeracion." << endl;
                    cout << endl;
                }
                else
                {
                    distanciaAglo(aglomeracion, Aglomeraciones, Municipios,SClista,Ldistancias);
                }
                comandoEncontrado = true;
            }
            else if (tokens[i] == "ciudad_remota")
            {
                string Nombre_Aglomeracion;
                Nombre_Aglomeracion = tokens[i + 1]
                    if (Existencia_Aglomeracion(aglomeracion,SClista) == false)
                    {
                        cout<< endl;
                        cout << "La aglomeración dada no existe." << endl;
                        cout << endl;
                    }
                else
                {
                    cout << "El costo total en kilómetros de la ruta más larga es K kilómetros y corresponde a la ciudad C en la aglomeración." << endl;
                }
            }
            else if (tokens[i] == "ayuda")
            {
                string menuayuda = tokens[i + 1];
                ayuda(menuayuda, comandoEncontrado);
            }
            else if (tokens[i] == "salir")
            {
                Salir = true;
                comandoEncontrado = true;
            }
            if (!comandoEncontrado) // si el comando no se encuentra el arroja este error de comando no encontrado
            {
                cout << endl;
                cout << "\tComando no identificado" << endl;
                cout << "\tPor favor ingrese ayuda con el comando que necesita ayuda con el comando  (ayuda listar_departamentos) o "
                     << "\n "
                     << "\tDijite ayuda general para ver todos los comandos disponibles para ayudarlo para tener mas informacion de los comandos " << endl;
                cout << endl;
                tokens.clear();
            }
            else
            {
                tokens.clear(); // esto borra el contenido de tokens para que no siga ejecutando el comando del for y asi termine con lo assignado
            }
        }
    } while (!Salir);
    return 0;
}
