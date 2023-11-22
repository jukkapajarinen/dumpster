#Includes common configuration for all subdirectory .pro files.
INCLUDEPATH += . ..

TEMPLATE = lib

# The following keeps the generated files at least somewhat separate
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

CONFIG += C++11
QMAKE_CXXFLAGS += -std=c++11
