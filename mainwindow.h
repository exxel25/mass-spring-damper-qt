#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include "massspringdamper.h" // Wajib ada ini biar kenal class sebelah

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSimulation();
    void updateSimulation();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;

    // INI KUNCINYA: Kita daftarkan pointer 'system' di sini
    MassSpringDamper *system;
};

#endif // MAINWINDOW_H
