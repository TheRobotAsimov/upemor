/*

  EP3 Archivos

    Integrantes:
    - García Mendoza Isaías
    - Gómez García José Alberto
    - Prado Acevedo Ian Marcus

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 

    Estructura de un cliente:
    
    - Nombre
    - Fecha de nacimiento
    - RFC
    - Dirección
    - Teléfono
    - Monto de crédito
    - Monto de deuda actual

    * 4 datos adicionales (de tres tipos de datos diferentes, no arreglos de caracteres)
    - Calidad de cliente (A, B, C, D, E)
    - Cantidad de compras
    - Cantidad de pagos
    - Precio de la última compra

    - Estado (activo = 1 o borrado = 0)

 */

int menu(void);

int addClient(char path[], long int position); // Validar
    void funcName(char nameA[]);
    void funcDate(char birthDate[]);
    void funcRFC(char rfc[]);
    void funcAddress(char address[]);
    void funcPhone(char phone[]);
    float funcCreditAm();
    float funcDebtAm();
    char funQuality();
    int funcParchuses();
    int funcPayments();
    float funcLastPar();

int deleteClient(char path[], long int dataSize); // Validar

int buyOrPay(char path[], int mode, long int dataSize);

int modify(char path[], long int dataSize); // Validar

int consultClient(char path[], char rfc[], long int dataSize); // Diferentes campos. Validar

void showActive(char path[], long int dataSize);
void showDeleted(char path[], long int dataSize);
void showAll(char path[]);
void ordenar(char path[]); 

int main(void) {
    int option, mode;
    char path[] = "clientes.dat";
    char rfc[14];
    //                          Nombre      Fecha de nacimiento           RFC          Direccion            Telefono          Credito         Deuda           Calidad        Compras       Pagos    Ultima compra       Estado
    long int dataSize = sizeof(char[50]) + sizeof(char[11]) + sizeof(char[14]) + sizeof(char[100]) + sizeof(char[11]) + sizeof(float) + sizeof(float) + sizeof(char) + sizeof(int) + sizeof(int) + sizeof(float) + sizeof(int);

    printf("%ld ", dataSize);
  
    do {
        option = menu();

        switch (option) {
            case 1:
                addClient(path, -1); // -1 para agregar al final
                break;
            case 2:
                deleteClient(path, dataSize);
                break;
            case 3:
                printf(" 1. Comprar\n");
                printf(" 2. Pagar\n");
                printf(" Ingrese la opcion que desee: ");
                scanf("%d", &mode);

                if (mode != 1 && mode != 2) {
                    printf(" Opcion invalida\n");
                    break;
                }

                buyOrPay(path, mode, dataSize);
                break;
            case 4:
                modify(path, dataSize);
                break;
            case 5: ; // Punto y coma para que no marque error
                char rfc[14];
                funcRFC(rfc);
                consultClient(path, rfc, dataSize);
                break;
            case 6:
                showActive(path, dataSize);
                break;
            case 7:
                showDeleted(path, dataSize);
                break;
            case 8:
                showAll(path);
                break;
            case 0:
                printf(" Saliendo...\n");
                break;
            default:
                printf(" Opcion invalida\n");
                break;
        }
    } while (option != 0);

    return 0;
}

int menu(void) {
    int option;

    printf("\n MENU\n");
    printf(" 1. Agregar nuevo cliente\n");
    printf(" 2. Eliminar cliente\n");
    printf(" 3. Hacer compra o pago\n");
    printf(" 4. Modificar datos de cliente\n");
    printf(" 5. Consultar cliente\n");
    printf(" 6. Ver todos los clientes activos\n");
    printf(" 7. Ver todos los clientes borrados\n");
    printf(" 8. Ver todos los clientes\n");
    printf(" 0. Salir\n");

    printf(" Ingrese la opcion que desee: ");
    scanf("%d", &option);
    printf("\n");

    return option;
}

int addClient (char path[], long int position) {
    FILE *file;

    file = fopen(path, "r+b");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return 0;
    }

    char name[50];
    funcName(name);
    char birthDate[11];
    funcDate(birthDate);
    char address[100];
    funcAddress(address);
    char rfc[14];
    char phone[11];
    funcPhone(phone);
    float creditAmount = funcCreditAm();
    float debtAmount = funcDebtAm();
    char quality = funQuality();
    int purchases = funcParchuses();
    int payments = funcPayments();
    float lastPurchase = funcLastPar();
    int state = 1;
    //                          Nombre      Fecha de nacimiento           RFC          Direccion            Telefono          Credito         Deuda           Calidad        Compras       Pagos    Ultima compra       Estado
    long int dataSize = sizeof(char[50]) + sizeof(char[11]) + sizeof(char[14]) + sizeof(char[100]) + sizeof(char[11]) + sizeof(float) + sizeof(float) + sizeof(char) + sizeof(int) + sizeof(int) + sizeof(float) + sizeof(int);

    // Si te dan una posición, saltate el rfc
    if (position >= 0) {
        fseek(file, position, SEEK_SET);

        fwrite(name, sizeof(name), 1, file);
        fwrite(birthDate, sizeof(birthDate), 1, file);
        fseek(file, sizeof(rfc), SEEK_CUR);
        //fwrite(rfc, sizeof(rfc), 1, file);
    } else {

        do{
            funcRFC(rfc);
                // Evitar repetidos
        }while (consultClient(path, rfc, dataSize) >= 0);

        fseek(file, 0, SEEK_END);

        fwrite(name, sizeof(name), 1, file);
        fwrite(birthDate, sizeof(birthDate), 1, file);
        fwrite(rfc, sizeof(rfc), 1, file);
        
    }

    fwrite(address, sizeof(address), 1, file);
    fwrite(phone, sizeof(phone), 1, file);
    fwrite(&creditAmount, sizeof(float), 1, file);
    fwrite(&debtAmount, sizeof(float), 1, file);
    fwrite(&quality, sizeof(char), 1, file);
    fwrite(&purchases, sizeof(int), 1, file);
    fwrite(&payments, sizeof(int), 1, file);
    fwrite(&lastPurchase, sizeof(float), 1, file);
    fwrite(&state, sizeof(int), 1, file);


    fclose(file);

    return 1;
}

int deleteClient(char path[], long int dataSize) { // rfc
    FILE *file;

    file = fopen(path, "r+b");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return 0;
    }

    char rfc1[14], rfc2[14];    
    int state, similar;
    long int nextDataAfterRFC = dataSize - (sizeof(char[50]) + sizeof(char[11]) + sizeof(char[14]));
    long int seekRFC = sizeof(char[50]) + sizeof(char[11]);
    long int seekState = nextDataAfterRFC - sizeof(int);

    funcRFC(rfc1);

    fseek(file, seekRFC, SEEK_SET);

    while (!feof(file)) {
        fread(rfc2, sizeof(rfc2), 1, file);
        fseek(file, seekState, SEEK_CUR);
        fread(&state, sizeof(int), 1, file);

        if (strcmp(rfc1, rfc2) == 0) {

            if(state == 0) {
                printf(" El cliente ya esta eliminado\n");
                return 0;
            }
            // Se regresa para sobreescribir el estado
            fseek(file, -sizeof(int), SEEK_CUR);
            state = 0;
            fwrite(&state, sizeof(int), 1, file);
            printf(" Cliente eliminado\n");
            return 1;
        }

        fseek(file, seekRFC, SEEK_CUR);
    }

    printf(" No se encontro el cliente\n");

    fclose(file);

    return 0;
}

// Comprar aumenta el monto de deuda actual y pagar lo disminuye
int buyOrPay(char path[], int mode, long int dataSize) {
    FILE *file;
    char rfc[14];

    funcRFC(rfc);

    long int position = consultClient(path, rfc, dataSize);

    if(position < 0) {
        return 0;
    }


    file = fopen(path, "r+b");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return 0;
    }

    long int seekDebt = position + sizeof(char[50]) + sizeof(char[11]) + sizeof(char[14]) + sizeof(char[100]) + sizeof(char[11]) + sizeof(float);
    float debt;
    float amount;

    if(mode == 1) {
        printf(" Ingrese el monto de la compra: ");
        scanf("%f", &amount);
    } else {
        printf(" Ingrese el monto del pago: ");
        scanf("%f", &amount);
        amount *= -1;
    }

    fseek(file, seekDebt, SEEK_SET);
    fread(&debt, sizeof(float), 1, file);

    fseek(file, -sizeof(float), SEEK_CUR);
    debt += amount;
    fwrite(&debt, sizeof(float), 1, file);

    fclose(file);

    return 1;

}

int modify(char path[], long int dataSize) { // preguntar
    FILE *file;

    file = fopen(path, "r+b");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return 0;
    }

    char rfc[14];
    funcRFC(rfc);

    long int position = consultClient(path, rfc, dataSize);

    if(position < 0) {
        return 0;
    }

    addClient(path, position);

    fclose(file);
    return 1;
}

int consultClient(char path[], char rfc[], long int dataSize) {
    FILE *file;

    file = fopen(path, "rb");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return -1;
    }

    char name[50];
    char birthDate[11];
    char rfcB[14];
    char address[100];
    char phone[11];
    float creditAmount;
    float debtAmount;
    char quality;
    int purchases;
    int payments;
    float lastPurchase;
    int state;

    long int seekRFC = sizeof(name) + sizeof(birthDate);
    long int nextDataAfterRFC = dataSize - (seekRFC + sizeof(rfcB));
    long int seekState = nextDataAfterRFC - sizeof(int);

    fseek(file, seekRFC, SEEK_SET);
    fread(rfcB, sizeof(rfcB), 1, file);

    while (!feof(file)) {

        if (strcmp(rfc, rfcB) == 0) {

            // Antes del estado
            fseek(file, seekState, SEEK_CUR);
            fread(&state, sizeof(int), 1, file);

            if(state == 1){
                //fwrite(&state, sizeof(int), 1, file);
                fseek(file, -dataSize, SEEK_CUR);

                int position = ftell(file);

                fread(name, sizeof(name), 1, file);
                fread(birthDate, sizeof(birthDate), 1, file);
                fread(rfcB, sizeof(rfcB), 1, file);
                fread(address, sizeof(address), 1, file);
                fread(phone, sizeof(phone), 1, file);
                fread(&creditAmount, sizeof(float), 1, file);
                fread(&debtAmount, sizeof(float), 1, file);
                fread(&quality, sizeof(char), 1, file);
                fread(&purchases, sizeof(int), 1, file);
                fread(&payments, sizeof(int), 1, file);
                fread(&lastPurchase, sizeof(float), 1, file);
                fread(&state, sizeof(int), 1, file);

                printf("\n RFC encontrado\n\n");

                printf(" Nombre: %s\n", name);
                printf(" Fecha de nacimiento: %s\n", birthDate);
                printf(" RFC: %s\n", rfcB);
                printf(" Direccion: %s\n", address);
                printf(" Telefono: %s\n", phone);
                printf(" Monto de credito: %.2f\n", creditAmount);
                printf(" Monto de deuda actual: %.2f\n", debtAmount);
                printf(" Calidad: %c\n", quality);
                printf(" Compras: %d\n", purchases);
                printf(" Pagos: %d\n", payments);
                printf(" Ultima compra: %.2f\n", lastPurchase);
                printf(" Estado: %d\n", state);
                printf("\n");

                fclose(file);
                return position;

            }

            fseek(file, -(nextDataAfterRFC + seekRFC), SEEK_CUR);

        }

        fseek(file, nextDataAfterRFC + seekRFC, SEEK_CUR);
        fread(rfcB, sizeof(rfcB), 1, file);
    }

    printf(" No se encontro el cliente\n");
    fclose(file);
    return -1;
}

void showActive(char path[], long int dataSize) {
    FILE *file;

    file = fopen(path, "rb");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return;
    }

    char name[50];
    char birthDate[11];
    char rfc[14];
    char address[100];
    char phone[11];
    float creditAmount;
    float debtAmount;
    char quality;
    int purchases;
    int payments;
    float lastPurchase;
    int state;
    long int seekState = dataSize - sizeof(int);

    fseek(file, seekState, SEEK_SET);
    fread(&state, sizeof(int), 1, file);

    while(!feof(file)) {
        if (state == 1) {
            // Regresa al principio del registro
            fseek(file, -dataSize, SEEK_CUR);

            fread(name, sizeof(name), 1, file);
            fread(birthDate, sizeof(birthDate), 1, file);
            fread(rfc, sizeof(rfc), 1, file);
            fread(address, sizeof(address), 1, file);
            fread(phone, sizeof(phone), 1, file);
            fread(&creditAmount, sizeof(float), 1, file);
            fread(&debtAmount, sizeof(float), 1, file);
            fread(&quality, sizeof(char), 1, file);
            fread(&purchases, sizeof(int), 1, file);
            fread(&payments, sizeof(int), 1, file);
            fread(&lastPurchase, sizeof(float), 1, file);
            fread(&state, sizeof(int), 1, file);

            printf(" Nombre: %s\n", name);
            printf(" Fecha de nacimiento: %s\n", birthDate);
            printf(" RFC: %s\n", rfc);
            printf(" Direccion: %s\n", address);
            printf(" Telefono: %s\n", phone);
            printf(" Monto de credito: %.2f\n", creditAmount);
            printf(" Monto de deuda actual: %.2f\n", debtAmount);
            printf(" Calidad: %c\n", quality);
            printf(" Compras: %d\n", purchases);
            printf(" Pagos: %d\n", payments);
            printf(" Ultima compra: %.2f\n", lastPurchase);
            printf(" Estado: %d\n", state);
            printf("\n");
        }

        fseek(file, seekState, SEEK_CUR);
        fread(&state, sizeof(int), 1, file);
    }

    fclose(file);

}

void showDeleted(char path[], long int dataSize) {
    FILE *file;

    file = fopen(path, "rb");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return;
    }

    char name[50];
    char birthDate[11];
    char rfc[14];
    char address[100];
    char phone[11];
    float creditAmount;
    float debtAmount;
    char quality;
    int purchases;
    int payments;
    float lastPurchase;
    int state;
    long int seekState = dataSize - sizeof(int);

    fseek(file, seekState, SEEK_SET);
    fread(&state, sizeof(int), 1, file);

    while(!feof(file)) {
        if (state == 0) {
            // Regresa al principio del registro
            fseek(file, -dataSize, SEEK_CUR);

            fread(name, sizeof(name), 1, file);
            fread(birthDate, sizeof(birthDate), 1, file);
            fread(rfc, sizeof(rfc), 1, file);
            fread(address, sizeof(address), 1, file);
            fread(phone, sizeof(phone), 1, file);
            fread(&creditAmount, sizeof(float), 1, file);
            fread(&debtAmount, sizeof(float), 1, file);
            fread(&quality, sizeof(char), 1, file);
            fread(&purchases, sizeof(int), 1, file);
            fread(&payments, sizeof(int), 1, file);
            fread(&lastPurchase, sizeof(float), 1, file);
            fread(&state, sizeof(int), 1, file);

            printf(" Nombre: %s\n", name);
            printf(" Fecha de nacimiento: %s\n", birthDate);
            printf(" RFC: %s\n", rfc);
            printf(" Direccion: %s\n", address);
            printf(" Telefono: %s\n", phone);
            printf(" Monto de credito: %.2f\n", creditAmount);
            printf(" Monto de deuda actual: %.2f\n", debtAmount);
            printf(" Calidad: %c\n", quality);
            printf(" Compras: %d\n", purchases);
            printf(" Pagos: %d\n", payments);
            printf(" Ultima compra: %.2f\n", lastPurchase);
            printf(" Estado: %d\n", state);
            printf("\n");
        }

        fseek(file, seekState, SEEK_CUR);
        fread(&state, sizeof(int), 1, file);
    }

    fclose(file);
}

void showAll(char path[]) {
    FILE *file;


    file = fopen(path, "rb");

    if (file == NULL) {
        printf(" Error al abrir el archivo\n");
        return;
    }

    char name[50];
    char birthDate[11];
    char rfc[14];
    char address[100];
    char phone[11];
    float creditAmount;
    float debtAmount;
    char quality;
    int purchases;
    int payments;
    float lastPurchase;
    int state;

    fread(name, sizeof(name), 1, file);

    while (!feof(file)) {
        fread(birthDate, sizeof(birthDate), 1, file);
        fread(rfc, sizeof(rfc), 1, file);
        fread(address, sizeof(address), 1, file);
        fread(phone, sizeof(phone), 1, file);
        fread(&creditAmount, sizeof(float), 1, file);
        fread(&debtAmount, sizeof(float), 1, file);
        fread(&quality, sizeof(char), 1, file);
        fread(&purchases, sizeof(int), 1, file);
        fread(&payments, sizeof(int), 1, file);
        fread(&lastPurchase, sizeof(float), 1, file);
        fread(&state, sizeof(int), 1, file);

        printf(" Nombre: %s\n", name);
        printf(" Fecha de nacimiento: %s\n", birthDate);
        printf(" RFC: %s\n", rfc);
        printf(" Direccion: %s\n", address);
        printf(" Telefono: %s\n", phone);
        printf(" Monto de credito: %.2f\n", creditAmount);
        printf(" Monto de deuda actual: %.2f\n", debtAmount);
        printf(" Calidad: %c\n", quality);
        printf(" Compras: %d\n", purchases);
        printf(" Pagos: %d\n", payments);
        printf(" Ultima compra: %.2f\n", lastPurchase);
        printf(" Estado: %d\n", state);
        printf("\n");
    
        fread(name, sizeof(name), 1, file);
    }

    fclose(file);

}
void funcName(char nameA[]){
    int block;

    do{
        block = 0;
        printf(" Ingrese el nombre del cliente: ");
        scanf(" %[^\n]", nameA);

        if(strlen(nameA) > 50){
            printf(" El nombre es demasiado largo\n");
            block = 1;
        }
        if (strlen(nameA) == 0){
            printf(" El nombre no puede estar vacio\n");
            block = 1;
        }
        for(int i = 0; i < strlen(nameA); i++){
            if(!isalpha(nameA[i]) && nameA[i] != ' '){
                printf(" El nombre no puede contener caracteres especiales\n");
                block = 1;
                break;
            }
        }

    }while (block);

   return;
}
void funcDate(char birthDate[]){
   
    int block;

    do{
        block = 0;
        printf(" Ingrese la fecha de nacimiento del cliente (dd/mm/aa): ");
        scanf(" %[^\n]", birthDate);
        
        int day = atoi(birthDate); // Para de leer hasta que se encuentra un caracter que no sea numero
        int month = atoi(birthDate + 3); // La direccion de memoria se mueve 3 espacios para adelante

        if(strlen(birthDate) != 8){
            printf(" La fecha debe tener 8 caracteres\n");
            block = 1;
        } else

        if (!isdigit(birthDate[0]) || !isdigit(birthDate[1]) || !isdigit(birthDate[3]) || !isdigit(birthDate[4]) || !isdigit(birthDate[6]) || !isdigit(birthDate[7])){
            printf(" Debe ingresar un numero\n");
            block = 1;
        } else

        if (birthDate[2] != '/' || birthDate[5] != '/') {
            printf(" La fecha debe ser separado por un '/'\n");
            block = 1;
        } else

        if (day < 1 || day > 31) {
            printf(" El dia debe estar entre 1 y 31\n");
            block = 1;
        } else

        if (month < 1 || month > 12) {
            printf(" El mes debe estar entre 1 y 12\n");
            block = 1;
        }

    }while(block);
    return;

}
void funcRFC(char rfc[]){

    int block;
    
    do {
        // RFC: 4 letras, 6 numeros (año, mes, dia de nacimiento), 3 letras o numeros
        block = 0;
        printf(" Ingrese el RFC del cliente: ");
        scanf(" %[^\n]", rfc);

        int date = atoi(rfc + 4);
        // date: aammdd -> 6 digitos
        int year = date / 10000;
        int month = (date % 10000) / 100; // Lo que sobre de dividir entre 10000
        int day = date % 100; // Lo que sobre de dividir entre 100

        if (strlen(rfc) != 13) {
            printf(" El RFC debe tener 13 caracteres\n");
            block = 1;
        } else
        if (!isalpha(rfc[0]) || !isalpha(rfc[1]) || !isalpha(rfc[2]) || !isalpha(rfc[3])) {
            printf(" Los primeros 4 caracteres deben ser letras\n");
            block = 1;
        } else
        if (isupper(rfc[0]) == 0 || isupper(rfc[1]) == 0 || isupper(rfc[2]) == 0 || isupper(rfc[3]) == 0) {
            printf(" Los primeros 4 caracteres deben ser mayusculas\n");
            block = 1;
        } else
        if (!isdigit(rfc[4]) || !isdigit(rfc[5]) || !isdigit(rfc[6]) || !isdigit(rfc[7]) || !isdigit(rfc[8]) || !isdigit(rfc[9])) {
            printf(" No puso números donde debía\n");
            block = 1;
        } else
        if (year < 0 || year > 99 || month < 1 || month > 12 || day < 1 || day > 31) {
            printf(" La fecha de nacimiento no es valida\n");
            block = 1;
        } else
        if (!isdigit(rfc[10]) && !isupper(rfc[10]) || !isdigit(rfc[11]) && !isupper(rfc[11]) || !isdigit(rfc[12]) && !isupper(rfc[12])) {
            printf(" Los ultimos 3 caracteres deben ser letras mayusculas o numeros\n");
            block = 1;
        }
        
    } while (block);


   return;
}
void funcAddress(char address[]){
    
    int block;

    do{
        block = 0;
        printf(" Ingrese la direccion del cliente: ");
        scanf(" %[^\n]", address);

        if(strlen(address) > 100){
            printf(" La direccion es demasiado larga\n");
            block = 1;
        }
        if (strlen(address) == 0){
            printf(" La direccion no puede estar vacia\n");
            block = 1;
        }
        for(int i = 0; i < strlen(address); i++){
            if(!isalnum(address[i]) && address[i] != ' '){
                printf(" La direccion no puede contener caracteres especiales\n");
                block = 1;
                break;
            }
        }
    } while (block);

    return;
    
}
void funcPhone(char phone[]){
    
    int block;

    do {
        block = 0;
        printf(" Ingrese el telefono del cliente: ");
        scanf(" %[^\n]", phone);

        if (strlen(phone) != 10) {
            printf(" El telefono debe tener 10 caracteres\n");
            block = 1;
        } else
        if (!isdigit(phone[0]) || !isdigit(phone[1]) || !isdigit(phone[2]) || !isdigit(phone[3]) || !isdigit(phone[4]) || !isdigit(phone[5]) || !isdigit(phone[6]) || !isdigit(phone[7]) || !isdigit(phone[8]) || !isdigit(phone[9])) {
            printf(" El telefono debe contener solo numeros\n");
            block = 1;
        }
    } while (block);

   return ;
}
float funcCreditAm(){
    float creditAmount;
    int block;

    do{
        block = 0;
        printf(" Ingrese el monto de credito del cliente: ");
        scanf("%f", &creditAmount);

        if(creditAmount <= 0){
            printf(" El monto de credito no puede ser negativo o cero\n");
            block = 1;
        }
    }while(block);

    return creditAmount;
}
float funcDebtAm(){
    float debtAmount;
    int block;

    do{
        block = 0;
        printf(" Ingrese el monto de deuda actual del cliente: ");
        scanf("%f", &debtAmount);
        

        if(debtAmount <= 0){
            printf(" El monto de deuda no puede ser negativo o cero\n");
            block = 1;
        }
    }while(block);

   return debtAmount;
}
char funQuality(){
    char quality;
    int block;

    do{
        block = 0;
        printf(" Ingrese la calidad del cliente (A, B, C): ");
        scanf(" %c", &quality);

        if(quality != 'A' && quality != 'B' && quality != 'C'){
            printf(" La calidad debe ser A, B o C\n");
            block = 1;
        }
    } while(block);

    return quality;
}
int funcParchuses(){
    int purchases;
    int block;

    do{
        block = 0;
        printf(" Ingrese la cantidad de compras del cliente: ");
        scanf("%d", &purchases);

        if(purchases < 0){
            printf(" La cantidad de compras no puede ser negativa\n");
            block = 1;
        }
    }while(block);

    return purchases;
}
int funcPayments(){
    int payments;
    int block;

    do{
        block = 0;
        printf(" Ingrese la cantidad de pagos del cliente: ");
        scanf("%d", &payments);

        if(payments < 0){
            printf(" La cantidad de pagos no puede ser negativa\n");
            block = 1;
        }
    }while(block);

   return payments;
}
float funcLastPar(){
    float lastPurchase;
    int block;

    do{
        block = 0;
        printf(" Ingrese el precio de la ultima compra del cliente: ");
        scanf("%f", &lastPurchase);
        
        if(lastPurchase <= 0){
            printf(" La compra no puede ser negativo o cero\n");
            block = 1;
        }
    }while(block);

    return lastPurchase;
}



