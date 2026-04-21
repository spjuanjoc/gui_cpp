#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>
#include <string>

GLuint texture_id;

void rescale_framebuffer(float width, float height);
void create_triangle();

static void glfw_error_callback(int error, const char* description)
{
  std::cerr << "GLFW Error\n" << error << ": " << description;
}

void drawSomething()
{
  const float window_width  = ImGui::GetContentRegionAvail().x;
  const float window_height = ImGui::GetContentRegionAvail().y;

//  rescale_framebuffer(window_width, window_height);
  glViewport(0, 0, window_width, window_height);

  ImVec2 pos = ImGui::GetCursorScreenPos();

  ImGui::GetWindowDrawList()->AddImage((void*) texture_id,
                                       ImVec2(pos.x, pos.y),
                                       ImVec2(pos.x + window_width, pos.y + window_height),
                                       ImVec2(0, 1),
                                       ImVec2(1, 0));
}

// Main code
int main(int, char**)
{
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create window with graphics context
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);

  if (window == nullptr)
    return 1;

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);  // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void) io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);

  ImGui_ImplOpenGL3_Init(glsl_version);

  bool   show_demo_window    = true;
  bool   show_another_window = false;
  ImVec4 clear_color         = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  create_triangle();


  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    /*{
      static float f       = 0.0f;
      static int   counter = 0;

      ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");           // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window);  // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);              // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*) &clear_color);  // Edit 3 floats representing a color

      if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
    }*/
    drawSomething();
    // 3. Show another simple window.
    /*if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);
      {
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
          show_another_window = false;
      }
      ImGui::End();
    }*/

    // Rendering
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>
#include <string>

const GLint WIDTH  = 800;
const GLint HEIGHT = 600;

GLuint VAO;
GLuint VBO;
GLuint FBO;
GLuint RBO;
//GLuint texture_id;
GLuint shader;

const char* vertex_shader_code = R"*(
#version 330

layout (location = 0) in vec3 pos;

void main()
{
  gl_Position = vec4(0.9*pos.x, 0.9*pos.y, 0.5*pos.z, 1.0);
}
)*";

const char* fragment_shader_code = R"*(
#version 330

out vec4 color;

void main()
{
  color = vec4(0.0, 1.0, 0.0, 1.0);
}
)*";


void create_triangle()
{
  GLfloat vertices[] = {
    -1.0f,
    -1.0f,
    0.0f,  // 1. vertex x, y, z
    1.0f,
    -1.0f,
    0.0f,  // 2. vertex ...
    0.0f,
    1.0f,
    0.0f  // etc...
  };

//  glGenVertexArrays(1, &VAO);
//  glBindVertexArray(VAO);
//
//  glGenBuffers(1, &VBO);
//  glBindBuffer(GL_ARRAY_BUFFER, VBO);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//  glEnableVertexAttribArray(0);
//
//  glBindBuffer(GL_ARRAY_BUFFER, 0);
//  glBindVertexArray(0);
}

void add_shader(GLuint program, const char* shader_code, GLenum type)
{
  GLuint current_shader = glCreateShader(type);

  const GLchar* code[1];
  code[0] = shader_code;

  GLint code_length[1];
  code_length[0] = strlen(shader_code);

  glShaderSource(current_shader, 1, code, code_length);
  glCompileShader(current_shader);

  GLint  result    = 0;
  GLchar log[1024] = {0};

  glGetShaderiv(current_shader, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    glGetShaderInfoLog(current_shader, sizeof(log), NULL, log);
    std::cout << "Error compiling " << type << " shader: " << log << "\n";
    return;
  }

  glAttachShader(program, current_shader);
}

void create_shaders()
{
  shader = glCreateProgram();
  if (!shader)
  {
    std::cout << "Error creating shader program!\n";
    exit(1);
  }

  add_shader(shader, vertex_shader_code, GL_VERTEX_SHADER);
  add_shader(shader, fragment_shader_code, GL_FRAGMENT_SHADER);

  GLint  result    = 0;
  GLchar log[1024] = {0};

  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shader, sizeof(log), NULL, log);
    std::cout << "Error linking program:\n" << log << '\n';
    return;
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(shader, sizeof(log), NULL, log);
    std::cout << "Error validating program:\n" << log << '\n';
    return;
  }
}

void create_framebuffer()
{
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void bind_framebuffer()
{
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void unbind_framebuffer()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void rescale_framebuffer(float width, float height)
{
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

int main2()
{
  if (!glfwInit())
  {
    std::cerr << "GLFW initialisation failed!\n";
    glfwTerminate();
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create the window
  GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "My Window", nullptr, nullptr);

  if (!mainWindow)
  {
    std::cerr << "GLFW creation failed!\n";
    glfwTerminate();
    return 1;
  }

  int bufferWidth, bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
  glfwMakeContextCurrent(mainWindow);
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "glew initialisation failed!\n";
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  glViewport(0, 0, bufferWidth, bufferHeight);

  create_triangle();
  create_shaders();
  create_framebuffer();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
//  ImGuiIO& io = ImGui::GetIO();
//  (void) io;
//  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();
//  ImGuiStyle& style = ImGui::GetStyle();
//  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//  {
//    style.WindowRounding              = 0.0f;
//    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//  }

  ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
  ImGui_ImplOpenGL3_Init("#version 330");


  while (!glfwWindowShouldClose(mainWindow))
  {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::NewFrame();
    ImGui::Begin("My Scene");

    const float window_width  = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;

//    rescale_framebuffer(window_width, window_height);
    glViewport(0, 0, window_width, window_height);

    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage((void*) texture_id,
                                         ImVec2(pos.x, pos.y),
                                         ImVec2(pos.x + window_width, pos.y + window_height),
                                         ImVec2(0, 1),
                                         ImVec2(1, 0));

    ImGui::End();
    ImGui::Render();


    bind_framebuffer();

    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);

    unbind_framebuffer();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//      GLFWwindow* backup_current_context = glfwGetCurrentContext();
//      ImGui::UpdatePlatformWindows();
//      ImGui::RenderPlatformWindowsDefault();
//      glfwMakeContextCurrent(backup_current_context);
//    }

    glfwSwapBuffers(mainWindow);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glDeleteFramebuffers(1, &FBO);
  glDeleteTextures(1, &texture_id);
  glDeleteRenderbuffers(1, &RBO);

  glfwDestroyWindow(mainWindow);
  glfwTerminate();

  return 0;
}
