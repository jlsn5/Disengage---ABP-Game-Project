Carpeta para otro tipo de recursos, no definidos en las otras carpetas de la plantilla.

*En este fichero se debe especificar como descargar los ficheros binarios (imágenes, sonidos...) que se requieran para corregir la práctica y como disponerlos de manera correcta en el proyecto y prototipos (solo de la rama master).*

Ejecución del fichero setup.sh para descargar todos los archivos multimedia del juego. Se descargarán todos los ficheros en la carpeta resources de src (./setup.sh)

DESDE LA RUTA : "proyectoabp-grupo-b5/" ejecutar ./setup.sh
DESDE LA RUTA : "proyectoabp-grupo-b5/src/pro/juego/"  ejecutar
    Nosotros personalmente lo hacemos de la siguiente forma:
    cmake -H. -Bbuild   (para crear la carpeta build en src/pro/juego/ )
    cmake --build build  (compilamos)
    cmake ./build/MiJuego  


