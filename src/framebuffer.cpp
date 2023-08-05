#include <glm/glm.hpp>
#include <SDL.h>
#include "color.h"
#include <vector>

const int width = 1200;
const int height = 700;
std::vector<Color> framebuffer;

void clear(const Color& clearColor) {
    framebuffer.resize(width * height);
    fill(framebuffer.begin(), framebuffer.end(), clearColor);
}

void point(const glm::vec3 coordinates, const Color color) {
    
    int x = static_cast<int>(coordinates.x);
    int y = static_cast<int>(coordinates.y);

    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        framebuffer[index] = color;
    }
}

void line(const glm::vec3 start, const glm::vec3 end, const Color color) {
    int x0 = static_cast<int>(start.x);
    int y0 = static_cast<int>(start.y);
    int x1 = static_cast<int>(end.x);
    int y1 = static_cast<int>(end.y);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        glm::vec3 coordinates(x0, y0, 0); // z-coordinate assumed as 0
        point(coordinates, color);

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void triangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const Color color) {
    line(A, B, color);
    line(B, C, color);
    line(C, A, color);
}

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        width, 
        height
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture, 
        NULL, 
        framebuffer.data(), 
        width * sizeof(Color)
    );

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}