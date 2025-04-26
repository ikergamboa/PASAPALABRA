#include <stdio.h>
#include <sqlite3.h>

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
    const char *sql = "CREATE TABLE IF NOT EXISTS Palabras(Id INT PRIMARY KEY, Palabra TEXT, Definicion TEXT);";
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    // Insertar datos
    sql = "INSERT INTO Palabras(Id, Palabra, Definicion) VALUES(1, 'Águila', 'Ave rapaz de gran tamaño');";
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    
    // Cerrar la base de datos
    sqlite3_close(db);
    
    return 0;
}
// Consultar datos (usando callback)
    sql = "SELECT * FROM Palabras;";
    
    int callback(void *data, int argc, char **argv, char **azColName) {
        for(int i = 0; i < argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }