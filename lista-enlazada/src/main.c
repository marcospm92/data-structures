#include "lista.h"
#include "libro.h"
#include <string.h>

int main() {
    Lista listaLibros;
    Libro libro1, libro2;

    strcpy(libro1.titulo, "Los juegos del hambre");
    strcpy(libro1.autor, "Suzanne Collins");
    strcpy(libro1.isbn, "123456789012");

    strcpy(libro2.titulo, "Ready Player One");
    strcpy(libro2.autor, "Ernest Cline");
    strcpy(libro2.isbn, "111112222333");

    InsertarPrincipio(&listaLibros, &libro2);
    printf("Longitud: %d\n", Contar(&listaLibros));
    InsertarFinal(&listaLibros, &libro1);
    printf("Longitud: %d\n", Contar(&listaLibros));


    return 0;
}
