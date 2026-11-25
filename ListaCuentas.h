#ifndef LISTA_CUENTAS_H
#define LISTA_CUENTAS_H

#include <iostream>
#include "Cuenta.h"
using namespace std;

// Lista doblemente enlazada que administra las cuentas (seccion 9.2)
struct NodoCuenta {
    Cuenta dato;
    NodoCuenta* sig;
    NodoCuenta* ant;
};

class ListaCuentas {
private:
    NodoCuenta* primero;
    NodoCuenta* ultimo;

public:
    ListaCuentas() : primero(nullptr), ultimo(nullptr) {}

    ~ListaCuentas() {
        while (primero != nullptr) {
            NodoCuenta* temp = primero;
            primero = primero->sig;
            delete temp;
        }
    }

    bool estaVacia() const { return primero == nullptr; }

    // Devuelve el puntero a la cuenta o nullptr si no existe (RF-02)
    Cuenta* buscar(int id) {
        for (NodoCuenta* p = primero; p != nullptr; p = p->sig)
            if (p->dato.id == id) return &p->dato;
        return nullptr;
    }

    // Inserta al final; rechaza identificadores repetidos (RF-01, RF-11)
    bool agregar(const Cuenta& c) {
        if (buscar(c.id) != nullptr) return false;
        NodoCuenta* nuevo = new NodoCuenta{c, nullptr, ultimo};
        if (ultimo == nullptr) primero = nuevo;
        else ultimo->sig = nuevo;
        ultimo = nuevo;
        return true;
    }

    // Elimina una cuenta actualizando los enlaces en ambos sentidos
    bool eliminar(int id) {
        for (NodoCuenta* p = primero; p != nullptr; p = p->sig) {
            if (p->dato.id == id) {
                if (p->ant != nullptr) p->ant->sig = p->sig;
                else primero = p->sig;
                if (p->sig != nullptr) p->sig->ant = p->ant;
                else ultimo = p->ant;
                delete p;
                return true;
            }
        }
        return false;
    }

    // Recorrido de inicio a fin (RF-08)
    void mostrarAdelante() const {
        if (estaVacia()) { cout << "No hay cuentas registradas.\n"; return; }
        for (NodoCuenta* p = primero; p != nullptr; p = p->sig)
            imprimir(p->dato);
    }

    // Recorrido de fin a inicio (RF-08)
    void mostrarAtras() const {
        if (estaVacia()) { cout << "No hay cuentas registradas.\n"; return; }
        for (NodoCuenta* p = ultimo; p != nullptr; p = p->ant)
            imprimir(p->dato);
    }

private:
    static void imprimir(const Cuenta& c) {
        cout << "ID: " << c.id << " | " << c.titular << " | " << c.tipo
             << " | Saldo: $" << c.saldo << "\n";
    }
};

#endif
