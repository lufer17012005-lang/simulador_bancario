#ifndef CUENTA_H
#define CUENTA_H

#include <string>
using namespace std;

// Datos de una cuenta bancaria (RF-01)
struct Cuenta {
    int id;
    string titular;
    string tipo;      // "Ahorros" o "Corriente"
    double saldo;
};

#endif
