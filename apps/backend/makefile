run: all
	./bin/HiddenFrame
.PHONY: all
all: build build/utils.o build/image_class.o build/authorization.o build/db_operations.o build/api.o
	g++ $(ObjectFiles) -o bin/HiddenFrame ${CompilationOptions} ${CompilationWarnings}

build/utils.o: src/utils.cpp include/hiddenframe_headers.h include/utils.h
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings}

build/image_class.o: src/image_class.cpp include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h 
	g++ -c $< -o $@ ${CompilationOptions}

build/authorization.o: src/authorization.cpp include/jwt-cpp/* include/picojson/* include/crow/* include/crow/* include/authorization.h
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings} 

build/db_operations.o: src/db_operations.cpp include/hiddenframe_headers.h include/sqlite/*
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings}

build/api.o: src/api.cpp include/hiddenframe_headers.h include/crow.h include/crow/* include/authorization.h 
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings}

build/test/test_image_io.o: test/test_image_io.cpp include/hiddenframe_headers.h
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings}

test-image: build/image_class.o build/test/test_image_io.o
	g++ $^ build/utils.o -o bin/test/test_image_io ${CompilationOptions} ${CompilationWarnings}

build/test/test_user_database.o: test/test_user_database.cpp include/hiddenframe_headers.h include/sqlite/*
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings} ${IncludePath}

test-db: build/db_operations.o build/test/test_user_database.o
	g++ $^ -o bin/test/usrdbtest ${CompilationOptions} ${CompilationWarnings} ${IncludePath}

build/test/main.o: test/main.cpp
	g++ -c $< -o $@ ${CompilationOptions} ${CompilationWarnings}

.PHONY: test
test: build build/utils.o build/image_class.o build/authorization.o build/db_operations.o build/test/test_image_io.o build/test/test_user_database.o build/test/main.o
	g++ build/utils.o build/image_class.o build/authorization.o build/db_operations.o build/test/test_image_io.o build/test/test_user_database.o build/test/main.o -o bin/test/HiddenFrame_Test ${CompilationOptions} ${CompilationWarnings}
	./bin/test/HiddenFrame_Test --log_level=message

macos: all

linux: all

windows: all

.PHONY: build
build:
	$(MKDIR) build
	$(MKDIR) build/test
	$(MKDIR) static
	$(MKDIR) bin
	$(MKDIR) bin/test
	$(MKDIR) database

.PHONY: clean
clean:
	$(CLEAN_DIR) build
	$(CLEAN_DIR) bin
	$(CLEAN_DIR) static
#   $(CLEAN_DIR) database

IncludePath  ?= -I include/ 
CompilationOptions= -ggdb -std=c++17 -lsqlite3 ${IncludePaths}
CompilationWarnings=-Wall -Wextra
ObjectFiles= build/utils.o build/image_class.o build/authorization.o build/db_operations.o build/api.o
TestObjectFiles= build/test/test_image_io.o build/test/test_user_database.o build/test/main.o

ifeq ($(OS),Windows_NT)
	OS := windows
else
	OS := $(shell uname)
endif

ifeq ($(OS),Linux)
	RM := rm -rf
	MKDIR := mkdir -p
	CLEAN_DIR := rm -rf static/*
	IncludePaths+= -I include/ -I /usr/local/include
else ifeq ($(OS),Darwin)
	RM := rm -rf
	MKDIR := mkdir -p
	CLEAN_DIR := rm -rf static/*
	IncludePaths+= -I include/ -I /opt/homebrew/include -L /opt/homebrew/opt/openssl/lib
	CompilationOptions += -lcrypto
else
	RM := rmdir /s /q 
	MKDIR := powershell -Command "New-Item -ItemType Directory -Force -Path " 
	CLEAN_DIR := del /q static\*
	IncludePaths += -I include/ -I  C:/msys64/ucrt64/include/asio/include 
	CompilationOptions += -lws2_32 -lmswsock -lssl -lcrypto 
endif