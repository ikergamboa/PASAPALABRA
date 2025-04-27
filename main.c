#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "interfaces.h"

#define MAX_LINE_LENGTH 512

typedef struct {
  char letra;
  char palabra[50];
  char definicion[256];
} Entrada;

typedef struct {
  Entrada entradas[10]; // Por ahora 10 palabras por letra por nuestro CSV. Expandir cuando sea necesario
  int size;
} Almacen; // Esta estructura almacena las palabras por cada letra.

typedef struct {
   Almacen almacen[26]; // 26 letras del alfabeto.
   int totalPreguntas;
} DiccionarioJuego; // Aquí guardamos las palabras que se utilizarán en el juego.

Almacen almacen[26]; // Almacen global para guardar las palabras por letra.

// FUNCION PARA IDENTIFICAR LA LETRA
int buscar_indice_letra(char letra) {
    letra = toupper(letra);
    if (letra >= 'A' && letra <= 'Z') {
        return letra - 'A';
    }
    return -1;
}

// FUNCION PARA CREAR EL ALMACEN POR LETRA
void crearAlmacenPorLetra(char letra, const char *palabra, const char *definicion){
  letra = toupper(letra);
  int indice = buscar_indice_letra(letra);

  if(indice != -1 && almacen[indice].size < 26) {
    Entrada *nuevaEntrada = &almacen[indice].entradas[almacen[indice].size];
    nuevaEntrada->letra = letra;
    strncpy(nuevaEntrada->palabra, palabra, 49); // 49 para dejar espacio para el \0
    strncpy(nuevaEntrada->definicion, definicion, 255);
    almacen[indice].size++;
  }
}


// FUNCION PARA LEER EL CSV
void leerCSV(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;

    char *letra = strtok(line, ";");
    char *palabra = strtok(NULL, ";");
    char *definicion = strtok(NULL, ";");

    if (letra && palabra && definicion) {
        // Agregar a la estructura de datos donde se guardan las palabras
    }
}
}

int main(void) {
    primeraInterfaz();

    return 0;
}
