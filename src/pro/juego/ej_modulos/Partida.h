#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/Transformable.hpp>
#include <string>

#include "Motor2D.h"
#include "Nivel.h"
#include "Objeto.h"
#include "O_Trampa.h"
#include "O_maldito.h"
#include "PersonajeBase.h"
#include "PersonajePrincipal.h"
#include "Hud.h"
#include "Armas.h"
#include "Enemigos.h"

/*

#include "Habilidad.h"
*/
using namespace std;
class Nivel;
class Partida{
	private:
		Motor2D *motor = Motor2D::getInstance();
		std::string nombre;
		PersonajePrincipal *personaje;
        std::vector<Armas*> huecosArmas;  //array de armas que ha conseguido
		int monedas; //?
		int fragmentos[4];
		bool primeraVez;
		Nivel *niv;
		vector<O_Trampa*> trampasDisponibles;
		vector<Objeto*> objetosDesbloqueados;
		vector<Objeto*> objetosDesbloqueables;
		vector<Armas*> armasDesbloqueadas;
		vector<Armas*> armasDesbloquebles;
		int maxObjetosSpawn;
		int totalEnemigosMatados;
		int totalObjetosRecogidos;
		int totalVecesMuerto;
		int totalObjetosDesbloqueados;
		int totalArmasDesbloqueadas;
		//Habilidad *habilidad;
		int posRecogido;
		double longitudPant;
		double longitudPantIntervalo;
		int desbloqueaHabilidad;
		int bossmuerto;
	public:
		Partida();
		Partida(std::string nombre);
		~Partida();
		void guardarPartida(int monedas, PersonajePrincipal *personaje, int fragmentos[]);
		std::string getNombre();
		void setNombre(std::string s);
		void crearNivel(int numNivel);
		int getHuecosObjetos();
		int getHuecosArmas();
		int getMonedas();
		void sumarMonedas(int s);
		void quitarMonedas(int s);
		void dibujar();
		void cargandoEnemigos();
		void cargandoObjetos();
		void cargandoTrampas();
		void cambiarPos(float x, float y);
		PersonajePrincipal * getPersonaje();
		Nivel * getNivel();
		vector<Objeto*> &getObjetos();
		vector<O_Trampa*> &getTrampas();
		float calcularDistanciaPJEnemigo(Enemigos* enemigo, PersonajePrincipal* personaje);
		void dispararArma();
		void dibujarHud(PersonajePrincipal *p, int m);
		//void borrarEnemigo();
		void setPosRecogido(int p);
		int getPosRecogido();
		void reiniciar();
		void enemigoAtaca();
		void cargarNivel();
		vector<std::string> getArmasDesbloqueadas();
		bool primeraVezQuePasoLaHistoria();
		void cambiarPrimeraVez(bool p);
		void agregarArmasAArmasDesbloqueadas(Armas *a);
		void agregarObjetosAObjetosDesbloqueados(Objeto *o);
		void sumarVecesMuerto();
		int getVecesMuerto();
		void sumarObjetosRecogidos();
		int getTotalObjetosRecogidos();
		void sumarEnemigosMatados();
		int getEnemigosMatados();
		int getTotalObjetosDesbloqueados();
		int getTotalArmasDesbloqueadas();
		void cargarEstadisticas(int vecesMuerto, int objRecogidos, int enemigosMatados);
		void setIntervaloTrampa(double intervalo);
		void setDesbloqueaHabilidad(int des);
		int getDesbloqueaHabilidad();
		void mejorarObjetos(int n);
		bool getBossMuerto();
};