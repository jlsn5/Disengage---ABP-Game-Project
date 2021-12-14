#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Motor2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Sprite1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Partida.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Nivel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Escena.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Objeto.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PersonajeBase.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PersonajePrincipal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_ataque.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_rango.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_vAtaque.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_velocidad.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_vida.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Armas.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Hud.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinystr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxmlerror.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxmlparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Linterna.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Npc_Mejora.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Npc_desbloqueo_objetos.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_Trampa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/O_maldito.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Juego.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"

)

