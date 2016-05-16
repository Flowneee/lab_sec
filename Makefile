# my wxWidgets Makefile
CXX 		= g++
CXXFLAGS 	= -c -Wall -Wpedantic -std=c++14
LDFLAGS		= -lstdc++fs
WX_DEBUG 	= yes
WX_MODE 	= --unicode=yes --debug=$(WX_DEBUG)
WX_LIBS 	= --libs base,core
WX_CXXFLAGS 	= $(shell wx-config --cxxflags $(WX_MODE))
WX_LIBFLAGS    	= $(shell wx-config $(WX_LIBS) $(WX_MODE))
SOURCES 	= main.cpp gui.cpp wxfb_gui.cpp user.cpp passwdmanager.cpp
OBJECTS 	= $(SOURCES:.cpp=.o)
EXECUTABLE 	= lab_sec

release: WX_DEBUG = no
release: CXXFLAGS += -O3 -s
release: $(EXECUTABLE)

debug: WX_DEBUG = yes
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@  $(LDFLAGS) $(WX_LIBFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@ $(WX_CXXFLAGS)

clean:
	rm -rf *.o $(EXECUTABLE)

list:
	@echo debug
	@echo release
	@echo clean
	@echo list
