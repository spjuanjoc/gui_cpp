#include "ImguiSFML/imgui-SFML.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <fmt/core.h>
#include <imgui.h>

int main()
{
  sf::RenderWindow main_window(sf::VideoMode(1240, 480), "Imgui SFML");
  const bool       isInit = ImGui::SFML::Init(main_window);
  sf::CircleShape  shape(100.f);
  sf::Clock        deltaClock;
  sf::Texture texture;
  texture.loadFromFile("share/textures/gameover.png");

  main_window.setFramerateLimit(30);
  shape.setFillColor(sf::Color::Green);
  ImGui::GetStyle().ScaleAllSizes(2.0);
  ImGui::GetIO().FontGlobalScale = 2.0;

  while (main_window.isOpen() && isInit)
  {
    sf::Event event{};
    ImGui::SFML::SetCurrentWindow(main_window);

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

    ImGui::ShowMetricsWindow();
    ImGui::ShowDemoWindow();


    ImGui::Begin("Window 1");
    {
      // we access the ImGui window size
      const float window_width = ImGui::GetContentRegionAvail().x;
      const float window_height = ImGui::GetContentRegionAvail().y;
      ImVec2 position = ImGui::GetCursorScreenPos();

      ImGui::GetWindowDrawList()->AddImage(static_cast<void*>(&texture),
                                           position,
                                           {position.x + window_width, position.y + window_height},
                                           {0,1},
                                           {1,0});
      ImGui::TextUnformatted("Hello, world!");
    }
//    ImGui::SFML::Render(main_window);
    ImGui::End();

    ImGui::Begin("Button window");
    {
      ImGui::Button("Look at this pretty button");
    }
    ImGui::End();

    main_window.draw(shape);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    main_window.draw(sprite);

    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
