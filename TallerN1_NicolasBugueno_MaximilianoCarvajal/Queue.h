#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include "Nodo.h"
#include "Paciente.h"

using namespace std;

// Cola de pacientes pendientes de atencion. Implementada a mano con
// nodos enlazados (sin std::queue), respetando estrictamente el orden
// de llegada (FIFO).
class Queue {
private:
    Nodo<Paciente*>* frente;
    Nodo<Paciente*>* final;
    int cantidad;

public:
    Queue();
    ~Queue();

    void encolar(Paciente* paciente);
    Paciente* desencolar();
    Paciente* verFrente() const;

    bool estaVacia() const;
    int getCantidad() const;

    void mostrarPacientesEnEspera() const;
    bool contieneId(const string& id) const;
};

#endif
