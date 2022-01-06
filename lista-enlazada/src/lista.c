#include "lista.h"
#include <stdlib.h> // malloc y free, memoria dinámica
#include <string.h>

// Crear un nuevo nodo a partir de los datos de un libro
Nodo* CrearNodo(Libro* libro) {
    Nodo* nodo = (Nodo *) malloc(sizeof(Nodo));

    strncpy(nodo->libro.titulo, libro->titulo, 50);
    strncpy(nodo->libro.autor, libro->autor, 50);
    strncpy(nodo->libro.isbn, libro->isbn, 13);

    nodo->siguiente = NULL;

    return nodo;
}

// En C no se eliminan las cosas automáticamente, necesito liberar memoria
void DestruirNodo(Nodo* nodo){
    free(nodo);
}

/*
Insertar un nodo al principio de la lista:
    - Crear un nuevo nodo
    - Hacer que la cola del nuevo nodo sea la cabeza de la lista previa
    - Mover el puntero de cabeza de la lista para que apunte al nuevo nodo
    - Incrementar la longitud de la lista
*/
void InsertarPrincipio(Lista* lista, Libro* libro) {
    Nodo* nodo = CrearNodo(libro);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->longitud++;
}

/*
Insertar un nodo al final de la lista:
    - Crear un nuevo nodo
    - Si la lista estuviera vacía simplemente hay que apuntar la cabeza de la lista al nuevo nodo
    - Recorrer la lista para encontrar el último nodo (aquel en el que siguiente es NULL)
    - Hacer que el siguiente del último nodo de la lista apunte al nodo recién creado
    - Incrementar la longitud de la lista
*/
void InsertarFinal(Lista* lista, Libro* libro) {
    Nodo* nodo = CrearNodo(libro);

    if (lista->cabeza == NULL) {
        lista->cabeza = nodo;
    } else {
        Nodo* puntero = lista->cabeza;
        while (puntero->siguiente) {
            puntero = puntero->siguiente;
        }

        puntero->siguiente = nodo;
    }
    lista->longitud++;
}

/*
Insertar un nodo después del elemento 'n' de la lista:
    - Crear un nuevo nodo
    - Si la lista estuviera vacía simplemente hay que apuntar la cabeza de la lista al nuevo nodo
    - Recorrer la lista para encontrar el nodo número 'n' o el final de la lista
    - Hacer que el siguiente del nodo recién creado apunte a nodo en posición 'n+1' (primero conectamos por la derecha)
    - Hacer que el siguiente del nodo en posicion 'n' apunte al nodo recién creado (después conectamos por la izquierda)
    - Incrementar la longitud de la lista
*/
void InsertarDespues(int n, Lista* lista, Libro* libro) {
    Nodo* nodo = CrearNodo(libro);

    if (lista->cabeza == NULL) {
        lista->cabeza = nodo;
    } else {
        Nodo* puntero = lista->cabeza;
        int posicion = 0;
        while (posicion < n && puntero->siguiente) {
            puntero = puntero->siguiente;
            posicion++;
        }

        nodo->siguiente = puntero->siguiente;
        puntero->siguiente = nodo;
    }
    lista->longitud++;
}

/*
Obtener el libro que está en la posición 'n' de la lista
Devolveré Libro, no Nodo, porque el nodo es algo interno que sólo le interesa a la lista
Si la lista está vacía devuelvo NULL
Si pido un libro fuera de los límites de la lista también devuelvo NULL
*/
Libro* Obtener(int n, Lista* lista) {
    if (lista->cabeza == NULL) {
        return NULL;
    } else {
        Nodo* puntero = lista->cabeza;
        int posicion = 0;
        while (posicion < n && puntero->siguiente) {
            puntero = puntero->siguiente;
            posicion++;
        }
        if (posicion != n) {
            return NULL;
        } else {
            return &puntero->libro;
        }
    }
}

// Saber cuántos elementos tengo en la lista

int Contar(Lista* lista) {
    return lista->longitud;
}

// Saber si una lista está vacía o no
int EstaVacia(Lista* lista) {
    return lista->cabeza == NULL;
}


/*
Eliminar el primer elemento de una lista:
    - Compruebo que la lista no esté vacía
    - Obtengo el nodo a eliminar (cabeza de la lista)
    - Guardar su referencia para destruir el nodo de memoria
    - Actualizar la cabeza de la lista para que apunte al segundo elemento
    - Destruir el nodo eliminado
    - Decrementar la longitud de la lista
*/
void EliminarPrincipio(Lista* lista) {
    if (lista->cabeza) {
        Nodo* eliminado = lista->cabeza;
        lista->cabeza = lista->cabeza->siguiente;
        DestruirNodo(eliminado);
        lista->longitud--;
    }
}

/*
Eliminar el último elemento de una lista:
    - Compruebo que la lista no esté vacía
    - Compruebo si la lista sólo tiene un elemento. En ese caso elimino el nodo dejando la lista vacía y decremento la longitud
    - Obtengo el penúltimo elemento
    - Guardar su referencia para destruir el nodo de memoria
    - Hacemos que su siguiente apunte a NULL
    - Destruir el nodo eliminado
    - Decrementar la longitud de la lista
*/
void EliminarFinal(Lista* lista) {
    if (lista->cabeza) {
        if(lista->cabeza->siguiente) {
            Nodo* puntero = lista->cabeza;
            while (puntero->siguiente->siguiente) {
                puntero = puntero->siguiente;
            }

            Nodo* eliminado = puntero->siguiente;
            puntero->siguiente = NULL;
            DestruirNodo(eliminado);
            lista->longitud--;
        } else {
            Nodo* eliminado = lista->cabeza;
            lista->cabeza = NULL;
            DestruirNodo(eliminado);
            lista->longitud--;
        }

    }
}

/*
Eliminar el elemento número 'n' de la lista:
    - Compruebo que la lista no esté vacía
    - Compruebo si me piden eliminar el primer elemento. En ese caso directamente lo elimino
    - Compruebo si me piden eliminar un libro que no existe porque la lista no es tan larga
    - Recorro la lista hasta el elemento anterior al que quiero eliminar
    - Marco el siguiente nodo como nodo a eliminar
    - Conecto el siguiente del nodo anterior al eliminado, con el siguiente del nodo eliminado, así me lo salto
    - Destruyo el nodo a eliminar
    - Decremento la longitud de la lista
*/
void EliminarElemento(int n, Lista* lista) {
    if (lista->cabeza) {
        if (n == 0) {
            Nodo* eliminado = lista->cabeza;
            lista->cabeza = lista->cabeza->siguiente;
            DestruirNodo(eliminado);
            lista->longitud--;
        } else if (n < lista->longitud) {
            Nodo* puntero = lista->cabeza;
            int posicion = 0;
            while(posicion < (n-1)) {
                puntero = puntero->siguiente;
                posicion++;
            }
            Nodo* eliminado = puntero->siguiente;
            puntero->siguiente = eliminado->siguiente;
            DestruirNodo(eliminado);
            lista->longitud--;
        }
    }
}
