#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

//Declaracion de constantes
#define FALSE 0;
#define TRUE 1;
#define CCP_NO_INI 2; //Intento de acceso inv´alido sobre Cola CP sin inicializar
#define POS_NULA NULL;//Posicion nula.
#define ELE_NULO NULL;//Elemento nulo.

int main()
{

    char archivo[100] = "";
    int opcionOperacion;
    FILE * f1;

    printf("Ingres el nombre del archivo: ");
    scanf("%s",&archivo);
    f1 = fopen(archivo, "r");
    if(f1==NULL)
        printf("NO SE ENCONTRO EL ARCHIVO\n");
    else{
        printf("abierto con exito \n");


    printf("Ingrese que operacion desea realizar:  \n");
    printf("--> Presione la tecla 1 para 'Mostrar Ascendente':  \n");
    printf("--> Presione la tecla 2 para 'Mostrar descendente':  \n");
    printf("--> Presione la tecla 3 para 'Reducir horas manejo':  \n");
    printf("--> Presione la tecla 4 para 'Salir': \n");
    scanf("%d",&opcionOperacion);


    }

    printf("Ingrese que operacion desea realizar:  \n");
}
