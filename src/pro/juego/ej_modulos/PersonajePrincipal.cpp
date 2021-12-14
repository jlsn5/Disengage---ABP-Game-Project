#include "PersonajePrincipal.h"
#include <iostream>
#include "Motor2D.h"
using namespace std;

PersonajePrincipal::PersonajePrincipal(){ //por defecto, valores base
    Motor2D *motor = Motor2D::getInstance();
    std::cout << "Creando personaje principa" << endl;
    objetosactuales = 4;
    armasactuales =2;
    trampeado =false;
    //armas principales del personaje
    a1= new Armas("cuchillo");
    a1->setArma();
    a1->cargarTexturas();
    a2 = new Armas("arco");
    a2->setArma();
    a2->cargarTexturas();
    this->setArmasIniciales(a1,a2);

    linternaPersonaje = "linterna.png";
    seleccionada=0;//como por defecto esta seleccionada el arma de la primera pos
    this->setNombre("Personaje 1");
    this->setAtaque(10);
    this->setVelocidad(5);
    this->setVelocidadAtaque(1);
    this->setVida(100);

    this->setRutaImg("resources/personajePrincipal.png");
    this->setPositionsImg(308,112,332,360); //308 //112 //640 //472 //pixeles que alcanza
    
    this->setX(motor->getAncho() / 2);
    this->setY(motor->getLongitud());
    cout << "Altura personaje: " << motor->getAlto() << endl;
    //this->setPositionsImg(0 * 75, 0 * 75, 75, 75);
    this->centrar(332/2, 360/2);
    this->cargarTexturas();
    this->getSprite()->escalar(0.2,0.2);
    malditoCogido = false;
    posMaldito = -1 ;
    linterna= new Linterna();
    for(int i = 0; i < 3; i++){
        fragmentos[i] = -1;
    }
    habilidadDisponible = 0;
    tipotrampeado=0;
    frameActual = 0;
}


PersonajePrincipal::PersonajePrincipal(string name){ //por defecto, valores base
    Motor2D *motor = Motor2D::getInstance();
    std::cout << "Creando personaje principa" << endl;
    objetosactuales = 4;
    armasactuales =2;
    trampeado =false;
    //armas principales del personaje
    a1= new Armas("cuchillo");
    a1->setArma();
    a1->cargarTexturas();
    a2 = new Armas("arco");
    a2->setArma();
    a2->cargarTexturas();
    this->setArmasIniciales(a1,a2);

    linternaPersonaje = "linterna.png";
    seleccionada=0;//como por defecto esta seleccionada el arma de la primera pos
    this->setNombre(name);
    this->setAtaque(10);
    this->setVelocidad(5);
    this->setVelocidadAtaque(1);
    this->setVida(100);

    this->setRutaImg("resources/personajePrincipal.png");
    this->setPositionsImg(308,112,332,360); //308 //112 //640 //472 //pixeles que alcanza
    
    this->setX(motor->getAncho() / 2);
    this->setY(motor->getLongitud());
    cout << "Altura personaje: " << motor->getAlto() << endl;
    //this->setPositionsImg(0 * 75, 0 * 75, 75, 75);
    this->centrar(332/2, 360/2);
    this->cargarTexturas();
    this->getSprite()->escalar(0.2,0.2);
    malditoCogido = false;
    posMaldito = -1 ;
    linterna= new Linterna();
    for(int i = 0; i < 3; i++){
        fragmentos[i] = -1;
    }
    habilidadDisponible = 0;
    tipotrampeado=0;
    frameActual = 0;
}

void PersonajePrincipal::reiniciar(){
    frameActual = 0;
    Motor2D *motor = Motor2D::getInstance();
   
    //armas principales del personaje
    a1= new Armas("cuchillo");
    a1->setArma();
    a1->cargarTexturas();
    a2 = new Armas("arco");
    a2->setArma();
    a2->cargarTexturas();
    this->setArmasIniciales(a1,a2);

    seleccionada=0;//como por defecto esta seleccionada el arma de la primera pos
    this->setAtaque(10);
    this->setVelocidad(5);
    this->setVelocidadAtaque(1);
    
    this->setX(motor->getAncho() / 2);
    this->setY(motor->getLongitud());
    this->setPositionsImg(308,112,332,360);
    this->centrar(332/2, 360/2);
    
    this->cargarTexturas();
    this->getSprite()->escalar(0.2,0.2);
    while(huecosObjetos.size() > 0){
        huecosObjetos.erase (huecosObjetos.begin() + huecosObjetos.size() - 1);
    }
    this->setVida(-100);
    for(int i = 0; i < 3; i++){
        fragmentos[i] = -1;
    }
}

