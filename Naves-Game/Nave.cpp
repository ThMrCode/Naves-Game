#include "Nave.h"

Nave::Nave()
{
}

Nave::Nave(int x_, int y_, int vida_, int w_, int h_, int dx_, char forma_, int v_x_, int v_y_): x(x_), y(y_), vida(vida_), dx(dx_), w(w_), h(h_), forma(forma_), velocity_x(v_x_), velocity_y(v_y_)
{
}

void Nave::moverDisparos()
{
	for (int i = 0; i < this->disparos.size(); i++)
	{
		this->disparos[i].y += this->dx;
	}
	Tensor<int> pots_delete;
	for (int i = 0; i < this->disparos.size(); i++)
	{
		if (this->disparos[i].y < 3 || this->disparos[i].y > (this->h - 3)) {
			pots_delete.push(i);
		}
	}
	this->disparos.pop(pots_delete);
}
