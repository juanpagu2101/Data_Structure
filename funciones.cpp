#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <string>
#include <algorithm>
#include <string>
#include <time.h>
#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <list>
#include "funciones.h"
#include "sstream"
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <iomanip>
#include <math.h>
#define MAX_SIZE 12
#define MAX_SIZEcol 112
#define PI 3.14159265358979323846
#define Char_size 256
using namespace std;

bool Existencia_Departamento_Municipio(string Codigo, list<Divipola> &Lista)
{
    list<Divipola>::iterator iter;
    for (iter = Lista.begin(); iter != Lista.end(); ++iter)
    {
        if (iter->Codigo == Codigo)
        {
            return true;
        }
    }
    return false;
}

void Contar_Municipios_Poblaciones(list<Divipola> &Departamentos, string Codigo, int indicador)
{
    list<Divipola>::iterator iter;

    int Codigo1_Auxiliar;
    int Codigo2_Auxiliar;

    for (iter = Departamentos.begin(); iter != Departamentos.end(); iter++)
    {
        Codigo1_Auxiliar = atoi(Codigo.c_str());
        if (indicador == 0)
        {
            Codigo1_Auxiliar = Codigo1_Auxiliar / 1000;
        }
        else if (indicador == 1)
        {
            Codigo1_Auxiliar = Codigo1_Auxiliar / 1000000;
        }
        Codigo2_Auxiliar = atoi(iter->Codigo.c_str());
        if (Codigo1_Auxiliar == Codigo2_Auxiliar)
        {
            if (indicador == 0)
            {
                int Numero_Municipios = atoi(iter->Latitud.c_str());
                Numero_Municipios += 1;
                iter->Latitud = to_string(Numero_Municipios);
            }
            else if (indicador == 1)
            {
                int Numero_Poblaciones = atoi(iter->Longitud.c_str());
                Numero_Poblaciones += 1;
                iter->Longitud = to_string(Numero_Poblaciones);
            }
        }
    }
}

void Cargar_divipola(list<Divipola> &Departamentos, list<Divipola> &Municipios, list<Divipola> &Poblaciones)
{
    string linea;
    fstream fout;
    char delimitador = ',';

    fout.open("DIVIPOLA_CentrosPoblados.csv", ios::in); // se lee el archivo .csv
    getline(fout, linea);                               // se omite la primera linea del archivo que no contiene nada importante
    setlocale(LC_CTYPE, "");
    while (getline(fout, linea))
    {
        Divipola Auxiliar;
        string Auxiliar_Verificacion;

        stringstream stream(linea); // convertir la cadena a un stream

        getline(stream, Auxiliar_Verificacion, delimitador);

        if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Departamentos) == false)
        {
            Divipola Departamento_Auxiliar;
            Departamento_Auxiliar.Codigo = Auxiliar_Verificacion;

            getline(stream, Departamento_Auxiliar.Nombre, delimitador);

            Departamento_Auxiliar.Longitud = "0";

            Departamento_Auxiliar.Latitud = "0";

            Departamentos.push_back(Departamento_Auxiliar);
        }
        else if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Departamentos) == true)
        {
            getline(stream, Auxiliar_Verificacion, delimitador);
        }

        getline(stream, Auxiliar_Verificacion, delimitador);

        if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Municipios) == false)
        {
            Divipola Municipio_Auxiliar;
            Municipio_Auxiliar.Codigo = Auxiliar_Verificacion;

            getline(stream, Municipio_Auxiliar.Nombre, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Municipio_Auxiliar.Latitud, delimitador);

            getline(stream, Municipio_Auxiliar.Longitud, delimitador);

            Municipios.push_back(Municipio_Auxiliar);

            Contar_Municipios_Poblaciones(Departamentos, Municipio_Auxiliar.Codigo, 0);
        }
        else if (Existencia_Departamento_Municipio(Auxiliar_Verificacion, Municipios) == true)
        {
            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar.Codigo, delimitador);

            getline(stream, Auxiliar.Nombre, delimitador);

            getline(stream, Auxiliar_Verificacion, delimitador);

            getline(stream, Auxiliar.Latitud, delimitador);

            getline(stream, Auxiliar.Longitud, delimitador);

            Poblaciones.push_back(Auxiliar);

            Contar_Municipios_Poblaciones(Departamentos, Auxiliar.Codigo, 1);
        }
    }
    fout.close();
}

void cargar_SC(list<SistemaCiudades> &SClista, list<Divipola> Municipio)
{
    string linea;
    fstream fout2;
    char delimitador = ';';
    fout2.open("Datos-ICM-2019.csv", ios::in); // se lee el archivo .csv
    setlocale(LC_ALL, "spanish");
    getline(fout2, linea); // se omite la primera linea del archivo que no contiene nada importante
    while (getline(fout2, linea))
    {

        SistemaCiudades nodo;

        stringstream stream(linea); // convertir la cadena a un stream
        getline(stream, nodo.aglomeracion, delimitador);

        getline(stream, nodo.FuncionCiudades, delimitador);

        getline(stream, nodo.cod_dept, delimitador);

        getline(stream, nodo.nom_mpio, delimitador);

        getline(stream, nodo.divipola, delimitador);

        getline(stream, nodo.anio, delimitador);

        getline(stream, nodo.personas, delimitador);

        getline(stream, nodo.hectareas, delimitador);

        SClista.push_back(nodo);
    }
    fout2.close();
}

void Nombre_Departamento(list<Divipola> Departamentos, string Codigo_Departamento)
{
    list<Divipola>::iterator iter;

    for (iter = Departamentos.begin(); iter != Departamentos.end(); iter++)
    {
        if ((iter->Codigo) == Codigo_Departamento)
        {
            cout << endl;
            cout << "\tEl departamento " << iter->Nombre << " esta conformado por " << iter->Latitud << " municipios y " << iter->Longitud << " centros poblados. " << endl;
            cout << endl;
        }
    }
}

