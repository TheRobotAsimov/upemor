#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mostrarMenu();
void agregar(char nombreArch[], char nombres[25], char apeP[15], char apeM[15], int *dia, int *mes, int *año, char curp[19],int *idPa, char direccion[90], char tel[11], char *sexo, int *consultorio,int *citas,int *estado);
int agregar2(char nombreArch[], char nombres[25], char apeP[15], char apeM[15], int dia, int mes, int año, char curp[19],int idPa, char direccion[90], char tel[11], char sexo, int consultorio,int citas,int estado);
void ordenar(char nombreArch[]);
void mostrarPacAct(char nombreArch[],char nombreArchCi[]);
void mostrarPacEli(char nombreArch[]);
int busquedaParcial(char nombreArch[],char nombre[]);
void busquedaP(char nombreArch[]);
void busIdPa(char nombreArch []);
int buscarPorIdPa(char nombreArch[],int idPaBuscar);
int eliminar(char nombreArch[],char nombreArchCi[], int clave, int estado);
int modificarDirec(char nombreArch[],int clave,char dire[]);
int modificarTel(char nombreArch[], int clave, char tel[]);
int modificarCon(char nombreArch[], int clave, int consult);
//validaciones
int validaTel(char telefono[]);
int validarFe(int dia, int mes, int año);
int validarIdPa(int idPa);
int valCurp(char curp[],int dia, int mes, int año, char sexo);
//citas
void agregarC(char nombreArchCi[],int *idPa,int *diaC, int *mesC, int *añoC,float *peso,float *pre,int *tem,float *estatura, char *turno,int *citas,int *estado2);
int agregarC2(char nombreArchCi[],int idPa,int diaC, int mesC, int añoC,float peso,float pre,int tem,float estatura, char turno,int citas,int estado2);

void buscarFecha2(char nombreArchCi[],int d,int m,int a);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    char nombreArch[30] = "pacientes.dat";
    char nombreArchCi[30] = "citas.dat";
    int opc,opc2;
    char nombres[25], apeP[15], apeM[15], direccion[90], tel[11], sexo,turno,curp[19];
    char direc[90], nuevoTel[11];
    int dia, mes, año,d, m, a,diaC, mesC, añoC, consultorio, estado,citas,tem,estado2, nuevoCons;
    int idPa, clave;
    float peso,estatura,pre;
    do{
        opc = mostrarMenu();
        switch (opc)
        {
        case 1:;
            if (agregar(nombreArch, nombres, apeP, apeM, &dia, &mes, &año, curp, &idPa, direccion, tel, &sexo, &consultorio,&citas,&estado),
                agregar2(nombreArch, nombres, apeP, apeM, dia, mes, año, curp, idPa, direccion, tel, sexo, consultorio,citas,estado)){
                printf("\t\t\n\033[1;32mRegistro exitoso.\033[0m\n");
                ordenar(nombreArch);
            }else{
                printf("\t\t\n\033[1;31mRegistro no exitoso.\033[0m\n");
            }
            break;

        case 2:
           if (agregarC(nombreArchCi,&idPa,&diaC, &mesC, &añoC,&peso,&pre,&tem,&estatura,&turno,&citas,&estado2),
               agregarC2(nombreArchCi,idPa,diaC,mesC,añoC,peso,pre,tem,estatura, turno,citas,estado2)){
                printf("\t\t\n\033[1;32mRegistro exitoso.\033[0m\n");
            }else{
                printf("\t\t\n\033[1;31mRegistro no exitoso.\033[0m\n");
            }
           break;
        case 3:
            int seguro;
            printf("Ingrese su ID de Paciente: ");
            scanf("%d", &clave);
            if(buscarPorIdPa(nombreArch,clave)){
                printf("Está seguro de eliminar? (1=SI, 2=NO)  ");
                scanf("%d", &seguro);
                if(seguro==1){
                    if(eliminar(nombreArch,nombreArchCi,clave, estado)){
                        printf("Registro eliminado de forma lógica\n");
                    }else{
                        printf("Paciente no encontrado\n");
                    }
                }else{
                    if(seguro!=1){
                        printf("De acuerdo...\n");
                    }else{
                        printf("Digite una opción válida.\n");
                    }
                    
                }
            }else{
                printf("Paciente no Registrado\n");
            }
            break;
        case 4:
            
            break;
        case 5:
                    do{
                        
                        printf("\n\t\t\033[1;35m----------------------------------\n");
                        printf ("\t\t¿Qué información desea modificar del paciente?\n");
                        printf ("\t\t1.Dirección.\n");
                        printf ("\t\t2.Teléfono.\n");
                        printf ("\t\t3.No. de consultorio.\n");
                        printf("\t\t0.Menu Principal\n");
                         printf("\n\t\t----------------------------------\033[0m\n");
                        printf ("\t\tIngrese una opción:");
                        scanf ("%d",&opc2);
                        switch(opc2){
                            case 1:
                            //aqui va el do para validar el NSS
                                printf("Ingrese su ID de Paciente: ");
                                scanf("%d%*c", &clave);
                                if(buscarPorIdPa(nombreArch,clave)){
                                    printf("Está seguro de modificar? (1=SI, 2=NO)  ");
                                    scanf("%d%*c", &seguro);
                                    if(seguro==1){
                                         printf("Ingrese la nueva Dirección : ");
                                         scanf("%[^\n]%*c",direc);
                                        if(modificarDirec(nombreArch,clave,direc)){
                                            printf("\t\t\n\033[0;32m La dirección ha cambiado. \033[0m\n");
                                        }else{
                                           printf("\t\t\n\033[1;31m No se pudo cambiar. \033[0m\n");
                                        }
                                    }else{
                                        if(seguro!=1){
                                            printf("De acuerdo...\n");
                                        }else{
                                            printf("Digite una opción válida.\n");
                                        }
                                        
                                    }
                                }else{
                                    printf("Paciente no Registrado\n");
                                }
                            break;
                            case 2:
                                printf("Ingrese su ID de Paciente: ");
                                scanf("%d%*c", &clave);
                            
                                if(buscarPorIdPa(nombreArch,clave)){
                                    printf("Está seguro de eliminar? (1=SI, 2=NO)  ");
                                    scanf("%d%*c", &seguro);
                                    if(seguro==1){
                                        printf("Ingrese el nuevo teléfono : ");
                                    scanf("%[^\n]%*c",nuevoTel);
                                        if (modificarTel(nombreArch,clave,nuevoTel)){
                                           printf("\t\t\n\033[0;32m El teléfono ha cambiado. \033[0m\n");
                                        }else{
                                           printf("\t\t\n\033[1;31m No se pudo cambiar. \033[0m\n");
                                        }
                                    }else{
                                        if(seguro!=1){
                                            printf("De acuerdo...\n");
                                        }else{
                                            printf("Digite una opción válida.\n");
                                        }
                                        
                                    }
                                }else{
                                    printf("Paciente no Registrado\n");
                                }
                                
                            break;
                            case 3:
                            printf("Ingrese su ID de Paciente: ");
                            scanf("%d%*c", &clave);
                            if(buscarPorIdPa(nombreArch,clave)){
                                    printf("Está seguro de eliminar? (1=SI, 2=NO)  ");
                                    scanf("%d%*c", &seguro);
                                    if(seguro==1){
                                        printf("Ingrese el nuevo no. de consultorio : ");
                                        scanf("%d",&nuevoCons);
                                        if (modificarCon(nombreArch,clave,nuevoCons)){
                                           printf("\t\t\n\033[0;32m El consultorio ha cambiado. \033[0m\n");
                                        }else{
                                           printf("\t\t\n\033[1;31m No se pudo cambiar. \033[0m\n");
                                        }
                                           
                                    }else{
                                        if(seguro!=1){
                                            printf("De acuerdo...\n");
                                        }else{
                                            printf("Digite una opción válida.\n");
                                        }
                                        
                                    }
                                }else{
                                    printf("Paciente no Registrado\n");
                                }
                            break;
                            case 0:
                                opc = mostrarMenu();
                                break;
                            default:
                                printf("Opción no válida.\n");
                                break;
                        }
                    }while(opc2!=0);
                break;
        case 6:
                 printf("Ingrese la fecha ...\n");
                    printf("\nDía (AA): ");
                    scanf("%d%*c",&d);
                    printf("\nMes (MM): ");
                    scanf("%d%*c",&m);
                    printf("\nAño (AA): ");
                    scanf("%d%*c",&a);
                
                buscarFecha2(nombreArchCi,d,m,a);
        
             break;
        case 7:
            busquedaP(nombreArch);
            break;
        case 8:
            mostrarPacAct(nombreArch,nombreArchCi);
        break;
        case 9:
            mostrarPacEli(nombreArch);
        break;

        case 0:
            printf("Saliendo del programa...\n");
        break;

        default:
            printf("Opción no válida\n");
            break;
        }

    } while (opc != 0);

    return 0;
}
int mostrarMenu(){
    int opc;
    printf("\n\t\t\033[1;34m----------------------------------\n");
    printf("\n\t\t\t NUTRIBALANCE CLÍNICA \n");
    printf("\n\t\t----------------------------------");
    printf("\n\t\t\t Menú de opciones. ");
    printf("\n\t\t----------------------------------\n");
    printf("\t\t1. Agregar un nuevo paciente. \n");
    printf("\t\t2. Agendar cita.\n");
    printf("\t\t3. Eliminar paciente.\n");
    printf("\t\t4. Eliminar una cita.\n");
    printf("\t\t5. Modificar información de un paciente.\n");
    printf("\t\t6. Consultar paciente dada su cita.\n");
    printf("\t\t7. Consultar paciente.\n");
    printf("\t\t8. Ver pacientes activos.\n");
    printf("\t\t9. Ver pacientes eliminados.\n");
    printf("\t\t0.SALIR\n");
    printf("\n\t\t----------------------------------\033[0m\n");
    printf("\t\tIngrese por favor una opción: ");
    scanf("%d%*c",&opc);
    
    return opc;
}

