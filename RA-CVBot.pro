#---------------------------------
#
# Proyecto de Interaccion Natural
#
#---------------------------------

QT += widgets

TEMPLATE = app

DEFINES += NO_DEBUG_ARUCO

DEFINES += RASPBERRY

# Si se define RASPBERRY entonces preparamos el servidor y las librerias del Serial con wiringPi
! exists( RASPBERRY )  {
    message( "Esta definida la macro RASPBERRY" )
    QT += network

    # Las siguiente bibliotecas parece que ya vienen en la Raspberry
    LIBS += -lwiringPi -lwiringPiDev -lpthread
}



unix:DIR_OPENCV_LIBS = /usr/local/lib

unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_core.so         # OpenCV
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_highgui.so      # OpenCV
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_imgproc.so      # OpenCV
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_objdetect.so    # OpenCV
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_calib3d.so      # OpenCV
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_ml.so           # OpenCV
#unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_contrib.so     # OpenCV

unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_video.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_features2d.so

unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_flann.so
#unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_gpu.so
#unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_legacy.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_ml.so
#unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_ocl.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_photo.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_stitching.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_superres.so
#unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_ts.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_video.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_videostab.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_imgcodecs.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_videoio.so


win32:DIR_OPENCV_LIBS = C:/Qt/OpenCV-3.1.0

win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/core/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/imgproc/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/video/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/flann/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/features2d/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/calib3d/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/legacy/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/objdetect/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/highgui/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/photo/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/ml/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/contrib/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/hal/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/imgcodecs/include"
win32:INCLUDEPATH += "$$DIR_OPENCV_LIBS/opencv/sources/modules/videoio/include"

win32:LIBS += -L"$$DIR_OPENCV_LIBS/opencv/compilado/lib"

win32:LIBS += -lopencv_core310.dll
win32:LIBS += -lopencv_highgui310.dll
win32:LIBS += -lopencv_imgproc310.dll
win32:LIBS += -lopencv_objdetect310.dll
win32:LIBS += -lopencv_calib3d310.dll

win32:LIBS += -lopencv_ml310.dll
win32:LIBS += -lopencv_video310.dll
win32:LIBS += -lopencv_features2d310.dll
win32:LIBS += -lopencv_flann310.dll
win32:LIBS += -lopencv_photo310.dll
win32:LIBS += -lopencv_stitching310.dll
win32:LIBS += -lopencv_superres310.dll
win32:LIBS += -lopencv_video310.dll
win32:LIBS += -lopencv_videostab310.dll
win32:LIBS += -lopencv_imgcodecs310.dll
win32:LIBS += -lopencv_videoio310.dll

win32:LIBS += -lopengl32
win32:LIBS += -lglu32

# A continuacion los archivos de cabecera de GLUT
win32:INCLUDEPATH += "C:/Qt/glut-3.7.6/include/GL"
# Aqui la carpeta donde se encuentran los archivos de libreria .a de GLUT
win32:LIBS += -L"C:/Qt/glut-3.7.6/lib/glut"
# A continuacion se indican cada uno de los archivos de libreria .a
# Donde se indica -lglut32 es porque el archivo se llama libglut32.a
win32:LIBS += -lglut32

# A continuacion los archivos de cabecera de Lib3ds
win32:INCLUDEPATH += "C:/Qt/lib3ds/include"
# Aqui la carpeta donde se encuentra el archivo de libreria .a de lib3ds
win32:LIBS += -L"C:/Qt/lib3ds/lib"
# A continuacion se indican elos archivo de libreria .a
# Donde se indica -lglut32 es porque el archivo se llama libglut32.a
win32:LIBS += -l3ds




SOURCES += main.cpp\
           scene.cpp \
           aruco/ar_omp.cpp \
           aruco/arucofidmarkers.cpp \
           aruco/board.cpp \
           aruco/boarddetector.cpp \
           aruco/cameraparameters.cpp \
           aruco/highlyreliablemarkers.cpp \
           aruco/marker.cpp \
           aruco/markerdetector.cpp \
           aruco/subpixelcorner.cpp \
    servertcp.cpp

HEADERS += \
           scene.h \
           aruco/ar_omp.h \
           aruco/aruco.h \
           aruco/arucofidmarkers.h \
           aruco/board.h \
           aruco/boarddetector.h \
           aruco/cameraparameters.h \
           aruco/exports.h \
           aruco/highlyreliablemarkers.h \
           aruco/marker.h \
           aruco/markerdetector.h \
           aruco/subpixelcorner.h \
    servertcp.h

FORMS +=

DISTFILES += \
    README.md \
    config/RA-CVBot.config

