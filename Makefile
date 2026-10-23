# ------------------------------------------------------------------------------
# Makefile
# ------------------------------------------------------------------------------

# Makefile settings
SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

SRC := ./src
BUILD	:= ./build

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

CXX := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Wpedantic

TARGET := wbp-solver

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

clean:
	rm -vf $(TARGET)

# .PHONY: clean
