#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("which");
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "注意", "登陆失败, 请重试", QMessageBox::Yes);
        return ;
    }
    QTextStream in(&file);
    in >> choice;
    if (2 == choice)
        in >> (char *)stuNum;
    file.close();
    if (2 == choice)
    {
        readStuInfo();
        setUpDetailWidget();
        setUpNewStudentsWidget();
    }
    else
    {
        Q_UNUSED(stuNum)
        setUpFirstWidget();
        setUpEditStudentsWidget();
        setUpNewStudentsWidget();
        setUpDetailWidget();
        readStuInfo();
    }

    QPalette pal;
    pal.setBrush(QPalette::Background, QBrush(QPixmap(":/mainBackground/image/background.png").scaled(600, 400)));
    setPalette(pal);

    setObjectName("MainWindow");
    setWindowTitle(QStringLiteral("学生信息管理系统"));
    setFixedSize(600, 400);
}

void MainWindow::readStuInfo()
{
    using namespace std;
    fstream file("students", ios_base::in);
    if (!file.is_open())
    {
        file.open("students", ios_base::out);
        file.close();
    }
    else
    {
        Stu temp;
        file.seekg(0, ios_base::beg);
        while(file.read((char *)&temp, sizeof(Stu)))
            studentsList.append(temp);
        file.close();
    }

    if (2 == choice)
    {
        for (int i = 0; i < studentsList.count(); i++)
        {
            if (strcmp(stuNum, studentsList.at(i).num) == 0)
            {
                signInStudent = i;
                return;
            }
        }
    }
}

void MainWindow::setTableInformation()
{
    spinBox->setValue(0);
    editStudentsTable->setRowCount(0);

    for (int i = 0; i < studentsList.count(); i++)
    {
        editStudentsTable->insertRow(editStudentsTable->rowCount());
        editStudentsTable->setItem(i, 0, new QTableWidgetItem(studentsList.at(i).name));
        editStudentsTable->setItem(i, 1, new QTableWidgetItem(studentsList.at(i).num));
        editStudentsTable->setItem(i, 2, new QTableWidgetItem(studentsList.at(i).sex));
        editStudentsTable->setItem(i, 3, new QTableWidgetItem(QString::number(studentsList.at(i).english)));
        editStudentsTable->setItem(i, 4, new QTableWidgetItem(QString::number(studentsList.at(i).chinese)));
        editStudentsTable->setItem(i, 5, new QTableWidgetItem(QString::number(studentsList.at(i).math)));
        editStudentsTable->setItem(i, 6, new QTableWidgetItem(QString::number(studentsList.at(i).avarage)));
    }
}

void MainWindow::editWidgetFlag()
{
    widgetFlag = 1;
    switchWidget();
}

void MainWindow::newWidgetFlag()
{
    widgetFlag = 2;
    switchWidget();
}

void MainWindow::setUpFirstWidget()
{
    QHBoxLayout butLayout;

    inOrOut = false;
    firstWidget = new QWidget(this);
    firstWidget->setStyleSheet("QWidget{background-color:QColor(0, 0, 0, 0)}");
    firstWidget->setFixedSize(WIDTH, HEIGHT);
    firstWidget->setAutoFillBackground(true);
    firstWidget->setLayout(&butLayout);

    editStudents = new QToolButton(firstWidget);
    newStudents = new QToolButton(firstWidget);
    saveAndQuit = new QToolButton(firstWidget);
    editStudents->setIcon(QIcon(QPixmap(":/mainBackground/image/edit.png").scaled(ICONWIDTH, ICONHEIGHT)));
    newStudents->setIcon(QIcon(QPixmap(":/mainBackground/image/new.png").scaled(ICONWIDTH, ICONHEIGHT)));
    saveAndQuit->setIcon(QIcon(QPixmap(":/mainBackground/image/saveAndExit").scaled(ICONWIDTH, ICONHEIGHT)));
    editStudents->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
    newStudents->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
    saveAndQuit->setIconSize(QSize(ICONWIDTH, ICONHEIGHT));
    editStudents->setGeometry(40, 140, ICONWIDTH, ICONHEIGHT);
    newStudents->setGeometry(223, 140, ICONWIDTH, ICONHEIGHT);
    saveAndQuit->setGeometry(406, 145, ICONWIDTH, ICONHEIGHT);

    butLayout.addWidget(editStudents);
    butLayout.addWidget(newStudents);

    connect(editStudents, SIGNAL(clicked()), this, SLOT(editWidgetFlag()));
    connect(newStudents, SIGNAL(clicked()), this, SLOT(newWidgetFlag()));
    connect(saveAndQuit, SIGNAL(clicked()), this, SLOT(saveAndExit()));
}

