#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actuator = new ThkActuator(800,800,800);
    status = findChild<QListWidget *>("list_status");
}

void MainWindow::update(){
    QRadioButton *x = findChild<QRadioButton *>("radio_x");
    QRadioButton *y = findChild<QRadioButton *>("radio_y");
    QRadioButton *z = findChild<QRadioButton *>("radio_z");

    if(x->isChecked()){
        currentAxis = Actuator::ActuatorAxis::ACTUATOR_AXIS_X;
    }

    if(y->isChecked()){
        currentAxis = Actuator::ActuatorAxis::ACTUATOR_AXIS_Y;
    }

    if(z->isChecked()){
        currentAxis = Actuator::ActuatorAxis::ACTUATOR_AXIS_Z;
    }

    QLineEdit *e_speed = findChild<QLineEdit *>("edit_speed");
    speed = std::atoi(e_speed->text().toStdString().c_str());

    QLineEdit *e_dist = findChild<QLineEdit *>("edit_dist");

    dist = std::atoi(e_dist->text().toStdString().c_str());

    QRadioButton *pos = findChild<QRadioButton *>("radio_positive");
    QRadioButton *neg = findChild<QRadioButton *>("radio_negative");

    if(pos->isChecked()){
        currentDirection = Actuator::Direction::POSITIVE;
    }

    if(neg->isChecked()){
        currentDirection = Actuator::Direction::NEGATIVE;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_reset_error_clicked()
{
    update();
    Actuator::Actuator_Error_Type result = actuator->resetAlarm(currentAxis);
    status->addItem(QString::fromStdString("Reset error " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));
    status->scrollToBottom();
}

void MainWindow::on_button_check_error_clicked()
{
    update();
    Actuator::ActuatorResponse response = actuator->getAlarm(currentAxis);

    status->addItem(QString::fromStdString("Check error " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(response.errType)));
    status->scrollToBottom();

    QLabel *error_label = findChild<QLabel *>("label_error");
    error_label->setText(QString::fromStdString(response.response.at(0)));
}

void MainWindow::on_button_servo_on_clicked()
{
    update();
    Actuator::Actuator_Error_Type result = actuator->servoOn(currentAxis);
    status->addItem(QString::fromStdString("Servo on " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));
    status->scrollToBottom();
}

void MainWindow::on_button_write_clicked()
{
    update();
    actuator->getCurrentPosition(currentAxis);
    Actuator::Actuator_Error_Type result = actuator->setSpeed(currentAxis, speed);
    status->addItem(QString::fromStdString("setSpeed " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));


    usleep(500000);

    result = actuator->setDistance(currentAxis, dist);
    status->addItem(QString::fromStdString("setDistance " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));
    status->scrollToBottom();
}

void MainWindow::on_button_move_clicked()
{
    update();
    Actuator::Actuator_Error_Type result =  actuator->move(currentAxis, currentDirection);
    status->addItem(QString::fromStdString("move " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));
    status->scrollToBottom();
}

void MainWindow::on_button_zero_clicked()
{
    update();
    Actuator::Actuator_Error_Type result =  actuator->zero(currentAxis);
    status->addItem(QString::fromStdString("zero " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));
    status->scrollToBottom();
}

void MainWindow::on_init_clicked()
{
    update();
    Actuator::Actuator_Error_Type result =  actuator->init(currentAxis);
    status->addItem(QString::fromStdString("init " + Actuator::axis_toString(currentAxis) + " " + Actuator::error_toString(result)));
    status->scrollToBottom();
}
