#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "PersonajeBase.h"
#include "O_ataque.h"
#include "O_velocidad.h"
#include "O_vAtaque.h"
#include "O_vida.h"
#include "O_rango.h"
#include "O_Trampa.h"
#include "O_maldito.h"
#include "Objeto.h"
#include "Armas.h"
#include "Linterna.h"
using namespace std;
class Linterna;
class PersonajePrincipal : public PersonajeBase{
	private:
                Armas *a1;
                Armas *a2;
 		std::vector<Objeto*> huecosObjetos;
                std::vector<Armas*> huecosArmas; //array de armas que posee en cada momento
                Objeto* recogido;//objeto que recoge y puede intercambiar
                int objetosactuales;//numero de huecos
                int armasactuales;//numero de armas
                int seleccionada; //posicion del arma seleccionada en ese momento
                std::string linternaPersonaje;
                bool trampeado;
                bool malditoCogido;
                int posMaldito;
                Linterna *linterna;
                int fragmentos[3];
                int habilidadDisponible;
                bool modoHudHabilidad;
                double tipotrampeado;
                int frameActual;
	public:
		PersonajePrincipal(); //valores por defecto 
                PersonajePrincipal(string name); //valores procedentes de un posible creador de personaje 
                
                bool cogerObjeto(Objeto *recogido); //función que actualizará el array de objetos del personaje //tambien se llevan acabo intercambios si estan a tope los huecos
                void intercambiarObjeto(int posicion);
                std::vector<Objeto*> &getObjetos();
                //Objeto *getObjetos(); //devuelve los objetos que lleva el jugador en ese momento
                
                void setLinternaPersonaje(std::string l);
                std::string getLinternaPersonaje();
                void aumentarHuecosDeObjetos();//aumenta la capacidad de llevar objetos del jugador a uno mas;  
                int getNumHuecosObjetos();
                //de base el jugador ya lleva dos armas asi que ahora solo puede intercambiar armas por las que ya lleva
                void intercambiarArma(Armas *recogido, int posicion);
                void setArmasIniciales(Armas *arm1, Armas *arm2);//inicialmente empieza con dos armas
                void aumentarHuecosDeArmas();//aumenta la capacidad de llevar armas del jugador a una mas;
                int getNumHuecosArmas(); //huecos de armas actuales
                void calcularAtaque(int seleccion);//esta funcion calcula el daño en conjunto del pj y el arma
                std::vector<Armas*> &getArmas(); //array de armas
                int getSeleccionada();
                void setSeleccionada(int pos);//cambiar posicion seleccionada
                void setRecogido(Objeto *o);
                Objeto* getRecogido();
                bool getMaldito();
                void setMaldito(bool siono);
                void reiniciar();
                void actualizarEstadisticasPorObjetos();
                bool getTrampeado();
                void setTrampeado(bool ahora);
                Linterna* getLinterna();
                void actualizarPosLinterna();
                int getHabilidadDispo();
                void setHabilidadDispo(int disp);
                bool puedoUsarHabilidad(int hab);
                double getTipoTrampeado();
                void animarPersonaje();
};