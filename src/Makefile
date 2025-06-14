# Variables de compilation
CXX := g++
CXXFLAGS = -ansi -pedantic -Wall -std=c++17
CXXFLAGS_DEBUG := -ansi -pedantic -Wall -std=c++17 -g -DMAP
TARGET := AirWatcher
TARGET_TEST := Test_AirWatcher
TEST_UNIT_TARGET := Unit_Test_AirWatcher
BUILD_DIR := build

SOURCES = IHM/CLI.cpp \
		  DataAccess/DataLoader.cpp DataAccess/AuthDataAccess.cpp DataAccess/UserDataAccess.cpp \
		  Data/Cleaner.cpp Data/Credentials.cpp Data/Measurement.cpp Data/Sensor.cpp Data/ParticulierData.cpp \
		  Services/AdminServices.cpp Services/PointsManager.cpp Services/Statistics.cpp \
		  Authentification/Session.cpp Authentification/AuthService.cpp
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

TEST_UNIT_SOURCES = tests/unit_tests/dataLoader_tests.cpp
TEST_UNIT_OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(TEST_UNIT_SOURCES))


all: $(TARGET)
test: Unit_Test_AirWatcher

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

Test_AirWatcher: build/Tests/functional_tests_main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) build/Tests/functional_tests_main.o $(filter-out $(BUILD_DIR)/IHM/CLI.o, $(OBJECTS))

build/Tests/functional_tests_main.o: tests/functional_tests_main.cpp
	$(CXX) $(CXXFLAGS) -c Tests/functional_tests_main.cpp -o build/Tests/functional_tests_main.o

# Règle pour compiler l'exécutable des tests unitaires
Unit_Test_AirWatcher: $(TEST_UNIT_OBJECTS) build/tests/unit_tests_main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_UNIT_TARGET) build/tests/unit_tests_main.o $(TEST_UNIT_OBJECTS) $(filter-out $(BUILD_DIR)/IHM/CLI.o, $(OBJECTS))

# Règle pour compiler unit_tests_main.cpp
build/tests/unit_tests_main.o: tests/unit_tests_main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c tests/unit_tests_main.cpp -o build/tests/unit_tests_main.o

# Règle pour compiler les fichiers de tests unitaires
$(BUILD_DIR)/tests/unit_tests/%.o: tests/unit_tests/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@