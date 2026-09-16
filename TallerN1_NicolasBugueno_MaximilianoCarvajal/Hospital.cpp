#include "Hospital.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

// -----------------------------------------------------------------
// Funcion auxiliar interna (no forma parte de la interfaz publica):
// compara dos strings ignorando mayusculas/minusculas. Se usa para que
// el nombre del servicio leido del archivo no tenga que coincidir de
// forma exacta en mayusculas con el nombre "oficial" del servicio.
// -----------------------------------------------------------------
static bool sonIgualesSinMayusculas(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (tolower(static_cast<unsigned char>(a[i])) != tolower(static_cast<unsigned char>(b[i]))) {
            return false;
        }
    }
    return true;
}

Hospital::Hospital() {
    inicializarServicios();
}

Hospital::~Hospital() {
    // La lista principal solo libera sus nodos; los objetos Servicio
    // los debe liberar quien los creo, o sea, el propio Hospital.
    Nodo<Servicio*>* actual = servicios.getCabeza();
    while (actual != nullptr) {
        delete actual->dato;
        actual = actual->siguiente;
    }
}

void Hospital::inicializarServicios() {
    // Estos son los 8 departamentos fijos definidos en el enunciado.
    // Se mantienen sin tildes a proposito, para que coincidan tal cual
    // con el formato usado en el archivo de ejemplo del taller.
    const string nombresIniciales[8] = {
        "Urgencias",
        "Medicina General",
        "Cardiologia",
        "Neurologia",
        "Traumatologia",
        "Cirugia",
        "Pediatria",
        "Hospitalizacion"
    };

    for (int i = 0; i < 8; i++) {
        servicios.insertarAlFinal(new Servicio(nombresIniciales[i]));
    }
}

