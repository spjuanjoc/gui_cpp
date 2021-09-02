#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

void addTextBox(const std::string& label, const std::string& data)
{
  ImGui::Begin(label.c_str());
  ImGui::TextUnformatted(data.c_str());
  ImGui::End();
}

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
  constexpr auto width        = 640;
  constexpr auto height       = 480;
  constexpr auto frame_rate   = 30;
  constexpr auto scale        = 2.0f;
  constexpr auto window_title = "Window 1";
  sf::Clock      delta_clock{};

  sf::RenderWindow main_window(sf::VideoMode(width, height), window_title);
  main_window.setFramerateLimit(frame_rate);

  ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(scale);
  ImGui::GetIO().FontGlobalScale = scale;

  main_window.setVerticalSyncEnabled(true);
  //  main_window.setTitle(window_title);

  while (main_window.isOpen())
  {
    sf::Event event{};
    pollMainWindow(main_window, event);
    ImGui::SFML::Update(main_window, delta_clock.restart());

    addTextBox("Box1", "Hello world from ImGUI + SFML");
    addTextBox("Box2", "Hello world from ImGUI + SFML 2");

    main_window.clear();
    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();
}
