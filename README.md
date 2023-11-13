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

É possível rotacionar o Pokémon com o botão esquerdo do mouse e o botão scroll do mouse funciona como zoom. Além disso, no canto inferior direito há um seletor onde o usuário pode selecionar os Pokémons para visualização.

## Alterações realizadas

1. Mescla dos projetos:
  - Adição dos arquivos trackball.cpp e trackball.hpp no projeto do starfields;
  - Inclusão de um objeto do tipo trackball no window.hpp para que seu conteúdo seja exibido na tela
    
 ```python
   TrackBall m_trackBall;
 ```

  - Modificação dos arquivos do projeto original para incluir as ações do trackball. Diversas funções foram modificadas nos arquivos .cpp para que a união dos projetos fosse bem sucedida. Funções como por exemplo OnEvent foram incluídas para que as entradas do mouse fossem capturadas. 
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
  - Adição dos modelos 3D (arquivos .obj) da temática Pokémon
```python
loadModel(getAssetsPath() + "pikachu.obj");
```

  - Troca da cor do objeto principal e secundários
```python
abcg::glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
```

## Otimizações feitas

Ao baixarmos os obj da internet, os arquivos apresentavam cerca de 500 mil triângulos, e inserindo 4 pokémons, a visualização tornava-se lenta. Para otimizar esse processo, utilizamos a ferramenta "Blender" para torná-las menores, reduzindo assim seu tamanho para cerca de 5 mil triângulos, uma redução de 99%. Assim a sua visualização ficou muito melhor.


