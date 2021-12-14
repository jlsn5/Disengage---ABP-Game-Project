#include "Partida.h"
#include <iostream>
#include <math.h>
using namespace std;

Partida::Partida(){
	bossmuerto = false;
	nombre = "Partida 1";
	monedas = 0;
	totalArmasDesbloqueadas = 2;
	totalEnemigosMatados = 0;
	totalObjetosRecogidos = 0;
	totalVecesMuerto = 0;
	totalObjetosDesbloqueados = 4;
	for(int i = 0; i < 4; i++){
		fragmentos[i] = 0;
	}
	personaje = new PersonajePrincipal();
	primeraVez = true;
	maxObjetosSpawn = 7; //cambia la cantidad de objetos que spawnea un nivel

	O_ataque *o = new O_ataque(0);
	O_vAtaque *va = new O_vAtaque(0);
	O_velocidad *v = new O_velocidad(0);
	O_vida *vid = new O_vida(0);
	O_rango *ra = new O_rango(0);

	O_ataque *o1 = new O_ataque(0);
	O_ataque *o2 = new O_ataque(0);
	O_ataque *o3 = new O_ataque(0);
	O_ataque *o4 = new O_ataque(0);
	objetosDesbloqueados.push_back(o);
	objetosDesbloqueados.push_back(o1);
	objetosDesbloqueados.push_back(o2);
	objetosDesbloqueados.push_back(o3);
	objetosDesbloqueados.push_back(o4);
	objetosDesbloqueados.push_back(va);
	objetosDesbloqueados.push_back(v);
	objetosDesbloqueados.push_back(vid);

	objetosDesbloqueables.push_back(ra);
	Armas *arm1 = new Armas("cuchillo");
	Armas *arm2 = new Armas("arco");
	armasDesbloqueadas.push_back(arm1);
	armasDesbloqueadas.push_back(arm2);
	
	O_Trampa *tr1 = new O_Trampa("p_azul");
	O_Trampa *tr2 = new O_Trampa("glitch");
	O_Trampa *tr3 = new O_Trampa("sonido");
	trampasDisponibles.push_back(tr1);
	trampasDisponibles.push_back(tr2);
	trampasDisponibles.push_back(tr3);
	cout << "objeto trampa por aqui"<<endl;
	trampasDisponibles[0]->getSpriteTrampa()->setPosicionSprite(0,9000);
	trampasDisponibles[1]->getSpriteTrampa()->setPosicionSprite(0,9000);
	//el tercero es de sonido no hace falta ponerle posicion
	longitudPant = motor->getLongitud()-480;
	longitudPantIntervalo = 0;
	desbloqueaHabilidad = 0;
}

Partida::Partida(std::string nomb){
	bossmuerto = false;
	this->nombre = nomb;
	monedas = 0;
	totalArmasDesbloqueadas = 2;
	totalEnemigosMatados = 0;
	totalObjetosRecogidos = 0;
	totalVecesMuerto = 0;
	totalObjetosDesbloqueados = 4;
	for(int i = 0; i < 4; i++){
		fragmentos[i] = 0;
	}
	personaje = new PersonajePrincipal(nomb);
	primeraVez = true;
	maxObjetosSpawn = 7; //cambia la cantidad de objetos que spawnea un nivel


	O_ataque *o = new O_ataque(0);
	O_vAtaque *va = new O_vAtaque(0);
	O_velocidad *v = new O_velocidad(0);
	O_vida *vid = new O_vida(0);
	O_rango *ra = new O_rango(0);

	O_maldito *tr = new O_maldito(0);
	O_ataque *o1 = new O_ataque(0);
	O_ataque *o2 = new O_ataque(0);
	O_ataque *o3 = new O_ataque(0);
	O_ataque *o4 = new O_ataque(0);
	
	objetosDesbloqueados.push_back(o);
	objetosDesbloqueados.push_back(o1);
	objetosDesbloqueados.push_back(o2);
	objetosDesbloqueados.push_back(o3);
	objetosDesbloqueados.push_back(o4);
	objetosDesbloqueados.push_back(va);
	objetosDesbloqueados.push_back(v);
	objetosDesbloqueados.push_back(vid);
	objetosDesbloqueados.push_back(tr); //maldito

	objetosDesbloqueables.push_back(ra);
	Armas *arm1 = new Armas("cuchillo");
	Armas *arm2 = new Armas("arco");
	armasDesbloqueadas.push_back(arm1);
	armasDesbloqueadas.push_back(arm2);
	
	O_Trampa *tr1 = new O_Trampa("p_azul");
	O_Trampa *tr2 = new O_Trampa("glitch");
	O_Trampa *tr3 = new O_Trampa("sonido");
	trampasDisponibles.push_back(tr1);
	trampasDisponibles.push_back(tr2);
	trampasDisponibles.push_back(tr3);
	cout << "objeto trampa por aqui"<<endl;
	trampasDisponibles[0]->getSpriteTrampa()->setPosicionSprite(0,9000);
	trampasDisponibles[1]->getSpriteTrampa()->setPosicionSprite(0,9000);
	//el tercero es de sonido no hace falta ponerle posicion
	longitudPant = motor->getLongitud()-480;
	longitudPantIntervalo = 0;
	desbloqueaHabilidad = 0;
}

