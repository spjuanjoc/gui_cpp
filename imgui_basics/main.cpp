#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <fmt/format.h>
#include <imgui-SFML.h>
#include <imgui.h>

constexpr auto font_filename = "share/calibri-font-family/calibri-regular.ttf";
constexpr auto font_size = 22.0f;

template<typename std::size_t SIZE>
void renderCheckbox(const std::string& label, std::array<const char*, SIZE> options, std::array<bool, SIZE>& states)
{
  ImGui::Begin(label.c_str());
  std::size_t index = 0;

  for (const auto& item : options)
  {
    ImGui::Checkbox(fmt::format("{} : {}", index + 1, item).c_str(), &states.at(index));
    ++index;
  }

  ImGui::End();
}

std::uint8_t validateColor(float& value)
{
  constexpr auto max_color = 255.0f;

  value = value > 1.0f ? 1.0f : value;
  value = value < 0.0f ? 0.0f : value;

  return static_cast<std::uint8_t>(value * max_color);
}

sf::Color& getColor(const std::string& label,
                    sf::RenderWindow&  main_window,
                    sf::Color&         background_color,
                    float              color[],
                    std::string&       colors)
{
  ImGui::Begin(label.c_str());

  if (ImGui::ColorEdit3("Color", color))
  {
    colors = fmt::format("{}, {}, {}", color[0], color[1], color[2]);

    background_color.r = validateColor(color[0]);
    background_color.g = validateColor(color[1]);
    background_color.b = validateColor(color[2]);
  }

  ImGui::InputText("Values", colors.data(), colors.size());
  ImGui::End();

  return background_color;
}

static void changeTitle(const std::string& label, sf::RenderWindow& main_window, std::string& window_title)
{
  constexpr auto max_size = 255;
  ImGui::Begin(label.c_str());
  ImGui::InputText("Label", window_title.data(), max_size);

  if (ImGui::Button("Update"))
  {
    main_window.setTitle(window_title);
  }

  ImGui::End();
}

static void addTextBox(const std::string& label, const std::string& data)
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

static void ShowExampleAppSimpleOverlay(bool* p_open)
{
  static int       corner       = 0;
  ImGuiIO&         io           = ImGui::GetIO();
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize
                                  | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing
                                  | ImGuiWindowFlags_NoNav;
  if (corner != -1)
  {
    const float          PAD       = 10.0f;
    const ImGuiViewport* viewport  = ImGui::GetMainViewport();
    ImVec2               work_pos  = viewport->WorkPos;  // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2               work_size = viewport->WorkSize;
    ImVec2               window_pos, window_pos_pivot;
    window_pos.x       = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
    window_pos.y       = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
    window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
    window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    window_flags |= ImGuiWindowFlags_NoMove;
  }

  ImGui::SetNextWindowBgAlpha(0.35f);  // Transparent background

  if (ImGui::Begin("Example: Simple overlay", p_open, window_flags))
  {
    ImGui::Text("Simple overlay\n"
      "in the corner of the screen.\n"
      "(right-click to change position)");

    ImGui::Separator();

    if (ImGui::IsMousePosValid())
      ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
    else
      ImGui::Text("Mouse Position: <invalid>");

    if (ImGui::BeginPopupContextWindow())
    {
      if (ImGui::MenuItem("Custom", nullptr, corner == -1))
        corner = -1;
      if (ImGui::MenuItem("Top-left", nullptr, corner == 0))
        corner = 0;
      if (ImGui::MenuItem("Top-right", nullptr, corner == 1))
        corner = 1;
      if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2))
        corner = 2;
      if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3))
        corner = 3;
      if (p_open && ImGui::MenuItem("Close"))
        *p_open = false;
      ImGui::EndPopup();
    }
  }

  ImGui::End();
}

static void addOverlayBox(const std::string& label, const std::string& data)
{
  ImVec2         window_pos{0,0};
  constexpr auto transparency = 0.25f;
  ImGuiIO&         io           = ImGui::GetIO();
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize
                                  | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing
                                  | ImGuiWindowFlags_NoNav;

  ImGui::SetNextWindowBgAlpha(transparency);  // Transparent background
  ImGui::SetNextWindowPos(window_pos, ImGuiCond_FirstUseEver);

  if (ImGui::Begin(label.c_str(), nullptr, window_flags))
  {
    ImGui::TextUnformatted(data.c_str());
  }

  ImGui::End();
}

int main()
{
  const auto  width        = 800;
  const auto  height       = 600;
  const auto  frame_rate   = 30;
  const auto  scale        = 1.75f;
  std::string window_title = "Hello ImGUI SFML";
  sf::Clock   delta_clock;
  float       color[3] = {0.0f, 0.0f, 0.0f};
  sf::Color   background_color;
  std::string colors = "0, 0, 0";

  constexpr std::array             options{"Option1", "Option2", "Option3"};
  std::array<bool, options.size()> states{};

  sf::RenderWindow main_window(sf::VideoMode(width, height), "");

  ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(scale);
  ImGuiIO& io = ImGui::GetIO();
  bool pipe = false;

  io.Fonts->Clear();
  io.Fonts->AddFontFromFileTTF(font_filename, font_size);
  ImGui::SFML::UpdateFontTexture();
  //  ImGui::GetIO().FontGlobalScale = scale;
  //  main_window.resetGLStates();

  main_window.setFramerateLimit(frame_rate);
  main_window.setVerticalSyncEnabled(true);
  main_window.setTitle(window_title);

  while (main_window.isOpen())
  {
    sf::Event event{};
    pollMainWindow(main_window, event);
    ImGui::SFML::Update(main_window, delta_clock.restart());

    // Box 1
    changeTitle("Update title", main_window, window_title);

    // Box 2
    background_color = getColor("Background", main_window, background_color, color, colors);

    // Box 3
    addTextBox("Box1", "some other text");

    // Box 4
    renderCheckbox<options.size()>("Checkbox1", options, states);

    // Box 5
    addOverlayBox("Overlay 1", "Some text in\nan overlay box");

    ShowExampleAppSimpleOverlay(&pipe);

    main_window.clear(background_color);
    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();
}
