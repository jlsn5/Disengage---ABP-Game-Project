#include "O_vida.h"
#include <iostream>
using namespace std;

O_vida::O_vida(int r){
    this->setRareza(r); //cambio la rareza por que por defecto es 1, por la que me pasan al crear el objeto
    //con la rareza establezco el nivel del objeto

    this->setTipo("vida");
    //vida base 100
    vida = 20 * getRareza(); 
    //rareza 1 -> 1*20 = 20 vida
    //rareza 2 -> 2*20 = 40 vida
    //rareza 3 -> 3*20 = 60 vida
    this->setValor(vida);
    this->setRutaImg("resources/objetoV.png");
    this->setPositionsImg(0,0,506,506);
    this->setEscala(0.45);
    this->cargarTexturas();

}
O_vida::~O_vida(){}

double O_vida::getVida(){
    return vida;
}