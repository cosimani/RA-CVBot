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
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_video.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_features2d.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_flann.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_ml.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_photo.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_stitching.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_superres.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_video.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_videostab.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_imgcodecs.so
unix:LIBS += $$DIR_OPENCV_LIBS/libopencv_videoio.so

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

