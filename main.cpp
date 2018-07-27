#include <QApplication>
#include "scene.h"

int main( int argc, char **argv )  {
    QApplication app( argc, argv );

    Scene scene;
    scene.show();
    scene.move( 100, 100 );
    scene.resize( 640, 480 );

    return app.exec();
}
