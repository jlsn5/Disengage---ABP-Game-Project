
#include "Hud.h"

#include <iostream>
#include <sstream>
using namespace std;

Hud::Hud(){
    huecosObjeto = 4;
    huecosArma = 2;

    spriteArmas.setTextura("resources/hud.png");
    spriteArmas.setOrigen(0,0);
    spriteArmas.recortarSetTextureRect(0 * 0, 0 * 16, 16, 13);
    spriteArmas.setPosicionSprite(3, 3);
    spriteArmas.escalar(4.0f, 4.0f);

    armaSelect.setTextura("resources/selectArma.png");
    armaSelect.setOrigen(0,0);
    armaSelect.recortarSetTextureRect(0 * 0, 0 * 10, 10, 13);
    armaSelect.setPosicionSprite(3, 3);
    armaSelect.escalar(4.0f, 4.0f);

    spriteObjeto.setTextura("resources/hud.png");
    spriteObjeto.setOrigen(0,0);
    spriteObjeto.recortarSetTextureRect(16, 0, 16, 13);
    spriteObjeto.setPosicionSprite(960-15*4, 3);
    spriteObjeto.escalar(4.0f, 4.0f);    

    spriteHM.setTextura("resources/hud.png");
    spriteHM.setOrigen(0,0);
    spriteHM.recortarSetTextureRect(32, 0, 13, 10);
    spriteHM.setPosicionSprite(0, 15*4);
    spriteHM.escalar(4.0f, 4.0f); 

    spriteMoneda.setTextura("resources/hud.png");
    spriteMoneda.setOrigen(0,0);
    spriteMoneda.recortarSetTextureRect(46, 0, 6, 6);
    spriteMoneda.setPosicionSprite(30*4, 2*4);
    spriteMoneda.escalar(4.0f, 4.0f); 

    spriteVida.setTextura("resources/vida.png");
    spriteVida.setOrigen(0,0);
    spriteVida.recortarSetTextureRect(0, 0, 30, 4);
    spriteVida.setPosicionSprite(30*4, 8.5*4);
    spriteVida.escalar(4.0f, 4.0f); 


    spriteBarraVida.setTextura("resources/vida.png");
    spriteBarraVida.setOrigen(0,0);
    spriteBarraVida.recortarSetTextureRect(30, 0, 57, 2);
    spriteBarraVida.setPosicionSprite(30*4, 8.5*4);
    spriteBarraVida.escalar(4.0f, 4.0f); 
    monedas.setTexto("0");
    monedas.setFont("resources/Ara.TTF");
    monedas.setColor("red",0);
    monedas.setTam(12);
    
    temporizador = new Sprite1();
    temporizador->setFont("resources/Ara.TTF");
    temporizador->setColor("white", 0);
    temporizador->setTexto("15:00");
    vidaActual =1; //numero de escalado para hacer disminuir la vida
}


