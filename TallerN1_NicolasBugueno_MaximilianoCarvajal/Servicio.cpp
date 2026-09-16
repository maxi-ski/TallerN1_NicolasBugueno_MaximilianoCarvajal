#include "Servicio.h"
#include <iostream>

using namespace std;

Servicio::Servicio(const string& nombreServicio) : nombre(nombreServicio) {}

Servicio::~Servicio() {
    // La lista enlazada solo se encarga de sus propios nodos, asi que
    // el servicio (que es quien realmente "posee" a estos pacientes
    // una vez atendidos) debe liberar cada Paciente por su cuenta.
    Nodo<Paciente*>* actual = pacientes.getCabeza();
    while (actual != nullptr) {
        delete actual->dato;
        actual = actual->siguiente;
    }
}

string Servicio::getNombre() const {
    return nombre;
}

void Servicio::recibirPaciente(Paciente* paciente) {
    paciente->setServicio(nombre);
    paciente->marcarComoAtendido();
    pacientes.insertarAlFinal(paciente);
}

void Servicio::mostrarPacientes() const {
    cout << "Pacientes en el departamento de " << nombre << ": " << pacientes.getCantidad() << endl;

    Nodo<Paciente*>* actual = pacientes.getCabeza();
    while (actual != nullptr) {
        cout << actual->dato->getNombre() << " (" << actual->dato->getEdad() << ")" << endl;
        actual = actual->siguiente;
    }
}

Paciente* Servicio::buscarPacientePorId(const string& id) const {
    Nodo<Paciente*>* actual = pacientes.getCabeza();
    while (actual != nullptr) {
        if (actual->dato->getId() == id) {
            return actual->dato;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

int Servicio::cantidadPacientes() const {
    return pacientes.getCantidad();
}
