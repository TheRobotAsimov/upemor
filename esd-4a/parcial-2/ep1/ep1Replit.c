#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Constantes para la urgencia de la cita
#define ALTA 2
#define MEDIA 1
#define BAJA 0

//estructura para la direccion del paciente
struct direccion
{
    char calle[30];
    char colonia[30];
    char municipio[15];
    int numero;
    int cp;
};

//estructura para los datos del paciente
typedef struct
{
    char nombre[40];
    int edad;
    struct direccion dirPaciente; //estructura anidada para ingresar los datos del paciente
    float estatura;
}paciente;

//estructura para los datos del medico
typedef struct
{
    char nombre[40];
    int especialidad;
    /*
    1 - Medicina General
    2 - Traumatologia
    3 - Pediatria
    4 - Cardiologia
    5 - Psiquiatría
    */
    struct direccion dirMedico;
    int sueldo;
    float pagoExtra;
    int antiguo;
}medico;

typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha;

//estructura para realizar la gestion de las consultas para cada paciente
typedef struct 
{
    char fecha[11];
    paciente p;
    medico m;
    char sintomas[100];
    int urgeTipo;
    char diagnos[100];
} consulta;

typedef struct
{
  char nombre[40];
  int antiguo;
  int consultas;
} reporteMed;

typedef struct
{
  char municipio[15];
  int consultas;
} consMunicipio;

int menu();
void registroPac(paciente *pacientes);
void registroMed(medico *medicos);
consulta* registroCons(int numConsultas, paciente *pacientes, medico *medicos);
void consulRegistro(int numConsultas, paciente *pacientes, medico *medicos);
//validar datos
int validarNombre(consulta *consultas, paciente  *pacientes, int i);
int validarEdad(consulta *consultas, paciente *pacientes, int i);
int validarNombreMed(consulta *consultas, medico  *medicos, int i);
int validarEspecialidad(consulta *consultas, medico  *medicos, int k);
//Reporte de pacientes atendidos por rango de edad 
void ordenarPorEdad(consulta* consultas, int numConsultas);
void busquedaBinaria(consulta *consultas, int numConsultas, int busqueda);
void mostrarConsEdades(consulta *consultas, int numConsultas);
void compensacion(medico *medicos, consulta *consultas);

void imprimirConsultas (consulta *consultas, int numConsultas);
void busquedaBinFechas (consulta *consultas, int primero, int ultimo, char *fecha_inicio, char *fecha_fin, consulta *aux, int *i);
void quickSortFechas (consulta *consultas, int primero, int ultimo);
void burbujaUrgencia (int consPorUrgencia[3][2]);
void mostrarConsMunicipio (consulta *consultas, int numConsultas);
void busquedaBinMesAnio (consulta *consultas, int primero, int ultimo, char *mes_anio, consulta *aux, int *i);

void contarConsPorUrgencia (consulta *consultas, int numConsultas, int consPorUrgencia[3][2]);
void imprimirConsPorUrgencia (int consPorUrgencia[3][2]);

void contarConsPorMunicipio (char *municipioCons, consMunicipio *municipios, int *numMunicipios);
void quickSortMunicipios (consMunicipio *municipios, int primero, int ultimo);

