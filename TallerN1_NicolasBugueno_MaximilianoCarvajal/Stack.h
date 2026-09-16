#ifndef STACK_H
#define STACK_H

#include <string>
#include "Nodo.h"

using namespace std;

// Registro pequeno con los datos de una atencion. No amerita una
// jerarquia de clases propia, por eso se dejo como una estructura
// simple usada unicamente por el historial.
struct RegistroAtencion {
    string nombrePaciente;
    int edadPaciente;
    string servicioDestino;

    RegistroAtencion(const string& nombre, int edad, const string& servicio)
        : nombrePaciente(nombre), edadPaciente(edad), servicioDestino(servicio) {}
};

// Historial de atenciones del hospital, implementado como una pila
// manual (sin std::stack). Se eligio LIFO porque, al revisar el
// historial, normalmente interesa ver primero la atencion mas reciente.
class Stack {
private:
    Nodo<RegistroAtencion*>* tope;
    int cantidad;

public:
    Stack();
    ~Stack();

    void apilarAtencion(const string& nombre, int edad, const string& servicio);
    void mostrarHistorial() const;

    bool estaVacia() const;
    int getCantidad() const;
};

#endif
