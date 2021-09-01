#include <fmt/core.h>
#include <gtk/gtk.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <glibmm/ustring.h>

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  //    ^^^^^^^^^^^^^^^^^^^ <- add something like this (see below)
//  Gtk::Button *button = new Gtk::Button("Quit");
//  button->signal_clicked().connect(sigc::ptr_fun(Gtk::Main::quit));
//  Gtk::Window window;
//  window.set_default_size(200, 200);
//  window.add(*button);
//  button->show();
//  return app->run(window);
  return 0;
}
