#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void create_menubar();
    void newFile();
    void openFile();
    bool saveFile_menu();
    void nesto();
    bool saveFile(const QString &fileName);
    void Exit();
    void cut();
    void copy();
    void paste();
    void help();
    void loadFile(const QString &fileName);

    QString curFile;

private:
    Ui::MainWindow *ui;

    bool is_saved();
    void setCurrentFile (const QString &fileName);


};
#endif // MAINWINDOW_H