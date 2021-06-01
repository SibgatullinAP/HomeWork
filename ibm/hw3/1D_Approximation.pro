QT += widgets
CONFIG += c++1z
DEFINES += MISC_WARNING_DISABLE

HEADERS       = window.h \
  common.h \
  coordinate.h \
  function.h \
  methods.h
SOURCES       = main.cpp \
                function.cpp \
                methods.cpp \
                window.cpp