Partida::~Partida(){
	std::string nombre = "No hay partida creada";
	delete personaje;
    monedas = -1; //?
	for(int i = 0; i < 4 ; i++){
		fragmentos[i] = -1;
	}
}
int Partida::getDesbloqueaHabilidad(){
	return desbloqueaHabilidad;
}
void Partida::setDesbloqueaHabilidad(int des){
	desbloqueaHabilidad = des;
}
void Partida::guardarPartida(int monedas, PersonajePrincipal *pers, int fragmentos[]){
	this->monedas = monedas;
	for(int i = 0; i < 4; i ++){
		this->fragmentos[i] = fragmentos[i];
	}
	this->personaje = pers;
}

std::string Partida::getNombre(){
	return this->nombre;
}

void Partida::setNombre(std::string s){
	this->nombre = s;
}

void Partida::crearNivel(int numNivel){
	niv = new Nivel (numNivel, this->getHuecosArmas(), this->getHuecosObjetos(), this->getMonedas());
	
	
}

int Partida::getHuecosObjetos(){
	return personaje->getNumHuecosObjetos();
}

int Partida::getHuecosArmas(){
	return personaje->getNumHuecosArmas();
}

int Partida::getMonedas(){
	return monedas;
}
void Partida::sumarMonedas(int s){
	monedas += s;
}
void Partida::quitarMonedas(int s){
	monedas = monedas - s;
}
void Partida::cargandoEnemigos(){
	niv->cargarEnemigos();

}
void Partida::cargandoObjetos(){ //spawn de objetos
	if (niv->getObjetos().size() <= maxObjetosSpawn){
		
		int r=rand()%objetosDesbloqueados.size();
		niv->objetoAobjetos(objetosDesbloqueados[r]);
	}
}

void Partida::cargandoTrampas(){ //spawn de objetos
	if (niv->getTrampas().size() <= 3){
		
		int r=rand()%trampasDisponibles.size();
		niv->trampaAtrampas(trampasDisponibles[r]);
	}
}

