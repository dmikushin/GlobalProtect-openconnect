#ifndef GLOBALPROTECTSERVICE_H
#define GLOBALPROTECTSERVICE_H

#include <QtCore/QObject>
#include <QtCore/QProcess>

#include "vpn.h"

static QList<QString> binaryPaths = QList<QString>() <<
    "/usr/local/bin/openconnect" <<
    "/usr/local/sbin/openconnect" <<
    "/usr/bin/openconnect" <<
    "/usr/sbin/openconnect" <<
    "/opt/bin/openconnect" <<
    "/opt/sbin/openconnect";

class GPService : public QObject, public IVpn
{
    Q_OBJECT
    Q_INTERFACES(IVpn)
public:
    explicit GPService(QObject *parent = nullptr);
    ~GPService();

    void quit();

    enum VpnStatus {
        VpnNotConnected,
        VpnConnecting,
        VpnConnected,
        VpnDisconnecting,
    };

signals:
    void connected();
    void disconnected();
    void error(QString errorMessage);
    void logAvailable(QString log);

public slots:
    void connect(const QString &server, const QString &username, const QString &passwd);
    void disconnect();
    int status();

private slots:
    void onProcessStarted();
    void onProcessError(QProcess::ProcessError error);
    void onProcessStdout();
    void onProcessStderr();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QProcess *openconnect;
    bool aboutToQuit = false;
    int vpnStatus = GPService::VpnNotConnected;

    void log(QString msg);
    bool isValidVersion(QString &bin);
    static QString findBinary();
    static QString extraOpenconnectArgs(const QString &gateway);
    static QStringList splitCommand(const QString &command);
};

#endif // GLOBALPROTECTSERVICE_H
