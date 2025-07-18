from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("fmt/11.2.0")
        self.requires("imgui-sfml/2.6.1")
        self.requires("opencv/4.11.0")
        self.requires("flac/1.4.2", override=True)

    def layout(self):
        cmake_layout(self)
