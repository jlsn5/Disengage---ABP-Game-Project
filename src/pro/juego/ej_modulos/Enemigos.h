#pragma once
#include "SFML/Graphics.hpp"

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "./PersonajeBase.h"
#include "./PersonajePrincipal.h"

using namespace std;

class Enemigos : public PersonajeBase{
    private:
        //caracteristicas generales de los personajes
        //string nombre; //nombre de los personajes

        //estadísticas
        //double vida;
        //double velocidad;
        //double ataque;
        //double velocidadAtaque;
        float rangoDeteccion;
        bool detectado;
        int frameActual;
        bool transformadoBoss;
        int fase;
        bool cargacaminar;
        bool cargaataque1;
        bool cargaataque2;
        bool vueltaanimacion;
        int contarvecesataque1;
    public:

        Enemigos(int e,sf::Texture texture); //constructor por defecto

        void detectarPersonaje(float distancia);
		float calcularDistancia(PersonajePrincipal* personaje);
		void golpe(PersonajePrincipal* personaje);
        void movimiento(PersonajePrincipal* personaje);
        void animarEnemigo();


        //void setNombre(string n);
        //void setVida(double v);
        //void setVelocidad(double vel);
        //void setAtaque(double at);
        //void setVelocidadAtaque(double va);



        //string getNombre();
        //double getVida();
        //double getVelocidad();
        //double getAtaque();
        //double getVelocidadAtaque();
        float getRangoDeteccion();
        bool getDetectado();

};