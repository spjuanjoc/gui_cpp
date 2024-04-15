#include <fmt/core.h>
#include <imgui.h>

#include <iostream>
#include <string>


int main()
{
  std::cout << fmt::format("Hello {}!\n", "world");
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  // Build atlas
  unsigned char* tex_pixels = nullptr;
  std::int32_t   width, height;

  io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &width, &height);

  for (std::size_t n = 0; n < 20; n++)
  {
    std::cout << fmt::format("NewFrame() {:>2}\n", n);
    io.DisplaySize = ImVec2(1920, 1080);
    io.DeltaTime   = 1.0f / 60.0f;
    ImGui::NewFrame();

    static float number = 0.0f;
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &number, 0.0f, 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::ShowDemoWindow(nullptr);

    ImGui::Render();
  }

  std::cout << "DestroyContext()\n";
  ImGui::DestroyContext();

  return 0;
}
