#include "Escena.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

Escena::Escena(){
    estado = 0; //menus
    menu.crearMenu(960, 960, "titulo");
    cont = 0;
    actual =0;
    primera = true;
    cargarPartidas();
}

Escena::Escena(int width, int height){
    estado = 0; //menus
    
    menu.crearMenu(width, height, "titulo");
    cont = 0;
    actual = 0;
    alturaActual = motor->getLongitud() - motor->getAlto() / 2;
    std::cout << "Altura inicial mapa: " << alturaActual << endl;
    primera = true;
    cargarPartidas();
    if(partidas.size() > 0){
        partidas[actual]->getPersonaje()->calcularAtaque(0);
    }
  
}
 
Escena::~Escena(){

}

void Escena::setEstado(int e){
    estado = e;
}
int Escena::getEstado(){
    return estado;
}

void Escena::actualizarEscena(){
    switch(estado){
        case 0: //Menus
            if(menu.getModo() == 'm'){ //menus
                estado = 0; //menus
                if(menu.getEliminada() != -1){
                        for(int i = 0; i < partidas.size(); i++){
                            if(i == menu.getEliminada()){
                                if(partidas[i] != NULL){
                                    //Elimino partida seleccionada
                                    eliminarPartida(i);
                                    delete partidas[i];
                                    partidas[i] = NULL;
                                    cont--;
                                }   
                            }
                        }
                        inputText = "";
                        menu.setNombre("No hay partida creada");

                        menu.actualizarPartidas(partidas);
                        menu.setEliminada(-1);
                        menu.setEstado(3);
                        
                }
            }else if(menu.getModo() == 't'){
                actual = menu.getpActual();
                std::ostringstream buff;
                vector<std::string> estadisticas;
                int mon = partidas[actual]->getMonedas();
                buff<<mon;
                estadisticas.push_back(buff.str());
                std::ostringstream buf;
                mon = partidas[actual]->getEnemigosMatados();
                buf<<mon;
                estadisticas.push_back(buf.str());
                std::ostringstream bufff;
                mon = partidas[actual]->getTotalObjetosRecogidos();
                bufff<<mon;
                estadisticas.push_back(bufff.str());
                std::ostringstream buffff;
                mon = partidas[actual]->getVecesMuerto();
                buffff<<mon;
                estadisticas.push_back(buffff.str());
                if(partidas[actual]->getTotalObjetosDesbloqueados() == 4){
                    estadisticas.push_back("Vida");
                    estadisticas.push_back("Ataque");
                    estadisticas.push_back("VelocidadAtaque");
                    estadisticas.push_back("Velocidad");
                }else if(partidas[actual]->getTotalObjetosDesbloqueados() == 5){
                    estadisticas.push_back("Vida");
                    estadisticas.push_back("Ataque");
                    estadisticas.push_back("VelocidadAtaque");
                    estadisticas.push_back("Velocidad");
                    estadisticas.push_back("Rango");
                }
                estadisticas.push_back("Cuchillo");
                estadisticas.push_back("Arco");
                if(partidas[actual]->getDesbloqueaHabilidad() == 1){
                    estadisticas.push_back("Desbloqueada");
                }else{
                    estadisticas.push_back("Bloqueada");
                }
                
                menu.actualizarEstadisticas(estadisticas);    
            }else if(menu.getModo() == 'p'){ //partida
                //partida
                if(menu.getpActual() == -1){
                    std::cout << "(escena/p)la partida existe actual : "<<menu.getpActual()<<endl;
                    menu.setNombre(this->inputText);
                    //std::cout<< "Cambia a partida" << endl;
                    if(partidas.size() < 4){
                        std::string n;
                        n = getMenu().getNombre();
                        if(n == ""){
                            n = "Partida " + static_cast<std::ostringstream*>(&(std::ostringstream() << partidas.size()))->str();  
                        }
                        p = new Partida(n);

                        std::cout<< "crea una partida" << endl;
                        int l = partidas.size();
                        if(l == cont){
                            partidas.push_back(p);
                        }else{
                            for(int i = 0; i < partidas.size(); i++){
                                if(partidas[i] == NULL){
                                    partidas[i] = p;
                                    std::cout << "lo reemplaza" << endl;
                                }
                            }
                        }
                        cont++;        
                        inputText = "";
                        menu.actualizarPartidas(partidas);
                        menu.setModo('b');
                        estado = 1;
                    }else{            
                        if(menu.getEliminada() != -1){
                            for(int i = 0; i < partidas.size(); i++){
                                if(i == menu.getEliminada()){
                                    if(partidas[i] != NULL){
                                        /*std::cout << "toca eliminar" << endl;
                                        //Elimino partida seleccionada
                                        delete partidas[i];
                                        partidas[i] = NULL;*/
                                        eliminarPartida(i);
                                        //Se reemplaza por una nueva con el nombre introducido previamente
                                        std::string n = getMenu().getNombre();
                                        p = new Partida(n);
                                        partidas[i] = p;
                                    }   
                                }
                            }
                            inputText = "";
                            menu.setNombre(this->inputText);
                            menu.actualizarPartidas(partidas);
                            menu.setEliminada(-1);
                            menu.setEstado(3);
                        }   
                    }
                }else{
                    switch(menu.getpActual()){
                        case 0:
                            actual = 0;
                            break;
                        case 1:
                            actual = 1;
                            break;
                        case 2:
                            actual = 2;
                            break;
                        case 3:
                            actual = 3;
                            break;
                    }
                    estado = 2;
                    menu.setModo('b');
                    partidas[actual]->reiniciar();
                    primera = true;
                }
            }else if(menu.getModo() == 'x'){
                estado = 6;
                p = new Partida();
                primera = true;
                p->crearNivel(20);
            }
            break;

        case 1: //Ya se ha creado la partida y se crea el nivel

            if(menu.getpActual() == -1){
                actual = partidas.size() - 1;
                primera = true;
            }else{
                actual = menu.getpActual();
            }
            if(partidas[actual] != NULL){
                partidas[actual]->crearNivel(0);
            }
            estado = 2;
            break;

        case 2: //Modo juego
            if(menu.getModo() != 'm'){
                alturaActual += motor->getVelocidad();
            }
            if (partidas[actual]->getPersonaje()->getVida() <= 0){
                estado = 5; //muerte
                partidas[actual]->sumarVecesMuerto();
                std::cout << "Lo esta matando" << endl;
                //guardarPartida(); //GUARDADO DE PARTIDA AL MORIR
            }
            
            if (partidas[actual]->getPersonaje()->getY() <= 100){ //100
                
                switch(partidas[actual]->getNivel()->getNumero()){
                    case 0: //bosque
                        estado = 4; //npc
                        std::cout << "Cambia a NPC" << endl;
                        break;
                    case 10: //hab 1
                        /*primera = true;
                        partidas[actual]->getNivel()->setNumero(1);*/ //cementerio
                        break;
                    case 1: //cementerio
                        estado = 4; //npc
                        std::cout << "Cambia a NPC" << endl;
                        break;
                    case 11: //hab 2
                       /* primera = true;
                        //cargar mapa final
                        partidas[actual]->getNivel()->setNumero(2);
                        std::cout << "Llegamos al mapa final" << endl;*/
                        break;
                    case 2: //pantano
                        //cout << "Final del juego" << endl;
                        primera = true;
                        partidas[actual]->getNivel()->setNumero(-2);
                        break;
                    case 19:
                        //estado = 5;
                        break;
                }
                if (partidas[actual]->getPersonaje()->getY() <= 50 && partidas[actual]->getPersonaje()->getX() >= 400 && partidas[actual]->getPersonaje()->getX() <= 700){
                    switch(partidas[actual]->getNivel()->getCasa()){
                        case 1:
                            primera = true;
                            partidas[actual]->getNivel()->setNumero(10 + (rand() % 3));
                            break;
                        case 2:
                            primera = true;
                            partidas[actual]->getNivel()->setNumero(13 + (rand() % 3));
                            break;
                        case 3:
                            primera = true;
                            partidas[actual]->getNivel()->setNumero(16 + (rand() % 3));
                            break;
                    }
                    
                }
            }
            
            
            menu.setAlturaActual(alturaActual);
            break;
        case 3: //menu intercambio
            if(menu.getModo() == 'b'){
                menu.actualizarObjetos(partidas[actual]->getPersonaje()->getObjetos());
                
                menu.setEstado(7);
                menu.setModo('m');
            }
            break;
        case 4://NPC
            if (partidas[actual]->getPersonaje()->getMaldito()!=false){
                partidas[actual]->getPersonaje()->setMaldito(false);
                //DESBLOQUEO DE HABILIDAD
                if (partidas[actual]->getDesbloqueaHabilidad() == 0){
                    //significa que no ha desbloqueado aún la habilidad y la desbloqueamos
                    partidas[actual]->setDesbloqueaHabilidad(1); //esto se guardara en el txt de la partida 
                    partidas[actual]->getPersonaje()->setMaldito(false); //ya no lleva el maldito, lo ha intercambiado por la habilidad desbloqueada para siempre
                }
            }
            guardarPartida(); //al terminar el nivel y pasar por el npc
            if(primera){
                estado = 2;
                partidas[actual]->cargarNivel();
            }
           
            break;

        case 5: //Game Over
            if(partidas[actual]->getNivel()->getNumero() == 19){
                menu.setEstado(12);
                menu.setModo('f');
                cout << "Aqui si entra" << endl;
                partidas[actual]->getNivel()->setNumero(-1);
            }else if(p->getNivel()->getNumero() == 20){
                menu.setEstado(0);
                estado = 0;
                p->getNivel()->setNumero(-1);
                menu.setModo('m');
            }
            if(menu.getModo() == 'b'){
                menu.setEstado(8);
                menu.setModo('f');
                
            }else if(menu.getModo() == 'l'){
                estado = 2;
                menu.setModo('b');
                partidas[actual]->reiniciar();
                primera = true;
                cout << "Vuelve a reiniciar?" << endl;
            }
            if(menu.getpActual() == -1){
                this->setEstado(0);
            }
            guardarPartida();//al morir guardo partida
            break;
        case 6: //Modo Extremo
            if (p->getPersonaje()->getVida() <= 0){
                estado = 5; //muerte
            }
            break;

    }
    
}

