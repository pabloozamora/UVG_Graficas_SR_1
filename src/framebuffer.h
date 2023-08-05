#pragma once
#include "color.h"
#include <glm/glm.hpp>
#include <vector>
#include <SDL.h>

void clear(const Color&);

void point(const glm::vec3, const Color);

void line(const glm::vec3, const glm::vec3, const Color);

void triangle(const glm::vec3&, const glm::vec3&, const glm::vec3&, const Color);

void renderBuffer(SDL_Renderer*);