void agregar(char nombreArch[], char nombres[25], char apeP[15], char apeM[15], int *dia, int *mes, int *año, char curp[19],int *idPa, char direccion[90], char tel[11], char *sexo, int *consultorio,int *citas,int *estado){
    FILE *apArch;
    int apoyo,res;
    printf("\nPara agregar un nuevo paciente ingrese...\n ");
    //nombre
    printf("\nNombre/s: ");
    scanf("%[^\n]%*c",nombres);
    printf("\nApellido Paterno:");
    scanf("%[^\n]%*c",apeP);
    printf("\nApellido Materno:");
    scanf("%[^\n]%*c",apeM);
    //fecha
    printf("\nFECHA DE NACIMIENTO:");
    do{
        printf("\nDía (AA): ");
        scanf("%d%*c",dia);
        printf("\nMes (MM): ");
        scanf("%d%*c",mes);
        printf("\nAño (AA): ");
        scanf("%d%*c",año);
        if(validarFe(*dia,*mes,*año)){
            
        }else{
            printf("\t\t\n\033[1;31m La fecha ingresada no es válida.\033[0m\n");
            printf("\t\t\n\033[1;31m INTENTE DE NUEVO.\033[0m\n");
        }
    }while(validarFe(*dia,*mes,*año)==0);
    //curp
    
    
    do{
        printf("\nID del Paciente: ");
        scanf("%d%*c",idPa);
        apoyo=buscarPorIdPa(nombreArch,*idPa);
        
         if(validarIdPa(*idPa)){
            if(apoyo==1){
                printf("\t\t\n\033[1;31m El Paciente ya existe\033[0m\n");
            }else{
                printf("\nDirección: ");
                scanf("%[^\n]%*c",direccion);
                do{
                    printf("\nTeléfono: ");
                    scanf("%[^\n]%*c",tel);
                    
                }while(validaTel(tel)!=1);
                printf("\nSexo (M o F): ");
                scanf(" %c", sexo);  
                printf("\nNúmero de consultorio: ");
                scanf("%d%*c", consultorio);
                
            }
            *citas=0;
                
            *estado=1;
        }else{
            printf("\t\t\n\033[1;31m El NSS ingresado no es válido.\033[0m\n");
            printf("\t\t\n\033[1;31m INTENTE DE NUEVO.\033[0m\n");
            
        }
    }while(validarIdPa(*idPa)!=1||apoyo);
    do{
        
         printf("\nCURP: ");
        scanf("%[^\n]%*c",curp);
        res=valCurp(curp ,*dia,*mes,*año,*sexo);
        if(res==1){
            
        }else{
            printf("\t\t\n\033[1;31m INTENTE DE NUEVO.\033[0m\n");
        }
       
    }while(res!=1);
}

