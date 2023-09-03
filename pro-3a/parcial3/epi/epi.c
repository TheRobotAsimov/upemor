/* 
    EPI. Reporte de evidencia integradora.

    Integrantes:
    - García Mendoza Isaías
    - Gómez García José Alberto
    - Prado Acevedo Ian Marcus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* 

    Estructura de un paciente:
    
    - Nombre completo
    - Fecha de nacimiento
    - CURP (campo único)
    - Dirección
    - Teléfono
    Tres datos adicionales (de tres tipos de datos diferentes)
        - (char) Genero
        - (float) Indice de masa corporal inicial
        - (int) Nivel de tolerancia al dolor en una escala del 1 al 10. 
    - Número de citas de revisión que ha tenido
    - Indicador de borrado lógico

    Estructra de una cita:

    - Identificador de forma única al paciente
    - Fecha
    - Peso
    - Presión arterial
    Tres campos adicionales de diferente tipo
        - (float) Estatura
        - (char) Tipo de sangre
        - (int) Número de cirugías previas
    - Indicador de borrado lógico

 */

int menuOption();

int addPatient(char patientPath[], int patientSize);
    void nameFunction(char name[]);
    void birthDateFunction(char birthDate[]);
    void curpFunction(char curp[]);
    void addressFunction(char address[]);
    void phoneFunction(char phone[]);
    char genderFunction();
    float initialBMIFunction();
    int painToleranceFunction();

int sortPatients(char patientPath[], int patientSize);

int seekPatient(char patientPath[], char curp[], int patientSize);

int removePatient(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize);

int showPatients(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize, int state);

int printPatient(char patientPath[], int position);

int showAppointments(char appointmentPath[], char curp[], int appointmentSize);

int addAppointment(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize);
    void registrationDateFunction(char registrationDate[]);
    void bloodPressureFunction(char bloodPressure[]);
    void bloodTypeFunction(char bloodType[]);
    int weightFunction();
    float heightFunction();
    int surgeriesFunction();

int removeAppointment(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize);

int removePatientAppointments(char appointmentPath[], char curp[], int appointmentSize);

int searchDate(char appointmentPath[], char registrationDate[], char curp[], int appointmentSize);



int main ()
{
    int option;
    char patientPath[] = "pacientes.dat";
    char appointmentPath[] = "citas.dat";
    //                      Nombre              Fecha               CURP              Direccion           Telefono       Genero           IMC           Dolor     Numero de citas  Estado
    int patientSize = sizeof(char[50]) + sizeof(char[11]) + sizeof(char[19]) + sizeof(char[100]) + sizeof(char[11]) + sizeof(char) + sizeof(float) + sizeof(int) + sizeof(int) + sizeof(int);
    //                     Fecha registro         CURP            Peso      Presion arterial       Estatura     Tipo de sangre  Num. cirugías         Estado
    int appointmentSize = sizeof(char[11]) + sizeof(char[19]) + sizeof(int) + sizeof(char[8]) + sizeof(float) + sizeof(char[4]) + sizeof(int) + sizeof(int);  


    do
    {
        option = menuOption();
        switch (option)
        {
        case 1:
            printf("Agregar un nuevo paciente\n");
            addPatient(patientPath, patientSize);
            sortPatients(patientPath, patientSize);
            break;
        case 2:
            printf("Agregar una cita a un paciente previamente registrado\n");
            addAppointment(patientPath, patientSize, appointmentPath, appointmentSize);
            break;
        case 3:
            printf("Eliminar un paciente\n");
            removePatient(patientPath, patientSize, appointmentPath, appointmentSize);
            break;
        case 4:
            printf("Eliminar una cita de un paciente en particular\n");
            removeAppointment(patientPath, patientSize, appointmentPath, appointmentSize);
            break;
        case 5:
            printf("Modificar el registro de información de un paciente\n");
            break;
        case 6:
            printf("Consultar todos los pacientes con cita en una fecha particular\n");
            break;
        case 7:
            printf("Consulta un paciente por su nombre escrito de forma parcial\n");
            break;
        case 8:
            printf("Ver todos los pacientes activos\n");
            showPatients(patientPath, patientSize, appointmentPath, appointmentSize, 1);
            break;
        case 9:
            printf("Ver todos los pacientes borrados de forma lógica\n");
            showPatients(patientPath, patientSize, appointmentPath, appointmentSize, 0);
            break;
        case 0:
            printf("Salir\n");
            break;
        default:
            printf("Opción no válida\n");
            break;
        }
    } while (option != 0);

    return 0;
}

