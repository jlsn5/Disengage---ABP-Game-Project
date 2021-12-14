#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <SFML/Graphics/Transformable.hpp>
#include <string>
class Sprite1;
using namespace std;
class Motor2D{
    private:
        sf::Event event;
        int estado;
        sf::RenderWindow *window;
        static Motor2D *pinstance;
        sf::Text *clicked;
        sf::SoundBuffer buffer;
        sf::Sound sonido;
        sf::Music musica;
        int ancho;
        int alto;
        int velocidadVista;
        int longitudMapa;
        bool silenciado;
        sf::View *view;
        int centroVista;
        bool actualizarVista;
    protected:
        Motor2D();
        //Motor2D(sf::RenderWindow &ventana);
       // Motor2D(const Motor2D& orig);
        Motor2D(Motor2D const&); 
        Motor2D& operator=(Motor2D const&);
    public:
        void setWindow(sf::RenderWindow *ventana);
        //void setWindow(sf::RenderWindow &ventana);
        void cargarEvento(sf::Event e);
        void dibujar(sf::Sprite aDibujar);
        void dibujarT(sf::Text aDibujar);
        void dibujarM(sf::Sprite aDibujar);
        void setClicked(sf::Text t);
        sf::Text* getClicked();
        static Motor2D* getInstance();
        sf::RenderWindow* getWindow();
        bool coinciden(Sprite1* pers, Sprite1* obj);
        bool coincidenLocal(Sprite1* pers, Sprite1* obj);
        bool coincide(sf::Text t, int posX, int posY);
        int getCentroVista();
        int getAncho();
        int getAlto();
        int getLongitud();
        void setLongitud(int aux);
        int getVelocidad();
        void setVelocidad(int aux);
        void cargarSonido(std::string ruta, char modo);
        void cambiarVolumen(int s, char modo);
        void reproducir(char modo);
        void pause();
        void silenciar(bool s);
        bool getSilenciado();
        void setCentroVista(int c);
        bool getNuevaVista();
        void mantenerVista();
        int getVistaNueva();
};
