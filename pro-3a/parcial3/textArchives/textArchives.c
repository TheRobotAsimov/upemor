#include <stdio.h>

/*

Un archivo son 1s y 0s

Archivo de texto:
- Leer
- Escribir

Archivo binario:
- No legible para el humano

 */

void readTArchive(char path[]);
void writeTArchive(char path[]);
void copyTArchive(char path[], char newpath[]);

int main()
{
    char path[] = "test.txt";
    char path2[] = "copy.txt";

    writeTArchive(path);
    printf("\n firts archive: \n");
    readTArchive(path);
    copyTArchive(path, path2);
    printf("\n second archive: \n");
    readTArchive(path2);

    return 0;
}

////////////////////////////////////////////////////////////

void readTArchive(char path[])
{
    FILE *archPointer;
    int character;

    archPointer = fopen(path, "rt"); // read text file
    
    if(archPointer == NULL)
    {
        printf("El archivo no exite\n");
        return;
    }

    character = fgetc(archPointer); // Recibe el apuntador del archivo, te da el código ASCII
    while(character!=-1)
    {
        printf("%c", character);
        character = fgetc(archPointer);
    }

    printf("\n\n");

    fclose(archPointer);
}

void writeTArchive(char path[])
{
    FILE *archPointer;
    int character, code = 123;
    char description[] = "hi.";

    archPointer = fopen(path, "wt");

    if(archPointer==NULL)
    {
        printf("Archivo no encontrado");
        return;
    }

    fprintf(archPointer, "\n#include <stdio.h>\nint main(){\n  printf(\"%s %d\");\n  return 0;\n}\n\n", description, code); // Cadena con formato

    for(int i=65; i<91; i++)
        fputc(i, archPointer); // Caracter por caracter

    fputs("\n...", archPointer); // String, no da formato

    fclose(archPointer);
}

void copyTArchive(char path[], char newpath[])
{
    FILE *fontPointer, *destPointer;

    fontPointer = fopen(path, "rt");
    destPointer = fopen(newpath, "wt");

    if(fontPointer==NULL || destPointer==NULL)
    {
        printf("Archivo(s) no encontrado(s)");
        return;
    }

    int character;

    character = fgetc(fontPointer);
    while(character!=-1)
    {
        fputc(character, destPointer);
        character = fgetc(fontPointer);
    }

    fclose(fontPointer);
    fclose(destPointer);    // SIEMPRE CERRAR
}