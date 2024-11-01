all: build utils.o image_class.o api.o authorization.o
	g++ -o bin/HiddenFrame build/image_class.o build/utils.o build/api.o build/authorization.o ${CompilationOptions} ${CompilationWarnings}

image_class.o: include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h 
	g++ -c src/image_class.cpp -o build/image_class.o ${CompilationOptions}

utils.o: include/hiddenframe_headers.h include/utils.h
	g++ -c src/utils.cpp -o build/utils.o ${CompilationOptions} ${CompilationWarnings}

api.o: include/hiddenframe_headers.h include/crow.h include/crow/*
	g++ -c src/api.cpp -o build/api.o ${CompilationOptions} ${CompilationWarnings}

authorization.o: include/jwt-cpp/* include/picojson/*
	g++ -c src/authorization.cpp -o build/authorization.o ${CompilationOptions} ${CompilationWarnings}

test: image_class.o test_image_io.o
	g++ -o test/test_image_io build/image_class.o test/test_image_io.o build/utils.o ${CompilationOptions} ${CompilationWarnings}

test_image_io.o: include/hiddenframe_headers.h
	g++ -c test/test_image_io.cpp -o test/test_image_io.o ${CompilationOptions} ${CompilationWarnings}

macos: all

linux: all

windows: all

build:
	$(MKDIR) build
	$(MKDIR) static
	$(MKDIR) bin

clean:
	$(CLEAN_DIR) build
	$(CLEAN_DIR) bin
	$(CLEAN_DIR) static

IncludePath  ?= -I include/ 
CompilationOptions= -ggdb -std=c++17 ${IncludePaths}
CompilationWarnings=-Wall -Wextra

OS := $(shell uname)
ifeq ($(OS),Linux)
	RM := rm -rf
	MKDIR := mkdir -p
	CLEAN_DIR := rm -rf static/*
	IncludePaths+= -I include/ -I /usr/local/include
else ifeq ($(OS),Darwin)
	RM := rm -rf
	MKDIR := mkdir -p
	CLEAN_DIR := rm -rf static/*
	IncludePaths+= -I include/ -I /opt/homebrew/include
else
	RM := rmdir /s /q 
	MKDIR := mkdir
	CLEAN_DIR := del /q static\*
	IncludePaths += -I include/ -I  C:/msys64/ucrt64/include/asio/include
	CompilationOptions += -lws2_32 -lmswsock
endif
