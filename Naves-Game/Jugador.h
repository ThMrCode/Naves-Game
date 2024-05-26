#pragma once
#include "Nave.h"
class Jugador : public Nave
{
public:
	Jugador(int x, int y, int w, int h);
	void mostrar(string& cadena);
	void mover(int num);
};
