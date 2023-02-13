#ifndef CHALLENGEDIALOGGUI_H
#define CHALLENGEDIALOGGUI_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ChallengeDialog; }
QT_END_NAMESPACE

namespace gp {

namespace gui {

class ChallengeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChallengeDialog(QWidget *parent = nullptr);
    ~ChallengeDialog();
 
    void setMessage(const QString &message);
    const QString getChallenge();
 
private slots:
    void on_challengeInput_textChanged(const QString &arg1);
 
private:
    Ui::ChallengeDialog *ui;
};

} // namespace gui

} // namespace gp

#endif // CHALLENGEDIALOG_H
