#ifndef GATEWAYAUTHENTICATOR_H
#define GATEWAYAUTHENTICATOR_H

#include <QtCore/QObject>

#include "loginparams.h"
#include "gatewayauthenticatorparams.h"

namespace gp {

namespace gui {

class StandardLoginWindow;
class ChallengeDialog;

class GatewayAuthenticator : public QObject
{
    Q_OBJECT
public:
    explicit GatewayAuthenticator(const QString &gateway, GatewayAuthenticatorParams params);

    void authenticate();

signals:
    void success(const QString &authCookie);
    void fail(const QString &msg = "");

private slots:
    void onLoginFinished();
    void onPreloginFinished();
    void onPerformStandardLogin(const QString &username, const QString &password);
    void onLoginWindowRejected();
    void onLoginWindowFinished();
    void onSAMLLoginSuccess(const QMap<QString, QString> &samlResult);
    void onSAMLLoginFail(const QString &code, const QString &msg);

private:
    QString gateway;
    GatewayAuthenticatorParams params;
    QString preloginUrl;
    QString loginUrl;
    
    StandardLoginWindow *standardLoginWindow { nullptr };
    ChallengeDialog *challengeDialog { nullptr };
    
    void login(const LoginParams& loginParams);
    void doAuth();
    void normalAuth(QString labelUsername, QString labelPassword, QString authMessage);
    void samlAuth(QString samlMethod, QString samlRequest, QString preloginUrl = "");
    void showChallenge(const QString &responseText);
};

} // namespace gui

} // namespace gp

#endif // GATEWAYAUTHENTICATOR_H
