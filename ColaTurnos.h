#ifndef COLA_TURNOS_H
#define COLA_TURNOS_H

#include <iostream>
#include <string>
using namespace std;

// Cola enlazada FIFO para turnos generales (seccion 9.7, RF-06)
struct Turno {
    int numero;
    string cliente;
    string servicio;
};

struct NodoTurno {
    Turno dato;
    NodoTurno* sig;
};

class ColaTurnos {
private:
    NodoTurno* frente;
    NodoTurno* fin;
    int contador;   // genera el numero de turno

public:
    ColaTurnos() : frente(nullptr), fin(nullptr), contador(0) {}

    ~ColaTurnos() {
        while (frente != nullptr) {
            NodoTurno* temp = frente;
            frente = frente->sig;
            delete temp;
        }
    }

    bool estaVacia() const { return frente == nullptr; }

    // Agrega al final y devuelve el numero de turno asignado
    int encolar(const string& cliente, const string& servicio) {
        contador++;
        NodoTurno* nuevo = new NodoTurno{{contador, cliente, servicio}, nullptr};
        if (fin == nullptr) frente = fin = nuevo;   // primer elemento
        else { fin->sig = nuevo; fin = nuevo; }
        return contador;
    }

    // Retira el turno del frente; false si la cola esta vacia (RF-11)
    bool desencolar(Turno& atendido) {
        if (estaVacia()) return false;
        NodoTurno* temp = frente;
        atendido = temp->dato;
        frente = frente->sig;
        if (frente == nullptr) fin = nullptr;       // se retiro el unico elemento
        delete temp;
        return true;
    }

    bool verProximo(Turno& proximo) const {
        if (estaVacia()) return false;
        proximo = frente->dato;
        return true;
    }

    // Muestra la fila en el orden en que sera atendida (RF-12)
    void mostrar() const {
        if (estaVacia()) { cout << "No hay turnos en espera.\n"; return; }
        for (NodoTurno* p = frente; p != nullptr; p = p->sig)
            cout << "Turno " << p->dato.numero << " | " << p->dato.cliente
                 << " | " << p->dato.servicio << "\n";
    }
};

#endif
