all: build build/utils.o build/image_class.o build/authorization.o build/db_operations.o build/api.o
	g++ -o bin/HiddenFrame build/image_class.o build/utils.o build/authorization.o build/db_operations.o build/api.o ${CompilationOptions} ${CompilationWarnings}

build/image_class.o: include/hiddenframe_headers.h include/stb_image_write.h include/stb_image.h 
	g++ -c src/image_class.cpp -o build/image_class.o ${CompilationOptions}

build/utils.o: include/hiddenframe_headers.h include/utils.h
	g++ -c src/utils.cpp -o build/utils.o ${CompilationOptions} ${CompilationWarnings}

build/db_operations.o: include/hiddenframe_headers.h include/sqlite/*
	g++ -c src/db_operations.cpp -o build/db_operations.o ${CompilationOptions} ${CompilationWarnings}

build/api.o: include/hiddenframe_headers.h include/crow.h include/crow/* include/authorization.h 
	g++ -c src/api.cpp -o build/api.o ${CompilationOptions} ${CompilationWarnings}

build/authorization.o: include/jwt-cpp/* include/picojson/* include/crow/* include/crow/* include/authorization.h
	g++ -c src/authorization.cpp -o build/authorization.o ${CompilationOptions} ${CompilationWarnings}

test-image: build/image_class.o test/test_image_io.o
	g++ -o test/test_image_io build/image_class.o test/test_image_io.o build/utils.o ${CompilationOptions} ${CompilationWarnings}

test/test_image_io.o: include/hiddenframe_headers.h
	g++ -c test/test_image_io.cpp -o test/test_image_io.o ${CompilationOptions} ${CompilationWarnings}

test/test_user_database.o: include/hiddenframe_headers.h include/sqlite/*
	g++ -c test/test_user_database.cpp -o test/test_user_database.o ${CompilationOptions} ${CompilationWarnings} ${IncludePath}

test-db: test/test_user_database.o build/db_operations.o
	g++ -o test/usrdbtest test/test_user_database.o build/db_operations.o ${CompilationOptions} ${CompilationWarnings} ${IncludePath}

.PHONY: build clean test-db macos linux windows

macos: all

linux: all

windows: all

build:
	$(BUILD_DIRS_COMMAND)

clean:
	$(CLEAN_DIR) build
	$(CLEAN_DIR) bin
	$(CLEAN_DIR) static
#	$(CLEAN_DIR) database 

IncludePath  ?= -I include/ 
CompilationOptions= -ggdb -std=c++17 -lsqlite3 ${IncludePaths}
CompilationWarnings=-Wall -Wextra

# Detect the OS type
ifeq ($(OS),Windows_NT)
	# For Windows
	IS_WINDOWS = 1
else
	# For Unix-based systems (Linux/macOS)
	IS_UNIX = 1
endif

ifeq ($(IS_UNIX), 1)
	# For Unix-like systems (Linux/macOS)
	RM := rm -rf
	MKDIR := mkdir -p
	CLEAN_DIR := rm -rf static/*
	IncludePaths+= -I include/ -I /usr/local/include
	BUILD_DIRS := build static bin database
	BUILD_DIRS_COMMAND = $(foreach dir,$(BUILD_DIRS),$(shell if [ ! -d "$(dir)" ]; then $(MKDIR) $(dir); fi))
else ifeq ($(IS_WINDOWS), 1)
	# For Windows (MinGW/MSYS) logic
	RM := rmdir /s /q 
	MKDIR := mkdir
	CLEAN_DIR := del /q static\*
	IncludePaths += -I include/ -I  C:/msys64/ucrt64/include/asio/include 
	CompilationOptions += -lws2_32 -lmswsock -lssl -lcrypto
	BUILD_DIRS := build static bin database
	BUILD_DIRS_COMMAND = $(foreach dir,$(BUILD_DIRS),$(shell if not exist "$(dir)" mkdir $(dir)))
endif
