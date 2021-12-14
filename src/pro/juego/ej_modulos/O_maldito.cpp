#include "O_maldito.h"
#include <iostream>
using namespace std;

O_maldito::O_maldito(int rar){
    this->setRareza(1); //cambio la rareza por que por defecto es 1, por la que me pasan al crear el objeto
    //con la rareza establezco el nivel del objeto

    this->setTipo("maldito");
    //ataque base 10
    maldicionVelocidad = -1 * 2; 

    this->setValor(maldicionVelocidad);

    this->setRutaImg("resources/maldito1.png");
    this->setPositionsImg(0,0,506,506);
    this->setEscala(0.45);
 
    this->cargarTexturas();
}

O_maldito::~O_maldito(){
    
}
double O_maldito::getMaldicion(){
    return maldicionVelocidad;
}