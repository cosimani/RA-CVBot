#ifdef RASPBERRY

#include "servertcp.h"

#include <QDebug>

static const int TotalBytes = 50 * 1024 * 1024;
static const int PayloadSize = 64 * 1024; // 64 KB


ServerTcp::ServerTcp(QObject *parent) : QObject(parent),
                                        tcpServer( new QTcpServer( this ) ),
                                        puerto( 0 )
{
    connect( tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    connect( this, SIGNAL(signal_serverClosed()), this, SLOT(iniciar()));

//    idPuerto = serialOpen( "/dev/ttyAMA0", 9600 );

    idPuerto = serialOpen("/dev/ttyS0",9600);

    qDebug() << "isPuerto" << idPuerto;


}

int ServerTcp::getPuerto() const
{
    return puerto;
}

void ServerTcp::setPuerto(int value)
{
    puerto = value;
}

/**
 * @brief ServerTcp::iniciar Inicia el servidor en cualquier interfaz de red y en el puerto indicado.
 * @param puerto
 */
void ServerTcp::iniciar()
{

    qDebug() << "Sever escuchando" << tcpServer->listen( QHostAddress::Any, puerto );
}

/**
 * @brief ServerTcp::acceptConnection Acepta las conexiones, las lee en void updateServerProgress(); y cierra la conexion
 */
void ServerTcp::acceptConnection()
{
    tcpServerConnection = tcpServer->nextPendingConnection();

    connect( tcpServerConnection, SIGNAL( readyRead() ),
             this, SLOT( updateServerProgress() ) );

    connect( tcpServerConnection, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( displayError( QAbstractSocket::SocketError ) ) );

    tcpServer->close();
    emit signal_serverClosed();
}

void ServerTcp::updateServerProgress()
{
    // Para desconectar el QTcpSocket que se crea por cada conexion nueva.
    // Este sender es el tcpServerConnection
    disconnect( this->sender(), SIGNAL( readyRead() ), this, SLOT( updateServerProgress() ) );

    qDebug() << "Bytes recibidos";
    bytesReceived += (int)tcpServerConnection->bytesAvailable();
    QByteArray ba = tcpServerConnection->readAll();

    qDebug() << ba;

    if ( ba == "abajo robot" )  {
        qDebug() << "ATRAS"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<1,2,255>");
    }
    if ( ba == "arriba robot" )  {
        qDebug() << "ADELANTE"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<1,1,255>");
    }
    if ( ba == "derecha robot" )  {
        qDebug() << "DERECHA"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<1,3,255>");
    }
    if ( ba == "izquierda robot" )  {
        qDebug() << "IZQUIERDA"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<1,4,255>");
    }
    if ( ba == "detener robot" )  {
        qDebug() << "PARE!!!!!"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<1,0,255>");
    }
    if ( ba == "arriba camara" )  {
        qDebug() << "CAM_ARRIBA"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<2,2,255>");
    }
    if ( ba == "abajo camara" )  {
        qDebug() << "CAM_ABAJO"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<2,1,255>");
    }
    if ( ba == "derecha camara" )  {
        qDebug() << "CAM_DERECHA"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<2,4,255>");
    }
    if ( ba == "izquierda camara" )  {
        qDebug() << "CAM_IZQUIERDA"; //<< ui->leEnviar->text();
        serialPuts(idPuerto,"<2,3,255>");
    }

    tcpServerConnection->close();

    delete tcpServerConnection;
}

void ServerTcp::displayError(QAbstractSocket::SocketError socketError)
{
    disconnect( this->sender(), SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( displayError( QAbstractSocket::SocketError ) ) );

    qDebug() << "Error en el server" << socketError;
}


void ServerTcp::displayError(QAbstractSocket::SocketError socketError)  {

}

/**
 * @brief ServerTcp::enviarAlSerial
 * @param cadena puede ser:
 *      "<1,2,255>"      "atras robot"
 *      "<1,1,255>"      "adelante robot"
 *      "<1,3,255>"      "derecha robot"
 *      "<1,4,255>"      "izquierda robot"
 *      "<1,0,255>"      "detener robot"
 *      "<2,2,255>"      "arriba camara"
 *      "<2,1,255>"      "abajo camara"
 *      "<2,4,255>"      "derecha camara"
 *      "<2,3,255>"      "izquierda camara"
 */
void ServerTcp::enviarAlSerial( const char * cadena )
{
    serialPuts( idPuerto, cadena );
}




#endif // RASPBERRY
