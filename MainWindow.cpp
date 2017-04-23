#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene.loadFromFile("test_scene_four.rt");
}

void MainWindow::paintEvent(QPaintEvent *event){
    (void) event;
    QImage img(600, 400, QImage::Format_RGB32);

    QPainter painter(this);

    scene.fillImage(img, 2);

//    for (int i = 0; i < img.width(); ++i)
//        for (int j = 0; j < img.height(); ++j)
//            img.setPixelColor(i, j, QColor(255,
//              i * 255 / img.width() , j * 255 / img.height()));

    painter.drawImage(5, 5, img);
}

MainWindow::~MainWindow()
{
    delete ui;
}
