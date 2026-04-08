#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>

class QLineEdit;
class QCheckBox;
class QTabWidget;
class QAction;

class RsyncCore;
class ProgressDialog;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setExtraParams(QString p);

private slots:
    void onPlayClicked();
    void showRsyncCommand();
    void browseSource();
    void browseDestination();
    void handleFinished(int code);

private:
    void createMenus();

    // core
    RsyncCore *core;
    ProgressDialog *diag;

    // input velden
    QLineEdit *uIn;
    QLineEdit *hIn;
    QLineEdit *pIn;

    QLineEdit *lSrcIn;
    QLineEdit *rPathIn;
    QLineEdit *lPathIn;

    QLineEdit *extraIn;

    // checkboxes
    QCheckBox *chkTime;
    QCheckBox *chkOwner;
    QCheckBox *chkPerms;
    QCheckBox *chkGroup;
    QCheckBox *chkDelete;
    QCheckBox *chkVerbose;
    QCheckBox *chkIgnoreExist;
    QCheckBox *chkSkipNewer;
    QCheckBox *chkNoFilesystem;
    QCheckBox *chkProgress;
    QCheckBox *chkSizeOnly;
    QCheckBox *chkDryRun;
    QCheckBox *chkArchive;
};

#endif // MAINWINDOW_H
