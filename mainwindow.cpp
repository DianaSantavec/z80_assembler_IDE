#include <QToolBar>
#include <QPlainTextEdit>
#include <QSaveFile>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <QCloseEvent>
#include <QShortcut>


#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_menubar();
    setupEditor();
    setCurrentFile(QString());

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::closeEvent (QCloseEvent *event){
    if (is_saved()){
        event->accept();
    }
    else {
        event->ignore();
    }
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

   QAction *save_as_action = new QAction(tr("&Save As..."), this);
   save_as_action->setShortcuts(QKeySequence::SaveAs);
   save_as_action->setStatusTip(tr("Save file as..."));
   connect(save_as_action,&QAction::triggered,this, &MainWindow::save_as);
   fileMenu->addAction(save_as_action);

   QAction *exit_action = new QAction(tr("&Quit"),this);
   exit_action->setShortcuts(QKeySequence::Quit);
   exit_action->setStatusTip(tr("Exit editor"));
   connect(exit_action,&QAction::triggered,this,&MainWindow::Exit);
   fileMenu->addAction(exit_action);

   QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

   QAction *undo_action = new QAction(tr("&Undo"),this);
   undo_action->setShortcuts(QKeySequence::Undo);
   undo_action->setStatusTip(tr("Undo changes"));
   connect(undo_action,&QAction::triggered, this, &MainWindow::undo);
   editMenu->addAction(undo_action);

   QAction *redo_action = new QAction(tr("&Redo"),this);
   redo_action->setShortcuts(QKeySequence::Redo);
   redo_action->setStatusTip(tr("Undo changes"));
   connect(redo_action,&QAction::triggered, this, &MainWindow::redo);
   editMenu->addAction(redo_action);

    QAction *cut_action = new QAction(tr("&Cut"), this);
    cut_action->setShortcuts(QKeySequence::Cut);
    cut_action->setStatusTip(tr("Create a new file"));
    connect(cut_action, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cut_action);

    QAction *copy_action = new QAction(tr("&Copy"), this);
    copy_action->setShortcuts(QKeySequence::Copy);
    copy_action->setStatusTip(tr("Copy"));
    connect(copy_action, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copy_action);

    QAction *paste_action = new QAction(tr("&Paste"), this);
    paste_action->setShortcuts(QKeySequence::Paste);
    paste_action->setStatusTip(tr("Create a new file"));
    connect(paste_action, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(paste_action);


    QMenu *assembleMenu = menuBar()->addMenu(tr("&Assemble"));

    QAction *assemble_action = new QAction(tr("&Assemble"), this);
    assemble_action->setShortcut(QKeySequence(Qt::Key_F5));
    assemble_action->setStatusTip(tr("Create a new file"));
    connect(assemble_action, &QAction::triggered, this, &MainWindow::assemble);
    assembleMenu->addAction(assemble_action);


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
    if (curent_file.isEmpty()){
       return save_as();
    }
    else {
        return saveFile(curent_file);
    }
}

bool MainWindow::save_as()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    QString file_path_string = dialog.selectedFiles().first();

    file_path = new char[file_path_string.length() + 1];
    strcpy(file_path, file_path_string.toLatin1().constData());

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
            errorMessage = tr("Cannot write file %1:\n%2.") .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    }
    else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.") .arg(QDir::toNativeSeparators(fileName), file.errorString());
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
    MainWindow::close();
}

void MainWindow::undo(){
    QWidget *focused = QApplication::focusWidget();
    QApplication::postEvent(focused,new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Z,Qt::ControlModifier));
    QApplication::postEvent(focused,new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Z,Qt::ControlModifier));
}

void MainWindow::redo(){
    QWidget *focused = QApplication::focusWidget();
    QApplication::postEvent(focused,new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Z,Qt::ShiftModifier | Qt::ControlModifier));
    QApplication::postEvent(focused,new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_Z,Qt::ShiftModifier | Qt::ControlModifier));
    //Qt::Modifier *modifiers =
    //QKeyEvent redo_event = new QKeyEvent(QEvent::KeyPress,Qt::Key_0,*modifiers);
    //QKeyEvent redo_event = new QKeyEvent();
    //QApplication::postEvent(focused,new QKeyEvent(redo_event));
    /*Qt::KeyboardModifier modifiers = new Qt::KeyboardModifiers(Qt::ControlModifier, Qt::AltModifier);
    QApplication::postEvent(focused,new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Z,Qt::ControlModifier,));*/
}

void MainWindow::cut(){
    QWidget* focused = QApplication::focusWidget();
    QApplication::postEvent( focused, new QKeyEvent( QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier ));
    QApplication::postEvent( focused, new QKeyEvent( QEvent::KeyRelease, Qt::Key_X, Qt::ControlModifier ));
}

void MainWindow::copy(){

    QWidget* focused = QApplication::focusWidget();
    QApplication::postEvent( focused, new QKeyEvent( QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier ));
    QApplication::postEvent( focused, new QKeyEvent( QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier ));
}

void MainWindow::paste(){
    QWidget* focused = QApplication::focusWidget();
    QApplication::postEvent( focused, new QKeyEvent( QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier ));
    QApplication::postEvent( focused, new QKeyEvent( QEvent::KeyRelease, Qt::Key_V, Qt::ControlModifier ));
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
            return saveFile(curent_file);
        case QMessageBox::Cancel:
            return false;
        default:
            break;
        }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName){
    curent_file = fileName;
    ui->mainTextEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curent_file;
    if (curent_file.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"), tr("Cannot read file %1:\n%2.") .arg(QDir::toNativeSeparators(fileName), file.errorString()));
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

void MainWindow::assemble(){
    assemble_function();
}

void MainWindow::assemble_function(){
    std::string bash_command = std::string() + "/home/dianas/Documents/z80IDE/assemble.sh " + file_path;
    const char *c_bash_command = bash_command.c_str();
    std::array<char,250> buffer;
    std::string errors_string;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(c_bash_command, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            errors_string += buffer.data();
        }

    QString error_string_qt = QString::fromStdString(errors_string);
    ui->errorTextEdit->setPlainText(error_string_qt);
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    ui->mainTextEdit->setFont(font);
    //editor = new QTextEdit;
    //editor->setFont(font);

    highlighter = new Highlighter(ui->mainTextEdit->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->mainTextEdit->setPlainText(file.readAll());
}
