#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include "model.h"
#include <QtWidgets>
#include <iostream>
#include <sstream>
#include <QtOpenGL>
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions_1_5>

using namespace std;

Model model;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::on_xRotSlider_valueChanged(int value)
{
    ui->myGLWidget->setXRotation(value);
}

void MainWindow::on_yRotSlider_valueChanged(int value)
{
    ui->myGLWidget->setYRotation(value);
}

void MainWindow::on_zRotSlider_valueChanged(int value)
{
    ui->myGLWidget->setZRotation(value);
}

void MainWindow::on_pushButton_clicked()
{
    QString XMAX=ui->lineEdit->text();
    ui->myGLWidget->renderFromButton(XMAX);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    ui->plainTextEdit->clear();

    ui->plainTextEdit->document()->setPlainText("Anubhav");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->myGLWidget->clearScreen();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->myGLWidget->renderAll(-1);
}
