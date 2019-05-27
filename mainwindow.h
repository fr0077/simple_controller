#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "../magmeasure/thk_actuator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void update();
    ~MainWindow();

private slots:

    void on_button_reset_error_clicked();

    void on_button_check_error_clicked();

    void on_button_servo_on_clicked();

    void on_button_write_clicked();

    void on_button_move_clicked();

    void on_button_zero_clicked();

    void on_init_clicked();

    void on_button_write_2_clicked();

    void on_get_pos_clicked();

private:
    Ui::MainWindow *ui;
    ThkActuator *actuator;
    Actuator::ActuatorAxis currentAxis = Actuator::ActuatorAxis::ACTUATOR_AXIS_X;
    Actuator::Direction currentDirection = Actuator::Direction::POSITIVE;
    int speed = 10;
    int dist = 10000;
    QListWidget *status;
};

#endif // MAINWINDOW_H
