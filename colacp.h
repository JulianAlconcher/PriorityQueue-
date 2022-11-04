#ifndef TDA_COLA_CON_PRIORIDAD_H_INCLUDED
#define TDA_COLA_CON_PRIORIDAD_H_INCLUDED

//Declaracion de constantes
#define FALSE 0 //Valor lógico falso
#define TRUE 1 //Valor lógico verdadero
#define CCP_NO_INI 2 //Intento de acceso inválido sobre Cola CP sin inicializar
#define POS_NULA NULL //Posición nula
#define ELE_NULO NULL //Elemento nulo

typedef void * TClave;
typedef void * TValor;

typedef struct entrada {
    TClave clave;
    TValor valor;
} *TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
}*TNodo;

typedef struct cola_con_prioridad {
        int cantidad_elementos;
        TNodo raiz;
        int (*comparador)(TEntrada, TEntrada);
}*TColaCP;

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;


//Crea y retorna una CCP vacía
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));


//Agrega la entrada entr en la cola 'cola', retorna verdadero (1) si procede con éxito, falso (0) en caso contrario
int cp_insertar(TColaCP cola, TEntrada entr);

int f(TEntrada e1, TEntrada e2);
/*
//Elimina y retorna la entrada con mayor prioridad (Esto es, menor clave) de la cola.
Reacomoda la estructura heap de forma conistente. Si la cola es vacía retorna ELE_NULO
*/
TEntrada cp_eliminar(TColaCP cola);

//Retorna la cantidad de entradas de la cola
int cp_cantidad(TColaCP cola);

// Elimina todas las entradas y libera toda la memoria utilizada por la cola cola. Para la eliminación de las entradas, utiliza la función fEliminar.
void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada) );

void fEliminar(TEntrada e);

int minHeap(TEntrada ent1, TEntrada ent2);
int maxHeap(TEntrada ent1, TEntrada ent2);

#endif // TDA_COLA_CON_PRIORIDAD_H_INCLUDED
