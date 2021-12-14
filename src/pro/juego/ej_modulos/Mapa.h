#pragma once
#ifndef MAPA_H
#define MAPA_H
#include "SFML/Graphics.hpp"
#include "Motor2D.h"

using namespace std;
using namespace sf;
class Mapa
{
    public:
        Mapa();
        ~Mapa();
        Mapa (const Mapa& aux);

        void leerMapa(int nivel);
        void draw(sf::RenderWindow* window);
        bool compruebaColision(sf::FloatRect &fr);
        void dibujar();
        
        int getAltura();
        int getAnchura();
        Sprite ****getMapaSprites();

    private:

        int anchura;
        int altura;
        int tileAnchura;
        int tileAltura;
        int numCapas;
        int ***_tilemap;

        Motor2D *motor = Motor2D::getInstance();


        Sprite * _tilesetSprites;
        Sprite **** _tilemapSprite;
        Texture _tilesetTexture;

};

#endif // MAPA_H