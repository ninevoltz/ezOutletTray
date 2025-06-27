#include <QApplication>
#include "traycontroller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Keep running even when dialogs are closed since the tray icon
    // is the primary interface
    app.setQuitOnLastWindowClosed(false);

    TrayController controller;
    controller.show();

    return app.exec();
}
