#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"

void iniciarSesion() {
    char username[50];
    char password[50];

    printf("\n---VENTANA DE INICIO DE SESIÓN---\n");
    printf("Nombre de usuario: ");
    scanf("%s", username);

    if (strcmp(username, "exit") == 0) exit(0);

    printf("Contraseña: ");
    scanf("%s", password);

    if (strcmp(password, "exit") == 0) exit(0);

    //TODO Falta verificar si el usuario y la contraseña son correctos
    //TODO Falta verificar si el usuario existe

    printf("¡Inicio de sesión exitoso!\n");
}
