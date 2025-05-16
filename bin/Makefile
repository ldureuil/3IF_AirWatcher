# Variables de compilation
CXX := g++
CXXFLAGS = -ansi -pedantic -Wall -std=c++11
CXXFLAGS_DEBUG := -ansi -pedantic -Wall -std=c++11 -g -DMAP
TARGET := AirWatcher
SOURCES = IHM/CLI.cpp Data/Cleaner.cpp Data/Credentials.cpp Data/Measurement.cpp \
		  Data/Sensor.cpp Authentification/AuthService.cpp Authentification/Session.cpp \
		  Services/AdminServices.cpp Services/PointsManager.cpp Services/Statistics.cpp \
		  DataAccess/DataLoader.cpp DataAccess/AuthDataAccess.cpp DataAccess/UserDataAccess.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: clean $(TARGET)


# Création de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compilation de chaque fichier source en objet
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Nettoyage du projet
clean:
	rm -rf $(OBJDIR) $(TARGET)