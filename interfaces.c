#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interfaces.h"
#include "bbdd.h"

void primeraInterfaz(){
    int opcion;

    while (1) {
        printf("-------VENTANA DE INICIO-------\n");
        printf("|                             |\n");
        printf("|  Bienvenido a Pasapalabra   |\n");
        printf("|                             |\n");
        printf("|      1. Iniciar sesion      |\n");
        printf("|      2. Registrarse         |\n");
        printf("|                             |\n");
        printf("-------------------------------\n");
        printf("\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            iniciarSesion();
            return;
        case 2:
            registerUser();
            return;
        default:
            printf("Opción inválida. Intenta de nuevo.\n");
        }
    }
}

void iniciarSesion() {
    char username[50];
    char password[50];

    printf("\n---VENTANA DE INICIO DE SESION---\n");
    printf("Nombre de usuario: ");
    scanf("%s", username);

    if (strcmp(username, "salir") == 0) exit(0);
    if (strcmp(username, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    printf("Contrasenya: ");
    scanf("%s", password);

    if (strcmp(password, "salir") == 0) exit(0);
    if (strcmp(password, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    //TODO Falta verificar si el usuario y la contraseña son correctos
    //TODO Falta verificar si el usuario existe

    printf("¡Inicio de sesión exitoso!\n");
}

void registerUser() {
    char username[50];
    char password[50];
    char confirmPassword[50];

    printf("\n---VENTANA DE REGISTRO---\n");
    printf("Nombre de usuario: ");
    scanf("%s", username);

    if (strcmp(username, "salir") == 0) exit(0); // Permitir salir
    if (strcmp(username, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    printf("Contraseña: ");
    scanf("%s", password);

    if (strcmp(password, "salir") == 0) exit(0); // Permitir salir
    if (strcmp(password, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    printf("Confirmar contraseña: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, "salir") == 0) exit(0); // Permitir salir
    if (strcmp(confirmPassword, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    if (strcmp(password, confirmPassword) != 0) {
        printf("Las contraseñas no coinciden. Intenta de nuevo.\n");
        registerUser();
        return;
    }

    printf("¡Registro exitoso!\n");

    //TODO Falta guardar el usuario y la contraseña en un archivo o base de datos
    //TODO Falta verificar si el usuario ya existe

}

void ventanaPrincipal(){
    int opcion;

    while (1) {
        printf("\n---VENTANA PRINCIPAL---\n");
        printf("1. Un jugador\n");
        printf("2. Multijugador\n");
        printf("3. Ranking Global\n");
        printf("4. Salir\n");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            return;
        case 2:
            return;
        case 3:
            return;
        case 4:
          exit(0);
        default:
            printf("Opción inválida. Intenta de nuevo.\n");
        }
    }
}

void rankingGlobal() {
    printf("\n---RANKING GLOBAL---\n");

    int count = 0;
    while(count < 50){
        printf("Usuario %d:\n", count);
        count++;
    }

    printf("Ranking global no implementado.\n");
}