int menuOption ()
{
    int option;

    printf("\n\n");
    printf("1- Agregar un nuevo paciente\n");
    printf("2- Agregar una cita a un paciente previamente registrado\n");
    printf("3- Eliminar un paciente\n");
    printf("4- Eliminar una cita de un paciente en particular\n");
    printf("5- Modificar el registro de información de un paciente\n");
    printf("6- Consultar todos los pacientes con cita en una fecha particular\n");
    printf("7- Consulta un paciente por su nombre escrito de forma parcial\n");
    printf("8- Ver todos los pacientes activos\n");
    printf("9- Ver todos los pacientes borrados de forma lógica\n");
    printf("0- Salir\n");
    printf("Opción: ");
    scanf("%d", &option);

    return option;
}

int addPatient (char patientPath[], int patientSize)
{
    FILE *patientFile;

    patientFile = fopen(patientPath, "ab");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    printf("\n\n");

    char name[50];
    nameFunction(name);
    char birthDate[11];
    birthDateFunction(birthDate);

    int existence;
    char curp[19];
    do{
        curpFunction(curp);
        existence = seekPatient(patientPath, curp, patientSize);
        if (existence != -1) {
            printf("La CURP ya existe\n");
            printPatient(patientPath, existence);
            printf("\n----------------------------------------\n");
        }
    }while(existence != -1);

    char address[100];
    addressFunction(address);
    char phone[11];
    phoneFunction(phone);
    char gender = genderFunction();
    float initialBMI = initialBMIFunction();
    int painTolerance = painToleranceFunction();
    int numberOfAppointments = 0;
    int state = 1;

    fwrite(name, sizeof(name), 1, patientFile);
    fwrite(birthDate, sizeof(birthDate), 1, patientFile);
    fwrite(curp, sizeof(curp), 1, patientFile);
    fwrite(address, sizeof(address), 1, patientFile);
    fwrite(phone, sizeof(phone), 1, patientFile);
    fwrite(&gender, sizeof(gender), 1, patientFile);
    fwrite(&initialBMI, sizeof(initialBMI), 1, patientFile);
    fwrite(&painTolerance, sizeof(painTolerance), 1, patientFile);
    fwrite(&numberOfAppointments, sizeof(numberOfAppointments), 1, patientFile);
    fwrite(&state, sizeof(state), 1, patientFile);

    fclose(patientFile);
    return 1;
}

void nameFunction (char name[]) 
{
    int block;

    do{
        block = 0;

        printf("Nombre completo: ");
        scanf(" %50[^\n]", name);

        if (!isupper(name[0]))
        {
            block = 1;
            printf("El nombre debe empezar con mayúscula\n");
        } else

        for (int i = 0; i < strlen(name); i++)
        {
            if (isalpha(name[i]) == 0 && name[i] != ' ')
            {
                block = 1;
                printf("El nombre no puede contener números\n");
                break;
            }
        }


    }while (block != 0);
}

void birthDateFunction (char birthDate[])
{
    int block;

    do{
        block = 0;

        printf("Fecha de nacimiento (dd/mm/aaaa): ");
        scanf(" %[^\n]", birthDate);

        int day, month, year;

        if (strlen(birthDate) != 10)
        {
            block = 1;
            printf("La fecha de nacimiento debe tener 10 caracteres\n");
        } else

        if (birthDate[2] != '/' || birthDate[5] != '/')
        {
            block = 1;
            printf("La fecha de nacimiento debe tener el formato dd/mm/aaaa\n");
        } else

        if (!isdigit(birthDate[0]) || !isdigit(birthDate[1]) || !isdigit(birthDate[3]) || !isdigit(birthDate[4]) || !isdigit(birthDate[6]) || !isdigit(birthDate[7]) || !isdigit(birthDate[8]) || !isdigit(birthDate[9]))
        {
            block = 1;
            printf("La fecha de nacimiento no puede contener letras\n");
        } else {
            sscanf(birthDate, "%d/%d/%d", &day, &month, &year);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2023)
            {
                block = 1;
                printf("La fecha de nacimiento no es válida\n");
            }
        }

    }while (block != 0);
}

