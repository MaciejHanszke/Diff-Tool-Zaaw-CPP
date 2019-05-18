#include "customtextedit.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *window = new QWidget();
    CustomTextEdit editor;
    window->setLayout(ui->horizontalLayout);
    setCentralWidget(window);
    QMainWindow::showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadFile1Button_clicked()
{
    MainWindow::on_actionLoad_File_1_triggered();
}

void MainWindow::on_loadFile2Button_clicked()
{
    MainWindow::on_actionLoad_File_2_triggered();
}

void MainWindow::on_saveFile1Button_clicked()
{
    MainWindow::on_actionSave_File_1_triggered();
}

void MainWindow::on_saveFile2Button_clicked()
{
    MainWindow::on_actionSave_File_2_triggered();
}

void MainWindow::on_actionLoad_File_1_triggered()
{
    if(loadFileToTextEdit(file1, ui->file1_Name, ui->textEditFile1))
        if(!ui->actionSave_File_1->isEnabled())
            {
                ui->actionSave_File_1->setEnabled(true);
                ui->saveFile1Button->setEnabled(true);
                ui->textEditFile1->setEnabled(true);
            }

    //TODO podswietl text tam gdzie zostal zmodyfikowany
        //setPosition ewidentnie lapie po numerze

        QTextDocument *doc = ui->textEditFile1->document();
        std::vector<std::pair<int, bool>> dane;
            dane.push_back( std::pair<int, bool>(1,true) );
            dane.push_back( std::pair<int, bool>(5,false) );
            dane.push_back( std::pair<int, bool>(10,true) );
        colorSpecificLines(doc, dane);

}

void MainWindow::on_actionLoad_File_2_triggered()
{
    if(loadFileToTextEdit(file2, ui->file2_Name, ui->textEditFile2))
        if(!ui->actionSave_File_2->isEnabled())
            {
                ui->actionSave_File_2->setEnabled(true);
                ui->saveFile2Button->setEnabled(true);
                ui->textEditFile2->setEnabled(true);
            }
}

void MainWindow::colorSpecificLines(QTextDocument *doc, std::vector<std::pair<int, bool>> linesToColour ){
    for(int i = 0; i< linesToColour.size(); i++)
    {
        QTextBlock block = doc->findBlockByNumber(linesToColour[i].first);
        if(block.blockNumber() != -1){
            QTextCursor cursor(block);

            QTextBlockFormat blockFormat = cursor.blockFormat();
            if(linesToColour[i].second)
                blockFormat.setBackground(QColor(158,255,158));
            else {
                blockFormat.setBackground(QColor(255,117,117));
            }
            cursor.setBlockFormat(blockFormat);


        }
    }
}

void MainWindow::on_actionSave_File_1_triggered()
{
    SaveFileFromTextEdit(file1, ui->textEditFile1);
}

void MainWindow::on_actionSave_File_2_triggered()
{
    SaveFileFromTextEdit(file2, ui->textEditFile2);
}


bool MainWindow::loadFileToTextEdit(QString & fileVar, QLineEdit * file_name_text_box, QPlainTextEdit * textEdit){
    QString filename = QFileDialog::getOpenFileName(this,"Select file");
    QFile file(filename);
    fileVar = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return false;
    }
    file_name_text_box->setText(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setPlainText(text);
    file.close();
    return true;
}

void MainWindow::SaveFileFromTextEdit(QString & fileVar, QPlainTextEdit * textEdit){
    QFile file(fileVar);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.close();

    QString notice = "File: \"";
    notice += fileVar;
    notice += "\" saved!";
    QMessageBox::warning(this, "Save file successful!", notice);
}

void MainWindow::SaveFileDialog(){
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEditFile3->toPlainText();
    out << text;
    file.close();
}




void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionSave_File_3_triggered()
{
    SaveFileDialog();
}
