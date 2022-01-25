#include "todowindow.h"
#include <gtkmm/application.h>
#include <iostream>


std::string file_path;
std::string style_path;


int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line,
                    Glib::RefPtr<Gtk::Application>& app)
{
	int argc = 0;
	char** argv = command_line->get_arguments(argc);

	app->activate(); // Without activate() the window won't be shown.
	return EXIT_SUCCESS;
}


int main(int argc, char* argv[])
{

	auto app = Gtk::Application::create(
		"org.gtkmm.example", Gio::Application::Flags::HANDLES_COMMAND_LINE);

	app->signal_command_line().connect(sigc::bind(sigc::ptr_fun(&on_command_line), app), false);

	int opt = 0;
	while ((opt = getopt(argc, argv, "hs:f:")) != -1) {
		switch(opt) {
			case 'h':
				printf("%s [-h] [-s style_path] [-f file_path]\n", argv[0]);
				return 0;
				break;
			case 's':
				style_path = optarg;
				break;
			case 'f':
				file_path = optarg;
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}

	return app->make_window_and_run<TodoWindow>(argc, argv, file_path, style_path);
}