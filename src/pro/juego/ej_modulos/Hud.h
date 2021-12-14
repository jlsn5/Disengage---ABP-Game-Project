#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Partida.h"
#include "Sprite1.h"
#include "Motor2D.h"
#include "PersonajePrincipal.h"


class Hud{
    private:
        int huecosObjeto;
        int huecosArma;
        int mov1;
        int mov2;
        int mov3;
        int mov4;
        int vidaActual;
        
        Sprite1 armaSelect;
        Sprite1 spriteArmas;
        Sprite1 spriteObjeto;
        Sprite1 spriteHM;
        Sprite1 spriteMoneda;
        Sprite1 spriteVida;
        Sprite1 spriteBarraVida;
        Sprite1 malditoObjeto;
        Sprite1 habilidad;
        Motor2D *motor= Motor2D::getInstance();
        Sprite1 monedas;
        Sprite1 *temporizador;
    public:
        Hud();
        Hud(int armas, int objetos);
        void dibujarHud(PersonajePrincipal *p, int money);
        int calcularCantidadVida(PersonajePrincipal *p);
        void reiniciarPos();
        void actualizarTemp(int c);
    };