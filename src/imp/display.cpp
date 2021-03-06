#include "raiGraphics/imp/display.h"
#include <GL/glew.h>
#include <iostream>
#include "raiCommon/rai_utils.hpp"

namespace rai_graphics {
Display::Display(int width, int height, const std::string &title) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

//     TODO what would be proper version? (>= 4.0?)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  m_window =
      SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_OPENGL);
  RAIFATAL_IF(m_window ==NULL, SDL_GetError());
  m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_SOFTWARE);
  RAIFATAL_IF(m_renderer ==NULL, SDL_GetError());
//
  m_glContext = SDL_GL_CreateContext(m_window);
  RAIFATAL_IF(m_glContext ==NULL, SDL_GetError());

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glewExperimental = GL_TRUE;
  GLenum res = glewInit();
  RAIFATAL_IF(res != GLEW_OK, "Glew failed to initialize!" << " Error: "<<glewGetErrorString(res));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_TEXTURE_2D);
}

Display::~Display() {
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(r, g, b, a);
}

void Display::SwapBuffers() {
  SDL_GL_SwapWindow(m_window);
}

void Display::HideWindow() {
  SDL_HideWindow(m_window);
}

void Display::ShowWindow() {
  SDL_ShowWindow(m_window);
}

} // rai_graphics