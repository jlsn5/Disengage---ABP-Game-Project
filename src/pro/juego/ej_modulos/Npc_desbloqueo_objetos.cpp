#include "Npc_desbloqueo_objetos.h"
#include <iostream>
#include <sstream>

Npc_desbloqueo_objetos::Npc_desbloqueo_objetos(){
  fondo = new Sprite1("resources/desbloqueo.png");
  fondo->setOrigen(0,0);
  fondo->setPosicionSprite(0, motor->getCentroVista() - 460);
  spriteNPC = new Sprite1();
  cantidad = 2;
  texto = new Sprite1();
  texto->setOrigen(0,0);
  texto->setPos(700, motor->getCentroVista() + 280, 0);
  texto->setFont("resources/Ara.TTF");
  texto->setColor("red", 0);
  texto->setText("Siguiente Nivel", 0);
}

int Npc_desbloqueo_objetos::getCantidad(){
  return cantidad;
}

Npc_desbloqueo_objetos::Npc_desbloqueo_objetos(PersonajePrincipal &p){
  fondo = new Sprite1("resources/desbloqueo.png");
  fondo->setOrigen(0,0);
  fondo->setPosicionSprite(0, motor->getCentroVista() - 460);
  spriteNPC = new Sprite1();
  prota = &p;
  texto = new Sprite1();
  texto->setOrigen(0,0);
  texto->setPos(700, motor->getCentroVista() + 280, 0);
  texto->setFont("resources/Ara.TTF");
  texto->setColor("red", 0);
  texto->setText("Siguiente Nivel", 0);
}

void Npc_desbloqueo_objetos::colocarObjetos(){
    
    fondo->dibujar("npc",0);
    
    double varposx = 606;
    double varposy = motor->getCentroVista() - 460;
    
    std::stringstream descripcionRar;
    std::stringstream descripcionVal1;
    std::stringstream descripcionVal2;
    std::string descripcionT="";
    texto->dibujar("npc", -1);
    spriteNPC->setFont("resources/Ara.TTF");
    spriteNPC->setColor("red",0);
    spriteNPC->setTam(20);
    //esto es para limpiar variables IMPORTANTE
    descripcionRar.str(std::string());
    descripcionVal1.str(std::string());
    descripcionVal2.str(std::string());
    //creacion del mensaje de la descripcion de los objetos en la pantalla de mejora
    if(prota->getObjetos().size() > 0){
      descripcionT = "Objeto de " + prota->getObjetos()[0]->getTipo() +"\n" + "Nivel: ";
      descripcionRar << prota->getObjetos()[0]->getRareza();
      descripcionT += descripcionRar.str();
      descripcionT += "\n";
    }
    
    descripcionVal1 << "Rango de linterna \n modificable"; //descripcion del objeto
    descripcionT += descripcionVal1.str();

    spriteNPC->setTexto(descripcionT);
    spriteNPC->setPos(varposx + 120, varposy + 73, -1);
     cout << "va a dibujar el texto" << endl;
    spriteNPC->dibujar("npc",0);
    cout << "dibuja el texto" << endl;
    varposy += 113;
      
}

void Npc_desbloqueo_objetos::setPersonaje(PersonajePrincipal *p){
  prota = p;
}

Sprite1* Npc_desbloqueo_objetos::getContinuar(){
    return texto;
}