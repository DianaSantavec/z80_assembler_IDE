#include <QToolBar>
#include <QPlainTextEdit>
#include <QSaveFile>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_menubar();

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::create_menubar(){
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *new_action = new QAction(tr("&New"), this);
    new_action->setShortcuts(QKeySequence::New);
    new_action->setStatusTip(tr("Create a new file"));
    connect(new_action, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(new_action);

    QAction *open_action = new QAction(tr("&Open"), this);
    open_action->setShortcuts(QKeySequence::Open);
    open_action->setStatusTip(tr("Open a existing file"));
    connect(open_action, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(open_action);

   QAction *save_action = new QAction(tr("&Save"), this);
   save_action->setShortcuts(QKeySequence::Save);
   save_action->setStatusTip(tr("Save file"));
   connect(save_action,&QAction::triggered,this, &MainWindow::saveFile_menu);
   fileMenu->addAction(save_action);

    QAction *exit_action = new QAction(tr("&Quit"),this);
    exit_action->setShortcuts(QKeySequence::Quit);
    exit_action->setStatusTip(tr("Exit"));
    connect(exit_action, &QAction::trigger,this,&MainWindow::Exit);
    fileMenu->addAction(exit_action);


    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    QAction *cut_action = new QAction(tr("&Cut"), this);
    cut_action->setShortcuts(QKeySequence::Cut);
    cut_action->setStatusTip(tr("Create a new file"));
    connect(cut_action, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cut_action);

    QAction *copy_action = new QAction(tr("&Copy"), this);
    copy_action->setShortcuts(QKeySequence::Copy);
    copy_action->setStatusTip(tr("Copy"));
    connect(cut_action, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copy_action);

    QAction *paste_action = new QAction(tr("&Paste"), this);
    paste_action->setShortcuts(QKeySequence::Paste);
    paste_action->setStatusTip(tr("Create a new file"));
    connect(paste_action, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(paste_action);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&About"));

    QAction *help_action = new QAction(tr("&Help"), this);
    help_action->setShortcuts(QKeySequence::HelpContents);
    help_action->setStatusTip(tr("Create a new file"));
    connect(help_action, &QAction::triggered, this, &MainWindow::help);
    aboutMenu->addAction(help_action);
}

void MainWindow::newFile(){
     if (is_saved()) {
         ui->mainTextEdit->clear();
         setCurrentFile(QString());
     }
}

void MainWindow::openFile(){
    if (is_saved()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()){
            loadFile(fileName);
        }
    }
}

bool MainWindow::saveFile_menu(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();

    QFileDialog dialog(this);
        dialog.setWindowModality(Qt::WindowModal);
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        if (dialog.exec() != QDialog::Accepted)
            return false;
        return saveFile(dialog.selectedFiles().first());
}

bool MainWindow::saveFile(const QString &fileName){

    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << ui->mainTextEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                    .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    }
    else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }

    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::Exit(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void MainWindow::cut(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void MainWindow::copy(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void MainWindow::paste(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void MainWindow::help(){
    QMessageBox msgBox;
    msgBox.setText("You'll have to ask me over the messenger :)");
    msgBox.exec();
}

bool MainWindow::is_saved(){
    if (!ui->mainTextEdit->document()->isModified()){
        return true;
    }

    const QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Warrning"),tr("The document has been modified\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    switch (ret) {
        case QMessageBox::Save:
            return saveFile(curFile);
        case QMessageBox::Cancel:
            return false;
        default:
            break;
        }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName){
    curFile = fileName;
    ui->mainTextEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    ui->mainTextEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}
