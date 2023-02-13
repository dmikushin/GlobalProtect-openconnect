#ifndef GPCLIENT_H
#define GPCLIENT_H

#include <QObject>

#include "portalconfigresponse.h"
#include "settingsdialog.h"
#include "vpn.h"
#include "gatewayauthenticator.h"

namespace gp {

class GPClient : public QMainWindow
{
    Q_OBJECT

public:
    GPClient(IVpn *vpn);

    void activate();
    void quit();

    QString portal() const;
    void portal(QString);

    GPGateway currentGateway() const;
    void setCurrentGateway(const GPGateway gateway);

    void doConnect();
    void reset();

private slots:
    void onSettingsButtonClicked();
    void onSettingsAccepted();

    void on_connectButton_clicked();
    void on_portalInput_returnPressed();
    void on_portalInput_editingFinished();

    void onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void onGatewayChanged(QAction *action);

    void onPortalSuccess(const PortalConfigResponse portalConfig, const QString region);
    void onPortalPreloginFail(const QString msg);
    void onPortalConfigFail(const QString msg);
    void onPortalFail(const QString &msg);

    void onGatewaySuccess(const QString &authCookie);
    void onGatewayFail(const QString &msg);

    void onVPNConnected();
    void onVPNDisconnected();
    void onVPNError(QString errorMessage);
    void onVPNLogAvailable(QString log);

private:
    enum class VpnStatus
    {
        disconnected,
        pending,
        connected
    };

    IVpn *vpn;

    bool isQuickConnect { false };
    bool isSwitchingGateway { false };
    PortalConfigResponse portalConfig;

    void setupSettings();

    void initSystemTrayIcon();
    void initVpnStatus();
    void populateGatewayMenu();
    void updateConnectionStatus(const VpnStatus &status);

    void portalLogin();
    void tryGatewayLogin();
    void gatewayLogin();

    bool connected() const;

    QList<GPGateway> allGateways() const;
    void setAllGateways(QList<GPGateway> gateways);
};

} // namespace gp

#endif // GPCLIENT_H
