all: steganography.o image_class.o
	g++ -o bin/HiddenFrame src/image_class.cpp src/steganography.cpp ${CompilationOptions}
image_class.o: include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h
	g++ -c src/image_class.cpp -o build/image_class.o ${CompilationOptions}
steganography.o: include/hiddenframe_headers.h
	g++ -c src/steganography.cpp -o build/steganography.o ${CompilationOptions} ${CompilationWarnings}
CompilationOptions= -ggdb -I include/ 
CompilationWarnings=-Wall -Wextra