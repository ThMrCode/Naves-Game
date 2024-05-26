#pragma once
#include <Conio.h>
#include <Windows.h>
#include "Tensor.h"
#include <string>
#include <iostream>
using namespace std;
using namespace System;

struct Disparo {
	int x;
	int y;
};

class Nave
{
public:
	Tensor<Disparo> disparos;
	int dx, h, w; char forma;
	int x, y, velocity_x, velocity_y, vida;
	Nave();
	Nave(int x_, int y_, int vida_, int w_, int h_, int dx_, char forma_, int v_x_, int v_y_);
	void moverDisparos();
};


