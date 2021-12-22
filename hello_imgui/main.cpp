#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

void pollMainWindow(sf::RenderWindow& main_window, sf::Event& event)
{
  while (main_window.pollEvent(event))
  {
    ImGui::SFML::ProcessEvent(event);

    if (event.type == sf::Event::Closed)
    {
      main_window.close();
    }
  }
}

int main()
{
  sf::RenderWindow main_window(sf::VideoMode(640, 480), "ImGui - Window");
  main_window.setFramerateLimit(60);
  sf::Clock delta_clock{};

  ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(2.0f);
  ImGui::GetIO().FontGlobalScale = 2.0f;

  while (main_window.isOpen())
  {
    sf::Event event{};
    pollMainWindow(main_window, event);
    ImGui::SFML::Update(main_window, delta_clock.restart());

    ImGui::Begin("Box1");
    ImGui::TextUnformatted("Hello world from ImGUI + SFML");
    ImGui::End();

    main_window.clear();
    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();
}
