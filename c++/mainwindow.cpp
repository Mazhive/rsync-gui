#include "mainwindow.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QTabWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QStyle>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QDir>
#include "rsynccore.h"
#include "progressdialog.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), core(new RsyncCore(this)), diag(nullptr) {
    // Venster Instellingen
    setWindowTitle("RemotePull Pro - Rsync Manager");
    setMinimumSize(650, 600);
    setStyleSheet("background-color: #f5f5f5; color: #333;");

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    
    // 1. Menu aanmaken
    createMenus();

    QTabWidget *tabs = new QTabWidget();

    // --- TAB 1: BASIS OPTIES ---
    QWidget *baseTab = new QWidget();
    QGridLayout *baseGrid = new QGridLayout(baseTab);
    
    uIn = new QLineEdit(); 
    hIn = new QLineEdit(); 
    pIn = new QLineEdit(); 
    pIn->setEchoMode(QLineEdit::Password);
    
    lSrcIn = new QLineEdit();  
    rPathIn = new QLineEdit(); 
    lPathIn = new QLineEdit(); 
    extraIn = new QLineEdit(); 

    auto sectionStyle = "font-weight: bold; color: #555; margin-top: 10px;";
    
    QLabel *lblRemote = new QLabel("REMOTE CONFIGURATIE (SSH)");
    lblRemote->setStyleSheet(sectionStyle);
    baseGrid->addWidget(lblRemote, 0, 0, 1, 2);
    
    baseGrid->addWidget(new QLabel("Gebruiker:"), 1, 0); baseGrid->addWidget(uIn, 1, 1);
    baseGrid->addWidget(new QLabel("Server IP:"), 2, 0); baseGrid->addWidget(hIn, 2, 1);
    baseGrid->addWidget(new QLabel("Wachtwoord:"), 3, 0); baseGrid->addWidget(pIn, 3, 1);
    
    QLabel *lblPaths = new QLabel("BRON EN BESTEMMING");
    lblPaths->setStyleSheet(sectionStyle);
    baseGrid->addWidget(lblPaths, 4, 0, 1, 2);
    
    baseGrid->addWidget(new QLabel("Lokaal Bron Pad:"), 5, 0); baseGrid->addWidget(lSrcIn, 5, 1);
    baseGrid->addWidget(new QLabel("OF Remote Pad:"), 6, 0); baseGrid->addWidget(rPathIn, 6, 1);
    baseGrid->addWidget(new QLabel("Bestemming Pad (Doel):"), 7, 0); baseGrid->addWidget(lPathIn, 7, 1);
    
    tabs->addTab(baseTab, "Basis opties");

    // --- TAB 2: RSYNC OPTIES ---
    QWidget *optTab = new QWidget();
    QGridLayout *optGrid = new QGridLayout(optTab);

    chkArchive = new QCheckBox("Archive modus (-a)");
    chkArchive->setChecked(true); // Standaard AAN om "skipping directory" te voorkomen
    
    chkTime = new QCheckBox("Preserve time (-t)");
    chkOwner = new QCheckBox("Preserve owner (-o)");
    chkPerms = new QCheckBox("Preserve permissions (-p)");
    chkGroup = new QCheckBox("Preserve group (-g)");
    chkDelete = new QCheckBox("Delete on destination (--delete)");
    chkVerbose = new QCheckBox("Verbose (-v)");
    chkIgnoreExist = new QCheckBox("Ignore existing (--ignore-existing)");
    chkSkipNewer = new QCheckBox("Skip newer (-u)");
    chkNoFilesystem = new QCheckBox("Do not leave filesystem (-x)");
    chkProgress = new QCheckBox("Show transfer progress (--progress)");
    chkSizeOnly = new QCheckBox("Size only (--size-only)");
    chkDryRun = new QCheckBox("Simulation (--dry-run)");

    optGrid->addWidget(chkArchive, 0, 0);   optGrid->addWidget(chkDelete, 0, 1);
    optGrid->addWidget(chkTime, 1, 0);      optGrid->addWidget(chkOwner, 1, 1);
    optGrid->addWidget(chkPerms, 2, 0);     optGrid->addWidget(chkGroup, 2, 1);
    optGrid->addWidget(chkVerbose, 3, 0);   optGrid->addWidget(chkIgnoreExist, 3, 1);
    optGrid->addWidget(chkSkipNewer, 4, 0); optGrid->addWidget(chkNoFilesystem, 4, 1);
    optGrid->addWidget(chkProgress, 5, 0);  optGrid->addWidget(chkSizeOnly, 5, 1);
    optGrid->addWidget(chkDryRun, 6, 0);
    
    tabs->addTab(optTab, "Rsync opties");

    // --- TAB 3: EXTRA PARAMETERS ---
    QWidget *extraTab = new QWidget();
    QVBoxLayout *extraLay = new QVBoxLayout(extraTab);
    extraLay->addWidget(new QLabel("Handmatige extra parameters:"));
    extraLay->addWidget(extraIn);
    extraLay->addStretch();
    tabs->addTab(extraTab, "Extra opties");

    mainLay->addWidget(tabs);

    // Grote Play Button
    QToolButton *playBtn = new QToolButton();
    playBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playBtn->setIconSize(QSize(64, 64));
    playBtn->setStyleSheet("border: 1px solid #ccc; border-radius: 10px; background: #fff;");
    connect(playBtn, &QToolButton::clicked, this, &MainWindow::onPlayClicked);
    mainLay->addWidget(playBtn, 0, Qt::AlignCenter);

    connect(core, &RsyncCore::finished, this, &MainWindow::handleFinished);
}

