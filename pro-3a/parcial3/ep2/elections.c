#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////////////////////
#include <time.h>

void setUpElections(int *vQuantity, int vSize, char **candNames, int cSize,
                     int nameLen);
void askSectVoters(int *vQuantity, int vSize);
void askCandNames (char **candNames, int cSize, int nameLen);


void option2(int *vMax, int **votes, int vSize, int cSize, char **candNames,
             int nameLen);
void initElections(int *vMax, int **votes, int vSize, int cSize);
void printElections(int **votes, int vSize, int cSize, char **candNames,
                    int nameLen);
void printCloseElections(int **votes, int vSize, int cSize, char **candNames,
                    int nameLen);
int add1Vote(int **votes, int vSize, int cSize, char **candNames, int nameLen);
int addVotes(int **votes, int vSize, int cSize, char **candNames, int nameLen);


void closeElections(int *vMax, int **votes, int vSize, int cSize,
                    char **candNames);
int validation(int *vMax, int **votes, int vSize, int cSize);
void printWinner (int **votes, int cSize, int vSize, char **candNames);
void printExcees(int *vMax, int **votes, int cSize, int vSize, char **candNames);
void rebootElections(int **votes, int vSize, int cSize);
int candSum(int **votes, int vSize, int candidate);
int sectSum(int **votes, int cSize, int section);

int menu();
int menu2();

int main() {
  int option, sections, candidates, block1 = 1, block2 = 1;
  int *vQuantity, **votes;
  char **candNames, *text;

  int nameLen = 30;

  srand(time(NULL));

  printf(" Ingrese la cantidad de secciones: ");
  scanf("%d", &sections);
  printf(" Ingrese el maximo numero de candidatos: ");
  scanf("%d", &candidates);

  vQuantity = (int *)malloc(sections * sizeof(int));
  if (vQuantity == NULL) {
    printf(" Problemas con la memoria\n");
    return 0;
  }

  candNames = (char **)malloc(candidates * sizeof(char *));
  for (int i = 0; i < candidates; i++)
    candNames[i] = (char *)malloc(nameLen * sizeof(char));
  if (candNames == NULL) {
    printf(" Problemas con la memoria\n");
    free(vQuantity);
    return 0;
  }

  votes = (int **)malloc(candidates * sizeof(int *));
  for (int i = 0; i < candidates; i++)
    votes[i] = (int *)malloc(sections * sizeof(int));
  if(votes == NULL) {
    printf(" Problemas con la memoria\n");

    for (int i = 0; i < candidates; i++)
      free(candNames[i]);
    free(candNames);
    
    free(vQuantity);

    return 0;
  }

  do {
    option = menu();
    switch (option) {
    case 1:
      setUpElections(vQuantity, sections, candNames, candidates, nameLen);
      block1 = 0;
      block2 = 1;
      break;
    case 2:
      if (block1 == 0) {
        option2(vQuantity, votes, sections, candidates, candNames, nameLen);
        block2 = 0;
        // block3 para evitar setUpElections?
      } else
        printf("\n Primero debe realizar la opcion 1\n");
      break;
    case 3:
      if (block1 == 0 && block2 == 0) {
        printCloseElections(votes, sections, candidates, candNames, nameLen);
        closeElections(vQuantity, votes, sections, candidates, candNames);
        rebootElections(votes, sections, candidates);
        block1 = 1;
        block2 = 1;
      } else
        printf("\n Antes debe realizar las primeras 2 opciones\n");
      break;
    case 0:
      break;
    default:
      printf("\n Opcion no valida\n");
      break;
    }

  } while (option != 0);

  if(vQuantity != NULL)
    free(vQuantity);

  if(candNames != NULL) {
    for (int i = 0; i < candidates; i++)
      free(candNames[i]);
    
    free(candNames);
  }

  if(votes != NULL) {
    for (int i = 0; i < candidates; i++)
      free(votes[i]);

    free(votes);
  }

  return 0;
}

///// OPCION 1 //////

void setUpElections(int *vQuantity, int vSize, char **candNames, int cSize,
                     int nameLen) {

  printf("\n");

  askSectVoters (vQuantity, vSize);

  printf("------------------------------------------------\n");

  askCandNames (candNames, cSize, nameLen);  
}

void askSectVoters(int *vQuantity, int vSize) {
  for (int i = 0; i < vSize; i++) {
    printf(" Ingrese el numero de votantes de la seccion %d: ", i + 1);
    scanf("%d%*c", &vQuantity[i]);

    if (vQuantity[i] < 1) {
      printf(" No se permiten numeros menores a 1\n");
      i--;
    }
  }
}

void askCandNames (char **candNames, int cSize, int nameLen) {
  int size;

  for (int i = 0; i < cSize; i++) {
    printf(" Ingrese el nombre completo del candidato %d: ", i + 1);
    scanf(" %[^\n]", candNames[i]);

    size = strlen(candNames[i]);

    for (int j = 0; j < size; j++) {
      if (size > nameLen) { // Quizas no sea muy optimo que poner este if dentro
                            // de este ciclo for, pero si lo pongo arriba se
                            // sale de la funcion o si lo pongo arriba y quito
                            // el break, puede provocar segmentation fault
        printf(" Superaste el limite de 30 caracteres\n");
        i--;
        break;
      }
      if (candNames[i][j] > 32 && candNames[i][j] < 65) { // Codigo ASCII
        printf(" No incluya caracteres especiales\n");
        i--;
        break;
      }
    }
    for (int k = 0; k < i; k++)
      if (strcmp(candNames[i], candNames[k]) == 0) {
        printf(" No se permite repetir nombre\n");
        i--;
        break;
      }
  }
}

///// OPCION 2 //////

void initElections(int *vMax, int **votes, int vSize, int cSize) {  // Inicializa arreglo
  // votes[candidate][section]
  for (int i = 0; i < cSize; i++)
    for (int j = 0; j < vSize; j++)
      votes[i][j] = rand() % (vMax[j] / 2); // Quitar /2
}

/////////////////////////

void printElections(int **votes, int vSize, int cSize, char **candNames,
                    int nameLen) {
  printf("\n%*s", nameLen + 2, ""); // Más 2 por el : y el espacio

  for (int j = 0; j < vSize; j++) {
    printf("%*s", 5 - 2, ""); // Menos 2 por S#
    printf("S%d", j + 1);
  }

  printf("\n\n");

  for (int i = 0; i < cSize; i++) {
    printf("%30s: ", candNames[i]);
    for (int j = 0; j < vSize; j++)
      printf("%5d", votes[i][j]);
    printf("\n");
  }

  printf("\n");
}

/////////////////////////

void printCloseElections(int **votes, int vSize, int cSize, char **candNames,
                    int nameLen) {

  printf("\n%*s", nameLen + 2, ""); // Más 2 por el : y el espacio

  for (int j = 0; j < vSize; j++) {
    printf("%*s", 5 - 2, ""); // Menos 2 por S#
    printf("S%d", j + 1);
  }

  printf("\n\n");

  for (int i = 0; i < cSize; i++) {
    printf("%30s: ", candNames[i]);
    for (int j = 0; j < vSize+1; j++) {
      if(j<vSize)
        printf("%5d", votes[i][j]);
      if(j==vSize)
        printf(" | %5d", candSum(votes, vSize, i));
    }
    printf("\n");
  }

  printf("%*s", nameLen + 2, ""); // nameLen
  for (int i = 0; i < vSize*5; i++) {
        printf("-");
    }
  printf("\n");

  printf("%*s", nameLen + 2, ""); // nameLen
  // Suma de los votos por seccion
  for (int i = 0; i < vSize; i++) {
    printf("%5d", sectSum(votes, cSize, i));
  }

  printf("\n");
}

///////////////////////////////////

int add1Vote(int **votes, int vSize, int cSize, char **candNames,
              int nameLen) {
  int section, candIndex = -1;
  char *candidate;

  candidate = (char *)malloc(nameLen * sizeof(char));

  if(candidate == NULL)
    return 0;

  printf(" Ingrese la seccion (solo el numero): ");
  scanf("%d%*c", &section);
  section--;
  printf(" Ingrese el candidato: ");
  scanf(" %[^\n]", candidate);

  printf("\n");

  for (int i = 0; i < cSize; i++) {
    if (strcmp(candNames[i], candidate) == 0)
      candIndex = i;
  }

  if (candIndex != -1 && section >= 0 && section < vSize) { // Validación de datos
    votes[candIndex][section]++;
  } else {
    printf("%*s", nameLen, ""); // Espacio en blanco
    printf(" No encontrado\n");
  }

  free(candidate);

  printf("\n");

  return 1;
}

//////////////////////////////

int addVotes(int **votes, int vSize, int cSize, char **candNames,
              int nameLen) {
  int section, candIndex = -1, quantity;
  char *candidate;

  candidate = (char *)malloc(nameLen * sizeof(char));

  if(candidate == NULL)
    return 0;

  printf(" Ingrese la seccion (solo el numero): ");
  scanf("%d%*c", &section);
  section--;
  printf(" Ingrese el candidato: ");
  scanf(" %[^\n]", candidate);

  for (int i = 0; i < cSize; i++) {
    if (strcmp(candNames[i], candidate) == 0)
      candIndex = i;
  }

  if (candIndex != -1 && section >= 0 && section < vSize) { // Validación de datos
    printf(" Ingrese la cantidad de votos que desea agregar: ");
    scanf("%d%*c", &quantity);

    printf("\n");

    votes[candIndex][section] += quantity;
  } else {
    printf("%*s", nameLen, "");
    printf(" No encontrado\n");
  }

  free(candidate);

  printf("\n");

  return 1;
}

