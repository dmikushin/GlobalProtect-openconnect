#include <QtCore/QVariantMap>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include "cdpcommand.h"

using namespace gp;

CDPCommand::CDPCommand(QObject *parent) : QObject(parent)
{
}

CDPCommand::CDPCommand(int id, QString cmd, QVariantMap& params) :
    QObject(nullptr),
    id(id),
    cmd(cmd),
    params(&params)
{
}

QByteArray CDPCommand::toJson()
{
    QVariantMap payloadMap;
    payloadMap["id"] = id;
    payloadMap["method"] = cmd;
    payloadMap["params"] = *params;

    QJsonObject payloadJsonObject = QJsonObject::fromVariantMap(payloadMap);
    QJsonDocument payloadJson(payloadJsonObject);

    return payloadJson.toJson();
}
