#include <SDL.h>
#include <glm/glm.hpp>
#include <iostream>
#include "color.h"
#include "objReader.h"
#include "framebuffer.h"

SDL_Window* window = SDL_CreateWindow("SR1", 150, 70, 1200, 700, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
SDL_Event event;

const std::string modelPath = "./test.obj";
Color currentColor(255, 255, 255);
Color clearColor(0, 0, 0);  // Color del fondo

std::vector<glm::vec3> vertices;
std::vector<Face> faces;
std::vector<glm::vec3> verticesArray;

void render(){

    SDL_Init(SDL_INIT_EVERYTHING);

    bool isRunning = true;
    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Renderizar el modelo
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);

        loadOBJ(modelPath, vertices, faces);
        verticesArray = setupVertexArray(vertices, faces);
        SDL_Log("hola");
        SDL_Log("%f", vertices[0].x);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
}

int main(int argv, char** args)
{
    clear(clearColor);
    render();
    return 0;
}