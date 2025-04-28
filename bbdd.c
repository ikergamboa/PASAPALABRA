#include <stdio.h>
#include "sqlite3.h"
#include <stdbool.h>
#include "bbdd.h"
#include <string.h> 


// Función para crear la tabla de usuarios
bool crear_tabla_usuarios(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Usuarios("
        "Usuario TEXT PRIMARY KEY, "
        "Contrasenya TEXT NOT NULL, "
        "FechaCreacion TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
        "Points INTEGER DEFAULT 0);";

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al crear tabla: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}


// Función para insertar usuarios
int insertar_usuario(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Usuarios(Usuario, Contrasenya) VALUES(?, ?);";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error preparando la consulta: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (rc == SQLITE_DONE) {
        return SQLITE_DONE; // Éxito
    } else {
        fprintf(stderr, "Error al insertar usuario: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR; // Fallo
    }
}


// Función para mirar a ver si los nombres de usuario ya existen en la tabla
bool usuario_existe_seguro(sqlite3 *db, const char *usuario) {
    sqlite3_stmt *stmt;
    bool existe = false;
    
    const char *sql = "SELECT 1 FROM Usuarios WHERE Usuario = ? LIMIT 1;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = true;
    }
    
    sqlite3_finalize(stmt);
    return existe;
}

// Función para verificar si la contraseña coincide con la del usuario
bool verificar_contrasena(sqlite3 *db, const char *usuario, const char *contrasena) {
    sqlite3_stmt *stmt;
    bool coincide = false;
    
    // Consulta para obtener el hash de la contraseña del usuario
    const char *sql = "SELECT Contrasenya FROM Usuarios WHERE Usuario = ? LIMIT 1;";
    
    // Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return false;
    }
    
    // Vincular el parámetro del usuario
    sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
    
    // Ejecutar y verificar
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *contrasena_almacenada = (const char *)sqlite3_column_text(stmt, 0);
        
        // Comparar las contraseñas (en texto plano - NO recomendado para producción)
        if (strcmp(contrasena, contrasena_almacenada) == 0) {
            coincide = true;
        }
    }
    
    // Liberar recursos
    sqlite3_finalize(stmt);
    return coincide;
}

int mostrarRanking(sqlite3 *db) {
  sqlite3_stmt *stmt;
  const char *sql = "SELECT Usuario, Points FROM Usuarios ORDER BY Points DESC LIMIT 10;";
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    printf("\n----------- RANKING ------------\n");
    printf("| Usuario\t|\tPuntos |\n");
    printf("--------------------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *username = (const char *)sqlite3_column_text(stmt, 0);
        int points = sqlite3_column_int(stmt, 1);
        printf("| %-14s| %10d   |\n", username, points);
    }
    printf("--------------------------------\n");

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}