void  MainWindow::setUpEditStudentsWidget()
{
    editWidgetInOut = true;
    editStudentsWidget = new QWidget(this);
    editStudentsWidget->setObjectName("editStuWidget");
    editStudentsWidget->setStyleSheet("QWidget{background-color:QColor(0, 0, 0, 0)}"
                                      "QPushButton{background-color:QColor(197, 240, 255, 90)}");
    editStudentsWidget->setFixedSize(WIDTH, HEIGHT);
    editStudentsWidget->move(600, 0);
    editStudentsWidget->setAutoFillBackground(true);

    QStringList str;
    QVBoxLayout *mainLayout = new QVBoxLayout(editStudentsWidget);
    QHBoxLayout *butLayout = new QHBoxLayout;

    str << "姓名" << "学号" << "性别" << "英语" << "语文" << "数学" << "平均分数";

    editStudentsTable = new QTableWidget(0, 7, editStudentsWidget);
    editStudentsTable->setHorizontalHeaderLabels(str);

    editStudentsTable->setFixedSize(WIDTH - 20, HEIGHT - 130);
    editStudentsTable->move(10, 100);
    for(int i = 0; i < 7; i++)
        editStudentsTable->setColumnWidth(i, 80);
    editStudentsTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:lightblue;}");
    editStudentsTable->verticalHeader()->setStyleSheet("QHeaderView::section{background-color:lightblue;}");
    editStudentsTable->setStyleSheet("selection-background-color:lightblue;");//cornerbutton颜色未修改。

    changeButton = new QPushButton(QStringLiteral("确认修改"), editStudentsWidget);
    detailButton = new QPushButton(QStringLiteral("详细信息"), editStudentsWidget);
    deleteButton = new QPushButton(QStringLiteral("删除学生"), editStudentsWidget);
    backButton = new QPushButton(QStringLiteral("返回"), editStudentsWidget);
    selectClass = new QLabel(QStringLiteral("学生班级"), editStudentsWidget);
    spinBox = new QSpinBox(editStudentsWidget);

    changeButton->setFixedSize(BUTTONWIDTH, BUTTONHEIGHT);
    detailButton->setFixedSize(BUTTONWIDTH, BUTTONHEIGHT);
    deleteButton->setFixedSize(BUTTONWIDTH, BUTTONHEIGHT);
    backButton->setFixedSize(BUTTONWIDTH, BUTTONHEIGHT);
    spinBox->setFixedSize(BUTTONWIDTH / 2, BUTTONHEIGHT);
    selectClass->setFixedSize(BUTTONWIDTH - 30, BUTTONHEIGHT);
    spinBox->setMaximum(20);

    butLayout->addWidget(selectClass);
    butLayout->addWidget(spinBox);
    butLayout->addSpacing(30);
    butLayout->addWidget(changeButton);
    butLayout->addSpacing(30);
    butLayout->addWidget(detailButton);
    butLayout->addSpacing(30);
    butLayout->addWidget(deleteButton);
    butLayout->addSpacing(30);
    butLayout->addWidget(backButton);

    mainLayout->addSpacing(88);
    mainLayout->addWidget(editStudentsTable);
    mainLayout->addLayout(butLayout);
    editStudentsWidget->setLayout(mainLayout);

    connect(changeButton, SIGNAL(clicked()), this, SLOT(getNewList()));
    connect(detailButton, SIGNAL(clicked()), this, SLOT(showDetail()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteStudent()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(switchWidget()));
    connect(editStudentsTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(editCell(int, int)));
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(filterStudentns(int)));
}

