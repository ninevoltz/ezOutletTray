#include <QApplication>
#include "traycontroller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TrayController controller;
    controller.show();

    return app.exec();
}
