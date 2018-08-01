#include <QtGui>
#include<QWidget>
// nur notwendig, wenn Qt 5:
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include  <QDebug>
#include <QLCDNumber>
//Ende Qt 5
#include "meinwidget.h"

meinWidget::meinWidget(QWidget *parent):QWidget(parent)
{
    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    quit->setFocusPolicy(Qt::NoFocus);
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QPushButton *start = new QPushButton(tr("Start"));
    start->setFont(QFont("Times", 18, QFont::Bold));
    start->setFocusPolicy(Qt::NoFocus);
    connect(start, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *saver = new QPushButton(tr("Save Game"));
    saver->setFont(QFont("Times", 18, QFont::Bold));
    saver->setFocusPolicy(Qt::NoFocus);
    connect(saver, SIGNAL(clicked()), this, SLOT(saver()));

    QPushButton *loader = new QPushButton(tr("Load Game"));
    loader->setFont(QFont("Times", 18, QFont::Bold));
    loader->setFocusPolicy(Qt::NoFocus);
    connect(loader, SIGNAL(clicked()), this, SLOT(loader()));


    meinZeichenFeld=new zeichenFeld;

    QGridLayout *Layout = new QGridLayout;
    Layout->addWidget(start,0,0);
    Layout->addWidget(quit,3,0);
    Layout->addWidget(saver, 1,0);
    Layout->addWidget(loader, 2,0);

    Layout->addWidget(meinZeichenFeld,0,1,6,2);
    Layout->setColumnStretch(1,10);
    setLayout(Layout);

}

void meinWidget::saver(void){
    QFileDialog dialog(this);
    QString fileName;
    QFile file;
    dialog.setFileMode(QFileDialog::AnyFile);
    fileName= dialog.getOpenFileName(this, tr("Save as"), ".", tr("Gamefile(*.xml)"));
    if (fileName.isNull()==true){
        QMessageBox::warning(this, tr("Error"), tr("Nothing to save yet"), QMessageBox::Ok);

    }
    if (fileName.isNull()==false){
        file.setFileName(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                 tr("Diese Datei kann nicht verwendet werden: ")+fileName, QMessageBox::Ok);
        }
        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

void meinWidget::loader(void){
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName= dialog.getOpenFileName(this,
                                     tr("Speichern als"), ".", tr("Zeichnungen (*.xml)"));
    if (fileName.isNull()==false){
        file.setFileName(fileName);
        if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Diese Datei kann nicht geöffnet werden: ")+fileName, QMessageBox::Ok);
        }
        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}



void meinWidget::start(void)
{
    meinZeichenFeld->start();
}