void MainWindow::setUpDetailWidget()
{
    detailWidgetInOut = true;
    detailWidget = new QWidget(this);
    detailWidget->setObjectName("detailStuWidget");
    detailWidget->setStyleSheet("QWidget#detailStuWidget{background-color:QColor(0, 0, 0, 0)}");

    if (2 == choice)
        detailWidget->setGeometry(0, 0, WIDTH, HEIGHT);
    else
        detailWidget->setGeometry(WIDTH, 0, WIDTH, HEIGHT);

    detailWidget->setAutoFillBackground(true);

    showNameLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>姓名:</FONT>", detailWidget);
    showNameLabel->setGeometry(QRect(10, 120, 60, 30));
\
    showNumLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>学号:</FONT>", detailWidget);
    showNumLabel->setGeometry(QRect(10, 210, 60, 30));

    showSexLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>性别:</FONT>", detailWidget);
    showSexLabel->setGeometry(QRect(10, 300, 60, 30));

    showName = new QLabel("", detailWidget);
    showName->setGeometry(QRect(80, 120, 100, 30));

    showNum = new QLabel("", detailWidget);
    showNum->setGeometry(QRect(80, 210, 100, 30));

    showSex = new QLabel("", detailWidget);
    showSex->setGeometry(QRect(80, 300, 100, 30));

    showEnglishLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>英语</FONT>", detailWidget);
    showEnglishLabel->setGeometry(QRect(210, 120, 60, 30));

    showEnglish = new QLabel("", detailWidget);
    showEnglish->setGeometry(QRect(280, 120, 100, 30));

    showMathLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>数学</FONT>", detailWidget);
    showMathLabel->setGeometry(QRect(210, 210, 60, 30));

    showMath = new QLabel("", detailWidget);
    showMath->setGeometry(QRect(280, 210, 100, 30));

    showChineseLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>语文</FONT>", detailWidget);
    showChineseLabel->setGeometry(QRect(210, 300, 60, 30));

    showChinese = new QLabel("", detailWidget);
    showChinese->setGeometry(QRect(280, 300, 100, 30));

    showIDLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>身份证</FONT>", detailWidget);
    showIDLabel->setGeometry(QRect(390, 120, 90, 30));

    showID = new QLabel("", detailWidget);
    showID->setGeometry(QRect(490, 120, 100, 30));

    showAddressLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>地址</FONT>", detailWidget);
    showAddressLabel->setGeometry(QRect(410, 210, 60, 30));

    showAddress = new QLabel("", detailWidget);
    showAddress->setGeometry(QRect(490, 210, 100, 30));

    showClassLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>班级</FONT>", detailWidget);
    showClassLabel->setGeometry(QRect(410, 300, 60, 30));

    showClass = new QLabel("",  detailWidget);
    showClass->setGeometry(QRect(490, 300, 100, 30));

    if (2 ==  choice)
    {
        showDetail();
        backButton3 = new QPushButton(QStringLiteral("退出"), detailWidget);
        changeInfoButton = new QPushButton(QStringLiteral("修改信息"), detailWidget);
        backButton3->setStyleSheet("background-color:QColor(197, 240, 255, 90)");
        changeInfoButton->setStyleSheet("background-color:QColor(197, 240, 255, 90)");
        backButton3->setGeometry(350, 360, BUTTONWIDTH, BUTTONHEIGHT);
        changeInfoButton->setGeometry(180, 360, BUTTONWIDTH, BUTTONHEIGHT);

        connect(backButton3, SIGNAL(clicked()), this, SLOT(saveAndExit()));
        connect(changeInfoButton, SIGNAL(clicked()), this, SLOT(changeFlag()));
    }
    else
    {
        Q_UNUSED(changeInfoButton);
        backButton3 = new QPushButton(QStringLiteral("返回"), detailWidget);
        backButton3->setStyleSheet("background-color:QColor(197, 240, 255, 90)");
        backButton3->setGeometry(260, 360, BUTTONWIDTH, BUTTONHEIGHT);

        connect(backButton3, SIGNAL(clicked()), this, SLOT(switchWidget()));
    }
}

