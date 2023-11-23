#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lista doblemente enlazada
typedef struct nodo_empleado
{
  char matricula[5];
  char nombre_empleado[50];
  float pago;
  struct nodo_empleado *siguiente;
  struct nodo_empleado *anterior;
} nodo_empleado;

// Cola
typedef struct nodo_pedido
{
  char vendedor[5];
  int cant_prod;
  float total_ventas;
  struct nodo_pedido *siguiente;
} nodo_pedido;

// Lista doblemente enlazada
typedef struct nodo_sucursal
{
  char nombre_sucursal[100];
  char domicilio[100];
  char gerente[100];
  struct nodo_sucursal *siguiente;
  struct nodo_sucursal *anterior;

  // Los pedidos al ser colas son del tipo FIFO: 
  // Se elimina siempre el primero, se agrega siempre al final
  nodo_pedido *primer_pedido;
  nodo_pedido *ultimo_pedido;

  // 
  nodo_empleado *primer_empleado;
  nodo_empleado *ultimo_empleado;
} nodo_sucursal;

int menu();

void gestion_sucursales ();
  int menu_gestion_sucursales ();

void gestion_vendedores (nodo_sucursal **primer_sucursal);
  int menu_gestion_vendedores ();
  void registrar_vendedor (nodo_sucursal **primer_sucursal);

void resgistro_pedido ();
  int menu_registro_pedido ();

void atencion_pedidos ();
  int menu_atencion_pedidos ();

void reporte_ventas ();
  int menu_reporte_ventas ();

nodo_sucursal *buscar_sucursal (nodo_sucursal *primer_sucursal);

/////////////////////////////////////////////////////
//////////////////////// MAIN  //////////////////////
/////////////////////////////////////////////////////

int main(void) {

  int opcion = 0;
  
  do
  {
    opcion = menu();
    switch(opcion)
    {
      case 1:
        gestion_sucursales();
        break;
      case 2:
        printf("\n\nGESTION DE VENDEDORES\n\n");
        break;
      case 3:
        printf("\n\nREGISTRO DE PEDIDO\n\n");
        break;
      case 4:
        printf("\n\nATENCION DE PEDIDOS\n\n");
        break;
      case 5:
        printf("\n\nREPORTE DE VENTAS\n\n");
        break;
      case 0:
        printf("\n\nSaliendo...\n\n");
        break;
      default:
        printf("\n\nOpcion no valida\n\n");
        break;
    }
  } while (opcion != 0);
  
  return 0;
}

int menu()
{
  int opcion;
  
  printf("\n\tMENU\n\n");
  printf("1. Gestion de Sucursales\n");
  printf("2. Gestion de Vendedores\n");
  printf("3. Registro de Pedido\n");
  printf("4. Atencion de Pedidos\n");
  printf("5. Reporte de Ventas\n");
  printf("0. Salir\n\n");
  printf("Ingrese la opcion: ");
  scanf("%d", &opcion);

  return opcion;
}

/////////////////////////////////////////////////////
///////////// FUNCIONES REUTILIZABLES  //////////////
/////////////////////////////////////////////////////

nodo_sucursal *buscar_sucursal (nodo_sucursal *primer_sucursal)
{
  char sucursal_a_buscar[100];

  printf("Ingrese la sucursal:\n");
  scanf(" %[^\n]", sucursal_a_buscar);
  
  nodo_sucursal *nodo_actual = primer_sucursal;

  while ( nodo_actual != NULL && 
          strcmp(sucursal_a_buscar, nodo_actual -> nombre_sucursal) != 0)
  {
    nodo_actual = nodo_actual -> siguiente;
  }

  if (nodo_actual == NULL)
  {
    printf("\nNo se encontro la sucursal\n\n");
    return NULL;
  }

  return nodo_actual;
}

/////////////////////////////////////////////////////
////////////// GESTION DE SUCURSALES  ///////////////
/////////////////////////////////////////////////////

int menu_gestion_sucursales ()
{
  int opcion;

  printf("\n\nGESTION DE SUCURSALES\n\n");
  printf("1. Registrar\n");
  printf("2. Eliminar\n");
  printf("3. Consultar\n");
  printf("0. Salir\n\n");
  printf("Ingrese la opcion: ");
  scanf("%d", &opcion);

  return opcion;
}

void gestion_sucursales ()
{
  int opcion = 0;

  do
  {
    opcion = menu_gestion_sucursales();
    switch(opcion)
      {
        case 1:
          printf("\n\nREGISTRAR\n\n");
          break;
        case 2:
          printf("\n\nELIMINAR\n\n");
          break;
        case 3:
          printf("\n\nCONSULTAR\n\n");
          break;
        case 0:
          printf("\n\nSaliendo...\n\n");
          break;
        default:
          printf("\n\nOpcion no valida\n\n");
          break;
      }
  } while (opcion != 0);
}

/////////////////////////////////////////////////////
////////////// GESTION DE VENDEDORES  ///////////////
/////////////////////////////////////////////////////

int menu_gestion_vendedores ()
{
  int opcion;

  printf("\n\nGESTION DE VENDEDORES\n\n");
  printf("1. Registrar\n");
  printf("2. Eliminar\n");
  printf("3. Consultar\n");
  printf("0. Salir\n\n");
  printf("Ingrese la opcion: ");
  scanf("%d", &opcion);

  return opcion;
}

void gestion_vendedores (nodo_sucursal **primer_sucursal)
{
  int opcion = 0;

  do
  {
    opcion = menu_gestion_vendedores();
    switch(opcion)
      {
        case 1:
          registrar_vendedor(primer_sucursal);
          break;
        case 2:
          printf("\n\nELIMINAR\n\n");
          break;
        case 3:
          printf("\n\nCONSULTAR\n\n");
          break;
        case 0:
          printf("\n\nSaliendo...\n\n");
          break;
        default:
          printf("\n\nOpcion no valida\n\n");
          break;
      }
  } while (opcion != 0);
  
}

void registrar_vendedor (nodo_sucursal **primer_sucursal)
{
  printf("\n\nREGISTRAR\n\n");
  
  nodo_sucursal *sucursal = buscar_sucursal(*primer_sucursal);

  if (sucursal == NULL)
  {
    return;
  }

  // Datos del vendedor
  printf("\nDatos del vendedor\n\n");

  char matricula_vendedor[5];
  printf("Matricula del vendedor:\n");
  scanf(" %[^\n]", matricula_vendedor);

  char nombre_vendedor[50];
  printf("Matricula del vendedor:\n");
  scanf(" %[^\n]", nombre_vendedor);

  float pago_vendedor;
  printf("Pago del vendedor:\n");
  scanf(" %f", &pago_vendedor);

  // (agregar el vendedor a la lista, ordenado alfabeticamente)
}

/////////////////////////////////////////////////////
//////////////// REGISTRO DE PEDIDO  ////////////////
/////////////////////////////////////////////////////

void registro_pedido ()
{
  
}

/////////////////////////////////////////////////////
/////////////// ATENCION DE PEDIDOS  ////////////////
/////////////////////////////////////////////////////

void atencion_pedidos ()
{
  
}

/////////////////////////////////////////////////////
///////////////// REPORTE DE VENTAS /////////////////
/////////////////////////////////////////////////////

void reporte_ventas ()
{
  
}