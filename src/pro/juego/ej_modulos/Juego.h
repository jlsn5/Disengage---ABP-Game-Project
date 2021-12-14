#pragma once
#include "SFML/Graphics.hpp"
#include "Escena.h"
#include "Motor2D.h"
#include "Mapa.h"

class Juego{
	private:
		Escena *escena;
        Motor2D *motor = Motor2D::getInstance();
        double x_coord;
        double y_coord;
        bool band, mover;
        int width, height;
        int kVel;
        int radio_sprite;
	public:
        Juego();
        Juego(int width, int height);
        void giraAPosDeRaton(sf::RenderWindow *win);
		void giraAPosDeRatonBala(sf::RenderWindow *win);
        FloatRect colisiona(sf::Sprite aux);
        void update();
        void render();
        Escena* getEscena();
        void dibujar();
        void dibujarBalas();
        void updatePositions();
        void MousePressedOnNPC(int x, int y, int seleccionado);
        void eventosHud(int i);
        int getkVel();
        void setkVel(int i);
        void intercambiarObjeto(int i);
};