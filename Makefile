CC = g++

SRCDIR=src
OBJDIR=obj
BINDIR=bin

CFLAGS = -c -Wall
SOURCES = $(SRCDIR)/campo.cpp $(SRCDIR)/drone.cpp $(SRCDIR)/sistema.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = main
INCLUDES = $(SRCDIR)/tipos.h


.PHONY: all clean

all: $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*

$(BINDIR)/$(TARGET): $(SRCDIR)/$(TARGET).cpp $(INCLUDES) $(OBJECTS)
	$(CC) -o $(BINDIR)/$(TARGET) $(SRCDIR)/$(TARGET).cpp $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@