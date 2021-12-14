# Manual de usuario

#Guía de ejecución

- Ejecución del fichero setup.sh para descargar todos los archivos multimedia del juego. Se descargarán todos los ficheros en la carpeta resources de src (./setup.sh). Se ejecuta en la ruta "proyectoabp-grupo-b5/".

- Ejecución del main. Se aconseja mantener la pantalla en la resolución por defecto. Ruta de ejecución: "proyectoabp-grupo-b5/src/pro/juego/"
Nosotros ejecutamos de la siguiente forma:
Si tienes carpeta build/ dentro de  src/pro/juego eliminala para empezar la ejecución de nuevo
cmake -H. -Bbuild
cmake --build build
./build/MiJuego

- Una vez todo ejecutado. Elegir Nueva partida, ponerle un nombre a la partida y jugar.

#Controles para jugar
![Carátula del juego](../src/pro/juego/resources/controles.png)

- Los trucos que se debe saber antes de corregir:
Hay objetos que al cogerlos te ponen dificultades (trampa)
Hay objetos que te suman facultades 
Hay objetos que te quitan facultades
Al llegar con un objeto que te quita facultades al primer npc se desbloquea un dash

si quieres probarlo sin enemigos : comentar linea 926 main.cpp
si quieres probarlo sin linterna : comentar lineas  929 y 933 main.cpp