void curpFunction (char curp[])
{
    int block;
    int day, month, year; // Implementar
    // CURP: 4 letras, 2 numeros (año), 2 numeros (mes), 2 numeros (dia), 1 letra (genero), 2 letras (estado), 3 letras (iniciales), 2 numero o letra (homoclave)
    do{
        block = 0;

        printf("CURP: ");
        scanf(" %[^\n]", curp);

        if (strlen(curp) != 18)
        {
            block = 1;
            printf("La CURP debe tener 18 caracteres\n");
        } else

        if (!isdigit(curp[4]) || !isdigit(curp[5]) || !isdigit(curp[6]) || !isdigit(curp[7]) || !isdigit(curp[8]) || !isdigit(curp[9]))
        {
            block = 1;
            printf("Ingreso mal los numeros\n");
        } else {
            
            sscanf(curp, "%*4s%2d%2d%2d", &year, &month, &day);

            if (day < 1 || day > 31 || month < 1 || month > 12)
            {
                block = 1;
                printf("La fecha de nacimiento no es válida\n");
            } else
            
            for (int i = 0; i < strlen(curp); i++)
            {
                if ( !isalnum(curp[i]) || !isupper(curp[i]) && !isdigit(curp[i]) )
                {
                    block = 1;
                    printf("La CURP no puede contener minusculas o caracteres especiales\n");
                    break;
                }
            }
        }


    }while (block != 0);
}

void addressFunction (char address[])
{
    int block;

    do{
        block = 0;

        printf("Direccion: ");
        scanf(" %[^\n]", address);

        for (int i = 0; i < strlen(address); i++)
        {
            if (isalnum(address[i]) == 0 && address[i] != ' ')
            {
                block = 1;
                printf("La direccion no puede contener caracteres especiales\n");
                break;
            }
        }

    }while (block != 0);
}

void phoneFunction (char phone[])
{
    int block;

    do{
        block = 0;

        printf("Telefono: ");
        scanf(" %[^\n]", phone);

        if (strlen(phone) != 10)
        {
            block = 1;
            printf("El telefono debe tener 10 digitos\n");
        }

        for (int i = 0; i < strlen(phone); i++)
        {
            if (!isdigit(phone[i]))
            {
                block = 1;
                printf("El telefono no puede contener letras\n");
                break;
            }
        }
    }while (block != 0);
}

char genderFunction ()
{
    int block;
    char gender;

    do{
        block = 0;
        printf("Genero (M o F): ");
        scanf(" %c", &gender);

        if (gender != 'M' && gender != 'F')
        {
            block = 1;
            printf("El genero debe ser M o F\n");
        }

    }while (block != 0);

    return gender;
}

float initialBMIFunction ()
{
    int block;
    float initialBMI;

    do{
        block = 0;
        printf("Indice de masa corporal inicial: ");
        scanf("%f", &initialBMI);

        if (initialBMI < 0)
        {
            block = 1;
            printf("El indice de masa corporal no puede ser negativo\n");
        }

    }while (block != 0);

    return initialBMI;
}

int painToleranceFunction ()
{
    int block;
    int painTolerance;

    do{
        block = 0;
        printf("Nivel de tolerancia al dolor en una escala del 1 al 10: ");
        scanf("%d", &painTolerance);

        if (painTolerance < 1 || painTolerance > 10)
        {
            block = 1;
            printf("El nivel de tolerancia al dolor debe ser un numero entre 1 y 10\n");
        }

    }while (block != 0);

    return painTolerance;
}

