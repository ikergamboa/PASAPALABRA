#ifndef DICCIONARIO_H
#define DICCIONARIO_H

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

Almacen almacen[25]; // Almacen global para guardar las palabras por letra.

int buscar_indice_letra(char letra);
void crearAlmacenPorLetra(char letra, const char *palabra, const char *definicion);
void leerCSV(const char *filename);
DiccionarioJuego crearDiccionarioJuego();
void imprimirDiccionarioJuego(DiccionarioJuego dict);

#endif //DICCIONARIO_H