void Partida::dibujar(){
	//niv->cargarMapa();
	//dibujar objetos
	//dibujar enemigos
	
	//int cont = 0;
	for (int i = 0; i < niv->getEnemigos().size(); i++)
	{
		if (niv->getEnemigos().empty() ==false){
			
			if(niv->getEnemigos()[i]!=0 && niv->getEnemigos()[i]->getVida()>0){
				niv->getEnemigos()[i]->animarEnemigo();
				//cout <<"imprimo i :" <<i<<endl;
				//niv->getEnemigos()[i]->getSprite()->setTextura("resources/spider06.png");
				//niv->getEnemigos()[i]->cargarTexturas();
				//cout<<"se dibuja el enemigo "<<i<<endl;
				//niv->animarEnemigos();
				//GIRO ENEMIGOS

				niv->getEnemigos()[i]->getSprite()->dibujar("enem",0);
				//cout<<"SPRTE ENEMIGO: "<<niv->getEnemigos()[i]->getSprite()->getSpritePuntero()<<endl;
				niv->getEnemigos()[i]->movimiento(personaje);
				//cout <<"enemigos: "<<cont<<endl;cont++;
				if (calcularDistanciaPJEnemigo(niv->getEnemigos()[i], personaje)>1100){
					niv->matar(i);
				}
			}
		}
	}
	cargandoObjetos();
	

	for (int i = 0; i < niv->getObjetos().size(); i++)
	{
		
		if (niv->getObjetos().empty() ==false){
			if(niv->getObjetos()[i]!=NULL){
				if(niv->getObjetos()[i]->getRecogido()==false)
					niv->getObjetos()[i]->getSpriteObjeto()->dibujar("obj",0);
			}
		}
	}
	
	//personaje->animarPersonaje();
	personaje->getSprite()->dibujar("pers", 0);

	cargandoTrampas();
	
	for (int i = 0; i < niv->getTrampas().size(); i++)
	{
		
		if (niv->getTrampas().empty() ==false){
			if(niv->getTrampas()[i]!=NULL){

				niv->getTrampas()[i]->getSpriteObjeto()->dibujar("obj",0);
			}
		}
	}
	//personaje->getSprite()->setOrigen(75 / 2, 75 / 2);
	//std::cout << "Dibujando partida" << endl;motor->getLongitud()-477
	//cout << "longitud pantalla : "<< motor->getLongitud()<<endl;
	//double longi = motor->getCentroVista() - 480;
	
	trampasDisponibles[0]->getSpriteTrampa()->setPosicionSprite(0,longitudPant);
	if (personaje->getTrampeado()==true && personaje->getTipoTrampeado() == 1){ //pantallazo azul 
		trampasDisponibles[0]->getSpriteTrampa()->dibujar("obj",1);
		cout << "l pantalla = "<< longitudPant<<endl;
		cout << "l pantalla inter = "<< longitudPantIntervalo<<endl;
		if( motor->getCentroVista() <= longitudPantIntervalo-200 ){
			personaje->setTrampeado(false);
		}
	}
	trampasDisponibles[1]->getSpriteTrampa()->setPosicionSprite(0,longitudPant);
	if (personaje->getTrampeado()==true && personaje->getTipoTrampeado() == 2){ //glitxh
		trampasDisponibles[1]->getSpriteTrampa()->dibujar("obj",1);
		cout << "l pantalla = "<< longitudPant<<endl;
		cout << "l pantalla inter = "<< longitudPantIntervalo<<endl;
		if( motor->getCentroVista() <= longitudPantIntervalo-200 ){
			personaje->setTrampeado(false);
		}
	}
	//trampasDisponibles[2]->getSpriteTrampa()->setPosicionSprite(0,longitudPant);
	if (personaje->getTrampeado()==true && personaje->getTipoTrampeado() == 3){ //sound
		//sonido
		motor->cargarSonido("resources/Cuchillo.wav",'s');
        motor->reproducir('s');
		if( motor->getCentroVista() <= longitudPantIntervalo-150 ){
			personaje->setTrampeado(false);
		}
	}
	longitudPant += motor->getVelocidad();
	
}

void Partida::setIntervaloTrampa(double intervalo){
	longitudPantIntervalo = intervalo;
}
void Partida::dibujarHud(PersonajePrincipal *p, int m){
	niv->cargarHud(p, m);
}

void Partida::cambiarPos(float x, float y){
	personaje->setX(x);
	personaje->setY(y);
}

PersonajePrincipal* Partida::getPersonaje(){
	return personaje;
}

Nivel* Partida::getNivel(){
	return niv;
}

vector<Objeto*> &Partida::getObjetos(){
	return objetosDesbloqueados;
}

vector<O_Trampa*> &Partida::getTrampas(){
	return trampasDisponibles;
}