int sortPatients(char patientPath[], int patientSize)
{
    FILE *patientFile;

    patientFile = fopen(patientPath, "rb+");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char name1[50], name2[50];
    char birthDate1[11], birthDate2[11];
    char curp1[19], curp2[19];
    char address1[100], address2[100];
    char phone1[11], phone2[11];
    char gender1, gender2;
    float initialBMI1, initialBMI2;
    int painTolerance1, painTolerance2;
    int numberOfAppointments1, numberOfAppointments2;
    int state1, state2;

    int numberOfPatients;
    fseek(patientFile, 0, SEEK_END);
    numberOfPatients = ftell(patientFile) / patientSize;
    fseek(patientFile, 0, SEEK_SET);

    // Ordenamiento por burbuja
    for(int i = 0; i < numberOfPatients - 1; i++)
    {
        for(int j = 0; j < numberOfPatients - i - 1; j++)
        {
            fseek(patientFile, j * patientSize, SEEK_SET);
            fread(name1, sizeof(name1), 1, patientFile);
            
            fseek(patientFile, (j + 1) * patientSize, SEEK_SET);
            fread(name2, sizeof(name2), 1, patientFile);

            if(strcmp(name1, name2) > 0)
            {
                // Registro 1
                fseek(patientFile, j * patientSize + sizeof(name1), SEEK_SET);
                fread(birthDate1, sizeof(birthDate1), 1, patientFile);
                fread(curp1, sizeof(curp1), 1, patientFile);
                fread(address1, sizeof(address1), 1, patientFile);
                fread(phone1, sizeof(phone1), 1, patientFile);
                fread(&gender1, sizeof(gender1), 1, patientFile);
                fread(&initialBMI1, sizeof(initialBMI1), 1, patientFile);
                fread(&painTolerance1, sizeof(painTolerance1), 1, patientFile);
                fread(&numberOfAppointments1, sizeof(numberOfAppointments1), 1, patientFile);
                fread(&state1, sizeof(state1), 1, patientFile);

                // Registro 2
                fseek(patientFile, sizeof(name1), SEEK_CUR);
                fread(birthDate2, sizeof(birthDate2), 1, patientFile);
                fread(curp2, sizeof(curp2), 1, patientFile);
                fread(address2, sizeof(address2), 1, patientFile);
                fread(phone2, sizeof(phone2), 1, patientFile);
                fread(&gender2, sizeof(gender2), 1, patientFile);
                fread(&initialBMI2, sizeof(initialBMI2), 1, patientFile);
                fread(&painTolerance2, sizeof(painTolerance2), 1, patientFile);
                fread(&numberOfAppointments2, sizeof(numberOfAppointments2), 1, patientFile);
                fread(&state2, sizeof(state2), 1, patientFile);

                // Cambiar registro 1 por registro 2
                fseek(patientFile, j * patientSize, SEEK_SET);
                fwrite(name2, sizeof(name2), 1, patientFile);
                fwrite(birthDate2, sizeof(birthDate2), 1, patientFile);
                fwrite(curp2, sizeof(curp2), 1, patientFile);
                fwrite(address2, sizeof(address2), 1, patientFile);
                fwrite(phone2, sizeof(phone2), 1, patientFile);
                fwrite(&gender2, sizeof(gender2), 1, patientFile);
                fwrite(&initialBMI2, sizeof(initialBMI2), 1, patientFile);
                fwrite(&painTolerance2, sizeof(painTolerance2), 1, patientFile);
                fwrite(&numberOfAppointments2, sizeof(numberOfAppointments2), 1, patientFile);
                fwrite(&state2, sizeof(state2), 1, patientFile);

                // Cambiar registro 2 por registro 1
                fwrite(name1, sizeof(name1), 1, patientFile);
                fwrite(birthDate1, sizeof(birthDate1), 1, patientFile);
                fwrite(curp1, sizeof(curp1), 1, patientFile);
                fwrite(address1, sizeof(address1), 1, patientFile);
                fwrite(phone1, sizeof(phone1), 1, patientFile);
                fwrite(&gender1, sizeof(gender1), 1, patientFile);
                fwrite(&initialBMI1, sizeof(initialBMI1), 1, patientFile);
                fwrite(&painTolerance1, sizeof(painTolerance1), 1, patientFile);
                fwrite(&numberOfAppointments1, sizeof(numberOfAppointments1), 1, patientFile);
                fwrite(&state1, sizeof(state1), 1, patientFile);
            }
        }
    }
    fclose(patientFile);
}

int seekPatient (char patientPath[], char curp[], int patientSize)
{
    FILE *patientFile;

    patientFile = fopen(patientPath, "rb");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char curpB[19];
    int state, position;

    int seekCurp = sizeof(char[50]) + sizeof(char[11]);
    int seekState = patientSize - (seekCurp + sizeof(curpB) + sizeof(int));

    fseek(patientFile, seekCurp, SEEK_SET);
    fread(curpB, sizeof(curpB), 1, patientFile);

    while (!feof(patientFile))
    {
        if (strcmp(curp, curpB) == 0)
        {
            fseek(patientFile, seekState, SEEK_CUR);
            fread(&state, sizeof(state), 1, patientFile);
            if (state == 1)
            {
                fseek(patientFile, -patientSize, SEEK_CUR);
                position = ftell(patientFile);

                fclose(patientFile);
                return position;
            }
            fseek(patientFile, -seekState-sizeof(int), SEEK_CUR);
        }
        
        fseek(patientFile, seekState + sizeof(int) + seekCurp, SEEK_CUR);
        fread(curpB, sizeof(curpB), 1, patientFile);
    }

    fclose(patientFile);
    return -1;
}

