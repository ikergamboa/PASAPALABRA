#include <stdio.h>
#include "sqlite3.h"
#include <stdbool.h>
#include "bbdd.h"


// Función para crear la tabla de usuarios
bool crear_tabla_usuarios(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Usuarios("
        "Username TEXT PRIMARY KEY, "
        "Password TEXT NOT NULL, "
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
    char *err_msg = 0;
    char sql[512];

    snprintf(sql, sizeof(sql),
             "INSERT OR REPLACE INTO Usuarios(Username, Password, Points) VALUES('%s', '%s', 0);",
             username, password);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al insertar: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return rc;
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

int mostrarRanking(sqlite3 *db) {
  sqlite3_stmt *stmt;
  const char *sql = "SELECT Username, Points FROM Usuarios ORDER BY Points DESC LIMIT 10;";
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar consulta: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    printf("\n--- RANKING ---\n");
    printf("Usuario\t\tPuntos\n");
    printf("-------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *username = (const char *)sqlite3_column_text(stmt, 0);
        int points = sqlite3_column_int(stmt, 1);
        printf("%s\t\t%d\n", username, points);
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}