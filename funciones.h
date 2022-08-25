#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

bool Existencia_Departamento_Municipio(string Codigo, list<Divipola> &Lista);

bool Existencia_Aglomeracion(string codglomeracion, list<SistemaCiudades> &Lista);

void Cargar_divipola(list<Divipola> &Departamentos, list<Divipola> &Municipios, list<Divipola> &Poblaciones);

void cargar_SC(list<SistemaCiudades> &SClista, list<Divipola> Municipio);

void Nombre_Departamento(list<Divipola> Departamentos, string Codigo_Departamento);

void Contar_Municipios_Poblaciones(list<Divipola> &Departamentos, string Codigo, int indicador);

void Listar_Departamentos(list<Divipola> Departamentos, list<Divipola> Municipios, list<Divipola> Poblaciones);

void Listar_Municipios_Poblaciones(string Codigo, list<Divipola> Lista);

void estaEnSistema(string codigoMunicipio, list<SistemaCiudades> SClista, list<Divipola> Municipios);

void ayuda(string menuayuda, bool &comandoEncontrado);

void capitalesmenores(list<SistemaCiudades> SClista, list<ciudadescapitales> &CiuCap);

vector<string> buscarpoblacion(string codigomun, string codigopob, list<Divipola> Municipios);

void reporte(list<SistemaCiudades> SClista);

bool Verificar_Aglomeracion(list<Aglomeracion> &Aglomeraciones, string Nombre_Aglomeracion);

void Crear_Aglomeraciones(list<SistemaCiudades> SClista, list<Aglomeracion> &Aglomeraciones);

void Crear_Uninodales(list<SistemaCiudades> SClista, list<Municipios_Ciudades> &Ciudades_Uninodales);

int codificar();

int decodificar();

double convertToRadians(double val);

void distanciaAglo(string aglomeracion, list<Aglomeracion> &Aglomeraciones, list<Divipola> &Municipios, list<SistemaCiudades> &SClista, list<distancia> Ldistancias);
#endif
