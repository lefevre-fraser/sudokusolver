########################################################################
#    Copyright 2021 Fraser LeFevre
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
# 
#        http://www.apache.org/licenses/LICENSE-2.0
# 
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#######################################################################

SRC_DIR = ./src
BOARD_DIR=./resources
BUILD_DIR=./build
EXECUTABLE=$(BUILD_DIR)/sudokusolver
TAR_SOURCE=$(BUILD_DIR)/source.zip

$(EXECUTABLE): $(SRC_DIR)/sudokusolver.cpp
	g++ -static -o "$(EXECUTABLE)" "$(SRC_DIR)/sudokusolver.cpp"

tar-source: 
	tar -cf "$(TAR_SOURCE)" "$(SRC_DIR)/sudokusolver.cpp" "$(BOARD_DIR)/*"

clean:
	rm  $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE)