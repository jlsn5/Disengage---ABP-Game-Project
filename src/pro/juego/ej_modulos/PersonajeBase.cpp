#include "PersonajeBase.h"
#include <iostream>
using namespace std;

PersonajeBase::PersonajeBase(){ //los valores reales se aplicarán en las clases hijas
    nombre = "No hay";
    vida = 1;
    velocidad = 1;
    ataque = 1;
    velocidadAtaque = 1;
    spritePersonaje = new Sprite1();
}


void PersonajeBase::setNombre(string n){
    cout << "Nombre personaje: " << n << endl;
    if (n != ""){
        nombre = n;
    }
}


void PersonajeBase::sumarVida(double v){
    if (vida >= 0){
        vida += v;
    }
    
}
void PersonajeBase::restarAtaque(double at){
    ataque = ataque - at;
}
void PersonajeBase::sumarVelocidad(double vel){
    if (vel > 0){
        velocidad +=vel;
    }
}
void PersonajeBase::sumarAtaque(double at){
    if(at>0){
        ataque += at;
    }
}
void PersonajeBase::sumarVelocidadAtaque(double va){
    if (va>0){
        velocidadAtaque +=va;
    }
}


void PersonajeBase::setVida(double v){
    if (vida > 0){
        vida = v;
    }
    if(v == -100){
        vida = 100;
    }
}

void PersonajeBase::setVelocidad(double vel){
    if (vel >= 0){
        velocidad =vel;
    }
}
void PersonajeBase::setAtaque(double at){
    if(at>0){
        ataque = at;
    }
}
void PersonajeBase::setVelocidadAtaque(double va){
    if (va>0){
        velocidadAtaque =va;
    }
}


string PersonajeBase::getNombre(){
    return nombre;
}
double PersonajeBase::getVelocidad(){
    return velocidad;
}
double PersonajeBase::getVelocidadAtaque(){
    return velocidadAtaque;
}
double PersonajeBase::getVida(){
    return vida;
}
double PersonajeBase::getAtaque(){
    return ataque;
}

void PersonajeBase::setPositionsImg(double a, double b, double c, double d){
  pos1 = a;
  pos2 = b;
  pos3 = c;
  pos4 = d;
}
void PersonajeBase::setX(double cordX){
    x=cordX;
    spritePersonaje->setPosicionSprite(x,y);
}
void PersonajeBase::setY(double cordY){
    y=cordY;
    spritePersonaje->setPosicionSprite(x,y);
}
double PersonajeBase::getX(){
    return x;
}
double PersonajeBase::getY(){
    return y;
}

void PersonajeBase::cargarTexturas(){
     //aplicamos la textura personalizada
    spritePersonaje->setTextura(rutaImagen);
    spritePersonaje->recortarSetTextureRect(pos1, pos2,pos3, pos4);
    spritePersonaje->escalar(1, 1);
    int coord_x = this->x;
    int coord_y = this->y;
    // Lo dispongo en el centro de la pantalla
    spritePersonaje->setOrigen(a, b);
    //Para que empiece debajo del mapa
}
void PersonajeBase::cargarTexturaAnimacion(){
    spritePersonaje->recortarSetTextureRect(pos1, pos2,pos3, pos4);
    spritePersonaje->escalar(1, 1);
    int coord_x = this->x;
    int coord_y = this->y;
    // Lo dispongo en el centro de la pantalla
    spritePersonaje->setOrigen(a, b);
    //Para que empiece debajo del mapa
}

void PersonajeBase::setRutaImg(std::string r){
    rutaImagen = r;
}

Sprite1* PersonajeBase::getSprite(){
    return spritePersonaje;
}

void PersonajeBase::centrar(double posX, double posY){
    this->a = posX;
    this->b = posY;
}