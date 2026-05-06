CREATE DATABASE db_escuela;
USE db_escuela;

CREATE TABLE tipos_sangre (
    id_tipo_sangre INT PRIMARY KEY AUTO_INCREMENT,
    sangre VARCHAR(5)
);

CREATE TABLE estudiantes (
    id_estudiante INT PRIMARY KEY AUTO_INCREMENT,
    carnet VARCHAR(20),
    nombres VARCHAR(60),
    apellidos VARCHAR(60),
    direccion VARCHAR(100),
    telefono INT,
    fecha_nacimiento DATE,
    id_tipo_sangre INT,
    FOREIGN KEY (id_tipo_sangre) REFERENCES tipos_sangre(id_tipo_sangre)
);

-- Insertar datos iniciales necesarios
INSERT INTO tipos_sangre (sangre) VALUES ('O+'), ('O-'), ('A+'), ('B+');