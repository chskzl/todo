#include "todowindow.h"
#include <iostream>
#include <fstream>
#include <string>

TodoWindow::TodoWindow() : m_VBox(Gtk::Orientation::VERTICAL)
{
	set_title("ToDo");
	set_default_size(300, 500);

	set_child(m_VBox);

	m_ScrolledWindow.set_child(m_TextView);

	// only show scrollbar when necessary
	m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
	m_ScrolledWindow.set_expand();

	m_VBox.append(m_ScrolledWindow);

	// read file into todo list
	get_list_from_file();
	m_TextView.set_buffer(m_refTextBuffer);

	// event handler
	auto controller = Gtk::EventControllerKey::create();
	controller->signal_key_pressed().connect(
		sigc::mem_fun(*this, &TodoWindow::on_window_key_pressed), false);
	add_controller(controller);

	// idle func
	Glib::signal_timeout().connect( sigc::mem_fun(*this, &TodoWindow::update_timer), 1000 );

	// create css provider
	auto css = Gtk::CssProvider::create();
	css->load_from_path("style.css");
	get_style_context()->add_provider_for_display(Gdk::Display::get_default(), 
	                                             css, 
	                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	
	// css classes
	get_style_context()->add_class("mainwin");
	m_VBox.get_style_context()->add_class("vb");
	m_ScrolledWindow.get_style_context()->add_class("sw");
	m_TextView.get_style_context()->add_class("ta");
}

TodoWindow::~TodoWindow()
{
}

void TodoWindow::get_list_from_file() {
	std::ifstream inf{ "todo.txt" };

	// create file if it doesnt exist
	if (!inf) {
		std::ofstream outf{ "todo.txt"};
	}

	// read data from file and put it in string
	std::string listStr;
	std::getline(inf, listStr);
	while (inf) {
		std::string temp;
		std::getline(inf, temp);
		listStr = listStr + "\n" + temp;
	}

	// put string data into the text buffer
	m_refTextBuffer = Gtk::TextBuffer::create();
	m_refTextBuffer->set_text(listStr);
}

void TodoWindow::write_back_to_file() {
	std::ofstream outf { "todo.txt" };
	outf << m_refTextBuffer->get_text();
}

bool TodoWindow::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state) {
	if(keyval == GDK_KEY_Escape)
	{
		//close the window, when the 'esc' key is pressed
		std::cout << "exiting\n";
		write_back_to_file();
		hide();
		return true;
	}

	//the event has not been handled
	return false;
}

bool TodoWindow::update_timer() {
	write_back_to_file();
	return true;
}