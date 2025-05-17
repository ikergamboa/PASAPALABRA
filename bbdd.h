#ifndef BBDD_H
#define BBDD_H

#include <stdio.h>
#include "sqlite3.h"
#include <stdbool.h>

// Declaración anticipada de funciones
bool usuario_existe_seguro(sqlite3 *db, const char *usuario);
bool verificar_contrasena(sqlite3 *db, const char *usuario, const char *contrasena);
int insertar_usuario(sqlite3 *db, const char *usuario, const char *contrasena);
bool crear_tabla_usuarios(sqlite3 *db);
int mostrarRanking(sqlite3 *db);
bool insertar_puntos_usuario(sqlite3 *db, const char *usuario, int puntos);

#endif //BBDD_H
