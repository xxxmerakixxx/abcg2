#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string_view>
#include "abcgOpenGL.hpp"

struct Vertex {
  glm::vec3 position{};

  bool operator==(const Vertex& other) const noexcept {
    static const auto epsilon{std::numeric_limits<float>::epsilon()};
    return glm::all(glm::epsilonEqual(position, other.position, epsilon));     
  }
};

class Model {
public:
  Model() = default;
  virtual ~Model();

  Model(const Model&) = delete;
  Model(Model&&) = default;
  void loadObj(std::string_view path, bool standardize = true);
  Model& operator=(const Model&) = delete;
  Model& operator=(Model&&) = default;
  void loadFromFile(std::string_view path, bool standardize = true);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);
//void destroy() const;

  [[nodiscard]] int getNumTriangles() const {
    return static_cast<int>(m_indices.size()) / 3;
  }

private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  void createBuffers();
  void standardize();
};

#endif