#include "progressdialog.h"
#include <QVBoxLayout>

ProgressDialog::ProgressDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Rsync Voortgang");
    resize(600, 400);
    setStyleSheet("background-color: #f0f0f0; color: #333;");

    QVBoxLayout *lay = new QVBoxLayout(this);
    
    statusLbl = new QLabel("Bezig met starten...");
    lay->addWidget(statusLbl);

    bar = new QProgressBar();
    bar->setRange(0, 100);
    lay->addWidget(bar);

    logArea = new QTextEdit();
    logArea->setReadOnly(true);
    logArea->setFontPointSize(9);
    logArea->setStyleSheet("background-color: #fff; border: 1px solid #ccc;");
    lay->addWidget(new QLabel("Details:"));
    lay->addWidget(logArea);

    closeBtn = new QPushButton("Afbreken");

    connect(closeBtn, &QPushButton::clicked, [this]() {
        if (closeBtn->text() == "Afbreken") {
            emit stopRequested();   // tijdens rsync
        } else {
            close();                // na afloop
        }
    });

    lay->addWidget(closeBtn);
} // <--- DIT HAAKJE MISTE

void ProgressDialog::updateStatus(int pct, QString speed, QString eta) {
    bar->setValue(pct);
    statusLbl->setText(QString("Voortgang: %1% | Snelheid: %2 | ETA: %3").arg(pct).arg(speed).arg(eta));
}

void ProgressDialog::addLog(QString line) {
    logArea->append(line);
}

void ProgressDialog::setFinished(int code) {
    closeBtn->setText("Sluiten");
    statusLbl->setText(
        code == 0 
        ? "Klaar: Succesvol voltooid!" 
        : "Klaar: Proces gestopt of fout."
    );
}
