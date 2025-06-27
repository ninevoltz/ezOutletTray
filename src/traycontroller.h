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
    void openSettings();

private:
    void sendCommand(bool on);
    void loadSettings();
    void saveSettings();
    QString settingsFilePath() const;

    QSystemTrayIcon trayIcon;
    QMenu menu;
    QAction actionOn;
    QAction actionOff;
    QAction actionSettings;
    QAction actionQuit;

    QNetworkAccessManager networkManager;

    QString outletIp = "10.0.0.74";  // Default IP
    QString username = "admin";
    QString password = "127D17";
};
