#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <ctime>
#include <cmath>
#include <windows.h>

#include "RenderWindow.hpp"
#include "DataEntity.hpp"

std::vector<int> numbers(50);
std::vector<DataEntity*> entities = {};
RenderWindow window("Sorting visualizer", 515, 135);

int position = 10;

std::vector<int> Randomize(std::vector<int> list)
{
    std::vector<int> result(list.size());
    srand(time(nullptr)); // we create the seed (the seed is a number in this case the actual date and actual hour on seconds)
    for (int i = 0; i < result.size() - 1; i++) {
        result[i] = rand() % 100 + 1; // after planting the seed we can use "rand()" creating new random values 
    }

    return result;
}

void GenerateList(std::vector<int> list) 
{
    for (int p:list)
    {
        DataEntity* entidad = new DataEntity(p, position);
        entities.push_back(entidad);
        position += 10;
    }
}

void RenderList()
{
    for (DataEntity* e:entities) 
    {
        window.render(*e);
    }
}

void UpdateList(std::vector<int> list)
{
    GenerateList(list);
    SDL_SetRenderDrawColor(window.getRenderer(), 0,0,0,255);
    window.clear();        
    RenderList();
    window.display();
    entities.clear();
    position = 10;    
}

void SelectionSort()
{
    for (int i = 0; i < numbers.size(); i++) {
        for (int j = 0; j < numbers.size(); j++) {
            if (numbers[i] <= numbers[j]) {
                std::swap(numbers[i], numbers[j]);
                SDL_Delay(5);
            }
            UpdateList(numbers);       
        }
    } 
}

void BubbleSort()
{
    for (int i = 0; i < numbers.size(); i++) {
        for (int j = 0; j < (numbers.size() -1); j++) {
            if (numbers[j] > numbers[j+1]) {
                std::swap(numbers[j], numbers[j+1]);
                SDL_Delay(5);
            }
            UpdateList(numbers);
        }
    }
}

std::vector<int> Merge (std::vector<int> l, std::vector<int> r)
{
    std::vector<int> result;
    int maxL = l.size();
    int maxR = r.size();
    int lCount = 0;
    int rCount = 0;

    while (lCount != l.size() + 1 && rCount != r.size() + 1)
    {   
        if (lCount == l.size() || rCount == r.size())
        {
            if (lCount >= maxL && rCount <= maxR)
            {
                result.push_back(r[rCount]);
                rCount++;
            }
            else if (lCount <= maxL && rCount >= maxR)
            {
                result.push_back(l[lCount]);
                lCount++;
            }
        }
        else
        {
            if (l[lCount] >= r[rCount] && lCount <= maxL) 
            {
                result.push_back(r[rCount]);
                rCount++;
            }
            else if (l[lCount] <= r[rCount] && rCount <= maxR)
            {
                result.push_back(l[lCount]);
                lCount++;
            }
        }
        SDL_Delay(5);
        UpdateList(result);
    }
    result.pop_back(); // we do this because every time the vector result ends with a extra value (sketchy fix)
    return result;
}

std::vector<int> MergeSort(std::vector<int> array) {
    int arrayLen = array.size();
    int arrayMid = floor(arrayLen/2);

    std::vector<int> firstHalf(array.begin(), array.begin() + arrayMid);
    std::vector<int> secondHalf(array.begin()  + arrayMid, array.end());

    if (arrayLen == 1) 
    {
        std::vector<int> result(array);
        return result;
    }
    else 
    {
        firstHalf = (MergeSort(firstHalf));
        secondHalf = (MergeSort(secondHalf));
        std::vector<int> result(Merge(firstHalf, secondHalf));
        return result;   
    }
}

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) { // comparamos que sdl inicie el video correctamente
        std::cout << "Hey, SDL_Init ha fallado. SDL_ERROR: " << SDL_GetError() << std::endl;
    }

    if (TTF_Init() == -1) 
    {
        std::cout << "There was a error loadint TrueFonts" << std::endl;
    }

    TTF_Font* font = TTF_OpenFont("../assets/fonts/8bitOperatorPlusSC-Regular.ttf", 32);
    if (font == nullptr) 
    {
        std::cout << "Font not loaded" << std::endl;
        exit(1);
    }
    SDL_Surface* surfaceText = TTF_RenderText_Solid(font, "[space]:new list, [1]:Merge-Sort, [2]:Selection-Sort, [3]:Bubble-Sort", {255,255,255,255});
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(window.getRenderer(), surfaceText);
    SDL_FreeSurface(surfaceText);
    SDL_Rect rectangle;
    rectangle.x = 10;
    rectangle.y = 110;
    rectangle.w = 500;
    rectangle.h = 21;

    bool gameRunning = true; 
    SDL_Event event;

    numbers = Randomize(numbers);
    
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false; 
            }
            if (event.type == SDL_KEYDOWN) // si se presiona una tecla
            {
                if (event.key.keysym.sym == SDLK_SPACE) 
                {
                    std::cout << "Randomized" << std::endl;
                    numbers = Randomize(numbers);
                }
                if (event.key.keysym.sym == SDLK_1) 
                {
                    std::cout << "Merge Sort" << std::endl;
                    numbers = MergeSort(numbers);
                }
                if (event.key.keysym.sym == SDLK_2) 
                {
                    std::cout << "Selection Sort" << std::endl;
                    // todo: add this to a function, i want to die aaaaa
                    SelectionSort();
                }
                if (event.key.keysym.sym == SDLK_3) 
                {
                    std::cout << "Bubble Sort" << std::endl;
                    BubbleSort();
                }
            }
        }
        SDL_SetRenderDrawColor(window.getRenderer(), 0,0,0,255);
        window.clear();    
        GenerateList(numbers);
        RenderList();
        window.renderText(textureText, rectangle);
        window.display();
        entities.clear();
        position = 10;
    }
    window.cleanUp(); // limpiamos la ventana
    SDL_Quit(); // salimos de sdl
    
    return 0;
}