int agregar2(char nombreArch[], char nombres[25], char apeP[15], char apeM[15], int dia, int mes, int año, char curp[19],int idPa, char direccion[90], char tel[11], char sexo, int consultorio,int citas, int estado ){
    FILE *apArch;
    apArch=fopen(nombreArch,"ab");
    if(apArch==NULL){
        printf("Error, el archivo no existe.\n");
        return 0;
    }
        fwrite(nombres,25,1,apArch);
        fwrite(apeP,15,1,apArch);
        fwrite(apeM,15,1,apArch);
        fwrite(&dia,sizeof(int),1,apArch);
        fwrite(&mes,sizeof(int),1,apArch);
        fwrite(&año,sizeof(int),1,apArch);
        fwrite(curp,19,1,apArch);
        fwrite(&idPa,sizeof(int),1,apArch);
        fwrite(direccion,90,1,apArch);
        fwrite(tel,11,1,apArch);
        fwrite(&sexo, sizeof(char), 1, apArch);
        fwrite(&consultorio,sizeof(int),1,apArch);
        fwrite(&citas,sizeof(int),1,apArch);
        fwrite(&estado,sizeof(int),1,apArch);
        fclose(apArch);
        return 1;
}

int validaTel(char tel[]){
    int i;
    if(strlen(tel)!= 10){
        return 0;
    }
    for(i =0; i < strlen(tel); i++){
        if(!isdigit(tel[i])){
        return 0;
        }
    }
    return 1;

}
int validarFe(int dia, int mes, int año) {
    if (mes < 1 || mes > 12 || dia < 1) {
        return 0; // Mes o día inválido
    }

    // Verificar si el año es bisiesto
    int añoBisiesto = (año % 4 == 0 && año % 100 != 0) || año % 400 == 0;

    int diasPorMes;
    switch (mes) {
        case 2: // Febrero
        if (añoBisiesto){
            diasPorMes=29;
        }else{
            diasPorMes=28;
        }
            break;
        //meses que tienen 30 d
        case 4: // Abril
        case 6: // Junio
        case 9: // Septiembre
        case 11: // Noviembre
            diasPorMes = 30;
            break;
        default: // Enero, Marzo, Mayo, Julio, Agosto, Octubre, Diciembre
            diasPorMes = 31;
            break;
    }

    if (dia > diasPorMes) {
        return 0;
    }

    return 1;
}
int validarIdPa(int idPa) {
    int aux = 0;
    while (idPa != 0) {
        idPa /= 10;
        ++aux;
    }
    return (aux == 4); 
}
void agregarC(char nombreArchCi[],int *idPa,int *diaC, int *mesC, int *añoC,float *peso,float *pre,int *tem,float *estatura, char *turno,int *citas,int *estado2){
     FILE *apArch2;
     
    printf("\nPara agregar una CITA a un paciente ingrese...\n ");
    
     do{
        printf("Ingrese su ID de Paciente: ");
        scanf("%d%*c",idPa);
        if(validarIdPa(*idPa)){
            
        }else{
            printf("\t\t\n\033[1;31m El NSS ingresado no es válido.\033[0m\n");
            printf("\t\t\n\033[1;31m INTENTE DE NUEVO.\033[0m\n");
        }
    }while(validarIdPa(*idPa)!=1);
    //fecha
    printf("\nFECHA DE CITA:");
    
        printf("\nDía (AA): ");
        scanf("%d%*c",diaC);
        printf("\nMes (MM): ");
        scanf("%d%*c",mesC);
        printf("\nAño (AAAA): ");
        scanf("%d%*c",añoC);
       
    //curp
   
    printf("\nPeso: ");
    scanf("%f%*c", peso);
    printf("\nPresión arterial: ");
    scanf("%f%*c", pre);
    printf("\nTemperatura: ");
    scanf("%d%*c",tem);
     printf("\nEstatura: ");
    scanf("%f%*c", estatura);
     printf("\nTurno (M o V): ");
    scanf(" %c", turno);  

    *citas= *citas+1;
    *estado2=1;
}
int agregarC2(char nombreArchCi[],int idPa,int diaC, int mesC, int añoC,float peso,float pre,int tem,float estatura, char turno,int citas,int estado2){
    FILE *apArch2;
    apArch2=fopen(nombreArchCi,"ab");
    if(apArch2==NULL){
        printf("Error, el archivo no existe.\n");
        return 0;
    }
        fwrite(&idPa,sizeof(int),1,apArch2);
        fwrite(&diaC,sizeof(int),1,apArch2);
        fwrite(&mesC,sizeof(int),1,apArch2);
        fwrite(&añoC,sizeof(int),1,apArch2);
        fwrite(&peso,sizeof(float),1,apArch2);
        fwrite(&pre,sizeof(float),1,apArch2);
        fwrite(&tem,sizeof(int),1,apArch2);
        fwrite(&estatura,sizeof(float),1,apArch2);
        fwrite(&turno,sizeof(char),1,apArch2);
        fwrite(&citas,sizeof(int),1,apArch2);
        fwrite(&estado2,sizeof(int),1,apArch2);
        fclose(apArch2);
        return 1;
}
void ordenar(char nombreArch[]){
    FILE *apArch;
    char nombres1[25], apeP1[15], apeM1[15], direccion1[90], tel1[11], sexo1,curp1[19];
    int dia1, mes1, año1, consultorio1, estado1,citas1;
    char nombres2[25], apeP2[15], apeM2[15], direccion2[90], tel2[11], sexo2,curp2[19];
    int dia2, mes2, año2, consultorio2, estado2,citas2,numReg;
    int idPa1,idPa2;
    apArch=fopen(nombreArch, "r+b");
    long int tamReg=204, i,j;
     if(apArch==NULL){
        return; 
     }
    fseek(apArch,0,2);
    numReg=ftell(apArch)/tamReg;
    for(i=0;i<numReg-1;i++){
        for(j=0;j<numReg-1;j++){
            fseek(apArch,tamReg*j,0);
            
            fread(nombres1,14,1,apArch);

            fseek(apArch,tamReg*(j+1),0);
           
            fread(nombres2,80,1,apArch);
            
            if(strcmp(nombres1,nombres2)>0){
                fseek(apArch,tamReg*j,0);
                
                fread(nombres1,25,1,apArch);
                fread(apeP1,15,1,apArch);
                fread(apeM1,15,1,apArch);
                fread(&dia1,sizeof(int),1,apArch);
                fread(&mes1,sizeof(int),1,apArch);
                fread(&año1,sizeof(int),1,apArch);
                fread(curp1,19,1,apArch);
                fread(&idPa1,sizeof(int),1,apArch);
                fread(direccion1,90,1,apArch);
                fread(tel1,11,1,apArch);
                fread(&sexo1,sizeof(char),1,apArch);
                fread(&consultorio1,sizeof(int),1,apArch);
                fread(&citas1,sizeof(int),1,apArch);
                fread(&estado1,sizeof(int),1,apArch);
                
                fread(nombres2,25,1,apArch);
                fread(apeP2,15,1,apArch);
                fread(apeM2,15,1,apArch);
                fread(&dia2,sizeof(int),1,apArch);
                fread(&mes2,sizeof(int),1,apArch);
                fread(&año2,sizeof(int),1,apArch);
                fread(curp2,19,1,apArch);
                fread(&idPa2,sizeof(int),1,apArch);
                fread(direccion2,90,1,apArch);
                fread(tel2,11,1,apArch);
                fread(&sexo2,sizeof(char),1,apArch);
                fread(&consultorio2,sizeof(int),1,apArch);
                fread(&citas2,sizeof(int),1,apArch);
                fread(&estado2,sizeof(int),1,apArch);
                 
                fseek(apArch,tamReg*j,0);
                
                fwrite(nombres2,25,1,apArch);
                fwrite(apeP2,15,1,apArch);
                fwrite(apeM2,15,1,apArch);
                fwrite(&dia2,sizeof(int),1,apArch);
                fwrite(&mes2,sizeof(int),1,apArch);
                fwrite(&año2,sizeof(int),1,apArch);
                fwrite(curp2,19,1,apArch);
                fwrite(&idPa2,sizeof(int),1,apArch);
                fwrite(direccion2,90,1,apArch);
                fwrite(tel2,11,1,apArch);
                fwrite(&sexo2, sizeof(char), 1, apArch);  
                fwrite(&consultorio2,sizeof(int),1,apArch);
                fwrite(&citas2,sizeof(int),1,apArch);
                fwrite(&estado2,sizeof(int),1,apArch);
                
                fwrite(nombres1,25,1,apArch);
                fwrite(apeP1,15,1,apArch);
                fwrite(apeM1,15,1,apArch);
                fwrite(&dia1,sizeof(int),1,apArch);
                fwrite(&mes1,sizeof(int),1,apArch);
                fwrite(&año1,sizeof(int),1,apArch);
                fwrite(curp1,19,1,apArch);
                fwrite(&idPa1,sizeof(int),1,apArch);
                fwrite(direccion1,90,1,apArch);
                fwrite(tel1,11,1,apArch);
                fwrite(&sexo1, sizeof(char), 1, apArch);  
                fwrite(&consultorio1,sizeof(int),1,apArch);
                fwrite(&citas1,sizeof(int),1,apArch);
                fwrite(&estado1,sizeof(int),1,apArch);
            }
            
        }
    }
    fclose(apArch);
} 

