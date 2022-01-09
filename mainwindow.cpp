#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linksqLite.h"
#include<QPropertyAnimation>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <form.h>
#include <addform.h>
#include <QSqlTableModel>
#include "qinputdialog.h"
#include<QTableWidgetItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//登陆校验
void MainWindow::on_loginButton_clicked()
{
    if(ui->usernameLine->text()=="admin" and ui->passwordLine->text()=="admin"){

    ui->loginError->setVisible(false);
    sql.showTable(ui);
    loginFlag=true;
    ui->tips->setText("登陆成功");
    }else{
    ui->loginError->setVisible(true);
    loginFlag=false;
     ui->tips->setText("登陆失败");
    }

}



//初始化
void MainWindow::init(){

    ui->passwordLine->setEchoMode(QLineEdit::Password);  //隐藏密码
    ui->loginError->setVisible(false);
    ui->tips->setText(sql.isLink());
    ui->EmpTable->setVisible(true);
    ui->SetForm->setVisible(false);
}





//折叠按钮的实现
void MainWindow::on_zhedie_clicked()
{
    QPropertyAnimation *time;//定义动画类指针
    time = new QPropertyAnimation(ui->left, "geometry");//新建一个动画
    time->setDuration(100);//设置动画飞出时间
    time->setStartValue(QRect(0, 0, 275, 615));//设置动画起始位置
    time->setEndValue(QRect(-275, 0, 0, 615));//设置动画结束位置
    time->start();//动画开始*/
    connect(time, &QAbstractAnimation::finished, [=]() {
        if( ui->left->isVisible()==true) ui->left->setVisible(false);
       else ui->left->setVisible(true);
    });
}


//查找按钮实现
void MainWindow::on_findButton_clicked()
{   if(loginFlag==true){
        sql.find(ui);
        ui->tips->setText("查询成功");
    }else{
    ui->tips->setText("查询失败");}
}


//更改按钮
void MainWindow::on_editButton_clicked()
{   QModelIndex index=ui->EmpTable->currentIndex();
    edit(index);
}

//删除按钮的实现
//void MainWindow::on_delete_2_clicked()
//{
//    if(!loginFlag){
//         ui->tips->setText("请登录");
//        return ;
//    }
//    if(QMessageBox::Yes == QMessageBox::question(this,"Make Sure","确定删除吗？",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes))
//       {//提示框，防止误操作，是/否，按下是的操作后
//          sql.deleteOne(this,ui);
//          ui->tips->setText("删除成功");
//       }

//}


//删除按钮的实现2
void MainWindow::on_delete_2_clicked()
{
    if(!loginFlag){
                     ui->tips->setText("请登录");
                    return ;
    }
    int row = ui->EmpTable->currentIndex().row();
    if(QMessageBox::Yes == QMessageBox::question(this,"Warnning","确定删除第"+QString::number(row+1)+"行吗？",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes))
    {
        QSqlTableModel * model = new QSqlTableModel(this,sql.getDB());
        model->setTable("EmpMoney");//设置表
        if(model->select())//判断是否为空表
            model->removeRow(row);
        model->submitAll();
        ui->EmpTable->setModel(model);
        sql.showTable(ui);
        ui->tips->setText("成功删除");
    }
}





//添加按钮的实现1
void MainWindow::on_addButton_clicked()
{
    if(!loginFlag){
        ui->tips->setText("请登录");
        return ;
    }

    if(ui->EmpTable->isVisible()==true){
    ui->EmpTable->setVisible(false);
    ui->SetForm->setVisible(true);
    }else{
        ui->EmpTable->setVisible(true);
        ui->SetForm->setVisible(false);
    }

}

//添加按钮的实现2
void MainWindow::on_addButton22_clicked()
{
    sql.add(ui);
    ui->SetForm->setVisible(false);
    ui->EmpTable->setVisible(true);
    sql.showTable(ui);
    ui->tips->setText("添加表单成功");
}

//双击行直接更改
void MainWindow::on_EmpTable_doubleClicked(const QModelIndex &index)
{
    edit(index);
}

//封装更改方法主体
void MainWindow::edit(QModelIndex index){

    QSqlTableModel * model = new QSqlTableModel(this,sql.getDB());
    model->setTable("EmpMoney");
    bool isOK;
    QString text = QInputDialog::getText(this,"Update","修改当前内容",QLineEdit::Normal,index.data().toString(),&isOK);
    if(!isOK)
        return ;
    if(model->select())
        model->setData(model->index(index.row(),index.column()+1),text);//列数加一，因为我省去了第一列--- id
    model->submitAll();//提交修改
    ui->EmpTable->setModel(model);
    sql.showTable(ui);
    ui->tips->setText("成功修改");



}

