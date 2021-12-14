using namespace std;
#include "Juego.h"
#include <iostream>
#include <math.h>
#include <cmath>

Juego::Juego(){
    escena = new Escena();
    band = false;
    mover = false;
    width = 960;
    height = 960;
    kVel = 5;
    radio_sprite = 75 / 2;
}

Juego::Juego(int width, int height){
    escena = new Escena(width, height);
    band = false;
    mover = false;
    width = width;
    height = height;
    kVel = 5;
    radio_sprite = 75 / 2;
}

void Juego::giraAPosDeRatonBala(sf::RenderWindow *win){
    //cojo pos del cursor en la pantalla
    sf::Sprite *bala = escena->getPartidas()[escena->getActual()]->getPersonaje()->getArmas()[escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()]->getSpriteBala()->getSpritePuntero();
    sf::Vector2i curPos = win->mapCoordsToPixel(bala->getPosition());//bala->getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(*win); //raton

    const float PI = 3.14159265;
    float dx = curPos.x- position.x; 
    float dy = curPos.y- position.y;

    float rotation = ((atan2(dy, dx)) * 180 / PI ) + 180;  
    bala->setRotation(rotation);
}

void Juego::giraAPosDeRaton(sf::RenderWindow *win){
    sf::Sprite *sombra = escena->getPartidas()[escena->getActual()]->getPersonaje()->getLinterna()->getSpriteLinterna()->getSpritePuntero();
    //cojo pos del cursor en la pantalla
    sf::Vector2i curPos = win->mapCoordsToPixel(sombra->getPosition());
    sf::Vector2i position = sf::Mouse::getPosition(*win); //raton
    //cout << "raton "<<position.y<<endl;
    const float PI = 3.14159265;
    //cout<< "SPRITE "<<curPos.x <<" y "<<curPos.y<<endl;
    int resto = (int)curPos.y%960;
    float dx = curPos.x- position.x; 
    float dy = resto - position.y;
    //cout<<"pos " <<  win->getView().getCenter().y - 480 + position.y <<endl;
    float rotation = ((atan2(dy, dx)) * 180 / PI ) -90; //calculo la tangente 
    //-90 para ajustar
    //cout <<"pantalla : "<< pantalla->getPosition().x<<endl;
    sombra->setRotation(rotation);
}

FloatRect Juego::colisiona(sf::Sprite sp){
    FloatRect dev;
    Mapa * map = escena->getPartidas()[escena->getActual()]->getNivel()->getMapa();
    FloatRect rec = sp.getGlobalBounds();
    
    for(int fil=0; fil<map->getAltura(); fil++){
        for(int col=0; col<map->getAnchura(); col++){
            //Elementos de la capa 1
            if(map->getMapaSprites()[2][fil][col]!=NULL){

                if(map->getMapaSprites()[2][fil][col]->getGlobalBounds().intersects(rec)){
                    //dev = true;
                    FloatRect recCapa1 = map->getMapaSprites()[2][fil][col]->getGlobalBounds();
                    dev = recCapa1;
                    cout << "Choque con capa1 -> " << endl;
                }
            }
        }
    }
    return dev;
}

