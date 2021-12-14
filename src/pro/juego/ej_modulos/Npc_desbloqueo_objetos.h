#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PersonajePrincipal.h"
#include "Motor2D.h"

class Npc_desbloqueo_objetos{
    private:
        Sprite1 *spriteNPC;
        Sprite1 *fondo;
        PersonajePrincipal *prota;
        Motor2D *motor = Motor2D::getInstance();
        int cantidad;
        Sprite1 *texto;
    public:
        Npc_desbloqueo_objetos();
        Npc_desbloqueo_objetos(PersonajePrincipal &p);
        void colocarObjetos();
        int getCantidad();
        void setPersonaje(PersonajePrincipal *p);
        Sprite1* getContinuar();
};