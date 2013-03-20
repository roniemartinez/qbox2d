#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setHidden(true);
    q_view = new QBox2DView;
    setCentralWidget(q_view);
    q_world = (QBox2DWorld*)q_view->scene();
    //FIXME: find another way to set currentIndexChange
    ui->testComboBox->setCurrentIndex(1);
    ui->testComboBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testComboBox_currentIndexChanged(int index)
{
    if (q_world != NULL)
        q_world->deleteLater();
    b2Vec2 gravity(0.0f, -10.0f);
    switch (index) {
    case 0:
    {
        VaryingFriction *varFrict = new VaryingFriction(gravity);
        q_world = (QBox2DWorld*)varFrict;
    } break;
    case 1:
    {
        Tiles *tiles = new Tiles(gravity);
        q_world = (QBox2DWorld*)tiles;
    } break;
    case 2:
    {
        VaryingRestitution *varRest = new VaryingRestitution(gravity);
        q_world = (QBox2DWorld*)varRest;
    } break;
    }
    q_view->setScene(q_world);
    q_world->setWarmStarting(ui->warmStartingCheckBox->isChecked());
    q_world->setSubStepping(ui->subSteppingCheckBox->isChecked());
    q_world->start();
}

void MainWindow::on_velSpinBox_valueChanged(int arg1)
{
    if (q_world != NULL)
        q_world->setVelocityIterations(arg1);
}

void MainWindow::on_posSpinBox_valueChanged(int arg1)
{
    if (q_world != NULL)
        q_world->setPositionIterations(arg1);
}

void MainWindow::on_hertzDoubleSpinBox_valueChanged(double arg1)
{
    if (q_world != NULL)
        q_world->setTimeStep(1/arg1);
}

void MainWindow::on_pauseButton_clicked()
{
    if (q_world != NULL) {
        if (q_world->isRunning()) {
            q_world->pause();
            ui->statusBar->showMessage("Paused...");
        } else {
            q_world->start();
            ui->statusBar->clearMessage();
        }
    }
}

void MainWindow::on_restartButton_clicked()
{
    int a = ui->testComboBox->currentIndex();
    ui->testComboBox->setCurrentIndex(a+1);
    ui->testComboBox->setCurrentIndex(a);
}

void MainWindow::on_quitButton_clicked()
{
    close();
}

void MainWindow::on_singleStepButton_clicked()
{
    q_world->step();
}

void MainWindow::on_warmStartingCheckBox_clicked(bool checked)
{
    if (q_world != NULL)
        q_world->setWarmStarting(checked);
}

void MainWindow::on_subSteppingCheckBox_clicked(bool checked)
{
    if (q_world != NULL)
        q_world->setSubStepping(checked);
}
