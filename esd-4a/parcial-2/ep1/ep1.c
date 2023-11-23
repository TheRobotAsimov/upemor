#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Constantes para la urgencia de la cita
#define ALTA 2
#define MEDIA 1
#define BAJA 0
#define LIMITE 50

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
    int numC;
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
    float sueldo;
    float pagoExtra;
    int antiguo;
    int consulMade;
}medico;

typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha;

  typedef struct
  {
      int rango;
      int totalCons;
  } rangoEdad;

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

//menu y submenu
int menu();
int submenu();

void registroPac(paciente *pacientes);
void registroMed(medico *medicos);
//consulta* registroCons(int numConsultas, paciente *pacientes, medico *medicos);
void consulRegistro(int *numConsultas, consulta *consultas, paciente *pacientes, medico *medicos);
//validar datos
void validarFecha(char fecha[]);
int validarNombre(consulta *consultas, paciente  *pacientes, int i);
int validarEdad(consulta *consultas, paciente *pacientes, int i, int x);
int validarNombreMed(consulta *consultas, medico  *medicos, int i);
int validarEspecialidad(consulta *consultas, medico  *medicos, int i, int v);
void validarSintomas(char sintomas[]);
void validarDiagnos(char diagnostico[]);
void validarUrgencia(int* urgencia);
//Reporte de pacientes atendidos por rango de edad 
void ordenarPorEdad(consulta* consultas, rangoEdad *rangoEdades);

void mostrarConsEdades(consulta *consultas, int numConsultas, rangoEdad *rangoEdades);
void consultasXedades(consulta *consultas, rangoEdad *rangoEdades, int numConsultas);
void imprimirPacEdades(consulta *consultas, rangoEdad *rangoEdades, int numConsultas);
//Funcion para la compensacion de sueldo
void compensacion(medico *medicos, consulta *consultas);

void imprimirConsultas (consulta *consultas, int numConsultas);
void busquedaBinFechas (consulta *consultas, int primero, int ultimo, char *fecha_inicio, char *fecha_fin, consulta *aux, int *i);
void quickSortFechas (consulta *consultas, int primero, int ultimo);
void burbujaUrgencia (int consPorUrgencia[3][2]);
void busquedaBinMesAnio (consulta *consultas, int primero, int ultimo, char *mes_anio, consulta *aux, int *i, medico *medicos);

void contarConsPorUrgencia (consulta *consultas, int numConsultas, int consPorUrgencia[3][2]);
void imprimirConsPorUrgencia (int consPorUrgencia[3][2]);
//Funcion para reporte de consultas por medico
void insersionMedicos (medico *medicos, int numMedicos);

void contarConsPorMunicipio (char *municipioCons, consMunicipio *municipios, int *numMunicipios);
void quickSortMunicipios (consMunicipio *municipios, int primero, int ultimo);

void pedirFechas(char *fecha_inicio, char *fecha_fin);
void pedirMes(char *mes_anio);

