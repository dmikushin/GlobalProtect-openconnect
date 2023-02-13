#ifndef CDPCOMMAND_H
#define CDPCOMMAND_H

#include <QtCore/QObject>

namespace gp {

class CDPCommand : public QObject
{
    Q_OBJECT
public:
    explicit CDPCommand(QObject *parent = nullptr);
    CDPCommand(int id, QString cmd, QVariantMap& params);

    QByteArray toJson();

signals:
    void finished();

private:
    int id;
    QString cmd;
    QVariantMap *params;
};

} // namespace gp

#endif // CDPCOMMAND_H
