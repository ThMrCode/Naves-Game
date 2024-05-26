#pragma once
#include "Jugador.h"
#include "Enemy.h"
class Controler
{
private:
	int heigth, width, score, contador;
	string pantalla = "";
	string pantallaUtil = "";
	Jugador* player;
	Tensor<Enemy*> enemys;
public:
	Controler(int w, int h);
	void verificarColisiones();
	void funcionEnemy();
	void funcionPlayer();
	void funcionMostrador();
	void gotoxy(int x, int y);
	void iniciar();
};

