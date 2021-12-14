
#include "Menu.h"
#include "Motor2D.h"
#include <iostream>
using namespace std;
Menu::Menu(){

}

void Menu::crearMenu(int width, int height, std::string tipo){
    sprite = new Sprite1();
	fondo = new Sprite1();
	info = new Sprite1();
	titulo = new Sprite1();
	objetosDes = new Sprite1();
	armas = new Sprite1();
    sprite->setFont("resources/Ara.TTF"); //definimos el sprite en Sprite
        ancho = width;
        alto = height;

        if(tipo == "titulo"){
            estado = 0;
        }else if(tipo == "principal"){
            estado = 1;
        }else if(tipo == "nuevaPartida"){
            estado = 2;
        }else if(tipo == "cargarPartida"){
            estado = 3;
        }else if(tipo == "ajustes"){
            estado = 4;
        }else if(tipo == "partida"){
            estado = 5;
        }else if(tipo == "eliminar"){
            estado = 6;
        }else if(tipo == "intercambio"){
			estado = 7;
		}
        inicializarMenu();
        modo = 0;
		cont = 0;
		pActual = -1;
		primera = true;
}
void Menu::inicializarMenu(){
	eliminada = -1;
	string silence;
    sprite->setFont("resources/Ara.TTF"); 
	switch(estado){
		case 0: //titulo
			max_number_of_items = 1;
            sprite->setColor("red", 0);
            sprite->setText("Empezar", 0);
            sprite->setFont("resources/Ara.TTF");
            //sprite->setPos(this->ancho/2.25, this->alto/1.5, 0);
			sprite->setPos(ancho / 2.25, motor->getCentroVista() + 150 , 0);
			//parametrosMenu[0].setPosition(sf::Vector2f(this->ancho / 3, this->alto / 2));
			selectedItemIndex = 0;
            fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;
		case 1: //principal
			max_number_of_items = 5;
            sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
                    sprite->setColor("red", i);
				}else{
                    sprite->setColor("white", i);				
                }
                sprite->setPos(ancho / 2.4, motor->getCentroVista() + 100*i, i );
			}
			selectedItemIndex = 0;
            sprite->setText("Nueva Partida", 0);
            sprite->setText("Cargar Partida", 1);
            sprite->setText("Modo Extremo", 2);
            sprite->setText("Ajustes", 3);
            sprite->setText("Salir", 4);
            fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;
		case 2: //nuevaPartida
			titulo->setFont("resources/Ara.TTF");
			titulo->setText("NUEVA PARTIDA", 0);
			titulo->setColor("white", 0);
			titulo->setPos(ancho / 2.45, 300, 0);
			titulo->escalar(1.4, 1.4);
			max_number_of_items = 3;
            sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
				sprite->setPos(ancho / 2.25, motor->getCentroVista() + 100*i + 30, i );
			}
			selectedItemIndex = 0;
			sprite->setText("Nombre: ", 0);
			sprite->setText("Jugar", 1);
			sprite->setText("Volver", 2);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;
		case 3: //cargarPartida
			titulo->setFont("resources/Ara.TTF");
			titulo->setText("CARGAR PARTIDA", 0);
			titulo->setColor("white", 0);
			titulo->setPos(ancho / 2.55, 300, 0);
			titulo->escalar(1.4, 1.4);
			max_number_of_items = 6;
			sprite->setFont("resources/Ara.TTF");
			if(primera == true){
				selectedItemIndex = 0;
				primera = false;
				cout << "no estara entrando aqui" << endl;
			}
			for(int i = 0; i < max_number_of_items; i++){
				if(i == selectedItemIndex){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
				sprite->setPos(ancho / 2.25, motor->getCentroVista()  + 70*i, i );
			}
			cargarPartidas();
			sprite->setText("Eliminar partida", 4);
			sprite->setText("Volver", 5);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;
		case 4: //ajustes
			titulo->setFont("resources/Ara.TTF");
			titulo->setText("AJUSTES", 0);
			titulo->setColor("white", 0);
			titulo->setPos(ancho / 2.3, 300, 0);
			titulo->escalar(1.4, 1.4);
			max_number_of_items = 3;
			sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
				sprite->setPos(ancho / 2.25, motor->getCentroVista() + 60 + 70*i, i );
			}
			selectedItemIndex = 0;
			
			if(motor->getSilenciado()){
				silence = "Audio: Activar sonido";
			}else{
				silence = "Audio: Silenciar";
			}
			sprite->setText(silence, 0);
			sprite->setText("Controles", 1);
			sprite->setText("Volver", 2);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;
		case 5: //partida
			titulo->setFont("resources/Ara.TTF");
			titulo->setText("ESTADISTICAS", 0);
			titulo->setColor("white", 0);
			titulo->setPos(60, 20, 0);
			titulo->escalar(1.4, 1.4);
			max_number_of_items = 4;
			sprite->setFont("resources/Ara.TTF");
			info->setFont("resources/Ara.TTF");
			if(estadisticas.size() == 11){
				objetosDes->setTextura("resources/4objetos.png");
			}else if(estadisticas.size() == 12){
				objetosDes->setTextura("resources/5objetos.png");
			}
			
			objetosDes->setPosicionSprite(700,644);
			objetosDes->escalar(0.45, 0.45);
			armas->setTextura("resources/armas1.png");
			armas->setPosicionSprite(700, 744);
			armas->escalar(4.f, 4.f);
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
				sprite->setPos(170, motor->getCentroVista() - 230 + 150*i, i );
			}
			selectedItemIndex = 0;
			primera = true;
			sprite->setText("Jugar", 0);
			sprite->setText("Habilidad", 1);
			sprite->setText("Libreria", 2);
			sprite->setText("Volver", 3);
			if(estadisticas.size() > 0){
				info->setText("Total monedas: " + estadisticas[0], 0);
				info->setText("Enemigos matados: " + estadisticas[1], 1);
				info->setText("Total Objetos Recogidos: " + estadisticas[2], 2);
				info->setText("Veces muerto: " + estadisticas[3], 3);
				info->setText("Objetos desbloqueados: ", 4);
				info->setText("Armas desbloqueadas: ", 5);
			}
			
			for(int i = 0; i < 6; i++){
				info->setColor("white", i);
				info->setPos(420, motor->getCentroVista() - 230 + 100*i, i);
			}

			fondo->setTextura("resources/estadis.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;

		case 6: //eliminar partidas

			//this->modo = 'e';
			max_number_of_items = 5;
			sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
				sprite->setPos(ancho / 2.25, motor->getCentroVista() + 100*i, i );
			}
			selectedItemIndex = 0;
			for(int i = 0; i < partidas.size(); i++){
				sprite->setText(partidas[i], i);
			}
			sprite->setText("Volver", 4);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - alto / 2);
			break;
		case 7: //intercambio objetos
			max_number_of_items = 5;
			sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
				sprite->setPos(ancho / 2.25, motor->getCentroVista()-320 + 125*i, i );
			}
			selectedItemIndex = 0;
			for(int i = 0; i < objetos.size(); i++){
				sprite->setText(objetos[i], i);
			}
			sprite->setText("Continuar", 4);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,0);
			break;

		case 8: //GAME OVER
			max_number_of_items = 2;
			sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
			}
			sprite->setPos(ancho / 2.25, motor->getCentroVista() , 0);
			sprite->setPos(ancho / 2.25, motor->getCentroVista()+200 , 1);

			selectedItemIndex = 0;
			sprite->setText("Volver a jugar", 0);
			sprite->setText("Salir", 1);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - 480);
			break;
		case 9: //controles
			max_number_of_items = 1;
			sprite->setFont("resources/Ara.TTF");
			sprite->setColor("red", 0);
			sprite->setPos(ancho/1.55, motor->getCentroVista() + 300, 0);
			sprite->setText("Volver", 0);
			fondo->setTextura("resources/controles.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - 480);
			break;
		case 10: //Libreria
			max_number_of_items = 1;
			sprite->setFont("resources/Ara.TTF");
			sprite->setColor("red", 0);
			sprite->setPos(20, motor->getCentroVista() -400, 0);
			sprite->setText("Volver", 0);
			fondo->setTextura("resources/libreria.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - 480);
			break;
		case 11: //Habilidad
			max_number_of_items = 1;
			sprite->setFont("resources/Ara.TTF");
			sprite->setColor("red", 0);
			sprite->setPos(ancho/1.55, motor->getCentroVista() + 300, 0);
			sprite->setText("Volver", 0);
			if(estadisticas[estadisticas.size() - 1] == "Bloqueada"){
				fondo->setTextura("resources/select_habilidad0.png");
			}else{
				fondo->setTextura("resources/select_habilidad1.png");
			}
			
			fondo->setPosicionSprite(0,motor->getCentroVista() - 480);
			break;
		case 12: //Fin del juego
			max_number_of_items = 2;
			sprite->setFont("resources/Ara.TTF");
			for(int i = 0; i < max_number_of_items; i++){
				if(i == 0){
					sprite->setColor("red", i);
				}else{
					sprite->setColor("white", i);
				}
			}
			sprite->setPos(ancho / 2.25, motor->getCentroVista()+100 , 0);
			sprite->setPos(ancho / 2.25, motor->getCentroVista()+300 , 1);
			int cont = 0;
			for(int i = 0; i < 3; i++){
				if(frags[i] == 0){
					cont++;
				}
			} 
			info->setFont("resources/Ara.TTF");
			info->setColor("white", 0);
			if(cont == 3){
				info->setText("ENHORABUENA, HAS GANADO", 0);
			}else{
				info->setText("Lo siento, no has conseguido todas las piezas", 0);
			}
			info->setPos(200, 400, 0);
			selectedItemIndex = 0;
			sprite->setText("Volver a jugar", 0);
			sprite->setText("Salir", 1);
			fondo->setTextura("resources/fondomenus.png");
			fondo->setPosicionSprite(0,motor->getCentroVista() - 480);
			break;
	}
}


Menu::~Menu()
{
}

void Menu::draw()
{   
	fondo->dibujar("menu", -1);
	sprite->dibujar("menu", max_number_of_items);
	if(estado == 5){
		if(estadisticas.size() != 0){
			info->dibujar("menu", 6);
			objetosDes->dibujar("menu", -1);
			armas->dibujar("menu", -1);
		}
		titulo->dibujar("menu", 1);
	}
	if(estado == 2 || estado == 3 || estado == 4){
		titulo->dibujar("menu", 1);
	}
    if(estado == 12){
		info->dibujar("menu", 1);
	}
}

void Menu::actualizarPartidas(vector<Partida*> &parts){
	int tam = partidas.size();
	int cuantos = 0;
	if(partidas.size() < 4){
		if(partidas.size() == cont){
			for(int i = partidas.size(); i < parts.size(); i++){
				partidas.push_back(parts[i]->getNombre());
				cont++;
			}
		}else{
			int t = parts.size();
			for(int i = 0; i < t; i++){
				
				if(parts[i] != NULL){
					cuantos++;
					partidas[i] = parts[i]->getNombre();
				}else{
					partidas[i] = "No hay partida creada";
				}
			}
			if(cuantos > cont){
				cont = cuantos;
			}
		}
	}else{
		int t = parts.size();
		for(int i = 0; i < t; i++){
			if(parts[i] != NULL){
				partidas[i] = parts[i]->getNombre();
			}
		}
	}
	
	
}

