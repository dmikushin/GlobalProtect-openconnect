#ifndef SAMLLOGINWINDOW_H
#define SAMLLOGINWINDOW_H

#include <QObject>
#include <QtCore/QMap>

namespace gp {

class SAMLLoginWindow : public QObject
{
    Q_OBJECT

public:

    virtual void login(const QString samlMethod, const QString samlRequest, const QString preloginUrl);

    virtual void close();
    virtual void show();

    virtual void success(QMap<QString, QString> samlResult);
    virtual void fail(const QString code, const QString msg);

signals:

    void accepted();
    void rejected();
    void finished();

protected:
    static const auto MAX_WAIT_TIME { 10 * 1000 };

    bool failed { false };
    QMap<QString, QString> samlResult;

    virtual void handleHtml(const QString &html);

    static QString parseTag(const QString &tag, const QString &html);
};

} // namespace gp

#endif // SAMLLOGINWINDOW_H