// esta funcion despliega toda la informacion de los departamentos
void Listar_Departamentos(list<Divipola> Departamentos, list<Divipola> Municipios, list<Divipola> Poblaciones)
{

    list<Divipola>::iterator iter;

    cout << endl;
    cout << "\t\tCODIGO"
         << "\t\t"
         << "NOMBRE"
         << "\t\t"
         << "NO. MUNICIPIOS"
         << "\t\t"
         << "NO. POBLACIONES" << endl;
    cout << endl;

    for (iter = Departamentos.begin(); iter != Departamentos.end(); ++iter)
    {
        int Contador_Municipios = 0;
        int Contador_Poblaciones = 0;
        cout << "\t\t" << iter->Codigo << "\t\t" << iter->Nombre << "\t\t" << iter->Latitud << "\t\t" << iter->Longitud << endl;
    }
    cout << endl;
}

void Listar_Municipios_Poblaciones(string Codigo, list<Divipola> Lista)
{

    list<Divipola>::iterator iter;

    int Codigo1_Auxiliar;
    int Codigo2_Auxiliar;

    cout << endl;
    cout << "\t\tCODIGO"
         << "\t\t "
         << "NOMBRE"
         << "\t\t"
         << "LATITUD"
         << "\t\t"
         << "LONGITUD" << endl;
    cout << endl;

    for (iter = Lista.begin(); iter != Lista.end(); ++iter)
    {
        Codigo1_Auxiliar = atoi(iter->Codigo.c_str());
        Codigo1_Auxiliar = Codigo1_Auxiliar / 1000;
        Codigo2_Auxiliar = atoi(Codigo.c_str());
        if (Codigo1_Auxiliar == Codigo2_Auxiliar)
        {
            cout << "\t\t" << iter->Codigo << "\t\t" << iter->Nombre << "\t\t" << iter->Latitud << "\t\t" << iter->Longitud << endl;
        }
    }
    cout << endl;
}

/*
funcion para determinar si un municipio esta en el sistema de ciudades usando la divipola para poder
idnetificar a los municipios en la divipola y en el sistema de ciudades
*/
void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<Divipola> Municipios)
{

    bool encontroSCMU = false;
    bool encontroDPMU = false;
    int cod_mpioDi = 0, cod_mpioSC = 0;
    if (SClista.empty())
    {
        cout << "La lista de sistema de ciudades esta vacia primero cargala" << endl;
    }
    if (!SClista.empty())
    {
        list<Divipola>::iterator iter;
        list<SistemaCiudades>::iterator otr;
        for (iter = Municipios.begin(); iter != Municipios.end(); ++iter)
        {
            if (iter->Codigo == codigoMunicipio)
            {
                for (otr = SClista.begin(); otr != SClista.end(); otr++)
                {
                    if (otr->divipola == iter->Codigo)
                    {
                        encontroSCMU = true;
                    }
                }
                encontroDPMU = true;
            }
        }
    }
    if (encontroDPMU == true && encontroSCMU == true)
    {
        cout << "El municipio existe y hace parte del SC" << endl;
    }
    if (encontroDPMU == true && encontroSCMU == false)
    {
        cout << "El municipio existe y no hace parte del SC" << endl;
    }
    if (encontroDPMU == false)
    {
        cout << "El municipio no existe" << endl;
    }
}

