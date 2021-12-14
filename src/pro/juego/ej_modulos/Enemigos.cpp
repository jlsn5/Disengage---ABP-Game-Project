#include "Enemigos.h"
#include <iostream>
#include <cmath>

using namespace std;

Enemigos::Enemigos(int e, sf::Texture texture){ //Cambiamos los valores de la clase padre segun el enemigo
    contarvecesataque1 = 0;
    frameActual = 0;
    vueltaanimacion = false;
    cargaataque1 =false;
    cargacaminar = false;
    fase = 0;
    transformadoBoss = false;
    detectado=true;
    switch (e)
    {
    case (0):
        this->setNombre("Araña");
        this->setVida(21);
        this->setVelocidad(3);
        this->setAtaque(1);
        this->setVelocidadAtaque(1);
        rangoDeteccion=25;

        this->setRutaImg("resources/spider06.png");
        this->setPositionsImg(0*37.5,3.5*37.5,72,72);
        this->cargarTexturas();

        this->getSprite()->getSprite().setTexture(texture);
        //this->spritePersonaje->setTextura(rutaImagen);
        this->getSprite()->recortarSetTextureRect(0*37.5,3.5*37.5,72,72);
        this->getSprite()->escalar(1, 1);
        // Lo dispongo en el centro de la pantalla
        this->getSprite()->setOrigen(1, 1);
        
        break;
    case (1):
        this->setNombre("Velocista");
        this->setVida(1);
        this->setVelocidad(9);
        this->setAtaque(7);
        this->setVelocidadAtaque(1);
        rangoDeteccion=50;

        this->setRutaImg("resources/enemigoSprite.png");
        this->setPositionsImg(745,313,140,90);
        this->cargarTexturas();

        this->getSprite()->getSprite().setTexture(texture);
        //this->spritePersonaje->setTextura(rutaImagen);
        this->getSprite()->recortarSetTextureRect(745,313,140,90);
        this->getSprite()->escalar(1, 1);
        // Lo dispongo en el centro de la pantalla
        this->getSprite()->setOrigen(1, 1);
        
        break;
    case (2):
        this->setNombre("BOSS");
        this->setVida(1000);
        this->setVelocidad(1.5);
        this->setAtaque(1);
        this->setVelocidadAtaque(1);
        rangoDeteccion=100;

        this->setRutaImg("resources/TRANSFORM.png");
        this->setPositionsImg(0,0,31,23);
        this->cargarTexturas();

        this->getSprite()->getSprite().setTexture(texture);
        //this->spritePersonaje->setTextura(rutaImagen);
        this->getSprite()->recortarSetTextureRect(0,0,31,23);
        this->getSprite()->escalar(4.f, 4.f);
        // Lo dispongo en el centro de la pantalla
        this->getSprite()->setOrigen(1, 1);
        
        
        break;
    default:
        break;
    }
    
}
void Enemigos::animarEnemigo(){
    if (getNombre() == "Araña"){
        switch (frameActual)
    {
        case 0:
            /* code */
            this->setPositionsImg(264,141,45,46);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            //this->getSprite()->escalar(0.2,0.2);
            frameActual++;
            break;
        case 1:
            /* code */
            this->setPositionsImg(328,141,55,46);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            //this->getSprite()->escalar(0.2,0.2);
            frameActual++;
            
            break;
        case 2:
            /* code */
            this->setPositionsImg(392,141,55,46);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            //this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 3:
            /* code */
            this->setPositionsImg(456,141,55,46);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            //this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 4:
            /* code */
            this->setPositionsImg(521,141,55,46);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            //this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 5:
            /* code */
            this->setPositionsImg(585,141,55,46);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            //this->getSprite()->escalar(0.2,0.2);
            frameActual=0;

            break;
        
        default:
            break;
        }
    }else if (getNombre() == "Velocista"){
        switch (frameActual)
        {
            case 0:
                /* code */
                this->setPositionsImg(745,313,140,90);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(0.4,0.4);
                frameActual++;
                break;
            case 1:
                /* code */
                this->setPositionsImg(554,313,140,90);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(0.4,0.4);
                frameActual++;
                
                break;
            case 2:
                /* code */
                this->setPositionsImg(370,313,140,90);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(0.4,0.4);
                frameActual++;

                break;
            case 3:
                /* code */
                this->setPositionsImg(168,313,140,90);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(0.4,0.4);
                frameActual=0;

                break;
            
            default:
                break;
        }
    }else if (getNombre() == "BOSS"){
        
        if (transformadoBoss == false){
            switch (frameActual){
            case 50:
                /* code */
                this->setPositionsImg(0,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                frameActual++;
                break;
            case 51:
                frameActual++;
            break;
            case 52:
                /* code */
                this->setPositionsImg(33,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
 
                frameActual++;
                
                break;
            case 53:
                frameActual++;
            break;
            case 54:
                /* code */
                this->setPositionsImg(67,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
  
                frameActual++;

                break;
            case 55:
                frameActual++;
                break;
            case 56:
                /* code */
                this->setPositionsImg(100,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
        
                frameActual++;

                break;
            case 57:
                frameActual++;
                break;
            case 58:
                /* code */
                this->setPositionsImg(131,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                frameActual++;

                break;
            case 59:
                frameActual++;
                break;
            case 60:
                /* code */
                this->setPositionsImg(165,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
   
                frameActual++;

                break;
            case 61:
                frameActual++;
                break;
            case 62:
                /* code */
                this->setPositionsImg(198,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
              
                frameActual++;

                break;
            case 63:
                frameActual++;
                break;
            case 64:
                /* code */
                this->setPositionsImg(231,0,31,23);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                frameActual = 0;
                transformadoBoss = true;
                fase = 0;
                break;
            
            default:
                frameActual++;
                break;
            }
        }else if(fase == 0){
            if(cargacaminar == false){
                this->setPositionsImg(0,0,35,24);
                this->setRutaImg("resources/CAMINAR.png");
                
                this->cargarTexturas();
                cargacaminar = true;
                cargaataque1 = false;
                cargaataque2 = false;
            }

            switch (frameActual){
            case 0:
                /* code */
                this->setPositionsImg(0,0,35,25);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                frameActual++;
                break;
            case 1:
                frameActual++;
            break;
            case 2:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,34,25);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                frameActual++;
                
                break;
            case 3:
                frameActual++;
            break;
            case 4:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,24);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                frameActual++;

                break;
            case 5:
                frameActual++;
                break;
            case 6:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,24);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
              
                frameActual++;

                break;
            case 7:
                frameActual++;
                break;
            case 8:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,24);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
              
                frameActual++;

                break;
            case 9:
                frameActual++;
                break;
            case 10:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,24);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                frameActual++;

                break;
            case 11:
                frameActual++;
                break;
            case 12:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,24);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
 
                frameActual++;

                break;
            case 13:
                frameActual++;
                break;
            case 14:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,24);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
          
                frameActual = 0;
                if (getVida() <= 500 && contarvecesataque1 >= 10){cout<<"entro al ataque supremo"<<endl;
                    fase = 2;
                    contarvecesataque1 = 0;
                }else if (getVida() <= 750){cout<<"entro al ataque "<<endl;
                    fase = 1;
                    contarvecesataque1++;
                }else if(getVida()>750){
                    fase = 0;
                }
                cout << "ataque veces: "<<contarvecesataque1<<endl;
                break;
            
            default:
                frameActual++;
                break;
            }
        }else if (fase == 1){
            
            if(cargaataque1 == false){
                this->setRutaImg("resources/ATAQUE.png");
                this->setPositionsImg(0,0,35,31);
                
                this->cargarTexturas();
                cargaataque1 = true;
                setVelocidad(0);
                setAtaque(1);
            }
            
            switch (frameActual){
            case 0:
                /* code */
                this->setPositionsImg(0,0,35,31);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                frameActual++;
                break;
            case 1:
                frameActual++;
            break;
            case 2:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,34,36);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual++;
                
                break;
            case 3:
                frameActual++;
            break;
            case 4:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,41);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual++;

                break;
            case 5:
                frameActual++;
                break;
            case 6:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,45);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual++;

                break;
            case 7:
                frameActual++;
                break;
            case 8:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,39);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual++;

                break;
            case 9:
                frameActual++;
                break;
            case 10:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,35);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual++;

                break;
            case 11:
                frameActual++;
                break;
            case 12:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,30);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual++;

                break;
            case 13:
                frameActual++;
                break;
            case 14:
                /* code */
                this->setPositionsImg(35*(frameActual/2),0,33,27);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                this->getSprite()->getSprite().setRotation(90.f);
                frameActual = 0;
                fase = 0;
                setVelocidad(1.5);
                setAtaque(1);
                cargacaminar = false;
                break;
            
            default:
                frameActual++;
                break;
            }

        }else if (fase == 2){
           if(cargaataque2 == false){
                this->setRutaImg("resources/ATAQUE2.png");
                this->setPositionsImg(0,19,45,43);

                this->cargarTexturas();
                cargaataque2 = true;
                frameActual = 0;
                setVelocidad(0);
                setAtaque(1);
            }
            //sw
            switch (frameActual){
            case 0:
                /* code */
                this->setPositionsImg(0,19,45,43);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
                
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual= 0;
                    vueltaanimacion =false;
                    fase = 0;
                }
                break;
            case 1:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
            break;
            case 2:
                /* code */
                this->setPositionsImg(45*(frameActual/2),19,45,66);
                //this->centrar(332/2, 360/2);
   
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
 
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                
                break;
            case 3:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
            break;
            case 4:
                /* code */
                this->setPositionsImg(45*(frameActual/2),19,45,66);
                //this->centrar(332/2, 360/2);

                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }

                break;
            case 5:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 6:
                /* code */
                this->setPositionsImg(45*(frameActual/2),16,45,69);
                //this->centrar(332/2, 360/2);

                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }

                break;
            case 7:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 8:
                /* code */
                this->setPositionsImg(45*(frameActual/2),12,45,73);
                //this->centrar(332/2, 360/2);
          
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
   
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }

                break;
            case 9:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 10:
                /* code */
                this->setPositionsImg(45*(frameActual/2),8,45,77);
                //this->centrar(332/2, 360/2);
         
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }

                break;
            case 11:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 12:
                /* code */
                this->setPositionsImg(45*(frameActual/2),0,45,85);
                //this->centrar(332/2, 360/2);
            
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);
  
                
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }

                break;
            case 13:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 14:
                /* code */
                this->setPositionsImg(45*(frameActual/2),0,45,85);
                //this->centrar(332/2, 360/2);
              
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 15:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 16:
                /* code */
                this->setPositionsImg(45*(frameActual/2),0,45,85);
                //this->centrar(332/2, 360/2);
                
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 17:
                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;

            case 18:
                /* code */
                this->setPositionsImg(45*(frameActual/2),0,45,85);
                //this->centrar(332/2, 360/2);
                
                this->cargarTexturaAnimacion();
                this->getSprite()->escalar(4.f,4.f);

                if (vueltaanimacion ==false){
                    frameActual++;
                }else{
                    frameActual--;
                }
                break;
            case 19:

                vueltaanimacion = true;
                cargacaminar = false;

                frameActual --;
                break;

            default:
                frameActual++;
                break;
            }
        }
        
    }
}

