#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int minHeap(TEntrada ent1, TEntrada ent2){
    int retorno = 0;
    if(*(float*) ent1->clave < *(float*) ent2->clave){//Retorno -1 si la clave e1 tiene menos prioridad que e2
        retorno = -1;
    }
    else{
        if( *(float*) ent1->clave > *(float*) ent2->clave){//Retorno 1 si e2 tiene mas prioridad (ES MAS CHICA)
            retorno = 1;
        }
    }
    return retorno;
}

int maxHeap(TEntrada ent1, TEntrada ent2){
    int retorno = 0;
    if(*(float*) ent1->clave < *(float*) ent2->clave){//Retorno 1 si la clave e2 tiene menos prioridad que e1
        retorno = 1;
    }
    else{
        if( *(float*) ent1->clave > *(float*) ent2->clave){//Retorno -1 si e1 tiene mas prioridad (ES MAS CHICA)
            retorno = -1;
        }
    }
    return retorno;
}

//Crea y retorna una CCP vacía
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){
    TColaCP cola = malloc(sizeof(struct cola_con_prioridad)); //Variable puntero al struct cola_con_prioridad y reservo espacio en memoria para el struct
    cola->cantidad_elementos = 0;
    cola-> comparador = f;
    cola-> raiz = ELE_NULO;
    return cola;
}

void burbujeoArriba(TNodo nodo, TColaCP ccp){
    if(nodo->padre != ELE_NULO && ccp->comparador(nodo->padre->entrada, nodo->entrada) == 1){
        TEntrada aux = nodo->entrada;
        nodo->entrada = nodo->padre->entrada;
        nodo->padre->entrada = aux;
        burbujeoArriba(nodo->padre,ccp);
    }
}

int altura(TNodo nodo){
    if(nodo-> hijo_izquierdo == ELE_NULO && nodo-> hijo_derecho == ELE_NULO){
        return 0;
    }
    else{
      if(nodo-> hijo_izquierdo != ELE_NULO && nodo-> hijo_derecho != ELE_NULO){
        return 1 + max(altura(nodo->hijo_izquierdo), altura(nodo->hijo_derecho));
      }
      else{ //El último caso posible es que no tenga hijo derecho, pues por propiedad de arbol binario primero se coloca hijo izquierdo y luego el derecho
        if(nodo-> hijo_izquierdo != ELE_NULO && nodo-> hijo_derecho == ELE_NULO)
        return 1;
      }
    }
    return 0;
}

TNodo ultimo(TNodo nodo){
    if(nodo-> hijo_izquierdo == ELE_NULO && nodo-> hijo_derecho == ELE_NULO){
        return nodo;
    }
    else{
        if(nodo-> hijo_izquierdo != ELE_NULO && nodo-> hijo_derecho == ELE_NULO){
            return (TNodo) nodo->hijo_izquierdo;
        }
        else{
            if(altura(nodo->hijo_izquierdo) > altura(nodo->hijo_derecho)){
                return ultimo(nodo->hijo_izquierdo);
            }
            else{
                return ultimo(nodo->hijo_derecho);
            }
        }
    }
}

TNodo hijoMenor(TColaCP cola, TNodo nodo){
    TNodo hijoM = ELE_NULO;
    if(nodo->hijo_izquierdo != ELE_NULO && nodo->hijo_derecho == ELE_NULO){
        hijoM = nodo->hijo_izquierdo;
    }
    else{
        if(nodo->hijo_izquierdo != ELE_NULO && nodo->hijo_derecho != ELE_NULO){
            if(cola->comparador(nodo->hijo_izquierdo->entrada,nodo->hijo_derecho->entrada) == 1){
                hijoM = nodo->hijo_derecho;
            }
            else{
                hijoM = nodo->hijo_izquierdo;
            }
        }
    }
    return hijoM;
}

void burbujeoAbajo(TNodo nodo, TNodo hijo, TColaCP cola){
    if(cola->comparador(nodo->entrada, hijo->entrada) == 1){
            TEntrada aux = nodo->entrada;
            nodo->entrada = hijo->entrada;
            hijo->entrada = aux;
            if(hijo->hijo_izquierdo != ELE_NULO){
                TNodo hijoM = hijoMenor(cola, hijo);
                burbujeoAbajo(hijo, hijoM, cola);
            }

    }
}