// se desplega el menu de ayuda necesario por si el cliente no responde al comando
void ayuda(string menuayuda, bool &comandoEncontrado)
{
    if (menuayuda == "carga_divipola")
    {
        cout << "CARGA_DIVIPOLA nombre_archivo.csv    " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del "
             << "                                                    archivo identificado por nombre_archivo." << endl;
        comandoEncontrado = true;
    }
    cout << endl;
    if (menuayuda == "listar_departamentos")
    {
        cout << "LISTAR_DEPARTAMENTOS   " << '\t' << "Imprime en n lineas (una para cada departamento) la informacion basica del departamento"
             << "                                 que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "listar_municipios")
    {
        cout << "LISTAR_MUNICIPIOS codigo_depto   " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica del "
             << "                                                departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "listar_poblaciones")
    {
        cout << "LISTAR_POBLACIONES codigo_municipio    " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica "
             << "                                                     del departamento que se cargo de la Divipola." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "info_sumaria")
    {
        cout << "INFO_SUMARIA codigo_depto   " << '\t' << "Imprime en una lineas la informacion basica del nombre del departamento que "
             << "                                            corresponde al codigo dado como parametro junto con la cantidad de municipios y "
             << "                                        centros poblados que lo conforman" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "carga_SC")
    {
        cout << "CARGA_SC nombre_archivo    " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del archivo "
             << "                                            identificado por nombre_archivo con la informacion basica para representar el "
             << "                                          sistema de ciudades." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "esta_en_sistema")
    {
        cout << "ESTA_EN_SISTEMA codigo_municipio   " << '\t' << "Determina si un municipio, con codigo dado por el usuario, existe "
             << "                                                      dentro de las municipios definidos en el Sistema de Ciudades y cargados "
             << "                                                desde el archivo correspondiente." << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "aglomeracion")
    {
        cout << "AGLOMERACION   " << '\t' << "El comando debe crear los componentes C2, aglomeraciones urbanas, como componentes del "
             << "                                 sistema de Ciudades, de acuerdo con los datos guardados en memoria" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "uninodal")
    {
        cout << "UNINODAL   " << '\t' << "El comando debe crear los componentes C1, ciudades uninodales, como componentes del sistema "
             << "                            de Ciudades, de acuerdo con los datos guardados en memoria" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "capital_menor")
    {
        cout << "CAPITAL_MENOR  " << '\t' << "El comando debe crear los componentes C3, ciudades capitales menores de cien mil habitantes,"
             << "                            como componentes del sistema de Ciudades, de acuerdo con los datos guardados en memoria" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "reporte")
    {
        cout << "REPORTE    " << '\t' << "El comando debe crear un reporte con los datos del sistema" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "codificar")
    {
        cout << "CODIFICAR nombre_archivo.icmbin    " << '\t' << "El comando debe cargar en memoria la informaci�n completa del �ndice "
             << "                                                   de Ciudades Modernas (ICM) y generar el archivo binario con la correspondiente "
             << "                                         codificaci�n de Huffman con toda la informaci�n que lo compone, almacen�ndolo "
             << "                                          en disco bajo el nombre: nombre_archivo.icmbin" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "decodificar")
    {
        cout << "DECODIFICAR nombre_archivo.icmbin   " << '\t' << "El comando debe cargar en memoria los datos contenidas en el archivo "
             << "                                                   binario nombre_archivo.icmbin , que contiene una codificaci�n Huffman de "
             << "                                               toda la informaci�n que compone el �ndice de Ciudades Modernas y debe "
             << "                                                  mostrarlo decodificado en pantalla" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "distancia")
    {
        cout << "DISTANCIA Aglomeracion                         " << '\t' << "El comando debe calcular la distancia en kilómetros entre el centro "
             << "                                                    de la aglomeración y cada una de las ciudades en la aglomeración      "
             << "                                                  utilizando los datos de latitud y longitud que tienen los       "
             << "                                                        municipios en la Divipola y guardarlos en la estructura  "
             << "                                                               del Sistema de Ciudades" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "ruta_mas_corta")
    {
        cout << "RUTA_MAS_CORTA Aglomeracion                    " << '\t' << "El comando debe imprimir en pantalla la secuencia de vértices del   "
             << "                                                    grafo que describen la ruta más corta entre el centro de la secuencia "
             << "                                                  aglomeracion y cada una de las ciudades en la aglomeración. Así "
             << "                                                        mismo, debe imprimir el costo total de la ruta en        "
             << "                                                               kilómetros" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "ciudad_remota")
    {
        cout << "CIUDAD_REMOTA Aglomeracion                    " << '\t' << "Para la ciudad centro de la aglomeración el comando busca la ciudad  "
             << "                                                   en la aglomeración más remota, y debe imprimir en pantalla la         "
             << "                                                  secuencia de vértices que describen la ruta entre el centro de  "
             << "                                                        de la aglomeracion y la ciudad en la aglomeracion mas    "
             << "                                                               más remota, y el costo total de la ruta en kilometros" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "salir")
    {
        cout << "SALIR  " << '\t' << "El comando permite finalizar la ejecuci�n del programa" << endl;
        comandoEncontrado = true;
    }
    if (menuayuda == "general")
    {
        cout << endl;
        cout << "carga_divipola DIVIPOLA_CentrosPoblados.csv    " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del "
             << "                                                    archivo identificado por nombre_archivo." << endl;
        cout << endl;
        cout << "listar_departamentos                           " << '\t' << "Imprime en n lineas (una para cada departamento) la informacion basica "
             << "                                                 del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "LISTAR_MUNICIPIOS codigo_depto                 " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica "
             << "                                                    del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "LISTAR_POBLACIONES codigo_municipio            " << '\t' << "Imprime en n lineas (una para cada municipio) la informacion basica "
             << "                                                    del departamento que se cargo de la Divipola." << endl;
        cout << endl;
        cout << "INFO_SUMARIA codigo_depto                      " << '\t' << "Imprime en una lineas la informacion basica del nombre del          "
             << "                                                    departamento que corresponde al codigo dado como parametro junto con la"
             << "                                                 cantidad de municipios y centros poblados que lo conforman." << endl;
        cout << endl;
        cout << "CARGA_SC nombre_archivo                        " << '\t' << "Carga en una o mas estructuras de datos en memoria el contenido del "
             << "                                                    archivo identificado por nombre_archivo con la informacion basica para "
             << "                                                 representar el sistema de ciudades." << endl;
        cout << endl;
        cout << "ESTA_EN_SISTEMA codigo_municipio               " << '\t' << "Determina si un municipio, con codigo dado por el usuario, existe   "
             << "                                                    dentro de las municipios definidos en el Sistema de Ciudades y cargados"
             << "                                                 desde el archivo correspondiente." << endl;
        cout << endl;
        cout << "AGLOMERACION                                   " << '\t' << "El comando debe crear los componentes C2, aglomeraciones urbanas,   "
             << "                                                    como componentes del sistema de Ciudades, de acuerdo con los datos     "
             << "                                                 guardados en memoria." << endl;
        cout << endl;
        cout << "UNINODAL                                       " << '\t' << "El comando debe crear los componentes C1, ciudades uninodales, como "
             << "                                                    componentes del sistema de Ciudades, de acuerdo con los datos guardados"
             << "                                                 en memoria." << endl;
        cout << endl;
        cout << "CAPITAL_MENOR                                  " << '\t' << "El comando debe crear los componentes C3, ciudades capitales menores"
             << "                                                    de cien mil habitantes, como componentes del sistema de Ciudades, de   "
             << "                                                 acuerdo con los datos guardados en memoria." << endl;
        cout << endl;
        cout << "REPORTE                                        " << '\t' << "El comando debe crear un reporte con los datos del sistema." << endl;
        cout << endl;
        cout << "CODIFICAR nombre_archivo.icmbin                " << '\t' << "El comando debe cargar en memoria la informaci�n completa del �ndice"
             << "                                                    de Ciudades Modernas (ICM) y generar el archivo binario con la        "
             << "                                                  correspondiente codificaci�n de Huffman con toda la informaci�n"
             << "                                                         que lo compone, almacen�ndolo en disco bajo el nombre: "
             << "                                                                 nombre_archivo.icmbin" << endl;
        cout << endl;
        cout << "DECODIFICAR nombre_archivo.icmbin              " << '\t' << "El comando debe cargar en memoria los datos contenidas en el archivo"
             << "                                                    binario nombre_archivo.icmbin , que contiene una codificaci�n Huffman "
             << "                                                  de toda la informaci�n que compone el �ndice de Ciudades Modernas"
             << "                                                       y debe mostrarlo decodificado en pantalla" << endl;
        cout << endl;
        cout << "DISTANCIA Aglomeracion                         " << '\t' << "El comando debe calcular la distancia en kilómetros entre el centro "
             << "                                                    de la aglomeración y cada una de las ciudades en la aglomeración      "
             << "                                                  utilizando los datos de latitud y longitud que tienen los       "
             << "                                                        municipios en la Divipola y guardarlos en la estructura  "
             << "                                                               del Sistema de Ciudades" << endl;
        cout << endl;
        cout << "RUTA_MAS_CORTA Aglomeracion                    " << '\t' << "El comando debe imprimir en pantalla la secuencia de vértices del   "
             << "                                                    grafo que describen la ruta más corta entre el centro de la secuencia "
             << "                                                  aglomeracion y cada una de las ciudades en la aglomeración. Así "
             << "                                                        mismo, debe imprimir el costo total de la ruta en        "
             << "                                                               kilómetros" << endl;
        cout << endl;
        cout << "CIUDAD_REMOTA Aglomeracion                    " << '\t' << "Para la ciudad centro de la aglomeración el comando busca la ciudad  "
             << "                                                   en la aglomeración más remota, y debe imprimir en pantalla la         "
             << "                                                  secuencia de vértices que describen la ruta entre el centro de  "
             << "                                                        de la aglomeracion y la ciudad en la aglomeracion mas    "
             << "                                                               más remota, y el costo total de la ruta en kilometros" << endl;
        cout << endl;
        cout << "SALIR                                          " << '\t' << "Termina la ejecucion de la aplicacion." << endl;
        comandoEncontrado = true;
    }
    cout << endl;
}

/*
Funcion del capitales menores  que debe sacar la lista de ciudades con la poblacion menor a 100.000
*/

void capitalesmenores(list<SistemaCiudades> SClista, list<ciudadescapitales> &CiuCap)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int poblacion = 0;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion < 100000 && iter->FuncionCiudades != "Fuera SC")
        {
            nodoCC.funcionCiudades = iter->FuncionCiudades;
            nodoCC.cod_dept = iter->cod_dept;
            nodoCC.nom_mpio = iter->nom_mpio;
            nodoCC.divipola = iter->divipola;
            CiuCap.push_back(nodoCC);
        }
    }
}

