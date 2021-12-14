#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include "include/config.h"
#include "ej_modulos/Motor2D.h"
#include "ej_modulos/Escena.h"
#include "ej_modulos/Mapa.h"
#include "ej_modulos/Linterna.h"


#define width 960
#define height 960
void girarEnemigos(sf::RenderWindow *win, sf::Sprite *pj, sf::Sprite *se){

    //cojo pos del cursor en la pantalla
    sf::Vector2i curPos = win->mapCoordsToPixel(se->getPosition());//;
    sf::Vector2i personajePos;
    personajePos.x = pj->getPosition().x;
    personajePos.y = pj->getPosition().y;

    const float PI = 3.14159265;
    float dx = curPos.x- personajePos.x; 
    float dy = curPos.y- personajePos.y;

    float rotation = ((atan2(dy, dx)) * 180 / PI ) + 90;  
    se->setRotation(rotation);
}
void girarPJ(sf::RenderWindow *win, sf::Sprite *pj){

    //cojo pos del cursor en la pantalla
    sf::Vector2i curPos = win->mapCoordsToPixel(pj->getPosition());//;
    sf::Vector2i position = sf::Mouse::getPosition(*win); //raton

    const float PI = 3.14159265;
    float dx = curPos.x- position.x; 
    float dy = curPos.y- position.y;

    float rotation = ((atan2(dy, dx)) * 180 / PI ) + 260;  
    pj->setRotation(rotation);
}
void giraAPosDeRatonBala(sf::RenderWindow *win, sf::Sprite *bala){

    //cojo pos del cursor en la pantalla
    sf::Vector2i curPos = win->mapCoordsToPixel(bala->getPosition());//bala->getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(*win); //raton

    const float PI = 3.14159265;
    float dx = curPos.x- position.x; 
    float dy = curPos.y- position.y;

    float rotation = ((atan2(dy, dx)) * 180 / PI ) + 180;  
    bala->setRotation(rotation);
}
void giraAPosDeRaton(sf::RenderWindow *win, sf::Sprite *sombra){
    
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


void disparar(sf::RenderWindow &win, sf::Sprite &disp){
    
    //cojo pos del cursor en la pantalla
    sf::Vector2i curPos = win.mapCoordsToPixel(disp.getPosition());
    sf::Vector2i position = sf::Mouse::getPosition(win); //raton
    
    const float PI = 3.14159265;

    float dx = curPos.x - position.x; 
    float dy = curPos.y - position.y;

    float rotation = ((atan2(dy, dx)) * 180 / PI ) +180; //calculo la tangente 
    //-90 para ajustar

    disp.setRotation(rotation);
    
}

FloatRect compCol(Mapa *map, Sprite sp){
    FloatRect dev;
    FloatRect rec = sp.getGlobalBounds();
    
    for(int fil=0; fil<map->getAltura(); fil++){
                
        for(int col=0; col<map->getAnchura(); col++){

            //Elementos de la capa 1
            if(map->getMapaSprites()[2][fil][col]!=NULL){

                if(map->getMapaSprites()[2][fil][col]->getGlobalBounds().intersects(rec)){
                    //dev = true;
                    FloatRect recCapa1 = map->getMapaSprites()[2][fil][col]->getGlobalBounds();
                    dev = recCapa1;
                   // cout << "Choque con capa1 -> " << endl;
                }
            }
        }
    }
    //cout << "estado dev -> " << dev << endl;
    return dev;
}

int main() {
  bool norotar = false;
  bool essonidotrampa = false;
  bool restartHabilidad = false;
  bool tengomaldito = false;
  int temporizador = 3; //3 seg 
  double posy_restart = 0;
  int kVel = 5;
  int contadorNPC= 0;
  sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Ventana Principal");
  window->setFramerateLimit(30);
  Sprite1 *cursor = new Sprite1("resources/cursor.png");
  window->setMouseCursorVisible(false);
  cursor->setOrigen(50,50);
  cursor->escalar(0.5,0.5);


  sf::Clock clock;
  //window->setPosition(winDim);
  //sf::Sprite *lin;
  bool escalado = false;

  //balas
  Sprite1 *spDisparo = new Sprite1("resources/flecha.png");
  spDisparo->setOrigen(0,2);
  spDisparo->recortarSetTextureRect(0, 0, 599, 4);
  spDisparo->escalar(0.5f,0.4f);

  Motor2D *motor = Motor2D::getInstance();

  Mapa *mapa = new Mapa();
  int countdown = 0;
  //El int elige el mapa
  mapa->leerMapa(1);
  sf::View vista;
  
  vista.setSize(width,height);
  vista.setCenter(width/2,9100);
  motor->setLongitud(9100);

  motor->setWindow(window);
  Escena escena(width, height);
  int radio_sprite = 75 / 2;
  if(escena.getPartidas().size() > 0){
    escena.getPartidas()[escena.getActual()]->getPersonaje()->calcularAtaque(0); //calculo del ataque de las armas
  }
  Linterna *linterna= new Linterna();
  std::string enterText = "";
  double x_coord, y_coord;
  bool band = false;
  bool mover = false;
  bool open = true;
  int hab = -1;
  
  while (window->isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    while (window->pollEvent(event)) {
      if(escena.getEstado() == 0 || escena.getEstado() == 3 || escena.getEstado() == 5){
          switch (event.type) {
            //Si se recibe el evento de cerrar la ventana la cierro
            
            case sf::Event::Closed:
              window->close();
              break;
            //Se pulsó una tecla, imprimo su codigo
            case sf::Event::KeyPressed:
              //Verifico si se pulsa alguna tecla de movimiento
              switch (event.key.code) {

                //Mapeo del cursor
                case sf::Keyboard::Right:
                  break;
                case sf::Keyboard::Return:
                  //escena.getMenu().onClick();
                  if(escena.getEstado() == 0 || escena.getEstado() == 5){
                      escena.actualizarMenu(0);
                  }else if(escena.getEstado() == 3){
                      switch(escena.getMenu().GetPressedItem()){
                        case 0:
                          escena.getPartidas()[escena.getActual()]->getPersonaje()->intercambiarObjeto(0);

                           escena.getPartidas()[escena.getActual()]->getObjetos()[escena.getPartidas()[escena.getActual()]->getPosRecogido()]->setRecogido();
                          escena.setEstado(2);
                          break;
                        case 1:
                          escena.getPartidas()[escena.getActual()]->getPersonaje()->intercambiarObjeto(1);
                          escena.getPartidas()[escena.getActual()]->getObjetos()[escena.getPartidas()[escena.getActual()]->getPosRecogido()]->setRecogido();
                          escena.setEstado(2);
                          break;
                        case 2:
                          escena.getPartidas()[escena.getActual()]->getPersonaje()->intercambiarObjeto(2);
                          escena.getPartidas()[escena.getActual()]->getObjetos()[escena.getPartidas()[escena.getActual()]->getPosRecogido()]->setRecogido();
                          escena.setEstado(2);
                          break;
                        case 3:
                          escena.getPartidas()[escena.getActual()]->getPersonaje()->intercambiarObjeto(3);
                          escena.getPartidas()[escena.getActual()]->getObjetos()[escena.getPartidas()[escena.getActual()]->getPosRecogido()]->setRecogido();
                          escena.setEstado(2);
                          break;
                        case 4:
                          escena.setEstado(2);
                          break;
                      }
                  }
                  
                  //menu.onClick();
                  break;

                case sf::Keyboard::Up:
                  //escena.getMenu().MoveUp();
                  escena.actualizarMenu(1);
                  //menu.MoveUp();
                  break;

                case sf::Keyboard::Down:
                  //escena.getMenu().MoveDown();
                  escena.actualizarMenu(2);
                  //menu.MoveDown();
                  break;

                //Tecla ESC para salir
                case sf::Keyboard::Escape:
                  window->close();
                  break;
                
                //Cualquier tecla desconocida se imprime por pantalla su código
                default:
                  std::cout << event.key.code << std::endl;
                  break;
              }
              break;
            case sf::Event::TextEntered:
              if(escena.getMenu().getEstado() == 2){
                if(event.text.unicode < 128 && event.text.unicode > 31){
                  enterText = event.text.unicode;
                  escena.setInputText(enterText);
                  escena.actualizarMenu(3);
                  //menu.setNombre(enterText);
                }else if(event.text.unicode == 8){
                  enterText = "borrar";
                  escena.setInputText(enterText);
                  escena.actualizarMenu(3);
                  //menu.setNombre(enterText);
                }
              }      
              break;

            case sf::Event::MouseButtonPressed:
              if(event.mouseButton.button == sf::Mouse::Left){
                for(int i = 0; i < escena.getMenu().getMNOI(); i++){
                  if(motor->coincide(escena.getMenu().getSprite()->getTextoo(i), (int)event.mouseButton.x, (int)event.mouseButton.y)){
                      escena.setSelectedItem(i);
                      escena.actualizarMenu(4);
                      escena.actualizarMenu(0);
                  }
                }
              }
              break;
          }
      }else if(escena.getEstado() == 2){
        escena.getPartidas()[escena.getActual()]->getPersonaje()->actualizarEstadisticasPorObjetos();
        kVel = escena.getPartidas()[escena.getActual()]->getPersonaje()->getVelocidad();
        //kVel = 50;
       // cout<< "velocidad del personaje:" <<kVel<<endl;

          switch(event.type){
            //linterna
            case sf::Event::MouseMoved:
                  //cojo pos del cursor en la pantalla
              giraAPosDeRaton(window, linterna->getSpriteLinterna()->getSpritePuntero());
              girarPJ(window, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero());
              
            break;
            
            case sf::Event::MouseButtonPressed:
            //disparo, ataque
            escena.getPartidas()[escena.getActual()]->dispararArma();
            break; 
            case sf::Event::Closed:
              window->close();
              break;
            case sf::Event::KeyPressed:

              switch(event.key.code){
                /*case sf::Keyboard::Space: //dash hacia delante 
                    cout << escena.getPartidas()[escena.getActual()]->getDesbloqueaHabilidad() <<endl;
                    if (escena.getPartidas()[escena.getActual()]->getDesbloqueaHabilidad() == 1){
                      if (tengomaldito == false){
                        cout << "se supone que dash" <<endl;
                        //tengomaldito = true;
                        restartHabilidad= true;
                        escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)0, -100);
                        y_coord -= kVel;
                        linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
                        escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
                        escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
                      }

                    }
                  break;*/
                case sf::Keyboard::Num1:
                    escena.getPartidas()[escena.getActual()]->getPersonaje()->restarAtaque(escena.getPartidas()[escena.getActual()]->getPersonaje()->getArmas()[escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()]->getAtaqueArma());//resto ataque del arma anterior
                    escena.getPartidas()[escena.getActual()]->getPersonaje()->setSeleccionada(0); //marco cual esta seleccionada
                    escena.getPartidas()[escena.getActual()]->getPersonaje()->calcularAtaque(0);
                    std::cout<<"Arma seleccionada : "<<escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()<<endl;
                    std::cout<<"Daño actual : "<<escena.getPartidas()[escena.getActual()]->getPersonaje()->getAtaque()<<endl;
                  break;
                case sf::Keyboard::Num2:
                  escena.getPartidas()[escena.getActual()]->getPersonaje()->restarAtaque(escena.getPartidas()[escena.getActual()]->getPersonaje()->getArmas()[escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()]->getAtaqueArma());//resto ataque del arma anterior
                  escena.getPartidas()[escena.getActual()]->getPersonaje()->setSeleccionada(1);
                  escena.getPartidas()[escena.getActual()]->getPersonaje()->calcularAtaque(1);
                  std::cout<<"Arma seleccionada : "<<escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()<<endl;
                  std::cout<<"Daño actual : "<<escena.getPartidas()[escena.getActual()]->getPersonaje()->getAtaque()<<endl;
                  break;
                case sf::Keyboard::E:
                  for(int i = 0; i < escena.getPartidas()[escena.getActual()]->getTrampas().size(); i++){
                    if(motor->coinciden(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite(), escena.getPartidas()[escena.getActual()]->getTrampas()[i]->getSpriteObjeto())){
                      if(escena.getPartidas()[escena.getActual()]->getPersonaje()->cogerObjeto(escena.getPartidas()[escena.getActual()]->getTrampas()[i])){
                        if (i == 2){
                          essonidotrampa = true;
                        }
                        std::cout<<"tengo la trampa"<<endl;
                        escena.getPartidas()[escena.getActual()]->setIntervaloTrampa(motor->getCentroVista());
                      }
                    }
                  }
                  switch(escena.getPartidas()[escena.getActual()]->getNivel()->getCasa()){
                    case 1:
                      if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == 11){
                          if(!escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(11)->getRecogido()){
                            if(motor->coinciden(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite(), escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(11)->getSpriteObjeto())){
                              escena.getPartidas()[escena.getActual()]->getPersonaje()->cogerObjeto(escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(11));
                              escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(11)->setRecogido();
                            }
                          }
                      
                      }
                      break;
                    case 2:
                      if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == 15){
                          if(!escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(15)->getRecogido()){
                            if(motor->coinciden(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite(), escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(15)->getSpriteObjeto())){
                              escena.getPartidas()[escena.getActual()]->getPersonaje()->cogerObjeto(escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(15));
                              escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(15)->setRecogido();
                            }
                          }
                      }
                      break;
                    case 3:
                      if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == 16){
                          if(!escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(16)->getRecogido()){
                            if(motor->coinciden(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite(), escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(16)->getSpriteObjeto())){
                              escena.getPartidas()[escena.getActual()]->getPersonaje()->cogerObjeto(escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(16));
                              escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(16)->setRecogido();
                            }
                          }
                      }
                      break;
                  }
                  for(int i = 0; i < escena.getPartidas()[escena.getActual()]->getObjetos().size(); i++){
                    //Comprueba que el objeto no está recogido todavía
                    if(!escena.getPartidas()[escena.getActual()]->getObjetos()[i]->getRecogido()){
                        //Comprueba que el personaje esta encima del objeto a coget
                        if(motor->coinciden(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite(), escena.getPartidas()[escena.getActual()]->getObjetos()[i]->getSpriteObjeto())){
                          //Comprueba si hay hueco para el objeto
                          if (escena.getPartidas()[escena.getActual()]->getObjetos()[i]->getTipo()=="maldito"){

                            escena.getPartidas()[escena.getActual()]->getPersonaje()->cogerObjeto(escena.getPartidas()[escena.getActual()]->getObjetos()[i]);
                            escena.getPartidas()[escena.getActual()]->getObjetos()[i]->setRecogido();
                            //Actualizo el objeto recogido de personaje para luego poder intercambiarlo
                            escena.getPartidas()[escena.getActual()]->getPersonaje()->setRecogido(escena.getPartidas()[escena.getActual()]->getObjetos()[i]);
                            std::cout << "Objeto recogido" << endl;
                            escena.getPartidas()[escena.getActual()]->sumarObjetosRecogidos();

                          }else{
                            if(escena.getPartidas()[escena.getActual()]->getPersonaje()->cogerObjeto(escena.getPartidas()[escena.getActual()]->getObjetos()[i])){
                            //Si hay hueco, lo agrega al vector de objetos del personaje
                            escena.getPartidas()[escena.getActual()]->getObjetos()[i]->setRecogido();
                            //Actualizo el objeto recogido de personaje para luego poder intercambiarlo
                            escena.getPartidas()[escena.getActual()]->getPersonaje()->setRecogido(escena.getPartidas()[escena.getActual()]->getObjetos()[i]);
                            std::cout << "Objeto recogido" << endl;
                            escena.getPartidas()[escena.getActual()]->sumarObjetosRecogidos();
                            if(escena.getPartidas()[escena.getActual()]->getObjetos()[i]->getTipo() == "rango"){
                              linterna->actualizarLinterna(escena.getPartidas()[escena.getActual()]->getPersonaje()->getLinternaPersonaje());
                            }

                          }else{
                            escena.getPartidas()[escena.getActual()]->setPosRecogido(i);
                            //Si no cabe, se muestra un menu para intercambiar el objeto a coger por uno de los que tiene el personaje
                            escena.setEstado(3);

                          }
                          }
                          
                        }
                    }
                    
                  }
                  /*
                      mostrarMenu = true;
                      recogidos = objeto1;
                      menu.actualizarObjetos(prota->getObjetos());
                      
                      //prota->setAIntercambiar(objeto1);
                    }
                  }*/
                  break;
                case::sf::Keyboard::Escape:
                  window->close();
                  break;
              }
              break;
           
          }
      }else if (escena.getEstado() == 4){
        switch(event.type){

          case sf::Event::Closed:
          window->close();
          break;

          case sf::Keyboard::Escape:
          window->close();
          //cout<< escena.getEstado()<<endl;
          break;

          case sf::Event::MouseButtonPressed: //pulsar para mejorar
            if(event.mouseButton.button == sf::Mouse::Left){
              std::cout << "Numero de mapa: " << escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() << endl;
              switch(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero()){
                case 0: //NPC mejora
                  if(motor->coincide(escena.getPartidas()[escena.getActual()]->getNivel()->getNPC()->getContinuar()->getTextoo(0), (int)event.mouseButton.x, (int)event.mouseButton.y)){
                    mapa->leerMapa(3); //habitacion 1
                    std::cout << "Se cambia el mapa a la habitacion" << endl;
                    escena.getPartidas()[escena.getActual()]->getNivel()->setNumero(10); //nivel hab 1
                    escena.setPrimera(true);
                    escena.getPartidas()[escena.getActual()]->getNivel()->setCasa(1);
                    open = true;
                  }
                  break;
                case 1: //NPC desbloqueo objetos
                  if(motor->coincide(escena.getPartidas()[escena.getActual()]->getNivel()->getNPC2()->getContinuar()->getTextoo(0), (int)event.mouseButton.x, (int)event.mouseButton.y)){
                    mapa->leerMapa(4);
                    escena.getPartidas()[escena.getActual()]->getNivel()->setNumero(13 + (rand() % 3)); //nivel hab 2
                    escena.setPrimera(true);
                    escena.getPartidas()[escena.getActual()]->getNivel()->setCasa(2);
                    open = true;
                  }   
                  break;
              }
              
            }
             
            if(sf::Mouse::getPosition(*window).x>=594 && sf::Mouse::getPosition(*window).x<=670){
              //rango de x perfecto
              if(sf::Mouse::getPosition(*window).y>=78 && sf::Mouse::getPosition(*window).y<=156){ //objeto 1
                if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0] != NULL){ //Hay objeto 1
                  if (escena.getPartidas()[escena.getActual()]->getMonedas() >= escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->getRareza()*50){
                    if (escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->getRareza() <3){
                      escena.getPartidas()[escena.getActual()]->quitarMonedas(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->getRareza()*50);
                      std::cout << "boton 1"<<endl;
                      escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->setRareza(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->getRareza() + 1);
                      //escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->setValor(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->getRareza()* escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[0]->getValor());

                    }
                  }

                }
              }else if (sf::Mouse::getPosition(*window).y>=189 && sf::Mouse::getPosition(*window).y<=270){ //objeto 2
                if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1] != NULL){ //Hay objeto 2
                  if (escena.getPartidas()[escena.getActual()]->getMonedas() >= escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->getRareza()*50){
                    if (escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->getRareza() <3){
                      escena.getPartidas()[escena.getActual()]->quitarMonedas(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->getRareza()*50);
                      std::cout << "boton 2"<<endl;
                      escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->setRareza(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->getRareza() + 1);
                      //escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->setValor(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->getRareza()*escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[1]->getValor());

                    }
                  }
                }
              }else if (sf::Mouse::getPosition(*window).y>=298 && sf::Mouse::getPosition(*window).y<=381){ //objeto 3
                if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2] != NULL){ //Hay objeto 3
                  if (escena.getPartidas()[escena.getActual()]->getMonedas() >= escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->getRareza()*50){
                    if (escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->getRareza() <3){
                      escena.getPartidas()[escena.getActual()]->quitarMonedas(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->getRareza()*50);
                      std::cout << "boton 3"<<endl;
                      escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->setRareza(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->getRareza() + 1);
                      //escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->setValor(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->getRareza()*escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[2]->getValor());  

                    }
                  }
                }
              }else if (sf::Mouse::getPosition(*window).y>=412 && sf::Mouse::getPosition(*window).y<=493){ //objeto 4
                if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3] != NULL){ //Hay objeto 4
                  if (escena.getPartidas()[escena.getActual()]->getMonedas() >= escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->getRareza()*50){
                    if (escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->getRareza() <3){
                      escena.getPartidas()[escena.getActual()]->quitarMonedas(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->getRareza()*50);
                      std::cout << "boton 4"<<endl;
                      escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->setRareza(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->getRareza() + 1);
                      //escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->setValor(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->getRareza()*escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[3]->getValor());
 
                    }
                  }
                }
              }else if (sf::Mouse::getPosition(*window).y>=520 && sf::Mouse::getPosition(*window).y<=601){ //objeto 5
                if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4] != NULL){ //Hay objeto 5
                  if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getNumHuecosObjetos()>4){
                    if (escena.getPartidas()[escena.getActual()]->getMonedas() >= escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->getRareza()*50){
                      if (escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->getRareza() <3){
                        escena.getPartidas()[escena.getActual()]->quitarMonedas(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->getRareza()*50);
                        std::cout << "boton 5"<<endl;
                        escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->setRareza(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->getRareza() + 1);
                        //escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->setValor(escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->getRareza()*escena.getPartidas()[escena.getActual()]->getPersonaje()->getObjetos()[4]->getValor());

                      }
                    }
                  }
                }
              }

            }
          break;
          
        }
      }else if(escena.getEstado() == 6){
        switch (event.type) {
           
            case sf::Event::Closed:
              window->close();
              break;
            case sf::Event::MouseMoved:
                  //cojo pos del cursor en la pantalla
                  giraAPosDeRaton(window, linterna->getSpriteLinterna()->getSpritePuntero());
                  girarPJ(window, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero());
                break;
                
            case sf::Event::MouseButtonPressed:
                //disparo, ataque
                escena.getPartida()->dispararArma();
                break; 
            case sf::Event::KeyPressed:

              switch(event.key.code){
                case::sf::Keyboard::Escape:
                  window->close();
                  break;
                case sf::Keyboard::Num1:
                    escena.getPartida()->getPersonaje()->restarAtaque(escena.getPartida()->getPersonaje()->getArmas()[escena.getPartida()->getPersonaje()->getSeleccionada()]->getAtaqueArma());//resto ataque del arma anterior
                    escena.getPartida()->getPersonaje()->setSeleccionada(0); //marco cual esta seleccionada
                    escena.getPartida()->getPersonaje()->calcularAtaque(0);
                    std::cout<<"Arma seleccionada : "<<escena.getPartida()->getPersonaje()->getSeleccionada()<<endl;
                    std::cout<<"Daño actual : "<<escena.getPartida()->getPersonaje()->getAtaque()<<endl;
                  break;
                case sf::Keyboard::Num2:
                  escena.getPartida()->getPersonaje()->restarAtaque(escena.getPartida()->getPersonaje()->getArmas()[escena.getPartida()->getPersonaje()->getSeleccionada()]->getAtaqueArma());//resto ataque del arma anterior
                  escena.getPartida()->getPersonaje()->setSeleccionada(1);
                  escena.getPartida()->getPersonaje()->calcularAtaque(1);
                  std::cout<<"Arma seleccionada : "<<escena.getPartida()->getPersonaje()->getSeleccionada()<<endl;
                  std::cout<<"Daño actual : "<<escena.getPartida()->getPersonaje()->getAtaque()<<endl;
                  break;
                case sf::Keyboard::E:
                  for(int i = 0; i < escena.getPartida()->getTrampas().size(); i++){
                    if(motor->coinciden(escena.getPartida()->getPersonaje()->getSprite(), escena.getPartida()->getTrampas()[i]->getSpriteObjeto())){
                      if(escena.getPartida()->getPersonaje()->cogerObjeto(escena.getPartida()->getTrampas()[i])){
                        if (i == 2){
                          essonidotrampa = true;
                        }
                        std::cout<<"tengo la trampa"<<endl;
                        escena.getPartida()->setIntervaloTrampa(motor->getCentroVista());
                      }
                    }
                  }
                  for(int i = 0; i < escena.getPartida()->getObjetos().size(); i++){
                    //Comprueba que el objeto no está recogido todavía
                    if(!escena.getPartida()->getObjetos()[i]->getRecogido()){
                        //Comprueba que el personaje esta encima del objeto a coget
                        if(motor->coinciden(escena.getPartida()->getPersonaje()->getSprite(), escena.getPartida()->getObjetos()[i]->getSpriteObjeto())){
                          //Comprueba si hay hueco para el objeto
                          if (escena.getPartida()->getObjetos()[i]->getTipo()=="maldito"){

                            escena.getPartida()->getPersonaje()->cogerObjeto(escena.getPartida()->getObjetos()[i]);
                            escena.getPartida()->getObjetos()[i]->setRecogido();
                            //Actualizo el objeto recogido de personaje para luego poder intercambiarlo
                            escena.getPartida()->getPersonaje()->setRecogido(escena.getPartida()->getObjetos()[i]);
                            std::cout << "Objeto recogido" << endl;
                            escena.getPartida()->sumarObjetosRecogidos();

                          }else{
                            if(escena.getPartida()->getPersonaje()->cogerObjeto(escena.getPartida()->getObjetos()[i])){
                            //Si hay hueco, lo agrega al vector de objetos del personaje
                            escena.getPartida()->getObjetos()[i]->setRecogido();
                            //Actualizo el objeto recogido de personaje para luego poder intercambiarlo
                            escena.getPartida()->getPersonaje()->setRecogido(escena.getPartida()->getObjetos()[i]);
                            std::cout << "Objeto recogido" << endl;
                            escena.getPartida()->sumarObjetosRecogidos();
                            if(escena.getPartida()->getObjetos()[i]->getTipo() == "rango"){
                              linterna->actualizarLinterna(escena.getPartida()->getPersonaje()->getLinternaPersonaje());
                            }

                          }else{
                            escena.getPartida()->setPosRecogido(i);
                            //Si no cabe, se muestra un menu para intercambiar el objeto a coger por uno de los que tiene el personaje
                            escena.setEstado(3);

                          }
                          }
                          
                        }
                    }
                    
                  }
                
              }
              break;
        }
      }
      
    }
    //Sprite auxright;
    
    //Sprite auxsin = escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite();
    //cout << "Este esprite > " << auxsin.getPosition().x << endl;
    //escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite();

    window->clear();
    switch(escena.getEstado()){
      case 0:
        escena.getMenu().draw();     
        
        break;
      case 2:
          window->setMouseCursorVisible(false); //oculto el raton
          cursor->setPosicionSprite(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
          
      /*if (tengomaldito == true && restartHabilidad == true){
        restartHabilidad = false;
        clock.restart();
        
      }
      if (tengomaldito == true && restartHabilidad == false){
        sf::Time habilidadTime = clock.getElapsedTime();
        if (habilidadTime.asSeconds()>=temporizador){
          tengomaldito == false;

        }
      }*/
      //probando este metodo
      x_coord = escena.getPartidas()[escena.getActual()]->getPersonaje()->getX();
      y_coord = escena.getPartidas()[escena.getActual()]->getPersonaje()->getY();
      //compCol(mapa,escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite());
      if(escena.getPrimera()){
        switch(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero()){
          case 0: //bosque
            mapa->leerMapa(1);
            vista.setCenter(width/2,9100);
            motor->setLongitud(9100);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(9100);
            break;
          case 1: //cementerio 
            mapa->leerMapa(2);
            vista.setCenter(width/2,9100);
            motor->setLongitud(9100);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(9100);
            break;
          case 2: //pantano
            mapa->leerMapa(5);
            vista.setCenter(width/2,9100);
            motor->setLongitud(9100);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(9100);
            break;
          case 10: //hab 1
            mapa->leerMapa(3);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 11: //hab 2
            mapa->leerMapa(4);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(800);
            break;
          case 12: //hab 3
            mapa->leerMapa(6);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 13: //hab 4
            mapa->leerMapa(7);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 14: //hab 5
            mapa->leerMapa(8);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 15: //hab 6
            mapa->leerMapa(9);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 16: //hab 7
            mapa->leerMapa(10);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 17: //hab 8
            mapa->leerMapa(11);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case 18: //hab 9
            mapa->leerMapa(12);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
          case -2: //transicion del pantano a la tercera casa
            mapa->leerMapa(7);
            escena.getPartidas()[escena.getActual()]->getNivel()->setNumero(13);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            open = true;
            escena.getPartidas()[escena.getActual()]->getNivel()->setCasa(3);
            break;
          case 19: //Mapa final
            std::cout << "Va a cargar el mapa final" << endl;
            mapa->leerMapa(13);
            vista.setCenter(width/2,height/2);
            motor->setLongitud(height);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(900);
            break;
        }
        escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(width/2);
        vista.setSize(width,height);
        
        escena.getPartidas()[escena.getActual()]->getNivel()->getHud()->reiniciarPos();
        escena.setPrimera(false);
        linterna->reiniciar();
        mover = false;
        band = false;
        if((escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 1 || escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 2 || escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 3) && open == true){
          clock.restart();
          countdown = 20;
          open = false;
        }
      }
      
      if(escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 1 || escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 2 || escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 3){
        sf::Time transcurrido = clock.getElapsedTime();
        std::cout << "Tiempo en la casa: " << transcurrido.asSeconds() << endl;;
        if((int)transcurrido.asSeconds() == (countdown - 3)){
            escena.getPartidas()[escena.getActual()]->getNivel()->getHud()->actualizarTemp(3);
            std::cout << "Quedan 3" << endl;
        }else if((int)transcurrido.asSeconds() == (countdown - 2)){
            escena.getPartidas()[escena.getActual()]->getNivel()->getHud()->actualizarTemp(2);
            std::cout << "Quedan 2" << endl;
        }else if((int)transcurrido.asSeconds() == (countdown - 1)){
            escena.getPartidas()[escena.getActual()]->getNivel()->getHud()->actualizarTemp(1);
            std::cout << "Quedan 1" << endl;
        }else if((int)transcurrido.asSeconds() == countdown){
          escena.getPartidas()[escena.getActual()]->getNivel()->getHud()->actualizarTemp(0);
        }
        if(transcurrido.asSeconds() > countdown){
          escena.setPrimera(true);
          if(escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 1){
            escena.getPartidas()[escena.getActual()]->getNivel()->setNumero(1);
            escena.getPartidas()[escena.getActual()]->getNivel()->setCasa(-1);
          }else if(escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 2){
            escena.getPartidas()[escena.getActual()]->getNivel()->setNumero(2);
            escena.getPartidas()[escena.getActual()]->getNivel()->setCasa(-1);
          }else if(escena.getPartidas()[escena.getActual()]->getNivel()->getCasa() == 3){
            escena.getPartidas()[escena.getActual()]->getNivel()->setNumero(19); //Mapa final
            escena.setPrimera(true);
            escena.getPartidas()[escena.getActual()]->getNivel()->setCasa(-1);
          }
          
        }
      }
        if (escena.getPartidas()[escena.getActual()]->getBossMuerto() == true){
          escena.setEstado(5);
        }
      //if(y_coord > vista.getCenter().y+520){
      if(y_coord == -7000){
          std::cout << "MUERTO";
          escena.getPartidas()[escena.getActual()]->sumarVecesMuerto();
          vista.setCenter(480,480);
          escena.setEstado(5);

      }else{

        //Asignando sprites auxiliares para comprobar colisiones
        Sprite auxright = escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite();
        Sprite auxleft = escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite();
        Sprite auxtop = escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite();
        Sprite auxdown = escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite();

        auxright.setPosition(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().x+kVel , escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().y);

        auxleft.setPosition(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().x-kVel , escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().y);

        auxtop.setPosition(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().x , escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().y-kVel);

        auxdown.setPosition(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().x , escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite().getPosition().y+kVel);

        //Añadir eventos del movimiento del personaje
        
        /* ------------- RIGHT ------------- */

        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (x_coord < width - radio_sprite)){
          //cout << "pos mapa -> " << compCol(mapa, auxright).left << endl;
          //cout << "pos personaje -> " << auxright.getPosition().x << endl;
          //compCol(mapa, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSprite());
          if(compCol(mapa, auxright).left > auxright.getPosition().x){
            //cout << "SE PARA" << endl;
          }else{
            escena.getPartidas()[escena.getActual()]->getPersonaje()->animarPersonaje();
            escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)kVel, -0);
            x_coord += kVel;
            linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
            escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
          }
                  
        }
        /* ------------- LEFT ------------- */
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (x_coord > 0 + radio_sprite)){

          if(compCol(mapa, auxleft).left > 0){
            //cout << "SE PARA" << endl;
          }else{
          escena.getPartidas()[escena.getActual()]->getPersonaje()->animarPersonaje();
          escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)-kVel, 0);
          x_coord -= kVel;
          linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
          escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
          escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
        }
        }
        /*---------------DASH----------------*/
        if (escena.getPartidas()[escena.getActual()]->getDesbloqueaHabilidad() == 1){ // comprueba que este desbloqueada
          if (restartHabilidad == false){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
              escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)0, -100);
              y_coord -= 100;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
              restartHabilidad = true;
              escena.getPartidas()[escena.getActual()]->getPersonaje()->puedoUsarHabilidad(1); //es para controlar el hud
              posy_restart = y_coord;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
              escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)-100, 0);
              x_coord -= 100;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
              restartHabilidad = true;
              escena.getPartidas()[escena.getActual()]->getPersonaje()->puedoUsarHabilidad(1); //es para controlar el hud
              posy_restart = y_coord;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
              escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)100, 0);
              x_coord += 100;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
              restartHabilidad = true;
              escena.getPartidas()[escena.getActual()]->getPersonaje()->puedoUsarHabilidad(1); //es para controlar el hud
              posy_restart = y_coord;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
              escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)0, 100);
              y_coord += 100;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
              escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
              restartHabilidad = true;
              escena.getPartidas()[escena.getActual()]->getPersonaje()->puedoUsarHabilidad(1); //es para controlar el hud
              posy_restart = y_coord;
            }
          }
          if ( y_coord <= posy_restart-750 ){
            restartHabilidad = false;
            escena.getPartidas()[escena.getActual()]->getPersonaje()->puedoUsarHabilidad(0);
          }

        }
        /* ------------- UP ------------- */
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (y_coord > 0 + radio_sprite)){
          band = true;
          //motor->cargarSonido("resources/paso.wav",'s');
          //motor->reproducir('s');
          
          if(compCol(mapa, auxtop).top > 0){
            //cout << "SE PARA" << endl;
          }else{
            escena.getPartidas()[escena.getActual()]->getPersonaje()->animarPersonaje();
          escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)0, -kVel);
          y_coord -= kVel;
          linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
          escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
          escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
        }
        }

        /* ------------- DOWN ------------- */
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (y_coord < motor->getCentroVista() + 460 - radio_sprite)){
          //cout << "Intenta moverse abajo" << endl;
          
          if(compCol(mapa, auxdown).top > 0){
            //cout << "SE PARA" << endl;
          }else{
          escena.getPartidas()[escena.getActual()]->getPersonaje()->animarPersonaje();
          escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->mover((double)0, kVel);
          y_coord += kVel;
          linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
          escena.getPartidas()[escena.getActual()]->getPersonaje()->setX(x_coord);
          escena.getPartidas()[escena.getActual()]->getPersonaje()->setY(y_coord);
          }                       
        }         
        mapa->draw(window);
        switch(escena.getPartidas()[escena.getActual()]->getNivel()->getCasa()){
          case 1:
            hab = 11;
            if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == hab){
              if(!escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(hab)->getRecogido()){
                escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(hab)->getSpriteObjeto()->dibujar("obj", -1);
              }
            }
            break;
          case 2:
            hab == 15;
            if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == hab){
              if(!escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(hab)->getRecogido()){
                escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(hab)->getSpriteObjeto()->dibujar("obj", -1);
              }
            }
            break;
          case 3:
            hab = 16;
            if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == hab){
              if(!escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(hab)->getRecogido()){
                escena.getPartidas()[escena.getActual()]->getNivel()->getFragmento(hab)->getSpriteObjeto()->dibujar("obj", -1);
              }
            }
            break;
        }
        window->setView(vista);

        escena.getPartidas()[escena.getActual()]->cargandoEnemigos();
        if(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() == 19 && norotar ==false){
          if (escena.getPartidas()[escena.getActual()]->getNivel()->getEnemigos()[0]->getVida() <=30){
            norotar = true;
          }
            girarEnemigos(window, escena.getPartidas()[escena.getActual()]->getPersonaje()->getSprite()->getSpritePuntero(),escena.getPartidas()[escena.getActual()]->getNivel()->getEnemigos()[0]->getSprite()->getSpritePuntero());
        }
        escena.dibujarPartida();
        if (escena.getPartidas()[escena.getActual()]->getPersonaje()->getTrampeado() == false){
          linterna->dibujarLinterna();
 
        }
        if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getTrampeado() == true && essonidotrampa==true){
          linterna->dibujarLinterna();

        }
       
        window->setMouseCursorVisible(false); //oculto el raton
 

        escena.dibujarPartidaHud(escena.getPartidas()[escena.getActual()]->getPersonaje());
        
        //motor->setVelocidad(0);
        if(band == true && mover == false && escena.getPartidas()[escena.getActual()]->getNivel()->getNumero() != 3){
          vista.move(0,-4);
          motor->setVelocidad(-4);
          if(vista.getCenter().y < 482){
            vista.move(0,0);
            motor->setVelocidad(0);
            mover = true;
            std::cout << "Se para al final del mapa" << endl;
          }
        }

        //dibujo de cada bala
        if(escena.getPartidas()[escena.getActual()]->getPersonaje()->getArmas()[escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()]->getDisparando() == true){
          
          giraAPosDeRatonBala(window, escena.getPartidas()[escena.getActual()]->getPersonaje()->getArmas()[escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()]->getSpriteBala()->getSpritePuntero());
          escena.getPartidas()[escena.getActual()]->getPersonaje()->getArmas()[escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()]->dibujarBala();
          escena.getPartidas()[escena.getActual()]->getPersonaje()->getArmas()[escena.getPartidas()[escena.getActual()]->getPersonaje()->getSeleccionada()]->setDisparandoF();
        }
        escena.getPartidas()[escena.getActual()]->enemigoAtaca(); //comprueba constantemente si el enemigo esta atacando
                
      }
          

        //eliminar enemigos
        //escena.getPartidas()[escena.getActual()]->borrarEnemigo();
        //vista.move(0,-0.01);
        break;

      case 3:
       // vista.setCenter(width/2, height/2);
        //window->setView(vista);
        escena.getMenu().draw();
        
      break;

      case 4:
        //cout<<vista.getCenter().x<< " " << vista.getCenter().y<<endl;  
        switch(escena.getPartidas()[escena.getActual()]->getNivel()->getNumero()){
          case 0: //NPC mejora
            escena.getPartidas()[escena.getActual()]->getNivel()->cargarNpc(0);
            //cout << "entro aqui" <<endl;
            escena.getPartidas()[escena.getActual()]->getNivel()->getNPC()->colocarObjetos(escena.getPartidas()[escena.getActual()]->getPersonaje(), escena.getPartidas()[escena.getActual()]->getMonedas());
            break;
          case 1: //NPC desbloqueo objetos
            escena.getPartidas()[escena.getActual()]->getNivel()->cargarNpc(1);
            escena.getPartidas()[escena.getActual()]->getNivel()->getNPC2()->setPersonaje(escena.getPartidas()[escena.getActual()]->getPersonaje());
            escena.getPartidas()[escena.getActual()]->getNivel()->getNPC2()->colocarObjetos();
            std::cout << "Dibuja el npc" << endl;           
            break;
        }
    
      break;

      case 5:
        vista.setCenter(width/2, height/2);
        //window->setView(vista);
        escena.getMenu().draw();
      break;
      case 6:
        window->setMouseCursorVisible(false); //oculto el raton
        cursor->setPosicionSprite(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
        x_coord = escena.getPartida()->getPersonaje()->getX();
        y_coord = escena.getPartida()->getPersonaje()->getY();
        if(escena.getPrimera() == true){
          mapa->leerMapa(0);
          vista.setCenter(width/2, 28310);
          motor->setLongitud(28310);
          escena.getPartida()->getPersonaje()->setX(width/2);
          escena.getPartida()->getPersonaje()->setY(28310);
          escena.setPrimera(false);
          linterna->reiniciar();
          mover = false;
          band = false;
          window->setView(vista);
          escena.getPartida()->getNivel()->getHud()->reiniciarPos();

        }
        
        if(y_coord > vista.getCenter().y+520){
          std::cout << "MUERTO";
          vista.setCenter(480,480);
          escena.setEstado(5);
        }else{
          
          //Asignando sprites auxiliares para comprobar colisiones
          Sprite auxright = escena.getPartida()->getPersonaje()->getSprite()->getSprite();
          Sprite auxleft = escena.getPartida()->getPersonaje()->getSprite()->getSprite();
          Sprite auxtop = escena.getPartida()->getPersonaje()->getSprite()->getSprite();
          Sprite auxdown = escena.getPartida()->getPersonaje()->getSprite()->getSprite();
          
          auxright.setPosition(escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().x+kVel , escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().y);

          auxleft.setPosition(escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().x-kVel , escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().y);

          auxtop.setPosition(escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().x , escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().y-kVel);

          auxdown.setPosition(escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().x , escena.getPartida()->getPersonaje()->getSprite()->getSprite().getPosition().y+kVel);
         
          /* ------------- RIGHT ------------- */

        
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (x_coord < width - radio_sprite)){
            if(compCol(mapa, auxright).left <= auxright.getPosition().x){
              escena.getPartida()->getPersonaje()->animarPersonaje();
              escena.getPartida()->getPersonaje()->getSprite()->mover((double)kVel, -0);
              x_coord += kVel;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartida()->getPersonaje()->setX(x_coord);
              escena.getPartida()->getPersonaje()->setY(y_coord);
            }
                    
          }
          /* ------------- LEFT ------------- */
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (x_coord > 0 + radio_sprite)){
            if(compCol(mapa, auxleft).left <= 0){
              escena.getPartida()->getPersonaje()->animarPersonaje();
              escena.getPartida()->getPersonaje()->getSprite()->mover((double)-kVel, 0);
              x_coord -= kVel;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartida()->getPersonaje()->setX(x_coord);
              escena.getPartida()->getPersonaje()->setY(y_coord);
            }
          }
          
          /* ------------- UP ------------- */
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (y_coord > 0 + radio_sprite)){
            band = true;
            if(compCol(mapa, auxtop).top <= 0){
              escena.getPartida()->getPersonaje()->animarPersonaje();
              escena.getPartida()->getPersonaje()->getSprite()->mover((double)0, -kVel);
              y_coord -= kVel;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartida()->getPersonaje()->setX(x_coord);
              escena.getPartida()->getPersonaje()->setY(y_coord);
            }
          }

          /* ------------- DOWN ------------- */
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (y_coord < motor->getCentroVista() + 460 - radio_sprite)){
            if(compCol(mapa, auxdown).top <= 0){
              escena.getPartida()->getPersonaje()->animarPersonaje();
              escena.getPartida()->getPersonaje()->getSprite()->mover((double)0, kVel);
              y_coord += kVel;
              linterna->getSpriteLinterna()->setPosicionSprite(escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().x, escena.getPartida()->getPersonaje()->getSprite()->getSpritePuntero()->getPosition().y);
              escena.getPartida()->getPersonaje()->setX(x_coord);
              escena.getPartida()->getPersonaje()->setY(y_coord);
            }                       
          }  
        }
         
        mapa->draw(window);
        
        escena.getPartida()->cargandoEnemigos();
        escena.dibujarPartida();
        
        linterna->dibujarLinterna();
        window->setMouseCursorVisible(false); //oculto el raton
 

        window->setView(vista);
        
        if(band == true && mover == false && escena.getPartida()->getNivel()->getNumero() != 3){
          vista.move(0,-4);
          motor->setVelocidad(-4);
          if(vista.getCenter().y < 482){
            vista.move(0,0);
            motor->setVelocidad(0);
            mover = true;
            std::cout << "Se para al final del mapa" << endl;
          }
        }
        escena.dibujarPartidaHud(escena.getPartida()->getPersonaje());
        
        //dibujo de cada bala
        if(escena.getPartida()->getPersonaje()->getArmas()[escena.getPartida()->getPersonaje()->getSeleccionada()]->getDisparando() == true){
          giraAPosDeRatonBala(window, escena.getPartida()->getPersonaje()->getArmas()[escena.getPartida()->getPersonaje()->getSeleccionada()]->getSpriteBala()->getSpritePuntero());
          
          escena.getPartida()->getPersonaje()->getArmas()[escena.getPartida()->getPersonaje()->getSeleccionada()]->dibujarBala();
          escena.getPartida()->getPersonaje()->getArmas()[escena.getPartida()->getPersonaje()->getSeleccionada()]->setDisparandoF();
        }
        escena.getPartida()->enemigoAtaca(); 
        break;
    }
  sf::Vector2i pixel_pos = sf::Mouse::getPosition(*window);
  sf::Vector2f coord_pos = window->mapPixelToCoords(pixel_pos);
 
  cursor->setPosicionSprite(sf::Mouse::getPosition(*window).x, coord_pos.y);
  //cursor->dibujar("hud", 0);
  window->draw(cursor->getSprite());
    window->display();
    escena.actualizarEscena();

  }

    
  
  return 0;
}