#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>

class ProgressDialog : public QDialog {
    Q_OBJECT
public:
    explicit ProgressDialog(QWidget *parent = nullptr);
    void updateStatus(int pct, QString speed, QString eta);
    void addLog(QString line);
    void setFinished(int code);

signals:
    void stopRequested();

private:
    QProgressBar *bar;
    QTextEdit *logArea;
    QLabel *statusLbl;
    QPushButton *closeBtn;
};

#endif
