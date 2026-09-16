#include <iostream>
#include <limits>
#include "Hospital.h"

using namespace std;

// Pide un numero entero al usuario y se asegura de que la entrada sea
// valida, limpiando el buffer si el usuario escribe algo que no es un
// numero. Se dejo como funcion aparte porque se repite varias veces en
// el menu.
int leerEntero(const string& mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cout << "Entrada invalida, por favor ingrese un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

string leerLinea(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

void mostrarMenu() {
    cout << endl;
    cout << "=== HOSPITAL MARMAJA ===" << endl;
    cout << "1. Atender pacientes" << endl;
    cout << "2. Ver departamento" << endl;
    cout << "3. Revisar historial de atencion" << endl;
    cout << "4. Mostrar cola de pacientes pendientes" << endl;
    cout << "5. Cargar pacientes desde otro archivo" << endl;
    cout << "6. Buscar un paciente por ID" << endl;
    cout << "7. Salir" << endl;
}

int main() {
    Hospital hospital;

    cout << "Bienvenido al sistema de gestion del Hospital Marmaja." << endl;
    string archivoInicial = leerLinea("Ingrese el nombre del archivo de pacientes a cargar: ");
    hospital.cargarPacientesDesdeArchivo(archivoInicial);

    bool continuarEjecutando = true;

    while (continuarEjecutando) {
        mostrarMenu();
        int opcion = leerEntero("Seleccionar opcion: ");

        switch (opcion) {
            case 1: {
                hospital.mostrarColaPendientes();
                int cantidad = leerEntero("Indique la cantidad de pacientes a atender: ");
                hospital.atenderPacientes(cantidad);
                break;
            }
            case 2: {
                hospital.mostrarServiciosDisponibles();
                string nombreServicio = leerLinea("Escriba el nombre del servicio que desea revisar: ");
                hospital.mostrarEstadoServicio(nombreServicio);
                break;
            }
            case 3: {
                hospital.mostrarHistorial();
                break;
            }
            case 4: {
                hospital.mostrarColaPendientes();
                break;
            }
            case 5: {
                string nuevoArchivo = leerLinea("Ingrese el nombre del nuevo archivo a cargar: ");
                hospital.cargarPacientesDesdeArchivo(nuevoArchivo);
                break;
            }
            case 6: {
                string idBuscado = leerLinea("Ingrese el ID del paciente a buscar: ");
                hospital.buscarPacienteEnSistema(idBuscado);
                break;
            }
            case 7: {
                continuarEjecutando = false;
                cout << "Hasta luego :D." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida, intente nuevamente." << endl;
                break;
            }
        }
    }

    // Al salir del while, "hospital" se destruye automaticamente y su
    // destructor se encarga de liberar todos los servicios, pacientes,
    // nodos de listas, colas y pilas creados con new durante la
    // ejecucion.
    return 0;
}
