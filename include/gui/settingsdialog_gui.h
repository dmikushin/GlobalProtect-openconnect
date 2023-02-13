#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class SettingsDialog;
}

namespace gp {

namespace gui {

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    void setExtraArgs(QString extraArgs);
    QString extraArgs();

    void setClientos(QString clientos);
    QString clientos();

    void setOsVersion(QString osVersion);
    QString osVersion();

private:
    Ui::SettingsDialog *ui;
};

} // namespace gui

} // namespace gp

#endif // SETTINGSDIALOG_H
