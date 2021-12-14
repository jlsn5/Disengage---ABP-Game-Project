#include "Motor2D.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Sprite1.h"
using namespace std;

Motor2D::Motor2D(){
    std::cout << "Creating Motor2D" << std::endl;
    velocidadVista = 0;
    silenciado = false;
}
Motor2D* Motor2D::pinstance = 0;
Motor2D* Motor2D::getInstance(){
    if(pinstance == 0){
        pinstance = new Motor2D;
    }
    return pinstance;
}
void Motor2D::setWindow(sf::RenderWindow *ventana){
    this->window = ventana;
    this->ancho = ventana->getSize().x;
    this->alto = ventana->getSize().y;
}

/*
void Motor2D::setWindow(sf::RenderWindow &ventana){
    window = &ventana;
    cout<<"ventana : "<< window->isOpen()<<endl;
}
*/

void Motor2D::dibujar(sf::Sprite aDibujar){
    window->draw(aDibujar);
}

void Motor2D::dibujarT(sf::Text aDibujar){
  //  cout<<"estoy a punto de dibujar"<<endl;
   // cout<<"aDibujar: "<<aDibujar.getPosition().x<<endl;
    window->draw(aDibujar);
    //cout<<"ya esta"<<endl;

}

void Motor2D::dibujarM(sf::Sprite aDibujar){
    window->draw(aDibujar);
}

void Motor2D::setClicked(sf::Text t){
    clicked = &t;
}

sf::Text* Motor2D::getClicked(){
    return clicked;
    std::cout << "getclicked" << endl;
}

sf::RenderWindow* Motor2D::getWindow(){
    return window;
}


bool Motor2D::coinciden(Sprite1* pers, Sprite1* obj){
    if(pers->getSprite().getGlobalBounds().intersects(obj->getSprite().getGlobalBounds())){
        return true;
    }else{
        return false;
    }
}bool Motor2D::coincide(sf::Text t, int posX, int posY){
    if(t.getGlobalBounds().contains(window->mapPixelToCoords( sf::Vector2i(posX, posY)))){
        return true;
    }else{
        return false;
    }
}

bool Motor2D::coincidenLocal(Sprite1* pers, Sprite1* obj){
    if(pers->getSprite().getLocalBounds().intersects(obj->getSprite().getGlobalBounds())){
        return true;
    }else{
        return false;
    }
}

int Motor2D::getCentroVista(){
    return window->getView().getCenter().y;
}

void Motor2D::setCentroVista(int c){
    centroVista = c;
    actualizarVista = true;
}

bool Motor2D::getNuevaVista(){
    return actualizarVista;
}

void Motor2D::mantenerVista(){
    actualizarVista = false;
}

int Motor2D::getAncho(){
    return ancho;
}

int Motor2D::getAlto(){
    return alto;
}

int Motor2D:: getLongitud(){
    return longitudMapa;
}
void Motor2D:: setLongitud(int aux){
    longitudMapa = aux;
}

int Motor2D:: getVelocidad(){
    return velocidadVista;
}
void Motor2D:: setVelocidad(int aux){
    velocidadVista = aux;
}

void Motor2D::cargarSonido(std::string ruta, char modo){
    if(modo == 's'){
        if(!buffer.loadFromFile(ruta)){
            cout << "Error al cargar el sonido " << ruta << endl;
        }
        sonido.setBuffer(buffer);
    }else if(modo == 'm'){
        if(!musica.openFromFile(ruta)){
            cout << "Error al cargar la musica " << ruta << endl;
        }
        musica.setLoop(true);
    }
    
}

void Motor2D::reproducir(char modo){
    if(!silenciado){
        if(modo == 'm'){
            musica.play();
        }else if(modo == 's'){
            sonido.play();
        }
    }
}

void Motor2D::pause(){
    musica.pause();
}

void Motor2D::cambiarVolumen(int s, char modo){
    if(modo == 's'){
        sonido.setVolume(s);
    }else if(modo == 'm'){
        musica.setVolume(s);
    }   
}

void Motor2D::silenciar(bool s){
    silenciado = s;
}

bool Motor2D::getSilenciado(){
    return silenciado;
}
