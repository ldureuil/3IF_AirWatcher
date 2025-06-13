# Variables de compilation
CXX := g++
CXXFLAGS = -ansi -pedantic -Wall -std=c++17
CXXFLAGS_DEBUG := -ansi -pedantic -Wall -std=c++17 -g -DMAP
TARGET := AirWatcher
TARGET_TEST := Test_AirWatcher
BUILD_DIR := build

SOURCES = IHM/CLI.cpp \
		  DataAccess/DataLoader.cpp DataAccess/AuthDataAccess.cpp DataAccess/UserDataAccess.cpp \
		  Data/Cleaner.cpp Data/Credentials.cpp Data/Measurement.cpp Data/Sensor.cpp Data/ParticulierData.cpp \
		  Services/AdminServices.cpp Services/PointsManager.cpp Services/Statistics.cpp \
		  Authentification/Session.cpp Authentification/AuthService.cpp
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))


all: $(TARGET)

debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: clean $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compilation de chaque fichier source en objet
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Création du répertoire build/
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Nettoyage du projet
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

cleano:
	rm -rf $(BUILD_DIR)

test: Test_AirWatcher

Test_AirWatcher: build/Tests/functional_tests_main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) build/Tests/functional_tests_main.o $(filter-out $(BUILD_DIR)/IHM/CLI.o, $(OBJECTS))

build/Tests/functional_tests_main.o: tests/functional_tests_main.cpp
	$(CXX) $(CXXFLAGS) -c Tests/functional_tests_main.cpp -o build/Tests/functional_tests_main.o
