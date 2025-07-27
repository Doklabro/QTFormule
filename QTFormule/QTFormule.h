#pragma once

#include <QtWidgets/QWidget>
#include "ui_QTFormule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QTFormuleClass; };
QT_END_NAMESPACE

class QTFormule : public QWidget
{
    Q_OBJECT

public:
    QTFormule(QWidget *parent = nullptr);
    ~QTFormule();
private slots:
    void ButtonCancel();
    void ButtonNumbers();
    void ButtonOperation();
    void ButtonHelp();
    void ButtonOK();
    void ButtonBS();
    void ButtonLF();
    void PushInColumn();
    void ButtonUpArrow();
    void ButtonDownArrow();
    void ButtonRightArrow();
    void ButtonLeftArrow();
private:
    Ui::QTFormuleClass *ui;
    void FileSaveTxt(const QString& content);
};

