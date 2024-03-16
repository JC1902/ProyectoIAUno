#include "Nodo.h"
#include <vector>
using namespace std;


class Grafo {
public:
    Grafo();

    void agregarNodo(Nodo* nodo);

    Nodo* buscarNodo(int x, int y);

    vector<Nodo*> algoritmoProfundidad(Nodo* nodo_origen, Nodo* nodo_destino);

private:
    vector<Nodo*> nodos;
};
