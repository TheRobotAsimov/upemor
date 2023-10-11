


#include <stdio.h>

typedef struct {
    char name[50];
    int age;
    char direction[50];
    char phone[15];

} patient;

typedef struct
{
    char name[50];
    char specialty[50];
    float base_salary;
    float compensation;
    int antiquity;

} doctor;

typedef struct
{
    char date[10];
    patient patient_data;
    doctor doctor_data;
    char symptoms[100];
    char urgency[10];
    char diagnosis[100];

} appointment;

void binarySearch (appointment *appointments, char *date_start, char *date_end, int *count);
void bubbleSort (appointment *appointments, int *count);

void addAppointment (appointment *appointments, patient *patients, doctor *doctors, int *count);
void informationReport (appointment *appointments, patient *patients, doctor *doctors,int *count);
    void urgencyReport (appointment *appointments, int *count);
    void ageRangeReport (appointment *appointments, patient, *patients, *count);
    void doctorReport (appointment *appointments, doctor *doctors, int *count);
    void townReport (appointment *appointments, patient *patients,int *count);
void applyCompensation (appointment *appointments, doctor *doctors, int *count);

int main (void)
{
    patient patients[5] = {
        {"Juan Perez", 25, "Calle 1", "123456789"},
        {"Maria Lopez", 30, "Calle 2", "987654321"},
        {"Pedro Ramirez", 35, "Calle 3", "456789123"},
        {"Jose Rodriguez", 40, "Calle 4", "321654987"},
        {"Ana Martinez", 45, "Calle 5", "159753456"}
    };

    doctor doctors[5] = {
        {"Dr. Juan", "Pediatra", 1000, 0, 5},
        {"Dr. Maria", "Cirujano", 2000, 0, 10},
        {"Dr. Pedro", "Dermatologo", 3000, 0, 15},
        {"Dr. Jose", "Oftalmologo", 4000, 0, 20},
        {"Dr. Ana", "Ginecologo", 5000, 0, 25}
    };

    appointment appointment[50];

    // MENU

    int option = 0;
    int count = 0;

    do
    {
        printf("1. Agregar cita\n");
        printf("2. Reporte de informacion\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                addAppointment(appointment, patients, doctors, &count);
                break;
            case 2:
                informationReport(appointment, patients, doctors, &count);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while (option != 0);

    return 0;
}

void binarySearch (appointment *appointments, char *date_start, char *date_end, int *count)
{
    int first = 0;
    int last = count - 1;
    int middle = last / 2;
    
    while(first <= last && appointments[middle].urgency != searching)
    {
        if (searching < appointments[middle].urgency)
            last = middle - 1;
        if (searching > appointments[middle].urgency)
            first = middle + 1;
        middle = first + (last - first) / 2;
    }
    
    if (searching == appointments[middle])
        printf("Valor encontrado\n");
    else
        printf("Valor no encontrado\n");
}

void bubbleSort (appointment *appointments, int *count)
{
    int i, j;
    appointment temp;

    for (i = 0; i < *count - 1; i++)
    {
        for (j = 0; j < *count - i - 1; j++)
        {
            if (appointments[j].urgency > appointments[j + 1].urgency)
            {
                temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
}

void selectionSort (appointment *appointments, int *count)
{
    int i, j, min;
    appointment temp;

    for (i = 0; i < *count - 1; i++)
    {
        min = i;

        for (j = i + 1; j < *count; j++)
        {
            if (appointments[j].urgency < appointments[min].urgency)
                min = j;
        }

        temp = appointments[i];
        appointments[i] = appointments[min];
        appointments[min] = temp;
    }
}

void insertionSort (appointment *appointments, int *count)
{
    int i, j;
    appointment temp;

    for (i = 1; i < *count; i++)
    {
        temp = appointments[i];
        j = i - 1;

        while (j >= 0 && appointments[j].urgency > temp.urgency)
        {
            appointments[j + 1] = appointments[j];
            j--;
        }

        appointments[j + 1] = temp;
    }
}

void quickSort (appointment *appointments, int *count)
{
    int i, j;
    appointment temp;

    for (i = 0; i < *count - 1; i++)
    {
        for (j = i + 1; j < *count; j++)
        {
            if (appointments[i].urgency > appointments[j].urgency)
            {
                temp = appointments[i];
                appointments[i] = appointments[j];
                appointments[j] = temp;
            }
        }
    }
}

void addAppointment (appointment *appointments, patient *patients, doctor *doctors, int *count)
{

}

void informationReport (appointment *appointments, patient *patients, doctor *doctors,int *count)
{
    //Submenu

    int option = 0;

    do
    {
        printf("1. Reporte de urgencia\n");
        printf("2. Reporte por rango de edad\n");
        printf("3. Reporte por doctor\n");
        printf("4. Reporte por localidad\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                urgencyReport(appointments, count);
                break;
            case 2:
                ageRangeReport(appointments, patients, count);
                break;
            case 3:
                doctorReport(appointments, doctors, count);
                break;
            case 4:
                townReport(appointments, patients, count);
                break;
            case 0:
                printf("Regresando...\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while (option != 0);
}

void askDates (char *date_start, char *date_end)
{
    printf("Fecha Inicio: ");
    scanf("%s", date_start);
    printf("Fecha Fin: ");
    scanf("%s", date_end);
}

void urgencyReport (appointment *appointments, int *count)
{
    /* 
    Reporte de urgencias: Se le presentarán de manera ordenada la cantidad de consultas atendidas según
    el tipo de urgencia, considerando un rango de fechas en particular. Ordenarlas de mayor a menor.
    Aplicar la búsqueda binaria para el rango de fechas y el método de Burbuja mejorado para ordenar
    los datos.
    Ejemplo:
    Fecha Inicio: 01-08-2023
    Fecha Fin: 01-10-2023
    Tipo Urgencia   Cantidad de consultas
        Baja                15
        Alta                10
        Media                8
     */

    char date_start[10];
    char date_end[10];

    printf("Reporte de urgencias\n");
    askDates(date_start, date_end);

    bubbleSort(appointments, count);
    binarySearch(appointments, date_start, date_end, count);
}

void ageRangeReport (appointment *appointments, patient, *patients, *count)
{
    /* 
    Se mostrará un desglose de los pacientes
    atendidos por rangos de edad y la cantidad de pacientes que caen dentro de ese rango, ordenados de
    menor a mayor. Considerar que solo se tomarán en cuenta los registros de consultas que caen dentro
    de un rango de fechas. Aplicar método de Selección y búsqueda binaria
    Ejemplo:
    Fecha Inicio: 01-08-2023
    Fecha Fin: 01-10-2023

    Rango edad      Cantidad de pacientes
    80-95                      0
    64-79                      2
    32-47                      7
    0-15                      10
    48-63                     14
    16-31                     20
     */

    char date_start[10];
    char date_end[10];

    printf("Reporte de pacientes atendidos por rango de edad\n");
    askDates(date_start, date_end);

    selectionSort(appointments, count);
    binarySearch(appointments, date_start, date_end, count);
}

void doctorReport (appointment *appointments, doctor *doctors, int *count)
{
    /* 
    Reporte de atenciones por médico: Se mostrará un desglose de las consultas realizadas por cada
    médico en un mes y año en particular, considerar que se deberán mostrar ordenados de mayor a menor
    por cantidad de consultas. Además, se deberá considerar el ordenar a los médicos por antigüedad
    cuando ambos tengan la misma cantidad de consultas. Aplicar método de inserción y búsqueda binaria.
    Ejemplo:

    Mes: 03
    Año: 2023

    Médico              Antigüedad      Cantidad de consultas atendidas
    Juan Pérez              2                       10
    Pedro López             4                       8
    Ruben Castrejón         5                       5
    Ana Torres              3                       5
    Lilian Sánchez          2                       3
    Rodrigo Díaz            1                       3
     */

    char month[3];
    char year[5];

    printf("Reporte de atenciones por medico\n");
    printf("Mes: ");
    scanf("%s", month);
    printf("Año: ");
    scanf("%s", year);

    insertionSort(appointments, count);
    binarySearch(appointments, month, year, count);
}

void townReport (appointment *appointments, patient *patients,int *count)
{
    /* 
    Reporte de Pacientes por Municipio. Se mostrará un desglose de las consultas realizadas por todos
    los pacientes organizados de manera ordenada por municipio al que pertenecen. El usuario
    seleccionará el rango de fechas y se presentarán ordenados alfabéticamente por nombre del municipio.
    Aplicar método QuickSort y búsqueda binaria.

    Ejemplo
    Fecha Inicio: 01-08-2023
    Fecha Fin: 01-10-2023

    Municipio       Cant. Consultas Médicas

    Cuernavaca              3
    Jiutepec                15
    Tlayacapan              4
    Zacatepec               8
     */

    char date_start[10];
    char date_end[10];

    printf("Reporte de pacientes por municipio\n");
    askDates(date_start, date_end);

    quickSort(appointments, count);
    binarySearch(appointments, date_start, date_end, count);
}

void applyCompensation (appointment *appointments, doctor *doctors, int *count)
{
    /* 
    3.- Aplicar Compensación . Se le asignará un pago extra correspondiente al 15% del sueldo base a los 3 primeros
    médicos que en un mes en particular hayan realizado más consultas. Lo primero que se mostrará será el reporte de
    atenciones por médico (el cual se mostró en el punto anterior), se tomarán en cuenta a los 3 primeros médicos, en
    caso de que algún médico tenga igual cantidad de consultas que otro, se tomará en cuenta al de mayor antigüedad.
    Por ejemplo, los médicos Juan Pérez, Pedro López y Ruben Castrejon recibirán una compensación del 15% extra.
     */

    char month[3];

    printf("Aplicar compensacion\n");
    printf("Mes: ");
    scanf("%s", month);

    
}