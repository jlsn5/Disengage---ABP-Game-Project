#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Objeto.h"
#include "Hud.h"
#include "Partida.h"
#include "Enemigos.h"
#include "Mapa.h"
#include "Npc_Mejora.h"
#include "Npc_desbloqueo_objetos.h"
/*
#include "NpcHuecos.h"

#include "NpcMejora.h"

#include "Trampas.h"*/
using namespace std;
class Hud;
class Mapa;
class Nivel{
	private:
		int numero;
		Mapa *mapa;
		sf::Texture texture;
		vector<Enemigos*> enemigos;
		vector<Objeto*> objetos;
		vector<O_Trampa*> trampas;
		int MAXenemigos;
		//vector<Trampas*> trampas;
		Hud *hud;
		Npc_Mejora *npc;
		Npc_desbloqueo_objetos *npcd;
		Objeto* fragmento1;
		Objeto* fragmento2;
		Objeto* fragmento3;
		Objeto* fragmento4;
		int casa;
	public:
		Nivel();
		Nivel(int num, int a, int o, int m);
		void cargarEnemigos();//rellena el array con los enemigos
		void cargarMapa();
		void cargarHud(PersonajePrincipal *p, int m);

		void cargarNpc(int n);
		void matar(int posicion);
		vector<Enemigos*> getEnemigos();
		int getMAXenemigos();
		vector<Objeto*> getObjetos();
		vector<O_Trampa*> getTrampas();
		void objetoAobjetos(Objeto * obj);
		void trampaAtrampas(O_Trampa * t);
		Npc_Mejora* getNPC();
		Npc_desbloqueo_objetos* getNPC2();
		void setNumero(int n);
		int getNumero();
		Objeto* getFragmento(int niv);
		Mapa* getMapa();
		Hud* getHud();
		int getCasa();
		void setCasa(int i);
};