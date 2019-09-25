#include "blink.h"
#include "ui_blink.h"

Blink::Blink(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Blink)
{
    ui->setupUi(this);
}

Blink::~Blink()
{
    delete ui;
}
