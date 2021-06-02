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

include include/osvars.mk

SRC_DIR = ./src/
BOARD_DIR=./resources/
BUILD_DIR=./build/
INCLUDE_DIR=./include/
EXECUTABLE=$(BUILD_DIR)sudokusolver$(F_EXT)
TAR_SOURCE=$(BUILD_DIR)source.zip

SRCS=$(wildcard $(SRC_DIR)*.cpp)
BOARDS=$(wildcard $(BOARD_DIR)*.txt)
INCLUDE=$(wildcard $(INCLUDE_DIR)*.mk)

FLAGS=-static
ifneq ($(OS), Windows_NT)
	FLAGS += -std=c++11
endif

$(EXECUTABLE): $(SRCS)
	g++ $(FLAGS) -o $(EXECUTABLE) $(SRCS)

tar-source: 
	tar -zcf $(TAR_SOURCE) $(SRCS) $(BOARDS) $(INCLUDE) Makefile

clean:
	$(RM) $(subst /,$(F_SEP), $(EXECUTABLE)) $(subst /,$(F_SEP), $(TAR_SOURCE))

run: $(EXECUTABLE)
	$(subst /,$(F_SEP), $(EXECUTABLE))