void Enemigos::detectarPersonaje(float distancia){//distancia calculada en el main entre el enemigo y el principal
    if(!detectado){
        if(distancia<=rangoDeteccion){
            detectado=true;
        }
    }
}
float Enemigos::calcularDistancia(PersonajePrincipal* personaje){
    float distance = 1000000.0f;
		distance = (float) sqrt(pow((this->getX() - (personaje->getX())), 2) + pow((this->getY() - (personaje->getY())), 2));

	return distance;
}
void Enemigos::golpe(PersonajePrincipal* personaje){
    personaje->setVida(personaje->getVida()-this->getAtaque());
}
void Enemigos::movimiento(PersonajePrincipal* personaje){
   
    if(detectado){
        if(this->getX()-2 > personaje->getX()){
            //mover enemigo en X negativa con la velocidad del enemigo
            this->getSprite()->mover(this->getVelocidad()*-1,0);
            //this->getSpriteO().move(this->getVelocidad()*-1,0);
            setX(this->getX()+(this->getVelocidad()*-1));
            setY(this->getY());
            //this->setPositions(this->getX()+(this->getVelocidad()*-1),this->getY());
        }else if(this->getX()+5 < personaje->getX()){
            //mover enemigo en X positiva con la velocidad del enemigo
            this->getSprite()->mover(this->getVelocidad(),0);
           // this->getSpriteO().move(this->getVelocidad(),0);
            setX(this->getX()+(this->getVelocidad()));
            setY(this->getY());
           
           // this->setPositions(this->getX()+(this->getVelocidad()),this->getY());
        }

        if(this->getY() > personaje->getY()){
            //mover enemigo en Y negativa con la velocidad del enemigo
            this->getSprite()->mover(0,this->getVelocidad()*-1);
            //this->getSpriteO().move(0,this->getVelocidad()*-1);
            setX(this->getX());
            setY(this->getY()+(this->getVelocidad()*-1));
            //this->setPositions(this->getX(),this->getY()+(this->getVelocidad()*-1));
        }else if(this->getY() < personaje->getY()){
            //mover enemigo en Y positiva con la velocidad del enemigo
            this->getSprite()->mover(0,this->getVelocidad());
            //this->getSpriteO().move(0,this->getVelocidad());
            setX(this->getX());
            setY(this->getY()+(this->getVelocidad()));
           // this->setPositions(this->getX(),this->getY()+(this->getVelocidad()));
        }
    }

}


float Enemigos::getRangoDeteccion(){
    return rangoDeteccion;
}
bool Enemigos::getDetectado(){
    return detectado;
}