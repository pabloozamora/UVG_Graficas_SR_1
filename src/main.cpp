#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "color.h"
#include "objReader.h"
#include "framebuffer.h"

SDL_Window* window = SDL_CreateWindow("SR 1: Carga de modelos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
SDL_Event event;

const int zoom = 60; //Agrandar modelo
const std::string modelPath = "../src/Lab_3_Pablo_Zamora.obj";
Color currentColor(255, 255, 255);
Color clearColor(0, 0, 0);  // Color del fondo
float rotationAngle = glm::radians(0.0f);

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

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle+=0.01, glm::vec3(0.0f, 1.0f, 0.0f));

        clear(clearColor);

        for (int i = 0; i*3 < verticesArray.size(); i++){
            glm::vec4 rotatedVertex1 = glm::vec4(verticesArray[i*3], 1.0f) * rotationMatrix;
            glm::vec4 rotatedVertex2 = glm::vec4(verticesArray[i*3+1], 1.0f) * rotationMatrix;
            glm::vec4 rotatedVertex3 = glm::vec4(verticesArray[i*3+2], 1.0f) * rotationMatrix;
            triangle(rotatedVertex1, rotatedVertex2, rotatedVertex3, currentColor);
        };
        
        renderBuffer(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

}

int main(int argv, char** args)
{
    clear(clearColor);
    loadOBJ(modelPath, vertices, faces, zoom);
    verticesArray = setupVertexArray(vertices, faces);
    render();
    return 0;
}