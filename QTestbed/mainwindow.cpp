#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    removeToolBar(ui->mainToolBar);

    //WARNING: there are performance problems with the subclassed QGraphicsView (QBox2DView)
    //FIXME: flickering
    //FIXME: some object disappears when goes outside the sceneRect and should return after
    //FIXME: more problems!!!
    q_view = new QBox2DView;
    setCentralWidget(q_view);
    q_world = (QBox2DWorld*)q_view->scene();
    generateWorld(ui->testComboBox->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testComboBox_currentIndexChanged(int index)
{
   generateWorld(index);
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

void MainWindow::generateWorld(int index)
{
    if (q_world != NULL)
        q_world->deleteLater();
    b2Vec2 gravity(0.0f, -10.0f);
    switch (index) {
    case 0:
    {
        q_view->setText("Varying Friction");
        VaryingFriction *varFrict = new VaryingFriction(gravity);
        q_world = (QBox2DWorld*)varFrict;
    } break;
    case 1:
    {
        q_view->setText("Tiles");
        Tiles *tiles = new Tiles(gravity);
        q_world = (QBox2DWorld*)tiles;
    } break;
    case 2:
    {
        q_view->setText("Varying Restitution");
        VaryingRestitution *varRest = new VaryingRestitution(gravity);
        q_world = (QBox2DWorld*)varRest;
    } break;
    case 3:
    {
        q_view->setText("Gears");
        Gears *gears = new Gears(gravity);
        q_world = (QBox2DWorld*)gears;
    } break;
    case 4:
    {
        q_view->setText("Cantilever\n"
                        "This tests various character collision shapes.\n"
                        "Limitation: square and hexagon can snag on aligned boxes.\n"
                        "Feature: edge chains have smooth collision inside and out.");
        CharacterCollision *charColl = new CharacterCollision(gravity);
        q_world = (QBox2DWorld*)charColl;
    } break;
    case 5:
    {
        q_view->setText("Cantilever");
        Cantilever *cantilever = new Cantilever(gravity);
        q_world = (QBox2DWorld*)cantilever;
    } break;
    case 6:
    {
        q_view->setText("Theo Jansen's Walker\n"
                        "Keys: left = a, brake = s, right = d, toggle motor = m");
        TheoJansen *theoJansen = new TheoJansen(gravity);
        q_world = (QBox2DWorld*)theoJansen;
    } break;
    case 7:
    {
        q_view->setText("Bullet Test");
        BulletTest *bulletTest = new BulletTest(gravity);
        q_world = (QBox2DWorld*)bulletTest;
    } break;
    case 8:
    {
        q_view->setText("Tumbler");
        Tumbler *tumbler = new Tumbler(gravity);
        q_world = (QBox2DWorld*)tumbler;
    } break;
    case 9:
    {
        q_view->setText("Car\n"
                        "Keys: left = a, brake = s, right = d, hz down = q, hz up = e");
        Car *car = new Car(gravity);
        q_world = (QBox2DWorld*)car;
    } break;
    case 10:
    {
        q_view->setText("Vertical Stack\n"
                        "Press: (,) to launch a bullet.");
        VerticalStack *vStack = new VerticalStack(gravity);
        q_world = (QBox2DWorld*)vStack;
    } break;
    case 11:
    {
        q_view->setText("Web\n"
        //"Press: (b) to delete a body, (j) to delete a joint");
        "Press: (j) to delete a joint");
        Web *web = new Web(gravity);
        q_world = (QBox2DWorld*)web;
    } break;
    case 12:
    {
        q_view->setText("Shape Editing\n"
        "Press: (c) create a shape, (d) destroy a shape");
        ShapeEditing *shapeEdit = new ShapeEditing(gravity);
        q_world = (QBox2DWorld*)shapeEdit;
    } break;
    default:
        break;
    }
    q_world->setSceneRect(-10000, -10000, 20000, 20000);
    q_view->setScene(q_world);
    q_view->setFocus();
    q_world->setWarmStarting(ui->warmStartingCheckBox->isChecked());
    q_world->setSubStepping(ui->subSteppingCheckBox->isChecked());
    q_world->setVelocityIterations(ui->velSpinBox->value());
    q_world->setPositionIterations(ui->posSpinBox->value());
    q_world->setTimeStep(1/ui->hertzDoubleSpinBox->value());
    q_world->start();
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if (ui->testComboBox->currentIndex() == 6)
    {
        TheoJansen* theoJansen = dynamic_cast<TheoJansen*>(q_world);
        if (!theoJansen)
            return;
        switch (ev->key())
        {
        case Qt::Key_A:
            theoJansen->setMotorSpeed(-theoJansen->getMotorSpeed());
            break;
        case Qt::Key_S:
            theoJansen->setMotorSpeed(0.0f);
            break;
        case Qt::Key_D:
            theoJansen->setMotorSpeed(theoJansen->getMotorSpeed());
            break;
        case Qt::Key_M:
            theoJansen->setToggleMotor();
            break;
        }
    } else if(ui->testComboBox->currentIndex() == 9) {
        Car* car = dynamic_cast<Car*>(q_world);
        if (!car)
            return;
        switch (ev->key())
        {
        case Qt::Key_A:
            car->setMotorSpeed(car->getMotorSpeed());
            break;

        case Qt::Key_S:
            car->setMotorSpeed(0.0f);
            break;

        case Qt::Key_D:
            car->setMotorSpeed(-car->getMotorSpeed());
            break;

        case Qt::Key_Q:
        {
            float32 freq = car->getSpringFrequencyHz();
            freq = b2Max(0.0f, freq - 1.0f);
            car->setSpringFrequencyHz(freq);
         } break;

        case Qt::Key_E:
        {
            float32 freq = car->getSpringFrequencyHz();
            freq += 1;
            car->setSpringFrequencyHz(freq);
        } break;
        }
    } else if(ui->testComboBox->currentIndex() == 10) {
        VerticalStack* vStack = dynamic_cast<VerticalStack*>(q_world);
        if (!vStack)
            return;
        switch (ev->key())
        {
        case Qt::Key_Comma:
            vStack->createBullet();
            break;
        }
    } else if(ui->testComboBox->currentIndex() == 11) {
        Web* web = dynamic_cast<Web*>(q_world);
        if (!web)
            return;
        switch (ev->key())
        {
        case Qt::Key_B:
            //FIXME: disabled on purpose, has some bugs
            //web->destroyABody();
            break;
        case Qt::Key_J:
            web->destroyAJoint();
            break;
        }
    } else if(ui->testComboBox->currentIndex() == 12) {
        ShapeEditing* shapeEdit = dynamic_cast<ShapeEditing*>(q_world);
        if (!shapeEdit)
            return;
        switch (ev->key())
        {
        case Qt::Key_C:
            shapeEdit->create();
            break;
        case Qt::Key_D:
            shapeEdit->destroy();
            break;
        case Qt::Key_S:
            shapeEdit->sensor();
            break;
        }
    }
}