int main(){
    int opc, opc2, numConsultas=0, busqueda, consPorUrgencia[3][2];
  
// Declaración e inicialización de un arreglo de 5 direcciones
  struct direccion direcciones[5] = {
    {"Calle1", "Colonia1", "Municipio1", 123, 45678},
    {"Calle2", "Colonia2", "Municipio2", 456, 78901},
    {"Calle3", "Colonia3", "Municipio3", 789, 12345},
    {"Calle4", "Colonia4", "Municipio4", 234, 56789},
    {"Calle5", "Colonia5", "Municipio5", 567, 90123}};

// Declaración e inicialización de un arreglo de 5 pacientes
  paciente pacientes[5] = {
    {"Paciente1", 25, direcciones[0], 1.75, 0},
    {"Paciente2", 30, direcciones[1], 1.80, 0},
    {"Paciente3", 40, direcciones[2], 1.70, 0},
    {"Paciente4", 35, direcciones[3], 1.60, 0},
    {"Paciente5", 28, direcciones[4], 1.85, 0}};

// Declaración e inicialización de un arreglo de 5 médicos
  medico medicos[5] = {
    {"Medico1", 1, direcciones[0], 6000, 0, 10, 0},
    {"Medico2", 3, direcciones[1], 7000, 0, 5, 0},
    {"Medico3", 2, direcciones[2], 7500, 0, 15, 0},
    {"Medico4", 4, direcciones[3], 8000, 0, 20, 0},
    {"Medico5", 5, direcciones[4], 9000, 0, 25, 0}};

  // 20
  
  consulta consultas[LIMITE];/* = {{"05/10/2023", pacientes[0], medicos[0], "Sintomas1", BAJA, "Diagnostico1"},
                            {"03/09/2023", pacientes[1], medicos[1], "Sintomas2", MEDIA, "Diagnostico2"},
                            {"01/10/2023", pacientes[2], medicos[2], "Sintomas3", ALTA, "Diagnostico3"},
                            {"02/09/2023", pacientes[3], medicos[3], "Sintomas4", ALTA, "Diagnostico4"},
                            {"04/10/2023", pacientes[4], medicos[4], "Sintomas5", MEDIA, "Diagnostico5"}};*/
  consulta aux[LIMITE];
  int i = -1;
  int numMedicos=5;
  //int rangoEdades[6];
  rangoEdad rangoEdades[6] = {{0,0},
                              {1,0},
                              {2,0},
                              {3,0},
                              {4,0},
                              {5,0}};
  /*
  0 = 0 - 15
  1 = 16 - 31
  2 = 32 - 47
  3 = 48 - 63
  4 = 64 - 79
  5 = 80 - 95
  */

  char fecha_inicio[11], fecha_fin[11], mes[8];

  consMunicipio municipios[40];
  int numMunicipios = 0;
  
    do
    {
        opc=menu();
        switch (opc)
        {
        case 1:
            consulRegistro(&numConsultas, consultas, pacientes, medicos);
            //imprimirConsultas(consultas, numConsultas);
            break;
        case 2:
          
          do{
            opc2 = submenu();
            switch(opc2)
              {
                // Registro por urgencia
                case 1:
                  i = -1;
                  quickSortFechas(consultas, 0, numConsultas-1);
                  pedirFechas(fecha_inicio, fecha_fin);
                  busquedaBinFechas(consultas, 0, numConsultas-1, fecha_inicio, fecha_fin, aux, &i);
                  if (i != -1)
                  {
                    contarConsPorUrgencia(aux, i+1, consPorUrgencia);
                    burbujaUrgencia(consPorUrgencia);
                    imprimirConsPorUrgencia(consPorUrgencia);
                  }
                  else
                  {
                    printf("\nNo se encontraron consultas con ese rango de fechas\n");
                  }
                  break;
                case 2:
                  i = -1;
                  //Por edad
                  quickSortFechas(consultas, 0, numConsultas-1);
                  pedirFechas(fecha_inicio, fecha_fin);
                  busquedaBinFechas(consultas, 0, numConsultas-1, fecha_inicio, fecha_fin, aux, &i);
                  
                  consultasXedades(aux, rangoEdades, i+1);
                  ordenarPorEdad(aux, rangoEdades);
                  //mostrarConsEdades(aux, numConsultas, rangoEdades);
                  if(i != -1)
                  {
                    imprimirPacEdades(aux, rangoEdades, i+1);
                  }
                  break;
                case 3:
                  for(int a=0;a<numMedicos;a++){
                    medicos[a].consulMade=0;
                  }
                  i = -1;
                  char string[25];
                  
                  quickSortFechas(consultas, 0, numConsultas-1); 
                  pedirMes(mes);
                  busquedaBinMesAnio(consultas, 0, numConsultas-1, mes, aux, &i,medicos);
                  if (i != -1){
                      insersionMedicos (medicos,numMedicos);
                              }
                  else
                  {
                  printf("\nNo se encontraron consultas con ese mes y anio\n");
                  }

                    break;
                  break;
                // Registro por municipios
                case 4:
                  i = -1;
                  quickSortFechas(consultas, 0, numConsultas-1);
                  pedirFechas(fecha_inicio, fecha_fin);
                  busquedaBinFechas(consultas, 0, numConsultas-1, fecha_inicio, fecha_fin, aux, &i);
                  if (i != -1)
                  {
                    numMunicipios = 0;
                    printf("\n");
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
                case 0:
                  printf("Saliendo del submenu...\n");
                  break;
                default:
                  printf("Opcion invalida\n");
                  break;
              }
          }while(opc2 != 0);
            /*ordenarPorEdad(consultas, numConsultas);
            mostrarConsEdades(consultas, numConsultas);*/
            break;
        // reporte de urgencias
        case 3:
          for(int a=0;a<numMedicos;a++){
            medicos[a].consulMade=0;
          }
          i = -1;
          quickSortFechas(consultas, 0, numConsultas-1); 
          pedirMes(mes);
          busquedaBinMesAnio(consultas, 0, numConsultas-1, mes, aux, &i,medicos);
          if (i != -1){
              insersionMedicos (medicos,numMedicos);
              int z;
            for(z=0;z<3;z++){
              if(medicos[z].consulMade!=0){
              medicos[z].pagoExtra=(medicos[z].sueldo*0.15)+medicos[z].sueldo;

              printf("\nMedico:n%s            sueldo:%.2f     Sueldo con aumento: %.2f\n",medicos[z].nombre,medicos[z].sueldo,medicos[z].pagoExtra);
                  }
              }
          }
          else
          {
          printf("\nNo se encontraron consultas con ese mes y anio\n");
          }

            break;
        // reporte por rango de pacientes por Municipio

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
    scanf("%d%*c", &opc);
    return opc;
}

int submenu()
{
  int opc2;
  printf("\n\tMEJORA TU SALUD\n\t\tSubmenu:\n\n");
  printf("1. Reporte de urgencias\n");
  printf("2. Reporte de pacientes atendidos por rango de edad\n");
  printf("3. Reporte de atenciones por medico\n"); 
  printf("4. Reporte de pacientes por municipio\n");
  printf("0. Salir\n");
  printf("Ingrese opcion: ");
  scanf("%d%*c", &opc2);
  return opc2;
}

void consulRegistro(int *numConsultas,consulta *consultas, paciente *pacientes, medico *medicos) {
    int j, k, x, y, v, w, seguir, i=0;

    if(*numConsultas >= LIMITE)
    {
      printf("\nSupero el limite de consultas\n");
      return;
    }
    
    // Registro de las consultas
    do {
        x=-1;
        y=-1;
        v=-1;
        w=-1;
      
        printf("\nCONSULTA %d:\n", i+1);
        
        char fecha1[11];
        validarFecha(fecha1);
        strcpy(consultas[i].fecha, fecha1);
      
        do{
          printf("Ingresa el nombre del paciente: ");
          scanf(" %[^\n]%*c", consultas[i].p.nombre);
        
          x = validarNombre(consultas, pacientes, i);
          if(x == -1)
          {
            printf("\nEl nombre del paciente no coincide con ningun paciente registrado...\n");
            printf("\n");
          }
        }while(x < 0);
        //printf("%d\n", x);
        do{
          printf("Edad: ");
          scanf("%d%*c", &consultas[i].p.edad);
          y = validarEdad(consultas, pacientes, i, x);
          if(y == -1)
          {
            printf("\nLa edad ingresada no es valida...\n");
            printf("\n");
          }
        }while(y < 0);
        do{
          printf("Ingrese el nombre del medico: ");
          scanf("%[^\n]%*c", consultas[i].m.nombre);

          v = validarNombreMed(consultas, medicos, i);
          if(v == -1)
          {
            printf("\nEl nombre del medico no coincide con ningun medico registrado...\n");
            printf("\n");
          }
        }while(v < 0);
        do{
          printf("Especialidad: ");
          printf("\n\t1. Medicina General\n\t2. Traumatologia\n\t3. Pediatria\n\t4. Cardiologia\n\t5. Psiquiatria\n>>");
          scanf("%d%*c", &consultas[i].m.especialidad);

          w = validarEspecialidad(consultas, medicos, i, v);
          if(w == -1)
          {
            printf("\nLa especialidad del medico no coincide con la especialidad del medico...\n");
            printf("\n");
          }
        }while(w < 0);

        char sintomas[100];
        validarSintomas(sintomas);
        strcpy(consultas[i].sintomas, sintomas);

        int urgencia;
        validarUrgencia(&urgencia);
        urgencia -= 1;
        consultas[i].urgeTipo = urgencia;
        
        char diagnostico[100];
        validarDiagnos(diagnostico);
        strcpy(consultas[i].diagnos, diagnostico);

        *numConsultas += 1;
        i++;

        printf("Desea agregar otra consulta? (0 = no, 1 = si\n");
        scanf("%d", &seguir);
      
    } while (seguir != 0 && *numConsultas <= 50);
    
}

void validarFecha(char fecha[])
{
  int block;

  do{
      block = 0;

      printf("Ingrese la fecha dd/mm/aa: ");
      scanf(" %[^\n]%*c", fecha);

      int dia, mes, anio;

      if (strlen(fecha) != 10)
      {
          block = 1;
          printf("La fecha debe tener 10 caracteres\n");
      } else

      if (fecha[2] != '/' || fecha[5] != '/')
      {
          block = 1;
          printf("La fecha debe tener el formato dd/mm/aaaa\n");
      } else

      if (!isdigit(fecha[0]) || !isdigit(fecha[1]) || !isdigit(fecha[3]) || !isdigit(fecha[4]) || !isdigit(fecha[6]) || !isdigit(fecha[7]) || !isdigit(fecha[8]) || !isdigit(fecha[9]))
      {
          block = 1;
          printf("La fecha no puede contener letras\n");
      } else {
          sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio);
          if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 2023 || anio > 2050)
          {
              block = 1;
              printf("La fecha no es valida\n");
          }
      }

  }while (block != 0);
}

void validarSintomas(char sintomas[])
  {
      int block;

      do{
          block = 0;

          printf("Sintomas: ");
          scanf("%[^\n]%*c", sintomas);

          for (int i = 0; i < strlen(sintomas); i++)
          {
              if (isalnum(sintomas[i]) == 0 && sintomas[i] != ' ')
              {
                  block = 1;
                  printf("Los sintomas no pueden contener caracteres especiales\n");
                  break;
              }
          }

      }while (block != 0);
  }

void validarDiagnos(char diagnostico[])
    {
        int block;

        do{
            block = 0;

            printf("Diagnostico: ");
            scanf("%[^\n]%*c", diagnostico);

            for (int i = 0; i < strlen(diagnostico); i++)
            {
                if (isalnum(diagnostico[i]) == 0 && diagnostico[i] != ' ')
                {
                    block = 1;
                    printf("El diagnostico no puede contener caracteres especiales\n");
                    break;
                }
            }

        }while (block != 0);
    }


//validar nombre y edad del paciente
int validarNombre(consulta *consultas, paciente  *pacientes, int i)
{
  for(int j=0; j<5; j++)
    {
      if (strcmp(consultas[i].p.nombre, pacientes[j].nombre) == 0)
      {
        consultas[i].p.edad = pacientes[j].edad;
        consultas[i].p.dirPaciente = pacientes[j].dirPaciente;
        consultas[i].p.estatura = pacientes[j].estatura;
        
        pacientes[j].numC++;
        consultas[i].p.numC = pacientes[j].numC;
        return j;
      }
    }
  return -1;
}

int validarEdad(consulta *consultas, paciente *pacientes, int i, int x)
{
  if(consultas[i].p.edad == pacientes[x].edad)
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
        consultas[i].m.especialidad = medicos[k].especialidad;
        consultas[i].m.dirMedico = medicos[k].dirMedico;
        consultas[i].m.sueldo = medicos[k].sueldo;
        consultas[i].m.pagoExtra = medicos[k].pagoExtra;
        consultas[i].m.antiguo = medicos[k].antiguo;
        consultas[i].m.consulMade = medicos[k].consulMade;

        return k;
      }
    }
  return -1;
}

