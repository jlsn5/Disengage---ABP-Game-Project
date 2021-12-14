
#include "Nivel.h"
#include "Motor2D.h"
#include <iostream>
#include <time.h>
using namespace std;

Nivel::Nivel(){
    numero = 0;
}

Nivel::Nivel(int num, int a, int o, int m){
    numero = num;
    mapa = new Mapa();
    mapa->leerMapa(1);
    //cargarMapa();
    hud = new Hud(a, o);
    //std::cout <<"Nivel creado" << endl;
    MAXenemigos=3;//modificar el constructor para que tambien se le pase este numero
    srand (time(NULL));
    fragmento1 = new Objeto("fragmento", 1);
    fragmento2 = new Objeto("fragmento", 2);
    fragmento3 = new Objeto("fragmento", 3);
    fragmento4 = new Objeto("fragmento", 4);
    texture.loadFromFile("resources/spider06.png");
    casa = 0;
}

void Nivel::cargarMapa(){
    //cout <<"BBBBBBBBBBBBBBBBBBBB" << "              "  << endl;
    mapa->leerMapa(1);
}
void Nivel::cargarHud(PersonajePrincipal *p, int m){
    hud->dibujarHud(p, m);
}
vector<Enemigos*>  Nivel::getEnemigos(){
    return enemigos;
}
vector<Objeto*> Nivel::getObjetos(){
    return objetos;
}
vector<O_Trampa*> Nivel::getTrampas(){
    return trampas;
}
int Nivel::getMAXenemigos(){
    return MAXenemigos;
}
void Nivel::cargarNpc(int n){
    switch(n){
        case 0:
            npc = new Npc_Mejora();
            break;
        case 1:
            npcd = new Npc_desbloqueo_objetos();
            break;
    }
    
}

Npc_Mejora* Nivel::getNPC(){
    return npc;
}

Npc_desbloqueo_objetos* Nivel::getNPC2(){
    return npcd;
}

void Nivel::cargarEnemigos(){
    if(getNumero()!=19){
        if ((rand()%1000) < 30){
            Motor2D *motor= Motor2D::getInstance();
            if(enemigos.size()<5){
                Enemigos *e = new Enemigos(rand()%2,texture);
                //e->getSprite()->getSprite().setTexture(texture);
                e->setX((rand()%900)+20);
                e->setY(motor->getCentroVista()-400);
                e->getSprite()->setPosicionSprite(e->getX(),e->getY());
                //cout<<"dont x:  "<<e->getX()<<" wowo: "<<e->getY()<<endl;
                enemigos.push_back(e);
            }else if(enemigos.size()==5){
                for (int i = 0; i < enemigos.size(); i++)
                {
                    if(enemigos[i]==0){
                        
                        Enemigos *e = new Enemigos(rand()%2, texture);
                        //e->getSprite()->getSprite().setTexture(texture);
                        e->setX((rand()%900)+20);
                        e->setY(motor->getCentroVista()-400);
                        e->getSprite()->setPosicionSprite(e->getX(),e->getY());
                        //cout<<"sonrt:  "<<e->getX()<<" wowo: "<<e->getY()<<endl;
                        enemigos[i]=e;

                        i=enemigos.size();
                    }
                }
            }  
        }
    }else{
        Motor2D *motor= Motor2D::getInstance();
            if(enemigos.size()<1){
                Enemigos *e = new Enemigos(2,texture);
                //e->getSprite()->getSprite().setTexture(texture);
                e->setX(400);
                e->setY(300);
                e->getSprite()->setPosicionSprite(e->getX(),e->getY());
                //cout<<"dont x:  "<<e->getX()<<" wowo: "<<e->getY()<<endl;
                enemigos.push_back(e);
            }
    }
}


void Nivel::objetoAobjetos(Objeto * obj){
    Motor2D *motor= Motor2D::getInstance();
    objetos.push_back(obj);
    
	objetos[objetos.size()-1]->getSpriteObjeto()->setPosicionSprite(rand()%930,rand()%motor->getLongitud());
    //and()%motor->getLongitud()/2
    //cout<<"done"<<endl;
}
void Nivel::trampaAtrampas(O_Trampa * t){
    Motor2D *motor= Motor2D::getInstance();
    trampas.push_back(t);
    
	trampas[trampas.size()-1]->getSpriteObjeto()->setPosicionSprite(rand()%930,rand()%motor->getLongitud());
    //and()%motor->getLongitud()/2
    //cout<<"done"<<endl;
}

void Nivel::matar(int posicion){
    delete enemigos[posicion];
    enemigos[posicion]=0;

}

void Nivel::setNumero(int n){
    numero = n;
}

int Nivel::getNumero(){
    return numero;
}

Objeto* Nivel::getFragmento(int niv){
    switch (niv){
        case 11:
            return fragmento1;
            break;
        case 15:
            return fragmento2;
            break;
        case 16:
            return fragmento3;
            break;
        default:
            return fragmento4;
            break;
    }
    
}

Mapa* Nivel::getMapa(){
    return mapa;
}

Hud* Nivel::getHud(){
    return hud;
}

int Nivel::getCasa(){
    return casa;
}

void Nivel::setCasa(int i){
    casa = i;
}