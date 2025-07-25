#include "QTFormule.h"
#include <QFileDialog>

QTFormule::QTFormule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QTFormuleClass())
{
    ui->setupUi(this);

    QLocale::setDefault(QLocale::system());

    //��� �������������� � ������
    connect(ui->ButtonCancel, SIGNAL(clicked()), this, SLOT(ButtonCancel()));
    connect(ui->ButtonHelp, SIGNAL(clicked()), this, SLOT(ButtonHelp()));
    connect(ui->ButtonOK, SIGNAL(clicked()), this, SLOT(ButtonOK()));
    //��� �������������� � �������
    connect(ui->ButtonBS, SIGNAL(clicked()), this, SLOT(ButtonBS()));
    connect(ui->ButtonUpArrow, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonDownArrow, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonRightArrow, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonLeftArrow, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    //��� ����
    connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(ButtonNumbers()));
    //��� ���. �������� � ��������
    connect(ui->ButtonPlus, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonMinus, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonPoint, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonE, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonLeftBracket, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonRightBracket, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonComma, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonDivision, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonExponentiation, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    connect(ui->ButtonIncrease, SIGNAL(clicked()), this, SLOT(ButtonOperation()));
    //�������
    ui->TableWidgetFunction->setRowCount(2);
    ui->TableWidgetFunction->setColumnCount(1);
    //����������
    ui->TableWidgetVariables->setRowCount(2);
    ui->TableWidgetVariables->setColumnCount(1);
    //���������
    ui->TableWidgetParameters->setRowCount(2);
    ui->TableWidgetParameters->setColumnCount(1);

}

QTFormule::~QTFormule()
{
    delete ui;
}

void QTFormule::ButtonCancel()
{
    this->close();
}

void QTFormule::ButtonHelp()
{

}

void QTFormule::ButtonBS()
{
    ui->textEdit->clear();
}

void QTFormule::ButtonLF()
{

}

void QTFormule::ButtonOK()
{
    QString content = ui->textEdit->toPlainText();
    FileSaveTxt(content);
}

//��� ���� ������ � �������
void QTFormule::ButtonNumbers()
{
    QPushButton* Numbers = (QPushButton*)sender();
     AllNumbers;
    AllNumbers = ui->textEdit->toPlainText() + Numbers->text();
    ui->textEdit->setText(AllNumbers);

}

//��� ���� ������ � ����������
void QTFormule::ButtonOperation()
{
    QPushButton* Operation = (QPushButton*)sender();
    QString AllOperation;
    AllOperation = ui->textEdit->toPlainText() + Operation->text();
    ui->textEdit->setText(AllOperation);
}

void QTFormule::FileSaveTxt(const QString& content)
{

    QDir dir("C:/Users/User/source/TxtFormule");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QFile file("C:/Users/User/source/TxtFormule/Formule.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    out << content;
    file.close();

}