int main(){
    int opc, numConsultas, busqueda, consPorUrgencia[3][2] = {{BAJA, 0}, {MEDIA, 0}, {ALTA, 0}};
  
// Declaración e inicialización de un arreglo de 5 direcciones
  struct direccion direcciones[5] = {
    {"Calle1", "Colonia1", "Municipio1", 123, 45678},
    {"Calle2", "Colonia2", "Municipio2", 456, 78901},
    {"Calle3", "Colonia3", "Municipio3", 789, 12345},
    {"Calle4", "Colonia4", "Municipio4", 234, 56789},
    {"Calle5", "Colonia5", "Municipio5", 567, 90123}};

// Declaración e inicialización de un arreglo de 5 pacientes
  paciente pacientes[5] = {
    {"Paciente1", 25, direcciones[2], 1.75},
    {"Paciente2", 30, direcciones[0], 1.80},
    {"Paciente3", 40, direcciones[2], 1.70},
    {"Paciente4", 35, direcciones[1], 1.60},
    {"Paciente5", 28, direcciones[2], 1.85}};

// Declaración e inicialización de un arreglo de 5 médicos
  medico medicos[5] = {
    {"Medico1", 1, direcciones[0], 6000, 500, 10},
    {"Medico2", 3, direcciones[1], 7000, 600, 5},
    {"Medico3", 2, direcciones[2], 7500, 550, 15},
    {"Medico4", 4, direcciones[3], 8000, 700, 20},
    {"Medico5", 5, direcciones[2], 9000, 800, 25}};

  fecha fechas[5] = { {1, 10, 2023},
                        {2, 10, 2023},
                        {3, 10, 2023},
                        {4, 10, 2023},
                        {5, 10, 2023}};

  // Municipios de Morelos

  consMunicipio municipios[40];
  int numMunicipios = 0;
  
  consulta consultas[5] = {{"05/10/2025", pacientes[0], medicos[0], "Sintomas1", ALTA, "Diagnostico1"},
                            {"03/10/2025", pacientes[1], medicos[1], "Sintomas2", ALTA, "Diagnostico2"},
                            {"01/10/2025", pacientes[2], medicos[2], "Sintomas3", ALTA, "Diagnostico3"},
                            {"02/10/2025", pacientes[3], medicos[3], "Sintomas4", BAJA, "Diagnostico4"},
                            {"04/09/2023", pacientes[4], medicos[4], "Sintomas5", BAJA, "Diagnostico5"}};
  consulta aux[5];
  int i = -1;
  numConsultas = 5;
    do
    {
        opc=menu();
        switch (opc)
        {
        case 1:
            /*printf("Ingrese el número de consultas a registrar: ");
            scanf("%d", &numConsultas);
            consulta *consultas = registroCons(numConsultas, pacientes, medicos); */
            //consulRegistro(numConsultas, pacientes, 
        case 2:
            ordenarPorEdad(consultas, numConsultas);
            mostrarConsEdades(consultas, numConsultas);
            break;
        // reporte de urgencias
        case 3:
            i = -1;
            imprimirConsultas(consultas, numConsultas);
            quickSortFechas(consultas, 0, numConsultas-1); 
            imprimirConsultas(consultas, numConsultas);
            busquedaBinFechas(consultas, 0, numConsultas-1, "01/10/2023", "05/10/2023", aux, &i);
            if (i != -1)
            {
              imprimirConsultas(aux, i+1);
              contarConsPorUrgencia(aux, i+1, consPorUrgencia);
              printf("Baja: %d\n", consPorUrgencia[BAJA][1]);
              printf("Media: %d\n", consPorUrgencia[MEDIA][1]);
              printf("Alta: %d\n", consPorUrgencia[ALTA][1]);
              burbujaUrgencia(consPorUrgencia);
              imprimirConsPorUrgencia(consPorUrgencia);
              
            }
            else
            {
              printf("\nNo se encontraron consultas con ese rango de fechas\n");
            }
            break;
        // reporte por rango de pacientes por Municipio
        case 4:
            i = -1;
            quickSortFechas(consultas, 0, numConsultas-1); 
            busquedaBinFechas(consultas, 0, numConsultas-1, "01/10/2023", "05/10/2023", aux, &i);
            if (i != -1)
            {
              numMunicipios = 0;
              for (int j=0; j<i+1; j++)
              {
                contarConsPorMunicipio(aux[j].p.dirPaciente.municipio, municipios, &numMunicipios);
              }
              for (int j=0; j<numMunicipios; j++)
              {
                printf("%s: %d\n", municipios[j].municipio, municipios[j].consultas);
              }
            }
            else
            {
              printf("\nNo se encontraron consultas con ese rango de fechas\n");
            }
            
            break;
        // reporte de atenciones por medico
        case 5:
            i = -1;
            printf("\nConsultas recibidas:\n");
            imprimirConsultas(consultas, numConsultas);
            quickSortFechas(consultas, 0, numConsultas-1); 
            printf("\nConsultas quickSortFechas:\n");
            imprimirConsultas(consultas, numConsultas);
            busquedaBinMesAnio(consultas, 0, numConsultas-1, "10/2025", aux, &i);
            if (i != -1)
            {
              
              //Obtener consultas atendidas de los médicos
              //Obtener antigüedad de los médicos
              //Inserción
              printf("\nConsultas filtradas:\n");
              imprimirConsultas(aux, i+1);
            }
            else
            {
              printf("\nNo se encontraron consultas con ese mes y anio\n");
            }
            break;
        case 6:
          if (strcmp("03/09/2023","01/10/2023") >= 0)
            printf("ei");
          break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida\n");
            break;
        }
    } while (opc!=0);
    
    return 0;
}

