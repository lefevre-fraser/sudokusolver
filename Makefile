SRC_DIR = .\src
BUILD_DIR=.\build
EXECUTABLE=$(BUILD_DIR)\sudokusolver.exe

$(EXECUTABLE): $(SRC_DIR)\sudokusolver.cpp
	g++ -static -o "$(EXECUTABLE)" "$(SRC_DIR)\sudokusolver.cpp"

clean:
	DEL /Q  $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE)