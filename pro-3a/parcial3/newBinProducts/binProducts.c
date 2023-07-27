#include <stdio.h>

int mostrarMenu();
int agregar(char nombreArch[]);
void mostrarProductos(char nombreArch[]);
int aumentarPrecio(char nombreArch[], int claveB, float incremento);
int modificarPrecio(char nombreArch[], int claveB, float precioN);
int buscarProducto(char nombreArch[], int claveB);
int borradoLogico(char nombreArch[],int claveB);
int aumentarTodo(char nombreArch[], float porcentaje);

int main()
{
    char nombreArch[50]="productos.dat";
    int opc;
    int claveB;
    float precioN;
    float aumento;
    float porcentaje;
  
    do{
        opc=mostrarMenu();
        switch (opc){
            case 0:
                break;
            case 1:
                if(agregar(nombreArch)){
                    printf("Registro agregado exitosamente\n");
                }else{
                    printf("Registro no exitoso.\n");
                }
                
                break;
                
            case 2:
                printf("\nIntroduce una clave: ");
                scanf("%d", &claveB);
                if (buscarProducto(nombreArch, claveB)){
                    printf("\nProducto encontrado :)\n");
                }else{
                    printf("Producto no encontrado :(\n");
                }
                break;
                
            case 3:
                printf("\n");
                mostrarProductos(nombreArch);
                printf("\n");
                break;
                
            case 4:
                printf("Clave del producto: ");
                scanf("%d",&claveB);
                printf("Cantidad de aumento: ");
                scanf("%f",&aumento);
                if (aumentarPrecio(nombreArch,claveB,aumento)){
                    printf("Precio cambiado exitosamente.\n");
                }else{
                    printf("No se encontró un artículo con esa clave");
                }
                break;
                
            case 5:
                printf("Clave del producto: ");
                scanf("%d",&claveB);
                printf("Nuevo precio: ");
                scanf("%f",&precioN);
                if(modificarPrecio(nombreArch,claveB,precioN)){
                    printf("Precio cambiado exitosamente.\n");
                }else{
                    printf("No se encontró un artículo con esa clave");
                }
                break;
                
            case 6:
                printf("Introduce la clave: ");
                scanf("%d",&claveB);
                
                if(borradoLogico(nombreArch,claveB)){
                    printf("Registro eliminado exitosamente.\n");
                }else{
                    printf("No se encontró un artículo con esa clave.");
                }
                break;
            
            case 7:
                printf("Introduce el porcentaje de aumento: ");
                scanf("%f",&porcentaje);
                aumentarTodo(nombreArch,porcentaje);
                break;
                
            default:
                printf("Introduzca un valor válido: ");
                break;
        }
    }while(opc!=0);
}


int mostrarMenu(){
    int opc;
    printf("\n1:Agregar un producto.\n");
    printf("2:Buscar la clave del producto.\n");
    printf("3:Mostrar todos los productos.\n");
    printf("4:Aumentar el precio.\n");
    printf("5:Cambiar el precio de un producto.\n");
    printf("6:Borrar logicamente\n");
    printf("7:Aumentar precio a todos los productos.\n");
    printf("0:Salir.\n");
    printf("Introduce una opción: ");
    scanf("%d",&opc);
    return opc;
}


int agregar(char nombreArch[]){
    int clave, cantidad,estado;
    char descripcion[50];
    float precio;
    FILE *apArch;
    
    printf("\nIntroduce la clave: ");
    scanf("%d%*c",&clave);
    
    if(buscarProducto(nombreArch, clave)){
        printf("\nLa clave ya existe.\n");
        return 0;
    }
    
    apArch=fopen(nombreArch, "ab"); //b es para un archivo binario_a es escribir algo al final
    
    if(apArch==NULL){
        printf("Archivo dañado");
        return 0;
    }
    
    printf("\nDescripción: ");
    scanf("%[^\n]", descripcion);
    
    printf("\nCantidad: ");
    scanf("%d",&cantidad);
    
    printf("\nPrecio: ");
    scanf("%f",&precio);
    
    estado=1;
    
    fwrite(&clave, sizeof(int), 1, apArch);
    fwrite(descripcion, sizeof(descripcion), 1, apArch);
    fwrite(&cantidad, sizeof(int), 1, apArch);
    fwrite(&precio, sizeof(float), 1, apArch);
    fwrite(&estado, sizeof(int), 1, apArch);
    
    fclose(apArch);
    
    return 1;
}

void mostrarProductos(char nombreArch[]){
    int clave, cantidad, estado=1;
    char descripcion[50];
    float precio;
    FILE *apArch;
    
    apArch=fopen(nombreArch, "rb");
    
    if(apArch==NULL){
        printf("Error el archivo no existe.");
        return;
    }
    
    fread(&clave,sizeof(int), 1, apArch);
    while(!feof(apArch)){
        fread(descripcion, sizeof(descripcion), 1, apArch);
        fread(&cantidad, sizeof(int), 1, apArch);
        fread(&precio, sizeof(float), 1, apArch);
        fread(&estado,sizeof(int),1,apArch);
        if(estado){
            printf("%d,%s,%d,%.2f\n",clave,descripcion,cantidad,precio);  
        }
        fread(&clave,sizeof(int), 1, apArch);
    }
    fclose(apArch);
}