int validarEspecialidad(consulta *consultas, medico  *medicos, int i, int v)
{
  if(consultas[i].m.especialidad == medicos[v].especialidad)
  {
    return 1;
  }
  return -1;
}

void validarUrgencia(int* urgencia)
  {
      int block;

      do{
          block = 0;
          printf("Indique el tipo de urgencia:\n\t1. Baja\n\t2. Media\n\t3. Alta\n>>");
          scanf("%d%*c", urgencia);

          if (*urgencia < 1 || *urgencia > 3)
          {
              block = 1;
              printf("El tipo de urgencia debe ser:\n\t1. Baja\n\t2. Media\n\t3. Alta\n>>");
          }

      }while (block != 0);
    
  }

// Ordenar por seleccion el rango de edades

void ordenarPorEdad(consulta* consultas, rangoEdad *rangoEdades) 
{
  
  int i,j,minimo;
  rangoEdad aux;
  int n=6;

  for(i=0;i<=(n-1);i++){
      minimo=i;
      for(j=(i+1);j<=(n-1);j++){
          if(rangoEdades[j].totalCons<rangoEdades[minimo].totalCons){
              minimo=j;
          }
      }
      if(i!=minimo){
          aux=rangoEdades[i];
          rangoEdades[i]=rangoEdades[minimo];
          rangoEdades[minimo]=aux;
      }
  }
}

