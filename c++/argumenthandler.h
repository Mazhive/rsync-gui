#ifndef ARGUMENTHANDLER_H
#define ARGUMENTHANDLER_H

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QStringList>

class ArgumentHandler {
public:
    // We gebruiken QCoreApplication, dat is de 'vader' van QApplication
    // en voldoende voor de parser.
    explicit ArgumentHandler(const QCoreApplication &app);
    QString getCombinedArgs() const;

private:
    QString m_combinedArgs;
};

#endif