void MainWindow::changeFlag()
{
    nameLineEdit->setText(studentsList.at(signInStudent).name);
    numLineEdit->setText(studentsList.at(signInStudent).num);
    sexLineEdit->setText(studentsList.at(signInStudent).sex);
    mathLineEdit->setText(QString::number(studentsList.at(signInStudent).math));
    englishLineEdit->setText(QString::number(studentsList.at(signInStudent).english));
    chineseLineEdit->setText(QString::number(studentsList.at(signInStudent).chinese));
    IDLineEdit->setText(studentsList.at(signInStudent).ID);
    addressLineEdit->setText(studentsList.at(signInStudent).address);
    classLineEdit->setText(QString::number(studentsList.at(signInStudent).klass));

    widgetFlag = 4;
    switchWidget();
}

void MainWindow::setUpNewStudentsWidget()
{
    newWidgetInOut = true;
    newStudentsWidget = new QWidget(this);
    newStudentsWidget->setObjectName("newStuWidget");
    newStudentsWidget->setStyleSheet("QWidget#newStuWidget{background-color:QColor(0, 0, 0, 0)}"
                                     "QLineEdit{background-color:QColor(197, 240, 255, 90)}"
                                     "QPushButton{background-color:QColor(197, 240, 255, 90)}");
    newStudentsWidget->setFixedSize(WIDTH, HEIGHT);
    newStudentsWidget->move(600, 0);
    newStudentsWidget->setAutoFillBackground(true);

    nameLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>姓名</FONT>", newStudentsWidget);
    nameLabel->setGeometry(QRect(10, 120, 60, 30));

    numLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>学号</FONT>", newStudentsWidget);
    numLabel->setGeometry(QRect(10, 210, 60, 30));

    sexLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>性别</FONT>", newStudentsWidget);
    sexLabel->setGeometry(QRect(10, 300, 60, 30));

    nameLineEdit = new QLineEdit(newStudentsWidget);
    nameLineEdit->setGeometry(QRect(80, 120, 100, 30));
    nameLineEdit->setMaxLength(MAX - 3);

    numLineEdit = new QLineEdit(newStudentsWidget);
    numLineEdit->setGeometry(QRect(80, 210, 100, 30));
    numLineEdit->setMaxLength(MAX - 3);

    sexLineEdit = new QLineEdit(newStudentsWidget);
    sexLineEdit->setGeometry(QRect(80, 300, 100, 30));
    sexLineEdit->setMaxLength(MAX - 3);

    englishLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>英语</FONT>", newStudentsWidget);
    englishLabel->setGeometry(QRect(210, 120, 60, 30));

    englishLineEdit = new QLineEdit(newStudentsWidget);
    englishLineEdit->setGeometry(QRect(280, 120, 100, 30));
    englishLineEdit->setMaxLength(MAX - 3);

    mathLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>数学</FONT>", newStudentsWidget);
    mathLabel->setGeometry(QRect(210, 210, 60, 30));

    mathLineEdit = new QLineEdit(newStudentsWidget);
    mathLineEdit->setGeometry(QRect(280, 210, 100, 30));
    mathLineEdit->setMaxLength(MAX - 3);

    chineseLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>语文</FONT>", newStudentsWidget);
    chineseLabel->setGeometry(QRect(210, 300, 60, 30));

    chineseLineEdit = new QLineEdit(newStudentsWidget);
    chineseLineEdit->setGeometry(QRect(280, 300, 100, 30));
    chineseLineEdit->setMaxLength(MAX - 3);

    IDLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>身份证</FONT>", newStudentsWidget);
    IDLabel->setGeometry(QRect(390, 120, 90, 30));

    IDLineEdit = new QLineEdit(newStudentsWidget);
    IDLineEdit->setGeometry(QRect(490, 120, 100, 30));
    IDLineEdit->setMaxLength(MAX - 3);

    addressLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>地址</FONT>", newStudentsWidget);
    addressLabel->setGeometry(QRect(410, 210, 60, 30));

    addressLineEdit = new QLineEdit(newStudentsWidget);
    addressLineEdit->setGeometry(QRect(490, 210, 100, 30));
    addressLineEdit->setMaxLength(MAX - 3);

    classLabel = new QLabel("<FONT size = 18 face = 华康娃娃体W5 color = lightblue>班级</FONT>", newStudentsWidget);
    classLabel->setGeometry(QRect(410, 300, 60, 30));

    classLineEdit = new QLineEdit(newStudentsWidget);
    classLineEdit->setGeometry(QRect(490, 300, 100, 30));

    if (2 == choice)
    {
        addStudentButton = new QPushButton(QStringLiteral("确认修改"), newStudentsWidget);
        backButton2 = new QPushButton(QStringLiteral("返回"), newStudentsWidget);

        classLineEdit->setEnabled(false);
        mathLineEdit->setEnabled(false);
        englishLineEdit->setEnabled(false);
        chineseLineEdit->setEnabled(false);


        connect(backButton2, SIGNAL(clicked()), this, SLOT(switchWidget()));
        connect(addStudentButton, SIGNAL(clicked()), this, SLOT(addStudent()));
    }
    else
    {
        addStudentButton = new QPushButton(QStringLiteral("确认添加"), newStudentsWidget);
        backButton2 = new QPushButton(QStringLiteral("返回"), newStudentsWidget);

        connect(backButton2, SIGNAL(clicked()), this, SLOT(switchWidget()));
        connect(addStudentButton, SIGNAL(clicked()), this, SLOT(addStudent()));
    }

    addStudentButton->setFixedSize(BUTTONWIDTH, BUTTONHEIGHT);
    backButton2->setFixedSize(BUTTONWIDTH, BUTTONHEIGHT);
    addStudentButton->move(100, 350);
    backButton2->move(400, 350);

    QRegExp exp("^([0-9]|[1-9][0-9]|100)$");
    englishLineEdit->setValidator(new QRegExpValidator(exp, englishLineEdit));
    mathLineEdit->setValidator(new QRegExpValidator(exp, mathLineEdit));
    chineseLineEdit->setValidator(new QRegExpValidator(exp, chineseLineEdit));

    exp.setPattern("^([1-9]|[1][0-9]|20)$");
    classLineEdit->setValidator(new QRegExpValidator(exp, classLineEdit));
}

