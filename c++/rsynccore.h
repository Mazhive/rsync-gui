#ifndef RSYNCCORE_H
#define RSYNCCORE_H

#include <QObject>
#include <QProcess>

class RsyncCore : public QObject {
    Q_OBJECT
public:
    explicit RsyncCore(QObject *parent = nullptr);
    void startTransfer(const QStringList &args);
    void stop();

signals:
    void progressUpdated(int percent, QString speed, QString eta);
    void rawOutputReceived(QString line);
    void finished(int exitCode);

private slots:
    void readOutput();

private:
    QProcess *process;
};

#endif
