#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "interfaces.h"
#include "bbdd.h"
#include "diccionario.h"

sqlite3 *db = NULL;
char usuarioLogueado[50] = {0};

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

    printf("|     Nombre de usuario: ");
    if (scanf("%49s", username) != 1) return;

    if (strcmp(username, "salir") == 0) exit(0);
    if (strcmp(username, "volver") == 0) {
        primeraInterfaz();
        return;
    }

    printf("|     Contrasenya: ");
    if (scanf("%49s", password) != 1) return;

    if (strcmp(password, "salir") == 0) exit(0);
    if (strcmp(password, "volver") == 0) {
        primeraInterfaz();
        return;
    }

    if (sqlite3_open("basedatos.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (!usuario_existe_seguro(db, username)) {
        printf("El usuario o la contrasenya son incorrectos.\n");
        sqlite3_close(db);
        iniciarSesion();
        return;
    }

    if (verificar_contrasena(db, username, password)) {
        printf("Inicio de sesion exitoso\n");
        // Guardar usuario logueado globalmente
        strcpy(usuarioLogueado, username);
        ventanaPrincipal();
    } else {
        printf("El usuario o la contrasenya son incorrectos.\n");
        iniciarSesion();
    }

    // NO cerrar la BD aquí, se cerrará al salir de la app
}


bool registerUser() {
    char username[50];
    char password[50];
    char confirmPassword[50];

    // Abrir la base de datos
    if (sqlite3_open("basedatos.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return false;
    }

    printf("\n--- VENTANA DE REGISTRO ---\n");

    while (1) {
        printf("|\n");
        printf("|   Nombre de usuario: ");
        if (scanf("%49s", username) != 1) {
            sqlite3_close(db);
            return false;
        }

        // Comandos especiales
        if (strcmp(username, "salir") == 0) {
            sqlite3_close(db);
            exit(0);
        }
        if (strcmp(username, "volver") == 0) {
            sqlite3_close(db);
            primeraInterfaz();
            return false;
        }

        printf("|   Contrasenya: ");
        if (scanf("%49s", password) != 1) {
            sqlite3_close(db);
            return false;
        }

        // Comandos especiales
        if (strcmp(password, "salir") == 0) {
            sqlite3_close(db);
            exit(0);
        }
        if (strcmp(password, "volver") == 0) {
            sqlite3_close(db);
            primeraInterfaz();
            return false;
        }

        printf("|   Confirmar contrasenya: ");
        if (scanf("%49s", confirmPassword) != 1) {
            sqlite3_close(db);
            return false;
        }

        // Comandos especiales
        if (strcmp(confirmPassword, "salir") == 0) {
            sqlite3_close(db);
            exit(0);
        }
        if (strcmp(confirmPassword, "volver") == 0) {
            sqlite3_close(db);
            primeraInterfaz();
            return false;
        }

        // Validar que las contraseñas coinciden
        if (strcmp(password, confirmPassword) != 0) {
            printf("\n---------------------------\n");
            printf("Las contrasenyas no coinciden. Intenta de nuevo.\n");
            continue;
        }

        // Validar que el usuario no exista
        if (usuario_existe_seguro(db, username)) {
            printf("\n---------------------------\n");
            printf("El usuario ya existe. Intenta con otro.\n");
            continue;
        }

        // Insertar el nuevo usuario en la base de datos
        if (insertar_usuario(db, username, password) == SQLITE_DONE) {
            printf("\n---------------------------\n");
            printf("Registro exitoso\n");

            // Guardar el nombre del usuario logueado
            strcpy(usuarioLogueado, username);
            ventanaPrincipal();  // Ir a la ventana principal
            return true;
        } else {
            printf("\n---------------------------\n");
            fprintf(stderr, "Error al registrar usuario.\n");
            sqlite3_close(db);
            return false;
        }
    }
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
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (opcion) {
        case 1:
            roscoUnJugador(db, usuarioLogueado);
            break;
        case 2:
            // Implementa la función para multijugador cuando esté lista
            break;
        case 3:
            rankingGlobal(db);
            break;
        case 4:
            sqlite3_close(db);  // Cerrar BD al volver al inicio (opcional)
            primeraInterfaz();
            return;
        case 5:
            sqlite3_close(db);  // Cerrar BD al salir
            exit(0);
        default:
            printf("Entrada invalida. Por favor, elige una opcion valida (1,2,3,4 o 5).\n");
            break;
        }
    }
}


void roscoUnJugador() {
    char input[20];
    char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
    int total_letras = sizeof(letras) / sizeof(letras[0]);
	const char *current_letra = letras;
    const char *end_letra = letras + sizeof(letras) / sizeof(letras[0]);
    int respuestasCorrectas = 0;
	int preguntasRespondidas = 0;

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
    while (preguntasRespondidas < dict.totalPreguntas) {
        if (current_letra >= end_letra) {
            current_letra = letras;
        }

        int indice = buscar_indice_letra(*current_letra);
        if (dict.almacen[indice].entradas[0].status != 0) {
            current_letra++;
            continue;
        }

        printf("\n   V   X   Y   Z   A   B   C   \n");
        printf("   U                       D   \n");
        printf("   T                       E   \n");
        printf("   S                       F   \n");
        printf("   R                       G   \n");
        printf("   Q                       H   \n");
        printf("   P   O   N   M   L   J   I   \n");

        printf("\nLetra %c:", *current_letra);
        printf("\nDefinicion: %s", dict.almacen[indice].entradas[0].definicion);
        printf("\nEscribe tu respuesta: ");
        scanf("%19s", input);

        char upperInput[20];
        strcpy(upperInput, input);
        str_toupper(upperInput);

        if (strcmp(upperInput, "PASAR") == 0) {
            printf("Saltando la letra %c...\n", *current_letra);
            current_letra++;
        } else if (strcmp(upperInput, "SALIR") == 0) {
            exit(0);
        } else {

          	char upperWord[50];
            strcpy(upperWord, dict.almacen[indice].entradas[0].palabra);
            str_toupper(upperWord);

            if (strcmp(upperInput, upperWord) == 0) {
                printf("Respuesta CORRECTA\n");
                dict.almacen[indice].entradas[0].status = 1;
				respuestasCorrectas++;
            } else if (strcmp(upperInput, "PASAPALABRA") == 0) {
                printf("Pasapalabra!\n");
                dict.almacen[indice].entradas[0].status = 0;
            } else {
                printf("Respuesta INCORRECTA\n");
                dict.almacen[indice].entradas[0].status = 2;
            }
            preguntasRespondidas++;
            current_letra++;
        }
    }

    printf("\n¡Has terminado el rosco!\n");
    printf("Respuestas correctas: %d\n", respuestasCorrectas);

    // Sumar puntos
    if (insertar_puntos_usuario(db, usuarioLogueado, respuestasCorrectas*10)) {
        printf("¡Se han sumado tus puntos al ranking!\n");
    } else {
        printf("%s", usuarioLogueado);
        printf("Error al guardar tus puntos.\n");
    }

	// Esperar que el usuario presione ENTER antes de volver al menú
    printf("\nPresiona ENTER para volver a la ventana principal...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Limpiar el buffer
    getchar();  // Esperar que el usuario presione ENTER
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