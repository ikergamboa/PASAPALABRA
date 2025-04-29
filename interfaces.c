#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "interfaces.h"
#include "bbdd.h"
#include "diccionario.h"

void str_toupper(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void primeraInterfaz(){
    int opcion;

    while (1) {
        printf("\n------ VENTANA DE INICIO ------\n");
        printf("|                             |\n");
        printf("|  Bienvenido a Pasapalabra   |\n");
        printf("|                             |\n");
        printf("|      1. Iniciar sesion      |\n");
        printf("|      2. Registrarse         |\n");
        printf("|      3. Salir               |\n");
        printf("|                             |\n");
        printf("-------------------------------\n");
        printf("\n");
        printf("Elige una opcion: ");
    
        if (scanf("%d", &opcion) != 1) {
        printf("Entrada invalida. Por favor, elige una opcion valida (1,2 o 3).\n");
        // Limpiar el buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        continue; // Volver a mostrar el menú
        }

        switch (opcion) {
        case 1:
            iniciarSesion();
            return;
        case 2:
            registerUser();
            return;
        case 3:
            exit(0);
        default:
            printf("Entrada invalida. Por favor, elige una opcion valida (1,2 o 3).\n");
            break;
        }
    }
}

void iniciarSesion() {
    char username[50];
    char password[50];

    printf("\n--- VENTANA DE INICIO DE SESION ---\n");

    // Leer nombre de usuario
    printf("|\n");
    printf("|     Nombre de usuario: ");
    if (scanf("%49s", username) != 1) return;

    if (strcmp(username, "salir") == 0) exit(0);
    if (strcmp(username, "volver") == 0) {
        primeraInterfaz(); // Permitir volver
        return;
    }

    // Leer contraseña
    printf("|     Contrasenya: ");
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
        printf("|\n");
        printf("-----------------------------------\n");
        printf("El usuario o la contrasenya son incorrectos.\n");
        sqlite3_close(db);
        iniciarSesion();
        return;
    }

    // Verificar si la contraseña es correcta
    if (verificar_contrasena(db, username, password)) {
        printf("|\n");
        printf("-----------------------------------\n");
        printf("Inicio de sesion exitoso\n");
        ventanaPrincipal();
    } else {
        printf("|\n");
        printf("-----------------------------------\n");
        printf("El usuario o la contrasenya son incorrectos.\n");
        iniciarSesion();
    }

    sqlite3_close(db);
}

bool registerUser() {
    char username[50];
    char password[50];
    char confirmPassword[50];

    printf("\n--- VENTANA DE REGISTRO ---\n");
    
    // 1. Obtener inputs
    printf("|\n");
    printf("|   Nombre de usuario: ");
    if (scanf("%49s", username) != 1) return false;
    
    if (strcmp(username, "salir") == 0) exit(0);
    if (strcmp(username, "volver") == 0) {
    primeraInterfaz();
    return false;
    }

    printf("|   Contrasenya: ");
    if (scanf("%49s", password) != 1) return false;
    
    if (strcmp(password, "salir") == 0) exit(0);
    if (strcmp(password, "volver") == 0) {
    primeraInterfaz();
    return false;
    }

    printf("|   Confirmar contrasenya: ");
    if (scanf("%49s", confirmPassword) != 1) return false;
    
    if (strcmp(confirmPassword, "salir") == 0) exit(0);
    if (strcmp(confirmPassword, "volver") == 0) {
    primeraInterfaz();
    return false;
    }

    // 2. Validaciones
    if (strcmp(password, confirmPassword) != 0) {
        printf("|");
        printf("\n---------------------------\n");
        printf("Las contrasenyas no coinciden.\n");
        registerUser();
    }

    // 3. Operaciones con BD
    sqlite3 *db;
    if (sqlite3_open("basedatos.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error al abrir BD: %s\n", sqlite3_errmsg(db));
        return false;
    }

    bool exito = false;

    if (usuario_existe_seguro(db, username)) {
        printf("|");
        printf("\n---------------------------\n");
        printf("El usuario ya existe.\n");
        goto cleanup;
    }

    if (insertar_usuario(db, username, password) == SQLITE_DONE) {
        printf("\n---------------------------\n");
        printf("Registro exitoso\n");
        exito = true;
        ventanaPrincipal();
    } else {
        printf("\n---------------------------\n");
        fprintf(stderr, "Error al registrar usuario.\n");
    }

cleanup:
    sqlite3_close(db);
    registerUser();
    return exito;
}

