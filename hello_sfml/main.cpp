#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

void pollMainWindow(sf::RenderWindow& main_window, sf::Event& event)
{
  while (main_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      main_window.close();
    }
  }
}

void drawText(sf::RenderWindow& window, const std::string& text)
{
  sf::Font font;

  if (!font.loadFromFile("share/calibri-font-family/calibri-regular.ttf"))
  {
    std::cerr << "Cannot load font file\n";
  }

  sf::Text text_drawable;
  text_drawable.setFont(font);
  text_drawable.setString(text);
  text_drawable.setCharacterSize(96);
  text_drawable.setFillColor(sf::Color::White);
//  text_drawable.setStyle(sf::Text::Bold | sf::Text::Underlined);
  window.draw(text_drawable);
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
  main_window.setVerticalSyncEnabled(true);

  while (main_window.isOpen())
  {
    sf::Event event{};
    pollMainWindow(main_window, event);
    main_window.clear();
    drawText(main_window, "Hello world");
    main_window.display();
  }

  return 0;
}