void Juego::render(){
    switch(escena->getEstado()){
      case 0:
        escena->getMenu().draw();     
        
        break;
      case 2:
      //probando este metodo
      x_coord = escena->getPartidas()[escena->getActual()]->getPersonaje()->getX();
      y_coord = escena->getPartidas()[escena->getActual()]->getPersonaje()->getY();
      if(escena->getPrimera()){
        if(escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() == 1){
           escena->getPartidas()[escena->getActual()]->getNivel()->getMapa()->leerMapa(2); //carga el cementerio
        }
        if(escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() == 3){
            motor->setCentroVista(480);
            //En el if despues del render hay que llamar a 
            //motor.getNuevaVista(); Y si es true hay que hacer
            //vista.setCenter(widht/2, motor.getVistaNueva())
            //motor.mantenerVista()
            
          motor->setLongitud(960);
          escena->getPartidas()[escena->getActual()]->getPersonaje()->setY(960);
        }else{
            motor->setCentroVista(9100);
            //En el if despues del render hay que llamar a 
            //motor.getNuevaVista(); Y si es true hay que hacer
            //vista.setCenter(widht/2, motor.getVistaNueva())
            //motor.mantenerVista()
          motor->setLongitud(9100);
          escena->getPartidas()[escena->getActual()]->getPersonaje()->setY(9100);
        }
        
        escena->setPrimera(false);
        escena->getPartidas()[escena->getActual()]->getPersonaje()->getLinterna()->reiniciar();
        mover = false;
        band = false;
        //Pasarlo al main
        /*if(juego.getEscena().getEstado() == 2 && escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() == 10){
          clock.restart();
          countdown = 15;
        }*/
      }
      //Pasarlo al main
      /*if(escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() == 10){
        sf::Time transcurrido = clock.getElapsedTime();
        cout << "Tiempo en la casa: " << transcurrido.asSeconds() << endl;
        if(transcurrido.asSeconds() > countdown){
          escena->setPrimera(true);
          escena->getPartidas()[escena->getActual()]->getNivel()->setNumero(1);
        }
      }*/
     // if(y_coord > vista.getCenter().y+520){
       if(y_coord == -7000){
          cout << "MUERTO";
          escena->getPartidas()[escena->getActual()]->sumarVecesMuerto();
          //vista.setCenter(480,480);
          motor->setCentroVista(480);
            //En el if despues del render hay que llamar a 
            //motor.getNuevaVista(); Y si es true hay que hacer
            //vista.setCenter(widht/2, motor.getVistaNueva())
            //motor.mantenerVista()
          
          escena->setEstado(5);

      }else{

        //Asignando sprites auxiliares para comprobar colisiones
        Sprite auxright = escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->getSprite();
        Sprite auxleft = auxright;
        Sprite auxtop = auxleft;
        Sprite auxdown = auxleft;
        int posX, posY;
        posX = escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().x;
        posY = escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().y;

        auxright.setPosition(posX+kVel, posY);
        auxleft.setPosition(posX-kVel , posY);
        auxtop.setPosition(posX, posY-kVel);
        auxdown.setPosition(posX, posY+kVel);

        //Añadir eventos del movimiento del personaje
        
        /* ------------- RIGHT ------------- */

        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (x_coord < width - radio_sprite)){
          if(colisiona(auxright).left <= auxright.getPosition().x){
            escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->mover((double)kVel, -0);
            x_coord += kVel;
            updatePositions();
          }
                  
        }
        /* ------------- LEFT ------------- */
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (x_coord > 0 + radio_sprite)){
          if(colisiona(auxleft).left <= 0){
            escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->mover((double)-kVel, 0);
            x_coord -= kVel;
            updatePositions();
          }
        }

        /* ------------- UP ------------- */
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (y_coord > 0 + radio_sprite)){
          band = true;
          if(colisiona(auxtop).top <= 0){
            escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->mover((double)0, -kVel);
            y_coord -= kVel;
            updatePositions();
          }
        }

        /* ------------- DOWN ------------- */
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (y_coord < motor->getCentroVista() + 460 - radio_sprite)){
          if(colisiona(auxdown).top <= 0){
            escena->getPartidas()[escena->getActual()]->getPersonaje()->getSprite()->mover((double)0, kVel);
            y_coord += kVel;
            updatePositions();
          }                             
        }     

        escena->getPartidas()[escena->getActual()]->getNivel()->getMapa()->draw(motor->getWindow());
        
        if(escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() == 10 || escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() == 11){
          escena->getPartidas()[escena->getActual()]->getNivel()->getFragmento(escena->getPartidas()[escena->getActual()]->getNivel()->getNumero())->getSpriteObjeto()->dibujar("obj", -1);
        }
        //Esto se deja en el main
        //window->setView(vista);

        escena->getPartidas()[escena->getActual()]->cargandoEnemigos();
        escena->dibujarPartida();
        if (escena->getPartidas()[escena->getActual()]->getPersonaje()->getTrampeado() == false){
            escena->getPartidas()[escena->getActual()]->getPersonaje()->getLinterna()->dibujarLinterna();
        }
        escena->dibujarPartidaHud(escena->getPartidas()[escena->getActual()]->getPersonaje());
        
        //motor->setVelocidad(0);
        if(band == true && mover == false && escena->getPartidas()[escena->getActual()]->getNivel()->getNumero() != 3){
          //Esto se deja en el main
          //vista.move(0,-2);
          motor->setVelocidad(-2);
          /*if(vista.getCenter().y < 482){
            vista.move(0,0);
            mover = true;
            std::cout << "Se para al final del mapa" << endl;
          }*/
        }

        //dibujo de cada bala
        dibujarBalas();      
      }
        break;

      case 3:
       // vista.setCenter(width/2, height/2);
        //window->setView(vista);
        dibujar();
        
      break;

      case 4:
        escena->cargarNPC();
    
      break;

      case 5:
        //vista.setCenter(width/2, height/2);
        motor->setCentroVista(480);
            //En el if despues del render hay que llamar a 
            //motor.getNuevaVista(); Y si es true hay que hacer
            //vista.setCenter(widht/2, motor.getVistaNueva())
            //motor.mantenerVista()
        //window->setView(vista);
        dibujar();
      break;
    }
}

Escena* Juego::getEscena(){
    return escena;
}

void Juego::dibujar(){
    escena->getMenu().draw();
}

void Juego::dibujarBalas(){
    if(escena->getPartidas()[escena->getActual()]->getPersonaje()->getArmas()[escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()]->getDisparando() == true){
          
          giraAPosDeRatonBala(motor->getWindow());
          escena->getPartidas()[escena->getActual()]->getPersonaje()->getArmas()[escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()]->dibujarBala();
          escena->getPartidas()[escena->getActual()]->getPersonaje()->getArmas()[escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()]->setDisparandoF();
        }
        escena->getPartidas()[escena->getActual()]->enemigoAtaca(); //comprueba constantemente si el enemigo esta atacando
}