void MainWindow::deleteStudent()
{
    if (-1 == editStudentsTable->currentRow())
    {
        QMessageBox::warning(0, "注意", "请选中学生所在行数", QMessageBox::Yes);
        return;
    }
    else
    {
        char tempNum[20];
        strcpy(tempNum, editStudentsTable->item(editStudentsTable->currentRow(), 1)->text().toStdString().data());

        for (int i = 0; i < studentsList.count(); i++)
        {
            if (strcmp(tempNum, studentsList.at(i).num) == 0)
            {
                studentsList.takeAt(i);
                editStudentsTable->removeRow(editStudentsTable->currentRow());
                break;
            }
        }
    }
}

void MainWindow::addStudent()
{
    if (nameLineEdit->text().isEmpty() || numLineEdit->text().isEmpty() || sexLineEdit->text().isEmpty() ||
            englishLineEdit->text().isEmpty() || mathLineEdit->text().isEmpty() || chineseLineEdit->text().isEmpty() ||
            IDLineEdit->text().isEmpty() || addressLineEdit->text().isEmpty() || classLineEdit->text().isEmpty())
    {
        QMessageBox::warning(newStudentsWidget, "警告", "学生的信息不能有空项", QMessageBox::Yes);
        return;
    }
    else
    {
        for (int i = 0; i < studentsList.count(); i++)
        {
            if (strcmp(numLineEdit->text().toStdString().data(), studentsList.at(i).num) == 0)
            {
                if (2 == choice)
                {
                    if (strcmp(numLineEdit->text().toStdString().data(), studentsList.at(signInStudent).num) == 0)
                        break;
                }
                QMessageBox::warning(newStudentsWidget, "注意", "不能有相同学号的学生", QMessageBox::Yes);
                return;
            }
        }
        if (englishLineEdit->text().toInt() < 0 || englishLineEdit->text().toInt() > 100 ||
                mathLineEdit->text().toInt()  < 0 || mathLineEdit->text().toInt() > 100 ||
                chineseLineEdit->text().toInt() < 0 || chineseLineEdit->text().toInt() > 100)
        {
            QMessageBox::warning(newStudentsWidget, "警告", "学生各科成绩范围0~100", QMessageBox::Yes);
            return;
        }
        else
        {
            if (2 == choice)
            {
                strcpy(studentsList[signInStudent].name, nameLineEdit->text().toStdString().data());
                strcpy(studentsList[signInStudent].num, numLineEdit->text().toStdString().data());
                strcpy(studentsList[signInStudent].sex, sexLineEdit->text().toStdString().data());
                strcpy(studentsList[signInStudent].ID, IDLineEdit->text().toStdString().data());
                strcpy(studentsList[signInStudent].address, addressLineEdit->text().toStdString().data());
                studentsList[signInStudent].klass = classLineEdit->text().toInt();
                studentsList[signInStudent].math = mathLineEdit->text().toInt();
                studentsList[signInStudent].chinese = chineseLineEdit->text().toInt();
                studentsList[signInStudent].english = englishLineEdit->text().toInt();
                studentsList[signInStudent].avarage = (double)(studentsList.at(signInStudent).math + studentsList.at(signInStudent).english + studentsList.at(signInStudent).chinese) / 3;

                showName->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).name) + "</FONT>");
                showNum->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).num) + "</FONT>");
                showSex->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).sex) + "</FONT>");
                showEnglish->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).english) + "</FONT>");
                showChinese->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).chinese) + "</FONT>");
                showMath->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).math) + "</FONT>");
                showID->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).ID) + "</FONT>");
                showAddress->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).address) + "</FONT>");
                showClass->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).klass) + "</FONT>");


                QMessageBox::information(newStudentsWidget, "提示", "学生信息已修改", QMessageBox::Yes);
            }
            else
            {
                Stu temp;
                strcpy(temp.name, nameLineEdit->text().toStdString().data());
                strcpy(temp.num, numLineEdit->text().toStdString().data());
                strcpy(temp.sex, sexLineEdit->text().toStdString().data());
                strcpy(temp.ID, IDLineEdit->text().toStdString().data());
                strcpy(temp.address, addressLineEdit->text().toStdString().data());
                temp.klass = classLineEdit->text().toInt();
                temp.math = mathLineEdit->text().toInt();
                temp.chinese = chineseLineEdit->text().toInt();
                temp.english = englishLineEdit->text().toInt();
                temp.avarage = (double)(temp.math + temp.english + temp.chinese) / 3;
                studentsList.append(temp);

                QMessageBox::information(newStudentsWidget, "提示", "新学生信息已保存", QMessageBox::Yes);
            }
        }
    }
}