int buscarProducto(char nombreArch[], int claveB){
    int clave, cantidad,estado=1;
    char descripcion[50];
    float precio;
    FILE *apArch;
    int tamReg=66;
    
    apArch=fopen(nombreArch, "rb");
    
    if(apArch==NULL){
        printf("Error; el archivo no existe.");
        return 0;
    }
    
    fread(&clave, sizeof(int), 1, apArch);
    while(!feof(apArch)){
        if(clave==claveB){
            fread(descripcion, sizeof(descripcion), 1, apArch);
            fread(&cantidad, sizeof(int), 1, apArch);
            fread(&precio, sizeof(float), 1, apArch);
            fread(&estado,sizeof(int), 1, apArch);
            if(estado){
                printf("%d,%s,%d,%.2f",clave,descripcion,cantidad,precio);
            }else{
                printf("Registro borrado lógicamente.\n");
            }
            fclose(apArch);
            return 1;
        }
        fseek(apArch, tamReg-4, 1);
        fread(&clave, sizeof(int), 1, apArch);
    }
    fclose(apArch);
    return 0;
}


int aumentarPrecio(char nombreArch[], int claveB, float incremento){
    int clave,estado=1;
    float precio;
    FILE *apArch;
    int tamReg=66;
    
    apArch=fopen(nombreArch, "r+b"); // r+ lee y despues escribe 
    
    if(apArch==NULL){
        printf("Error; el archivo no existe.");
        return 0;
    }
    
    fread(&clave, sizeof(int), 1, apArch);
    while(!feof(apArch)){
        if(clave==claveB){
            fseek(apArch, 54, 1);//fseek sirve para avanzar a traves del archvivo
            fread(&precio, sizeof(float), 1, apArch);
            fread(&estado, sizeof(int), 1, apArch);
            if(estado==1){
                precio+=incremento;
                fseek(apArch, ftell(apArch)-8, 0); //ftell da la posicion en la que se esta
                fwrite(&precio, sizeof(float), 1, apArch);
                fclose(apArch);
                return 1; 
            }else{
                fclose(apArch);
                return 0;
            }
        }
        fseek(apArch, 62, SEEK_CUR);
        fread(&clave, sizeof(int), 1, apArch);
    }
    fclose(apArch);
    return 0;
}


int modificarPrecio(char nombreArch[], int claveB, float precioN){
    int clave,estado=1;
    float precio;
    FILE *apArch;
    int tamReg=66;
    
    apArch=fopen(nombreArch, "r+b"); // r+ lee y despues escribe 
    
    if(apArch==NULL){
        printf("Error; el archivo no existe.");
        return 0;
    }
    
    fread(&clave, sizeof(int), 1, apArch);
    while(!feof(apArch)){
        if(clave==claveB){
            fseek(apArch, 54, 1);
            fread(&precio, sizeof(float), 1, apArch);
            fread(&estado, sizeof(int), 1, apArch);
            if(estado==1){
                precio=precioN;
                fseek(apArch, ftell(apArch)-8, 0); //ftell da la posicion en la que se esta
                fwrite(&precio, sizeof(float), 1, apArch);
                fclose(apArch);
                return 1;
            }else{
                fclose(apArch);
                return 0;
            }
        }
        fseek(apArch, 62, SEEK_CUR);
        fread(&clave, sizeof(int), 1, apArch);
    }
    fclose(apArch);
    return 0;
}


int borradoLogico(char nombreArch[], int claveB){
    int clave, estado, tamReg=66;
    FILE *apArch;
    
    apArch=fopen(nombreArch,"r+b");
    if(apArch==NULL){
        printf("El archivo no existe.\n");
        return 0;
    }
    
    fread(&clave,sizeof(int),1,apArch);
    while(!feof(apArch)){
        if(clave==claveB){
            fseek(apArch,tamReg-8,SEEK_CUR);
            fread(&estado,sizeof(int),1,apArch);
            if(estado){   //if(estado==1)
                estado=0;
                fseek(apArch,ftell(apArch)-4,SEEK_SET);
                fwrite(&estado, sizeof(int), 1, apArch);
                fclose (apArch);
                return 1;
            }else{
                printf("El registro está borrado\n");
                fclose(apArch);
                return 0;
            }
        }
        
        fseek(apArch,62,SEEK_CUR);
        fread(&clave, sizeof(int), 1, apArch);
    }
    
    fclose(apArch);
    return 0;
}


int aumentarTodo(char nombreArch[], float porcentaje){
    int estado=1,tamReg=66;
    float precio;
    FILE *apArch;
    
    apArch=fopen(nombreArch,"r+b");
    if(apArch==NULL){
        printf("Archivo no existente\n");
        return 0;
    }
    
    fseek(apArch,tamReg-4,1);
    fread(&estado,sizeof(int),1,apArch); 
    
    while(!feof(apArch)){
        if(estado==1){
            fseek(apArch,ftell(apArch)-8,SEEK_SET);
            fread(&precio,sizeof(float),1,apArch);
            precio+=precio*porcentaje;
            fseek(apArch,ftell(apArch)-4,SEEK_SET);
            fwrite(&precio,sizeof(float),1,apArch);
            fseek(apArch,66,1);
        }else{
            fseek(apArch,62,1);
        }
        fread(&estado,sizeof(int),1,apArch);
    }
    fclose(apArch);

    /* remove(nombreArch); //elimina el archivo
    rename("temp.dat",nombreArch); //cambia el nombre del archivo */

    return 1;
}