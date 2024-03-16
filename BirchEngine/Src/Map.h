#pragma once
#include <string>
#include <list>
#include <vector>
//#include "Nodo.h"
#include "Grafo.h"

class Map
{
public:
	Map();
	~Map();

	static vector<Nodo*> LoadMap(std::string path,int sizeX, int sizeY);
	

private:
	

};