int removePatient (char patientPath[], int patientSize, char appointmentPath[], int appointmentSize)
{
    FILE *patientFile;

    patientFile = fopen(patientPath, "rb+");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char curp[19];
    curpFunction(curp);

    int position = seekPatient(patientPath, curp, patientSize);

    if (position == -1)
    {
        printf("No se encontro el paciente\n");
        return 0;
    }

    printPatient(patientPath, position);
    printf("----------------------------------------\n");
    
    int option;

    int state = 0, seekState = patientSize - sizeof(int);
    do{
        printf("\nEsta seguro que desea eliminar al paciente? (si = 1, no = 0): ");
        scanf("%d", &option);

        switch (option)
        {
            case 0:
                printf("Paciente no eliminado\n");
                fclose(patientFile);
                return 0;
                break;
            case 1:

                fseek(patientFile, position + seekState, SEEK_SET);
                fwrite(&state, sizeof(state), 1, patientFile);
                printf("Paciente eliminado\n");

                // Borrado de citas
                removePatientAppointments(appointmentPath, curp, appointmentSize);
              
                fclose(patientFile);
                return 1;
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }while (option != 0 && option != 1);

}

int showPatients(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize, int state)
{
    FILE *patientFile;

    patientFile = fopen(patientPath, "rb");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char curp[19];
    int seekCurp = sizeof(char[50]) + sizeof(char[11]);
    int stateB, seekState = patientSize - sizeof(int);

    int numberOfPatients;
    fseek(patientFile, 0, SEEK_END);
    numberOfPatients = ftell(patientFile) / patientSize;
    fseek(patientFile, 0, SEEK_SET);

    for (int i = 0; i < numberOfPatients; i++)
    {
        fseek(patientFile, i * patientSize + seekState, SEEK_SET);
        fread(&stateB, sizeof(stateB), 1, patientFile);

        if (stateB == state) 
        {
            printPatient(patientPath, i * patientSize);
        }

        if (stateB == 1)
        {
            fseek(patientFile, i * patientSize + seekCurp, SEEK_SET);
            fread(curp, sizeof(curp), 1, patientFile);
            printf("\n");
            showAppointments(appointmentPath, curp, appointmentSize); // Falta por mplementar
        }

    }

    printf("\n----------------------------------------\n\n");

    fclose(patientFile);
    return 1;
}

int printPatient(char patientPath[], int position)
{
    FILE *patientFile;

    patientFile = fopen(patientPath, "rb");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char name[50];
    char birthDate[11];
    char curp[19];
    char address[100];
    char phone[11];
    char gender;
    float initialBMI;
    int painTolerance;
    int numberOfAppointments;
    int state;

    fseek(patientFile, position, SEEK_SET);

    fread(name, sizeof(name), 1, patientFile);
    fread(birthDate, sizeof(birthDate), 1, patientFile);
    fread(curp, sizeof(curp), 1, patientFile);
    fread(address, sizeof(address), 1, patientFile);
    fread(phone, sizeof(phone), 1, patientFile);
    fread(&gender, sizeof(gender), 1, patientFile);
    fread(&initialBMI, sizeof(initialBMI), 1, patientFile);
    fread(&painTolerance, sizeof(painTolerance), 1, patientFile);
    fread(&numberOfAppointments, sizeof(numberOfAppointments), 1, patientFile);
    fread(&state, sizeof(state), 1, patientFile);

    printf("\n----------------------------------------\n");
    printf("\nNombre: %s\n", name);
    printf("Fecha de nacimiento: %s\n", birthDate);
    printf("CURP: %s\n", curp);
    printf("Direccion: %s\n", address);
    printf("Telefono: %s\n", phone);
    printf("Genero: %c\n", gender);
    printf("Indice de masa corporal inicial: %.2f\n", initialBMI);
    printf("Nivel de tolerancia al dolor en una escala del 1 al 10: %d\n", painTolerance);
    printf("Numero de citas de revision que ha tenido: %d\n", numberOfAppointments);
    printf("Estado: %d\n", state);

    fclose(patientFile);
    return 1;
}

int addAppointment(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize){
    
    char curp[19];
    curpFunction(curp);

    int position = seekPatient(patientPath, curp, patientSize);

    if (position == -1)
    {
        printf("No se encontro el paciente\n");
        return 0;
    }


    ////////////////////////////////////////////
    
    char registrationDate[11];
    registrationDateFunction(registrationDate);
    
    int resultado = searchDate(appointmentPath, registrationDate, curp, appointmentSize);

    if (resultado == 1) {
        printf("Solo se puede realiazar una cita al día\n");
        return 0;
    }

    if (resultado == -1) {
        return 0;
    }

    FILE *appointmentFile;

    appointmentFile = fopen(appointmentPath, "ab");

    if (appointmentFile == NULL)
    {
        printf("Error al abrir el archivo de citas\n");
        return 0;
    }
    
    int weight = weightFunction();
    char bloodPressure[8];
    bloodPressureFunction(bloodPressure);
    float height = heightFunction();
    char bloodType[4];
    bloodTypeFunction(bloodType);
    int surgeries = surgeriesFunction();
    int state = 1;
        
    fwrite(curp, sizeof(curp), 1, appointmentFile);
    fwrite(registrationDate, sizeof(registrationDate), 1, appointmentFile);
    fwrite(&weight, sizeof(int), 1, appointmentFile);
    fwrite(bloodPressure, sizeof(bloodPressure), 1, appointmentFile);
    fwrite(&height, sizeof(float), 1, appointmentFile);
    fwrite(bloodType, sizeof(bloodType), 1, appointmentFile);
    fwrite(&surgeries, sizeof(int), 1, appointmentFile);
    fwrite(&state, sizeof(state), 1, appointmentFile);

    fclose(appointmentFile);
    
    /////////////////////////////////////////////////

    FILE *patientFile;

    patientFile = fopen(patientPath, "rb+");

    if (patientFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }
    
    int numberOfAppointments;
    int seekAppointments = patientSize - sizeof(int) - sizeof(int);

    fseek(patientFile, position + seekAppointments, SEEK_SET);
    fread(&numberOfAppointments, sizeof(numberOfAppointments), 1, patientFile);
    numberOfAppointments++;
    fseek(patientFile, -sizeof(int), SEEK_CUR);
    fwrite(&numberOfAppointments, sizeof(numberOfAppointments), 1, patientFile);
    
    fclose(patientFile);
    
    return 1;
}


int searchDate(char appointmentPath[], char date[], char curp[], int appointmentSize) {
    FILE *appointmentFile = fopen(appointmentPath, "rb");
    if (appointmentFile == NULL) {
        printf("No se pudo abrir el archivo de citas.\n");
        return -1; // Valor de retorno para indicar error
    }

    int position = -1; // Flag para indicar si se encontró el dato
    int i = 0;
    char date2[11], curp2[19];

    while (!feof(appointmentFile)) {
        fseek(appointmentFile, i * appointmentSize, SEEK_SET);
        fread(curp2, sizeof(curp2), 1, appointmentFile);
        printf("%s = %s ?\n", curp2, curp); // Quitar
        if (strcmp(curp2, curp) == 0) {
            fread(date2, sizeof(date2), 1, appointmentFile);
            printf("%s = %s ?\n", date2, date); // Quiitar
            if (strcmp(date2, date) == 0) {
                fseek(appointmentFile, i * appointmentSize, SEEK_SET);
                position = ftell(appointmentFile);
                break;
            }
        }
        i++;
    }

    fclose(appointmentFile);

    return position;
}

int showAppointments(char appointmentPath[], char curp[], int appointmentSize)
{
    FILE *appointmentFile;

    appointmentFile = fopen(appointmentPath, "rb");

    if (appointmentFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char curpB[19];
    char registrationDate[11];
    int weight;
    char bloodPressure[8];
    float height;
    char bloodType[4];
    int surgeries;
    int state, seekState = appointmentSize - sizeof(int);
    int i = 0;

    fseek(appointmentFile, i * appointmentSize, SEEK_SET);
    fread(curpB, sizeof(curpB), 1, appointmentFile);

    while (!feof(appointmentFile))
    {
        if (strcmp(curp, curpB) == 0)
        {
            fseek(appointmentFile, i * appointmentSize + seekState, SEEK_SET);
            fread(&state, sizeof(state), 1, appointmentFile);
            if (state)
            {
                fseek(appointmentFile, i * appointmentSize + sizeof(curpB), SEEK_SET);
                fread(registrationDate, sizeof(registrationDate), 1, appointmentFile);
                fread(&weight, sizeof(weight), 1, appointmentFile);
                fread(bloodPressure, sizeof(bloodPressure), 1, appointmentFile);
                fread(&height, sizeof(height), 1, appointmentFile);
                fread(bloodType, sizeof(bloodType), 1, appointmentFile);
                fread(&surgeries, sizeof(surgeries), 1, appointmentFile);
                fread(&state, sizeof(state), 1, appointmentFile);

                printf("Fecha de la cita: %s\n", registrationDate);
                printf("Peso: %d\n", weight);
                printf("Presión arterial: %s\n", bloodPressure);
                printf("Estatura: %.2f\n", height);
                printf("Tipo de sangre: %s\n", bloodType);
                printf("Numero de cirugías previas: %d\n", surgeries);
                printf("Estado: %d\n\n", state);
            }
        }
        i++;
        fseek(appointmentFile, i * appointmentSize, SEEK_SET);
        fread(curpB, sizeof(curpB), 1, appointmentFile);
    }

    fclose(appointmentFile);
    return 1;
}

void registrationDateFunction(char registrationDate[]){
    int block;

    do{
        block = 0;

        printf("Fecha de la cita (dd/mm/aaaa): ");
        scanf(" %[^\n]", registrationDate);
        
        int day, month, year;

        if (strlen(registrationDate) != 10)
        {
            block = 1;
            printf("La fecha debe tener 10 caracteres\n");
        }else

        if (registrationDate[2] != '/' || registrationDate[5] != '/')
        {
            block = 1;
            printf("La fecha de nacimiento debe tener el formato dd/mm/aaaa\n");
        } else

        if (!isdigit(registrationDate[0]) || !isdigit(registrationDate[1]) || !isdigit(registrationDate[3]) || !isdigit(registrationDate[4]) || !isdigit(registrationDate[6]) || !isdigit(registrationDate[7]) || !isdigit(registrationDate[8]) || !isdigit(registrationDate[9]))
        {
            block = 1;
            printf("La fecha de nacimiento no puede contener letras\n");
        } else {
            sscanf(registrationDate, "%d/%d/%d", &day, &month, &year);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2023)
            {
                block = 1;
                printf("La fecha de nacimiento no es válida\n");
            }
        }

    }while (block != 0);
}

void bloodPressureFunction(char bloodPressure[]){
    int block;

    do{
        block = 0;

        printf("Presión arterial xxx/xxx (En caso de ser doble digito 0xx/0xx): ");
        scanf(" %[^\n]", bloodPressure);
        
        int num1, num2;

        if (strlen(bloodPressure) > 7)
        {
            block = 1;
            printf("La Presión arterial debe tener 7 caracteres\n");
        }else

        if (bloodPressure[3] != '/' )
        {
            block = 1;
            printf("La presión arterial debe tener el formato (xxx/xxx)\n");
        }else
        
        if (!isdigit(bloodPressure[0]) || !isdigit(bloodPressure[1]) || !isdigit(bloodPressure[2]) || !isdigit(bloodPressure[4]) || !isdigit(bloodPressure[5]) || !isdigit(bloodPressure[6]))
        {
            block = 1;
            printf("La presión arterial no puede contener letras\n");
        } else {
            sscanf(bloodPressure, "%d/%d", &num1, &num2);
            if (num1 < 80 || num1 > 180 || num2 < 50 || num2 > 120)
            {
                block = 1;
                printf("La presión arterial no es válida\n");
            }
        }

    }while (block != 0);
}

void bloodTypeFunction(char bloodType[]){
    int block;

    do{
        block = 0;

        printf("Tipo de sangre (A+, A-, B+, B-, AB+, AB-, O+ y O-): ");
        scanf(" %[^\n]", bloodType);

        if (strlen(bloodType) > 3)
        {
            block = 1;
            printf("El tipo de sangre debe tener 3 caracteres\n");
        }else
        
        if (strcspn(bloodType, "0123456789") != strlen(bloodType)) {
            block = 1; // Contiene dígitos, no es válido
            printf("No debe llevar dígitos\n");
        }
        
        for (int i = 0; bloodType[i] != '\0'; i++) {
            if (!isalpha(bloodType[i]) && bloodType[i] != '+' && bloodType[i] != '-') {
                block = 1; // No es un tipo de sangre válido
                printf("No es un tipo de sangre válido\n");
            }
        }
        
    }while (block != 0);
}

int weightFunction(){
    int block;
    int weight;

    do{
        block = 0;
        printf("Peso: ");
        scanf("%d", &weight);

        if (weight < 0)
        {
            block = 1;
            printf("El peso no puede ser negativo\n");
        }

    }while (block != 0);

    return weight;
}

float heightFunction(){
    int block;
    float height;

    do{
        block = 0;
        printf("Estatura: ");
        scanf("%f", &height);

        if (height < 0)
        {
            block = 1;
            printf("La estatura no puede ser negativa\n");
        }

    }while (block != 0);

    return height;
}

int surgeriesFunction(){
    int block;
    int surgeries;

    do{
        block = 0;
        printf("Numero de cirugías previas: ");
        scanf("%d", &surgeries);

        if (surgeries < 0)
        {
            block = 1;
            printf("El numero de cirugías previas no puede ser negativo\n");
        }

    }while (block != 0);

    return surgeries;
}

int removeAppointment(char patientPath[], int patientSize, char appointmentPath[], int appointmentSize){
    char curp[19];
    curpFunction(curp);

    int position = seekPatient(patientPath, curp, patientSize);

    if (position == -1){
        printf("No se encontro el paciente\n");
        return 0;
    }
    
    FILE *appointmentFile;

    appointmentFile = fopen(appointmentPath, "rb+");

    if (appointmentFile == NULL){
        printf("Error al abrir el archivo de citas\n");
        return 0;
    }
    
    printf("\n----------------------------------------\n");
    showAppointments(appointmentPath, curp, appointmentSize);
    printf("----------------------------------------\n");
    
    char registrationDate[11];
    registrationDateFunction(registrationDate);
    
    int position2 = searchDate(appointmentPath, registrationDate, curp, appointmentSize);
    int block;
    
    do{
        if (position2 >= 0){
            int option;
    
            int state = 0, seekState = appointmentSize - sizeof(int);
            do{
                printf("\nEsta seguro que desea eliminar la cita? (si = 1, no = 0): ");
                scanf("%d", &option);
    
                switch (option)
                {
                    case 0:
                        printf("Cita no eliminada\n");
                        fclose(appointmentFile);
                        block = 0;
                        break;
                    case 1:
                        fseek(appointmentFile, position2 + seekState, SEEK_CUR);
                        fwrite(&state, sizeof(state), 1, appointmentFile);
                      
                        printf("Cita eliminada\n");
                        
                        fclose(appointmentFile);
                        
                        FILE *patientFile;
                        
                        patientFile = fopen(patientPath, "rb+");
                        
                        if (patientFile == NULL)
                        {
                          printf("Error al abrir el archivo\n");
                          return 0;
                        }
                        
                        int numberOfAppointments;
                        int seekAppointments = patientSize - sizeof(int) - sizeof(int);
                        
                        fseek(patientFile, position + seekAppointments, SEEK_SET);
                        fread(&numberOfAppointments, sizeof(numberOfAppointments), 1, patientFile);
                        numberOfAppointments--;
                        fseek(patientFile, -sizeof(int), SEEK_CUR);
                        fwrite(&numberOfAppointments, sizeof(numberOfAppointments), 1, patientFile);
                        
                        fclose(patientFile);
                        
                        block = 0;
                        break;
                    default:
                        printf("Opcion no valida\n");
                        block = 0;
                        break;
                }
            }while (option != 0 && option != 1);
        }
        if (position2 == -1) {
            printf("No se encontró la cita\n");
            block = 1;
        }
    }while(block != 0);
}

int removePatientAppointments(char appointmentPath[], char curp[], int appointmentSize)
{
    FILE *appointmentFile;

    appointmentFile = fopen(appointmentPath, "rb+");

    if (appointmentFile == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char curpB[19];
    int state = 0, seekState = appointmentSize - sizeof(curpB) - sizeof(int);
    int i = 0;

    fread(curpB, sizeof(curpB), 1, appointmentFile);

    while(!feof(appointmentFile))
    {
        if (strcmp(curp, curpB) == 0)
        {
            fseek(appointmentFile, seekState, SEEK_CUR);
            fwrite(&state, sizeof(state), 1, appointmentFile);
        }
        i++;
        fseek(appointmentFile, i * appointmentSize, SEEK_SET);
        fread(curpB, sizeof(curpB), 1, appointmentFile);
    }
}