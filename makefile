UNAME := $(shell uname)

CC = g++

ifeq ($(UNAME), Linux)
	CXXFLAGS = -Wall -O0 -std=c++20
	LIBS = -lboost_system -lboost_iostreams
else
	CXXFLAGS = -I C:/boost_build/include/boost-1_81 -Wall -O0 -std=c++20
	LDFLAGS = -L C:/boost_build/lib
	LIBS = -lboost_system-mgw13-mt-x64-1_81 -lws2_32
endif

SOURCE = Main.cpp Boost_Transmitter.cpp Boost_Client.cpp
OUTPUT = build


all: $(SOURCE)
	@echo $(shell ver)
	@echo "----------Compile---------"		
	$(CC) $(SOURCE) -o $(OUTPUT) $(CXXFLAGS) $(LDFLAGS) $(LIBS)	
	@echo "----------Done------------"

clean:
	rm -f $(OUTPUT)