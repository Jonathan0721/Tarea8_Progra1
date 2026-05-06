/*
* ESTUDIANTE: JONATHAN DAVID CACERES
* CARNET: 7691-25-11564
* MATERIA: PROGRAMACION 1
* TAREA 8 - CONEXION MYSQL (CRUD COMPLETO)
*/

#include <iostream>
#include <string>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

void limpiar() { system("cls"); }

int main() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "root", "Proverbios17:17");
        con->setSchema("db_escuela");

        int opcion;
        do {
            limpiar();
            cout << "====================================================" << endl;
            cout << "       SISTEMA ACADEMICO - REGISTRO UMG             " << endl;
            cout << "       JONATHAN CACERES - 7691-25-11564             " << endl;
            cout << "====================================================" << endl;
            cout << " 1. Ingresar Nuevo Estudiante" << endl;
            cout << " 2. Ver Estudiantes Registrados" << endl;
            cout << " 3. Salir" << endl;
            cout << "----------------------------------------------------" << endl;
            cout << " Seleccione una opcion: "; cin >> opcion;

            if (opcion == 1) {
                string carnet, nom, ape, dir, fecha;
                int tel, opcionSangre, id_sangre;

                limpiar();
                cout << ">>> FORMULARIO DE INSCRIPCION <<<" << endl;
                cout << "---------------------------------" << endl;
                cout << " Carnet: "; cin >> carnet;
                cout << " Nombres: "; cin.ignore(); getline(cin, nom);
                cout << " Apellidos: "; getline(cin, ape);
                cout << " Direccion: "; getline(cin, dir);
                cout << " Telefono: "; cin >> tel;
                cout << " Fecha Nac. (AAAA-MM-DD): "; cin >> fecha;

                cout << "\n Seleccione Tipo de Sangre:" << endl;
                cout << " 1. O Positivo (O+)\n 2. O Negativo (O-)\n 3. A Positivo (A+)\n 4. B Positivo (B+)" << endl;
                cout << " Elija una opcion (1-4): "; cin >> opcionSangre;
                id_sangre = (opcionSangre >= 1 && opcionSangre <= 4) ? opcionSangre : 1;

                sql::PreparedStatement* pstmt = con->prepareStatement(
                    "INSERT INTO estudiantes(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES (?,?,?,?,?,?,?)");

                pstmt->setString(1, carnet);
                pstmt->setString(2, nom);
                pstmt->setString(3, ape);
                pstmt->setString(4, dir);
                pstmt->setInt(5, tel);
                pstmt->setString(6, fecha);
                pstmt->setInt(7, id_sangre);

                pstmt->executeUpdate();
                cout << "\n [!] EXITO: Estudiante registrado correctamente." << endl;
                delete pstmt;
                system("pause");
            }
            else if (opcion == 2) {
                limpiar();
                cout << ">>> LISTADO DE ESTUDIANTES REGISTRADOS <<<" << endl;
                cout << "--------------------------------------------------------------------------------" << endl;

                sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM estudiantes");
                sql::ResultSet* res = pstmt->executeQuery();

                while (res->next()) {
                    cout << "ID: " << res->getInt("id_estudiante") << " | ";
                    cout << "Carnet: " << res->getString("codigo") << " | ";
                    cout << "Nombre: " << res->getString("nombres") << " " << res->getString("apellidos") << endl;
                    cout << "Tel: " << res->getString("telefono") << " | ";
                    cout << "Fecha Nac: " << res->getString("fecha_nacimiento") << endl;
                    cout << "--------------------------------------------------------------------------------" << endl;
                }

                delete res;
                delete pstmt;
                system("pause");
            }
        } while (opcion != 3);

        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "\n [X] ERROR: " << e.what() << endl;
        system("pause");
    }
    return 0;
}