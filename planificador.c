#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "colacp.h"
//VALOR = NOMBRE CIUDAD
//CLAVE = DISTANCIA AL ORIGEN

void eliminarEntrada(TEntrada e){
    free(e->clave);
    free(e->valor);
    free(e);
}

//Calcula la distancia de Manhattan de los valores pasados por parametro
//Distancia de Manhattan : |X2-X1| + |Y2-Y1|
float obtenerDistancia(float miX,float miY,float ciudad_x,float ciudad_y){
    float resultado = abs(ciudad_x - miX) + abs(ciudad_y - miY);
    return resultado;
}

// Crea una nueva entrada con los valores pasados por parametros y la retorna
TEntrada crearNuevaEntrada(TValor nombre, TClave distancia){
    TEntrada en1 = (TEntrada) malloc(sizeof(struct entrada));
    en1->valor = nombre;
    en1->clave = &distancia;
    return en1;
}
//Crea una cola de manera que la prioridad sea ascendente
void MostrarAscendente(TCiudad * arregloCiudades, int cant){
    TColaCP nuevaCola = crear_cola_cp(minHeap);//--> MINHEAP
    for(int i=1; i<cant; i++){
        float * distancia = (float*) malloc(sizeof(float));
        *distancia = obtenerDistancia(arregloCiudades[0]->pos_x,arregloCiudades[0]->pos_y,arregloCiudades[i]->pos_x,arregloCiudades[i]->pos_y);

        TEntrada nuevaEntrada = (TEntrada) malloc(sizeof(struct entrada));
        nuevaEntrada->valor = arregloCiudades[i]->nombre;
        nuevaEntrada->clave = distancia;

        cp_insertar(nuevaCola, nuevaEntrada);

        free(distancia);
        //free(nuevaEntrada);
    }
    int indice = 1;
    while(nuevaCola->cantidad_elementos > 0){
        TEntrada en = cp_eliminar(nuevaCola);
        printf("%i",indice);
        printf(". %s",(char*)en->valor);
        printf("\n");
        eliminarEntrada(en);
        indice++;
    }
    free(nuevaCola);

}

void MostrarDescendente(TCiudad * arregloCiudades, int cant){
    TColaCP nuevaCola = crear_cola_cp(maxHeap);//--> MINHEAP
    for(int i=1; i<cant; i++){
        float * distancia = (float*) malloc(sizeof(float));
        *distancia = obtenerDistancia(arregloCiudades[0]->pos_x,arregloCiudades[0]->pos_y,arregloCiudades[i]->pos_x,arregloCiudades[i]->pos_y);

        TEntrada nuevaEntrada = (TEntrada) malloc(sizeof(struct entrada));
        nuevaEntrada->valor = arregloCiudades[i]->nombre;
        nuevaEntrada->clave = distancia;

        cp_insertar(nuevaCola, nuevaEntrada);

        free(distancia);
        free(nuevaEntrada);
    }
    int indice = 1;
    while(nuevaCola->cantidad_elementos > 0){
        TEntrada en = cp_eliminar(nuevaCola);
        printf("\n");
        printf("%i",indice);
        printf(". %s",(char*)en->valor);
        eliminarEntrada(en);
        indice++;
    }
    //cp_destruir(nuevaCola, eliminarEntrada);
    free(nuevaCola);

}

void reducirHorasManejo(TCiudad * arregloCiudades, int cant){
    float sumaTotalRecorrido = 0;
    float miX = arregloCiudades[0]->pos_x;
    float miY = arregloCiudades[0]->pos_y;

    int j = 1;

    while(j < cant){
        TColaCP nuevaCola = crear_cola_cp(minHeap);
        for(int i=1; i<cant; i++){
            if(arregloCiudades[i] != POS_NULA){

                float * distancia = (float*) malloc(sizeof(float));
                *distancia = obtenerDistancia(miX, miY, arregloCiudades[i]->pos_x, arregloCiudades[i]->pos_y);

                TEntrada nuevaEntrada = (TEntrada) malloc(sizeof(struct entrada));
                nuevaEntrada->valor = (TCiudad) arregloCiudades[i];
                nuevaEntrada->clave = distancia;

                cp_insertar(nuevaCola, nuevaEntrada);

                free(distancia);
                free(nuevaEntrada);
            }
        }
        TEntrada en = cp_eliminar(nuevaCola);
        TCiudad ciudadAux = (TCiudad) en->valor;
        miX = ciudadAux->pos_x;
        miY = ciudadAux->pos_y;
        sumaTotalRecorrido += *(float*) en->clave;
        for(int h = 0; h< cant; h++){
            if(arregloCiudades[h] == ciudadAux){
                arregloCiudades[h] = POS_NULA;
            }
        }
        printf(" %d. %s \n",j, (char*) ciudadAux->nombre );
        while(cp_cantidad(nuevaCola) > 0){
            cp_eliminar(nuevaCola);
        }
        //cp_destruir(nuevaCola, fEliminar);
        j++;
        free(nuevaCola);
    }
    printf(" Total recorrido : %f", sumaTotalRecorrido);
}

