#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <array>
#include <SDL.h>

struct Face {
    std::vector<std::array<int, 3>> vertexIndices;
};

bool loadOBJ(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<Face>& out_faces, int zoom = 10) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::vector<glm::vec3> temp_vertices;
    std::vector<Face> temp_faces;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {  // Vertex
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(glm::vec3(vertex.x * zoom, vertex.y * zoom, vertex.z * zoom));
        } else if (type == "f") {  // Face
            Face face;
            std::array<int, 3> vertexIndices;
            for (int i = 0; i < 3; ++i) {
            char slash;
            // Read the vertex index and ignore the rest
            iss >> vertexIndices[i];
            int nextChar = iss.peek(); // Peek at the next character
            if (nextChar == '/') {
                iss.ignore(); // Ignore the slash
                while (isdigit(iss.peek())) {
                    iss.ignore(); // Ignore the texture coordinate index
                }
                iss.ignore(); // Ignore the second slash
                while (isdigit(iss.peek())) {
                    iss.ignore(); // Ignore the normal index
                }
            }
    }
            face.vertexIndices.push_back(vertexIndices);
            temp_faces.push_back(face);
            //SDL_Log("%d %d %d", face.vertexIndices[0][0], face.vertexIndices[0][1], face.vertexIndices[0][2]);
        }
    }

    out_vertices = temp_vertices;
    out_faces = temp_faces;

    return true;
}

std::vector<glm::vec3> setupVertexArray(const std::vector<glm::vec3>& vertices, const std::vector<Face>& faces)
{
    std::vector<glm::vec3> vertexArray;
    
    // For each face
    for (const auto& face : faces)
    {
        //SDL_Log("For this face: %d %d %d", face.vertexIndices[0][0], face.vertexIndices[0][1], face.vertexIndices[0][2]);
        // For each vertex in the face
        for (const auto& vertexIndex : face.vertexIndices[0])
        {
            // Get the vertex position from the input arrays using the indices from the face
            glm::vec3 vertexPosition = vertices[vertexIndex - 1]; //Restar uno para que los índices empiecen en 0
            //SDL_Log("Vertex position: %f %f %f", vertexPosition.x, vertexPosition.y, vertexPosition.z);

            // Add the vertex position and normal to the vertex array
            vertexArray.push_back(vertexPosition);
        }
    }

    return vertexArray;
}