void Escena::dibujarPartida(){
    if(estado == 6){
        p->dibujar();
    }else{
        partidas[actual]->dibujar();
    }
   
}

void Escena::dibujarPartidaHud(PersonajePrincipal *per){
    if(estado == 6){
        p->dibujarHud(per, p->getMonedas());
    }else{
        partidas[actual]->dibujarHud(per, partidas[actual]->getMonedas());
    }
    
}


Menu Escena::getMenu(){
    return menu;
}

void Escena::actualizarMenu(int c){
    switch(c){
        case 0: //onclick
            menu.onClick();
            break;
        case 1: //moveup
            menu.MoveUp();
            break;
        case 2: //movedown
            menu.MoveDown();
            break;
        case 3: //setnombre
           menu.setNombre(this->inputText);
            break;
        case 4: //setSelectedItem
            menu.setSelectedItem(this->selectedItem);
            break;
    }
}

void Escena::setInputText(std::string t){
    if(t == "borrar" && inputText.size() > 0){
        inputText.erase(inputText.size()-1);
    }else{
        inputText += t;
    }
    
}

void Escena::setSelectedItem(int i){
    selectedItem = i;
}

std::vector<Partida*> &Escena::getPartidas(){
    return partidas;
}

int Escena::getActual(){
    return actual;
}

