#include <QApplication>
#include "mainwindow.h"
#include "argumenthandler.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    ArgumentHandler handler(app);
    MainWindow w;
    
    if (!handler.getCombinedArgs().isEmpty()) {
        w.setExtraParams(handler.getCombinedArgs());
    }

    w.show();
    return app.exec();
}
