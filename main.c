#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mostrarVentanaInicio();

void mostrarVentanaInicio() {
    int opcion;

    while (1) {
        printf("\n---VENTANA DE INICIO---\n");
        printf("¡Bienvenido a Pasapalabra!\n");
        printf("1. Iniciar sesión\n");
        printf("2. Registrarse\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                iniciarSesion();
                return; // Salimos de esta función después de iniciar sesión
            case 2:
                registrarse();
                return; // Salimos de esta función después de registrarse
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
    }
}