bool PersonajePrincipal::cogerObjeto(Objeto *recogido){
    cout <<"accedo a coger el objeto "<<endl;
    if (recogido->getTipo() == "trampa"){ 
        trampeado =true;
        tipotrampeado = recogido->getValor();
        cout <<"entro aqui al coger obnjeto"<<endl;
        return true;
    }else if(recogido->getTipo() == "fragmento"){
        bool entra = false;
        for(int i = 0; i < 3; i++){
            if(!entra && fragmentos[i] == -1){
                fragmentos[i] = 0;
                entra = true;
            }
        }
        if(entra){
            return true;
        }
        
    }else if (recogido->getTipo() == "maldito"){
        if (malditoCogido == false){
            this->sumarVelocidad(recogido->getValor());
            malditoCogido = true;
            cout <<"he hecho todo lo que supone coger objetos"<<endl;
            return true;
        }
    }else{
        cout<<"entro a las NO trampas"<<endl;
        bool bol = false;
        if (huecosObjetos.size() < objetosactuales){
            cout<<"entro a los objetos normales"<<endl;
            for(int i=0; i<huecosObjetos.size();i++){
                if(huecosObjetos[i]->getTipo() == "rango"){
                    huecosObjetos[i] = recogido;//si ya hay un objeto linterna se cambia por ese objeto no ocupa otro espacio
                    bol = true;
                }
            }
            if(bol == false){
                if (recogido->getTipo()!="maldito"){
                    huecosObjetos.push_back(recogido);
                }
                if (huecosObjetos[huecosObjetos.size()-1]->getTipo() == "ataque"){
                    this->sumarAtaque(huecosObjetos[huecosObjetos.size()-1]->getValor());
                }else if (huecosObjetos[huecosObjetos.size()-1]->getTipo() == "vida"){
                    this->sumarVida(huecosObjetos[huecosObjetos.size()-1]->getValor());
                }else if(huecosObjetos[huecosObjetos.size()-1]->getTipo() == "velocidad"){
                    this->sumarVelocidad(huecosObjetos[huecosObjetos.size()-1]->getValor());
                }else if(huecosObjetos[huecosObjetos.size()-1]->getTipo() == "velocidadAtaque"){
                    this->sumarVelocidadAtaque(huecosObjetos[huecosObjetos.size()-1]->getValor());
                }else if(huecosObjetos[huecosObjetos.size()-1]->getTipo() == "rango"){
                    this->setLinternaPersonaje(huecosObjetos[huecosObjetos.size()-1]->getImgLinterna());
                }

            }
            return true;
        }
        
    }
    
    return false;
} //al coger objeto si devuelve false se ejecutará el intercambiar
void PersonajePrincipal::intercambiarObjeto(int posicion){
    if(recogido != NULL){
        cout << "Lo voy a intercambiar" << endl;
        //elimino la estadistica que suma dicho objeto al jugador
        if (huecosObjetos[posicion]->getTipo() == "ataque"){
            this->sumarAtaque(huecosObjetos[posicion]->getValor()*-1);
        }else if (huecosObjetos[posicion]->getTipo() == "vida"){
            //this->sumarVida(huecosObjetos[posicion]->getValor()*-1);
        }else if(huecosObjetos[posicion]->getTipo() == "velocidad"){
            this->sumarVelocidad(huecosObjetos[posicion]->getValor()*-1);
        }else if(huecosObjetos[posicion]->getTipo() == "velocidadAtaque"){
            this->sumarVelocidadAtaque(huecosObjetos[posicion]->getValor()*-1);
        }else if(huecosObjetos[posicion]->getTipo() == "rango"){
            this->setLinternaPersonaje("linterna.png");
        }
        //lo intercambio por el recogido
        //delete huecosObjetos[posicion];
        cout << "Voy a añadir: " << recogido->getTipo() << endl;
        for(int i = 0; i < huecosObjetos.size(); i++){
            cout << huecosObjetos[i]->getTipo() << endl;
        }
        huecosObjetos[posicion] = recogido;
        recogido->setRecogido();
        for(int i = 0; i < huecosObjetos.size(); i++){
            cout << huecosObjetos[i]->getTipo() << endl;
        }
    }
    

}
bool PersonajePrincipal::getMaldito(){

    return malditoCogido;
}
void PersonajePrincipal::setMaldito(bool siono){
    malditoCogido = siono;
}
void PersonajePrincipal::setLinternaPersonaje(std::string l){
    linternaPersonaje = l;
}
std::string PersonajePrincipal::getLinternaPersonaje(){
    return linternaPersonaje;
}
void PersonajePrincipal::aumentarHuecosDeObjetos(){
    objetosactuales++;//aumento los huecos

}
void PersonajePrincipal::aumentarHuecosDeArmas(){
    armasactuales++;//aumento los huecos

}


