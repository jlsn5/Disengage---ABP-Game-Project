#include "Armas.h"
#include <iostream>

using namespace std;

Armas::Armas(){
    tipo="";
    rango=1;
    ataqueArma=1;
    cadencia=1;
    disparando =false;
    bala = new Sprite1("resources/flecha.png");
    bala->setOrigen(0,2);
    bala->recortarSetTextureRect(0,0,599,4);
    bala->escalar(0.5f,0.4f);
    spriteArma = new Sprite1();
    cargarTexturas();
}
Armas::Armas(std::string t){
    tipo = t;//debe ser cuchillo o arco
    rango = 1; //el rango del arma entero
    ataqueArma = 1;//daño que tiene el arma
    cadencia =1;//velocidad de golpe
    //posX = x;
    //posY=y;
    disparando =false;

    bala = new Sprite1("resources/flecha.png");
    bala->setOrigen(0,2);
    bala->recortarSetTextureRect(0,0,599,4);
    bala->escalar(0.5f,0.4f);
    spriteArma = new Sprite1();

    cargarTexturas();
} 

Armas::Armas(std::string t, double x, double y){
    tipo = t;//debe ser cuchillo o arco
    rango = 1; //el rango del arma entero
    ataqueArma = 1;//daño que tiene el arma
    cadencia =1;//velocidad de golpe
    posX = x;
    posY=y;
    disparando =false;

    bala = new Sprite1("resources/flecha.png");
    bala->setOrigen(0,2);
    bala->recortarSetTextureRect(0,0,599,4);
    bala->escalar(0.5f,0.4f);
    spriteArma = new Sprite1();

    cargarTexturas();
} 

void Armas::setArma(){
    //segun el tipo ponemos un valor u otro
    if (tipo == "cuchillo"){
        rango = 120; // pixeles
        ataqueArma = 5; //daño solo del cuchillo
        cadencia = 1; //no se en que se mide
    }else if(tipo == "arco"){
        rango = 300; //pixeles
        ataqueArma = 6; //daño que tiene el arma
        cadencia = 1;
    }
}

void Armas::setAtaqueArma(double d){
    ataqueArma =d;
}

void Armas::setRango(int pixelsRango){
    rango = pixelsRango;
}

void Armas::setTipo(std::string t){
    tipo = t;
}


void Armas::cargarTexturas(){
     //aplicamos la textura personalizada
    std::string ruta="";

    if(tipo == "cuchillo"){
    ruta="resources/armas1.png";
    spriteArma->escalar(4.0f,4.0f);
    spriteArma->recortarSetTextureRect(11, 0, 22, 11);
    }else if(tipo == "arco"){
    ruta = "resources/armas1.png";
    spriteArma->escalar(4.0f,4.0f);
    spriteArma->recortarSetTextureRect(0, 0, 11, 11);
    }
    spriteArma->setTextura(ruta);
    spriteArma->setPosicionSprite(posX, posY);
}

int Armas::getRango(){
    return rango;//devuelve el numero de pixels a los que es efectiva
}

double Armas::getAtaqueArma(){
    return ataqueArma;//devuelve el daño del arma
}

std::string Armas::getTipo(){
    return tipo;
}

Sprite1 *Armas::getSpriteBala(){
    return bala;
}

void Armas::setDisparandoT(){
    disparando = true;
}

void Armas::setDisparandoF(){
    disparando = false;
}
bool Armas::getDisparando(){
    return disparando;
}

void Armas::dibujarBala(){
    std::cout << "Dibuja la bala" << endl;
    bala->dibujar("bala",0);
}
 
Sprite1 *Armas::getSpriteArma(){
    return spriteArma;
}