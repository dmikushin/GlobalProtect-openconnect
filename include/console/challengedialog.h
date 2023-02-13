#ifndef CHALLENGEDIALOG_H
#define CHALLENGEDIALOG_H

#include <QObject>

namespace gp {

class ChallengeDialog : public QObject
{
    Q_OBJECT

public:

    virtual void setMessage(const QString &message);
    virtual const QString getChallenge();

    virtual void close();
    virtual void show();

signals:

    void accepted();
    void rejected();
    void finished();
};

} // namespace gp

#endif // CHALLENGEDIALOG_H
