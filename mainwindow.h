#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SaveFileDialog();
    void colorSpecificLines(QTextDocument *doc, std::vector<std::pair<int, bool> > linesToColour);
private slots:
    bool loadFileToTextEdit(QString & fileVar, QLineEdit * file_name, QPlainTextEdit * textEdit);
    void SaveFileFromTextEdit(QString & fileVar, QPlainTextEdit * textEdit);

    void on_loadFile1Button_clicked();

    void on_loadFile2Button_clicked();

    void on_actionLoad_File_1_triggered();

    void on_actionLoad_File_2_triggered();

    void on_actionSave_File_1_triggered();

    void on_actionSave_File_2_triggered();

    void on_saveFile1Button_clicked();

    void on_saveFile2Button_clicked();

    void on_actionExit_triggered();

    void on_actionSave_File_3_triggered();

private:
    Ui::MainWindow *ui;
    QString file1 = "";
    QString file2 = "";
};

#endif // MAINWINDOW_H
