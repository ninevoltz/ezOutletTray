#pragma once

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class TrayController : public QObject {
    Q_OBJECT

public:
    TrayController();
    void show();

private slots:
    void turnOn();
    void turnOff();
    void quit();

private:
    void sendCommand(bool on);

    QSystemTrayIcon trayIcon;
    QMenu menu;
    QAction actionOn;
    QAction actionOff;
    QAction actionQuit;

    QNetworkAccessManager networkManager;

    const QString outletIp = "10.0.0.74";  // Replace with your ezOutlet5 IP
    const QString username = "admin";
    const QString password = "127D17";
};
