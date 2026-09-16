#include "Persona.h"
#include <iostream>

using namespace std;

Persona::Persona() : id(""), nombre(""), edad(0) {}

Persona::Persona(const string& idPersona, const string& nombrePersona, int edadPersona)
    : id(idPersona), nombre(nombrePersona), edad(edadPersona) {}

// El destructor no necesita liberar nada de forma explicita aca, pero se
// deja implementado (y virtual en el header) para que la destruccion de
// las clases hijas funcione correctamente por polimorfismo.
Persona::~Persona() {}

string Persona::getId() const {
    return id;
}

string Persona::getNombre() const {
    return nombre;
}

int Persona::getEdad() const {
    return edad;
}

void Persona::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Persona::setEdad(int nuevaEdad) {
    edad = nuevaEdad;
}

void Persona::mostrarInfo() const {
    cout << "ID: " << id << " | Nombre: " << nombre << " | Edad: " << edad << endl;
}