bool Verificar_Aglomeracion(list<Aglomeracion> &Aglomeraciones, string Nombre_Aglomeracion)
{
    bool bandera = true;
    if (Aglomeraciones.empty())
    {
        bandera = false;
    }
    else
    {
        list<Aglomeracion>::iterator iter;

        for (iter = Aglomeraciones.begin(); iter != Aglomeraciones.end(); iter++)
        {
            if ((iter->Nombre) == Nombre_Aglomeracion)
            {
                return 0;
            }
            else
            {
                bandera = false;
            }
        }
    }
    if (bandera == false)
    {
        Aglomeracion Auxiliar;
        Auxiliar.Nombre = Nombre_Aglomeracion;
        Aglomeraciones.push_back(Auxiliar);
        return 1;
    }
    return 0;
}

void Crear_Aglomeraciones(list<SistemaCiudades> SClista, list<Aglomeracion> &Aglomeraciones)
{
    list<SistemaCiudades>::iterator iter;
    list<Aglomeracion>::iterator iter_aux;

    Municipios_Ciudades Auxiliar_Componente;
    int Contador_Aglomeraciones = 0;
    int Contador_Ciudades = 0;

    for (iter = SClista.begin(); iter != SClista.end(); iter++)
    {
        Auxiliar_Componente.Divipola = iter->divipola;
        Auxiliar_Componente.Nombre = iter->nom_mpio;
        Auxiliar_Componente.Personas = iter->personas;
        Auxiliar_Componente.Hectareas = iter->hectareas;
        Auxiliar_Componente.Nombre_Aglomeracion = iter->aglomeracion;

        if ((iter->FuncionCiudades) == "Centro aglomeracion")
        {
            if (Verificar_Aglomeracion(Aglomeraciones, iter->aglomeracion) == 1)
            {
                Contador_Aglomeraciones += 1;
            }

            for (iter_aux = Aglomeraciones.begin(); iter_aux != Aglomeraciones.end(); iter_aux++)
            {
                if ((iter_aux->Nombre) == iter->aglomeracion)
                {
                    iter_aux->Ciudad_Principal = Auxiliar_Componente;
                    iter_aux->Ciudades_Componentes.push_back(Auxiliar_Componente);
                }
            }
            Contador_Ciudades += 1;
        }
        else if ((iter->FuncionCiudades) == "En aglomeracion")
        {
            if (Verificar_Aglomeracion(Aglomeraciones, iter->aglomeracion) == 1)
            {
                Contador_Aglomeraciones += 1;
            }

            for (iter_aux = Aglomeraciones.begin(); iter_aux != Aglomeraciones.end(); iter_aux++)
            {
                if ((iter_aux->Nombre) == iter->aglomeracion)
                {
                    iter_aux->Ciudades_Componentes.push_back(Auxiliar_Componente);
                }
            }
            Contador_Ciudades += 1;
        }
    }
    cout << endl;
    cout << "\tSe crearon " << Contador_Aglomeraciones << " aglomeraciones urbanas, compuestas por " << Contador_Ciudades << " municipios" << endl;
    cout << endl;
}

