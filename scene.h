#ifndef SCENE_H
#define SCENE_H

#define RESOLUTION_WIDTH  640
#define RESOLUTION_HEIGHT 480

#include <stdio.h>
#include <stdlib.h>

#include <QDir>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <QMouseEvent>

#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <aruco/aruco.h>

#ifdef RASPBERRY
#include "servertcp.h"
#endif

#include <QLabel>

using namespace cv;
using namespace std;
using namespace aruco;

class Scene : public QLabel  {
    Q_OBJECT

private:
    VideoCapture *videoCapture;
    QTimer *sceneTimer;
    MarkerDetector *markerDetector;
    QVector< Marker > detectedMarkers;
    CameraParameters *cameraParameters;
    cv::Mat frame;

    // Mantiene el ultimo mensaje enviado al robot, esto para que no siga enviando el mismo mensaje si ya lo esta haciendo
    int ultimoMensajeSerial;
    // 0      "detener robot"
    // 1      "adelante robot"
    // 2      "atras robot"
    // 3      "derecha robot"
    // 4      "izquierda robot"
    // 21     "abajo camara"
    // 22     "arriba camara"
    // 23     "izquierda camara"
    // 24     "derecha camara"


#ifdef RASPBERRY
    ServerTcp server;
#endif

public:
    Scene( QWidget *parent = 0 );
    ~Scene();

protected:
    void keyPressEvent( QKeyEvent *event );

private slots:
    void slot_procesar();
};

#endif // SCENE_H
