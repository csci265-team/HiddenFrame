all: build steganography.o image_class.o api.o
	g++ -o build/HiddenFrame build/image_class.o build/steganography.o build/api.o ${CompilationOptions} ${CompilationWarnings}

build:
	mkdir -p build
	mkdir -p static

image_class.o: include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h
	g++ -c src/image_class.cpp -o build/image_class.o ${CompilationOptions}

steganography.o: include/hiddenframe_headers.h
	g++ -c src/steganography.cpp -o build/steganography.o ${CompilationOptions} ${CompilationWarnings}

api.o: include/hiddenframe_headers.h
	g++ -c src/api.cpp -o build/api.o ${CompilationOptions} ${CompilationWarnings}


macos: IncludePaths= -I include/ -I /opt/homebrew/include
macos: all

linux: IncludePaths= -I include/ -I /usr/local/include
linux: all

windows: IncludePaths= -I include/ -I /usr/local/include
windows: build steganography.o image_class.o api.o
	g++ -o build/HiddenFrame.exe build/image_class.o build/steganography.o build/api.o ${CompilationOptions} ${CompilationWarnings}


cleanStatic:
	rm -rf static
	mkdir -p static

clean:
	rm -rf build

IncludePaths= -I include/
CompilationOptions= -ggdb -std=c++11 ${IncludePaths} 
CompilationWarnings=-Wall -Wextra