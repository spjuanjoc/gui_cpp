# Hello ImGui with OpenCV

This is a "Hello World" for ImGUI using OpenCV 4.5 in Ubuntu Jammy 20.04, with
SFML as back-end.

Steps:
  - Init
  - Load the cv::image (cv::Mat)
  - Add alpha channel
  - Create a sf::image from the cv::image
  - Create a sf::Texture from the image
  - Add the texture to a sf::Sprite
  - Draw the sprite
