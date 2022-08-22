#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "DataEntity.hpp"

// en este archivo creamos la renderizacion de la ventana como si fuera un objeto
class RenderWindow
{

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    // esta funcion se encargara de renderizar la ventana
    RenderWindow(const char* p_title, int p_w, int p_h);
    
    
    // esta funcion se encargara de limpiar la ventana antes de cerrarla
    SDL_Renderer* getRenderer();
    void cleanUp();

    // funciones de pantalla
    void clear(); // esta funcion se encargara de limpiar nuestro "render"
    void render(DataEntity& entity); // esta funcion renderizara una imagen
    void renderText(SDL_Texture* texture, SDL_Rect rectangle) ;
    void display(); // esta funcion mostrara en pantalla todo lo que se renderize
};