// Implementacion de LinkedList. No se debe compilar como unidad
// independiente: se incluye automaticamente al final de LinkedList.h.

template <typename T>
LinkedList<T>::LinkedList() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        Nodo<T>* siguienteNodo = actual->siguiente;
        delete actual;
        actual = siguienteNodo;
    }
}

template <typename T>
void LinkedList<T>::insertarAlFinal(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        cola = nuevoNodo;
    }

    cantidad++;
}

template <typename T>
bool LinkedList<T>::estaVacia() const {
    return cabeza == nullptr;
}

template <typename T>
int LinkedList<T>::getCantidad() const {
    return cantidad;
}

template <typename T>
Nodo<T>* LinkedList<T>::getCabeza() const {
    return cabeza;
}
