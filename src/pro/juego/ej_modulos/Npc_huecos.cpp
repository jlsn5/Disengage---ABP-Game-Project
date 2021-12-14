#include "Npc_huecos.h"
#include <iostream>
#include <sstream>

Npc_huecos::Npc_huecos(){
    spriteNpc.setTextura("resources/desbloqueo.png");
    spriteNpc.setOrigen(0,0);
    spriteNpc.setOrigen(0, 0);
}

void Npc_huecos::dibujarNpcHuecos(){
    spriteNpc.dibujar("npc",0);
}