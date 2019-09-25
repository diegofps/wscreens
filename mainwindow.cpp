#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <wup/wup.hpp>
#include <QWindow>
#include <QScreen>
#include <QThread>
#include <QMutex>
#include <QStyle>

using namespace wup;

MainWindow::MainWindow(QRect * r, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, true);

    show();

    if (r != nullptr)
    {
        setGeometry(r->x(),r->y(),r->width(),r->height());
    }

    anim = new Anim(150, 15);
    QMutex * m = new QMutex();

    connect(anim, &Anim::update, [&](const double v)
    {
//        m->lock();
        int v2 = 128 - v * 128;
        QString tmp;
        tmp.setNum(v2, 16);

//        print("Progress", v, tmp);

        QString style;

        if (tmp.size() == 1)
            style = "background-color: #0" + tmp + "ffffff;";
        else
            style = "background-color: #" + tmp + "ffffff;";

//        print(style);

//        setStyleSheet(style);
        QMetaObject::invokeMethod(this, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, style));

//        m->unlock();
    });

    connect(anim, &Anim::finished, [&]()
    {
//        print("Finished");
//        delete m;
        close();
    });

    anim->start();
}

MainWindow::~MainWindow()
{
    anim->quit();
    anim->wait();
    delete ui;
}
