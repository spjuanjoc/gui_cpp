#include "ImguiSFML/imgui-SFML.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <fmt/core.h>
#include <imgui.h>

int main()
{
  sf::RenderWindow main_window(sf::VideoMode(1240, 480), "Imgui SFML");
  const bool       isInit = ImGui::SFML::Init(main_window);
  sf::CircleShape  shape(100.f);
  sf::Clock        deltaClock;

  main_window.setFramerateLimit(30);
  shape.setFillColor(sf::Color::Green);
  ImGui::GetStyle().ScaleAllSizes(2.0);
  ImGui::GetIO().FontGlobalScale = 2.0;

  while (main_window.isOpen() && isInit)
  {
    sf::Event event{};

    while (main_window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(main_window, event);

      if (event.type == sf::Event::Closed)
      {
        main_window.close();
      }
    }
    ImGui::SFML::Update(main_window, deltaClock.restart());
    main_window.clear();

    ImGui::ShowDemoWindow();

    ImGui::Begin("Window 1");
    {
      ImGui::TextUnformatted("Hello, world!");
    }
    ImGui::End();

    ImGui::Begin("Button window");
    {
      ImGui::Button("Look at this pretty button");
      main_window.draw(shape);
    }
    ImGui::End();

    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
