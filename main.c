#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interfaces.h"

#define MAX_LINE_LENGTH 512

void leerCSV(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0; // Remove newline character

    char *letra = strtok(line, ";");      // Get first part before ;
    char *palabra = strtok(NULL, ";");    // Get second part before ;
    char *definicion = strtok(NULL, ";"); // Get last part

    if (letra && palabra && definicion) {
        // Agregar a la estructura de datos donde se guardan las palabras
    }
}
}

int main(void) {
    primeraInterfaz();

    return 0;
}
