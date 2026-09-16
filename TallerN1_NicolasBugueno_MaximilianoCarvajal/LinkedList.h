#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Nodo.h"

// Lista enlazada simple implementada a mano, sin usar std::list.
// Se usa como plantilla porque la misma estructura sirve tanto para
// la lista principal de servicios del hospital como para la lista de
// pacientes que tiene cada servicio.
//
// Importante: la lista solo administra los nodos que crea. Si T es un
// puntero (como Servicio* o Paciente*), la responsabilidad de liberar
// el objeto apuntado es de quien use la lista (Hospital, Servicio),
// porque son ellos los que realmente saben cuando ese objeto ya no se
// necesita.
template <typename T>
class LinkedList {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int cantidad;

public:
    LinkedList();
    ~LinkedList();

    void insertarAlFinal(T dato);
    bool estaVacia() const;
    int getCantidad() const;

    // Se expone la cabeza para permitir recorridos y busquedas
    // especificas de cada dominio (por ejemplo, buscar por ID o por
    // nombre de servicio) sin tener que duplicar esa logica dentro de
    // la lista generica.
    Nodo<T>* getCabeza() const;
};

// Las plantillas necesitan que el compilador vea la implementacion en
// cada archivo donde se instancien, por eso el .cpp se incluye aca en
// vez de compilarse por separado.
#include "LinkedList.cpp"

#endif