Hud::Hud(int armas, int objetos){
    //Motor2D *motor = Motor2D::getInstance();
    huecosObjeto = objetos;
    huecosArma = armas;
    spriteArmas.setTextura("resources/hud.png");
    spriteArmas.setOrigen(0,0);
    spriteArmas.recortarSetTextureRect(0 * 0, 0 * 16, 16, 13);
    //spriteArmas.setPosicionSprite(3, 3);
    spriteArmas.escalar(4.0f, 4.0f);

    spriteObjeto.setTextura("resources/hud.png");
    spriteObjeto.setOrigen(0,0);
    spriteObjeto.recortarSetTextureRect(16, 0, 16, 13);
    //spriteObjeto.setPosicionSprite(960-15*4, 3);
    spriteObjeto.escalar(4.0f, 4.0f);    

    armaSelect.setTextura("resources/selectArma.png");
    armaSelect.setOrigen(0,0);
    armaSelect.recortarSetTextureRect(0 * 0, 0 * 10, 10, 13);
    //armaSelect.setPosicionSprite(3, 3);
    armaSelect.escalar(4.0f, 4.0f);

    spriteHM.setTextura("resources/hud.png");
    spriteHM.setOrigen(0,0);
    spriteHM.recortarSetTextureRect(32, 0, 13, 10);
    //spriteHM.setPosicionSprite(0, 15*4);
    spriteHM.escalar(4.0f, 4.0f); 

    spriteMoneda.setTextura("resources/hud.png");
    spriteMoneda.setOrigen(0,0);
    spriteMoneda.recortarSetTextureRect(46, 0, 6, 6);
    spriteMoneda.setPosicionSprite(30*4, 2*4);
    spriteMoneda.escalar(4.0f, 4.0f); 

    spriteVida.setTextura("resources/vida.png");
    spriteVida.setOrigen(0,0);
    spriteVida.recortarSetTextureRect(0, 0, 30, 4);
    spriteVida.setPosicionSprite(30*4, 8.5*4);
    spriteVida.escalar(4.0f, 4.0f); 

    spriteBarraVida.setTextura("resources/vida.png");
    spriteBarraVida.setOrigen(0,0);
    spriteBarraVida.recortarSetTextureRect(30, 0, 57, 4);
    spriteBarraVida.setPosicionSprite(30*4, 8.5*4);
    spriteBarraVida.escalar(4.0f, 4.0f); 

    malditoObjeto.setTextura("resources/maldito1.png");
    malditoObjeto.setOrigen(0,0);
    //malditoObjeto.setPosicionSprite(30, 15.3*4);
    malditoObjeto.escalar(0.3, 0.3);
    //malditoObjeto.getSpritePuntero()->rotate(30.0);

    habilidad.setTextura("resources/dash.png");
    habilidad.setOrigen(0,0);
    //malditoObjeto.setPosicionSprite(30, 15.3*4);
    habilidad.escalar(0.25, 0.25);
    

    monedas.setFont("resources/Ara.TTF");
    monedas.setColor("red",0);
    monedas.setOrigen(0,0);
    monedas.setTam(12);
    monedas.setTexto("0");

    
    mov1 = motor->getLongitud()-477;
    mov2 = motor->getLongitud()-420;
    mov3 = motor->getLongitud()-472;
    mov4 = motor->getLongitud()-450;

    temporizador = new Sprite1();
    temporizador->setFont("resources/Ara.TTF");
    temporizador->setColor("white", 0);
    temporizador->setText("15:00", 0);
    temporizador->setPos(1002, -60, 0);
    temporizador->escalar(7.0, 7.0);

    vidaActual =1;
}

