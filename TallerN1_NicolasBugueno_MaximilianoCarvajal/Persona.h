#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

// Clase base del proyecto. Representa cualquier persona que pueda pasar
// por el sistema del hospital. Hoy en dia solo se usa para dar origen a
// Paciente, pero se dejo como clase base porque en un hospital real
// tambien existirian, por ejemplo, medicos o personal administrativo que
// comparten estos mismos datos (id, nombre, edad).
class Persona {
protected:
    string id;
    string nombre;
    int edad;

public:
    Persona();
    Persona(const string& idPersona, const string& nombrePersona, int edadPersona);
    virtual ~Persona();

    string getId() const;
    string getNombre() const;
    int getEdad() const;

    void setNombre(const string& nuevoNombre);
    void setEdad(int nuevaEdad);

    // Se marca como virtual para que las clases derivadas puedan
    // sobrescribir la forma en que se muestra la informacion.
    virtual void mostrarInfo() const;
};

#endif
