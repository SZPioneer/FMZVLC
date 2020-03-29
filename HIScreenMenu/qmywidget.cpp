#include "qmywidget.h"
#include "xmlconfig.h"

QMyWidget::QMyWidget(QWidget *parent) : QWidget(parent)
{
    connect(XmlConfig::GetInstance(), SIGNAL(notifyWheel(QObject*,int)), this, SLOT(onWheel(QObject*,int)));
    connect(XmlConfig::GetInstance(), SIGNAL(notifyKeyEnter(QObject*)), this, SLOT(onKeyEnter(QObject*)));

}
