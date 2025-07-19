EXENAME		?= game.exe
SRCDIR		?= ./src
OBJDIR		?= ./obj
BINDIR		?= ./bin
PREFIX		?= /usr/local

EXECUTABLE	:= $(BINDIR)/$(EXENAME)
SOURCES		:= $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPENDS		:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)
OBJDIRS		:= $(sort $(dir $(OBJECTS)))

CC		:= g++
CFLAGS		:= -Wall -Werror
CPPFLAGS	:= -I $(SRCDIR)

.PHONY: all debug build clean

all: build

debug: CFLAGS += -g
debug: CPPFLAGS += $(DEBUGMACROS)
debug: $(OBJDIRS) $(EXECUTABLE)

build: CFLAGS += -O3
build: CPPFLAGS += -DNDEBUG
build: $(OBJDIRS) $(EXECUTABLE)

-include $(DEPENDS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIRS):
	mkdir -p $@

$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

install: $(EXECUTABLE)
	install $(EXECUTABLE) $(DESTDIR)$(PREFIX)/$(EXECUTABLE)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/$(EXECUTABLE)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