void salir(TCiudad ciudades, int longitud){
    printf("SALIENDO...");
    for(int i = 0; i<longitud; i++){
        free(ciudades[i].nombre);
    }
    free(ciudades);
    exit(0);
}

int main(int argc, char *argv[])
{
    int opcionOperacion;
    argc = 2;
    if(argc != 2){
        printf("Error: Cantidad incorrecta de archivos. \n");
        exit(-1); //Finalizamos la ejecución del programa por error.
    }

    else{


        FILE *file = fopen("viajes.txt", "r"); //Abrimos el archivo en modo lectura
        if(file == NULL){
            printf("Error: el archivo no fue encontrado. \n");
            exit(-1); //Finalizamos la ejecución del programa por error.
        }

        //Asumimos que ingresarán 4 ciudades y el origen para una solucion mas eficiente.
        //Caso contrario deberíamos recorrer el archivo y contar lineas
        int cantidadDeCiudades = 5;
        TCiudad ciudades[cantidadDeCiudades] ;
        for(int i=0; i<cantidadDeCiudades; i++){
            ciudades[i] = (TCiudad) malloc(sizeof(struct ciudad));
        }

        float miX = fscanf(file,"%f",&miX);
        getc(file); //Salteo el ";"
        float miY = fscanf(file,"%f",&miY);

        char nombreOrigen[] = "origen";
        TCiudad origen = (TCiudad) malloc(sizeof(struct ciudad));
        origen->nombre = &nombreOrigen[0];
        origen->pos_x = miX;
        origen->pos_y = miY;
        int indice = 0;
        ciudades[indice] = origen;
        indice++;


        char ch;
        while(feof(file)==0){

            char *nom = malloc(20*sizeof(char));
            int i = 0;
            float x;
            float y;
            fscanf(file,"%c",&ch);
            while(ch != ';' && i<20){
                nom[i] = ch;
                i++;
                fscanf(file,"%c",&ch);
            }
            //ch=';'
            fscanf(file,"%f",&x);
            getc(file); //ch toma el ; que separa x de y
            fscanf(file,"%f",&y);
            fscanf(file,"%f",&y);

            TCiudad nuevaCiudad = (TCiudad) malloc(sizeof(struct ciudad));
            nuevaCiudad->nombre = &nom[0];
            nuevaCiudad->pos_x = x;
            nuevaCiudad->pos_y = y;
            ciudades[indice] = nuevaCiudad;
            indice++;

        }

            printf("\n");
            printf("Ingrese que operacion desea realizar:  \n");
            printf("--> Presione la tecla 1 para 'Mostrar Ascendente':  \n");
            printf("--> Presione la tecla 2 para 'Mostrar descendente':  \n");
            printf("--> Presione la tecla 3 para 'Reducir horas manejo':  \n");
            printf("--> Presione la tecla 4 para 'Salir': \n");
            scanf("%i",&opcionOperacion);

            switch (opcionOperacion){

                case 1:{
                    printf("MOSTRAR ASCENDENTE... ");
                    MostrarAscendente(ciudades, cantidadDeCiudades);
                }
                break;

                case 2:{
                    printf("MOSTRAR DESCENDENTE ");
                    MostrarDescendente(ciudades,cantidadDeCiudades);
                }
                break;

                case 3:{
                    printf("REDUCIR HORAS MANEJO \n");
                    reducirHorasManejo(ciudades, cantidadDeCiudades);
                }
                break;

                case 4:{
                    salir(*ciudades, indice);
                }
                break;

                default: printf("--> INGRESE UNA OPCION VALIDA <-- \n");
            }


        }
                return 0;
}
