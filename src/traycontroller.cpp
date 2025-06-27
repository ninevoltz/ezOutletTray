#include "traycontroller.h"
#include "settingsdialog.h"
#include <QSettings>
#include <QApplication>
#include <QIcon>
#include <QNetworkRequest>
#include <QUrl>
#include <QAuthenticator>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

TrayController::TrayController()
    : actionOn("Turn On", this),
      actionOff("Turn Off", this),
      actionSettings("Settings", this),
      actionQuit("Quit", this)
{
    trayIcon.setIcon(QIcon::fromTheme("network-wired"));
    trayIcon.setToolTip("ezOutlet5 Controller");

    loadSettings();

    menu.addAction(&actionOn);
    menu.addAction(&actionOff);
    menu.addAction(&actionSettings);
    menu.addSeparator();
    menu.addAction(&actionQuit);

    trayIcon.setContextMenu(&menu);

    connect(&actionOn, &QAction::triggered, this, &TrayController::turnOn);
    connect(&actionOff, &QAction::triggered, this, &TrayController::turnOff);
    connect(&actionSettings, &QAction::triggered, this, &TrayController::openSettings);
    connect(&actionQuit, &QAction::triggered, this, &TrayController::quit);
}

void TrayController::show() {
    trayIcon.show();
}

void TrayController::turnOn() {
    sendCommand(true);
}

void TrayController::turnOff() {
    sendCommand(false);
}

void TrayController::quit() {
    trayIcon.hide();
    QApplication::quit();
}

void TrayController::sendCommand(bool on) {
    QString urlStr =
        QString("http://%1/cgi-bin/control.cgi?user=%2&passwd=%3&target=1&control=%4")
            .arg(outletIp)
            .arg(username)
            .arg(password)
            .arg(on ? "1" : "0");

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString credentials = username + ":" + password;
    QByteArray base64 = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + base64);

    networkManager.get(request);
}

void TrayController::openSettings() {
    SettingsDialog dialog;
    dialog.setIp(outletIp);
    dialog.setUsername(username);
    dialog.setPassword(password);

    if (dialog.exec() == QDialog::Accepted) {
        outletIp = dialog.ip();
        username = dialog.username();
        password = dialog.password();
        saveSettings();
    }
}

void TrayController::loadSettings() {
    QSettings settings(QDir(QCoreApplication::applicationDirPath()).filePath("config.ini"),
                       QSettings::IniFormat);
    if (QFile::exists(settings.fileName())) {
        outletIp = settings.value("outletIp", outletIp).toString();
        username = settings.value("username", username).toString();
        password = settings.value("password", password).toString();
    }
}

void TrayController::saveSettings() {
    QSettings settings(QDir(QCoreApplication::applicationDirPath()).filePath("config.ini"),
                       QSettings::IniFormat);
    settings.setValue("outletIp", outletIp);
    settings.setValue("username", username);
    settings.setValue("password", password);
}
