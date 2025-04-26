#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "register.h"

void registerUser() {
  char username[50];
  char password[50];
  char confirmPassword[50];

  printf("\n---VENTANA DE REGISTRO---\n");
  printf("Nombre de usuario: ");
  scanf("%s", username);

  if (strcmp(username, "exit") == 0) exit(0); // Permitir salir

  printf("Contraseña: ");
  scanf("%s", password);

  printf("Confirmar contraseña: ");
  scanf("%s", confirmPassword);

  if (strcmp(username, "exit") == 0) exit(0); // Permitir salir

  if (strcmp(password, confirmPassword) != 0) {
    printf("Las contraseñas no coinciden. Intenta de nuevo.\n");
    registerUser();
    return;
  }

  printf("¡Registro exitoso!\n");

  //TODO Falta guardar el usuario y la contraseña en un archivo o base de datos
  //TODO Falta verificar si el usuario ya existe

}