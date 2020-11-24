#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

    double u = 0;
    double v = 0;

private slots:
    void on_spinBoxU(double value);
    void on_spinBoxV(double value);
    void on_sliderU(int value);
    void on_sliderV(int value);
    void checkBox(bool value);
};

#endif // MAINWINDOW_H