int menu()
{
    int opc;
    printf("\n\tMEJORA TU SALUD\n\t\tMenu:\n\n");
    printf("1. Registrar Consulta\n");
    printf("2. Reporte de Informacion\n");
    printf("3. Aplicar Compensacion\n"); 
    printf("0. Salir\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opc);
    return opc;
}

//validar nombre y edad del paciente
int validarNombre(consulta *consultas, paciente  *pacientes, int i)
{
  for(int j=0; j<5; j++)
    {
      if (strcmp(consultas[i].p.nombre, pacientes[j].nombre) == 0)
      {
        return j;
      }
    }
  return -1;
}

int validarEdad(consulta *consultas, paciente *pacientes, int i)
{
  if(consultas[i].p.edad == pacientes[i].edad)
  {
    return 1;
  }
  return -1;
}

int validarNombreMed(consulta *consultas, medico  *medicos, int i)
{
  for(int k=0; k<5; k++)
    {
      if (strcmp(consultas[i].m.nombre, medicos[k].nombre) == 0)
      {
        return k;
      }
    }
  return -1;
}

int validarEspecialidad(consulta *consultas, medico  *medicos, int k)
{
  if(consultas[k].m.especialidad == medicos[k].especialidad)
  {
    return 1;
  }
  return -1;
}

// Ordenar por seleccion

void ordenarPorEdad(consulta* consultas, int numConsultas) 
{
  int i, j, minimo;
  consulta aux;
  for(i=0; i<(numConsultas-1); i++)
    {
      minimo = i;
      if(consultas[i].p.edad % 2 == 0)
      {
        for(j=(i+1); j<(numConsultas-1); j++)
          {
            if(consultas[j].p.edad < consultas[minimo].p.edad)
            {
              minimo = j;
            }
          }
        if(i != minimo)
        {
          aux = consultas[i];
          consultas[i] = consultas[minimo];
          consultas[minimo] = aux;
        }
      }
    }
}

void mostrarConsEdades(consulta *consultas, int numConsultas)
{
  int i;
  for(i=0; i<numConsultas; i++)
    {
      printf("\n\tCONSULTA %d:\n", i+1);
      printf("Nombre: %s\n", consultas[i].p.nombre);
      printf("Edad: %d\n", consultas[i].p.edad);
    }
}

// Funcion para la busqueda en rango de edades
void busquedaBinaria(consulta *consultas, int numConsultas, int busqueda)
{
  int prim = 0;
  int ult = numConsultas - 1;
  int central;

  central = (prim + ult) / 2;
  
  
}

void compensacion(medico *medicos, consulta *consultas)
{
  
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void imprimirConsultas (consulta *consultas, int numConsultas)
{
    int i;

    for (i = 0; i < numConsultas; i++)
    {
        printf("-----------------------------------------\n");
        printf("Fecha: %s\n", consultas[i].fecha);
        printf("Paciente: %s\n", consultas[i].p.nombre);
        printf("Doctor: %s\n", consultas[i].m.nombre);
        printf("Sintomas: %s\n", consultas[i].sintomas);
        char *urgencia_str;
        switch (consultas[i].urgeTipo)
        {
            case BAJA:
                urgencia_str = "Baja";
                break;
            case MEDIA:
                urgencia_str = "Media";
                break;
            case ALTA:
                urgencia_str = "Alta";
                break;
            default:
                urgencia_str = "Desconocida";
                break;
        }

        printf("Urgencia: %s\n", urgencia_str);
        printf("Diagnostico: %s\n", consultas[i].diagnos);
    }
        printf("-----------------------------------------\n");
        printf("-----------------------------------------\n");
}

void busquedaBinFechas (consulta *consultas, int primero, int ultimo, char *fecha_inicio, char *fecha_fin, consulta *aux, int *i)
{
  // D D / M M / A A A A
  // 1 2 3 4 5 6 7 8 9 0
    if (primero > ultimo)
        return;
        
    int mitad = primero + (ultimo - primero) / 2;

    if( strcmp(fecha_fin+6, consultas[mitad].fecha+6) < 0 ||
        strcmp(fecha_fin+6, consultas[mitad].fecha+6) == 0 && strcmp(fecha_fin+3, consultas[mitad].fecha+3) < 0 ||
        strcmp(fecha_fin+6, consultas[mitad].fecha+6) == 0 && strcmp(fecha_fin+3, consultas[mitad].fecha+3) == 0 && strcmp(fecha_fin, consultas[mitad].fecha) < 0)
    {
        busquedaBinFechas(consultas, primero, mitad-1, fecha_inicio, fecha_fin, aux, i);
    }
    else if(strcmp(fecha_inicio+6, consultas[mitad].fecha+6) > 0 ||
            strcmp(fecha_inicio+6, consultas[mitad].fecha+6) == 0 && strcmp(fecha_inicio+3, consultas[mitad].fecha+3) > 0 ||
            strcmp(fecha_inicio+6, consultas[mitad].fecha+6) == 0 && strcmp(fecha_inicio+3, consultas[mitad].fecha+3) == 0 && strcmp(fecha_inicio, consultas[mitad].fecha) > 0)
    {
        busquedaBinFechas(consultas, mitad+1, ultimo, fecha_inicio, fecha_fin, aux, i);
    }
    else
    {
        *i += 1;
        aux[(*i)] = consultas[mitad];
        busquedaBinFechas(consultas, primero, mitad-1, fecha_inicio, fecha_fin, aux, i);
        busquedaBinFechas(consultas, mitad+1, ultimo, fecha_inicio, fecha_fin, aux, i);
    }
}

void quickSortFechas (consulta *consultas, int primero, int ultimo)
{
    // D D / M M / A A A A
    // 1 2 3 4 5 6 7 8 9 0

    int mitad = primero + (ultimo - primero) / 2;
    int i = primero;
    int j = ultimo;
    consulta pivote = consultas[mitad];
    consulta aux;

    do
    {
        while ( strcmp(consultas[i].fecha+6, pivote.fecha+6) < 0 ||
                strcmp(consultas[i].fecha+6, pivote.fecha+6) == 0 && strcmp(consultas[i].fecha+3, pivote.fecha+3) < 0 || 
                strcmp(consultas[i].fecha+6, pivote.fecha+6) == 0 && strcmp(consultas[i].fecha+3, pivote.fecha+3) == 0 && strcmp(consultas[i].fecha, pivote.fecha) < 0)
        {
          i++;
        }
            
        while ( strcmp(consultas[j].fecha+6, pivote.fecha+6) > 0 ||
                strcmp(consultas[j].fecha+6, pivote.fecha+6) == 0 && strcmp(consultas[j].fecha+3, pivote.fecha+3) > 0 || 
                strcmp(consultas[j].fecha+6, pivote.fecha+6) == 0 && strcmp(consultas[j].fecha+3, pivote.fecha+3) == 0 && strcmp(consultas[j].fecha, pivote.fecha) > 0)
        {
          j--;
        }
            
        if (i <= j)
        {
            aux = consultas[i];
            consultas[i] = consultas[j];
            consultas[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    
    if (j > primero)
        quickSortFechas(consultas, primero, j);
    if (i < ultimo)
        quickSortFechas(consultas, i, ultimo);
}

void contarConsPorUrgencia (consulta *consultas, int numConsultas, int consPorUrgencia[3][2])
{
  int urgencia;

  // Inicializar la segunda columna del arreglo en ceros y que la primera columna sea el tipo de urgencia y así evitar hacer busquedas
  for (int i=0; i<3; i++)
  {
    consPorUrgencia[i][0] = i;
    consPorUrgencia[i][1] = 0;
  }

  // Contar consultas por urgencia
  for (int i=0; i<numConsultas; i++)
  {
    urgencia = consultas[i].urgeTipo;
    consPorUrgencia[urgencia][1]++;
  }
  
}

/* void burbujaUrgencia (consulta *consultas, int numConsultas)
{
    int swap, i;
    consulta aux;
    
    for (i = 0; i < numConsultas - 1; i++)
    {
        swap = 0;
        for (int j = 0; j < numConsultas - i - 1; j++)
        {
            if (consultas[j].urgeTipo < consultas[j+1].urgeTipo)
            {
                aux = consultas[j+1];
                consultas[j+1] = consultas[j];
                consultas[j] = aux;
                swap = 1;
            }
        }
        if (swap == 0)
            break;
    }
} */

void burbujaUrgencia (int consPorUrgencia[3][2])
{
    int auxCant, auxUrgencia, swap, i;
    
    for (i = 0; i < 3 - 1; i++)
    {
        swap = 0;
        for (int j = 0; j < 3 - i - 1; j++)
        {
            if (consPorUrgencia[j][1] < consPorUrgencia[j+1][1])
            {
                auxCant = consPorUrgencia[j+1][1];
                auxUrgencia = consPorUrgencia[j+1][0];
                consPorUrgencia[j+1][1] = consPorUrgencia[j][1];
                consPorUrgencia[j+1][0] = consPorUrgencia[j][0];
                consPorUrgencia[j][1] = auxCant;
                consPorUrgencia[j][0] = auxUrgencia;
                swap = 1;
            }
        }
        if (swap == 0)
            break;
    }
    
    //printf("\nCantidad de pasadas: %d\n", i+1);
}

void quickSortMunicipios (consMunicipio *municipios, int primero, int ultimo)
{
    
    int mitad = primero + (ultimo - primero) / 2;
    int i = primero;
    int j = ultimo;
    consMunicipio pivote = municipios[mitad];
    consMunicipio aux;
    
    do
    {
        while (strcmp(municipios[i].municipio, pivote.municipio) < 0)
            i++;
            
        while (strcmp(municipios[j].municipio, pivote.municipio) > 0)
            j--;
            
        if (i <= j)
        {
            aux = municipios[i];
            municipios[i] = municipios[j];
            municipios[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    
    if (j > primero)
        quickSortMunicipios(municipios, primero, j);
    if (i < ultimo)
        quickSortMunicipios(municipios, i, ultimo);
}

void mostrarConsMunicipio (consulta *consultas, int numConsultas)
{
  
}

void busquedaBinMesAnio (consulta *consultas, int primero, int ultimo, char *mes_anio, consulta *aux, int *i)
{
  // 03/2023
  

    if (primero > ultimo)
        return;
        
    int mitad = primero + (ultimo - primero) / 2;

    if(strcmp(mes_anio, consultas[mitad].fecha + 3) < 0)
    {
        busquedaBinMesAnio(consultas, primero, mitad-1, mes_anio, aux, i);
    }
    else if(strcmp(mes_anio, consultas[mitad].fecha + 3) > 0)
    {
        busquedaBinMesAnio(consultas, mitad+1, ultimo, mes_anio, aux, i);
    }
    else if(strcmp(mes_anio, consultas[mitad].fecha + 3) == 0)
    {
        *i += 1;
        aux[(*i)] = consultas[mitad];
        busquedaBinMesAnio(consultas, primero, mitad-1, mes_anio, aux, i);
        busquedaBinMesAnio(consultas, mitad+1, ultimo, mes_anio, aux, i);
    }
}

void imprimirConsPorUrgencia (int consPorUrgencia[3][2])
{
    printf("\n--------------------------------------\n");
    printf("|| Reporte de consultas por urgencia ||\n");
    printf("--------------------------------------\n");
    for (int j=0; j<3; j++)
    {
    char *urgencia_str;
    switch (consPorUrgencia[j][0])
    {
        case BAJA:
            urgencia_str = "Baja";
            break;
        case MEDIA:
            urgencia_str = "Media";
            break;
        case ALTA:
            urgencia_str = "Alta";
            break;
        default:
            urgencia_str = "Desconocida";
            break;
    }
    printf("Urgencia: %s\n", urgencia_str);
    printf("Cantidad: %d\n", consPorUrgencia[j][1]);
    }
}

/* void contarConsPorMunicipio (consulta *consultas, int numConsultas, consMunicipio *municipios)
{
    for (int i=0; i<numConsultas; i++)
    {
        municipios[i].municipio = consultas[i].p.dirPaciente.municipio;
    }
} */

void obtenerMedDatos (consulta *consultas, int numConsultas, reporteMed *medicos)
{
  //for()
}

void insersionMedicos (reporteMed *medicos, int numMedicos)
{
  
}

void contarConsPorMunicipio (char *municipioCons, consMunicipio *municipios, int *numMunicipios)
{
    // Si no hay municipios registrados, agregar el primero
    if (*numMunicipios == 0)
    {
        strcpy(municipios[0].municipio, municipioCons);
        municipios[0].consultas = 1;
        *numMunicipios = 1;
        return;
    }

    // Busqueda binaria. Si se encuentra el municipio, se incrementa el contador
    int primero = 0;
    int ultimo = *numMunicipios - 1;
    int mitad = primero + (ultimo - primero) / 2;
    int encontrado = 0;

    while (primero <= ultimo)
    {
        if (strcmp(municipios[mitad].municipio, municipioCons) < 0)
        {
            primero = mitad + 1;
        }
        else if (strcmp(municipios[mitad].municipio, municipioCons) == 0)
        {
            municipios[mitad].consultas++;
            encontrado = 1;
            break;
        }
        else
        {
            ultimo = mitad - 1;
        }
        mitad = primero + (ultimo - primero) / 2;
    }

    // Si no se encontró el municipio, agregarlo al final y ordenar alfabetícamente
    if (encontrado == 0)
    {
        strcpy(municipios[*numMunicipios].municipio, municipioCons);
        municipios[*numMunicipios].consultas = 1;
        *numMunicipios += 1;
        quickSortMunicipios(municipios, 0, *numMunicipios-1);
    }
}