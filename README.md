# Tarea 8 - Sistema de Registro de Estudiantes (C++ & MySQL)

## Datos del Estudiante
* **Nombre:** Jonathan David Cáceres
* **Carnet:** 7691-25-11564
* **Curso:** Programación 1
* **Universidad:** Mariano Gálvez de Guatemala

## Descripción del Proyecto
Este proyecto es una aplicación de consola desarrollada en C++ que se conecta a una base de datos local en MySQL. Permite el registro de estudiantes y la consulta de los mismos, validando la integridad de los datos mediante menús de selección (como el tipo de sangre).

## Tecnologías Utilizadas
* **Lenguaje:** C++ (Visual Studio 2022)
* **Base de Datos:** MySQL Server 8.0
* **Conector:** MySQL Connector/C++ 8.0
* **Arquitectura:** x64 (Release)

## Instrucciones para Compilación
Para que el proyecto compile correctamente, se deben configurar las siguientes rutas en las Propiedades del Proyecto:
1. **C/C++ -> General -> Directorios de inclusión adicionales:** Carpeta `include` y `include/jdbc`.
2. **Vinculador -> General -> Directorios de bibliotecas adicionales:** Carpeta `lib`.
3. **Vinculador -> Entrada -> Dependencias adicionales:** Agregar `mysqlcppconn.lib`.

*Nota: Es indispensable tener los archivos .dll (mysqlcppconn-10-vs14.dll, libcrypto-3-x64.dll y libssl-3-x64.dll) en la carpeta de ejecución.*