void MainWindow::createMenus() {
    QMenuBar *mBar = new QMenuBar(this);
    QMenu *fileMenu = mBar->addMenu("&File");

    QAction *actSrc = new QAction("Browse Source", this);
    actSrc->setShortcut(QKeySequence("Ctrl+S"));
    connect(actSrc, &QAction::triggered, this, &MainWindow::browseSource);
    fileMenu->addAction(actSrc);

    QAction *actDst = new QAction("Browse Destination", this);
    actDst->setShortcut(QKeySequence("Ctrl+D"));
    connect(actDst, &QAction::triggered, this, &MainWindow::browseDestination);
    fileMenu->addAction(actDst);

    fileMenu->addSeparator();

    QAction *actSim = new QAction("Simulation", this);
    actSim->setShortcut(QKeySequence("Alt+S"));
    connect(actSim, &QAction::triggered, [this](){ chkDryRun->setChecked(true); onPlayClicked(); });
    fileMenu->addAction(actSim);

    QAction *actCmd = new QAction("Rsync Command Line", this);
    actCmd->setShortcut(QKeySequence("Alt+R"));
    connect(actCmd, &QAction::triggered, this, &MainWindow::showRsyncCommand);
    fileMenu->addAction(actCmd);

    fileMenu->addSeparator();

    QAction *actQuit = new QAction("Quit", this);
    actQuit->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actQuit, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(actQuit);

    layout()->setMenuBar(mBar);
}

void MainWindow::browseSource() {
    QString d = QFileDialog::getExistingDirectory(this, "Selecteer Bronmap", QDir::homePath());
    if(!d.isEmpty()) lSrcIn->setText(d);
}

void MainWindow::browseDestination() {
    QString d = QFileDialog::getExistingDirectory(this, "Selecteer Doelmap", QDir::homePath());
    if(!d.isEmpty()) lPathIn->setText(d);
}

void MainWindow::showRsyncCommand() {
    QString cmd = "rsync ";
    if(chkArchive->isChecked()) cmd += "-a ";
    if(chkVerbose->isChecked()) cmd += "-v ";
    if(chkProgress->isChecked()) cmd += "--progress ";
    
    QString source = lSrcIn->text().isEmpty() ? QString("%1@%2:%3").arg(uIn->text(), hIn->text(), rPathIn->text()) : lSrcIn->text();
    cmd += QString("%1 %2").arg(source, lPathIn->text());
    
    QMessageBox::information(this, "Rsync Commando Preview", cmd);
}

void MainWindow::onPlayClicked() {
    QString source;
    bool isRemote = false;

    // 1. Bron bepalen
    if (!lSrcIn->text().isEmpty()) {
        source = lSrcIn->text();
        isRemote = false;
    } else if (!rPathIn->text().isEmpty() && !hIn->text().isEmpty()) {
        source = QString("%1@%2:%3").arg(uIn->text(), hIn->text(), rPathIn->text());
        isRemote = true;
    } else {
        QMessageBox::warning(this, "Input Fout", "Geen bron opgegeven.");
        return;
    }

    if (lPathIn->text().isEmpty()) {
        QMessageBox::warning(this, "Input Fout", "Geen doelpad opgegeven.");
        return;
    }

    QStringList args;

    // 2. Wrapper bepalen (sshpass alleen bij remote)
    if (isRemote && !pIn->text().isEmpty()) {
        args << "sshpass" << "-p" << pIn->text() << "rsync";
    } else {
        args << "rsync";
    }

    // 3. Rsync vlaggen (Forceer -v en -P voor de GUI feedback)
    args << "--outbuf=L"; // Line buffering voor real-time output
    if(chkArchive->isChecked()) args << "-a";
    if(chkTime->isChecked()) args << "-t";
    if(chkOwner->isChecked()) args << "-o";
    if(chkPerms->isChecked()) args << "-p";
    if(chkGroup->isChecked()) args << "-g";
    if(chkDelete->isChecked()) args << "--delete";
    if(chkVerbose->isChecked() || true) args << "-v"; // Altijd verbose voor log
    if(chkProgress->isChecked() || true) args << "-P"; // Altijd progress voor balk
    if(chkIgnoreExist->isChecked()) args << "--ignore-existing";
    if(chkSkipNewer->isChecked()) args << "-u";
    if(chkNoFilesystem->isChecked()) args << "-x";
    if(chkSizeOnly->isChecked()) args << "--size-only";
    if(chkDryRun->isChecked()) args << "--dry-run";
    
    if(!extraIn->text().isEmpty()) {
        args << extraIn->text().split(" ", Qt::SkipEmptyParts);
    }

    // 4. SSH opties (alleen remote)
    if (isRemote) {
        args << "-e" << "ssh -o StrictHostKeyChecking=no";
    }

    // 5. Paden toevoegen
    args << source << lPathIn->text();

    // 6. Setup Progress Dialog
    if(diag) { diag->close(); delete diag; }
    diag = new ProgressDialog(this);
    diag->setAttribute(Qt::WA_DeleteOnClose, false);

    // VERBINDINGEN LEGGEN VOORDAT HET PROCES START
    connect(diag, &ProgressDialog::stopRequested, core, &RsyncCore::stop);
    connect(core, &RsyncCore::progressUpdated, diag, &ProgressDialog::updateStatus);
    connect(core, &RsyncCore::rawOutputReceived, diag, &ProgressDialog::addLog);
    
    diag->show();

    // 7. Start de motor
    core->startTransfer(args);
}

void MainWindow::handleFinished(int code) {
    if (diag) {
        diag->setFinished(code);
    }
}

void MainWindow::setExtraParams(QString p) {
    extraIn->setText(p);
}