void PersonajePrincipal::intercambiarArma(Armas *recogido, int posicion){
    //elimino la estadistica que suma dicho objeto al jugador
  
    if (armasactuales==2){ //si llevo dos armas
        
        delete huecosArmas[posicion];
        huecosArmas[posicion] = recogido;
    }else{//si llevo mas 
        if(huecosArmas[2] == NULL){//si llevo 3 huecos pero no tengo ningun arma en la pos3
            
            huecosArmas[2] = recogido;
        }else{
            
            delete huecosArmas[posicion];
            huecosArmas[posicion] = recogido;
        }
    }
}


void PersonajePrincipal::setArmasIniciales(Armas *arm1, Armas *arm2){
    huecosArmas.push_back(arm1);
    huecosArmas.push_back(arm2);
}

std::vector<Objeto*> &PersonajePrincipal::getObjetos(){
    return huecosObjetos;
}
std::vector<Armas*> &PersonajePrincipal::getArmas(){
    return huecosArmas;
}

void PersonajePrincipal::setSeleccionada(int pos){
    seleccionada = pos;
}
void PersonajePrincipal::calcularAtaque(int seleccion){ //sigo por aqui falta restar daño del anterior arma
    this->setAtaque(this->getAtaque()+huecosArmas[seleccion]->getAtaqueArma());
}

int PersonajePrincipal::getSeleccionada(){
    return seleccionada;
}
int PersonajePrincipal::getNumHuecosObjetos(){
    return objetosactuales;
}
int PersonajePrincipal::getNumHuecosArmas(){
    return armasactuales;
}

void PersonajePrincipal::setRecogido(Objeto* o){
    recogido = o;
}

Objeto* PersonajePrincipal::getRecogido(){
    return recogido;
}

void PersonajePrincipal::actualizarEstadisticasPorObjetos(){
    // estadisticas iniciales
    this->setVelocidad(5);
    this->setVelocidadAtaque(1);
    //recarga de objetos 
    for (int i = 0; i < huecosObjetos.size(); i++){
        if (huecosObjetos[i]->getTipo() =="velocidadAtaque"){
            sumarVelocidadAtaque(huecosObjetos[i]->getValor());
        }else if (huecosObjetos[i]->getTipo() == "velocidad"){
            sumarVelocidad(huecosObjetos[i]->getValor());
        }
        if (malditoCogido == true){
            sumarVelocidad(-2); //lo que hace el maldito
        }
    }
}

bool PersonajePrincipal::getTrampeado(){
    return trampeado;
}
void PersonajePrincipal::setTrampeado(bool ahora) {
    trampeado = ahora;
}

Linterna* PersonajePrincipal::getLinterna(){
    return linterna;
}

void PersonajePrincipal::actualizarPosLinterna(){
    getLinterna()->getSpriteLinterna()->setPosicionSprite(getSprite()->getSpritePuntero()->getPosition().x, getSprite()->getSpritePuntero()->getPosition().y);
}
int PersonajePrincipal::getHabilidadDispo(){return habilidadDisponible;}
void PersonajePrincipal::setHabilidadDispo(int disp){habilidadDisponible=disp;}

bool PersonajePrincipal::puedoUsarHabilidad(int hab){
    if(hab == 0){
        modoHudHabilidad = false;
    }else if (hab == 1){
        modoHudHabilidad = true;
    }else{
        return modoHudHabilidad;
    }
}
double PersonajePrincipal::getTipoTrampeado(){
    return tipotrampeado;
}

void PersonajePrincipal::animarPersonaje(){
    if (seleccionada == 0){
        switch (frameActual)
    {
        case 0:
            /* code */
            this->setPositionsImg(308,112,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;
            break;
        case 1:
            /* code */
            this->setPositionsImg(2036,108,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;
            
            break;
        case 2:
            /* code */
            this->setPositionsImg(3766,98,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 3:
            /* code */
            this->setPositionsImg(5494,96,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 4:
            /* code */
            this->setPositionsImg(7226,98,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 5:
            /* code */
            this->setPositionsImg(8952,108,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 6:
            /* code */
            this->setPositionsImg(10678,112,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 7:
            /* code */
            this->setPositionsImg(12408,108,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual = 0;
            break;
        
        default:
            break;
        }
    }else{
        switch (frameActual)
    {
        case 0:
            /* code */
            this->setPositionsImg(308,112+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;
            break;
        case 1:
            /* code */
            this->setPositionsImg(2036,108+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;
            
            break;
        case 2:
            /* code */
            this->setPositionsImg(3766,98+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 3:
            /* code */
            this->setPositionsImg(5494,96+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 4:
            /* code */
            this->setPositionsImg(7226,98+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 5:
            /* code */
            this->setPositionsImg(8952,108+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 6:
            /* code */
            this->setPositionsImg(10678,112+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual++;

            break;
        case 7:
            /* code */
            this->setPositionsImg(12408,108+450,332,400);
            //this->centrar(332/2, 360/2);
        
            this->cargarTexturaAnimacion();
            this->getSprite()->escalar(0.2,0.2);
            frameActual = 0;
            break;
        
        default:
            break;
        }
    }
}