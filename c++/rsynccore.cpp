#include "rsynccore.h"
#include <QRegularExpression>
#include <QDebug>

RsyncCore::RsyncCore(QObject *parent) : QObject(parent), process(new QProcess(this)) {
    // Verbind de output van het proces aan onze lees-functie
    connect(process, &QProcess::readyReadStandardOutput, this, &RsyncCore::readOutput);
    connect(process, &QProcess::readyReadStandardError, this, &RsyncCore::readOutput); // Ook fouten lezen!
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &RsyncCore::finished);
}

void RsyncCore::startTransfer(const QStringList &args) {
    if (args.isEmpty()) return;

    // Belangrijk: we voegen het proceskanaal samen om alles te vangen
    process->setProcessChannelMode(QProcess::MergedChannels);
    
    // We splitsen sshpass en rsync correct voor QProcess
    QString program = args.first();
    QStringList arguments = args.mid(1);

    process->start(program, arguments);
}

void RsyncCore::readOutput() {
    // Lees alle beschikbare data
    QByteArray data = process->readAllStandardOutput();
    QString output = QString::fromUtf8(data);
    
    // Splits op regels (werkt ook met \r voor rsync progressie)
    QStringList lines = output.split(QRegularExpression("[\r\n]"), Qt::SkipEmptyParts);

    for (const QString &line : lines) {
        QString trimmedLine = line.trimmed();
        if (trimmedLine.isEmpty()) continue;

        emit rawOutputReceived(trimmedLine); // Dit vult je details-venster
        
        // Regex voor rsync progressie (bijv: 45%  1.23MB/s  0:00:05)
        if (trimmedLine.contains("%")) {
            QRegularExpression re("(\\d+)%.*?(\\d+\\.\\d+\\w+/s).*?(\\d+:\\d+:\\d+)");
            auto match = re.match(trimmedLine);
            if (match.hasMatch()) {
                emit progressUpdated(match.captured(1).toInt(), match.captured(2), match.captured(3));
            }
        }
    }
}

void RsyncCore::stop() {
    if (process->state() == QProcess::Running) {
        process->terminate();
        if (!process->waitForFinished(2000)) process->kill();
    }
}