bool Escena::getPrimera(){
    return primera;
}

void Escena::setPrimera(bool n){
    primera = n;
}

void Escena::guardarPartida(){
    //cout << "autoguardado..."<<endl;
  //creamos el archivo y lo abrimos en la ruta
  ofstream file;
  std::stringstream parti;
  parti.str(std::string());  
  parti<<actual;
  std::string cadenaNumerica ="partidas_guardadas/partida_"+ parti.str();
  
  file.open(cadenaNumerica.c_str());
  
  //Escribo en el fichero lo que quiero guardar
  file <<partidas[actual]->getNombre()<<"\n";
  file <<partidas[actual]->getMonedas()<<"\n";
  
  std::string armassdes="";  
  for(int i=0;i<partidas[actual]->getArmasDesbloqueadas().size();i++){
      if (i==partidas[actual]->getArmasDesbloqueadas().size()-1){
          armassdes +=partidas[actual]->getArmasDesbloqueadas()[i];
      }else{
          armassdes +=partidas[actual]->getArmasDesbloqueadas()[i] + "|";
      }
  }
  
  file <<armassdes<<"\n";
    
  std::string objdes="";
  for (int i=0;i<partidas[actual]->getObjetos().size();i++){
      if(i+1 != partidas[actual]->getObjetos().size() && partidas[actual]->getObjetos()[i+1]!=NULL){
          if (partidas[actual]->getObjetos()[i+1]->getTipo()!="ataque"){//este sirve para no coger 5 veces ataque
              objdes +=partidas[actual]->getObjetos()[i]->getTipo() + "|";
          }
      }else{
          objdes +=partidas[actual]->getObjetos()[i]->getTipo();
      }
  }
  file<<objdes<<"\n";
  file<< partidas[actual]->primeraVezQuePasoLaHistoria()<<"\n";

  file<< partidas[actual]->getVecesMuerto()<<"\n";
  file<< partidas[actual]->getTotalObjetosRecogidos() << "\n";
  file<< partidas[actual]->getEnemigosMatados()<<"\n";
  file<< partidas[actual]->getDesbloqueaHabilidad()<<"\n"; //si guarda un 0 no tiene habilidad, si guarda un 1 tiene habilidad
  //file << "ObjetoDesbloqueado:"<<<<"\n";
  //std::cout << "guardado terminado!"<<endl;
  
  file.close();
}

