#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>

#include <QDesktopWidget>

#include <QApplication>
#include <QWidget>
#include <QPainter>

#include <QFile>
#include <QTextStream>

#include <QMovie>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *ep);

public slots:
    void Up();
    void Down();
    void Left();
    void Right();
    void restart();
    void check_wall();
    void check_pass();
    void next_level();
    void boom();

signals:
    void Up_signal();
    void Down_signal();
    void Left_signal();
    void Right_signal();
    void grade_signal();
    void check_wall_signal();
    void check_pass_signal();
    void boom_signal();

private:
    Ui::MainWindow *ui;

    int step_num = 0;
    int now_level = 0;

    int mapsize_m, mapsize_n;
    int map1[8][8];

    int person1_x;
    int person1_y;
    int person1_x_early;
    int person1_y_early;

    int box_x[8];
    int box_y[8];
    int box_x_early;
    int box_y_early;
    int box_num;

    int hidden_point_x;
    int hidden_point_y;
    int goto_x;
    int goto_y;

    int map_boom[8][8];
    int boom_num;

    bool choose_person;
    int num_person;

    QLabel* label = new QLabel(this);
    QMovie* movie = new QMovie(":/res/pass.gif");
};

#endif // MAINWINDOW_H
