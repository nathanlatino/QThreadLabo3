QT += widgets

HEADERS       = \
    displaymandel.h \
    workerthread.h \
    bossthread.h
SOURCES       = main.cpp \
    displaymandel.cpp \
    workerthread.cpp \
    bossthread.cpp

unix:!mac:!vxworks:!integrity:!haiku:LIBS += -lm

# install
target.path = $$[QT_INSTALL_EXAMPLES]/corelib/threads/mandelbrot
INSTALLS += target

FORMS +=