Servicio* Hospital::buscarServicio(const string& nombreServicio) const {
    Nodo<Servicio*>* actual = servicios.getCabeza();
    while (actual != nullptr) {
        if (sonIgualesSinMayusculas(actual->dato->getNombre(), nombreServicio)) {
            return actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool Hospital::esServicioValido(const string& nombreServicio) const {
    return buscarServicio(nombreServicio) != nullptr;
}

bool Hospital::idYaExiste(const string& id) const {
    if (colaPacientes.contieneId(id)) {
        return true;
    }

    Nodo<Servicio*>* actual = servicios.getCabeza();
    while (actual != nullptr) {
        if (actual->dato->buscarPacientePorId(id) != nullptr) {
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

bool Hospital::parsearLinea(const string& linea, string& id, string& nombre, int& edad, string& servicioStr) const {
    // Se trabaja directamente sobre el buffer de caracteres de la
    // linea (c_str) en vez de usar stringstream, para poder aplicar
    // aritmetica de punteros al ubicar los 3 separadores ';' que debe
    // tener una linea con formato ID;Nombre;Edad;Servicio.
    const char* inicio = linea.c_str();
    const char* puntero = inicio;

    const char* separadores[3] = {nullptr, nullptr, nullptr};
    int separadoresEncontrados = 0;

    while (*puntero != '\0') {
        if (*puntero == ';') {
            if (separadoresEncontrados < 3) {
                separadores[separadoresEncontrados] = puntero;
            }
            separadoresEncontrados++;
        }
        puntero++;
    }

    if (separadoresEncontrados != 3) {
        return false;
    }

    // Cada longitud se obtiene restando punteros, no contando
    // caracteres con un indice: esa es la aritmetica de punteros
    // "significativa" que pide el enunciado, ya que sin ella no se
    // podria saber donde termina cada campo del archivo.
    const char* finLinea = inicio + linea.size();

    int longitudId = static_cast<int>(separadores[0] - inicio);
    int longitudNombre = static_cast<int>(separadores[1] - separadores[0] - 1);
    int longitudEdad = static_cast<int>(separadores[2] - separadores[1] - 1);
    int longitudServicio = static_cast<int>(finLinea - separadores[2] - 1);

    if (longitudId <= 0 || longitudNombre <= 0 || longitudEdad <= 0 || longitudServicio <= 0) {
        return false;
    }

    id = string(inicio, longitudId);
    nombre = string(separadores[0] + 1, longitudNombre);
    string edadTexto(separadores[1] + 1, longitudEdad);
    servicioStr = string(separadores[2] + 1, longitudServicio);

    // La edad debe ser un numero valido, sin letras ni signos raros.
    for (size_t i = 0; i < edadTexto.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(edadTexto[i]))) {
            return false;
        }
    }

    edad = stoi(edadTexto);
    return true;
}

void Hospital::cargarPacientesDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo '" << rutaArchivo << "'. Verifique que la ruta sea correcta." << endl;
        return;
    }

    string linea;
    int numeroLinea = 0;
    int pacientesCargados = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;

        if (linea.empty()) {
            continue;
        }

        string id, nombre, servicioStr;
        int edad;

        if (!parsearLinea(linea, id, nombre, edad, servicioStr)) {
            cout << "Linea " << numeroLinea << " con formato invalido, se omite: \"" << linea << "\"" << endl;
            continue;
        }

        if (!esServicioValido(servicioStr)) {
            cout << "Linea " << numeroLinea << ": el servicio '" << servicioStr
                 << "' no es un departamento valido, se omite al paciente " << id << "." << endl;
            continue;
        }

        if (idYaExiste(id)) {
            cout << "Linea " << numeroLinea << ": ya existe un paciente registrado con ID "
                 << id << ", se omite la linea duplicada." << endl;
            continue;
        }

        Paciente* nuevoPaciente = new Paciente(id, nombre, edad, servicioStr);
        colaPacientes.encolar(nuevoPaciente);
        pacientesCargados++;
    }

    archivo.close();
    cout << pacientesCargados << " paciente(s) cargado(s) correctamente a la cola de espera." << endl;
}

void Hospital::atenderPacientes(int cantidad) {
    if (colaPacientes.estaVacia()) {
        cout << "No hay pacientes en espera para atender." << endl;
        return;
    }

    if (cantidad <= 0) {
        cout << "La cantidad de pacientes a atender debe ser mayor que 0." << endl;
        return;
    }

    cout << "=== ATENDIENDO PACIENTES ===" << endl;

    int atendidos = 0;
    while (atendidos < cantidad && !colaPacientes.estaVacia()) {
        Paciente* paciente = colaPacientes.desencolar();
        Servicio* destino = buscarServicio(paciente->getServicio());

        // En teoria esto ya se valido al cargar el archivo, pero se
        // deja el control igual por robustez ante posibles cambios
        // futuros en la forma de cargar pacientes.
        if (destino == nullptr) {
            cout << "No se encontro el servicio " << paciente->getServicio()
                 << " para el paciente " << paciente->getId() << ", se descarta." << endl;
            delete paciente;
            continue;
        }

        cout << "ID: " << paciente->getId() << endl;
        cout << "Nombre: " << paciente->getNombre() << endl;
        cout << "Edad: " << paciente->getEdad() << endl;
        cout << "Servicio: " << paciente->getServicio() << endl;

        // A partir de aca el servicio pasa a ser el dueno del objeto
        // Paciente; el historial solo guarda una copia de los datos
        // relevantes, no el puntero al paciente.
        string nombrePacienteAtendido = paciente->getNombre();
        int edadPacienteAtendido = paciente->getEdad();
        string servicioDestino = paciente->getServicio();

        destino->recibirPaciente(paciente);
        historial.apilarAtencion(nombrePacienteAtendido, edadPacienteAtendido, servicioDestino);

        cout << "Paciente enviado a " << servicioDestino << "." << endl << endl;
        atendidos++;
    }

    if (atendidos < cantidad) {
        cout << "Se atendieron " << atendidos << " paciente(s); no quedaban mas pacientes en espera." << endl;
    }
}

void Hospital::mostrarColaPendientes() const {
    cout << "=== PACIENTES EN ESPERA ===" << endl;
    colaPacientes.mostrarPacientesEnEspera();
}

void Hospital::mostrarServiciosDisponibles() const {
    cout << "=== DEPARTAMENTOS/SERVICIOS ===" << endl;
    int numero = 1;
    Nodo<Servicio*>* actual = servicios.getCabeza();
    while (actual != nullptr) {
        cout << numero << ". " << actual->dato->getNombre() << endl;
        actual = actual->siguiente;
        numero++;
    }
}

void Hospital::mostrarEstadoServicio(const string& nombreServicio) const {
    Servicio* servicio = buscarServicio(nombreServicio);

    if (servicio == nullptr) {
        cout << "El servicio '" << nombreServicio << "' no existe." << endl;
        return;
    }

    cout << "=== ESTADO " << servicio->getNombre() << " ===" << endl;
    servicio->mostrarPacientes();
}

void Hospital::mostrarEstadoGeneral() const {
    cout << "=== ESTADO GENERAL DE LOS SERVICIOS ===" << endl;
    Nodo<Servicio*>* actual = servicios.getCabeza();
    while (actual != nullptr) {
        cout << "- " << actual->dato->getNombre() << ": "
             << actual->dato->cantidadPacientes() << " paciente(s)" << endl;
        actual = actual->siguiente;
    }
}

void Hospital::mostrarHistorial() const {
    cout << "=== HISTORIAL DE ULTIMAS ATENCIONES DEL HOSPITAL ===" << endl;
    historial.mostrarHistorial();
}

void Hospital::buscarPacienteEnSistema(const string& id) const {
    Nodo<Servicio*>* actual = servicios.getCabeza();
    while (actual != nullptr) {
        Paciente* encontrado = actual->dato->buscarPacientePorId(id);
        if (encontrado != nullptr) {
            cout << "Paciente encontrado en " << actual->dato->getNombre() << ":" << endl;
            encontrado->mostrarInfo();
            return;
        }
        actual = actual->siguiente;
    }

    if (colaPacientes.contieneId(id)) {
        cout << "El paciente con ID " << id << " todavia esta en la cola de espera (no ha sido atendido)." << endl;
        return;
    }

    cout << "No se encontro ningun paciente con ID " << id << " en el sistema." << endl;
}
