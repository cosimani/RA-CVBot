#include "scene.h"
#include <QApplication>
#include "ui_principal.h"  // Necesario para acceder al ui de Principal

#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include "common.h"

Scene::Scene( QWidget *parent ) : QLabel( parent ),
                                  videoCapture ( new cv::VideoCapture( 0 ) ),
                                  sceneTimer ( new QTimer( this ) ),
                                  markerDetector( new MarkerDetector ),
                                  cameraParameters( new CameraParameters )
{

    QString archivoYml = "../RA-CVBot/Files/CameraParameters.yml";

    QFile file( archivoYml );
    if ( !file.exists() )  {
        QMessageBox::critical(this, "No se puede configurar la camara", "Falta el archivo CameraParameters.yml.");
        std::exit(0);
    }
    cameraParameters->readFromXMLFile( archivoYml.toStdString() );

    if ( cameraParameters->isValid() )  {
        sceneTimer->start( 50 );
    }

    connect( sceneTimer, SIGNAL( timeout() ), SLOT( slot_procesar() ) );
}

Scene::~Scene()
{
    videoCapture->release();
}

void Scene::slot_procesar()  {
    videoCapture->operator >>( frame );

    cvtColor(frame, frame, CV_BGR2RGB);

    Mat grayscaleMat; cvtColor( frame, grayscaleMat, CV_BGR2GRAY );
    Mat binaryMat; threshold( grayscaleMat, binaryMat, 128, 255, cv::THRESH_BINARY );

    std::vector< Marker > detectedMarkersVector;
    cameraParameters->resize( binaryMat.size() );
    markerDetector->detect( binaryMat, detectedMarkersVector, *cameraParameters, 0.08f );
    detectedMarkers = QVector< Marker >::fromStdVector( detectedMarkersVector );

    // descripcion del marker
    for( int i = 0; i < detectedMarkers.size(); i++ )
        detectedMarkers.at( i ).draw( frame, Scalar( 255, 0, 255 ), 1 );

    QPixmap pixmap = QPixmap::fromImage( QImage( frame.data,
                                                 frame.cols,
                                                 frame.rows,
                                                 frame.step,
                                                 QImage::Format_RGB888
                                               ).scaled( this->width(), this->height() )
                                       );
    this->setPixmap( pixmap );
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    switch( event->key() )  {
    case Qt::Key_Escape:
        qApp->quit();
        break;

    default:;
    }
}





