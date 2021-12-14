#include "O_Trampa.h"
#include <iostream>
#include <string>
using namespace std;

O_Trampa::O_Trampa(std::string es_de){
    if (es_de == "p_azul"){
        duracion = 2;
        tipo = es_de;
        
        this->setTrampa("resources/p_azul.png");
        this->setValor(1);
        
        this->setRutaImg("resources/objetoA.png");
        
        this->setPositionsImg(0,0,506,506);
        
        this->setEscala(0.45);
        
        this->cargarTexturas();
        this->setTipo("trampa");
    }else if(es_de == "glitch"){
        duracion =3;
        tipo =es_de;
        this->setTrampa("resources/glitch1.png");
        this->setValor(2);
        this->setRutaImg("resources/objetoVA.png");
        
        this->setPositionsImg(0,0,506,506);
        
        this->setEscala(0.45);
        
        this->cargarTexturas();
        this->setTipo("trampa");
    }else if(es_de == "sonido"){
        tipo =es_de;
        //FALTA APLICAR SONIDO 
        this->setValor(3);
        this->setRutaImg("resources/objetoV.png");
        this->setPositionsImg(0,0,506,506);
        
        this->setEscala(0.45);
        
        this->cargarTexturas();
        this->setTipo("trampa");
    }else{
        duracion=0;
        tipo="no";
    }
}

void O_Trampa::dibujarTrampa(){
    spriteTrampa->dibujar("obj",1);
}

void O_Trampa::borrar(){
    delete this;
}

int O_Trampa::getTiempoTrampa(){
    return duracion;
}

std::string O_Trampa::getTipoTrampa(){
    return tipo;
}