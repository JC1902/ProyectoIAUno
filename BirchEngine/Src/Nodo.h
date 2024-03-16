#include <vector>
using namespace std;
#include <iostream>
class Nodo {
public:
    Nodo(int x, int y, int tipo_casilla, int valor_casilla);
    Nodo();
    int getX() const;
    int getY() const;
    int getTipoCasilla() const;
    int getValorCasilla() const;
    bool isVisitado() const;
    vector<Nodo*> getAdyacentes();
    void setVisitado(bool visitado);
    void agregarAdyacente(Nodo* nodo);

private:
    int x;
    int y;
    int tipo_casilla;
    int valor_casilla;
    bool visitado;
    vector<Nodo*> adyacentes;
};