//Agrega la entrada entr en la cola 'cola', retorna verdadero (1) si procede con éxito, falso (0) en caso contrario/
int cp_insertar(TColaCP cola, TEntrada entr){

    if(cola == ELE_NULO){
        return FALSE;
        exit(CCP_NO_INI);
    }

    TNodo nodo = (TNodo) malloc(sizeof(struct nodo));
    nodo-> entrada = entr;
    nodo-> hijo_izquierdo = ELE_NULO;
    nodo-> hijo_derecho = ELE_NULO;


    if(cola->cantidad_elementos <= 1){
        if(cola->cantidad_elementos == 0){ //Cola vacía
            nodo-> padre = ELE_NULO;
            cola->raiz = nodo;
        }
        else{//Solo está la raiz
            TNodo raiz = cola->raiz;
            raiz->hijo_izquierdo = nodo;
            nodo->padre = raiz;
        }
    }else{
        TNodo ult = ultimo(cola-> raiz);
        TNodo papa = ult->padre;
        TNodo padreDePapa = ELE_NULO;
        TNodo aux = ELE_NULO;
        if(papa->hijo_izquierdo == ult){ //El último es hijo izquierdo
            papa->hijo_derecho = nodo;
            nodo->padre = papa;
        }
        else{ //Ult es hijo derecho
            if(papa == cola->raiz){//Caso padre es raiz
                aux = papa->hijo_izquierdo;
                aux->hijo_izquierdo = nodo;
                nodo->padre = aux;
            }
            else{//Caso padre no es raiz
                padreDePapa = papa->padre;
                while(padreDePapa != cola->raiz && padreDePapa->hijo_izquierdo != papa){
                    aux = padreDePapa;
                    padreDePapa = padreDePapa->padre;
                    papa = aux;
                }
                if(padreDePapa->hijo_izquierdo == papa){ //papa es hijo izquierdo
                    papa = padreDePapa->hijo_derecho;
                }
                else{
                    papa = padreDePapa->hijo_izquierdo;
                }
                while(papa->hijo_izquierdo != ELE_NULO){
                        aux = papa->hijo_izquierdo;
                        papa = aux;
                    }
                    papa->hijo_izquierdo = nodo;
                    nodo->padre = papa;
            }
        }
    }
    cola->cantidad_elementos++;

    //Burbujeo y ordeno
    burbujeoArriba(nodo, cola);

    return TRUE;
}

/*Elimina y retorna la entrada con mayor prioridad (Esto es, menor clave) de la cola.
Reacomoda la estructura heap de forma conistente. Si la cola es vacía retorna ELE_NULO*/
TEntrada cp_eliminar(TColaCP cola){
    TNodo nodoAEliminar = cola->raiz;

    if(cola->cantidad_elementos <= 1){
        if(cola->cantidad_elementos == 0){
            return ELE_NULO;
        }
        else{
            cola->raiz = ELE_NULO;

        }
    }
    else{//Caso la cola tiene mas de 1 elemento

        TNodo nuevaRaiz = ultimo(nodoAEliminar);
        cola->raiz = nuevaRaiz;

        //Asigno los hijos correspondientes a la raiz
        nuevaRaiz->hijo_derecho = nodoAEliminar->hijo_derecho;
        nuevaRaiz->hijo_izquierdo = nodoAEliminar->hijo_izquierdo;


        //Los hijos de la ex-raiz conocen a su nuevo padre
        if(nodoAEliminar->hijo_derecho != ELE_NULO)
            nodoAEliminar->hijo_derecho->padre = nuevaRaiz;

        if(nodoAEliminar->hijo_derecho != ELE_NULO)
            nodoAEliminar->hijo_izquierdo->padre = nuevaRaiz;

        //Como nuevaRaiz pasa a ser raíz, no sera mas hija de su padre
        if(nuevaRaiz->padre->hijo_izquierdo == nuevaRaiz)
            nuevaRaiz->padre->hijo_izquierdo = ELE_NULO;
        if(nuevaRaiz->padre->hijo_derecho == nuevaRaiz)
            nuevaRaiz->padre->hijo_derecho = ELE_NULO;

        //Como es raiz no debe tener padre
        nuevaRaiz->padre = ELE_NULO;

        nodoAEliminar->hijo_derecho = ELE_NULO;
        nodoAEliminar->hijo_izquierdo = ELE_NULO;

        TNodo hijoM = hijoMenor(cola, nuevaRaiz);
        burbujeoAbajo(nuevaRaiz, hijoM, cola);

    }
    cola->cantidad_elementos--;

    return nodoAEliminar->entrada;
}

//Retorna la cantidad de entradas de la cola
int cp_cantidad(TColaCP cola){
 return cola->cantidad_elementos;
}


void destruirRec(TColaCP cola, TNodo nodo, void (*fEliminar)(TEntrada e)){
    if(nodo->hijo_izquierdo != ELE_NULO)
        destruirRec(cola, nodo->hijo_izquierdo, fEliminar);
    if(nodo->hijo_derecho != ELE_NULO)
        destruirRec(cola, nodo->hijo_derecho, fEliminar);

    fEliminar(nodo->entrada);
    free(nodo);//Libero memoria ocupada por nodo
}

//Elimina todas las entradas y libera toda la memoria utilizada por la cola cola.
//Para la eliminación de las entradas, utiliza la función fEliminar.
void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada e) ){
    destruirRec(cola, cola->raiz, fEliminar);
    free(cola); //Libero espacio ocupado por la cola en si
}
