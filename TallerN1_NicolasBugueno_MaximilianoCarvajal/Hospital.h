#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include "LinkedList.h"
#include "Servicio.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

// Clase que coordina toda la logica del sistema: carga de pacientes
// desde archivo, cola de espera, derivacion hacia los servicios e
// historial de atenciones. Es la unica clase que "conoce" el flujo
// completo (Archivo -> Atencion -> Derivacion -> Guardado de historial).
class Hospital {
private:
    LinkedList<Servicio*> servicios;
    Queue colaPacientes;
    Stack historial;

    void inicializarServicios();
    bool esServicioValido(const string& nombreServicio) const;
    Servicio* buscarServicio(const string& nombreServicio) const;
    bool idYaExiste(const string& id) const;

    // Parseo manual de una linea del archivo de entrada. Se recorre el
    // buffer de caracteres con aritmetica de punteros para ubicar los
    // separadores ';' y extraer cada campo, en vez de apoyarse en
    // stringstream u otras utilidades de alto nivel.
    bool parsearLinea(const string& linea, string& id, string& nombre, int& edad, string& servicio) const;

public:
    Hospital();
    ~Hospital();

    void cargarPacientesDesdeArchivo(const string& rutaArchivo);
    void atenderPacientes(int cantidad);

    void mostrarColaPendientes() const;
    void mostrarServiciosDisponibles() const;
    void mostrarEstadoServicio(const string& nombreServicio) const;
    void mostrarEstadoGeneral() const;
    void mostrarHistorial() const;
    void buscarPacienteEnSistema(const string& id) const;
};

#endif
