#include "customtextedit.h"
#include "lcs.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <iostream>
#include <map>


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
    ui->textEditFile1->setIsLeft(true);
    ui->textEditFile1->setCursorCurPos(ui->file1_cursor_pos_text);
    ui->textEditFile2->setCursorCurPos(ui->file2_cursor_pos_text);
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

    applyRelationsToTextEdits();
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

    applyRelationsToTextEdits();
}

void MainWindow::applyRelationsToTextEdits(){
    if(file1 != "" && file2 != "")
    {
        QString textLeft = ui->textEditFile1->toPlainText();
        QString textRight = ui->textEditFile2->toPlainText();
        QStringList listLeft =  textLeft.split("\n");
        QStringList listRight = textRight.split("\n");
        std::map<int, std::pair<int,int>>map;
        Lcs l;
        l.initiate(textLeft, textRight);
        for(int i=0; i<listLeft.size();++i){
           std::pair<int, int> p = std::make_pair(l.getRelationTypeLeft(i),
                                                        l.getRelationIndexLeft(i));
           std::pair<int, std::pair<int,int>> ip = std::make_pair(i, p);
           map.insert(ip);
        }

        ui->textEditFile1->setRelationMap(map);


        Lcs r;
        r.initiate(textRight, textLeft);
        std::map<int, std::pair<int,int>>map2;

        for(int i=0; i<listLeft.size();++i){
           std::pair<int, int> p = std::make_pair(r.getRelationTypeRight(i),
                                                        r.getRelationIndexRight(i));
           std::pair<int, std::pair<int,int>> ip = std::make_pair(i, p);
           map2.insert(ip);
        }

        ui->textEditFile2->setRelationMap(map2);
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
