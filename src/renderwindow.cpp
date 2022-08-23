#include <iostream>
#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)  // declaramos la funcion
    :window(NULL), renderer(NULL) // iniciamos nuestra ventana y renderer como nulos
{
   	// creamos la ventana
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL) // en caso de que la ventana no se crea
    {
        std::cout << "Window failed to init. Error:" << SDL_GetError() << std::endl;
    }

    // nuestro renderizador es directamente nuestra gpu
    //y este utilizara la ventana para mostrar elementos
    renderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Renderer* RenderWindow::getRenderer()
{
    return renderer;
}

// limpiamos la ventana
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()  
{
    SDL_RenderClear(renderer); // limpiamos el renderer
}

// esta funcion se encarga de mostrar todos los elementos renderizados en la pantalla
void RenderWindow::display() 
{
    SDL_RenderPresent(renderer); 
}

void RenderWindow::render(DataEntity& entity) 
{
    SDL_SetRenderDrawColor(renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
    SDL_RenderDrawRect(renderer, &entity.rect);
}

void RenderWindow::renderText(SDL_Texture* texture, SDL_Rect rectangle) 
{
    SDL_RenderCopy(renderer, texture, NULL, &rectangle); 
}