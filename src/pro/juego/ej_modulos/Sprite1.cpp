#include "Sprite1.h"
#include <iostream>
using namespace std;
Sprite1::Sprite1(){

}

Sprite1::~Sprite1(){

}


Sprite1::Sprite1(std::string rutaT){
    //texture = texture;
    if(!texture.loadFromFile(rutaT)){
        std::cout << "Error al cargar la imagen " << endl;
    }
    sprite.setTexture(texture);

}

void Sprite1::recortar(int x, int y, int ancho, int alto){
    sprite.setTextureRect(sf::IntRect(x, y, ancho, alto));
}

void Sprite1::escalar(float x, float y){
    sprite.setScale(x, y);
}

void Sprite1::mover(float velX, float velY){
    sprite.move(velX, velY);
}

void Sprite1::setFont(std::string ruta){
    if (!font.loadFromFile(ruta))
	{
        std::cout << "Error al cargar la fuente " << endl;
		// handle error
	}
}
void Sprite1::setText(std::string cadena, int pos){
    menu[pos].setString(cadena);
    menu[pos].setFont(font);

}
void Sprite1::setTam(int e){
    tamFuente = e;
    texto.setCharacterSize(e);
    menu[0].setCharacterSize(e); //solo para las monedas uso esto //no es nada del menu
}
void Sprite1::setTexto(std::string c){
    texto.setString(c);
    texto.setFont(font);
}
 
void Sprite1::setColor(std::string c, int pos){
    if (pos != -1){
        if(c == "red"){
            menu[pos].setColor(sf::Color::Red);
        }else if(c == "white"){
            menu[pos].setColor(sf::Color::White); 
        }
    }else{
        if(c == "red"){
            texto.setColor(sf::Color::Red);
        }else if(c == "white"){
            texto.setColor(sf::Color::White);
        }
    }
}
void Sprite1::setPos(int ancho, int alto, int pos){
    if (pos != -1){
        menu[pos].setPosition(sf::Vector2f(ancho, alto));
    }else{
        texto.setPosition(sf::Vector2f(ancho, alto));
    }
}

void Sprite1::setTextura(std::string ruta){
    if(!texture.loadFromFile(ruta)){
        std::cout << "Error al cargar la imagen " << endl;
    }
    sprite.setTexture(texture);
    
}

void Sprite1::recortarSetTextureRect(double pos1, double pos2, double pos3, double pos4){
    sprite.setTextureRect(sf::IntRect(pos1, pos2,pos3, pos4));
    
}
void Sprite1::setPosicionSprite(double p1, double p2){
    sprite.setPosition(p1,p2);
    
}

void Sprite1::dibujar(std::string t, int p){
    if(t == "menu"){
        if(p == -1){
            motor->dibujar(sprite);
        }else{
            for(int i = 0; i < p; i++){
            // cout<<"dibujo"<<endl;
                //cout<<"motor x: "<<menu[i].getPosition().x<<"motor y: "<<menu[i].getPosition().y<< endl;
                motor->dibujarT(menu[i]);
            // motor->getWindow()->draw(menu[i]);
                
            // window.draw(menu[i]);
                
            }
        }
        //cout<<"voy a dibujar 2"<<endl;
        
    }else if(t == "hud"){
        if(p == -3){
            motor->dibujarT(menu[0]);
        }else{
            motor->dibujar(sprite);
        }
        
    }else if(t == "pers"){
        motor->dibujar(sprite);
       // std::cout << "pprincipal dibujado" << endl;
    }else if(t == "enem"){
        motor->dibujar(sprite);
    }else if (t == "obj"){
        motor->dibujar(sprite);
    }else if (t == "npc"){
        if(p == -1){
            motor->dibujarT(menu[0]);
        }else if (p !=0 ){
            motor->dibujarT(texto);
        }else{
            motor->dibujar(sprite);

        }
        //cout<<"esta dibujando"<<endl;
    }else if (t == "linterna"){
        motor->dibujar(sprite);
    }else if (t == "bala"){
        motor->dibujar(sprite); 
    }
}

sf::Text Sprite1::getTextoo(int p){
    return menu[p];
    //motor->setClicked(menu[p]);
}

void Sprite1::mover(double x, double y){
    float posX = x;
    float posY = y;
    sprite.move(posX, posY);
}

void Sprite1::setOrigen(double x, double y){
    float posX = x;
    float posY = y;
    sprite.setOrigin(posX, posY);
    
}

sf::Sprite Sprite1::getSprite(){
    return this->sprite;
}

sf::Sprite* Sprite1::getSpritePuntero(){
    return &this->sprite;
}