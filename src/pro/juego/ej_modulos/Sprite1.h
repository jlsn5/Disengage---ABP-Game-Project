#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Motor2D.h"
using namespace std;
class Sprite1{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Font font;
        sf::Text texto;
        sf::Text menu[7];
        sf::Color color;
        Motor2D *motor = Motor2D::getInstance();
        int tamFuente;
    public:
        Sprite1();
        ~Sprite1();
        Sprite1(std::string rutaT);
        void setPos(int ancho, int alto, int pos);
        void setPosicionSprite(double p1, double p2);
        void setFont(std::string ruta);
        void setText(std::string cadena, int pos);
        void setTexto(std::string c);
        void getTexto(int p);
        sf::Text getTextoo(int p);
        void recortar(int x, int y, int ancho, int alto);
        void escalar(float x, float y);
        void mover(float velX, float velY);
        void setColor(std::string c, int pos);
        void setTextura(std::string ruta);
        void recortarSetTextureRect(double pos1, double pos2, double pos3, double pos4);
        void dibujar(std::string t, int p);
        void mover(double x, double y);
        void setOrigen(double x, double y);
        void setTam(int e);
        sf::Sprite getSprite();
        sf::Sprite *getSpritePuntero();
};