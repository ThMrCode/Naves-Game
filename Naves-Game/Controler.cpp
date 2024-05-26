#include "Controler.h"

Controler::Controler(int w, int h): width(w), heigth(h), score(0), contador(0)
{
	// Generar Jugador
	int x_start = 0;
	if ((this->width % 2) == 1) x_start = ((this->width - 1) / 2);
	else if ((this->width % 2) == 0) x_start = (this->width / 2);
	this->player = new Jugador(x_start, (this->heigth - 5), this->width, this->heigth);
	// Generador de Pantalla
	this->pantalla = this->pantalla + " PUNTOS 0";
	for (int x = 9; x < (w - 8); x++)
	{
		this->pantalla = this->pantalla + " ";
	}
	this->pantalla = this->pantalla + "VIDAS 3 ";
	this->pantalla = this->pantalla + "\n";
	for (int x = 0; x < w; x++)
	{
		this->pantalla = this->pantalla + "#";
	}
	this->pantalla = this->pantalla + "\n";
	for (int y = 2; y < (h - 1); y++)
	{
		this->pantalla = this->pantalla + "#";
		for (int x = 1; x < (w - 1); x++)
		{
			this->pantalla = this->pantalla + " ";
		}
		this->pantalla = this->pantalla + "#";
		this->pantalla = this->pantalla + "\n";
	}
	for (int x = 0; x < w; x++)
	{
		this->pantalla = this->pantalla + "#";
	}
}

void Controler::verificarColisiones()
{
	// Colisiones del Jugador con Disparos de los Enemigos
	int navex = this->player->x;
	int navey = this->player->y;
	int potnave[][2] = { {navex,navey}, {navex,(navey + 1)}, {(navex - 1),(navey + 1)} , {(navex + 1),(navey + 1)} ,{navex,(navey + 2)}, {(navex - 1),(navey + 2)}, {(navex + 1),(navey + 2)}, {(navex - 2),(navey + 2)}, {(navex + 2),(navey + 2)} };
	for (int i = 0; i < this->enemys.size(); i++)
	{
		// Para Cada Enemigo
		Tensor<int> disp_delete;
		for (int j = 0; j < this->enemys[i]->disparos.size(); j++)
		{
			// Para Cada Disparo (Puede que mas de uno choque a la Nave), disp_delete ascendente
			for (int k = 0; k < 9; k++)
			{
				if (potnave[k][0] == this->enemys[i]->disparos[j].x && potnave[k][1] == this->enemys[i]->disparos[j].y) {
					disp_delete.push_if_not(j);
					break;
				}
			}
		}
		this->player->vida -= disp_delete.size();
		this->enemys[i]->disparos.pop(disp_delete);
	}
	// Colisiones de los Enemigos con Disparos del Jugador
	Tensor<int> enemy_delete;
	Tensor<int> disp_delete;
	for (int i = 0; i < this->enemys.size(); i++)
	{
		// Para cada Enemigo (Puede que mas de uno muera), enemy_delete ascendente
		int enemyx = this->enemys[i]->x;
		int enemyy = this->enemys[i]->y;
		int potenemy[][2] = { {enemyx,enemyy}, {(enemyx - 1),enemyy}, {(enemyx + 1),enemyy}, {(enemyx - 1),(enemyy + 1)}, {(enemyx + 1),(enemyy + 1)} };
		for (int j = 0; j < this->player->disparos.size(); j++)
		{
			// Para Cada Disparo (Puede que mas de uno choque al enemigo), disp_delete ascendente
			for (int k = 0; k < 5; k++)
			{
				if (potenemy[k][0] == this->player->disparos[j].x && potenemy[k][1] == this->player->disparos[j].y) {
					disp_delete.push_if_not(j);
					enemy_delete.push_if_not(i);
					break;
				}
			}
		}
	}
	this->player->disparos.pop(disp_delete);
	this->enemys.pop(enemy_delete);
	this->score += (10*enemy_delete.size());
}

void Controler::funcionEnemy()
{
	// Generador de enemigos
	if (this->contador % 50 == 0) {
		Enemy* enemigo = new Enemy(this->player->x, 2, this->width, this->heigth);
		this->enemys.push(enemigo);
	}
	// Actualizador de posiciones
	for (int i = 0; i < this->enemys.size(); i++)
	{
		if (this->contador % 15 == 0) this->enemys[i]->y += this->enemys[i]->velocity_y;
	}
	Tensor<int> enemys_delete;
	for (int i = 0; i < this->enemys.size(); i++)
	{
		if (this->enemys[i]->y > (this->heigth - 4)) {
			enemys_delete.push(i);
		}
	}
	// Generador de disparos y mostrador
	for (int i = 0; i < this->enemys.size(); i++)
	{
		if (this->contador % 12 == 0) {
			Disparo disp; disp.x = this->enemys[i]->x; disp.y = this->enemys[i]->y;
			this->enemys[i]->disparos.push(disp);
		}
		if (this->contador % 2 == 0) this->enemys[i]->moverDisparos();
		this->enemys[i]->mostrar(this->pantallaUtil);
	}
}

void Controler::funcionPlayer()
{
	// Actualizador de posicion disparos y mostrador
	if (_kbhit()) {
		int a = _getch();
		if (a == 32) {
			Disparo disp; disp.x = this->player->x; disp.y = this->player->y;
			this->player->disparos.push(disp);
		}
		else this->player->mover(a);
	}
	this->player->moverDisparos();
	this->player->mostrar(this->pantallaUtil);
}

void Controler::funcionMostrador()
{
	// Actualizador de score vida y mostrador
	string aux = to_string(this->score);
	for (int i = 0; i < aux.length(); i++)
	{
		this->pantallaUtil[(8 + i)] = aux[i];
	}
	this->pantallaUtil[(this->width - 2)] = to_string(this->player->vida)[0];
}

void Controler::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Controler::iniciar()
{
	// Bucle principal
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
	this->contador = 0;
	while (true) {
		this->contador++;
		this->pantallaUtil = this->pantalla;
		this->verificarColisiones();
		if (this->player->vida <= 0) {
			system("cls");
			cout << "Ya fue chamo" << endl;
			system("pause");
			break;
		}
		else {
			this->funcionMostrador();
			this->funcionPlayer();
			this->funcionEnemy();
			gotoxy(0, 0);
			cout << this->pantallaUtil;
		}
		Sleep(20);
	}
}



