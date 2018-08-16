#include "scene.h"
#include <QApplication>

#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>

Scene::Scene( QWidget *parent ) : QLabel( parent ),
                                  //videoCapture ( new cv::VideoCapture( "tcp://10.0.7.34:2222" ) ),
                                  videoCapture ( new cv::VideoCapture( 0 ) ),
                                  sceneTimer ( new QTimer( this ) ),
                                  markerDetector( new MarkerDetector ),
                                  cameraParameters( new CameraParameters ),
                                  ultimoMensajeSerial( 0 )
{

    QString archivoYml = "../RA-CVBot/Files/CameraParameters.yml";

    QFile file( archivoYml );
    if ( !file.exists() )  {
        QMessageBox::critical(this, "No se puede configurar la camara", "Falta el archivo CameraParameters.yml.");
        std::exit(0);
    }
    cameraParameters->readFromXMLFile( archivoYml.toStdString() );

    if ( cameraParameters->isValid() )  {
        sceneTimer->start( 20 );
    }

    connect( sceneTimer, SIGNAL( timeout() ), SLOT( slot_procesar() ) );

#ifdef RASPBERRY
//    server.setPuerto( 5000 );
//    server.iniciar();
#endif

}

Scene::~Scene()
{
    server.enviarAlSerial( "<1,0,255>" );
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

    // Si no detecta ningun marcador, entonces que detenga el robot
//    if ( detectedMarkers.size() == 0 )  {
//        server.enviarAlSerial( "<1,0,255>" );
//    }

    for( int i = 0; i < detectedMarkers.size(); i++ )  {
        // Recuadra el marcador y dibuja su id
        detectedMarkers.at( i ).draw( frame, Scalar( 255, 0, 255 ), 1 );

#ifdef RASPBERRY

        int perimetro = detectedMarkers.at( i ).getPerimeter();
        int x = detectedMarkers.at( i ).getCenter().x;

        qDebug() << "Perimetro = " << perimetro << "     x = " << x;

        // Estos rangos son para que no este constantemente corrigiendose la posicion.
        int rangoPerimetro = 30;
        int rangoX = rangoPerimetro * 2;

        int perimetroDeseado = 400;
        int xDeseado = this->width() / 2;

        if ( perimetro < perimetroDeseado - rangoPerimetro )  {
            qDebug() << "Avanzar <1,1,100>";
            if ( ultimoMensajeSerial != 1 )  {  server.enviarAlSerial( "<1,1,120>" );  ultimoMensajeSerial = 1;  }
        }        
        else if ( perimetro >= perimetroDeseado + rangoPerimetro )  {
            qDebug() << "Retroceder <1,2,100>";
            if ( ultimoMensajeSerial != 2 )  {  server.enviarAlSerial( "<1,2,120>" );  ultimoMensajeSerial = 2;  }
        }
        else  {
            qDebug() << "Detenerse <1,0,255>";
            if ( ultimoMensajeSerial != 0 )  {  server.enviarAlSerial( "<1,0,255>" );  ultimoMensajeSerial = 0;  }
        }

        if ( x >= xDeseado + rangoX )  {
            qDebug() << "Ir a la derecha <1,3,100>";
            if ( ultimoMensajeSerial != 3 )  {  server.enviarAlSerial( "<1,3,120>" );  ultimoMensajeSerial = 3;  }
        }
        else if ( x < xDeseado - rangoX )  {
            qDebug() << "Ir a la izquierda <1,4,100>";
            if ( ultimoMensajeSerial != 4 )  {  server.enviarAlSerial( "<1,4,120>" );  ultimoMensajeSerial = 4;  }
        }
        else  {
            qDebug() << "Detenerse <1,0,255>";
            if ( ultimoMensajeSerial != 0 )  {  server.enviarAlSerial( "<1,0,255>" );  ultimoMensajeSerial = 0;  }
        }

#endif

    }

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
        server.enviarAlSerial( "<1,0,255>" );
        qApp->quit();
        break;

    case Qt::Key_W:
        server.enviarAlSerial( "<1,1,130>" );  // Avanzar
        qDebug() << "Avanza";
        break;
    case Qt::Key_S:
        server.enviarAlSerial( "<1,2,130>" );  // Retrocede
        qDebug() << "Retrocede";
        break;
    case Qt::Key_D:
        server.enviarAlSerial( "<1,3,130>" );  // Derecha
        qDebug() << "Derecha";
        break;
    case Qt::Key_A:
        server.enviarAlSerial( "<1,4,130>" );  // Izquierda
        qDebug() << "Izquierda";
        break;
    case Qt::Key_P:
        server.enviarAlSerial( "<1,0,255>" );  // Detenerse
        qDebug() << "Se detiene";
        break;

    default:;
    }
}