void mostrarConsEdades(consulta *consultas, int numConsultas, rangoEdad *rangoEdades)
{
  int i,j;

  for(i=0; i<6; i++)
    {
      printf("%d ", rangoEdades[i].totalCons);  
      /*
      printf("Nombre: %s\n", consultas[i].p.nombre);
      printf("Edad: %d\n", consultas[i].p.edad);
      printf("Consultas: %c\n", consultas[i].p.numC);*/
    }
}

void consultasXedades(consulta *consultas, rangoEdad *rangoEdades, int numConsultas)
{

  /* {{0,0},
      {1,0},
      {2,0},
      {3,0},
      {4,0},
      {5,0}}; */
  
  int i, j, k;

  for(i=0; i<6; i++)
  {
     rangoEdades[i].rango = i; 
     rangoEdades[i].totalCons = 0; 
  }
  
  for(i=0; i<numConsultas; i++)
    {
      if(consultas[i].p.edad >= 0 && consultas[i].p.edad < 16)
        rangoEdades[0].totalCons++;
      if(consultas[i].p.edad >= 16 && consultas[i].p.edad < 32)
        rangoEdades[1].totalCons++;
      if(consultas[i].p.edad >= 32 && consultas[i].p.edad < 48)
        rangoEdades[2].totalCons++;
      if(consultas[i].p.edad >= 48 && consultas[i].p.edad < 64)
        rangoEdades[3].totalCons++;
      if(consultas[i].p.edad >= 64 && consultas[i].p.edad < 80)
        rangoEdades[4].totalCons++;
      if(consultas[i].p.edad >= 80 && consultas[i].p.edad < 96)
        rangoEdades[5].totalCons++;
    }
  /*for(k=0;k<5;k++)
    {
      printf("%d ", rangoEdades[k].totalCons);
    }*/
}

