//Objetos trampa
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include "Objeto.h"
#include "Sprite1.h"
class O_Trampa : public Objeto{
    private:
        int duracion; //tiempo que tarda el objeto trampa actuando
        std::string tipo; //tipo de objeto trampa 
        Sprite1 *spriteTrampa; //sprite de los objeto trampa
    public:
        //O_Trampa();
        O_Trampa(std::string es_de);

        void dibujarTrampa();
        void borrar();

        int getTiempoTrampa(); //tiempo que dura la trampa "duracion"
        std::string getTipoTrampa();
};