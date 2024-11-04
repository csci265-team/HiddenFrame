all: build build/utils.o build/image_class.o build/api.o build/authorization.o build/db_operations.o
	g++ -o bin/HiddenFrame build/image_class.o build/utils.o build/api.o build/authorization.o build/db_operations.o ${CompilationOptions} ${CompilationWarnings}

build/image_class.o: include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h 
	g++ -c src/image_class.cpp -o build/image_class.o ${CompilationOptions}

build/utils.o: include/hiddenframe_headers.h include/utils.h
	g++ -c src/utils.cpp -o build/utils.o ${CompilationOptions} ${CompilationWarnings}

build/db_operations.o: include/hiddenframe_headers.h include/sqlite/*
	g++ -c src/db_operations.cpp -o build/db_operations.o ${CompilationOptions} ${CompilationWarnings}

build/api.o: include/hiddenframe_headers.h include/crow.h include/crow/*
	g++ -c src/api.cpp -o build/api.o ${CompilationOptions} ${CompilationWarnings}

build/authorization.o: include/jwt-cpp/* include/picojson/* include/authorization.h
	g++ -c src/authorization.cpp -o build/authorization.o ${CompilationOptions} ${CompilationWarnings}

test-image: build/image_class.o test/test_image_io.o
	g++ -o test/test_image_io build/image_class.o test/test_image_io.o build/utils.o ${CompilationOptions} ${CompilationWarnings}

test/test_image_io.o: include/hiddenframe_headers.h
	g++ -c test/test_image_io.cpp -o test/test_image_io.o ${CompilationOptions} ${CompilationWarnings}

test/test_user_database.o: include/hiddenframe_headers.h include/sqlite/*
	g++ -c test/test_user_database.cpp -o test/test_user_database.o ${CompilationOptions} ${CompilationWarnings} ${IncludePath}

test-db: test/test_user_database.o build/db_operations.o
	g++ -o test/usrdbtest test/test_user_database.o build/db_operations.o ${CompilationOptions} ${CompilationWarnings} ${IncludePath}

macos: all

linux: all

windows: all

build:
	$(MKDIR) build
	$(MKDIR) static
	$(MKDIR) bin
	$(MKDIR) database

clean:
	$(CLEAN_DIR) build
	$(CLEAN_DIR) bin
	$(CLEAN_DIR) static
	$(CLEAN_DIR) database

IncludePath  ?= -I include/ 
CompilationOptions= -ggdb -std=c++17 -lsqlite3 ${IncludePaths}
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
	IncludePaths+= -I include/ -I /opt/homebrew/include -L /opt/homebrew/opt/openssl/lib
	CompilationOptions += -lcrypto
else
	RM := rmdir /s /q 
	MKDIR := mkdir
	CLEAN_DIR := del /q static\*
	IncludePaths += -I include/ -I  C:/msys64/ucrt64/include/asio/include
	CompilationOptions += -lws2_32 -lmswsock -lssl -lcrypto
endif
