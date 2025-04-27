#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "interfaces.h"

#define MAX_LINE_LENGTH 512

typedef struct {
  char letra;
  char palabra[50];
  char definicion[256];
  int status; // 0 = no respondida, 1 = correcta, 2 = incorrecta
} Entrada;

typedef struct {
  Entrada entradas[10]; // Por ahora 10 palabras por letra por nuestro CSV. Expandir cuando sea necesario
  int size;
} Almacen; // Esta estructura almacena las palabras por cada letra.

typedef struct {
   Almacen almacen[25]; // 25 letras del alfabeto.
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
      crearAlmacenPorLetra(letra[0], palabra, definicion);
        }
    }
}

DiccionarioJuego crearDiccionarioJuego() {
    DiccionarioJuego diccionario = {0};
    srand(time(NULL));

    for (int i = 0; i < 26; i++) {
        if (almacen[i].size > 0) {
            int randIndex = rand() % almacen[i].size; // se selecciona un valor random entre 0 y el tamaño de la lista de palabras -1 (10)

            Entrada entradaSeleccionada = almacen[i].entradas[randIndex]; // se crea una entrada con la palabra y definición seleccionada
            diccionario.almacen[i].entradas[0] = entradaSeleccionada;
            diccionario.almacen[i].size = 1;
            diccionario.totalPreguntas++;
        }
    }

    // ACCESO A LAS PALABRAS Y DEFINICIONES DEL DICCIONARIO CREADO

    // Para la palabra
    //diccionario.almacen[i].entradas[0].palabra
    // Para la definición
    //diccionario.almacen[i].entradas[0].definicion

    return diccionario;
}

int main(void) {

    //primeraInterfaz();
    roscoUnJugador();

    leerCSV("palabras.csv");
    DiccionarioJuego juego = crearDiccionarioJuego();

    for (int i = 0; i < 26; i++) {
        if (almacen[i].size > 0) {
            printf("\nLetra %c (%d palabras):\n", 'A' + i, almacen[i].size);
            for (int j = 0; j < almacen[i].size; j++) {
                printf("  Palabra: %s\n", almacen[i].entradas[j].palabra);
                printf("  Definicion: %s\n", almacen[i].entradas[j].definicion);
                printf("---\n");
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (juego.almacen[i].size > 0) {
            printf("\nLetra %c (%d palabras):\n", 'A' + i, juego.almacen[i].size);
            for (int j = 0; j < juego.almacen[i].size; j++) {
                printf("  Palabra: %s\n", juego.almacen[i].entradas[j].palabra);
                printf("  Definicion: %s\n", juego.almacen[i].entradas[j].definicion);
                printf("---\n");
            }
        }
    }



    return 0;
}