void Juego::updatePositions(){
    escena->getPartidas()[escena->getActual()]->getPersonaje()->actualizarPosLinterna();
    escena->getPartidas()[escena->getActual()]->getPersonaje()->setX(x_coord);
    escena->getPartidas()[escena->getActual()]->getPersonaje()->setY(y_coord);
}

void Juego::MousePressedOnNPC(int x, int y, int seleccionado){
    switch(seleccionado){
        case 0: //Left
            //Desde el main se tiene que llamar
            //juego.MousePressedOnNPC((int)event.mouseButton.x, (int)event.mouseButton.y,0);
            switch(escena->getPartidas()[escena->getActual()]->getNivel()->getNumero()){
                case 0: //NPC mejora
                  if(motor->coincide(escena->getPartidas()[escena->getActual()]->getNivel()->getNPC()->getContinuar()->getTextoo(0), x, y)){
                    escena->getPartidas()[escena->getActual()]->getNivel()->getMapa()->leerMapa(3); //habitacion 1
                    escena->getPartidas()[escena->getActual()]->getNivel()->setNumero(10); //nivel hab 1
                  }
                  break;
                case 1: //NPC desbloqueo objetos
                  if(motor->coincide(escena->getPartidas()[escena->getActual()]->getNivel()->getNPC2()->getContinuar()->getTextoo(0), x, y)){
                    escena->getPartidas()[escena->getActual()]->getNivel()->getMapa()->leerMapa(4);
                    escena->getPartidas()[escena->getActual()]->getNivel()->setNumero(11); //nivel hab 2
                  }   
                  break;
              }
              escena->setPrimera(true);
            break;
        case 1: //Objeto1
            //Desde el main se tiene que llamar
            //juego.MousePressedOnNPC(-1,-1,1);
            escena->getPartidas()[escena->getActual()]->mejorarObjetos(0);
            break;
        case 2: //Objeto2
            //Desde el main se tiene que llamar
            //juego.MousePressedOnNPC(-1,-1,2);
            escena->getPartidas()[escena->getActual()]->mejorarObjetos(1);
            break;
        case 3: //Objeto3
            //Desde el main se tiene que llamar
            //juego.MousePressedOnNPC(-1,-1,3);
            escena->getPartidas()[escena->getActual()]->mejorarObjetos(2);
            break;
        case 4: //Objeto4
            //Desde el main se tiene que llamar
            //juego.MousePressedOnNPC(-1,-1,4);
            escena->getPartidas()[escena->getActual()]->mejorarObjetos(3);
            break;
        case 5: //Objeto5
            //Desde el main se tiene que llamar
            //juego.MousePressedOnNPC(-1,-1,5);
            escena->getPartidas()[escena->getActual()]->mejorarObjetos(4);
            break;
    }
}

void Juego::eventosHud(int i){
  switch(i){
    case 0: //num1
      escena->getPartidas()[escena->getActual()]->getPersonaje()->restarAtaque(escena->getPartidas()[escena->getActual()]->getPersonaje()->getArmas()[escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()]->getAtaqueArma());//resto ataque del arma anterior
      escena->getPartidas()[escena->getActual()]->getPersonaje()->setSeleccionada(0); //marco cual esta seleccionada
      escena->getPartidas()[escena->getActual()]->getPersonaje()->calcularAtaque(0);
      std::cout<<"Arma seleccionada : "<<escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()<<endl;
      std::cout<<"Daño actual : "<< escena->getPartidas()[escena->getActual()]->getPersonaje()->getAtaque()<<endl;
      break;
    case 1: //num2
      escena->getPartidas()[escena->getActual()]->getPersonaje()->restarAtaque(escena->getPartidas()[escena->getActual()]->getPersonaje()->getArmas()[escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()]->getAtaqueArma());//resto ataque del arma anterior
      escena->getPartidas()[escena->getActual()]->getPersonaje()->setSeleccionada(1);
      escena->getPartidas()[escena->getActual()]->getPersonaje()->calcularAtaque(1);
      cout<<"Arma seleccionada : "<<escena->getPartidas()[escena->getActual()]->getPersonaje()->getSeleccionada()<<endl;
      cout<<"Daño actual : "<<escena->getPartidas()[escena->getActual()]->getPersonaje()->getAtaque()<<endl;
      break;
    case 2: //E
      //HAY QUE ACTUALIZARLO
      break;
  }
}

int Juego::getkVel(){
  return kVel;
}
void Juego::setkVel(int i){
  kVel = i;
}

void Juego::intercambiarObjeto(int i){
  int sel = escena->getMenu().GetPressedItem();
  if(sel == 0 || sel == 1 || sel == 2 || sel == 3){
    escena->getPartidas()[escena->getActual()]->getPersonaje()->intercambiarObjeto(sel);
      escena->getPartidas()[escena->getActual()]->getObjetos()[escena->getPartidas()[escena->getActual()]->getPosRecogido()]->setRecogido();
  }
  escena->setEstado(2);
}