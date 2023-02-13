#ifndef STANDARDLOGINWINDOWGUI_H
#define STANDARDLOGINWINDOWGUI_H

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class StandardLoginWindow; }
QT_END_NAMESPACE

namespace gp {

namespace gui {

class StandardLoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StandardLoginWindow(const QString &portalAddress, const QString &labelUsername,
                                 const QString &labelPassword, const QString &authMessage);
 
    void setProcessing(bool isProcessing);
 
private slots:
 
    void on_loginButton_clicked();
 
signals:
 
    void performLogin(QString username, QString password);
 
private:
    Ui::StandardLoginWindow *ui;
 
    void closeEvent(QCloseEvent *event);
    void autocomplete();
};

} // namespace gui

} // namespace gp

#endif // STANDARDLOGINWINDOWGUI_H
