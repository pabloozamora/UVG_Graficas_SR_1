#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <array>

struct Face {
    std::vector<std::array<int, 3>> vertexIndices;
};

bool loadOBJ(const std::string& path, std::vector<glm::vec3>& out_vertices, std::vector<Face>& out_faces) {
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
            temp_vertices.push_back(vertex);
        } else if (type == "f") {  // Face
            Face face;
            std::array<int, 3> vertexIndices;
            for (int i = 0; i < 3; ++i) {
                char slash;
                iss >> vertexIndices[i] >> slash >> slash >> vertexIndices[i];
            }
            face.vertexIndices.push_back(vertexIndices);
            temp_faces.push_back(face);
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
        // For each vertex in the face
        for (const auto& vertexIndices : face.vertexIndices)
        {
            // Get the vertex position and normal from the input arrays using the indices from the face
            glm::vec3 vertexPosition = vertices[vertexIndices[0]];

            // Add the vertex position and normal to the vertex array
            vertexArray.push_back(vertexPosition);
        }
    }

    return vertexArray;
}