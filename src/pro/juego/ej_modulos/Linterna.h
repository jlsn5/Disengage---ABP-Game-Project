#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PersonajePrincipal.h"

class Linterna{

    private:
        Sprite1 *spriteLinterna;


    public:
       //constructor 
        Linterna();
        //event on MouseMoved en el main
        //void giraAPosDeRaton(sf::RenderWindow &win, sf::Sprite &pantalla);
        void dibujarLinterna();
        void actualizarLinterna(std::string s);
        Sprite1* getSpriteLinterna();
        void reiniciar();
};
