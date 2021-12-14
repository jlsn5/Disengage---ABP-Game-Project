#include "Mapa.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

Mapa::Mapa()
{
    //ctor
    numCapas=0;
}

Mapa::~Mapa(){
  //Destructor
    for(int cont=0; cont<numCapas; cont++){
        for(int cont2; cont2<altura; cont2++){
            delete[] _tilemap[cont][cont2];
        }
    delete[] _tilemap[cont];
    }
    delete[] _tilemap;
}

Mapa::Mapa(const Mapa& aux){

}

void Mapa::leerMapa(int nivel){
  TiXmlDocument doc;
  //int matriz3D
  //Se le pasa un entero para determinar el nivel, 1-Nivel Bosque, 2-Nivel cementerio...

  //Faltaria filtrar el nivel con el entero por parametro
    if(nivel == 0){ //Mapa modo extremo
        doc.LoadFile("./resources/infinito.tmx");
    }else if(nivel==1){ //bosque
        doc.LoadFile("./resources/bosque1.tmx");
    }else if(nivel==2){ //cementerio
        doc.LoadFile("./resources/cementerio.tmx");
    }else if(nivel == 3){ //hab 1
        doc.LoadFile("./resources/habitacion1.tmx");
    }else if(nivel == 4){ //hab 2
        doc.LoadFile("./resources/habitacion2.tmx");
    }else if(nivel == 5){ //patano
        doc.LoadFile("./resources/pantano.tmx");
    }else if(nivel == 6){ //Hab 3
        doc.LoadFile("./resources/habitacion3.tmx");
    }else if(nivel == 7){ //hab 4
        doc.LoadFile("./resources/habitacion4.tmx");
    }else if(nivel == 8){ //hab 5
        doc.LoadFile("./resources/habitacion5.tmx");
    }else if(nivel == 9){ //hab 6
        doc.LoadFile("./resources/habitacion6.tmx");
    }else if(nivel == 10){ //hab 7
        doc.LoadFile("./resources/habitacion7.tmx");
    }else if(nivel == 11){ //hab 8
        doc.LoadFile("./resources/habitacion8.tmx");
    }else if(nivel == 12){ //hab 9
        doc.LoadFile("./resources/habitacion9.tmx");
    }else if(nivel == 13){ //Mapa final
        doc.LoadFile("./resources/final.tmx");
    }

  //doc.LoadFile("./resources/bosque1.tmx");

  //Navegar por los items del documento
  TiXmlElement* mapaxml = doc.FirstChildElement("map");

  //Metadatos del tmx
  //if(mapaxml != NULL){
    mapaxml-> QueryIntAttribute("width", &anchura);
    mapaxml-> QueryIntAttribute("height", &altura); 
    mapaxml-> QueryIntAttribute("tilewidth", &tileAnchura);
    mapaxml-> QueryIntAttribute("tileheight", &tileAltura);
  //}

  //Imagen del tileset
  TiXmlElement *img = mapaxml->FirstChildElement("tileset")->FirstChildElement("image");

    if(img != NULL){
        //const char *filename = img->Attribute("source");
        //cout<<"filename-->"<<filename<<endl;

        //filename="./resources/"+filename;

        string fulname= (string)img->Attribute("source");
        fulname="./resources/"+fulname;

        
        _tilesetTexture.loadFromFile(fulname);
    }

  //Acceder a diferentes capas y contabilizarlo
  TiXmlElement *capa = mapaxml->FirstChildElement("layer");
  numCapas=0;
  //Si capa es null, numcapas es igual a 0
  if(capa != NULL){
    while(capa){
        capa=capa->NextSiblingElement("layer");
        numCapas++;
    }
  }
  //cout<<"n de capas->  "<<numCapas<<endl;


  //Generar matriz 3D
   _tilemap = new int**[numCapas];

  for(int i=0; i<numCapas; i++){
      _tilemap[i]=new int*[altura];
  }
  //Segundo bucle donde guardamos la anchura
  for(int l=0; l<numCapas; l++){
      for(int y=0; y<altura; y++){
          _tilemap[l][y]=new int[anchura];
      }
  }

  //Cargando los GIDs de multiples capas
  TiXmlElement *datos;
  string *nombre=new string[numCapas];
  capa=mapaxml->FirstChildElement("layer");

  int var1;
  var1=0;



  //TiXmlElement *data = mapaxml->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

  //bool aux;

  while(capa){
    datos=capa->FirstChildElement("data")->FirstChildElement("tile");
    nombre[var1]=(string)capa->Attribute("name");   //Numero
    //for(int l=0; l<numCapas;l++){
        
    while(datos){
    for(int y=0; y<altura; y++){
        for(int x=0; x<anchura; x++){
            if(nombre[var1] != ""){
                datos->QueryIntAttribute("gid", &_tilemap[var1][y][x]);
                
                datos=datos->NextSiblingElement("tile");
            }
        }
    }
  }
    var1++;
    capa=capa->NextSiblingElement("layer");
  }


//Cod pab
//Guardamos los sprites
//\EXTRA
_tilemapSprite=new Sprite***[numCapas];

for (int num1=0; num1<numCapas; num1++){
    _tilemapSprite[num1]=new sf::Sprite**[altura];
}

for (int num1=0; num1<numCapas; num1++){

    for(int num2=0; num2<altura; num2++){
            _tilemapSprite[num1][num2]=new sf::Sprite*[anchura];

        for(int num4=0; num4<anchura;num4++){
            _tilemapSprite[num1][num2][num4]=new sf::Sprite();
        }
    }

}
//cout <<"BBBBBBBBBBBBBBBBBBBB" << "              "  << endl;
//cout<<"texturetileset->"<<_tilesetTexture.getSize().y<<endl;
int filas = _tilesetTexture.getSize().y/tileAltura;
int columnas = _tilesetTexture.getSize().x/tileAnchura;
/*
cout << "filasycol ->" <<filas<<" "<<columnas<<endl;
cout << _tilesetTexture.getSize().x <<endl;
cout << _tilesetTexture.getSize().y << endl;*/



_tilesetSprites=new sf::Sprite[filas*columnas]; 
//Espacio para las imagenes

int aux=0;
//tileset nos lo guardamos
//for (int l = 0; l < numCapas; l++){
    for(int fil=0; fil<filas;fil++){
        for(int col=0; col<columnas; col++){
            //cout << "ayuda " << endl;
            _tilesetSprites[aux].setTexture(_tilesetTexture);
            _tilesetSprites[aux].setTextureRect(sf::IntRect(col*tileAnchura, fil*tileAltura, tileAnchura, tileAltura));
            aux++;
        }
    }
//}
//cout <<"CCCCCCCCCCCCCCCCC" << "              "  << endl;
//cout<<"HOLA"<<endl;

  //Matrices de Sprites
    //DIBUJANDO
  for(int l=0; l<numCapas;l++){
      for(int y=0; y<altura; y++){
          for(int x=0; x<anchura; x++){
              int gid = _tilemap[l][y][x]-1;
              //cout <<filas*columnas << "              " << gid << endl;

                if(gid>= filas*columnas){
                    //cout<<"gid->"<<gid<<endl;
                    //cout<<"filas->"<<filas<<endl;
                    //cout<<"columnas->"<<columnas<<endl;
                    //cout<<"Error en el calculo de tiles"<<endl;
                    //_tilemapSprite[l][y][x] = NULL;

                }else if(gid>0){
                    //Si fuera 0 no creo Sprite
                    _tilemapSprite[l][y][x] = new sf::Sprite(
                        _tilesetTexture, _tilesetSprites[gid].getTextureRect());
                    _tilemapSprite[l][y][x]->setPosition(x*tileAnchura, y*tileAltura);

                }else{
                    //No sobrecarga nada
                    _tilemapSprite[l][y][x] = NULL;
                }
          }
      }
  }
}