void Crear_Uninodales(list<SistemaCiudades> SClista, list<Municipios_Ciudades> &Ciudades_Uninodales)
{
    list<SistemaCiudades>::iterator iter;

    Municipios_Ciudades Auxiliar;

    for (iter = SClista.begin(); iter != SClista.end(); iter++)
    {
        if ((iter->FuncionCiudades) == "Uninodal")
        {
            Auxiliar.Divipola = iter->divipola;
            Auxiliar.Nombre = iter->nom_mpio;
            Auxiliar.Personas = iter->personas;
            Auxiliar.Hectareas = iter->hectareas;
            Ciudades_Uninodales.push_back(Auxiliar);
        }
    }
}

/*

Funcion reporte que debe sacar el reporte del documento
*/

int totalaglomeracionesUrbanas(list<SistemaCiudades> SClista, vector<string> &codigosdeptoaglo)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    setlocale(LC_CTYPE, "Spanich");
    string aglo = "Centro aglomeracion";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {

        setlocale(LC_CTYPE, "Spanich");
        if (iter->FuncionCiudades == aglo)
        {
            codigosdeptoaglo.push_back(iter->aglomeracion);
            contador++;
        }
    }
    return contador;
}
int totalCiudadesuni(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    setlocale(LC_CTYPE, "Spanich");
    string uni = "Uninodal";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {

        setlocale(LC_CTYPE, "Spanich");
        if (iter->FuncionCiudades == uni)
        {
            contador++;
        }
    }
    return contador;
}

int ciudadesMenores(list<SistemaCiudades> SClista, vector<string> &codigosmunCME)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    int poblacion = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion <= cien && iter->FuncionCiudades == "Fuera SC")
        {
            codigosmunCME.push_back(iter->divipola);
            contador++;
        }
    }
    return contador;
}

int ciudadesMayores(list<SistemaCiudades> SClista, vector<string> &codigosmunCMA)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    int poblacion = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion >= cien && iter->FuncionCiudades == "Fuera SC")
        {
            codigosmunCMA.push_back(iter->divipola);
            contador++;
        }
    }
    return contador;
}

int totalMuniAglo(list<SistemaCiudades> SClista, vector<string> codigosdeptoaglo)
{
    list<SistemaCiudades>::iterator iter;
    list<SistemaCiudades>::iterator iter2;
    vector<string>::iterator viter;
    int contador = 0;
    setlocale(LC_CTYPE, "Spanich");
    string aglo = "Centro aglomeracion";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        for (int i = 0; i < codigosdeptoaglo.size(); i++)
        {
            if (iter->aglomeracion == codigosdeptoaglo[i])
            {
                contador++;
            }
        }
    }
    return contador;
}
int poblaciontotal(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int total = 0;
    int pob = 0;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        pob = stoi(iter->personas);
        total = pob + total;
    }
    return total;
}

int totalpoblaaglo(list<SistemaCiudades> SClista, vector<string> codigosdeptoaglo)
{
    list<SistemaCiudades>::iterator iter;
    list<SistemaCiudades>::iterator iter2;
    int contador = 0;
    int pob = 0;
    setlocale(LC_CTYPE, "Spanich");
    string aglo = "Centro aglomeracion";
    setlocale(LC_CTYPE, "Spanich");
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        for (int i = 0; i < codigosdeptoaglo.size(); i++)
        {
            if (iter->aglomeracion == codigosdeptoaglo[i])
            {
                pob = stoi(iter->personas);
                contador = pob + contador;
            }
        }
    }
    return contador;
}

int totalPoblaUni(list<SistemaCiudades> SClista)
{

    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    int pob = 0;
    setlocale(LC_CTYPE, "Spanich");
    string uni = "Uninodal";
    setlocale(LC_CTYPE, "Spanich");

    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {

        setlocale(LC_CTYPE, "Spanich");
        if (iter->FuncionCiudades == uni)
        {
            pob = stoi(iter->personas);
            contador = pob + contador;
        }
    }
    return contador;
}

int TotalPobCiudMayor(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    int poblacion = 0;
    int pob = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion >= cien && iter->FuncionCiudades == "Fuera SC")
        {
            pob = stoi(iter->personas);
            contador = pob + contador;
        }
    }
    return contador;
}

int TotalPobCiudMenor(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    int contador = 0;
    int poblacion = 0;
    int pob = 0;
    int cien = 100000;
    for (iter = SClista.begin(); iter != SClista.end(); ++iter)
    {
        poblacion = stoi(iter->personas);
        if (poblacion <= cien && iter->FuncionCiudades == "Fuera SC")
        {
            pob = stoi(iter->personas);
            contador = pob + contador;
        }
    }
    return contador;
}

int totalmunCMayores(list<SistemaCiudades> SClista, vector<string> codigosmunCMA)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    for (int i = 0; i < codigosmunCMA.size(); i++)
    {
        for (iter = SClista.begin(); iter != SClista.end(); ++iter)
        {
            if (codigosmunCMA[i] == iter->divipola)
            {
                contador++;
            }
        }
    }

    return contador;
}
int totalmunCMEnores(list<SistemaCiudades> SClista, vector<string> codigosmunCMA)
{
    list<SistemaCiudades>::iterator iter;
    ciudadescapitales nodoCC;
    int contador = 0;
    for (int i = 0; i < codigosmunCMA.size(); i++)
    {
        for (iter = SClista.begin(); iter != SClista.end(); ++iter)
        {
            if (codigosmunCMA[i] == iter->divipola)
            {
                contador++;
            }
        }
    }
    return contador;
}

