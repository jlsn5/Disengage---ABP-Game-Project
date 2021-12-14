#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include "Sprite1.h"
using namespace std;

class Objeto{
	protected:
		int rareza; //NIVEL DEL OBJETO, lo podemos usar para spawnear ciertos objetos según el nivel a lo largo del juego
        std::string tipo;//tipos posibles: ataque, vida, velocidad, velocidadAtaque, rango
        double valor;//valor que suma o resta ese objeto
        Sprite1 *spriteObjeto; //sprite para el objeto
        Sprite1 *trampa;
        //POSICION DEL OBJETO
        double pos_x;
        double pos_y;
        std::string linterna;
        std::string rutaImagen;//ruta que el hijo pasa al padre para crear la imagen
        //variables de posicion para cada una de las imagenes, se las pasa el objeto hijo
        double pos1;
        double pos2;
        double pos3;
        double pos4;
        double escala; //escalado de la imagen
        double recogido; //nos indica si ha sido recogido por el personaje
	public:
		bool operator == (const Objeto &obj) const;
        //void operator = (const Objeto &obj) const;
        Objeto &operator = (const Objeto &de);
        Objeto(const Objeto& o); //Constructor copia
        Objeto(); //constructor por defecto establece a 1 la rareza
        ~Objeto(); //Destructor
        Objeto(std::string tipo, int i);
        void setImgLinterna(std::string lin);
        std::string getImgLinterna();
        void setRareza(int r);//Aplica una rareza al objeto entre 1 y 5
        int getRareza(); //devuelve la rareza del objeto base
        void setTipo(std::string tip);
        void setValor(double val);//recogera la estadistica a sumar al pj procedente de los objetos hijo
        double getValor();//devuelve el valor a añadir al personaje 
        std::string getTipo();//devuelve el tipo
        
		void setTexture(sf::Texture t); //aplicar la textura 
        void setPosX(double cord_x);//establecer posicion x
        void setPosY(double cord_y);//establecer posicion y
        double getPosX();//devuelve pos_x
        double getPosY();//devuelve pos_y
        //sf::Sprite getSpriteO();
		void setEscala(double escalado); //sirve para establecer la escala
        void setPositions(); //Posiciona el objeto en las coordenadas x e y. Se llama a esta función despues de cambiar alguno de los valor pos_x o pos_y del objeto
        void setPositions(float cord_x, float cord_y); //Cambia las dos coordenadas directamente
        void cargarTexturas();//hay que llamarla siempre despues de crear un objeto
        Sprite1 *getSpriteObjeto();
        void setRutaImg(std::string r);
        void setRecogido();
        double getRecogido();
		void setPositionsImg(double a, double b, double c, double d);//sirve para establecer las dimensiones del recorte de la imagen
        void setTrampa(std::string ruta);
        Sprite1 *getSpriteTrampa();

};