std::string Menu::getNombre(){
	return this->nombreInput;
}

void Menu::cargarPartidas(){
	for(int i = 0; i < 4; i++){
		sprite->setText("No hay partida creada", i);
	}
	for(int i = 0; i < partidas.size(); i++){
		sprite->setText(partidas[i], i);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex  > 0)
	{
		sprite->setColor("white", selectedItemIndex);
		selectedItemIndex--;
		sprite->setColor("red", selectedItemIndex);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < max_number_of_items)
	{
		sprite->setColor("white", selectedItemIndex);
		selectedItemIndex++;
		sprite->setColor("red", selectedItemIndex);
	}
}

void Menu::onClick()
{
	
	switch(estado){
		case 0: //titulo
			setEstado(1);
			break;
		case 1: //pantalla principal
			switch(selectedItemIndex){
				case 0: //nueva partida
					setEstado(2);
					break;
				case 1: //cargar partida
					setEstado(3);
					break;
				case 2: //modo extremo
					modo = 'x';
					break; 
				case 3:  //ajustes
					setEstado(4);
					break;
				case 4: //Salir
					setEstado(0);
					break;
			}
			break;
		case 2: //nueva partida
			switch(selectedItemIndex){
				case 1: //Jugar
					if(partidas.size() < 4){
						std::cout << "Se ha actualizado a partida" << endl;
						nombreInput = "";
						
					}else{
						setEstado(6);
					}
					this->modo = 'p';
					break;
				case 2: //Volver
					this->modo = 'm';
					setEstado(1);
					break;
			}
			break;
		case 3: //cargar partida
			if(modo == 't'){
				this->setEstado(5);
				modo = 'm';
			}else{
				switch(selectedItemIndex){
					case 0:
						if(partidas.size() > 0){
							if(partidas[0] != "No hay partida creada"){
								pActual = 0;
								
								modo = 't';
								cout << "Cargando partida 0" << endl;
								cout << "Estado: " << this->getEstado() << endl;
								//this->modo = 'p';
							}
						}
						break;
					case 1:
						if(partidas.size() > 1){
							if(partidas[1] != "No hay partida creada"){
								pActual = 1;
								modo = 't';
								cout << "Cargando partida 1" << endl;
								//this->modo = 'p';
							}
						}
						break;
					case 2:
						if(partidas.size() > 2){
							if(partidas[2] != "No hay partida creada"){
								cout << "No puede entrar" << endl;
								pActual = 2;
								this->modo = 'p';
							}
						}
						break;
					case 3:
						if(partidas.size() > 3){
							if(partidas[3] != "No hay partida creada"){
								pActual = 3;
								this->modo = 'p';
							}
						}
						break;
					case 4: //eliminar partida
						setEstado(6);
						break;
					case 5:
						setEstado(1);
						break;
				}
			}
			cout << "Selected: " << selectedItemIndex << endl;
			
			break;
		case 4: //ajustes
			switch(selectedItemIndex){
				case 0:
					if(motor->getSilenciado()){
						motor->silenciar(false);
					}else{
						motor->silenciar(true);
					}
					inicializarMenu();
					break;
				case 1:
					setEstado(9);
					break;
				case 2:
					setEstado(1);
					break;
			}
			break;
		case 5: //partida
			switch(selectedItemIndex){
				case 0: //Jugar
					this->modo = 'p';
					break;
				case 1: //Habilidad
					setEstado(11);
					break;
				case 2:	//Libreria
					setEstado(10);
					break;
				case 3: //volver
					this->modo = 'm';
					setEstado(3);
					
					break;
			}
			break;
		case 6:	//Eliminar partida
			switch(selectedItemIndex){
				case 0:
					setEliminada(0);
					cont--;
					modo = 'm';
					//setEstado(3);
					break;
				case 1:
					setEliminada(1);
					cont--;
					//setEstado(3);
					break;
				case 2:
					setEliminada(2);
					cont--;
					//setEstado(3);
					break;
				case 3:
					setEliminada(3);
					cont--;
					//setEstado(3);
					break;
				case 4: //Volver
					setEstado(2);
					setEliminada(-1);
					break;
			}

			break;
		case 7:
			//Se hace en el main para poder intercambiar el objeto
			break;

		case 8:
			//Game over, salir
			switch (selectedItemIndex)
			{
				case 0:
					modo = 'l';
					break;
				case 1:
					this->setEstado(0);
					pActual = -1;
				break;
			
			}

		break;
		case 9: //Controles
			setEstado(4);
			break;
		case 10: //LIBRERIA
			setEstado(5);
			break;
		case 11: //Habilidad
			setEstado(5);
			break;
		case 12: //Final del juego
			switch (selectedItemIndex)
			{
				case 0:
					modo = 'l';
					break;
				case 1:
					this->setEstado(0);
					pActual = -1;
				break;
			
			}
			break;
	}
}

