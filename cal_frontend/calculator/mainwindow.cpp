#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1700,1700);
    ui->textEdit_show->setText("please press the button.");
    process="";
    result=0;
    S="";
    stat=0;
    choose=0;
    sum=0;
    dot=0;
    ui->textEdit_show->setWordWrapMode(QTextOption::NoWrap);
    textBrowser_history = ui->textBrowser_history;
    textBrowser_history->setVisible(false);
    ui->textEdit_show->setAlignment(Qt::AlignLeft);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_Exit_clicked()
{
    close();
}

void MainWindow::on_pushButton_clear_clicked()
{
    result=0;
    S="";
    process="";
    stat=0;
    choose=0;
    ui->textEdit_show->setText("please press the button");
    dot=0;
}

void MainWindow::on_pushButton_equal_clicked()
{
    QString calculation = ui->textEdit_show->toPlainText();
    switch (choose)
    {
        case 1:

        result+=S.toFloat()+process.toFloat();
        sum=result;

        Sresult=QString("%1").arg(result);
        ui->textEdit_show->setText(Sresult);
        break;
    case 2:
        result+=S.toFloat()-process.toFloat();
        sum=result;
        Sresult=QString("%1").arg(result);
        ui->textEdit_show->setText(Sresult);
        break;
    case 3:

        if(sum==0)
        {
            result=1;
        }
        else
        {
            result=sum;
        }
        if(S.toFloat()*process.toFloat()!=0)
        {
        result*=S.toFloat()*process.toFloat();
        qDebug()<<result<<""<<sum;
        }
        else
        {
            result*=(S.toFloat()+process.toFloat());
            qDebug()<<result<<""<<sum;
        }
        sum=result;
        Sresult=QString("%1").arg(result);
        ui->textEdit_show->setText(Sresult);
        break;
    case 4:
        if(process.toFloat()==0)
        {
            ui->textEdit_show->setText("system error!");
            QTimer::singleShot(1000,this,SLOT(on_pushButton_clear_clicked()));

            break;
        }
        if(sum==0)
        {
            result=1;
        }
        else
        {
            result=sum;
        }
        if(S.toFloat()/process.toFloat()!=0)
        {
        result=S.toFloat()/process.toFloat();
        qDebug()<<result<<""<<sum;
        }
        else
        {
            result/=(S.toFloat()+process.toFloat());
            qDebug()<<result<<""<<sum;
        }
        sum=result;
        Sresult=QString("%1").arg(result);
        ui->textEdit_show->setText(Sresult);
        break;
    case 5: // 取余操作
        if (process.toFloat() == 0)
        {
            ui->textEdit_show->setText("除数不能为零！");
            QTimer::singleShot(1000, this, SLOT(on_pushButton_clear_clicked()));
            break;
        }
        result = static_cast<int>(S.toFloat()) % static_cast<int>(process.toFloat());
        sum = result;
        Sresult = QString("%1").arg(result);
        ui->textEdit_show->setText(Sresult);
        break;

    }
    // 插入历史记录到数据库

    sum=result;
    stat=-1;//如果刚按了等号又按数字，相当于做了一次AC，如果按了等号再按加号，就继续计算。
    choose=0;//告诉程序可以重新接受运算符
    S="";
    process="";
    //因为连续计算，所以不将过程值清0
    QString result = Sresult;
    QSqlQuery query;
        query.prepare("INSERT INTO History (Calculation, Result) VALUES (?, ?)");
        query.addBindValue(calculation);
        query.addBindValue(result);

        if (query.exec()) {
            qDebug() << "Record inserted!";
        } else {
            qWarning() << "Insert failed: " << query.lastError().text();
        }

        // 在历史记录文本框中显示完整的历史记录，包括计算过程
        textBrowser_history->setText(calculation + " = " + result);


}

void MainWindow::on_pushButton_1_clicked()
{   ui->textEdit_show->setAlignment(Qt::AlignLeft);
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }

    if(choose==0)
    {
    S+="1";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="1";;
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="2";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="2";
        ui->textEdit_show->insertPlainText(process);
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="3";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="3";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="4";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="4";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="5";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="5";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="6";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="6";
        ui->textEdit_show->insertPlainText(process);

    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="7";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="7";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="8";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="8";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="9";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="9";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_0_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="0";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="0";
        ui->textEdit_show->insertPlainText(process);
    }
}

void MainWindow::on_pushButton_plus_clicked()
{
    if(stat==0||stat==-1)
    {
        ui->textEdit_show->insertPlainText("+");
    }
    stat=1;
    choose=1;
    dot=0;
}

void MainWindow::on_pushButton_jian_clicked()
{
    if(stat==0||stat==-1)
    {
        ui->textEdit_show->insertPlainText("-");
    }
    stat=1;
    choose=2;
    dot=0;
}

void MainWindow::on_pushButton_chen_clicked()
{
    if(stat==0||stat==-1)
    {
        ui->textEdit_show->insertPlainText("*");

    }
    sum=result;
    stat=1;
    choose=3;
    dot=0;
}
void MainWindow::on_pushButton_divide_clicked()
{
    if(stat==0||stat==-1)
    {
        ui->textEdit_show->insertPlainText("/");

    }
    sum=result;
    stat=1;
    choose=4;
    dot=0;
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(dot==0)
    {
    if(choose==0)
    {
        S+=".";
        ui->textEdit_show->setText(S);
    }
    else if(choose!=0)
    {
        process+=".";
        ui->textEdit_show->setText(process);
    }
    }
    stat=1;
    dot=1;
}

void MainWindow::on_pushButton_BackSpace_clicked()
{

    if(choose==0)
    {
    S.chop(1);//退一格
    ui->textEdit_show->setText(S);
    }
    else if(choose!=0)
    {
        process.chop(1);
        ui->textEdit_show->setText(process);
    }

}

void MainWindow::on_pushButton_00_clicked()
{
    if(stat==-1)
    {
        result=sum;
        on_pushButton_clear_clicked();
    }
    if(choose==0)
    {
    S+="00";
    ui->textEdit_show->setText(S);
    QTextCursor cursor = ui->textEdit_show->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_show->setTextCursor(cursor);
    }
    else if(choose!=0)
    {
        QTextCursor cursor = ui->textEdit_show->textCursor();

        // 将光标移动到要删除的字符之前
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, process.length());

        // 删除选中的字符
        cursor.removeSelectedText();
        process+="00";
        ui->textEdit_show->insertPlainText(process);
    }
}
void MainWindow::on_pushButton_mod_clicked()
{
    if (stat == 0 || stat == -1)
    {
        ui->textEdit_show->insertPlainText("%");
    }
    stat = 1;
    choose = 5;  // 5表示取余操作
    dot = 0;
}
void MainWindow::on_showHistoryButton_clicked()
{
    if (ui->textBrowser_history->isVisible()) {
        // 如果文本框可见，隐藏它
        ui->textBrowser_history->setVisible(false);
    } else {
        // 如果文本框不可见，显示它
        ui->textBrowser_history->setVisible(true);
    }
}
