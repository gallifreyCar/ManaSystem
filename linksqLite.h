#include <QSqlDatabase>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    "user.h"
#include "addform.h"
#include "ui_addform.h"
#ifndef LINKSQLITE_H
#define LINKSQLITE_H


class LinkSQLite
{
    private:
    QSqlDatabase database;
    QVector<User> UserVector;
public:
    LinkSQLite();
    ~LinkSQLite();
    QString isLink();
    void showTable(Ui::MainWindow *ui);
    void add(Ui::MainWindow *ui);
    void deleteOne( QObject *parent,Ui::MainWindow *ui);
    QSqlDatabase getDB();
    void fixTable();
    void find(Ui::MainWindow *ui);
    void MAndV(Ui::MainWindow *ui,QString temp);
};

#endif // LINKSQLITE_H
