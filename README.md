# abcg2

# Pokémon
## Integrantes:
Isabela Lima Sigaki RA: 11201810447
Júlia Oliveira Costa RA: 11201810014


![build workflow](https://github.com/hbatagelo/abcg/actions/workflows/build.yml/badge.svg)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/hbatagelo/abcg)](https://github.com/hbatagelo/abcg/releases/latest)

Desenvolvimento do Projeto Aquário como atividade para a disciplina [MCTA008-17 Computer Graphics](http://professor.ufabc.edu.br/~harlen.batagelo/cg/) na [UFABC](https://www.ufabc.edu.br/).

[Documentation](https://hbatagelo.github.io/abcg/abcg/doc/html/) | [Release notes](CHANGELOG.md)

O projeto foi criado utilizando o framework ABCg que facilita o desenvolvimento de aplicações baseadas em 
[OpenGL](https://www.opengl.org), [OpenGL ES](https://www.khronos.org), [WebGL](https://www.khronos.org/webgl/), e [Vulkan](https://www.vulkan.org). 

***

## Sobre o projeto

O objetivo é desenvolver uma aplicação que mostre gráficos 3D com primitivas do OpenGL e use transformações geométricas para produzir algum tipo de animação (isto é, a geometria não pode ser estática).

O projeto é uma aplicação usando moldes 3D da animação Pokémon. Foram utilizados como base os projetos "viewer1" que apresenta uma implementação de um visualizador de modelos geométricos 3D que permite a interação através do trackball virtual e o "starfields" que é um campo estelar em perspectiva. O projeto apresenta um Pikachu como objeto principal e no fundo temos um "starfield" de pequenos pikachus. 

## Controles

É possível rotacionar o Pokémon com o botão esquerdo do mouse e o botão scroll do mouse funciona como zoom, onde é possível visualizar o efeito de sombreamento por causa dos shaders. Além disso, no canto inferior direito há um seletor onde o usuário pode selecionar os Pokémons para visualização.

## Alterações realizadas

  - Mescla dos projetos "starfields" e "viewer";
  - Adição dos arquivos trackball.cpp e trackball.hpp no projeto do starfields;
  - Inclusão de um objeto do tipo trackball no window.hpp para que seu conteúdo seja exibido na tela:
    
 ```python
   TrackBall m_trackBall;
 ```

  - Modificação dos arquivos do projeto original para incluir as ações do trackball. Diversas funções foram modificadas nos arquivos .cpp para que a união dos projetos fosse bem sucedida. Funções como por exemplo OnEvent foram incluídas para que as entradas do mouse fossem capturadas:
 ```python
void Window::onEvent(SDL_Event const &event) {
  glm::ivec2 mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  if (event.type == SDL_MOUSEMOTION) {
    m_trackBall.mouseMove(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    m_trackBall.mousePress(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONUP &&
      event.button.button == SDL_BUTTON_LEFT) {
    m_trackBall.mouseRelease(mousePosition);
  }
  if (event.type == SDL_MOUSEWHEEL) {
    m_zoom += (event.wheel.y > 0 ? -1.0f : 1.0f) / 5.0f;
    m_zoom = glm::clamp(m_zoom, -1.5f, 1.0f);
  }
}
```
  - Adição de 4 modelos 3D (arquivos .obj) da temática Pokémon: pokemon_PIKACHU.obj, pokemon_EEVEE.obj, pokemon_EKANS.obj e pokemon_JIGGLYPUFF.obj
  - Declaramos dentro da classe _Window_ do arquivo window.hpp o vetor de chars m_pokemonNames com os nomes dos Pokémons a serem exibidos dentro do seletor:
```python
  const std::vector<const char *> m_pokemonNames{"PIKACHU", "EEVEE", "EKANS", "JIGGLYPUFF"};
```
  - Para realizar a troca da cor dos objetos principal e secundário com base na seleção do usuário, adicionamos na função _onPaintUI()_ do arquivo window.cpp dois IFs para checar qual Pokémon está selecionado no momento e atualizar o arquivo .obj que está sendo utilizado para a visualização:
    
```python
static std::size_t currentIndex{};

    ImGui::PushItemWidth(120);
    if (ImGui::BeginCombo("Pokemon", m_pokemonNames.at(currentIndex))) {
      for (auto index : iter::range(m_pokemonNames.size())) {
        const bool isSelected{currentIndex == index};
        if (ImGui::Selectable(m_pokemonNames.at(index), isSelected))
          currentIndex = index;
        if (isSelected) ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }
    ImGui::PopItemWidth();

    if (static_cast<int>(currentIndex) != m_currentPokemonIndex) {
      m_currentPokemonIndex = currentIndex;

      m_model.loadFromFile(fmt::format("{}pokemon_{}.obj", assetsPath, m_pokemonNames.at(m_currentPokemonIndex)));
      m_model.setupVAO(m_program);
      m_trianglesToDraw = m_model.getNumTriangles();
    }
```
- Para trocar a cor com base no objeto selecionado pelo usuário, incluímos na função _onPaint()_ do window.cpp as seguintes cláusulas IFs:
  
```python
  if (m_currentPokemonIndex == 0) {
    abcg::glUniform4f(colorLoc, 1.0f, 0.843137255f, 0.0f, 1.0f); // Yellow
  } 
  if (m_currentPokemonIndex == 1) {
    abcg::glUniform4f(colorLoc, 0.62745098f, 0.321568627f, 0.176470588f, 1.0f); // Brown
  } 
  if (m_currentPokemonIndex == 2) {
    abcg::glUniform4f(colorLoc, 0.541176471f, 0.168627451f, 0.88627451f, 1.0f); // Purple
  } 
  if (m_currentPokemonIndex == 3) {
    abcg::glUniform4f(colorLoc, 1.0f, 0.752941176f, 0.796078431f, 1.0f); // PINK
  } 

```

## Otimizações feitas

Ao baixarmos os obj da internet, os arquivos apresentavam cerca de 500 mil triângulos, e inserindo 4 pokémons, a visualização tornava-se lenta. Para otimizar esse processo, utilizamos a ferramenta "Blender" para torná-las menores, reduzindo assim seu tamanho para cerca de 5 mil triângulos, uma redução de 99%. Assim a sua visualização ficou muito mais rápida.


