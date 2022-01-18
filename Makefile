all: todo

todo: main.o todowindow.o 
	g++ -o todo main.o todowindow.o `pkg-config gtkmm-4.0 --cflags --libs`

main.o: main.cpp
	g++ -c main.cpp `pkg-config gtkmm-4.0 --cflags --libs`

todowindow.o: todowindow.cpp todowindow.h
	g++ -c todowindow.cpp `pkg-config gtkmm-4.0 --cflags --libs`

clean:
	rm -f *.o todo *~ \#*