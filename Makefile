file-manager: build/app.o build/window.o
	g++ build/app.o build/window.o -o file-manager `wx-config --cxxflags --libs`

build/app.o: headers/app.h src/app.cpp
	g++ -c src/app.cpp -o build/app.o `wx-config --cxxflags --libs`

build/window.o: headers/window.h src/window.cpp src/file_operations.cpp
	g++ -c src/window.cpp -o build/window.o `wx-config --cxxflags --libs`

clean:
	rm build/*.o