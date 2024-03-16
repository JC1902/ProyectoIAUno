//#include "Nodo.h"
#include "Map.h"
#include "Game.h"
#include <fstream>

//#include "Grafo.h"
#include <list>
#include <vector>
//#include "Grafo.h"
//#include "Nodo.h"
//#include "ECS/KeyboardController.h"

using namespace std;
static void  setNodosAdyacentesIzq(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, -1);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, 1);
}
static void setNodosAdyacentesDown(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, 32);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, -32);
}
static void setNodosAdyacentesUp(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, -32);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, 32);
}
static void  setNodosAdyacentesDer(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, 1);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, -1);
}
//---------------------------------------------------------------------------
Map::Map()
{

}
//---------------------------------------------------------------------------
Map::~Map()
{

}
//---------------------------------------------------------------------------
vector<Nodo*> Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);
	int idCasilla = 1;
	list<Nodo*> listaNodos;

	int numNodos = 1024;
	int idTipoCasilla;
	Grafo* grafo = new Grafo();
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			idTipoCasilla = atoi(&tile);
			Nodo* nodo = new Nodo(x * 32, y * 32, idTipoCasilla, idCasilla);
			listaNodos.push_back(nodo);
			Game::addTile(idTipoCasilla, x * 32, y * 32);
			mapFile.ignore();
			idCasilla++;
		}
	}
	for (list<Nodo*>::iterator it = listaNodos.begin(); it != listaNodos.end(); it++) {
		Nodo* nodoAux = new Nodo();
		Nodo* nodoActual = new Nodo();
		nodoAux = *it;
		nodoActual = *it;
		if (nodoAux->getY() == 992 && nodoAux->getX() == 992) {
			grafo->agregarNodo(nodoActual);
		}
		else if (nodoAux->getX() == 992) {
			setNodosAdyacentesDown(it, nodoAux, nodoActual);
			grafo->agregarNodo(nodoActual);
		}
		else if (nodoAux->getY() == 992) {
			setNodosAdyacentesDer(it, nodoAux, nodoActual);
			grafo->agregarNodo(nodoActual);
		}
		else {
			setNodosAdyacentesDer(it, nodoAux, nodoActual);
			setNodosAdyacentesDown(it, nodoAux, nodoActual);
			grafo->agregarNodo(nodoActual);
		}

		//Casilla de la esquina superior izquierda
	//	if (nodoAux->getValorCasilla() == 1) {
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casilla de la esquina superior derecha
	//	else if (nodoActual->getY() <= 0 && nodoActual->getX() == 992) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas sobrantes de la primer fila
	//	else if (nodoActual->getY() <= 0 && nodoActual->getX() != 992 && nodoActual->getX() !=0) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas de la primer columna
	//	else if (nodoActual->getY() != 0 && nodoActual->getX() == 0 && nodoActual->getY() != 992) {
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casilla de la esquina inferior izquierda
	//	else if (nodoActual->getY() == 992 && nodoActual->getX() == 0) {
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas de la ultima fila, sin contar la casilla hasta el final de la derecha
	//	else if (nodoActual->getY() == 992 && nodoActual->getX() != 992 && nodoActual->getX()!=0) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casilla de la esquina inferior derecha
	//	else if (nodoActual->getY() == 992 && nodoActual->getX() == 992) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas de la ultima columna
	//	else if (nodoActual->getX() == 992 && nodoActual->getY() != 992 && nodoActual->getY() != 0) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas del centro del mapa
	//	else {
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}

	}
	Nodo* nodoOrigen, * nodoDestino;
	nodoOrigen = (grafo->buscarNodo(0, 0));
	nodoDestino = (grafo->buscarNodo(96, 96));
	// Ejecutamos el algoritmo de profundidad

	vector<Nodo*> camino = grafo->algoritmoProfundidad(nodoOrigen, nodoDestino);

	// Imprimimos el camino encontrado
	if (!camino.empty()) {
		for (Nodo* nodo : camino) {
			int x = nodo->getX();
			int y = nodo->getY();
			int casilla = nodo->getValorCasilla();
			cout << x << "," << y << " VC: " << casilla << endl;
		}
	}
	else {
		cout << "No se encontró un camino" << endl;
	}
	//KeyBoardController movementController;
	
	mapFile.close();
	return camino;
}


//---------------------------------------------------------------------------

