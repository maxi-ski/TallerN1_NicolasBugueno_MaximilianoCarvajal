#include "Paciente.h"
#include <iostream>

using namespace std;

Paciente::Paciente() : Persona(), servicio(""), atendido(false) {}

Paciente::Paciente(const string& idPaciente, const string& nombrePaciente, int edadPaciente, const string& servicioDestino)
    : Persona(idPaciente, nombrePaciente, edadPaciente), servicio(servicioDestino), atendido(false) {}

Paciente::~Paciente() {}

string Paciente::getServicio() const {
    return servicio;
}

void Paciente::setServicio(const string& nuevoServicio) {
    servicio = nuevoServicio;
}

bool Paciente::fueAtendido() const {
    return atendido;
}

void Paciente::marcarComoAtendido() {
    atendido = true;
}

void Paciente::mostrarInfo() const {
    cout << "ID: " << id << " | Nombre: " << nombre << " | Edad: " << edad
         << " | Servicio: " << servicio
         << " | Estado: " << (atendido ? "Atendido" : "En espera") << endl;
}
