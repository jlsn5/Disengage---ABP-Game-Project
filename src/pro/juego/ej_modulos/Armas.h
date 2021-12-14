#pragma once
#include "SFML/Graphics.hpp"
#include "Sprite1.h"
class Armas{
	private:
	 	std::string tipo; 
		int rango;//rango del arma
		double ataqueArma;//daño que hace el arma, habra que sumarle el daño del jugador
		int cadencia;//velocidad a la que dispara el arma
		Sprite1 *spriteArma;
		double posX;
        double posY;
		Sprite1 *bala;

		bool disparando; //booleano que controla si se ha disparado o no el arma
	public:
		Armas();
		Armas(std::string t);
		//Armas(std::string t,double x, double y);
		Armas(std::string t,double x, double y);
		void setArma();
		void setAtaqueArma(double d);
        void setRango(int pixelsRango);
        void setTipo(std::string t);

		void cargarTexturas();
        double getAtaqueArma();//devuelve el daño del arma
        std::string getTipo();
        int getRango();
		Sprite1 *getSpriteBala();
		Sprite1 *getSpriteArma();
		void setDisparandoT();
		void setDisparandoF();
		bool getDisparando();

		void dibujarBala();
};