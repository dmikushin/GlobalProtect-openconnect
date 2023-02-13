#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

#include "challengedialog_gui.h"
#include "ui_challengedialog_gui.h"

using namespace gp::gui;

ChallengeDialog::ChallengeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChallengeDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
}

ChallengeDialog::~ChallengeDialog()
{
    delete ui;
}

void ChallengeDialog::setMessage(const QString &message)
{
    ui->challengeMessage->setText(message);
}

const QString ChallengeDialog::getChallenge()
{
    return ui->challengeInput->text();
}

void ChallengeDialog::on_challengeInput_textChanged(const QString &value)
{
    QPushButton *okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (value.isEmpty()) {
        okBtn->setDisabled(true);
    } else {
        okBtn->setEnabled(true);
    }
}
