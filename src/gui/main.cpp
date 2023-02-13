#include <QCommandLineParser>
#include <QObject>
#include <QString>
#include <QStandardPaths>
#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "singleapplication.h"
#include "gpclient_gui.h"
#include "sigwatch.h"
#include "version.h"
#include "gpservice.h"

#define QT_AUTO_SCREEN_SCALE_FACTOR "QT_AUTO_SCREEN_SCALE_FACTOR"

using namespace gp;
using namespace gp::gui;

int main(int argc, char *argv[])
{
    plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender(plog::streamStdErr);
    plog::init(plog::debug, &consoleAppender);

    LOGI << "GlobalProtect started, version: " << VERSION;

    auto port = QString::fromLocal8Bit(qgetenv(ENV_CDP_PORT));
    auto hidpiSupport = QString::fromLocal8Bit(qgetenv(QT_AUTO_SCREEN_SCALE_FACTOR));

    if (port.isEmpty()) {
        qputenv(ENV_CDP_PORT, "12315");
    }

    if (hidpiSupport.isEmpty()) {
        qputenv(QT_AUTO_SCREEN_SCALE_FACTOR, "1");
    }

    SingleApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("server", "The URL of the VPN server. Optional.");
    parser.addPositionalArgument("gateway", "The URL of the specific VPN gateway. Optional.");
    parser.addOptions({
      {"now", "Do not show the dialog with the connect button; connect immediately instead."},
      {"start-minimized", "Launch the client minimized."},
      {"reset", "Reset the client's settings."},
    });
    parser.process(app);

    const auto positional = parser.positionalArguments();

    GPService service;

    UnixSignalWatcher sigwatch;
    sigwatch.watchForSignal(SIGINT);
    sigwatch.watchForSignal(SIGTERM);
    sigwatch.watchForSignal(SIGQUIT);
    sigwatch.watchForSignal(SIGHUP);
    QObject::connect(&sigwatch, &UnixSignalWatcher::unixSignal, &service, &GPService::quit);

    auto *vpn = static_cast<IVpn*>(&service);
    GPClient w(nullptr, vpn);

    if (positional.size() > 0) {
      w.portal(positional.at(0));
    }
    if (positional.size() > 1) {
      GPGateway gw;
      gw.setName(positional.at(1));
      gw.setAddress(positional.at(1));
      w.setCurrentGateway(gw);
    }

    QObject::connect(&app, &SingleApplication::instanceStarted, &w, &GPClient::activate);

    QObject::connect(&sigwatch, &UnixSignalWatcher::unixSignal, &w, &GPClient::quit);

    if (parser.isSet("reset")) {
        w.reset();
    }

    if (parser.isSet("now")) {
      w.doConnect();
    } else if (parser.isSet("start-minimized")) {
      w.showMinimized();
    } else {
      w.show();
    }

    return app.exec();
}

