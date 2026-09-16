#ifndef SERVICIO_H
#define SERVICIO_H

#include <string>
#include "Paciente.h"
#include "LinkedList.h"

using namespace std;

// Representa un departamento del hospital (Urgencias, Cardiologia,
// etc). Cada servicio mantiene su propia lista enlazada con los
// pacientes que fueron derivados a el.
class Servicio {
private:
    string nombre;
    LinkedList<Paciente*> pacientes;

public:
    Servicio(const string& nombreServicio);
    ~Servicio();

    string getNombre() const;

    void recibirPaciente(Paciente* paciente);
    void mostrarPacientes() const;
    Paciente* buscarPacientePorId(const string& id) const;
    int cantidadPacientes() const;
};

#endif