void Escena::cargarPartidas(){ 


    std::string cadena;
    std::cout<<"intento leer la partida del fichero" <<endl;
    //compruebo si existe el fichero de la partida 0 1 2;
    //si existe lo leo
    for (int i = 0 ; i < 4 ; i++ ){
        int mon;
        int enemigosMatados;
        int totalObjRecogidos;
        int vecesMuerto;
        int habilidadDesbloqueada = 0;
        std::string nom;
        vector<std::string> arms;
        vector<std::string> objs;
        bool firstTime;
        std::stringstream parti;
        parti.str(std::string());  
        parti<<i;
        std::string archivo ="partidas_guardadas/partida_" + parti.str();
        ifstream archALeer(archivo.c_str());
        int contador=0;
        while (getline(archALeer, cadena)) {
            
            contador++;
            //archALeer >> cadena;
            //cout << cadena << endl;
            
            //FALTA RECOGER VALORES
            if (cadena !="" && contador <11){
                if (contador == 1){
                    nom = cadena.c_str();
                    //cout<<cadena<<endl;
                    std::cout <<"nombre leido: " << nom <<endl;
                }else if (contador == 2){
                    //cout << cadena<<endl;
                    mon = atoi(cadena.c_str()) ; //de string a int 
                    std::cout << "monedas leidas : "<< mon <<endl;
                }else if (contador == 3){
                    int i = 0;
                    std::cout << "armas leidas :" <<endl;
                    for(size_t p=0, q=0; p!=cadena.npos; p=q){
                        arms.push_back(cadena.substr(p+(p!=0),(q=cadena.find("|", p+1))-p-(p!=0)));
                        std::cout << arms[i] << endl;
                        i++;
                    }

                }else if (contador == 4){
                    int i = 0;
                    std::cout << "objetos leidas :" <<endl;
                    for(size_t p=0, q=0; p!=cadena.npos; p=q){
                        objs.push_back(cadena.substr(p+(p!=0),(q=cadena.find("|", p+1))-p-(p!=0)));
                        std::cout << objs[i] << endl;
                        i++;
                    }

                }else if (contador == 5){
                    if (cadena == "0"){
                        firstTime = false;
                    }else{
                        firstTime = true;
                    }
                }else if(contador == 6){
                    vecesMuerto = atoi(cadena.c_str());
                    std::cout << "Veces muerto: " << vecesMuerto << endl;
                }else if(contador == 7){
                    totalObjRecogidos = atoi(cadena.c_str());
                    std::cout << "Total objs recogidos: " << totalObjRecogidos << endl;
                }else if(contador == 8){
                    enemigosMatados = atoi(cadena.c_str());
                    std::cout << "Total enemigos matados: " << enemigosMatados << endl;
                }else if (contador == 9){
                    habilidadDesbloqueada = atoi(cadena.c_str());
                    std::cout << "La habilidad está en : " <<habilidadDesbloqueada <<endl;
                }//una vez guardo todas las variables abajo en el if contador <5 creo las partidas con esos valores
            }else {
                std::cout << "partida vacia" << endl;
            }
        }//por ultimo FALTA METER TODO EN LAS VARIABLES 

        if (contador<8){
            //partidas[i] = NULL;
            std::cout <<"Partida no existe "<<endl;
        }else{
            //Valores recogidos, aplicados a la partida en cuestion;       
            Partida *par = new Partida(nom);
            std::cout << "APLICO las monedas"<<endl;
            par->sumarMonedas(mon); //inicialmente 0 pero al cargar += lo que carguemos
            std::cout <<"antes de entrar a las armas"<<endl;
            for (int j = 0; j < arms.size();j++){
                if (arms.size()>2){
                    if (arms[j]!="cuchillo" && arms[j]!="arco"){
                        Armas *a = new Armas(arms[j]); //nunca entrará, pero lo dejo preparado para cuando haya +armas
                        par->agregarArmasAArmasDesbloqueadas(a);
                    }
                }else{
                    break;
                }
            }
            std::cout <<"antes de entrar a los objetos"<<endl;
            std::cout << "objetos size " << objs.size()<<endl;
            
            for (int j = 0; j < objs.size();j++){
                if (objs.size()>4){
                    if (objs[j]!="ataque" && objs[j]!="vida" && objs[j]!="velocidad" && objs[j]!="velocidadAtaque" && objs[j]!="maldito"){
                        if (objs[j]=="rango"){
                            O_rango *o = new O_rango(1);
                            par->agregarObjetosAObjetosDesbloqueados(o);
                        } 
                    }
                    //cout <<"habilidad desbloqueada: " <<habilidadDesbloqueada <<endl;
                }else{
                    break;
                }
            }
            
            par->setDesbloqueaHabilidad(habilidadDesbloqueada);
            par->cargarEstadisticas(vecesMuerto, totalObjRecogidos, enemigosMatados);
            std::cout << "antes de la primera vez"<<endl;
            par->cambiarPrimeraVez(firstTime);
            partidas.push_back(par); //creo la partida y le paso los valores
            
            partidas[partidas.size()-1]->crearNivel(0);
            partidas[actual]->getPersonaje()->setHabilidadDispo(habilidadDesbloqueada);
        }
        archALeer.close();
    }
    
    cont = partidas.size();
    std::cout << "Hay : " << cont << " partidas" <<endl;
    menu.actualizarPartidas(partidas);
}

void Escena::eliminarPartida(int posicion){
    if(partidas[posicion]!=NULL){
        ofstream file;
        std::stringstream parti;
        parti.str(std::string());  
        parti<<posicion;
        std::string nombreFich ="partidas_guardadas/partida_"+ parti.str();

        file.open(nombreFich.c_str(), std::ofstream::out | std::ofstream::trunc); //borra el contenido del fichero
        file.close();
        delete partidas[posicion];
        partidas[posicion] = NULL;
        cout << "Se elimina la partida" << endl;

    }
}


void Escena::cargarNPC(){
    switch(partidas[actual]->getNivel()->getNumero()){
        case 0:
            partidas[actual]->getNivel()->cargarNpc(0);
            partidas[actual]->getNivel()->getNPC()->colocarObjetos(partidas[actual]->getPersonaje(), partidas[actual]->getMonedas());
            break;
        case 1:
            partidas[actual]->getNivel()->cargarNpc(1);
            partidas[actual]->getNivel()->getNPC2()->setPersonaje(partidas[actual]->getPersonaje());
            partidas[actual]->getNivel()->getNPC2()->colocarObjetos();
            break;
    }
}
              
           
Partida* Escena::getPartida(){
    return p;
}