void mostrarPacAct(char nombreArch[],char nombreArchCi[]){
    char nombres [25], apeP[15],apeM[15], curp [19], direccion[90], tel[11];
    char sexo,turno;
    int dia, mes, año,diaC, mesC, añoC, consultorio,estado,estado2, citas,tem;
    int idPa;
    float peso,estatura,pre;
    
    FILE *apArch;
    FILE *apArch2;
    
    apArch=fopen(nombreArch,"rb");
    if(apArch==NULL){
        printf("Error, el archivo no existe\n");
        return ;
    }
    fread(nombres,25,1,apArch);
    while(!feof(apArch)){
        fread(apeP,15,1,apArch);
        fread(apeM,15,1,apArch);
        fread(&dia,sizeof(int),1,apArch);
        fread(&mes,sizeof(int),1,apArch);
        fread(&año,sizeof(int),1,apArch);
        fread(curp,19,1,apArch);
        fread(&idPa,sizeof(int),1,apArch);
        fread(direccion,90,1,apArch);
        fread(tel,11,1,apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio,sizeof(int),1,apArch);
        fread(&citas,sizeof(int),1,apArch);
        fread(&estado,sizeof(int),1,apArch);
        if(estado){
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            printf("\n\t\033[1;34mNOMBRE/S : \033[0m%s", nombres);
            printf("\n\t\033[1;34mFAPELLIDO P : \033[0m%s", apeP);
            printf("\n\t\033[1;34mAPELLIDO M : \033[0m%s", apeM);
            printf("\n\t\033[1;34m-FECHA DE NACIMIENTO- \033[0m");
            printf("\n\t\033[1;34mDía: \033[0m%d", dia);
            printf("\n\t\033[1;34mMes: \033[0m%d", mes);
            printf("\n\t\033[1;34mAño: \033[0m%d", año);
            printf("\n\t\033[1;34mCURP : \033[0m%s", curp);
            printf("\n\t\033[1;34mID Paciente : \033[0m%d", idPa);
            printf("\n\t\033[1;34mDIRECCIÓN : \033[0m%s", direccion);
            printf("\n\t\033[1;34mTELÉFONO : \033[0m%s", tel);
            printf("\n\t\033[1;34mSEXO : \033[0m%c", sexo);
            printf("\n\t\033[1;34mNO. CONSULTORIO : \033[0m%d", consultorio);
            printf("\n\t\033[1;34mNO. CITAS : \033[0m%d", citas);
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            
        }
        fread(nombres,sizeof(nombres),1,apArch);
    }
    fclose(apArch);
    
    
    apArch2=fopen(nombreArchCi,"rb");
    if(apArch2==NULL){
        printf("Error, el archivo no existe\n");
        return ;
    }
    fread(&idPa,sizeof(int),1,apArch2);
    while(!feof(apArch2)){
        fread(&diaC,sizeof(int),1,apArch2);
        fread(&mesC,sizeof(int),1,apArch2);
        fread(&añoC,sizeof(int),1,apArch2);
        fread(&peso,sizeof(float),1,apArch2);
        fread(&pre,sizeof(float),1,apArch2);
        fread(&tem,sizeof(int),1,apArch2);
        fread(&estatura,sizeof(float),1,apArch2);
        fread(&turno,sizeof(char),1,apArch2);
        fseek(apArch2,sizeof(int),SEEK_CUR);
        fread(&estado2,sizeof(int),1,apArch2);
        
        
        if(estado2){
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            printf("\n\t\033[1;34mID Paciente : \033[0m%d",idPa);
            printf("\n\t\033[1;34m-FECHA DE CITA- \033[0m");
            printf("\n\t\033[1;34mDía: \033[0m%d",diaC);
            printf("\n\t\033[1;34mMes: \033[0m%d",mesC);
            printf("\n\t\033[1;34mAño: \033[0m%d",añoC);
            printf("\n\t\033[1;34mPeso : \033[0m%.1f",peso);
            printf("\n\t\033[1;34mPresión arterial : \033[0m%.1f",pre);
            printf("\n\t\033[1;34mTemperatura : \033[0m%d",tem);
            printf("\n\t\033[1;34mEstatuta : \033[0m%.2f",estatura);
            printf("\n\t\033[1;34mTurno : \033[0m%c",turno);
            printf("\n\t\033[1;34mNO. CITAS : \033[0m%d",citas);
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            
        }
        fread(&idPa,sizeof(int),1,apArch2);
    }
    fclose(apArch2);
    
}
void mostrarPacEli(char nombreArch[]){
    char nombres [25], apeP[15],apeM[15], curp [19], direccion[90], tel[11];
    char sexo;
    int dia, mes, año, consultorio,estado, citas;
    int idPa;
    FILE *apArch;
    
    apArch=fopen(nombreArch,"rb");
    if(apArch==NULL){
        printf("Error, el archivo no existe\n");
        return ;
    }
    fread(nombres,25,1,apArch);
    while(!feof(apArch)){
        fread(apeP,15,1,apArch);
        fread(apeM,15,1,apArch);
        fread(&dia,sizeof(int),1,apArch);
        fread(&mes,sizeof(int),1,apArch);
        fread(&año,sizeof(int),1,apArch);
        fread(curp,19,1,apArch);
        fread(&idPa,sizeof(int),1,apArch);
        fread(direccion,90,1,apArch);
        fread(tel,11,1,apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio,sizeof(int),1,apArch);
        fread(&citas,sizeof(int),1,apArch);
        fread(&estado,sizeof(int),1,apArch);
        if(estado==0){
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            printf("\n\t\033[1;34mNOMBRE/S : \033[0m%s", nombres);
            printf("\n\t\033[1;34mFAPELLIDO P : \033[0m%s", apeP);
            printf("\n\t\033[1;34mAPELLIDO M : \033[0m%s", apeM);
            printf("\n\t\033[1;34m-FECHA DE NACIMIENTO- \033[0m");
            printf("\n\t\033[1;34mDía: \033[0m%d", dia);
            printf("\n\t\033[1;34mMes: \033[0m%d", mes);
            printf("\n\t\033[1;34mAño: \033[0m%d", año);
            printf("\n\t\033[1;34mCURP : \033[0m%s", curp);
            printf("\n\t\033[1;34mID Paciente : \033[0m%d", idPa);
            printf("\n\t\033[1;34mDIRECCIÓN : \033[0m%s", direccion);
            printf("\n\t\033[1;34mTELÉFONO : \033[0m%s", tel);
            printf("\n\t\033[1;34mSEXO : \033[0m%c", sexo);
            printf("\n\t\033[1;34mNO. CONSULTORIO : \033[0m%d", consultorio);
            printf("\n\t\033[1;34mNO. CITAS : \033[0m%d", citas);
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            
        }
        fread(nombres,sizeof(nombres),1,apArch);
    }
    fclose(apArch);
    
}
void busquedaP(char nombreArch[]) {
    char nombre[25];
    
    printf("Ingrese el numero de NOMBRE a buscar: ");
     scanf("%[^\n]%*c",nombre);
     if(busquedaParcial(nombreArch,nombre)){
            printf("\t\t\n\033[1;31m Paciente Encontrado.\033[0m\n");
        }else{
            printf("\t\t\n\033[1;31m Paciente no Encontrado. \033[0m\n");
        }
}
int busquedaParcial(char nombreArch[],char nombre[]){
    char nombres [25], apeP[15],apeM[15], curp [19], direccion[90], tel[11];
    char sexo;
    int dia, mes, año, consultorio,estado, citas,tamReg=204;
    int idPa;
    FILE *apArch;
    apArch=fopen(nombreArch,"rb");
    if(apArch==NULL){
        printf("\t\t\n\033[1;31mEl archivo no existe \033[0m\n");
        return 0;
    }
    fread(nombres,25,1,apArch);
    while(!feof(apArch)){
        if(strstr(nombres,nombre)!=NULL){
            fread(apeP,15,1,apArch);
            fread(apeM,15,1,apArch);
            fread(&dia,sizeof(int),1,apArch);
            fread(&mes,sizeof(int),1,apArch);
            fread(&año,sizeof(int),1,apArch);
            fread(curp,19,1,apArch);
            fread(&idPa,sizeof(int),1,apArch);
            fread(direccion,90,1,apArch);
            fread(tel,11,1,apArch);
            fread(&sexo, sizeof(char), 1, apArch);
            fread(&consultorio,sizeof(int),1,apArch);
            fread(&citas,sizeof(int),1,apArch);
            fread(&estado,sizeof(int),1,apArch);
            if(estado){
                printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
                printf("\n\t\033[1;34mNOMBRE/S : \033[0m%s", nombres);
                printf("\n\t\033[1;34mFAPELLIDO P : \033[0m%s", apeP);
                printf("\n\t\033[1;34mAPELLIDO M : \033[0m%s", apeM);
                printf("\n\t\033[1;34m-FECHA DE NACIMIENTO- \033[0m");
                printf("\n\t\033[1;34mDía: \033[0m%d", dia);
                printf("\n\t\033[1;34mMes: \033[0m%d", mes);
                printf("\n\t\033[1;34mAño: \033[0m%d", año);
                printf("\n\t\033[1;34mCURP : \033[0m%s", curp);
                printf("\n\t\033[1;34mID Paciente : \033[0m%d", idPa);
                printf("\n\t\033[1;34mDIRECCIÓN : \033[0m%s", direccion);
                printf("\n\t\033[1;34mTELÉFONO : \033[0m%s", tel);
                printf("\n\t\033[1;34mSEXO : \033[0m%c", sexo);
                printf("\n\t\033[1;34mNO. CONSULTORIO : \033[0m%d", consultorio);
                printf("\n\t\033[1;34mNO. CITAS : \033[0m%d", citas);
                printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            }else{
                printf("\t\t\n\033[1;31mRegistro borrado lógicamente.\033[0m\n");
            }
             fclose(apArch);
             return 1;
        }
        fseek(apArch,tamReg-25,1);
        fread(nombres,sizeof(nombres),1,apArch);
    }
    fclose(apArch);
    return 0;
    
    /*if (encontrado) {
        return 1; 
    } else {
        return 0; 
    }*/
}
void busIdPa(char nombreArch[]) {
    long idPaBuscar;
    printf("Ingrese el ID de Paciente a ELIMINAR: ");
    scanf("%ld", &idPaBuscar);
     if(buscarPorIdPa(nombreArch,idPaBuscar)){
            printf("\t\t\n\033[1;31m Paciente Encontrado.\033[0m\n");
        }else{
            printf("\t\t\n\033[1;31m Paciente no Encontrado. \033[0m\n");
    }
}
int buscarPorIdPa(char nombreArch[],int idPaBuscar) {
    FILE *apArch;
    char nombres[25], apeP[15], apeM[15], curp[19], direccion[90], tel[11];
    char sexo;
    int dia, mes, año, consultorio, estado, citas, tamReg = 204;
    int idPa;
    
    apArch = fopen(nombreArch, "rb");
    if (apArch == NULL) {
        printf("\t\t\n\033[1;31mEl archivo no existe.\033[0m\n");
        return 0;
    }

    fread(nombres, 25, 1, apArch);
    while (!feof(apArch)) {
        fread(apeP, 15, 1, apArch);
        fread(apeM, 15, 1, apArch);
        fread(&dia, sizeof(int), 1, apArch);
        fread(&mes, sizeof(int), 1, apArch);
        fread(&año, sizeof(int), 1, apArch);
        fread(curp, 19, 1, apArch);
        fread(&idPa, sizeof(int), 1, apArch);
        fread(direccion, 90, 1, apArch);
        fread(tel, 11, 1, apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio, sizeof(int), 1, apArch);
        fread(&citas, sizeof(int), 1, apArch);
        fread(&estado, sizeof(int), 1, apArch);
        if (estado && idPa == idPaBuscar) {
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            printf("\n\t\033[1;34mNOMBRE/S : \033[0m%s", nombres);
            printf("\n\t\033[1;34mFAPELLIDO P : \033[0m%s", apeP);
            printf("\n\t\033[1;34mAPELLIDO M : \033[0m%s", apeM);
            printf("\n\t\033[1;34m-FECHA DE NACIMIENTO- \033[0m");
            printf("\n\t\033[1;34mDía: \033[0m%d", dia);
            printf("\n\t\033[1;34mMes: \033[0m%d", mes);
            printf("\n\t\033[1;34mAño: \033[0m%d", año);
            printf("\n\t\033[1;34mCURP : \033[0m%s", curp);
            printf("\n\t\033[1;34mID Paciente : \033[0m%d", idPa);
            printf("\n\t\033[1;34mDIRECCIÓN : \033[0m%s", direccion);
            printf("\n\t\033[1;34mTELÉFONO : \033[0m%s", tel);
            printf("\n\t\033[1;34mSEXO : \033[0m%c", sexo);
            printf("\n\t\033[1;34mNO. CONSULTORIO : \033[0m%d", consultorio);
            printf("\n\t\033[1;34mNO. CITAS : \033[0m%d", citas);
            printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
            fclose(apArch);
            return 1;
        }
        fread(nombres, sizeof(nombres), 1, apArch);
    }
    fclose(apArch);
    return 0;
}
int eliminar(char nombreArch[],char nombreArchCi[], int clave, int estado) {
    FILE *apArch;
    FILE *apArch2;
    char nombres[25], apeP[15], apeM[15], curp[19], direccion[90], tel[11];
    char sexo;
    int dia, mes, año, consultorio, tamReg = 204;
    int idPa;
    int encontrado = 0;

    int estadoB = 0;
    
    int dia2, mes2, año2, tem, citas, estado2;
    float peso, pre, estatura;
    char turno;

    apArch = fopen(nombreArch, "r+b");
    if (apArch == NULL) {
        printf("Error, el archivo no existe.\n");
        return 0;
    }

    fread(nombres, 25, 1, apArch);
    while (!feof(apArch)) {
        fread(apeP, 15, 1, apArch);
        fread(apeM, 15, 1, apArch);
        fread(&dia2, sizeof(int), 1, apArch);
        fread(&mes2, sizeof(int), 1, apArch);
        fread(&año2, sizeof(int), 1, apArch);
        fread(curp, 19, 1, apArch);
        fread(&idPa, sizeof(int), 1, apArch);
        fread(direccion, 90, 1, apArch);
        fread(tel, 11, 1, apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio, sizeof(int), 1, apArch);
        fread(&citas, sizeof(int), 1, apArch);
        fread(&estadoB, sizeof(int), 1, apArch);

        if (idPa == clave && estadoB == 1) {
            encontrado = 1;
            estadoB = 0;  // Marcar el registro como eliminado
            fseek(apArch,-4,1);
            fwrite(&estadoB, sizeof(int), 1, apArch); 
            break;
        }
      fread(nombres, sizeof(nombres), 1, apArch);

    }    
    fclose(apArch);
            
    apArch2 = fopen(nombreArchCi, "r+b");
        
     fread(nombres, sizeof(nombres), 1, apArch);
     if (apArch2 == NULL) {
        printf("Error, el archivo de citas no existe.\n");
        return 0;
        }
        fread(&idPa,sizeof(int),1,apArch2);
        while (!feof(apArch)){
            fread(&dia,sizeof(int),1,apArch2);
            fread(&mes,sizeof(int),1,apArch2);
            fread(&año,sizeof(int),1,apArch2);
            fread(&peso,sizeof(float),1,apArch2);
            fread(&pre,sizeof(float),1,apArch2);
            fread(&tem,sizeof(int),1,apArch2);
            fread(&estatura,sizeof(float),1,apArch2);
            fread(&turno,sizeof(char),1,apArch2);
            fread(&citas,sizeof(int),1,apArch2);
            fread(&estado2,sizeof(int),1,apArch2);
            if (idPa == clave) {
                int citaEstado = 0;  // Marcar la cita como eliminada
                fseek(apArch2, -4, SEEK_CUR);
                fwrite(&citaEstado, sizeof(int), 1, apArch2);
            }
            fread(&idPa,sizeof(int),1,apArch2);
            
        }
        fclose(apArch2);
        return 1;
    

    if (encontrado) {
        return 1; 
    } else {
        return 0; 
    }
}
int modificarDirec(char nombreArch[], int clave, char dire[]) {
    FILE *apArch;
    char nombres[25], apeP[15], apeM[15], curp[19], direccion[90], tel[11];
    char sexo;
    int estado, numSS;
    int dia, mes, año, consultorio, citas;
    int idPa;
    long int tamReg =204;
    
    
    apArch = fopen(nombreArch, "r+b");
    if (apArch == NULL) {
        printf("Error, el archivo no existe.\n");
        return 0;
    }

    fread(nombres, 25, 1, apArch);
    while (!feof(apArch)) {
        fread(apeP, 15, 1, apArch);
        fread(apeM, 15, 1, apArch);
        fread(&dia, sizeof(int), 1, apArch);
        fread(&mes, sizeof(int), 1, apArch);
        fread(&año, sizeof(int), 1, apArch);
        fread(curp, 19, 1, apArch);
        fread(&idPa, sizeof(int), 1, apArch);
        fread(direccion, 90, 1, apArch);
        fread(tel, 11, 1, apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio, sizeof(int), 1, apArch);
        fread(&citas, sizeof(int), 1, apArch);
        fread(&estado, sizeof(int), 1, apArch);

        if (idPa == clave && estado == 1) {
            fseek(apArch,-114,1);
            fwrite(dire, 90, 1, apArch);
            fclose(apArch);
            return 1;
        }
         fread(nombres, 25, 1, apArch);
    }
    fclose(apArch);
    
    return 0;
}
int modificarTel(char nombreArch[], int clave, char tel[]) {
    FILE *apArch;
    char nombres[25], apeP[15], apeM[15], curp[19], direccion[90], telefono[11];
    char sexo;
    int estado, numSS;
    int dia, mes, año, consultorio, citas;
    int idPa;
    long int tamReg =204;
    
    
    apArch = fopen(nombreArch, "r+b");
    if (apArch == NULL) {
        printf("Error, el archivo no existe.\n");
        return 0;
    }

    fread(nombres, 25, 1, apArch);
    while (!feof(apArch)) {
        fread(apeP, 15, 1, apArch);
        fread(apeM, 15, 1, apArch);
        fread(&dia, sizeof(int), 1, apArch);
        fread(&mes, sizeof(int), 1, apArch);
        fread(&año, sizeof(int), 1, apArch);
        fread(curp, 19, 1, apArch);
        fread(&idPa, sizeof(int), 1, apArch);
        fread(direccion, 90, 1, apArch);
        fread(tel, 11, 1, apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio, sizeof(int), 1, apArch);
        fread(&citas, sizeof(int), 1, apArch);
        fread(&estado, sizeof(int), 1, apArch);

        if (idPa == clave && estado == 1) {
            fseek(apArch,-24,1);
            fwrite(telefono, 11, 1, apArch);
            fclose(apArch);
            return 1;
        }
         fread(nombres, 25, 1, apArch);
    }
    fclose(apArch);
    
    return 0;
}
int modificarCon(char nombreArch[], int clave, int consult){
   FILE *apArch;
   char nombres[25], apeP[15], apeM[15], curp[19], direccion[90], tel[11];
   char sexo;
   int estado, numSS;
   int dia, mes, año, consultorio, citas;
   int idPa;
   long int tamReg =204;
    
    
    apArch = fopen(nombreArch, "r+b");
    if (apArch == NULL) {
        printf("Error, el archivo no existe.\n");
        return 0;
    }

    fread(nombres, 25, 1, apArch);
    while (!feof(apArch)) {
        fread(apeP, 15, 1, apArch);
        fread(apeM, 15, 1, apArch);
        fread(&dia, sizeof(int), 1, apArch);
        fread(&mes, sizeof(int), 1, apArch);
        fread(&año, sizeof(int), 1, apArch);
        fread(curp, 19, 1, apArch);
        fread(&idPa, sizeof(int), 1, apArch);
        fread(direccion, 90, 1, apArch);
        fread(tel, 11, 1, apArch);
        fread(&sexo, sizeof(char), 1, apArch);
        fread(&consultorio, sizeof(int), 1, apArch);
        fread(&citas, sizeof(int), 1, apArch);
        fread(&estado, sizeof(int), 1, apArch);

        if (idPa == clave && estado == 1) {
            fseek(apArch,-12,1);
            fwrite(&consult, sizeof(int), 1, apArch);
            fclose(apArch);
            return 1;
        }
         fread(nombres, 25, 1, apArch);
    }
    fclose(apArch);
    
    return 0;
   
   
}
int valCurp(char curp[19] ,int dia, int mes, int año, char sexo){
     int i,dia1,mes1,ano1, num,aux,ano;
     char sexo1;
     char nombre[5], cinco[6], ultimoA[3];
     int ultimo=año%100;
     if(strlen(curp)!=18){
        printf("ERROR... El CURP debe contener 18 caracteres\n");
        return 0;
    }
    for(i=0;i<4;i++){
        if(!isalpha(curp[i])){
            printf("ERROR... Los primeros digitos deben ser caracteres\n");
            return 0;
        }
    }
    
    for(i=4;i<10;i++){
        if(!isdigit(curp[i])){
            printf("ERROR... La fecha de nacimiento no coincide\n");
            return 0;
        }
    }
    for(i=10;i<11;i++){
        if(!isalpha(curp[i])){
            printf("ERROR... El sexo no coincide\n");
            return 0;
        }
    }
    for(i=11;i<16;i++){
        if(!isalpha(curp[i])){
            printf("ERROR... Del 12 al 16 deben ser caracteres\n");
            return 0;
        }
    }
    for(i=16;i<18;i++){
        if(!isdigit(curp[i])){
            printf("ERROR... Los ultimos dos digitos deben ser numeros\n");
            return 0;
        }
    }
    sscanf(curp,"%4s%2d%2d%2d%1c%5s%2d", nombre, &ano1, &mes1,&dia1,&sexo1,cinco,&num);
    sscanf(ultimoA, "%02d", &ultimo);
    
    if(ultimo!=ano1||mes!=mes1||dia!=dia1){
          printf("Las fechas no coinciden\n");
          return  0;
    }
    return 1;
    
}