void reporte(list<SistemaCiudades> SClista)
{
    list<SistemaCiudades>::iterator iter;
    setlocale(LC_CTYPE, "Spanich");
    vector<string> codigosdeptoaglo;
    vector<string> codigosmunCMA;
    vector<string> codigosmunCME;

    float totaglo = totalaglomeracionesUrbanas(SClista, codigosdeptoaglo);
    float totaluni = totalCiudadesuni(SClista);
    float ciudadesmascien = ciudadesMayores(SClista, codigosmunCMA);
    float ciudadesmenoscien = ciudadesMenores(SClista, codigosmunCME);
    int totalMunCMA = totalmunCMayores(SClista, codigosmunCMA);
    int totalMunCME = totalmunCMayores(SClista, codigosmunCME);
    float totalSC = totaglo + totaluni;
    float totalCol = SClista.size();
    float totalmunAglo = totalMuniAglo(SClista, codigosdeptoaglo);
    float totalMuni = totalmunAglo + totaluni;
    int totalpob = poblaciontotal(SClista);
    int totPobAglo = totalpoblaaglo(SClista, codigosdeptoaglo);
    int totPobUni = totalPoblaUni(SClista);
    int totPobCMA = TotalPobCiudMayor(SClista);
    int totPobCME = TotalPobCiudMenor(SClista);
    float totPobMun = totPobAglo + totPobUni;
    float clac = totalMuni / totalCol;
    float calcpob = totPobMun / totalpob;
    float probatot = clac * 100;
    float probapob = calcpob * 100;
    cout << endl;
    cout << "\t\tSistema Ciudades"
         << "\t\t\t\t"
         << "Municipios"
         << "\t"
         << "Poblacion Total"
         << endl;
    cout << endl;
    cout << "\t\t Ciudades que hacen parte del sistema" << endl;
    cout << "\t\t Aglomeraciones urbanas (" << totaglo << ")"
         << "\t\t\t\t" << totalmunAglo << "\t\t" << totPobAglo << endl;
    cout << "\t\t Ciudades Uninodales (" << totaluni << ")"
         << "\t\t\t\t" << totaluni << "\t\t" << totPobUni << endl;
    cout << "\t\t Ciudades furea del sistema" << endl;
    cout << "\t\t Ciudades con mas de cien mil habitantes (" << ciudadesmascien << ")"
         << "\t\t" << totalMunCMA << "\t\t" << totPobCMA << endl;
    cout << "\t\t Ciudades con menos de cien mil habitantes (" << ciudadesmenoscien << ")"
         << "\t" << totalMunCME << "\t\t" << totPobCME << endl;
    cout << "\t\t Total sistema de ciudades (" << totalSC << ")"
         << "\t\t\t\t" << totalMuni << "\t\t" << totPobMun << endl;
    cout << "\t\t % con respecto a colombia (" << totalCol << ")"
         << "\t\t\t"
         << probatot << " %"
         << "\t\t"
         << probapob << " %" << endl;
    cout << "\t\t Total colombia "
         << "\t\t\t\t\t" << totalCol << "\t\t" << totalpob << endl;
}

