#include <imgui.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <portable-file-dialogs.h>
#include <fmt/format.h>

std::string openFileDialog()
{
  const auto selection = pfd::open_file("Select a file").result();
  std::string file_path;

  if (!selection.empty())
  {
    std::cout << "User selected file " << selection[0] << "\n";
    file_path = selection[0];
  }

  return file_path;
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
  sf::RenderWindow main_window(sf::VideoMode(640, 480), "ImGui - Window");
  main_window.setFramerateLimit(60);
  sf::Clock delta_clock{};

  [[maybe_unused]]
  bool isLoaded = ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(2.0f);
  ImGui::GetIO().FontGlobalScale = 2.0f;
  std::string value = "empty";

  while (main_window.isOpen())
  {
    sf::Event event{};
    pollMainWindow(main_window, event);
    ImGui::SFML::Update(main_window, delta_clock.restart());

    ImGui::TextUnformatted(fmt::format("File: ({})", value).c_str());

    if (ImGui::Button("Some Button"))
    {
      value = openFileDialog();
    }

    main_window.clear();
    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
