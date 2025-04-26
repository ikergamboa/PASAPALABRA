#include <stdio.h>
#include <sqlite3.h>

// Declaración anticipada de funciones
int callback(void *data, int argc, char **argv, char **azColName);
int insertar_usuario(sqlite3 *db, const char *usuario, const char *contrasena);

int main(int argc, char* argv[]) {
    sqlite3 *db;
    char *err_msg = 0;
    
    // Abrir o crear la base de datos
    int rc = sqlite3_open("ejemplo.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    // Crear una tabla
    const char *sql = "CREATE TABLE IF NOT EXISTS Usuarios(Usuario TEXT PRIMARY KEY, Contraseña TEXT);";
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    // Insertar datos usando la función
    
    // Consultar datos

    
    // Cerrar la base de datos
    sqlite3_close(db);
    
    return 0;
}

// Función para insertar usuarios
int insertar_usuario(sqlite3 *db, const char *usuario, const char *contrasena) {
    char *err_msg = 0;
    char sql[256];
    
    // Preparar la sentencia SQL
    snprintf(sql, sizeof(sql), 
             "INSERT INTO Usuarios(Usuario, Contraseña) VALUES('%s', '%s');",
             usuario, contrasena);
    
    // Ejecutar la inserción
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al insertar: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    return rc;
}

// Función callback para mostrar resultados
int callback(void *data, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++) {
        printf("%-12s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("------------------------\n");
    return 0;
}