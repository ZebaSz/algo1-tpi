CC = g++

SRCDIR=src
OBJDIR=obj
BINDIR=bin

CFLAGS = -c -std=c++11
SOURCES = $(SRCDIR)/campo.cpp $(SRCDIR)/drone.cpp $(SRCDIR)/sistema.cpp $(SRCDIR)/tipos.cpp $(SRCDIR)/aux.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = main


.PHONY: all clean

all: $(BINDIR)/$(TARGET)

$(TARGET): $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*

$(BINDIR)/$(TARGET): $(SRCDIR)/$(TARGET).cpp $(INCLUDES) $(OBJECTS)
	$(CC) -o $(BINDIR)/$(TARGET) $(SRCDIR)/$(TARGET).cpp $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
