#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue() : frente(nullptr), final(nullptr), cantidad(0) {}

Queue::~Queue() {
    // Si el programa termina y todavia quedan pacientes sin atender,
    // la cola es la unica duena de esos objetos Paciente, asi que le
    // corresponde a ella liberarlos (ademas de sus propios nodos).
    Nodo<Paciente*>* actual = frente;
    while (actual != nullptr) {
        Nodo<Paciente*>* siguienteNodo = actual->siguiente;
        delete actual->dato;
        delete actual;
        actual = siguienteNodo;
    }
}

void Queue::encolar(Paciente* paciente) {
    Nodo<Paciente*>* nuevoNodo = new Nodo<Paciente*>(paciente);

    if (final == nullptr) {
        frente = nuevoNodo;
        final = nuevoNodo;
    } else {
        final->siguiente = nuevoNodo;
        final = nuevoNodo;
    }

    cantidad++;
}

Paciente* Queue::desencolar() {
    if (estaVacia()) {
        return nullptr;
    }

    Nodo<Paciente*>* nodoAEliminar = frente;
    Paciente* pacienteRetirado = nodoAEliminar->dato;

    frente = frente->siguiente;
    if (frente == nullptr) {
        final = nullptr;
    }

    delete nodoAEliminar;
    cantidad--;

    return pacienteRetirado;
}

Paciente* Queue::verFrente() const {
    if (estaVacia()) {
        return nullptr;
    }
    return frente->dato;
}

bool Queue::estaVacia() const {
    return frente == nullptr;
}

int Queue::getCantidad() const {
    return cantidad;
}

void Queue::mostrarPacientesEnEspera() const {
    if (estaVacia()) {
        cout << "No hay pacientes en espera actualmente." << endl;
        return;
    }

    int posicion = 1;
    Nodo<Paciente*>* actual = frente;
    while (actual != nullptr) {
        cout << posicion << ". " << actual->dato->getId() << " - " << actual->dato->getNombre() << endl;
        actual = actual->siguiente;
        posicion++;
    }
}

bool Queue::contieneId(const string& id) const {
    Nodo<Paciente*>* actual = frente;
    while (actual != nullptr) {
        if (actual->dato->getId() == id) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}
