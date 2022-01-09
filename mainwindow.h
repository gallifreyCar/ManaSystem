#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"linksqLite.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();//初始化，给部分组件增加特性
    void edit(QModelIndex index);
private slots:

    void on_loginButton_clicked();//login按钮监听 槽函数
    void on_zhedie_clicked();//折叠按钮的实现

    void on_findButton_clicked();

    void on_editButton_clicked();

    void on_delete_2_clicked();

    void on_addButton_clicked();

    void on_addButton22_clicked();

    void on_EmpTable_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    LinkSQLite sql;
    bool loginFlag=false;

};
#endif // MAINWINDOW_H
