#include "O_vAtaque.h"
#include <iostream>
using namespace std;

O_vAtaque::O_vAtaque(int r){
    this->setRareza(r); //cambio la rareza por que por defecto es 1, por la que me pasan al crear el objeto
    //con la rareza establezco el nivel del objeto

    this->setTipo("velocidadAtaque");
    //velocidad de ataque base 1
    velAta = 1 * getRareza(); 
    //rareza 1 -> 1 x 1 = 1 velocidad de ataque
    //rareza 2 -> 1 x 2 = 2 velocidad de ataque
    //rareza 3 -> 1 x 3 = 3 velocidad de ataque
    this->setValor(velAta);
    this->setRutaImg("resources/objetoVA.png");
    this->setPositionsImg(0,0,506,506);
    this->setEscala(0.45);

        this->cargarTexturas();

}
O_vAtaque::~O_vAtaque(){}
double O_vAtaque::get_velAta(){
    return velAta;
}