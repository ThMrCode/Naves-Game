#pragma once
#include "Nave.h"
class Enemy : public Nave
{
public:
	Enemy();
	Enemy(int x, int y, int w, int h);
	void mostrar(string& cadena);
};