void MainWindow::showDetail()
{
    if (2 == choice)
    {qDebug() << studentsList.at(signInStudent).name;
        showName->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).name) + "</FONT>");
        showNum->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).num) + "</FONT>");
        showSex->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).sex) + "</FONT>");
        showEnglish->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).english) + "</FONT>");
        showChinese->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).chinese) + "</FONT>");
        showMath->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).math) + "</FONT>");
        showID->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).ID) + "</FONT>");
        showAddress->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(signInStudent).address) + "</FONT>");
        showClass->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(signInStudent).klass) + "</FONT>");
        switchWidget();
    }
    else
    {
        if (-1 == editStudentsTable->currentRow())
        {
            QMessageBox::warning(0, "注意", "请选中学生所在行数", QMessageBox::Yes);
            return;
        }

        char tempNum[20];
        strcpy(tempNum, editStudentsTable->item(editStudentsTable->currentRow(), 1)->text().toStdString().data());

        for (int i = 0; i < studentsList.count(); i++)
        {
            if (strcmp(tempNum, studentsList.at(i).num) == 0)
            {
                showName->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(i).name) + "</FONT>");
                showNum->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(i).num) + "</FONT>");
                showSex->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(i).sex) + "</FONT>");
                showEnglish->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(i).english) + "</FONT>");
                showChinese->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(i).chinese) + "</FONT>");
                showMath->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(i).math) + "</FONT>");
                showID->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(i).ID) + "</FONT>");
                showAddress->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::fromStdString(studentsList.at(i).address) + "</FONT>");
                showClass->setText("<FONT color = lightblue face = 华康娃娃体W5 size = 6>" + QString::number(studentsList.at(i).klass) + "</FONT>");
                break;
            }
        }
        widgetFlag = 3;
        switchWidget();
    }
}

