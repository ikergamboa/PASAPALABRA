#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "register.h"

int main(void) {
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
            case 2:
                registerUser();
            default:
                printf("Opción inválida. Intenta de nuevo.\n");
        }
    }
}