///// OPCION 3 //////

void closeElections(int *vMax, int **votes, int vSize, int cSize,
                    char **candNames) {

  int valido = validation(vMax, votes, vSize, cSize);

  printf("\n\n");

  if(valido) {

    printWinner(votes, cSize, vSize, candNames);

  } else {

    printExcees(vMax, votes, cSize, vSize, candNames);

  }
}

void printExcees(int *vMax, int **votes, int cSize, int vSize, char **candNames) {
  for (int i = 0; i < vSize; i++) {
    if (sectSum(votes, cSize, i) > vMax[i]) {
      printf(" La seccion %d sobrepaso el limite de votos (%d) con %d votos\n", i + 1, vMax[i], sectSum(votes, cSize, i));
      for (int j = 0; j < cSize; j++) {
        if (votes[j][i] > vMax[i])
          printf("  - %s sobrepaso el numero de votos permitidos\n", candNames[j]);
      }
    }
  }
}

void printWinner (int **votes, int cSize, int vSize, char **candNames) {
  int max = 0, maxInd, winners = 0;

  for (int i = 0; i < cSize; i++) {
    if (candSum(votes, vSize, i) > max) {
      max = candSum(votes, vSize, i);
      maxInd = i;
    }
  }

  for (int i = 0; i < cSize; i++) {
    if (candSum(votes, vSize, i) == max)
      winners++;
  }

  if (winners == 1)
    printf(" El ganador fue %s\n", candNames[maxInd]);
  else {
    printf(" Los %d ganadores fueron:\n", winners);
    for (int i = 0; i < cSize; i++)
      if(candSum(votes, vSize, i) == max)
        printf(" * %s\n", candNames[i]);
  }

  printf("\n");

  for (int i = 0; i < cSize; i++)
    printf("  - %s tuvo %d votos\n", candNames[i], candSum(votes, vSize, i)); // Se imprime los valores que retorna la función candSum
}

int validation(int *vMax, int **votes, int vSize, int cSize) {

  for (int i = 0; i < vSize; i++) {
    if (sectSum(votes, cSize, i) > vMax[i]) {
      return 0;
    }
  }

  return 1;
}

int candSum(int **votes, int vSize, int candidate) {
  int totalVotes = 0;
  for (int i = 0; i < vSize; i++) {
    totalVotes += votes[candidate][i];
  }
  return totalVotes;
}

int sectSum(int **votes, int cSize, int section) {
  int totalVotes = 0;
  for (int i = 0; i < cSize; i++) {
    totalVotes += votes[i][section];
  }
  return totalVotes;
}

void rebootElections(int **votes, int vSize, int cSize) {
  // votes[candidate][section]
  for (int i = 0; i < cSize; i++)
    for (int j = 0; j < vSize; j++)
      votes[i][j] = 0; // Quitar /2
}

////// MENUS //////

int menu() {
  int option;

  printf("\n MENU\n");
  printf(" 1. Preparar elecciones\n");
  printf(" 2. Realizar elecciones\n");
  printf(" 3. Cerrar elecciones\n");
  printf(" 0. Fin del programa\n\n");
  printf(" Ingrese la opcion que desee: ");
  scanf("%d", &option);

  return option;
}

int menu2() {

  int option;

  printf("\n Elecciones\n");
  printf(" 1. Inicializar arreglo de votos\n");
  printf(" 2. Agregar un voto\n");
  printf(" 3. Agregar varios votos\n");
  printf(" 0. Volver al menu\n\n");
  printf(" Ingrese la opcion que desee: ");
  scanf("%d", &option);

  return option;
}

void option2(int *vMax, int **votes, int vSize, int cSize, char **candNames,
             int nameLen) {
  int option, block = 1;
  do {
    option = menu2();
    switch (option) {
    case 1:
      initElections(vMax, votes, vSize, cSize);
      printElections(votes, vSize, cSize, candNames, nameLen);
      block = 0;
      break;
    case 2:
      if (block == 0) {
        if(add1Vote(votes, vSize, cSize, candNames, nameLen))
          printElections(votes, vSize, cSize, candNames, nameLen);
        else {
          printf(" Problemas con la memoria\n");
          option = 0;
        }
      } else
        printf("\n Primero debe realizar la inicializacion\n");
      break;
    case 3:
      if (block == 0) {
        if(addVotes(votes, vSize, cSize, candNames, nameLen))
          printElections(votes, vSize, cSize, candNames, nameLen);
        else {
          printf(" Problemas con la memoria\n");
          option = 0;
        }
      } else
        printf("\n Primero debe realizar la inicializacion\n");
      break;
    case 0:
      if (block == 0) {
        break;
      } else {
        printf("\n Primero debe realizar la inicializacion\n");
        option = 1;
      }
      break;
    default:
      printf("\n Opcion no valida\n");
      break;
    }
  } while (option != 0);
}