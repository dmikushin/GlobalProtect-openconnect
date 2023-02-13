#ifndef VPN_H
#define VPN_H
#include <QtCore/QObject>
#include <QtCore/QString>

namespace gp {

class IVpn
{
public:
    virtual ~IVpn() = default;

    virtual void connect(const QString &server, const QString &username, const QString &passwd) = 0;
    virtual void disconnect() = 0;
    virtual int status() = 0;
};

} // namespace gp

#endif
