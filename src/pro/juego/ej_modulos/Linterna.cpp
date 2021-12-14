#include "Linterna.h"
#include <iostream>
#include "Motor2D.h"
#include <math.h>


Linterna::Linterna(){
    Motor2D *motor = Motor2D::getInstance();
    spriteLinterna = new Sprite1("resources/linterna.png");
    spriteLinterna->setOrigen(2560/2-11, 2560/2 -16);
    spriteLinterna->recortarSetTextureRect(0,0,2560,2560);
    spriteLinterna->setPosicionSprite(960/2, motor->getLongitud());
}
/*
void Linterna::giraAPosDeRaton(sf::RenderWindow &win, sf::Sprite &pantalla){

    //cojo pos del cursor en la pantalla
    sf::Vector2f curPos = pantalla.getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(win); //raton

    const float PI = 3.14159265;

    float dx = curPos.x - position.x; 
    float dy = curPos.y - position.y;

    float rotation = ((atan2(dy, dx)) * 180 / PI ) -90; //calculo la tangente 
    //-90 para ajustar

    pantalla.setRotation(rotation);
}*/

void Linterna::actualizarLinterna(std::string s){
    spriteLinterna->setTextura("resources/" + s);
    spriteLinterna->recortarSetTextureRect(0,0,2560,2560);
}

void Linterna::dibujarLinterna(){
    spriteLinterna->dibujar("linterna", 0);
}

Sprite1* Linterna::getSpriteLinterna(){
    return spriteLinterna;
}

void Linterna::reiniciar(){
    Motor2D *motor = Motor2D::getInstance();
    spriteLinterna->setPosicionSprite(960/2, motor->getLongitud());
}
