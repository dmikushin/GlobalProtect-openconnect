#ifndef ENHANCEDWEBVIEW_H
#define ENHANCEDWEBVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>

#include "cdpcommandmanager.h"

namespace gp {

namespace gui {

class EnhancedWebView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit EnhancedWebView(QWidget *parent = nullptr);

    void initialize();

signals:
    void responseReceived(QJsonObject params);

private slots:
    void onCDPReady();
    void onEventReceived(QString eventName, QJsonObject params);

private:
    CDPCommandManager *cdp { nullptr };
};

} // namespace gui

} // namespace gp

#endif // ENHANCEDWEBVIEW_H
