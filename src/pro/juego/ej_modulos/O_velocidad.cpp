#include "O_velocidad.h"
#include <iostream>
using namespace std;


O_velocidad::O_velocidad(int r){
    this->setRareza(r); //cambio la rareza por que por defecto es 1, por la que me pasan al crear el objeto
    //con la rareza establezco el nivel del objeto
    
    //la base de la velocidad será 5 (probando) 
    this->setTipo("velocidad");
    velocidad = 2 * getRareza();
    //rareza 1 -> 2 x 1 = 2 velocidad
    //rareza 2 -> 2 x 2 = 4 velocidad
    //rareza 3 -> 2 x 3 = 6 velocidad
    this->setValor(velocidad);
    
    this->setRutaImg("resources/objetoVel.png");
    this->setPositionsImg(0,0,506,506);
    this->setEscala(0.45);

    this->cargarTexturas();

}
O_velocidad::~O_velocidad(){}
double O_velocidad::getVelocidad(){
    return velocidad;
}