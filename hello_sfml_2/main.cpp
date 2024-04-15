#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <filesystem>
#include <iostream>
#include <string>

sf::Font loadFonts()
{
  sf::Font       font;
  constexpr auto FONT_FILENAME = "share/fonts/calibri-regular.ttf";

  try
  {
    if (std::filesystem::exists(FONT_FILENAME))
    {
      if (!font.loadFromFile(FONT_FILENAME))
      {
        std::cerr << "Cannot load font file\n";
      }
      else
      {
        std::cout << "Successfully loaded the font " << FONT_FILENAME << '\n';
      }
    }
    else
    {
      std::cerr << "The fonts file '" << FONT_FILENAME << "' does not exist. Using the default font.\n";
    }
  }
  catch (const std::exception& exception)
  {
    std::cerr << "The fonts could not be loaded. " << exception.what() << '\n';
  }
  catch (...)
  {
    std::cerr << "The fonts could not be loaded.\n";
  }

  return font;
}

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

void drawText(sf::RenderWindow& window, const sf::Font& font, const std::string& text)
{
  sf::Text text_drawable;

  text_drawable.setFont(font);
  text_drawable.setString(text);
  text_drawable.setCharacterSize(48);
  text_drawable.setFillColor(sf::Color::White);
  text_drawable.setStyle(sf::Text::Bold | sf::Text::Underlined);
  window.draw(text_drawable);
}


int main()
{
  constexpr auto width        = 640;
  constexpr auto height       = 480;
  constexpr auto frame_rate   = 30;
  constexpr auto window_title = "Hello SFML";
  const sf::Font font         = loadFonts();

  sf::RenderWindow main_window(sf::VideoMode(width, height), window_title);

  main_window.setFramerateLimit(frame_rate);
  main_window.setVerticalSyncEnabled(true);

  while (main_window.isOpen())
  {
    sf::Event event{};
    pollMainWindow(main_window, event);
    main_window.clear();
    drawText(main_window, font, "Hello world in SFML");
    main_window.display();
  }

  return 0;
}