void ventanaPrincipal(){
    int opcion;
        while(1){
        printf("\n--------- VENTANA PRINCIPAL ---------\n");
        printf("|\n");
        printf("|  1. Un jugador\n");
        printf("|  2. Multijugador\n");
        printf("|  3. Ranking Global\n");
        printf("|  4. Volver a la ventana de inicio\n");
        printf("|  5. Salir\n");
        printf("|\n");
        printf("-------------------------------------");
        printf("\nElige una opcion: ");

        if (scanf("%d", &opcion) != 1) {
        printf("Entrada invalida. Por favor, elige una opcion valida (1,2,3,4 o 5).\n");
        // Limpiar el buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        continue; // Volver a mostrar el menú
        }

        switch (opcion) {
        case 1:
            roscoUnJugador();
            break;
        case 2:
            return;
        case 3:
            rankingGlobal();
            break;
        case 4:
            primeraInterfaz();
            break;
        case 5:
            exit(0);
        default:
            printf("Entrada invalida. Por favor, elige una opcion valida (1,2 o 3).\n");
            break;
        }
        }
}

void roscoUnJugador() {
    char input[20];
    char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
    int total_letras = sizeof(letras) / sizeof(letras[0]);
    int i = 0;
    int respuestasCorrectas = 0;

    leerCSV("palabras.csv");
    DiccionarioJuego dict = crearDiccionarioJuego();

    printf("\n---------- UN JUGADOR -----------\n");
    printf("|                               |\n");
    printf("|   V   X   Y   Z   A   B   C   |\n");
    printf("|   U                       D   |\n");
    printf("|   T                       E   |\n");
    printf("|   S      Pasapalabra      F   |\n");
    printf("|   R                       G   |\n");
    printf("|   Q                       H   |\n");
    printf("|   P   O   N   M   L   J   I   |\n");
    printf("|                               |\n");
    printf("---------------------------------\n");

    // Bucle para validar entrada inicial
    while (1) {
        printf("\nEscribe \"JUGAR\" para comenzar, \"salir\" para salir o \"volver\" para volver: ");
        scanf("%19s", input);

        char upperInput[20];
        strcpy(upperInput, input);
        str_toupper(upperInput);

        if (strcmp(upperInput, "JUGAR") == 0) {
            break; // Salir del bucle y empezar el juego
        } else if (strcmp(upperInput, "SALIR") == 0) {
            exit(0);
        } else if (strcmp(upperInput, "VOLVER") == 0) {
            ventanaPrincipal();
            return;
        } else {
            printf("\nOpcion invalida.\n");
        }
    }

    printf("\nEmpezamos en la letra A.\n");

    // Bucle principal del rosco
    while (respuestasCorrectas < total_letras) {
        if (i >= total_letras) {
            i = 0;
        }

        int indice = buscar_indice_letra(letras[i]);
        if (dict.almacen[indice].entradas[0].status != 0) {
            i++;
            continue;
        }

        printf("\n   V   X   Y   Z   A   B   C   \n");
        printf("   U                       D   \n");
        printf("   T                       E   \n");
        printf("   S                       F   \n");
        printf("   R                       G   \n");
        printf("   Q                       H   \n");
        printf("   P   O   N   M   L   J   I   \n");

        printf("\nLetra %c:", letras[i]);
        printf("\nDefinicion: %s", dict.almacen[indice].entradas[0].definicion);
        printf("\nEscribe tu respuesta: ");
        scanf("%19s", input);

        char upperInput[20];
        strcpy(upperInput, input);
        str_toupper(upperInput);

        if (strcmp(upperInput, "PASAR") == 0) {
            printf("Saltando la letra %c...\n", letras[i]);
            i++;
        } else if (strcmp(upperInput, "SALIR") == 0) {
            exit(0);
        } else {

          	char upperWord[50];
            strcpy(upperWord, dict.almacen[indice].entradas[0].palabra);
            str_toupper(upperWord);

            if (strcmp(upperInput, upperWord) == 0) {
                printf("Respuesta CORRECTA\n");
                dict.almacen[indice].entradas[0].status = 1;
            } else {
                printf("Respuesta INCORRECTA\n");
                dict.almacen[indice].entradas[0].status = 2;
            }
            respuestasCorrectas++;
            i++;
        }
    }

    printf("\n¡Has terminado el rosco!\n");
}

void rankingGlobal() {
    sqlite3 *db;
    int rc = sqlite3_open("basedatos.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la BD: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Mostrar el ranking
    mostrarRanking(db);

    sqlite3_close(db);

    // Esperar que el usuario presione ENTER antes de volver al menú
    printf("\nPresiona ENTER para volver a la ventana principal...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Limpiar el buffer
    getchar();  // Esperar que el usuario presione ENTER
}