bool Partida::primeraVezQuePasoLaHistoria(){
	return primeraVez;
}
void Partida::cambiarPrimeraVez(bool p){
	primeraVez = p;
}
float Partida::calcularDistanciaPJEnemigo(Enemigos* enemigo, PersonajePrincipal* personaje){
	float distance = 1000000.0f;
	//if (!labyrinth->tileBlocksEntity(ghost->getTileX() + addX, ghost->getTileY() + addY))
	//{
		distance = (float) sqrt(pow((enemigo->getX() - (personaje->getX())), 2) + pow((enemigo->getY() - (personaje->getY())), 2));
	//}
	return distance;
}

void Partida::dispararArma(){
	
	if(personaje->getArmas()[personaje->getSeleccionada()]->getTipo() == "cuchillo"){
		motor->cargarSonido("resources/Cuchillo.wav",'s');
		motor->reproducir('s');
		for (int i = 0 ; i < niv->getEnemigos().size();i++){
			if (niv->getEnemigos()[i] != NULL){

				cout << "distancia: " << calcularDistanciaPJEnemigo(niv->getEnemigos()[i], personaje)<<" rango: " <<  personaje->getArmas()[personaje->getSeleccionada()]->getRango()<<endl;
				if (calcularDistanciaPJEnemigo(niv->getEnemigos()[i], personaje) < personaje->getArmas()[personaje->getSeleccionada()]->getRango()){ //calculamos el rango, si el enemigo esta cerca, cuchillazo

				cout<<"muerete perro "<<endl;
					niv->getEnemigos()[i]->sumarVida(-1*personaje->getAtaque());
					std::cout<< "resto :"<<-1 * personaje->getAtaque()<<" al perro su vida actual es "<<niv->getEnemigos()[i]->getVida()<<endl;
					std::cout<< "vida personaje: "<< personaje->getVida()<<endl;
					if(niv->getEnemigos()[i]->getVida()<=0){
						
						monedas += (rand()%10)+1; //monedas que se obtiene
						niv->matar(i);
						sumarEnemigosMatados();
						std::cout<<"perro muerto"<<endl;

					}
				}
			}
		}
	}else if (personaje->getArmas()[personaje->getSeleccionada()]->getTipo() == "arco"){

		motor->cargarSonido("resources/arco.wav",'s');
		motor->reproducir('s');
		personaje->getArmas()[personaje->getSeleccionada()]->getSpriteBala()->setPosicionSprite(personaje->getX(),personaje->getY()-15);

		personaje->getArmas()[personaje->getSeleccionada()]->setDisparandoT(); //true disparo

		for (int i =0 ; i < niv->getEnemigos().size();i++){
			if (niv->getEnemigos()[i] !=NULL){
				if(calcularDistanciaPJEnemigo(niv->getEnemigos()[i], personaje) < personaje->getArmas()[personaje->getSeleccionada()]->getRango()){

					if (motor->coinciden(personaje->getArmas()[1]->getSpriteBala(),niv->getEnemigos()[i]->getSprite())){
						cout<<"distancia al enemigo"<<calcularDistanciaPJEnemigo(niv->getEnemigos()[i], personaje)<<endl;
						cout<<"el rango del arma es:"<<personaje->getArmas()[personaje->getSeleccionada()]->getRango()<<endl;
						niv->getEnemigos()[i]->sumarVida(-1*personaje->getAtaque());
						std::cout<< "resto :"<<-1 * personaje->getAtaque()<<" al perro su vida actual es "<<niv->getEnemigos()[i]->getVida()<<endl;
						std::cout<< "vida personaje: "<< personaje->getVida()<<endl;
						if(niv->getEnemigos()[i]->getVida()<=0){	
							monedas += (rand()%10)+1; //monedas que se obtiene
							if (niv->getEnemigos()[i]->getNombre() == "BOSS"){
								bossmuerto=true;
							}
							niv->matar(i);
							sumarEnemigosMatados();
							std::cout<<"perro muerto"<<endl;
							
						}
						break;
					}
				}
			}
		}
	}
}
/*
void Partida::borrarEnemigo(){
	for(int j=0;j<niv->getEnemigos().size();j++){
          if(niv->getEnemigos()[j]!=NULL){
			niv->getEnemigos()[j]->getSprite()->dibujar("pers",0);
		  }
        }
}*/

int Partida::getPosRecogido(){
	return posRecogido;
}

void Partida::setPosRecogido(int p){
	posRecogido = p;
}

