#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PersonajePrincipal.h"
#include "Motor2D.h"

class Npc_Mejora{
    private:
        Motor2D *motor = Motor2D::getInstance();
        Sprite1 *spriteNPC;
        Sprite1 *fondo;
        Sprite1 *monedaje;
        Sprite1 *texto;
    public:
        Npc_Mejora();
        void colocarObjetos(PersonajePrincipal *p, int money);
        Sprite1* getFondo();
        Sprite1* getContinuar();
        
};  