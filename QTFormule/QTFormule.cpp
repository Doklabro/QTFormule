#include "QTFormule.h"
#include <QFileDialog>
#include <list>
#include"string"
#include <QTextEdit>
#include <QMessageBox>

using namespace std;
QTFormule::QTFormule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QTFormuleClass())
{
    ui->setupUi(this);
    QLocale::setDefault(QLocale::system());

    //Убираем сворачивание, разворачивание и крестик
    this->setWindowFlag(Qt::WindowCloseButtonHint, false);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    //Для взаимодействия с формой
    connect(ui->ButtonCancel, SIGNAL(clicked()), this, SLOT(ButtonCancel()));
    connect(ui->ButtonHelp, SIGNAL(clicked()), this, SLOT(ButtonHelp()));
    connect(ui->ButtonOK, SIGNAL(clicked()), this, SLOT(ButtonOK()));

    //Для взаимодействия с текстом
    connect(ui->ButtonBS, SIGNAL(clicked()), this, SLOT(ButtonBS()));
    connect(ui->ButtonLF, SIGNAL(clicked()), this, SLOT(ButtonLF()));
    connect(ui->ButtonUpArrow, SIGNAL(clicked()), this, SLOT(ButtonUpArrow()));
    connect(ui->ButtonDownArrow, SIGNAL(clicked()), this, SLOT(ButtonDownArrow()));
    connect(ui->ButtonRightArrow, SIGNAL(clicked()), this, SLOT(ButtonRightArrow()));
    connect(ui->ButtonLeftArrow, SIGNAL(clicked()), this, SLOT(ButtonLeftArrow()));

    //Для цифр
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

    //Для мат. операций и символов
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

    //Функции
    ui->TableWidgetFunction->verticalHeader()->hide();
    ui->TableWidgetFunction->horizontalHeader()->hide();
    ui->TableWidgetFunction->setRowCount(10);
    ui->TableWidgetFunction->setColumnCount(1);
    ui->TableWidgetFunction->setColumnWidth(0, 130);
    connect(ui->TableWidgetFunction, SIGNAL(cellClicked(int, int)), this, SLOT(onTableCellClicked(int, int)));

    //Переменные
    ui->TableWidgetVariables->verticalHeader()->hide();
    ui->TableWidgetVariables->horizontalHeader()->hide();
    ui->TableWidgetVariables->setRowCount(10);
    ui->TableWidgetVariables->setColumnCount(1);
    ui->TableWidgetVariables->setColumnWidth(0, 140);
    connect(ui->TableWidgetVariables, SIGNAL(cellClicked(int, int)), this, SLOT(onTableCellClicked(int, int)));

    //Параметры
    ui->TableWidgetParameters->verticalHeader()->hide();
    ui->TableWidgetParameters->horizontalHeader()->hide();
    ui->TableWidgetParameters->setRowCount(10);
    ui->TableWidgetParameters->setColumnCount(1);
    ui->TableWidgetParameters->setColumnWidth(0, 140);
    connect(ui->TableWidgetParameters, SIGNAL(cellClicked(int, int)), this, SLOT(onTableCellClicked(int, int)));
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
    QMessageBox::information(this, "Справка о формулах", "Москвин В.Д. 2025");
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
    QString text = ui->textEdit->toPlainText();
    validateBrackets(text);
    FileSaveTxt(text);
}

//Для всех кнопок с цифрами
void QTFormule::ButtonNumbers()
{
    QPushButton* Numbers = qobject_cast<QPushButton*>(sender());
    if (Numbers) 
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertText(Numbers->text());
    }
    ui->textEdit->setFocus();
}

//Для всех кнопок с операциями
void QTFormule::ButtonOperation()
{
    QPushButton* Operation = qobject_cast<QPushButton*>(sender());
    if (Operation) 
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertText(Operation->text());
    }
    ui->textEdit->setFocus();
}

void QTFormule::FileSaveTxt(const QString& content)
{

    QDir dir("C:/Users/User/source/TxtFormule");
    if (!dir.exists())
    {
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
    Formule f = Formule();

    vector<string> functionVec(f.function.begin(), f.function.end());
    for (int i = 0; i < ui->TableWidgetFunction->rowCount(); i++)
    {
        if (i < functionVec.size() && !functionVec[i].empty())
        {
             QTableWidgetItem* item = new QTableWidgetItem;
             item->setText(QString::fromStdString(functionVec[i]));
             item->setFlags(item->flags() & ~Qt::ItemIsEditable);
             ui->TableWidgetFunction->setItem(i, 0, item);
        }
    }

    vector<string> variablesVec(f.variables.begin(), f.variables.end());
    for (int i = 0; i < ui->TableWidgetVariables->rowCount(); i++)
    {
        if (i < variablesVec.size())
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(QString::fromStdString(variablesVec[i]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->TableWidgetVariables->setItem(i, 0, item);
        }
    }

    vector<string> paramsVec(f.parameters.begin(), f.parameters.end());
    for (int i = 0; i < ui->TableWidgetParameters->rowCount(); i++)
    {
        if (i < paramsVec.size())
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(QString::fromStdString(paramsVec[i]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->TableWidgetParameters->setItem(i, 0, item);
        }
    }
}

void QTFormule::onTableCellClicked(int row, int column)
{
    QTableWidget* table = qobject_cast<QTableWidget*>(sender());
    if (!table) return;

    QTableWidgetItem* item = table->item(row, column);
    if (item)
    {
        QString text = item->text();
        ui->textEdit->insertPlainText(text);
        ui->textEdit->setFocus();
    }
}

void QTFormule::validateBrackets(const QString& text) 
{
    int i = 0;
    for (const QChar& ch : text) 
    {
        if (ch == '(') 
        {
            i++;
        }
        else if (ch == ')') 
        {
            i--;
        }
    }

    if (i != 0 || i > 0 || i < 0)
    {
        QMessageBox::warning(this, ("Ошибка"), "Введите недостающие скобки!");
    }
    
    else
    {
        QMessageBox::information(this, "C:/Users/User/source/TxtFormule/Formule.txt", "Файл сохранён");
    }

}