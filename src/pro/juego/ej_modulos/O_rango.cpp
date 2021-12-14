#include "O_rango.h"
#include <iostream>
using namespace std;


O_rango::O_rango(int rar){
    this -> setRareza(rar);
    this -> setTipo("rango");
    std::string val="";
    if(rar == 1){//calculo la cadena a sumar a la ruta
        val = "1";
    }else if(rar == 2){
        val = "2";
    }else if(rar == 3){
        val = "3";
    }
    rangoLinterna = "linterna";
    rangoLinterna += val;
    rangoLinterna += ".png";
    this -> setImgLinterna(rangoLinterna);

    this->setRutaImg("resources/objetoR.png");
    this->setPositionsImg(0,0,506,506);
    this->setEscala(0.45);

    this->cargarTexturas();
}
O_rango::~O_rango(){

}

std::string O_rango::getRangoLinterna(){
    return rangoLinterna;
}