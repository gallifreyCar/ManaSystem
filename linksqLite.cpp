#include "linksqLite.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>
//构造函数
LinkSQLite::LinkSQLite()
{
      //连接数据库
      database = QSqlDatabase::addDatabase("QSQLITE");
      database.setDatabaseName("MyDataBase.db");
      if (!database.open())
      {
           qDebug()<< "数据库连接失败" ;
      }
      else
      {
          qDebug()<< "数据库连接成功" ;
      }


}

//打印一下数据库连接情况
QString LinkSQLite::isLink(){
    if (!database.open())
    {
         return "数据库连接失败" ;
    }
    else
    {
        return "数据库连接成功" ;
    }
}


//查询全部 显示所有工资的信息
void LinkSQLite::showTable(Ui::MainWindow *ui){
        fixTable();
        QString temp=QString("select * from EmpMoney");
        MAndV(ui,temp);
}


//编号模糊查询并工资信息
void LinkSQLite::find(Ui::MainWindow *ui){

    QString who=ui->find->text();
    QString temp=QString("select * from EmpMoney where empid like '%%1%'  ").arg(who.toInt());
    MAndV(ui,temp);
}



//
void LinkSQLite::add(Ui::MainWindow *ui){
    QString basePay=ui->basepay->text();
    QString  empID=ui->empid->text();
    QString  allowance=ui->allo->text();
    QString  subsidy=ui->subsidy->text();
    QString  posteSub=ui->posteSub->text();
    QString  punishment=ui->punish->text();
    QString temp=QString("insert into EmpMoney (empID,basePay,allowance,subsidy,PosteSub,punishment)values(%1,%2,%3,%4,%5,%6) ")
            .arg(empID.toInt())
            .arg(basePay.toDouble())
            .arg(allowance.toDouble())
            .arg(subsidy.toDouble())
            .arg(posteSub.toDouble())
            .arg(punishment.toDouble());
    qDebug()<<temp;
    MAndV(ui,temp);
}


//删除方法 暂时废弃
//void LinkSQLite::deleteOne(QObject *parent,Ui::MainWindow *ui){
//     QString tempid=ui->find->text();
//     QString temp=QString("delete from EmpMoney where empid = %1 ").arg(tempid.toInt());
//     MAndV(ui,temp)
//}



//获取全部User对象 计算应发数，税收和实发工资，补全表格
void LinkSQLite::fixTable(){
    QSqlQuery query;
    QString temp=QString("select * from EmpMoney");
    query.exec(temp);

    while(query.next()){
    User user;
    user.setEmpId(query.value("empID").toInt());
    user.setAllowance(query.value("allowance").toDouble());
    user.setBasePay(query.value("basePay").toDouble());
    user.setSubsidy(query.value("subsidy").toDouble());
    user.setPosteSub(query.value("PosteSub").toDouble());
    user.setPunishment(query.value("Punishment").toDouble());
    UserVector.append(user);
    }



    //处理应发数 税收 实发数
    for(int i=0;i<UserVector.size();i++){
      UserVector[i].setDeserve(UserVector[i].countDeserve());
      UserVector[i].setTax(UserVector[i].couTax());
      UserVector[i].setRealGet(UserVector[i].CountRealGet());
      temp=QString("update EmpMoney set deserve = %1 , tax = %2 , realGet =%3 where empid =%4")
              .arg(UserVector[i].getDeserve())
              .arg(UserVector[i].getTax())
              .arg(UserVector[i].getRealGet())
              .arg(UserVector[i].getEmpId());
      query.exec(temp);
    }

    //
}

//获取数据库
QSqlDatabase LinkSQLite::getDB(){
    return database;
}

//析构函数
LinkSQLite:: ~LinkSQLite(){
    database.close();
}

//update模型和视图
void LinkSQLite::MAndV(Ui::MainWindow *ui,QString temp){
    static QSqlQueryModel *mode= new QSqlQueryModel(ui->EmpTable);
    mode->setQuery(temp);
    mode->removeColumn(0);
    ui->EmpTable->setModel(mode);
    mode->setHeaderData(0,Qt::Horizontal, "职工编号");
    mode->setHeaderData(1,Qt::Horizontal, "基本工资");
    mode->setHeaderData(2,Qt::Horizontal, "津贴");
    mode->setHeaderData(3,Qt::Horizontal, "补贴");
    mode->setHeaderData(4,Qt::Horizontal, "岗贴");
    mode->setHeaderData(5,Qt::Horizontal, "应发数");
    mode->setHeaderData(6,Qt::Horizontal, "个人所得税");
    mode->setHeaderData(7,Qt::Horizontal, "应扣数");
    mode->setHeaderData(8,Qt::Horizontal, "实发数");

}

