#include "Jugador.h"

Jugador::Jugador(int x, int y, int w, int h) :Nave(x, y, 3, w, h, -1, 'o',2,1)
{
}

void Jugador::mostrar(string& cadena)
{
	// Graficando la Nave
	int pot1 = this->x + this->y * (1 + this->w);
	int pot2 = pot1 + (1 + this->w);
	int pot3 = pot1 + (2 * (1 + this->w));
	int num = 220;
	cadena[pot1] = char(num);
	cadena[pot2 - 1] = char(num); cadena[pot2] = char(num); cadena[pot2 + 1] = char(num);
	cadena[pot3 - 2] = char(num); cadena[pot3 - 1] = char(num); cadena[pot3] = char(num); cadena[pot3 + 1] = char(num); cadena[pot3 + 2] = char(num);
	// Graficando Los Disparos
	for (int i = 0; i < this->disparos.size(); i++)
	{
		int pot = this->disparos[i].x + this->disparos[i].y * (1 + this->w);
		cadena[pot] = this->forma;
	}
}

void Jugador::mover(int num)
{
	// Velocidad de 2 en x, de 1 en y (para hacerlo ameno)
	if (num == 100) {
		int newpot = this->x + this->velocity_x;
		if (newpot > 2 && newpot < (this->w - 3)) this->x = newpot;
	}
	else if (num == 97) {
		int newpot = this->x - this->velocity_x;
		if (newpot > 2 && newpot < (this->w - 3)) this->x = newpot;
	}
	else if (num == 119) {
		int newpot = this->y - this->velocity_y;
		if (newpot > 1 && newpot < (this->h - 3)) this->y = newpot;
	}
	else if (num == 115) {
		int newpot = this->y + this->velocity_y;
		if (newpot > 1 && newpot < (this->h - 3)) this->y = newpot;
	}
}