/*int busquedaFecha(char nombreArch[],char nombreArchCi[],int d,int m,int a){
    char nombres[25], apeP[15], apeM[15], direccion[90], tel[11], sexo,turno,curp[19];
    char direc[90];
    int dia, mes, año,diaC, mesC, añoC, consultorio, estado,citas,tem,estado2;
    int idPa, clave,tamReg=204;
    float peso,estatura,pre;
    
    FILE *apArch;
    FILE *apArch2;
    
    apArch=fopen(nombreArch,"rb");
    if(apArch==NULL){
        printf("Error, el archivo no existe\n");
        return 0;
    }
    
    fread(nombres,25,1,apArch);
    while(!feof(apArch)){
            fread(apeP,15,1,apArch);
            fread(apeM,15,1,apArch);
            fread(&dia,sizeof(int),1,apArch);
            fread(&mes,sizeof(int),1,apArch);
            fread(&año,sizeof(int),1,apArch);
            fread(curp,19,1,apArch);
            fread(&idPa,sizeof(int),1,apArch);
            fread(direccion,90,1,apArch);
            fread(tel,11,1,apArch);
            fread(&sexo, sizeof(char), 1, apArch);
            fread(&consultorio,sizeof(int),1,apArch);
            fread(&citas,sizeof(int),1,apArch);
            fread(&estado,sizeof(int),1,apArch);
            
        if(estado){
            printf("\nESTADO:%d ",estado);
            apArch2=fopen(nombreArchCi,"rb");
            if(apArch2==NULL){
                printf("Error, el archivo no existe\n");
                return 0;
            }
            
             fread(&idPa,sizeof(int),1,apArch2);
             while(!feof(apArch2)){
                fread(&diaC,sizeof(int),1,apArch2);
                fread(&mesC,sizeof(int),1,apArch2);
                fread(&añoC,sizeof(int),1,apArch2);
                fread(&peso,sizeof(float),1,apArch2);
                fread(&pre,sizeof(float),1,apArch2);
                fread(&tem,sizeof(int),1,apArch2);
                fread(&estatura,sizeof(float),1,apArch2);
                fread(&turno,sizeof(char),1,apArch2);
                fseek(apArch2,sizeof(int),SEEK_CUR);
                fread(&estado2,sizeof(int),1,apArch2);
                printf("\nDIA:%d ",diaC);
                printf("\nMES:%d ",mesC);
                printf("\nA:%d ",añoC);
                 printf("\nDIA:%d ",d);
                printf("\nMES:%d ",m);
                printf("\nA:%d ",a);
                
            if((diaC==d)&&(mesC==m)&&(añoC==a)){
                printf("\nDIA:%d ",diaC);
                printf("\nMES:%d ",mesC);
                printf("\nA:%d ",añoC);
                 printf("\nDIA:%d ",d);
                printf("\nMES:%d ",m);
                printf("\nA:%d ",a);
                
                if(estado2){
                    printf("\nESTADO2:%d ",estado2);
                    printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
                    printf("\n\t\033[1;34mNOMBRE/S : \033[0m%s", nombres);
                    printf("\n\t\033[1;34mFAPELLIDO P : \033[0m%s", apeP);
                    printf("\n\t\033[1;34mAPELLIDO M : \033[0m%s", apeM);
                    printf("\n\t\033[1;34m-FECHA DE NACIMIENTO- \033[0m");
                    printf("\n\t\033[1;34mDía: \033[0m%d", dia);
                    printf("\n\t\033[1;34mMes: \033[0m%d", mes);
                    printf("\n\t\033[1;34mAño: \033[0m%d", año);
                    printf("\n\t\033[1;34mCURP : \033[0m%s", curp);
                    printf("\n\t\033[1;34mID Paciente : \033[0m%d", idPa);
                    printf("\n\t\033[1;34mDIRECCIÓN : \033[0m%s", direccion);
                    printf("\n\t\033[1;34mTELÉFONO : \033[0m%s", tel);
                    printf("\n\t\033[1;34mSEXO : \033[0m%c", sexo);
                    printf("\n\t\033[1;34mNO. CONSULTORIO : \033[0m%d", consultorio);
                    printf("\n\t\033[1;34mNO. CITAS : \033[0m%d", citas);
                    printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
                    printf("\n\t\t\t\t\t\t\t\033[1;36m-FECHA DE CITA- \033[0m");
                    printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
                    printf("\n\t\033[1;34mDía: \033[0m%d",diaC);
                    printf("\n\t\033[1;34mMes: \033[0m%d",mesC);
                    printf("\n\t\033[1;34mAño: \033[0m%d",añoC);
                    printf("\n\t\033[1;34mPeso : \033[0m%.1f",peso);
                    printf("\n\t\033[1;34mPresión arterial : \033[0m%.1f",pre);
                    printf("\n\t\033[1;34mTemperatura : \033[0m%d",tem);
                    printf("\n\t\033[1;34mEstatuta : \033[0m%.2f",estatura);
                    printf("\n\t\033[1;34mTurno : \033[0m%c",turno);
                    printf("\n\t\033[1;34mNO. CITAS : \033[0m%d",citas);
                    printf("\n\033[1;34m-------------------------------------------------------------------------------------------------\033[0m\n");
                }
                fread(&idPa,sizeof(int),1,apArch2);
            }else{
                printf("\t\t\n\033[1;31mRegistro borrado lógicamente.\033[0m\n");
            }
             fclose(apArch);
             fclose(apArch2);
             return 1;
           }
           fclose(apArch2);
        }
        fseek(apArch,tamReg-25,1);
        fread(nombres,sizeof(nombres),1,apArch);
    }
    fclose(apArch);
    fclose(apArch2);
    return 0;
}*/