void Mapa::dibujar(){
    for(int l=0; l<numCapas;l++){
        for(int y=0; y<altura; y++){
            for(int x=0; x<anchura; x++){
                if(_tilemapSprite[l][y][x]!=NULL){
                    cout << "    1    " <<_tilemapSprite[l][y][x] << endl;
                    motor->dibujarM(*(_tilemapSprite[l][y][x]));
                    cout << "   2     " <<_tilemapSprite[l][y][x] << endl;
                    //window->draw((_tilemapSprite[l][y][x]));
                }
            }
        }
    }
}

void Mapa::draw(sf::RenderWindow* window){
    for(int l=0; l<numCapas;l++){
      for(int y=0; y<altura; y++){
          for(int x=0; x<anchura; x++){
            if(_tilemapSprite[l][y][x]!=NULL){
                window->draw(*(_tilemapSprite[l][y][x]));
            }
          }
       }
    }
}

/*
bool Mapa::compruebaColision(sf::FloatRect &fr){
    bool dev = false;
    if(numCapas >= 1){
        for(int fil=0; fil<altura; fil++){
            for(int col=0; col<anchura; col++){
                // cout<<"pintando sprites"<<endl;
                if(_tilemapSprite[1][fil][col]!=NULL){
                    if(fr.intersects(_tilemapSprite[0][fil][col]->getGlobalBounds())){
                        dev = true;
                    }
                }
            }
        }
    }
    return dev;
}
*/

int Mapa::getAltura(){
    return altura;
}
int Mapa::getAnchura(){
    return anchura;
}
Sprite**** Mapa::getMapaSprites(){
    return _tilemapSprite;
}

