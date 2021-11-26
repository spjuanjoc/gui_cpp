#include <gtk/gtk.h>


static void print_hello(GtkWidget* widget, gpointer data)
{
  g_print("Hello World\n");
}

static void activate(GtkApplication* app, gpointer user_data)
{
  GtkWidget* window;
  GtkWidget* button;
  constexpr auto window_title  = "Window1";
  constexpr auto button_label  = "Button1";
  constexpr auto signal_clicked  = "clicked";
  constexpr auto window_width  = 200;
  constexpr auto window_height = 200;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), window_title);
  gtk_window_set_default_size(GTK_WINDOW(window), window_width, window_height);

  button = gtk_button_new_with_label(button_label);
  g_signal_connect(button, signal_clicked, G_CALLBACK(print_hello), nullptr);
  gtk_window_set_child(GTK_WINDOW(window), button);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char** argv)
{
  GtkApplication* app;
  int             status;
  constexpr auto application_id = "org.gtk.example";
  constexpr auto detailed_signal = "activate";

  app = gtk_application_new(application_id, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, detailed_signal, G_CALLBACK(activate), nullptr);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
