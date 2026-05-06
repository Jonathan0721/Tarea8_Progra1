/*
* ESTUDIANTE: JONATHAN DAVID CACERES
* CARNET: 7691-25-11564
* TAREA 9 - VALIDACIONES Y SEGURIDAD (CRUD MEJORADO)
*/

#include <iostream>
#include <string>
#include <regex> // Para validar el formato E001
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

// --- FUNCIONES DE VALIDACIÓN ---

// Validar que solo sean letras y espacios (para nombres y apellidos)
bool esSoloLetras(string texto) {
    if (texto.empty()) return false;
    for (char c : texto) {
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;
}

// Validar formato de código (E + 3 números, máximo 4 caracteres)
bool validarCodigo(string cod) {
    const regex pattern("E[0-9]{3}");
    return regex_match(cod, pattern);
}

// Validar que el teléfono sean solo 8 números
bool validarTelefono(string tel) {
    const regex pattern("[0-9]{8}");
    return regex_match(tel, pattern);
}

// Validar formato fecha AAAA-MM-DD
bool validarFecha(string fecha) {
    const regex pattern("[0-9]{4}-[0-9]{2}-[0-9]{2}");
    return regex_match(fecha, pattern);
}

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
            cout << "       SISTEMA UMG - SEGURIDAD Y VALIDACION         " << endl;
            cout << "       JONATHAN CACERES - 7691-25-11564             " << endl;
            cout << "====================================================" << endl;
            cout << " 1. Ingresar Nuevo Estudiante (Con Validaciones)" << endl;
            cout << " 2. Ver Listado" << endl;
            cout << " 3. Salir" << endl;
            cout << "----------------------------------------------------" << endl;
            cout << " Seleccione una opcion: "; cin >> opcion;

            if (opcion == 1) {
                string carnet, nom, ape, dir, fecha;
                string tel; // Lo leemos como string para validarlo mejor
                int id_sangre;

                limpiar();
                cout << ">>> REGISTRO PROTEGIDO <<<" << endl;

                // VALIDACIÓN DE CÓDIGO
                do {
                    cout << " Codigo (Ej: E001): "; cin >> carnet;
                    if (!validarCodigo(carnet)) cout << " [!] Error: Formato invalido (E000) o mas de 4 caracteres.\n";
                } while (!validarCodigo(carnet));

                // VALIDACIÓN DE NOMBRES
                cin.ignore();
                do {
                    cout << " Nombres: "; getline(cin, nom);
                    if (!esSoloLetras(nom) || nom.length() > 60) cout << " [!] Error: Solo letras, max 60 caracteres.\n";
                } while (!esSoloLetras(nom) || nom.length() > 60);

                // VALIDACIÓN DE APELLIDOS
                do {
                    cout << " Apellidos: "; getline(cin, ape);
                    if (!esSoloLetras(ape) || ape.length() > 60) cout << " [!] Error: Solo letras, max 60 caracteres.\n";
                } while (!esSoloLetras(ape) || ape.length() > 60);

                // VALIDACIÓN DE DIRECCIÓN
                do {
                    cout << " Direccion: "; getline(cin, dir);
                    if (dir.empty() || dir.length() > 100) cout << " [!] Error: No puede estar vacia, max 100 caracteres.\n";
                } while (dir.empty() || dir.length() > 100);

                // VALIDACIÓN DE TELÉFONO
                do {
                    cout << " Telefono (8 digitos): "; cin >> tel;
                    if (!validarTelefono(tel)) cout << " [!] Error: Solo 8 numeros.\n";
                } while (!validarTelefono(tel));

                // VALIDACIÓN DE FECHA
                do {
                    cout << " Fecha Nac. (AAAA-MM-DD): "; cin >> fecha;
                    if (!validarFecha(fecha)) cout << " [!] Error: Formato incorrecto.\n";
                } while (!validarFecha(fecha));

                // VALIDACIÓN DE TIPO DE SANGRE (Solo 1-4 existentes)
                do {
                    cout << " ID Tipo Sangre (1-4): "; cin >> id_sangre;
                    if (id_sangre < 1 || id_sangre > 4) cout << " [!] Error: ID de sangre no existe.\n";
                } while (id_sangre < 1 || id_sangre > 4);

                // INSERCIÓN SEGURA (Evita Inyección SQL)
                sql::PreparedStatement* pstmt = con->prepareStatement(
                    "INSERT INTO estudiantes(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES (?,?,?,?,?,?,?)");

                pstmt->setString(1, carnet);
                pstmt->setString(2, nom);
                pstmt->setString(3, ape);
                pstmt->setString(4, dir);
                pstmt->setString(5, tel);
                pstmt->setString(6, fecha);
                pstmt->setInt(7, id_sangre);

                try {
                    pstmt->executeUpdate();
                    cout << "\n [!] EXITO: Registro validado y guardado." << endl;
                }
                catch (sql::SQLException& e) {
                    cout << "\n [X] ERROR: El codigo ya existe o hay duplicidad." << endl;
                }

                delete pstmt;
                system("pause");
            }
            else if (opcion == 2) {
                // ...  código de lectura  ...
                limpiar();
                sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM estudiantes");
                sql::ResultSet* res = pstmt->executeQuery();
                while (res->next()) {
                    cout << res->getString("codigo") << " | " << res->getString("nombres") << " " << res->getString("apellidos") << endl;
                }
                delete res; delete pstmt;
                system("pause");
            }
        } while (opcion != 3);

        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "\n [X] ERROR DE CONEXION: " << e.what() << endl;
        system("pause");
    }
    return 0;
}
