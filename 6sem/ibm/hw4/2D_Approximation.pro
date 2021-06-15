QT += widgets opengl
CONFIG += c++1z

HEADERS       = \
  common.h \
  data_bus.h \
  domain.h \
  function.h \
  graphicwidgetopengl.h \
  grid_3d.h \
  kernel.h \
  point_3d.h \
  solver.h \
  thread_func.h \
  window.h
SOURCES       = \
  data_bus.cpp \
  domain.cpp \
  function.cpp \
  graphicwidgetopengl.cpp \
  grid_3d.cpp \
  kernel.cpp \
  main.cpp \
  point_3d.cpp \
  solver.cpp \
  thread_func.cpp \
  window.cpp