void MainWindow::filterStudentns(int classNum)
{
    if (0 == classNum)
        setTableInformation();
    else
    {
        editStudentsTable->setRowCount(0);

        QListIterator<Stu> iterator(studentsList);
        Stu temp;
        int i = 0;
        while(iterator.hasNext())
        {
            temp = iterator.next();
            if (classNum == temp.klass)
            {
                editStudentsTable->insertRow(editStudentsTable->rowCount());
                editStudentsTable->setItem(i, 0, new QTableWidgetItem(temp.name));
                editStudentsTable->setItem(i, 1, new QTableWidgetItem(temp.num));
                editStudentsTable->setItem(i, 2, new QTableWidgetItem(temp.sex));
                editStudentsTable->setItem(i, 3, new QTableWidgetItem(QString::number(temp.english)));
                editStudentsTable->setItem(i, 4, new QTableWidgetItem(QString::number(temp.chinese)));
                editStudentsTable->setItem(i, 5, new QTableWidgetItem(QString::number(temp.math)));
                editStudentsTable->setItem(i++, 6, new QTableWidgetItem(QString::number(temp.avarage)));
            }
        }
    }

}

void MainWindow::editCell(int r, int c)
{
    delete editStudentsTable->takeItem(r, c);
    editStudentsTable->setItem(r, c, new QTableWidgetItem(""));
}

void  MainWindow::getNewList()
{
    for (int i = 0; i < editStudentsTable->rowCount(); i++)
        for (int j = i + 1; j < editStudentsTable->rowCount(); j++)
        {
            if (strcmp(editStudentsTable->item(i, 1)->text().toStdString().data(), editStudentsTable->item(j, 1)->text().toStdString().data()) == 0)
            {
                QMessageBox::warning(0, "注意", "不能有相同学号的学生", QMessageBox::Yes);

                return;
            }
        }

    int count = studentsList.count() <= editStudentsTable->rowCount() ? studentsList.count() : editStudentsTable->rowCount();
    for (int i = 0; i < count; i++)
    {
        strcpy(studentsList[i].name, editStudentsTable->item(i, 0)->text().toStdString().data());
        strcpy(studentsList[i].num, editStudentsTable->item(i, 1)->text().toStdString().data());
        strcpy(studentsList[i].sex, editStudentsTable->item(i, 2)->text().toStdString().data());
        studentsList[i].english = editStudentsTable->item(i, 3)->text().toInt();
        studentsList[i].chinese = editStudentsTable->item(i, 4)->text().toInt();
        studentsList[i].math = editStudentsTable->item(i, 5)->text().toInt();
        studentsList[i].avarage = editStudentsTable->item(i, 3)->text().toDouble();
    }

    while (studentsList.count() > count)
    {
        count--;
        studentsList.pop_back();
    }
}

void MainWindow::tableWidgetMove()
{
    QPropertyAnimation *animation = new QPropertyAnimation(editStudentsWidget,  "pos", this);
    animation->setDuration(ANIMATIONTIME);
    if (editWidgetInOut)
    {
        animation->setStartValue(editStudentsWidget->pos());
        animation->setEndValue(QPoint(editStudentsWidget->pos().x() - WIDTH, 0));
        editWidgetInOut = false;
    }
    else
    {
        animation->setStartValue(editStudentsWidget->pos());
        animation->setEndValue(QPoint(editStudentsWidget->pos().x() + WIDTH, 0));
        editWidgetInOut = true;
    }
    animation->start();
}

