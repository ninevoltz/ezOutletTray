#include "traycontroller.h"
#include <QApplication>
#include <QIcon>
#include <QNetworkRequest>
#include <QUrl>
#include <QAuthenticator>
#include <QTimer>

TrayController::TrayController()
    : actionOn("Turn On", this),
      actionOff("Turn Off", this),
      actionQuit("Quit", this)
{
    trayIcon.setIcon(QIcon::fromTheme("network-wired"));
    trayIcon.setToolTip("ezOutlet5 Controller");

    menu.addAction(&actionOn);
    menu.addAction(&actionOff);
    menu.addSeparator();
    menu.addAction(&actionQuit);

    trayIcon.setContextMenu(&menu);

    connect(&actionOn, &QAction::triggered, this, &TrayController::turnOn);
    connect(&actionOff, &QAction::triggered, this, &TrayController::turnOff);
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
    QString urlStr = QString("http://%1/cgi-bin/control.cgi?user=%2&passwd=%1&target=1&control=%3")
        .arg(outletIp)
        .arg(username)
        .arg(on ? "1" : "0");

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString credentials = username + ":" + password;
    QByteArray base64 = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + base64);

    networkManager.get(request);
}
