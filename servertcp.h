#ifndef SERVERTCP_H
#define SERVERTCP_H

#ifdef RASPBERRY

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <wiringSerial.h>



class ServerTcp : public QObject
{
    Q_OBJECT
public:
    explicit ServerTcp(QObject *parent = 0);



    int getPuerto() const;
    void setPuerto(int value);

private:
    QTcpServer * tcpServer;
    QTcpSocket * tcpServerConnection;
    int bytesWritten;
    int bytesReceived;

    int puerto;

    int idPuerto;

signals:
    /**
     * @brief signal_serverClosed Se emite cuando este server se cierra y deja de escuchar.
     * La idea es que se establezca una conexion TCP por cada mensaje enviado.
     * Emitimos esta senal para inmediatamente ponerlo a escuchar de nuevo.
     */
    void signal_serverClosed();

public slots:
    void iniciar();

private slots:
    void acceptConnection();
    void updateServerProgress();
    void displayError( QAbstractSocket::SocketError socketError);

};

#endif // RASPBERRY

#endif // SERVERTCP_H