void MainWindow::detailWidgetMove()
{
    QPropertyAnimation *animation = new QPropertyAnimation(detailWidget, "pos");
    animation->setDuration(ANIMATIONTIME);
    if (detailWidgetInOut)
    {
        if (2 == choice)
        {
            animation->setStartValue(detailWidget->pos());
            animation->setEndValue(QPoint(detailWidget->pos().x() + WIDTH, 0));
            detailWidgetInOut = false;
        }
        else
        {
            animation->setStartValue(detailWidget->pos());
            animation->setEndValue(QPoint(detailWidget->pos().x() - WIDTH, 0));
            detailWidgetInOut = false;
        }
    }
    else
    {
        if (2 == choice)
        {
            animation->setStartValue(detailWidget->pos());
            animation->setEndValue(QPoint(detailWidget->pos().x() - WIDTH, 0));
            detailWidgetInOut = true;
        }
        else
        {
            animation->setStartValue(detailWidget->pos());
            animation->setEndValue(QPoint(detailWidget->pos().x() + WIDTH, 0));
            detailWidgetInOut = true;
        }
    }
    animation->start();
}

void MainWindow::firstWidgetMove()
{
    QPropertyAnimation *animation = new QPropertyAnimation(firstWidget,  "pos", this);
    animation->setDuration(ANIMATIONTIME);
    if (!inOrOut)
    {
        animation->setStartValue(firstWidget->pos());
        animation->setEndValue(QPoint(firstWidget->pos().x() - WIDTH, 0));
        inOrOut = true;
    }
    else
    {
        animation->setStartValue(firstWidget->pos());
        animation->setEndValue(QPoint(firstWidget->pos().x() + WIDTH, 0));
        inOrOut = false;
    }
    animation->start();
}

void MainWindow::newWidgetMove()
{
    QPropertyAnimation *animation = new QPropertyAnimation(newStudentsWidget,  "pos", this);
    animation->setDuration(ANIMATIONTIME);
    if (newWidgetInOut)
    {
        animation->setStartValue(newStudentsWidget->pos());
        animation->setEndValue(QPoint(newStudentsWidget->pos().x() - WIDTH, 0));
        newWidgetInOut = false;
    }
    else
    {
        animation->setStartValue(newStudentsWidget->pos());
        animation->setEndValue(QPoint(newStudentsWidget->pos().x() + WIDTH, 0));
        newWidgetInOut = true;
    }
    animation->start();
}

void MainWindow::switchWidget()
{
    switch(widgetFlag)
    {
    case 1:
        if (editWidgetInOut)
            setTableInformation();
        firstWidgetMove();
        tableWidgetMove();
        break;
    case 2:
        firstWidgetMove();
        newWidgetMove();
        break;
    case 3:
        if (!detailWidgetInOut)
            widgetFlag = 1;
        tableWidgetMove();
        detailWidgetMove();
        break;

    case 4:
        detailWidgetMove();
        newWidgetMove();
    }
}

void MainWindow::saveAndExit()
{
    QMessageBox question;
    question.setWindowTitle("请确认");
    question.setText("是否保存并且退出?");
    question.addButton(QMessageBox::Yes);
    question.addButton(QMessageBox::No);

    if (QMessageBox::No == question.exec())
    {
        this->close();
    }
    else
    {
        using namespace std;
        fstream file("students", ios_base::out);
        if (!file.is_open())
        {
            QMessageBox::warning(this, "警告", "保存失败", QMessageBox::Yes);
            return ;
        }
        else
        {
            QListIterator<Stu>  iterator(studentsList);
            while(iterator.hasNext())
                file.write((char *)&iterator.next(), sizeof(Stu));

            file.close();
            this->close();
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    if (2  == choice)
    {
        delete detailWidget;
        delete newStudentsWidget;
    }
    else
    {
        delete firstWidget;
        delete editStudentsWidget;
        delete detailWidget;
        delete newStudentsWidget;
    }
}

