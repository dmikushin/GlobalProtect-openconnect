#ifndef STANDARDLOGINWINDOW_H
#define STANDARDLOGINWINDOW_H

#include <QObject>

namespace gp {

class StandardLoginWindow : public QObject
{
    Q_OBJECT

public:

    explicit StandardLoginWindow(const QString &portalAddress, const QString &labelUsername,
                                 const QString &labelPassword, const QString &authMessage);

    virtual void setProcessing(bool isProcessing);

    virtual void close();
    virtual void show();

    virtual void performLogin(QString username, QString password);

signals:

    void accepted();
    void rejected();
    void finished();

protected:

    virtual void autocomplete();
};

} // namespace gp

#endif // STANDARDLOGINWINDOW_H
