/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * Fenêtre principale
 * Au cas où, l'UI contient une barre de menu, une barre de status, une barre d'outils (cf QMainWindow).
 * Une zone est laissée libre à droite du Widget OpenGL pour mettre de futurs contrôles ou informations.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    connect ( ui->doubleSpinBoxU, SIGNAL(valueChanged(double)), this, SLOT(on_spinBoxU(double)) );
    connect ( ui->doubleSpinBoxV, SIGNAL(valueChanged(double)), this, SLOT(on_spinBoxV(double) ));

    connect ( ui->horizontalSliderU, SIGNAL(valueChanged(int)), this, SLOT(on_sliderU(int)) );
    connect ( ui->horizontalSliderV, SIGNAL(valueChanged(int)), this, SLOT(on_sliderV(int)) );
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_sliderU(int value)
{
    emit ui->openGLWidget->nbU_changed(value);
}

void MainWindow::on_sliderV(int value)
{
    emit ui->openGLWidget->nbV_changed(value);
}

void MainWindow::on_spinBoxU(double value)
{
    u = value;
    emit ui->openGLWidget->u_changed(u);
}

void MainWindow::on_spinBoxV(double value)
{
    v = value;
    emit ui->openGLWidget->v_changed(v);
}
