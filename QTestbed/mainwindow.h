#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qbox2dview.h"

#include <qbox2dbody.h>
#include <qbox2dworld.h>


#include "tests/varyingfriction.h"
#include "tests/tiles.h"
#include "tests/varyingrestitution.h"
#include "tests/gears.h"
#include "tests/charactercollision.h"
#include "tests/cantilever.h"
#include "tests/theojansen.h"
#include "tests/bullettest.h"
#include "tests/tumbler.h"
#include "tests/car.h"
#include "tests/verticalstack.h"
#include "tests/web.h"
#include "tests/shapeediting.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void generateWorld(int index);

    void on_testComboBox_currentIndexChanged(int index);

    void on_velSpinBox_valueChanged(int arg1);

    void on_posSpinBox_valueChanged(int arg1);

    void on_hertzDoubleSpinBox_valueChanged(double arg1);

    void on_pauseButton_clicked();

    void on_restartButton_clicked();

    void on_quitButton_clicked();

    void on_singleStepButton_clicked();

    void on_warmStartingCheckBox_clicked(bool checked);

    void on_subSteppingCheckBox_clicked(bool checked);

protected:
    void keyPressEvent(QKeyEvent *ev);
private:
    Ui::MainWindow *ui;
    QBox2DView* q_view;
    QBox2DWorld *q_world;
};

#endif // MAINWINDOW_H
