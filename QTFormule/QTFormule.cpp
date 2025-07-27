#include "QTFormule.h"
#include <QFileDialog>
#include <list>
#include"string"
using namespace std;
QTFormule::QTFormule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QTFormuleClass())
{
    ui->setupUi(this);

    QLocale::setDefault(QLocale::system());

    //������� ������������, �������������� � �������
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);


    //��� �������������� � ������
    connect(ui->ButtonCancel, SIGNAL(clicked()), this, SLOT(ButtonCancel()));
    connect(ui->ButtonHelp, SIGNAL(clicked()), this, SLOT(ButtonHelp()));
    connect(ui->ButtonOK, SIGNAL(clicked()), this, SLOT(ButtonOK()));

    //��� �������������� � �������
    connect(ui->ButtonBS, SIGNAL(clicked()), this, SLOT(ButtonBS()));
    connect(ui->ButtonLF, SIGNAL(clicked()), this, SLOT(ButtonLF()));
    connect(ui->ButtonUpArrow, SIGNAL(clicked()), this, SLOT(ButtonUpArrow()));
    connect(ui->ButtonDownArrow, SIGNAL(clicked()), this, SLOT(ButtonDownArrow()));
    connect(ui->ButtonRightArrow, SIGNAL(clicked()), this, SLOT(ButtonRightArrow()));
    connect(ui->ButtonLeftArrow, SIGNAL(clicked()), this, SLOT(ButtonLeftArrow()));

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
    ui->TableWidgetFunction->verticalHeader()->hide();
    ui->TableWidgetFunction->horizontalHeader()->hide();
    ui->TableWidgetFunction->setRowCount(10);
    ui->TableWidgetFunction->setColumnCount(1);
    ui->TableWidgetFunction->setColumnWidth(0, 130);
    //connect(ui->TableWidgetFunction, SIGNAL(cellClicked(int, int)), this, SLOT(PushInColumn()));

    //����������
    ui->TableWidgetVariables->verticalHeader()->hide();
    ui->TableWidgetVariables->horizontalHeader()->hide();
    ui->TableWidgetVariables->setRowCount(10);
    ui->TableWidgetVariables->setColumnCount(1);
    ui->TableWidgetVariables->setColumnWidth(0, 140);
    //connect(ui->TableWidgetVariables, SIGNAL(cellClicked(int, int)), this, SLOT(PushInColumn()));

    //���������
    PushInColumn();
    ui->TableWidgetParameters->verticalHeader()->hide();
    ui->TableWidgetParameters->horizontalHeader()->hide();
    ui->TableWidgetParameters->setRowCount(10);
    ui->TableWidgetParameters->setColumnCount(1);
    ui->TableWidgetParameters->setColumnWidth(0, 140);
    PushInColumn();

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
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertText("\n");
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void QTFormule::ButtonUpArrow()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Up);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void QTFormule::ButtonDownArrow()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Down);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void QTFormule::ButtonLeftArrow()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Left);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void QTFormule::ButtonRightArrow()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Right);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->setFocus();
}

void QTFormule::ButtonOK()
{
    QString content = ui->textEdit->toPlainText();
    FileSaveTxt(content);
}

//��� ���� ������ � �������
void QTFormule::ButtonNumbers()
{
    QPushButton* Numbers = qobject_cast<QPushButton*>(sender());
    if (Numbers) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertText(Numbers->text());
    }
    ui->textEdit->setFocus();
}

//��� ���� ������ � ����������
void QTFormule::ButtonOperation()
{
    QPushButton* Operation = qobject_cast<QPushButton*>(sender());
    if (Operation) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertText(Operation->text());
    }
    ui->textEdit->setFocus();
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

void QTFormule::PushInColumn()
{
    list<string> function = { "sin(a)","cos(a)","tan(a)","atan(a)","exp(a)" };
    list<string> variables;
    list<string> parameters = { "R1.W","R1.L","R1.Rs","R1.Freq" };

    vector<string> functionVec(function.begin(), function.end());
    vector<string> variablesVec(variables.begin(), variables.end());
    vector<string> paramsVec(parameters.begin(), parameters.end());

    for (int i = 0; i < ui->TableWidgetFunction->rowCount(); i++)
    {
        for (int j = 0; j < ui->TableWidgetFunction->columnCount(); j++)
        {
            if (j < functionVec.size())
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText(QString::fromStdString(functionVec[j]));
                ui->TableWidgetFunction->setItem(i, j, item);
            }
        }
    }

    for (int i = 0; i < ui->TableWidgetVariables->rowCount(); i++)
    {
        for (int j = 0; j < ui->TableWidgetVariables->columnCount(); j++)
        {
            if (j < variablesVec.size())
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText(QString::fromStdString(variablesVec[j]));
                ui->TableWidgetVariables->setItem(i, j, item);
            }
        }
    }

    for (int i = 0; i < ui->TableWidgetParameters->rowCount(); i++)
    {
        for (int j = 0; j < ui->TableWidgetParameters->columnCount(); j++)
        {
            if (j < paramsVec.size())
            {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText(QString::fromStdString(paramsVec[j]));
                ui->TableWidgetParameters->setItem(i, j, item);
            }
        }
    }
}