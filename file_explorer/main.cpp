#include <imgui.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <portable-file-dialogs.h>
#include <fmt/format.h>

void runProcess()
{
  ImGui::TextUnformatted("Running some process");
}

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

void pollMainWindow(sf::RenderWindow& main_window)
{
  while (auto event = main_window.pollEvent())
  {
    ImGui::SFML::ProcessEvent(main_window, *event);

    if (event->is<sf::Event::Closed>())
    {
      main_window.close();
    }
  }
}

void
doWork(std::string& value, bool& is_running)
{
  if (ImGui::Button("Select a file"))
  {
    value = openFileDialog();
  }

  ImGui::SameLine();
  ImGui::TextUnformatted(fmt::format("{}", value).c_str());

  if (!value.empty() && value != "empty")
  {
    if (ImGui::Button("Run"))
    {
      is_running = true;
    }

    if (is_running)
    {
      ImGui::SameLine();
      runProcess();
    }
  }
}

void
runMainLoop(sf::RenderWindow& main_window)
{
  sf::Clock delta_clock;
  std::string value = "empty";
  bool is_running = false;

  while (main_window.isOpen())
  {
    pollMainWindow(main_window);
    ImGui::SFML::Update(main_window, delta_clock.restart());

    doWork(value, is_running);

    main_window.clear();
    ImGui::SFML::Render(main_window);
    main_window.display();
  }
}

int main()
{
  sf::RenderWindow main_window(sf::VideoMode({1200, 230}), "ImGui - Window");
  main_window.setFramerateLimit(60);

  [[maybe_unused]]
  bool isLoaded = ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(2.0f);
  ImGui::GetIO().FontGlobalScale = 2.0f;

  runMainLoop(main_window);

  ImGui::SFML::Shutdown();

  return 0;
}