void imprimirPacEdades(consulta *consultas, rangoEdad *rangoEdades, int numConsultas)
{
  int i;
  printf("\n\n  Rango edad\tCantidad de pacientes\n ");
  for(i=0; i<6 ;i++)
    { 
      /*
      0 = 0 - 15
      1 = 16 - 31
      2 = 32 - 47
      3 = 48 - 63
      4 = 64 - 79
      5 = 80 - 95
      */
      if(rangoEdades[i].rango == 0)
        printf("   0 - 15\t\t\t\t  %d\n", rangoEdades[i].totalCons);
      if(rangoEdades[i].rango == 1)
        printf("   16 - 31\t\t\t\t  %d\n", rangoEdades[i].totalCons);
      if(rangoEdades[i].rango == 2)
        printf("   32 - 47\t\t\t\t  %d\n", rangoEdades[i].totalCons);
      if(rangoEdades[i].rango == 3)
        printf("   48 - 63\t\t\t\t  %d\n", rangoEdades[i].totalCons);
      if(rangoEdades[i].rango == 4)
        printf("   64 - 79\t\t\t\t  %d\n", rangoEdades[i].totalCons);
      if(rangoEdades[i].rango == 5)
        printf("   80 - 95\t\t\t\t  %d\n", rangoEdades[i].totalCons);
      //printf("Rango de edades: %d - %d\n", rangoEdades[i].rango, rangoEdades[i].totalCons);
    }
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

  // Inicializar la segunda columna del arreglo en ceros y que la primera columna sea el tipo de urgencia
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
}

