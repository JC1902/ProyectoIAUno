
using namespace std;
#include "Grafo.h"
#include <stack>
//#include "Nodo.cpp"
//#include "Nodo.h"
Grafo::Grafo() {}

void Grafo::agregarNodo(Nodo* nodo) {
    nodos.push_back(nodo);
}

Nodo* Grafo::buscarNodo(int x, int y) {
    for (Nodo* nodo : nodos) {
        if (nodo->getX() == x && nodo->getY() == y) {
            return nodo;
        }
    }
    return nullptr;
}

vector<Nodo*> Grafo::algoritmoProfundidad(Nodo* nodo_origen, Nodo* nodo_destino) {
    std::stack<Nodo*> pila;
    vector<Nodo*> camino;

    pila.push(nodo_origen);
    nodo_origen->setVisitado(true);
    camino.push_back(nodo_origen);

    while (!pila.empty()) {
        Nodo* nodo_actual = pila.top();
        pila.pop();

        if (nodo_actual == nodo_destino) {
            return camino;
        }
        /*for (int i = 0; i < camino.size();i++) {
            if (camino.at(i) == nodo_destino)
                return camino;
        }*/
        for (int i = 0; i < nodo_actual->getAdyacentes().size();i++) {
            Nodo* nodo_adyacente = nodo_actual->getAdyacentes().at(i);
            if (!nodo_adyacente->isVisitado()) {
                pila.push(nodo_adyacente);
               // this->buscarNodo(nodo_actual.getAdyacentes().at(i).getX(), nodo_actual.getAdyacentes().at(i).getY()).setVisitado(true);
                nodo_adyacente->setVisitado(true);
                //pila.push(nodo_adyacente);
                camino.push_back(nodo_adyacente);
                if (nodo_adyacente == nodo_destino) {
                    return camino;
                }
            }
        }
        /*for (Nodo* nodo_adyacente : nodo_actual->getAdyacentes()) {
            if (!nodo_adyacente->isVisitado()) {
                pila.push(nodo_adyacente);
                nodo_adyacente->setVisitado(true);
                camino.push_back(nodo_adyacente);
            }
        }*/
    }


    return vector<Nodo*>();
}