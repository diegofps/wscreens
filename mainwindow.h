#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "anim.h"

#include <wup/wup.hpp>
#include <QMainWindow>
#include <QThread>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QRect * r, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Anim *anim;
};

#endif // MAINWINDOW_H
