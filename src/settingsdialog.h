#pragma once

#include <QDialog>
#include <QLineEdit>

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    void setIp(const QString &ip);
    QString ip() const;

    void setUsername(const QString &username);
    QString username() const;

    void setPassword(const QString &password);
    QString password() const;

private:
    QLineEdit *ipEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
};
