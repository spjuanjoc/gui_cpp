#include <fmt/core.h>

#include <imgui.h>
#include <string>

#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

sf::Image
cvMat2sfImage(const cv::Mat& cv_mat)
{
  sf::Image sf_image;
  cv::Mat   cv_image_alpha;

  cv::cvtColor(cv_mat, cv_image_alpha, cv::COLOR_BGR2RGBA);
  sf_image.create(cv_image_alpha.cols, cv_image_alpha.rows, cv_image_alpha.ptr());

  return sf_image;
}

cv::Mat
sfImage2cvMat(const sf::Image& sf_image)
{
  sf::Image image { sf_image };
  cv::Size  size(image.getSize().x, image.getSize().y);
  cv::Mat   cv_mat(size, CV_8UC4, (void*) image.getPixelsPtr(), cv::Mat::AUTO_STEP);

  cv::cvtColor(cv_mat, cv_mat, cv::COLOR_RGBA2BGRA);

  return cv_mat.clone();
}

cv::Mat
applyMedianFilter(const cv::Mat& image)
{
  int     kernel_size = 5;
  cv::Mat filter_image;

  cv::medianBlur(image, filter_image, kernel_size);

  return filter_image;
}

int
main()
{
  cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
  fmt::println("Hello world for ImGui '{}' with OpenCV '{}'", IMGUI_VERSION, CV_VERSION);

  sf::RenderWindow main_window(sf::VideoMode(512 * 2, 512), "Imgui SFML");
  const bool       isInit = ImGui::SFML::Init(main_window);
  sf::Clock        deltaClock;
  std::string      filename  = "share/images/lena.bmp";
  cv::Mat          cv_image  = cv::imread(filename, cv::IMREAD_UNCHANGED);
  sf::Image        image_src = cvMat2sfImage(cv_image);
  sf::Texture      texture_src;
  sf::Sprite       sprite_src;
  sf::Texture      texture_dst;
  sf::Sprite       sprite_dst;

  main_window.setFramerateLimit(60);

  cv::Mat   mat       = sfImage2cvMat(image_src);
  sf::Image image_dst = cvMat2sfImage(applyMedianFilter(mat));

  texture_src.loadFromImage(image_src);

  texture_dst.loadFromImage(image_dst);
  sprite_src.setTexture(texture_src);
  sprite_dst.setTexture(texture_dst);
  sprite_dst.setPosition(sprite_dst.getPosition().x + texture_dst.getSize().x, sprite_dst.getPosition().y);
  fmt::println("Position src ({},{})", sprite_src.getPosition().x, sprite_src.getPosition().y);
  fmt::println("Position dst ({},{})", sprite_dst.getPosition().x, sprite_dst.getPosition().y);

  while (main_window.isOpen() && isInit)
  {
    sf::Event event {};
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

    main_window.draw(sprite_src);
    main_window.draw(sprite_dst);
    //    ImGui::Begin("Window 1");
    //    {
    //    }
    //    ImGui::End();

    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
