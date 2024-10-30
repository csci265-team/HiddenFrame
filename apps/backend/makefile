all: build steganography.o image_class.o api.o
	g++ -o build/HiddenFrame build/image_class.o build/steganography.o build/api.o ${CompilationOptions} ${CompilationWarnings}

build:
	mkdir -p build
	mkdir -p static

image_class.o: include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h
	g++ -c src/image_class.cpp -o build/image_class.o ${CompilationOptions}

steganography.o: include/hiddenframe_headers.h
	g++ -c src/steganography.cpp -o build/steganography.o ${CompilationOptions} ${CompilationWarnings}

api.o: include/hiddenframe_headers.h include/crow.h include/crow/*
	g++ -c src/api.cpp -o build/api.o ${CompilationOptions} ${CompilationWarnings}

test: image_class.o test_image_io.o
	g++ -o test/test_image_io build/image_class.o test/test_image_io.o ${CompilationOptions} ${CompilationWarnings}

test_image_io.o: include/hiddenframe_headers.h
		g++ -c test/test_image_io.cpp -o test/test_image_io.o ${CompilationOptions} ${CompilationWarnings}


macos: IncludePaths= -I include/ -I /opt/homebrew/include
macos: all

linux: IncludePaths= -I include/ -I /usr/local/include
linux: all

windows: IncludePaths= -I include/ -I  C:/msys64/ucrt64/include/asio/include
windows: CompilationOptions= -ggdb -std=c++17 -lws2_32 -lmswsock ${IncludePaths}
windows: all

cleanStatic:
	rm -rf static
	mkdir static

clean:
	rm -rf build

IncludePaths= -I include/ 
CompilationOptions= -ggdb -std=c++17 ${IncludePaths}
CompilationWarnings=-Wall -Wextra