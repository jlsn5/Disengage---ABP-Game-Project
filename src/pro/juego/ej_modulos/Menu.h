#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
/*
#include "Objeto.h"
#include "PersonajeBase.h"
#include "Partida.h"
#include "PersonajePrincipal.h"
#include "Motor2D.h"
#include "Sprite.h"*/
#include "Partida.h"
#include "Sprite1.h"
#include "Objeto.h"
#include <vector>
using namespace std;

class Menu{
	private:
		int ancho;
		int alto;
		int estado;
		int selectedItemIndex;
		int max_number_of_items;
		Sprite1 *sprite;
		Sprite1 *fondo;
		Sprite1 *titulo;
		Sprite1 *objetosDes;
		Sprite1 *armas;
		vector<std::string> parametrosMenu;
		std::string tipo;
		vector<std::string> partidas;
		vector<std::string> objetos;
		int cont;
		std::string nombreInput;
		Sprite1 *info;
		vector<std::string> estadisticas;
		char modo;
		int eliminada;
		int pActual;
		int alturaActual;
		Motor2D *motor = Motor2D::getInstance();
		bool primera;
		int frags[3];
	public:
		Menu();
		~Menu();
		//Menu(int width, int height, std::string t);
		void crearMenu(int width, int height, std::string t); 
		void inicializarMenu();
		void draw();
		void onClick();
		void MoveUp();
		void MoveDown();
		int GetPressedItem() { return selectedItemIndex; }
		int getMNOI(){ return max_number_of_items; }
		void actualizarPartidas(vector<Partida*> &parts);
		void cargarPartidas();
		void setEstado(int e);
		int getEstado();
		void setNombre(std::string n);
		std::string getNombre();
		void haceClick(int pos);
		void setSelectedItem(int s);
		char getModo();
		void setModo(char a);
		void setEliminada(int e);
		int getEliminada();
		int getpActual();
		void setAlturaActual(int a);
		void actualizarObjetos(vector<Objeto*> &huecos);
		Sprite1* getSprite();
		void actualizarEstadisticas(vector<std::string> est);
		void actualizarFragmentos(int f[3]);
};