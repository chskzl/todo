#ifndef GTKMM_TODOWINDOW_H
#define GTKMM_TODOWINDOW_H

#include <gtkmm.h>
#include <fstream>

class TodoWindow : public Gtk::Window
{
public:
	TodoWindow(std::string file_path, std::string style_path);
	virtual ~TodoWindow();

protected:

	// file io funcs
	void get_list_from_file();
	bool write_back_to_file();

	bool on_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);

	Gtk::Box m_VBox;

	Gtk::ScrolledWindow m_ScrolledWindow;
	Gtk::TextView m_TextView;

	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

	std::string file_path;
	std::string style_path;
};

#endif //GTKMM_TODOWINDOW_H