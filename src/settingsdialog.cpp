#include "settingsdialog.h"
#include <QDialogButtonBox>
#include <QFormLayout>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), ipEdit(new QLineEdit(this)), usernameEdit(new QLineEdit(this)),
      passwordEdit(new QLineEdit(this)) {
    passwordEdit->setEchoMode(QLineEdit::Password);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(tr("IP Address:"), ipEdit);
    layout->addRow(tr("Username:"), usernameEdit);
    layout->addRow(tr("Password:"), passwordEdit);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void SettingsDialog::setIp(const QString &ip) { ipEdit->setText(ip); }
QString SettingsDialog::ip() const { return ipEdit->text(); }

void SettingsDialog::setUsername(const QString &username) { usernameEdit->setText(username); }
QString SettingsDialog::username() const { return usernameEdit->text(); }

void SettingsDialog::setPassword(const QString &password) { passwordEdit->setText(password); }
QString SettingsDialog::password() const { return passwordEdit->text(); }

