#ifndef GTKMM_TODOWINDOW_H
#define GTKMM_TODOWINDOW_H

#include <gtkmm.h>

class TodoWindow : public Gtk::Window
{
public:
	TodoWindow();
	virtual ~TodoWindow();

protected:

	// file io funcs
	void get_list_from_file();
	void write_back_to_file();

	bool on_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);

	bool update_timer();

	Gtk::Box m_VBox;

	Gtk::ScrolledWindow m_ScrolledWindow;
	Gtk::TextView m_TextView;

	Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
};

#endif //GTKMM_TODOWINDOW_H