void buscarFecha2(char nombreArchCi[],int d,int m,int a){
    char turno;
    int diaC, mesC, añoC,tem,estado2;
    int idPa,tamReg=204;
    float peso,estatura,pre;
    FILE *apArch2;
    apArch2=fopen(nombreArchCi,"rb");
            if(apArch2==NULL){
                printf("Error, el archivo no existe\n");
                return;
            }
    int encontrados = 0;
    printf("Pacientes con citas en la fecha %d/%d/%d:\n", d, m, a);
    while (1) {
                fread(&idPa,sizeof(int),1,apArch2);
                fread(&diaC,sizeof(int),1,apArch2);
                fread(&mesC,sizeof(int),1,apArch2);
                fread(&añoC,sizeof(int),1,apArch2);
                fread(&peso,sizeof(float),1,apArch2);
                fread(&pre,sizeof(float),1,apArch2);
                fread(&tem,sizeof(int),1,apArch2);
                fread(&estatura,sizeof(float),1,apArch2);
                fread(&turno,sizeof(char),1,apArch2);
                fseek(apArch2,sizeof(int),SEEK_CUR);
                fread(&estado2,sizeof(int),1,apArch2);
        
        if (feof(apArch2)) {
            break;
        }
        
        if (diaC == d && mesC == m && añoC == a) {
            // Aquí deberías mostrar la información del paciente utilizando la función que prefieras
            printf("-ID paciente: %d\n", idPa);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron pacientes con citas en esa fecha.\n");
    }
    
    fclose(apArch2);

}