void Menu::setEstado(int e){
	this->estado = e;
	inicializarMenu();
}

int Menu::getEstado(){
	return estado;
}

void Menu::setNombre(std::string n){
	if(estado == 2){
		sprite->setText("Nombre: ", 0);
		if(n == "borrar"){
			
			if(nombreInput.size() > 0){
				nombreInput.erase(nombreInput.size()-1);
			}
		}else{
			nombreInput = n;
		}
		sprite->setText("Nombre: " + nombreInput, 0);
	}else if(estado == 6){
		nombreInput = n;
	}
}

void Menu::setSelectedItem(int s){
	sprite->setColor("white", selectedItemIndex);
	selectedItemIndex = s;
	sprite->setColor("red", selectedItemIndex);
}

char Menu::getModo(){
	return modo;
}

void Menu::setModo(char a){
	modo = a;
}

void Menu::setEliminada(int e){
	eliminada = e;
	cout << "Modo: " << modo << endl;
}

int Menu::getEliminada(){
	return eliminada;
}

void Menu::haceClick(int pos){
	sprite->getTextoo(pos);
}

int Menu::getpActual(){
	return pActual;
}

void Menu::setAlturaActual(int a){
	alturaActual = a;
}

void Menu::actualizarObjetos(vector<Objeto*> &huecos){
	if(objetos.size() == 0){
		for(int i = 0; i < huecos.size(); i++){
			objetos.push_back(huecos[i]->getTipo());
		}
	}else if(objetos.size() == 4){
		for(int i = 0; i < huecos.size(); i++){
			objetos[i] = huecos[i]->getTipo();
		}
	}
}

Sprite1* Menu::getSprite(){
	return sprite;
}

void Menu::actualizarEstadisticas(vector<std::string> est){
	if(estadisticas.size() == 0){
		for(int i = 0; i < est.size(); i++){
			estadisticas.push_back(est[i]);
		}
	}else if(estadisticas.size() == 11 && est.size() == 12){
		for(int i = 0; i < 11; i++){
			estadisticas[i] = est[i];
		}
		estadisticas.push_back(est[11]);
	}else if(est.size() == 11 || est.size() == 12){
		for(int i = 0; i < est.size(); i++){
			estadisticas[i] = est[i];
		}
	}

	for(int i = 0; i < estadisticas.size(); i++){
		cout << estadisticas[i] << endl;
	}
	
	
}

void Menu::actualizarFragmentos(int f[3]){
	for(int i = 0; i < 3; i++){
		frags[i] = f[i];
	}
}
