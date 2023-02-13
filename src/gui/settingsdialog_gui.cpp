#include "settingsdialog_gui.h"
#include "ui_settingsdialog_gui.h"

using namespace gp::gui;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setExtraArgs(QString extraArgs)
{
    ui->extraArgsInput->setPlainText(extraArgs);
}

QString SettingsDialog::extraArgs()
{
    return ui->extraArgsInput->toPlainText().trimmed();
}

void SettingsDialog::setClientos(QString clientos)
{
    ui->clientosInput->setText(clientos);
}

QString SettingsDialog::clientos()
{
    return ui->clientosInput->text();
}

void SettingsDialog::setOsVersion(QString osVersion) {
    ui->osVersionInput->setText(osVersion);
}

QString SettingsDialog::osVersion() {
    return ui->osVersionInput->text();
}
