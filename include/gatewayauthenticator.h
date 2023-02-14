#ifndef GATEWAYAUTHENTICATOR_H
#define GATEWAYAUTHENTICATOR_H

#include <QtCore/QObject>

#include "standardloginwindow.h"
#include "challengedialog.h"
#include "loginparams.h"
#include "gatewayauthenticatorparams.h"
#include "preloginresponse.h"

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
    
    PreloginResponse preloginResponse;

    bool isAutoLogin{ false };

    StandardLoginWindow *standardLoginWindow { nullptr };
    ChallengeDialog *challengeDialog { nullptr };

    void login(const LoginParams& loginParams);
    void tryAutoLogin();
    void doAuth();
    void fetchConfig(QString username, QString password);
    void normalAuth();
    void samlAuth(QString samlMethod, QString samlRequest, QString preloginUrl = "");
    void showChallenge(const QString &responseText);
};

#endif // GATEWAYAUTHENTICATOR_H
