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

    printf("¡Inicio de sesion exitoso!\n");
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

    printf("Contrasenya: ");
    scanf("%s", password);

    if (strcmp(password, "salir") == 0) exit(0); // Permitir salir
    if (strcmp(password, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    printf("Confirmar contrasenya: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, "salir") == 0) exit(0); // Permitir salir
    if (strcmp(confirmPassword, "volver") == 0) primeraInterfaz(); // Permitir volver a la ventana de inicio

    if (strcmp(password, confirmPassword) != 0) {
        printf("Las contrasenyas no coinciden. Intenta de nuevo.\n");
        registerUser();
        return;
    }

    sqlite3 *db;  // Puntero a la conexión.
    int rc;       // Código de retorno.

    // 1. Abrir la conexión a la BD (crea el archivo si no existe).
    rc = sqlite3_open("basedatos.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la BD: %s\n", sqlite3_errmsg(db));
    }

    // 2. Llamar a la función para crear la tabla.
    if (!crear_tabla_usuarios(db)) {
        fprintf(stderr, "Error al crear la tabla.\n");
        sqlite3_close(db);  // Cerrar conexión antes de salir.
    }

    // 3. Cerrar la conexión cuando ya no se necesite.
    sqlite3_close(db);

    printf("Registro exitoso\n");

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
            roscoUnJugador();
        case 2:
            return;
        case 3:
            rankingGlobal();
        case 4:
          exit(0);
        default:
            printf("Opción inválida. Intenta de nuevo.\n");
        }
    }
}

void roscoUnJugador() {

    char input[20];

    printf("\n---VENTANA UN JUGADOR---\n\n");
    
    printf("    U V X Y Z A B C D\n");
    printf("    T           E\n");
    printf("    S     ¡Pasapalabra!     F\n");
    printf("          -------\n");
    printf("    R     |  JUGAR  |     G\n");
    printf("          -------\n");
    printf("    Q           H\n");
    printf("\n    P O Ñ N M L J I\n");

    printf("\nEscribe \"JUGAR\" para comenzar: ");
    scanf("%s", input);

    if (strcmp(input, "JUGAR") == 0) {
        printf("\n¡Correcto! Vamos a la letra A.\n");
        
    } else {
        printf("\nNo escribiste \"JUGAR\". Intenta de nuevo.\n");
    }
     
    return 0;
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

