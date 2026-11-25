#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "Cuenta.h"

// Operaciones monetarias con validaciones (RF-03, RF-04, RF-05, RF-11)

inline bool depositar(Cuenta* c, double monto) {
    if (c == nullptr || monto <= 0) return false;
    c->saldo += monto;
    return true;
}

// Falla si el monto es invalido o los fondos no alcanzan
inline bool retirar(Cuenta* c, double monto) {
    if (c == nullptr || monto <= 0 || monto > c->saldo) return false;
    c->saldo -= monto;
    return true;
}

// Solo aplica debito y credito si ambas validaciones se cumplen
inline bool transferir(Cuenta* origen, Cuenta* destino, double monto) {
    if (origen == nullptr || destino == nullptr || origen == destino) return false;
    if (monto <= 0 || monto > origen->saldo) return false;
    origen->saldo -= monto;
    destino->saldo += monto;
    return true;
}

#endif
