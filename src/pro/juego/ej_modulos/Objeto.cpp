#include "Objeto.h"
#include <iostream>
#include <string>
using namespace std;


bool Objeto::operator==(const Objeto &obj) const{
  return rareza == obj.rareza && tipo == obj.tipo;
}

Objeto &Objeto::operator = (const Objeto &de){
  rareza = de.rareza; 
  tipo = de.tipo; 
  valor = de.valor;
  recogido = de.recogido;
  
  return *this; // devuelvo el objeto implicito.
  // 

}

Objeto::Objeto(const Objeto& o){
    rareza = o.rareza; 
    tipo = o.tipo; 
    valor = o.valor;
    recogido = o.recogido;
}



Objeto::Objeto(){
  rareza=1;
  tipo="";
  valor=0;
  recogido = false;
  //el tipo por defecto no se inicializa
  spriteObjeto = new Sprite1();

}

Objeto::Objeto(std::string tip, int i){
  tipo = tip;
  spriteObjeto = new Sprite1();
  switch(i){
    case 1:
      spriteObjeto->setTextura("resources/pieza1.png");
      spriteObjeto->setPosicionSprite(300, 600);
      break;
    case 2:
      spriteObjeto->setTextura("resources/pieza2.png");
      spriteObjeto->setPosicionSprite(100, 200);
      break;
    case 3:
      spriteObjeto->setTextura("resources/pieza3.png");
      spriteObjeto->setPosicionSprite(700, 400);
      break;
    case 4: 
      spriteObjeto->setTextura("resources/pieza4.png");
      spriteObjeto->setPosicionSprite(100, 700);
      break;
    default:
      spriteObjeto->setTextura("resources/pieza1.png");
      spriteObjeto->setPosicionSprite(300, 600);
      break;
  }
  
  spriteObjeto->escalar(0.1, 0.1);
  recogido = false;
}


void Objeto::cargarTexturas(){
    spriteObjeto->setTextura(rutaImagen);
    spriteObjeto->escalar(escala,escala);
    spriteObjeto->recortarSetTextureRect(pos1,pos2,pos3,pos4);
    spriteObjeto->setPosicionSprite(pos_x,pos_y);
}

Objeto::~Objeto(){

}

void Objeto::setRutaImg(std::string r){
  rutaImagen = r;
}
void Objeto::setImgLinterna(std::string lint){
  linterna = lint;
}
std::string Objeto::getImgLinterna(){
  return linterna;
}

void Objeto::setPositionsImg(double a, double b, double c, double d){
  pos1 = a;
  pos2 = b;
  pos3 = c;
  pos4 = d;
}
void Objeto::setEscala(double escalado){
  escala = escalado;
}


void Objeto::setRareza(int r){
    if (r != 0 && r >0 && r<=3){ //por defecto rareza es 1 la más básica. Hasta 5 rarezas
    rareza = r;
  }else {
    rareza = 1;
  }
  if (rareza > 1){
    this->setValor( rareza*(valor/(rareza-1)));
  }
}

void Objeto::setTipo(std::string tip){
  this->tipo = tip;
}

int Objeto::getRareza(){
    return rareza; //devuelve la rareza del objeto
}
void Objeto::setValor(double val){
  //this->valor = val;
  this->valor = val;
}

double Objeto::getValor(){
  return valor;
}

void Objeto::setRecogido(){
  this->recogido = true;
}

double Objeto::getRecogido(){
  return recogido;
}

std::string Objeto::getTipo(){
    return tipo; //devuelve la rareza del objeto
}

void Objeto::setPosX(double cord_x){ 
  this->pos_x = cord_x;
  setPositions();
}
void Objeto::setPosY(double cord_y){ 
  this->pos_y = cord_y;
  setPositions();
}

double Objeto::getPosX(){
  return pos_x;
}
double Objeto::getPosY(){
  return pos_y;
}

void Objeto::setPositions(float cord_x, float cord_y){
  setPosX(cord_x);
  setPosY(cord_y);
}
void Objeto::setPositions(){
  setPosX(this->getPosX());
  setPosY(this->getPosY());
}
Sprite1* Objeto::getSpriteObjeto(){
  return spriteObjeto;
}

Sprite1* Objeto::getSpriteTrampa(){
  return trampa;
}

void Objeto::setTrampa(std::string ruta){
  trampa = new Sprite1(ruta);
}