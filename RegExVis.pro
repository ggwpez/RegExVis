#-------------------------------------------------
#
# Project created by QtCreator 2016-01-02T14:00:30
#
#-------------------------------------------------

QT       += core core gui opengl

TARGET = RegExVis

TEMPLATE = app
LIBS += -lGLU

SOURCES += main.cpp \
	renderer.cpp \
	ast.cpp \
	parser.cpp \
	interpreter.cpp \
	vec3.cpp \
	state.cpp \
	point3f.cpp \
	bruteforce.cpp

HEADERS += \
	renderer.h \
	ast.h \
	parser.h \
	interpreter.h \
	vec3.h \
	state.h \
	point3f.h \
	bruteforce.h

QMAKE_CXXFLAGS += -std=c++14 -fpermissive -O0 -Wcomment -pipe