void busquedaBinMesAnio (consulta *consultas, int primero, int ultimo, char *mes_anio, consulta *aux, int *i, medico *medicos)
{
    if (primero > ultimo)
        return;
        
    int mitad = primero + (ultimo - primero) / 2;

    if(strcmp(mes_anio, consultas[mitad].fecha + 3) < 0)
    {
       busquedaBinMesAnio(consultas, primero, mitad-1, mes_anio, aux, i,medicos);
    }
    else if(strcmp(mes_anio, consultas[mitad].fecha + 3) > 0)
    {
       busquedaBinMesAnio(consultas, mitad+1, ultimo, mes_anio, aux, i,medicos);
    }
    else if(strcmp(mes_anio, consultas[mitad].fecha + 3) == 0)
    {
        *i += 1;
        aux[(*i)] = consultas[mitad];
       int c;  
         for(c=0;c<5;c++){
             if(strcmp(consultas[mitad].m.nombre,medicos[c].nombre)==0){
                  medicos[c].consulMade++;
              }
          }
      busquedaBinMesAnio(consultas, primero, mitad-1, mes_anio, aux, i,medicos);
      busquedaBinMesAnio(consultas, mitad+1, ultimo, mes_anio, aux, i,medicos);
    }
}



void insersionMedicos (medico *medicos, int numMedicos)
{
    medico aux;
    int j=0,k=0;

  for(int i=0;i<numMedicos;i++){
      j=i;
      aux= medicos[i];
      while(j>0 && aux.consulMade>=medicos[j-1].consulMade){
          if(aux.consulMade==medicos[j-1].consulMade){
              if(aux.antiguo<medicos[j-1].antiguo){
                  break;
              }
          }
          medicos[j]=medicos[j-1];

          j--;

      }

      medicos[j]=aux;
  }
   printf("\nMedico              Antigüedad         Numero de consultas\n");
  for(k=0;k<numMedicos;k++){
     printf("\n%s               %5d                  %d\n",medicos[k].nombre,medicos[k].antiguo,medicos[k].consulMade);
  
  }
  return;
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

void pedirFechas(char *fecha_inicio, char *fecha_fin)
{
  printf("\nRANGO DE FECHAS\n");
  printf("\n-Fecha de Inicio-\n");
  validarFecha(fecha_inicio);
  do
  {
    printf("\n-Fecha Fin-\n");
    validarFecha(fecha_fin);
  } while ( strcmp(fecha_fin+6, fecha_inicio+6) < 0 ||
            strcmp(fecha_fin+6, fecha_inicio+6) == 0 && strcmp(fecha_fin+3, fecha_inicio+3) < 0 || 
            strcmp(fecha_fin+6, fecha_inicio+6) == 0 && strcmp(fecha_fin+3, fecha_inicio+3) == 0 && strcmp(fecha_fin, fecha_inicio) < 0);
}

void pedirMes(char *mes_anio)
{
  printf("\nIngrese mes y anio (mm/aaaa): \n");
  scanf(" %[^\n]", mes_anio);
}