#ifndef NODO_H
#define NODO_H

// Nodo generico reutilizado por la lista enlazada, la cola y la pila del
// proyecto. Se usa una plantilla para no tener que escribir un nodo
// distinto para cada tipo de dato (Servicio*, Paciente*, etc).
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(T valorInicial) : dato(valorInicial), siguiente(nullptr) {}
};

#endif
