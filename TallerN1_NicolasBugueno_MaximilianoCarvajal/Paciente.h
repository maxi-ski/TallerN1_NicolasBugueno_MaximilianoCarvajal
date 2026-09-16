#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include "Persona.h"

using namespace std;

// Un Paciente es una Persona que ademas necesita ser derivada a un
// servicio especifico del hospital y que puede o no haber sido atendida
// todavia. Se aprovecha la herencia para no repetir id/nombre/edad, que
// ya estan resueltos en Persona.
class Paciente : public Persona {
private:
    string servicio;
    bool atendido;

public:
    Paciente();
    Paciente(const string& idPaciente, const string& nombrePaciente, int edadPaciente, const string& servicioDestino);
    ~Paciente();

    string getServicio() const;
    void setServicio(const string& nuevoServicio);

    bool fueAtendido() const;
    void marcarComoAtendido();

    // Se sobrescribe para agregar el dato del servicio, que Persona no
    // conoce.
    void mostrarInfo() const override;
};

#endif
