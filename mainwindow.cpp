#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , system(nullptr)
{
    ui->setupUi(this);


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Setup Timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
}

MainWindow::~MainWindow()
{
    if (system) delete system; // Hapus sisa memory
    delete ui;
}

void MainWindow::startSimulation()
{

    double m = ui->lineEdit_m->text().toDouble();
    double k = ui->lineEdit_k->text().toDouble();
    double c = ui->lineEdit_c->text().toDouble();
    double x0 = ui->lineEdit_x0->text().toDouble();

    if (m <= 0) m = 1.0;


    if (system) delete system;
    system = new MassSpringDamper(m, k, c, x0);

    scene->clear();
    timer->start(20);
}

void MainWindow::updateSimulation()
{

    if (!system) return;

    // 1. Hitung Fisika
    system->update(0.02);
    double x = system->getPosition();


    scene->clear();


    scene->addLine(-200, -50, -200, 50, QPen(Qt::black, 3));
    scene->addLine(-250, 20, 300, 20, QPen(Qt::black, 1));


    double startX = -200;
    double endX = x * 100;
    int coils = 12;
    double step = (endX - startX) / coils;

    QPainterPath springPath;
    springPath.moveTo(startX, 0);

    for (int i = 0; i < coils; i++) {
        double currentX = startX + (i * step);
        double yOffset = (i % 2 == 0) ? -10 : 10;
        springPath.lineTo(currentX + step/2, yOffset);
        springPath.lineTo(currentX + step, 0);
    }
    scene->addPath(springPath, QPen(Qt::black, 1));


    scene->addRect(endX, -20, 40, 40, QPen(Qt::black), QBrush(Qt::blue));



    QGraphicsTextItem *textStatus = scene->addText("Status: " + system->getStatus());
    textStatus->setPos(-200, -120);
    textStatus->setDefaultTextColor(Qt::red);

    QGraphicsTextItem *textPos = scene->addText("Position: " + QString::number(x, 'f', 2));
    textPos->setPos(-200, -100);
}
