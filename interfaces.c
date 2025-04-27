#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interfaces.h"
#include "bbdd.h"
#include "diccionario.h"

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

    printf("\n--- VENTANA DE INICIO DE SESION ---\n");

    // Leer nombre de usuario
    printf("Nombre de usuario: ");
    if (scanf("%49s", username) != 1) return;

    if (strcmp(username, "salir") == 0) exit(0);
    if (strcmp(username, "volver") == 0) {
        primeraInterfaz(); // Permitir volver
        return;
    }

    // Leer contraseña
    printf("Contrasenya: ");
    if (scanf("%49s", password) != 1) return;

    if (strcmp(password, "salir") == 0) exit(0);
    if (strcmp(password, "volver") == 0) {
        primeraInterfaz(); // Permitir volver
        return;
    }

    // Abrir conexión a la base de datos
    sqlite3 *db;
    if (sqlite3_open("basedatos.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Verificar si el usuario existe
    if (!usuario_existe_seguro(db, username)) {
        printf("El usuario no existe.\n");
        sqlite3_close(db);
        return;
    }

    // Verificar si la contraseña es correcta
    if (verificar_contrasena(db, username, password)) {
        printf("¡Inicio de sesión exitoso!\n");
        // Aquí podrías continuar con tu flujo normal después de iniciar sesión.
    } else {
        printf("Contraseña incorrecta.\n");
    }

    sqlite3_close(db);
}

bool registerUser() {
    char username[50];
    char password[50];
    char confirmPassword[50];

    printf("\n---VENTANA DE REGISTRO---\n");
    
    // 1. Obtener inputs
    printf("Nombre de usuario: ");
    if (scanf("%49s", username) != 1) return false;
    
    if (strcmp(username, "salir") == 0) exit(0);
    if (strcmp(username, "volver") == 0) return false;

    printf("Contrasenya: ");
    if (scanf("%49s", password) != 1) return false;
    
    if (strcmp(password, "salir") == 0) exit(0);
    if (strcmp(password, "volver") == 0) return false;

    printf("Confirmar contrasenya: ");
    if (scanf("%49s", confirmPassword) != 1) return false;
    
    if (strcmp(confirmPassword, "salir") == 0) exit(0);
    if (strcmp(confirmPassword, "volver") == 0) return false;

    // 2. Validaciones
    if (strcmp(password, confirmPassword) != 0) {
        printf("Las contrasenyas no coinciden.\n");
        return false;
    }

    // 3. Operaciones con BD
    sqlite3 *db;
    if (sqlite3_open("basedatos.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
        return false;
    }

    bool exito = false;
    
    // Verificar creación de tabla
    if (!crear_tabla_usuarios(db)) {
        fprintf(stderr, "Error crítico: no se pudo crear la tabla.\n");
        goto cleanup;
    }


    if (usuario_existe_seguro(db, username)) {
        printf("El usuario ya existe.\n");
        goto cleanup;
    }

    if (insertar_usuario(db, username, password) == SQLITE_DONE) {
        printf("Registro exitoso\n");
        exito = true;
    } else {
        fprintf(stderr, "Error al registrar usuario *****.\n");
    }

cleanup:
    sqlite3_close(db);
    return exito;
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
    char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
    int total_letras = sizeof(letras) / sizeof(letras[0]);
    int i = 0;

    DiccionarioJuego dict = crearDiccionarioJuego();


    printf("\n---VENTANA UN JUGADOR---\n\n");
    
    printf("  V   X   Y   Z   A   B   C\n");
    printf("  U                       D\n");
    printf("  T     ¡Pasapalabra!     E\n");
    printf("          -------          \n");
    printf("  S     |  JUGAR  |       F\n");
    printf("  R       -------         G\n");
    printf("  Q                       H\n");
    printf("  P   O   N   M   L   J   I\n");

    printf("\nEscribe \"JUGAR\" para comenzar: ");
    scanf("%s", input);

    if (strcmp(input, "JUGAR") == 0) {
        printf("\n¡Correcto! Empezamos en la letra A.\n");

        while (i < total_letras) {
            printf("\nLetra %c: Escribe tu respuesta (o escribe \"pasar\" para saltar): ", letras[i]);
            scanf("%s", input);

            if (strcmp(input, "pasar") == 0) {
                printf("Saltando la letra %c...\n", letras[i]);
                i++; // Pasa a la siguiente letra
            } else {
                printf("Respuesta registrada para la letra %c.\n", letras[i]);
                i++; // También avanza
            }
        }

        printf("\n¡Has terminado el rosco!\n");
    } else {
        printf("\nNo escribiste \"JUGAR\". Terminando programa.\n");
    }

}

void rankingGlobal() {
    sqlite3 *db;
    int rc = sqlite3_open("basedatos.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la BD: %s\n", sqlite3_errmsg(db));
        return;
    }

    mostrarRanking(db);
    sqlite3_close(db);
}