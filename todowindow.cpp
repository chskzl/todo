#include "todowindow.h"
#include <iostream>
#include <string>

TodoWindow::TodoWindow(std::string file_path, std::string style_path) : m_VBox(Gtk::Orientation::VERTICAL)
{

	//-----------------

	this->style_path = style_path;
	this->file_path = file_path;
	if (this->style_path == "")
		this->style_path = "style.css";
	if (this->file_path == "")
		this->file_path = "todo.txt";


	std::cout << this->file_path;

	//-----------------

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
	Glib::signal_timeout().connect( sigc::mem_fun(*this, &TodoWindow::write_back_to_file), 1000 );

	// create css provider
	auto css = Gtk::CssProvider::create();
	css->load_from_path(this->style_path);
	get_style_context()->add_provider_for_display(Gdk::Display::get_default(), 
	                                             css, 
	                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	
	// css classes
	get_style_context()->add_class("mainwin");
	m_VBox.get_style_context()->add_class("vb");
	m_ScrolledWindow.get_style_context()->add_class("sw");
	m_TextView.get_style_context()->add_class("ta");
}


TodoWindow::~TodoWindow() {
	write_back_to_file();
}


void TodoWindow::get_list_from_file() {
	std::ifstream inf{ this->file_path };

	// create file if it doesnt exist
	if (!inf) {
		std::ofstream outf{ this->file_path };
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

	inf.close();
}


bool TodoWindow::write_back_to_file() {
	std::ofstream ofs;

	this->file_path = file_path;

	ofs.open(file_path, std::ofstream::out);

	if (!ofs) {
		std::cout << "failed to open file\n";
		exit(EXIT_FAILURE);
	}

	ofs << m_refTextBuffer->get_text();
	ofs.close();

	return true;
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
