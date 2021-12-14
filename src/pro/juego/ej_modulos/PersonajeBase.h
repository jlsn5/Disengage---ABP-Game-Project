#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Sprite1.h"
using namespace std;

class PersonajeBase{
	private:
		string nombre; //nombre de los personajes
        //estadísticas
        double vida;
        double velocidad;
        double ataque;
        double velocidadAtaque;
		std::string rutaImagen;
		Sprite1 *spritePersonaje;
        double x;
        double y;
        double a, b;
		double pos1;
        double pos2;
        double pos3;
        double pos4;
	public:
		PersonajeBase(); //constructor por defecto


        void setNombre(string n);
        void setX(double cordX);
        void setY(double cordY);
        void restarAtaque(double at);//para cuando cambias de arma quitar el ataque del arma anterior para poner el nuevo ataque
        void sumarVida(double v);
        void sumarVelocidad(double vel);
        void sumarAtaque(double at);
        void sumarVelocidadAtaque(double va);
 		void setRutaImg(std::string r);
		 void setPositionsImg(double a, double b, double c, double d);
        void setVida(double v);
        void setVelocidad(double vel);
        void setAtaque(double at);
        void setVelocidadAtaque(double va);
		void cargarTexturas();
		string getNombre();
        double getVida();
        double getVelocidad();
        double getAtaque();
        double getVelocidadAtaque();
        double getX();
        double getY();
        Sprite1* getSprite();
        void centrar(double posX, double posY);
        void cargarTexturaAnimacion();
};