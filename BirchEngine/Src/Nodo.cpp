#include "Nodo.h"


Nodo::Nodo(int x, int y, int tipo_casilla, int valor_casilla) {
    this->x = x;
    this->y = y;
    this->tipo_casilla = tipo_casilla;
    this->valor_casilla = valor_casilla;
    this->visitado = false;
    this->adyacentes = vector<Nodo*>();
}
Nodo::Nodo() {};
int Nodo::getX() const { return x; }

int Nodo::getY() const { return y; }

int Nodo::getTipoCasilla() const { return tipo_casilla; }

int Nodo::getValorCasilla() const { return valor_casilla; }

vector<Nodo*> Nodo::getAdyacentes() { return adyacentes; }

bool Nodo::isVisitado() const { return visitado; }

void Nodo::setVisitado(bool visitado) { this->visitado = visitado; }

void Nodo::agregarAdyacente(Nodo* nodo) { adyacentes.push_back(nodo); }

