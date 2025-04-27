#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "interfaces.h"
#include "diccionario.h"

int main(void) {

    primeraInterfaz();

    leerCSV("palabras.csv");
    DiccionarioJuego dict = crearDiccionarioJuego();

    imprimirDiccionarioJuego(dict);

    return 0;
}
