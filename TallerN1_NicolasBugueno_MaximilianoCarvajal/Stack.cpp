#include "Stack.h"
#include <iostream>

using namespace std;

Stack::Stack() : tope(nullptr), cantidad(0) {}

Stack::~Stack() {
    Nodo<RegistroAtencion*>* actual = tope;
    while (actual != nullptr) {
        Nodo<RegistroAtencion*>* siguienteNodo = actual->siguiente;
        delete actual->dato;
        delete actual;
        actual = siguienteNodo;
    }
}

void Stack::apilarAtencion(const string& nombre, int edad, const string& servicio) {
    RegistroAtencion* nuevoRegistro = new RegistroAtencion(nombre, edad, servicio);
    Nodo<RegistroAtencion*>* nuevoNodo = new Nodo<RegistroAtencion*>(nuevoRegistro);

    // Insertar en la cabeza es lo que le da el comportamiento LIFO a
    // la estructura: el ultimo que entra es el primero en mostrarse.
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
    cantidad++;
}

void Stack::mostrarHistorial() const {
    if (estaVacia()) {
        cout << "Todavia no se ha registrado ninguna atencion." << endl;
        return;
    }

    Nodo<RegistroAtencion*>* actual = tope;
    while (actual != nullptr) {
        RegistroAtencion* registro = actual->dato;
        cout << "Nombre: " << registro->nombrePaciente
             << " | Edad: " << registro->edadPaciente
             << " | Departamento: " << registro->servicioDestino << endl;
        actual = actual->siguiente;
    }
}

bool Stack::estaVacia() const {
    return tope == nullptr;
}

int Stack::getCantidad() const {
    return cantidad;
}