void Partida::enemigoAtaca(){
	for (int i = 0; i< niv->getEnemigos().size();i++){
		if (niv->getEnemigos()[i]!=NULL){
			if (niv->getEnemigos()[i]->getSprite()->getSpritePuntero()->getGlobalBounds().intersects(personaje->getSprite()->getSpritePuntero()->getGlobalBounds())){
				personaje->sumarVida(-1*niv->getEnemigos()[i]->getAtaque());
				//cout <<" vida " << personaje->getVida()<<endl;
				
			}
		}
	}
}

void Partida::reiniciar(){
	personaje->reiniciar();
	niv->getHud()->reiniciarPos();
	niv->setNumero(0);
	/*while(personaje->getObjetos().size() > 0){
		delete personaje->getObjetos()[0];
		cout << "Entra" << endl;
	} */
}

void Partida::cargarNivel(){
	personaje->setX(motor->getAncho() / 2);
	personaje->setY(motor->getLongitud());
}

vector<std::string> Partida::getArmasDesbloqueadas() {
	vector<std::string> nombrearmas;
	for(int i=0;i<armasDesbloqueadas.size();i++){
		nombrearmas.push_back(armasDesbloqueadas[i]->getTipo());
	}
	return nombrearmas;
}

void Partida::agregarArmasAArmasDesbloqueadas(Armas *a){
	//añado al vector de armas disponibles el arma 
	armasDesbloqueadas.push_back(a);

	//elimino de armas a desbloquear ese arma
	for (int i = 0; i < armasDesbloquebles.size(); i++){
		if (armasDesbloquebles[i]->getTipo() == a->getTipo()){
			delete armasDesbloquebles[i];
		}
	}
}
void Partida::agregarObjetosAObjetosDesbloqueados(Objeto *o){
	//añado al vector de objetos disponibles el objeto 
	objetosDesbloqueados.push_back(o);

	//elimino de armas a desbloquear ese arma
	for (int i = 0; i < objetosDesbloqueables.size(); i++){
		if (objetosDesbloqueables[i]->getTipo() == o->getTipo()){
			delete objetosDesbloqueables[i];
		}
	}
}

void Partida::sumarVecesMuerto(){
	totalVecesMuerto+=1;
	cout << "Me mata: "<< totalVecesMuerto << endl;
}
int Partida::getVecesMuerto(){
	return totalVecesMuerto;
}
void Partida::sumarObjetosRecogidos(){
	totalObjetosRecogidos++;
}
int Partida::getTotalObjetosRecogidos(){
	return totalObjetosRecogidos;
}
void Partida::sumarEnemigosMatados(){
	totalEnemigosMatados++;
}
int Partida::getEnemigosMatados(){
	return totalEnemigosMatados;
}
int Partida::getTotalObjetosDesbloqueados(){
	return totalObjetosDesbloqueados;
}
int Partida::getTotalArmasDesbloqueadas(){
	totalArmasDesbloqueadas = armasDesbloqueadas.size();
	return totalArmasDesbloqueadas;
}

void Partida::cargarEstadisticas(int vecesMuerto, int objRecogidos, int enemigosMatados){
	totalArmasDesbloqueadas = armasDesbloqueadas.size();
	//totalObjetosDesbloqueados = objetosDesbloqueados.size();
	totalVecesMuerto = vecesMuerto;
	totalEnemigosMatados = enemigosMatados;
	totalObjetosRecogidos = objRecogidos;
}

void Partida::mejorarObjetos(int n){
	if(getPersonaje()->getObjetos()[n] != NULL){ //Hay objeto 1
        if (getMonedas() >= getPersonaje()->getObjetos()[n]->getRareza()*10){
            if (getPersonaje()->getObjetos()[n]->getRareza() <3){
                quitarMonedas(getPersonaje()->getObjetos()[n]->getRareza()*10);
                std::cout << "boton 1"<<endl;
                getPersonaje()->getObjetos()[n]->setRareza(getPersonaje()->getObjetos()[n]->getRareza() + 1);
            }
        }
    }
}

bool Partida::getBossMuerto() {
	return bossmuerto;
}