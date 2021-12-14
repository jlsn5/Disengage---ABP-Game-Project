#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Partida.h"
#include "Motor2D.h"

class Escena{
	private:
		int estado;
        Menu menu;
        std::vector<Partida*> partidas;
        int cont;
        Partida *p;
        std::string inputText;
        int selectedItem;
        int actual;
        Motor2D *motor = Motor2D::getInstance();
        int alturaActual;
        bool primera;
	public:
		Escena();
        Escena(int width, int height);
        ~Escena();
        void setEstado(int e);
        int getEstado();
        Menu getMenu();
        void actualizarEscena();
        void actualizarMenu(int c);
        void setInputText(std::string t);
        void setSelectedItem(int i);
        std::vector<Partida*> &getPartidas();
        void dibujarPartida();
        void dibujarPartidaHud(PersonajePrincipal *p);
        int getActual();
        bool getPrimera();
        void setPrimera(bool n);

        void guardarPartida(); //guardado de partida
        void cargarPartidas(); //carga de partida
        void eliminarPartida(int posicion); //metodo para eliminar partidas según la partida seleccionada a eliminar
        void cargarNPC();
        Partida* getPartida();
};