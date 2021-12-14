
#include "O_ataque.h"
#include <iostream>
using namespace std;

O_ataque::O_ataque(int r){
    this->setRareza(r); //cambio la rareza por que por defecto es 1, por la que me pasan al crear el objeto
    //con la rareza establezco el nivel del objeto

    this->setTipo("ataque");
    //ataque base 10
    ataque = 3 * getRareza(); 
    //rareza 1 -> 3 x 1 = 3 ataque
    //rareza 2 -> 3 x 2 = 6 ataque
    //rareza 3 -> 3 x 3 = 9 ataque
    this->setValor(ataque);

    this->setRutaImg("resources/objetoA.png");
    this->setPositionsImg(0,0,506,506);
    this->setEscala(0.45);
 
    this->cargarTexturas();

}
O_ataque::~O_ataque(){
    
}
double O_ataque::getAtaque(){
    return ataque;
}