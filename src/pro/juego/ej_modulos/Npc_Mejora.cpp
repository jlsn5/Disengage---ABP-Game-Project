#include "Npc_Mejora.h"
#include <iostream>
#include <sstream>


Npc_Mejora::Npc_Mejora(){
    fondo = new Sprite1("resources/npcmejora.png");
    spriteNPC = new Sprite1();
    //fondo->setTextura("resources/npcmejora.png");
    spriteNPC->setOrigen(0,0);
    fondo->setOrigen(0,0);
    fondo->setPosicionSprite(0,motor->getCentroVista() - 460);
    spriteNPC->setFont("resources/Ara.TTF");
    spriteNPC->setColor("red", 0);
    spriteNPC->setTam(20);
    
    monedaje = new Sprite1();
    monedaje->setOrigen(0,0);
    monedaje->setFont("resources/Ara.TTF");
    monedaje->setColor("red", 0);
    monedaje->setTam(20);
    texto = new Sprite1();
    texto->setOrigen(0,0);
    texto->setPos(700, motor->getCentroVista() + 280, 0);
    texto->setFont("resources/Ara.TTF");
    texto->setColor("red", 0);
    texto->setText("Siguiente Nivel", 0);
}

void Npc_Mejora::colocarObjetos(PersonajePrincipal *prota, int money) {
    fondo->dibujar("npc",0);

    double varposx = 606;
    double varposy = motor->getCentroVista() - 460 + 88;//motor->getCentroVista() - 460 +
    std::stringstream moneda;
    std::string monedaT;
    moneda.str(std::string());
    moneda << money << " $";
    monedaT += moneda.str();
    monedaje->setTexto(monedaT);
    monedaje->setPos(75, motor->getCentroVista()- 460 + 15, -1);
    monedaje->dibujar("npc", 11);
    std::stringstream descripcionRar;
    std::stringstream descripcionVal1;
    std::stringstream descripcionVal2;
    std::stringstream descripcionP;
    std::string descripcionT="";
    texto->dibujar("npc", -1);
   
    
    for (int i =0; i < prota->getObjetos().size();i++){ //objetos ordenados segun el huec
    //cout << "veces : " << i+1<<endl;

        prota->getObjetos()[i]->getSpriteObjeto()->setPosicionSprite(varposx,varposy);
        prota->getObjetos()[i]->getSpriteObjeto()->dibujar("obj",0);
        //esto es para limpiar variables IMPORTANTE
        descripcionRar.str(std::string());
        descripcionVal1.str(std::string());
        descripcionVal2.str(std::string());
        descripcionP.str(std::string());
        //creacion del mensaje de la descripcion de los objetos en la pantalla de mejora
        descripcionT = "Objeto de " + prota->getObjetos()[i]->getTipo() +"\n" + "Nivel: ";
        descripcionRar << prota->getObjetos()[i]->getRareza();
        descripcionT += descripcionRar.str();
        descripcionT += "\nAhora: ";
        descripcionVal1 << prota->getObjetos()[i]->getValor();
        descripcionT += descripcionVal1.str();
        descripcionT += " Mejorado: ";
        descripcionVal2 << (prota->getObjetos()[i]->getValor()/prota->getObjetos()[i]->getRareza()) * (prota->getObjetos()[i]->getRareza()+1);
        descripcionT += descripcionVal2.str();
        descripcionP << "  "<< prota->getObjetos()[i]->getRareza()*50 << " $";
        descripcionT += descripcionP.str();
        //cout << "descripcion: " << descripcionT<<endl;
        spriteNPC->setTexto(descripcionT);
        spriteNPC->setPos(varposx + 120, varposy-15, -1);
        spriteNPC->dibujar("npc",11);
        varposy += 113;
    }
}

Sprite1* Npc_Mejora::getFondo(){
    return fondo;
}

Sprite1* Npc_Mejora::getContinuar(){
    return texto;
}