void Hud::dibujarHud(PersonajePrincipal *p, int money){
    int pos = 0;
    for(int i = 0; i < huecosArma; i++){
        if (i<p->getArmas().size()){
            if(p->getArmas()[i] != NULL){
                if (p->getArmas()[i]->getTipo() == "cuchillo"){
                    p->getArmas()[i]->getSpriteArma()->setPosicionSprite((i)*(14*4)+5, mov1+5);
                }else{
                    p->getArmas()[i]->getSpriteArma()->setPosicionSprite((i)*(14*4)+5, mov1+5);
                }
                p->getArmas()[i]->getSpriteArma()->dibujar("hud",0);
            }
        }
        //dibujo espacio armas
        spriteArmas.dibujar("hud", 0);
        //window.draw(spriteArmas);
        spriteArmas.setPosicionSprite((i)*(14*4), mov1);
        if (i == p->getSeleccionada()){
            pos = i;
        }

    }

    for(int i = 0; i < huecosObjeto; i++){
        //dibujo espacio objetos
        if (i<p->getObjetos().size()){
            if(p->getObjetos()[i] != NULL){
                p->getObjetos()[i]->getSpriteObjeto()->setPosicionSprite(960-14*4 * (i+1) , mov1);
                p->getObjetos()[i]->getSpriteObjeto()->dibujar("hud",0);
            }
        }
        spriteObjeto.dibujar("hud", 0);
        spriteObjeto.setPosicionSprite(956-14*4 * (i+1) , mov1);
    }

    if(p->getMaldito() == true){
        malditoObjeto.dibujar("hud", 0);
        malditoObjeto.setPosicionSprite((14*4)+15, mov1+63);
    }
    if(p->getHabilidadDispo() == 1){
        habilidad.dibujar("hud",0);
        habilidad.setPosicionSprite(13,mov1+63);
    }
    mov1+=motor->getVelocidad();
    for(int a = 0; a < 2; a++){

        if (p->getHabilidadDispo() == 1 && p->puedoUsarHabilidad(-1) == false){
            if (a == 1){
                spriteHM.setTextura("resources/select-skill.png");
                //spriteHM.setOrigen(0,0);
                spriteHM.recortarSetTextureRect(0, 0, 13, 9.5);
                spriteHM.escalar(4.0f,4.0f);
                spriteHM.dibujar("hud", 0);
                
            }
            if (a != 1){
                spriteHM.setTextura("resources/hud.png");
                spriteHM.setOrigen(0,0);
                spriteHM.recortarSetTextureRect(32, 0, 13, 10);
                //spriteHM.setPosicionSprite(0, 15*4);
                spriteHM.escalar(4.0f, 4.0f); 
                spriteHM.dibujar("hud", 0);
            }
            

        }else{
            spriteHM.setTextura("resources/hud.png");
            spriteHM.setOrigen(0,0);
            spriteHM.recortarSetTextureRect(32, 0, 13, 10);
            //spriteHM.setPosicionSprite(0, 15*4);
            spriteHM.escalar(4.0f, 4.0f); 
            spriteHM.dibujar("hud", 0);
        }
        
        //window.draw(spriteHM);
        spriteHM.setPosicionSprite(14*4 * (a) , mov2+5);
    }
    mov2+=motor->getVelocidad();
    spriteMoneda.dibujar("hud", 0);
    
    std::string mone;
    std::stringstream mon;
    mon.str(std::string());
    mon <<money;
    mone =mon.str();
    monedas.setText(mone,0);
    monedas.setTam(25);

    spriteVida.dibujar("hud", 0);
    spriteBarraVida.dibujar("hud",0);
    
    monedas.dibujar("menu",1); //pongo menu pero es texto de las monedas
    
    spriteMoneda.setPosicionSprite(30*4,mov3);
    monedas.setPos(37*4,mov3-6,0);
    spriteVida.setPosicionSprite(30*4,mov4);
    spriteBarraVida.setPosicionSprite(30*4,mov4+4);

    //falta regla de tres 
    spriteBarraVida.recortarSetTextureRect(30, 0, calcularCantidadVida(p), 4); //30 entera

    mov3+=motor->getVelocidad();
    mov4+=motor->getVelocidad();

    //window.draw(spriteMoneda);
    //window.draw(spriteVida);
    if (pos == 0){
        armaSelect.setPosicionSprite(pos*(17*4)+12, mov1+3);//3
    }else{
        armaSelect.setPosicionSprite(pos*(17*4), mov1+7);//7
    }
    armaSelect.dibujar("hud",0);
     //temporizador->dibujar("hud", -3);
    temporizador->dibujar("hud", -3);
    
}

int Hud::calcularCantidadVida(PersonajePrincipal *p){ 
    // 100 +20por obj --- 30
    // vida --- x

    //cuando empiezas tienes 100 pero si coges un objeto no te curas +20, si no que la vida max aumenta en 20 por lo tanto proporcionalmente tienes mas 
    int sumaDeLosObjetosDeVida =0 ;
    for (int i = 0; i< p->getObjetos().size();i++){
        if (p->getObjetos()[i]->getTipo() == "vida"){
            sumaDeLosObjetosDeVida += p->getObjetos()[i]->getValor();
        }
    }

    int vidaPix = 0;;
    int aux;
    aux = p->getVida() * 30;
    vidaPix = aux/(100 + sumaDeLosObjetosDeVida);
    //cout<<"vida "<<p->getVida()<<endl;
    //cout <<"vida en pixeles"<<vidaPix<<endl;
    return vidaPix;
}

void Hud::reiniciarPos(){
    if(motor->getLongitud() == 960){
        motor->setLongitud(960/2);
    }
    mov1 = motor->getLongitud()-477;
    mov2 = motor->getLongitud()-420;
    mov3 = motor->getLongitud()-472;
    mov4 = motor->getLongitud()-450;
}

void Hud::actualizarTemp(int c){
    string str;
    stringstream ss;
    if(c != 0){
        ss << c;  
        ss >> str;
        temporizador->setText(str, 0);
    }else{
        temporizador->setText("", 0);
    }
    
    temporizador->setPos(480, 150, 0);
    
}