// Estructura del arbol de Huffman
struct nodo
{
    unsigned char caracter;
    long long int Frecuencia;
    nodo *izquierda;
    nodo *derecha;
    nodo(unsigned char c, long long int f, nodo *l = NULL, nodo *r = NULL)
    {
        caracter = c;
        Frecuencia = f;
        izquierda = l;
        derecha = r;
    }
};
// Esta funcion se encarga de comparar el nodo recien insertado con otros dos (serian sus hijos) para asi poder escoger el mas pequeño e intercambiarlo
void Minimo_monticulo(vector<nodo *> &A, int i, int length)
{
    int menor = i;
    if (2 * i + 1 <= length && A[2 * i + 1]->Frecuencia < A[i]->Frecuencia)
    {
        menor = 2 * i + 1;
        if (2 * i + 2 <= length && A[2 * i + 2]->Frecuencia < A[2 * i + 1]->Frecuencia)
            menor = 2 * i + 2;
    }
    else if (2 * i + 2 <= length && A[2 * i + 2]->Frecuencia < A[i]->Frecuencia)
        menor = 2 * i + 2;
    if (menor != i)
    {
        swap(A[i], A[menor]);
        Minimo_monticulo(A, menor, length);
    }
}
// Extrear el minimo del monticulo
nodo *Extraer_menor(vector<nodo *> &A)
{
    if (A.size() < 1)
        return NULL;
    nodo *minimo = A[0];
    A[0] = A.back();
    A.pop_back();
    Minimo_monticulo(A, 0, A.size() - 1);
    return minimo;
}
// Esta funcion inserta el caracter en el monticulo
void Insertar_min_mon(vector<nodo *> &A, nodo *elemento)
{
    A.push_back(elemento);
    int i = A.size() - 1;
    while (i > 0 && A[(i - 1) / 2]->Frecuencia > A[i]->Frecuencia)
    {
        swap(A[i], A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
// con esta funcion se construye el monticulo
void Crear_monticulo(vector<nodo *> &A, int length)
{
    for (int i = (length - 1) / 2; i >= 0; i--)
    {
        Minimo_monticulo(A, i, length);
    }
}
// Esta funcion se encarga de almacenar cada caracter en el vector
void Guardar_car(nodo *raiz, char cod_simple[], int index, vector<long long int> &mapaHuffman)
{
    if (raiz->izquierda)
    {
        cod_simple[index] = '0';
        Guardar_car(raiz->izquierda, cod_simple, index + 1, mapaHuffman);
    }
    if (raiz->derecha)
    {
        cod_simple[index] = '1';
        Guardar_car(raiz->derecha, cod_simple, index + 1, mapaHuffman);
    }
    if (!raiz->izquierda && !raiz->izquierda)
    {
        for (int i = index; i >= 0; i--)
        {
            if (i != index)
            {
                mapaHuffman[raiz->caracter] *= 10;
                mapaHuffman[raiz->caracter] += cod_simple[i] - '0';
            }
            else
                mapaHuffman[raiz->caracter] = 1;
        }
    }
}
// Esta funcion se encarga de almacenar el arbol al archivo
void Guardar_Arbol(ofstream &input, nodo *raiz)
{
    if (!raiz->izquierda && !raiz->derecha)
    {
        input << '1';
        input << raiz->caracter;
    }
    else
    {
        input << '0';
        Guardar_Arbol(input, raiz->izquierda);
        Guardar_Arbol(input, raiz->derecha);
    }
}
// En esta funcion se desarrolla el algoritmo de Huffman
nodo *Huffman(long long int Contador[])
{
    vector<nodo *> monticulo;
    for (int i = 0; i < Char_size; i++)
        if (Contador[i] != 0)
            monticulo.push_back(new nodo(i, Contador[i]));
    Crear_monticulo(monticulo, monticulo.size() - 1);
    while (monticulo.size() != 1)
    {
        nodo *Z = new nodo(-1, 0, Extraer_menor(monticulo), Extraer_menor(monticulo));
        Z->Frecuencia = Z->izquierda->Frecuencia + Z->derecha->Frecuencia;
        Insertar_min_mon(monticulo, Z);
    }
    return (monticulo[0]);
}
// Con esta funcion se utiliza para poder volver a escribir en un archivo per ya comprimido
void Escrbir_codif(ifstream &input, ofstream &output, vector<long long int> &mapaHuffman)
{
    char da;
    unsigned char bits;
    long long int contador = 0;
    while (input.get(da))
    {
        long long int temp = mapaHuffman[static_cast<unsigned char>(da)];
        while (temp != 1)
        {
            bits <<= 1;
            if ((temp % 10) != 0)
                bits |= 1;
            temp /= 10;
            contador++;
            if (contador == 8)
            {
                output << bits;
                contador = bits = 0;
            }
        }
    }
    while (contador != 8)
    {
        bits <<= 1;
        contador++;
    }
    output << bits;
    output.close();
}

int codificar()
{
    vector<long long int> mapaHuffman;
    mapaHuffman.resize(Char_size);
    int error = 0;
    long long int Contador[Char_size] = {0};
    ifstream input_file("Datos-ICM-2019.csv", ios::binary);
    if (!input_file.good())
    {
        perror("Error con el codigo\t");
        error = 1;
    }
    char da;
    while (input_file.get(da))
        Contador[static_cast<unsigned char>(da)]++;
    input_file.clear();
    input_file.seekg(0);
    nodo *arbol = Huffman(Contador);
    ofstream output_file("codificado.icmbin", ios::binary);
    if (!output_file.good())
    {
        perror("Error con el codigo\t");
        error = 2;
    }
    output_file << arbol->Frecuencia;
    output_file << ',';
    Guardar_Arbol(output_file, arbol);
    output_file << ' ';
    char cod_simple[16];
    Guardar_car(arbol, cod_simple, 0, mapaHuffman);
    Escrbir_codif(input_file, output_file, mapaHuffman);
    input_file.close();
    output_file.close();
    return error;
}

// Estructura del nodo del arbol de Huffman para poder decodificar
struct Nodo
{
    unsigned char dato;
    Nodo *izq;
    Nodo *der;
    Nodo(char c, Nodo *l = NULL, Nodo *r = NULL)
    {
        dato = c;
        izq = l;
        der = r;
    }
};
// Crear el arbol de Huffman utilizando el archivo comprimido
Nodo *CrearArbol(ifstream &input)
{
    char da;
    input.get(da);
    if (da == '1')
    {
        input.get(da);
        return (new Nodo(da));
    }
    else
    {
        Nodo *izq = CrearArbol(input);
        Nodo *der = CrearArbol(input);
        return (new Nodo(-1, izq, der));
    }
}
// Se hace uso de esta funcion para poder decodificar cada item binario de acuerdo al arbol creado
void decodificar(ifstream &input, string Nom_archivo, Nodo *raiz, long long int Frecuencia_total)
{
    ofstream output((Nom_archivo.erase(Nom_archivo.size() - 4)).c_str(), ios::binary);
    if (!output.good())
    {
        perror("Error:\t");
        // exit(-1);
    }
    bool eof_flag = false;
    char bits;
    Nodo *puntero = raiz;
    while (input.get(bits))
    {
        int contador = 7;
        while (contador >= 0)
        {
            if (!puntero->izq && !puntero->der)
            {
                output << puntero->dato;
                Frecuencia_total--;
                if (!Frecuencia_total)
                {
                    eof_flag = true;
                    break;
                }
                puntero = raiz;
                continue;
            }
            if ((bits & (1 << contador)))
            {
                puntero = puntero->der;
                contador--;
            }
            else
            {
                puntero = puntero->izq;
                contador--;
            }
        }
        if (eof_flag)
            break;
    }
    output.close();
}

int decodificar()
{
    string Nom_archivo = "codificado.icmbin";
    int error = 0;
    ifstream abrir_archivo(Nom_archivo.c_str(), ios::binary);
    if (!abrir_archivo.good())
    {

        perror("Error con el archivo\t");
        error = 1;
    }
    if (Nom_archivo.find(".icmbin") == string::npos)
    {
        cout << "Error: El archivo ya esta descomprimido\n\n";
        error = 2;
    }
    long long int Frecuencia_total = 0;
    char da;
    while (abrir_archivo.get(da))
    {
        if (da == ',')
            break;
        Frecuencia_total *= 10;
        Frecuencia_total += da - '0';
    }
    Nodo *Arbol_Huffman = CrearArbol(abrir_archivo);
    abrir_archivo.get(da);
    decodificar(abrir_archivo, Nom_archivo, Arbol_Huffman, Frecuencia_total);
    abrir_archivo.close();
    return error;
}

bool Existencia_Aglomeracion(string aglomeracion, list<SistemaCiudades> &Lista)
{
    list<SistemaCiudades>::iterator iter;
    for (iter = Lista.begin(); iter != Lista.end(); ++iter)
    {
        if (iter->aglomeracion == aglomeracion)
        {
            return true;
        }
    }
    return false;
}

double convertToRadians(double val)
{
    return val * PI / 180;
}

double calcularDistanciaEntreDosCoordenadas(double lat1, double lon1, double lat2, double lon2)
{
    // Convertir todas las coordenadas a radianes
    lat1 = convertToRadians(lat1);
    lon1 = convertToRadians(lon1);
    lat2 = convertToRadians(lat2);
    lon2 = convertToRadians(lon2);
    // Aplicar fórmula
    double RADIO_TIERRA_EN_KILOMETROS = 6371;
    double diferenciaEntreLongitudes = (lon2 - lon1);
    double diferenciaEntreLatitudes = (lat2 - lat1);
    double a = pow(sin(diferenciaEntreLatitudes / 2.0), 2) + cos(lat1) * cos(lat2) * pow(sin(diferenciaEntreLongitudes / 2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = RADIO_TIERRA_EN_KILOMETROS * c;
    return d;
}
double strtodouble(string str)
{
    double val;
    istringstream iss(str);
    iss >> val;
    return val;
}

void distanciaAglo(string aglomeracion, list<Aglomeracion> &Aglomeraciones, list<Divipola> &Municipios, list<SistemaCiudades> &SClista, list<distancia> Ldistancias)
{
    long double PIx = 3.141592653589793;
    double RADIO_TIERRA_EN_KILOMETROS = 6371;
    list<Divipola>::iterator itermuni;
    list<Divipola>::iterator itermunicl;
    list<Aglomeracion>::iterator iteraglo;
    list<SistemaCiudades>::iterator itersistema;
    list<SistemaCiudades>::iterator itersistema2;
    list<distancia>::iterator iterdistancia;
    distancia dist;
    int contador = 1;
    double lat1 = 0, lat2 = 0, lon1 = 0, lon2 = 0;
    double diskm;
    double codigo;
    string codigoaglo;

    int contadoraglo = 0;
    for (itersistema = SClista.begin(); itersistema != SClista.end(); ++itersistema)
    {
        if (itersistema->aglomeracion == aglomeracion)
        {
            contadoraglo++;
        }
    }
    double anteriorkm = 0;
    double **disclon = new double *[contadoraglo];
    for (int i = 0; i < contadoraglo; i++)
    {
        disclon[i] = new double[contadoraglo];
    }

    int tammatrix = 0;
    int i = 0, j = 0;
    bool centroencontrado = false;
    string nombremuni;
    for (itersistema = SClista.begin(); itersistema != SClista.end(); ++itersistema)
    {
        for (itermuni = Municipios.begin(); itermuni != Municipios.end(); ++itermuni)
        {
            if (itersistema->aglomeracion == aglomeracion && itersistema->FuncionCiudades == "Centro aglomeracion" && itersistema->divipola == itermuni->Codigo)
            {
                nombremuni = itermuni->Nombre;
            }
            if (itersistema->aglomeracion == aglomeracion && itersistema->divipola == itermuni->Codigo)
            {

                codigoaglo = itersistema->divipola;
                lat1 = strtodouble(itermuni->Latitud);
                lon1 = strtodouble(itermuni->Longitud);

                for (itersistema2 = SClista.begin(); itersistema2 != SClista.end(); ++itersistema2)
                {
                    for (itermunicl = Municipios.begin(); itermunicl != Municipios.end(); ++itermunicl)
                    {
                        if (itersistema2->aglomeracion == aglomeracion && itersistema2->divipola == itermunicl->Codigo)
                        {
                            lat2 = strtodouble(itermunicl->Latitud);

                            lon2 = strtodouble(itermunicl->Longitud);
                            diskm = calcularDistanciaEntreDosCoordenadas(lat1, lon1, lat2, lon2);
                            dist.Codigo = itermuni->Codigo;
                            dist.distanciakm = diskm;
                            Ldistancias.push_back(dist);
                        }
                    }
                }
            }
        }
    }

    for (iterdistancia = Ldistancias.begin(); iterdistancia != Ldistancias.end(); ++iterdistancia)
    {
        if (j < contadoraglo)
        {
            disclon[i][j] = iterdistancia->distanciakm;
            j++;
        }
        if (j == contadoraglo)
        {
            j = 0;
            i++;
        }
    }
    // aca se imprime la matriz para verificar que se hace bien
    /* for (int i = 0; i < contadoraglo; i++)
        {
            for (int j = 0; j < contadoraglo; j++)
            {
                cout << disclon[i][j] << " ";
            }
            cout << endl;
        }*/

    for (iteraglo = Aglomeraciones.begin(); iteraglo != Aglomeraciones.end(); ++iteraglo)
    {
        if (iteraglo->Nombre == nombremuni)
        {
            iteraglo->Distancias = disclon;
        }
    }
}