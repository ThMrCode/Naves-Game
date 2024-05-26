#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int x, int y, int w, int h) :Nave(x, y, 1, w, h, 1, 'o',0,1)
{
}

void Enemy::mostrar(string& cadena)
{
	// Graficando Enemigo
	int pot1 = this->x + this->y * (1 + this->w);
	int pot2 = pot1 + (1 + this->w);
	int num = 220;
	cadena[pot1 - 1] = char(num); cadena[pot1] = char(num); cadena[pot1 + 1] = char(num);
	cadena[pot2 - 1] = char(num); cadena[pot2 + 1] = char(num);
	// Graficando Disparos
	for (int i = 0; i < this->disparos.size(); i++)
	{
		int pot = this->disparos[i].x + this->disparos[i].y * (1 + this->w);
		cadena[pot] = this->forma;
	}
}

