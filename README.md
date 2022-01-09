## 1	概述	

### 1.1程序的基本功能

#### 1.1.1 登陆功能

该系统设置了管理员登陆校验，只有输入正确的管理员账号和密码成功登陆才能进行相应的权限操作。

#### 1.1.2 查询功能

该系统设置模糊（前模糊和后模糊）查找功能，可以根据职工编号快速找到相应的职工信息

#### 1.1.3 删除功能

该系统具有删除职工工资信息功能

#### 1.1.4 新增表单功能

该系统具有新增表单功能

#### 1.1.5 修改数据功能

该系统可方便更改数据	

#### 1.1.6账目自动统计

该系统会自动统计职工的每月工资，应发数，个人所得税，实发数，并确保计算所得数据准确且无法被人为修改。

### 1.2其他功能	

#### 1.2.1信息安全

该系统将信息保存在本地的文件类型数据库SQLite中，确保数据安全。

#### 1.2.2可视化界面

该系统具有美观，易读，易操作的可视化界面

#### 1.2.3动画效果

部分组件增加动画效果，提高观赏性

## 2	课题的分析	

### 2.1	图形化界面开发框架选择

考虑到是给用户使用的工资管理系统，我认为可视化的界面是必不可少的。因为C++的标准库中并没有包含GUI，我只能从第三方C++图形化界面开发库中选择。最终我选择了Qt，因为Qt是一个比较老的C++图形界面开发框架，各种功能都比较完善，问题解决方法也比较多，有优秀的跨平台性。而且集成开发工具和跨平台的IDE，可视化地图形化界面设计，可以减少很多前端学习成本。

### 2.2	数据库选择

考虑要存储数据，我第一时间想到的就是数据库。我最初想使用mysql数据库的，因为我个人对MySQL数据库比熟悉，而且mysql数据库配合navicat可以极大加快我的开发效率。但是因为Qt对MySQL的驱动支持问题（mysql版本太多），最终还是使用Qt自带的数据库SQLite。SQLite是一款轻型的数据库，它的设计目标是嵌入式的，而且已经在很多嵌入式产品中使用了它，它占用资源非常的低。

### 2.3   MVC模式

这次课程设计，我打算用mvc模式来写。将视图，模型，控制器和业务逻辑等分离出来。但是毕竟是一个C++的课设，而我又从未接触过Qt，所以可能只是尽可能往mvc模式方向设计。但并不能说严格地像springboot一样规范。





## 3	详细设计	

### 3.1	数据库设计

![image-20211231073900186](E:\HUMEN\学习笔记\picture\image-20211231073900186-16409075427701.png)

EmpMoney（职工工资）就是我这次用到的数据库表，SQLite只有4种数据类型，除了表主键id，职工编号empID外，其余用于计算工资的数值类型均选择了与double亲和类型最近的real类型

| 亲和类型 | 描述                                                         |
| :------- | :----------------------------------------------------------- |
| TEXT     | 数值型数据在被插入之前，需要先被转换为文本格式，之后再插入到目标字段中。 |
| NUMERIC  | 当文本数据被插入到亲缘性为NUMERIC的字段中时，如果转换操作不会导致数据信息丢失以及完全可逆，那么SQLite就会将该文本数据转换为INTEGER或REAL类型的数据，如果转换失败，SQLite仍会以TEXT方式存储该数据。对于NULL或BLOB类型的新数据，SQLite将不做任何转换，直接以NULL或BLOB的方式存储该数据。需要额外说明的是，对于浮点格式的常量文本，如"30000.0"，如果该值可以转换为INTEGER同时又不会丢失数值信息，那么SQLite就会将其转换为INTEGER的存储方式。 |
| INTEGER  | 对于亲缘类型为INTEGER的字段，其规则等同于NUMERIC，唯一差别是在执行CAST表达式时。 |
| REAL     | 其规则基本等同于NUMERIC，唯一的差别是不会将"30000.0"这样的文本数据转换为INTEGER存储方式。 |
| NONE     | 不做任何的转换，直接以该数据所属的数据类型进行存储。         |

### 3.2	实体类模型设计

数据中所有职工工资映射的实体类

### 3.3	数据库连接层设计


LinkSQLite类的设计，用于连接数据，编写SQLite的sql语句，数据库的增删改查得以实现

### 3.4	控制器和视图交互	

视图层和控制器合二为一 了，删去冗余的业务逻辑层，在mainwindow完成了模型和视图的交互，并处理业务逻辑。

## 4	课程设计总结	

### 4.1	完成情况	

#### 4.1.1登陆功能

1.登陆失败提醒 （管理员初始账号密码均为:admin）

![clip_image010](https://user-images.githubusercontent.com/29010376/148675410-21dbcce0-80bd-4d09-8314-0c3dffae8992.png)


2.登陆成功显示所有职工工资信息

![clip_image012](https://user-images.githubusercontent.com/29010376/148675426-70160239-7081-4267-9be4-b3ede68473e5.png)


#### 4.1.2查询功能

1.精确查询  （登陆页面提供折叠功能，已经折叠）

![clip_image014](https://user-images.githubusercontent.com/29010376/148675446-5af672aa-6d33-499e-85bf-40bbb521d9ae.png)

2.模糊查询
![clip_image016](https://user-images.githubusercontent.com/29010376/148675472-c2ac0ad8-dc5a-4310-89ad-4cd0c2cecd1e.png)

#### 4.1.3删除功能

![clip_image028](https://user-images.githubusercontent.com/29010376/148675551-66ff37ec-4fd7-40a5-8917-7fab34a65fa2.png)


#### 4.1.3新增表单功能

1.点击查找旁边的增加表单按钮 进入新增表单页面

![clip_image024](https://user-images.githubusercontent.com/29010376/148675589-903ef373-f46c-4a9a-a4bc-4800f1076d53.png)

2.填写并提交

![clip_image026](https://user-images.githubusercontent.com/29010376/148675638-fdf59357-4c83-4b4d-ad8d-66eb38db163c.png)


3.自动计算工资税务，应发数，实发数
![clip_image028-16413769338422](https://user-images.githubusercontent.com/29010376/148675649-24c6318d-a216-4e1f-85df-b7678e4ba3c1.png)




4.14修改
![clip_image032](https://user-images.githubusercontent.com/29010376/148675656-09efae92-b5a8-4b87-bb5e-c4a7071c92ae.png)


### 4.2	遇到的问题及解决	

​	SQLite字符串传参多次失效，改用Qt的字符串类型QString，情况极大改善。

​	添加数据的输入文本框设计时，数据库连接中断，程序崩坏。后查明是io流阻塞问题，采用单窗口解决了。

## 参考文献	

1.[SQLite 教程 | 菜鸟教程 (runoob.cohttps://www.runoob.com/sqlite/sqlite-tutorial.htmlm)](https://www.runoob.com/sqlite/sqlite-tutorial.html)

https://www.runoob.com/sqlite/sqlite-tutorial.html

2.[User Interface Design Toolshttps://www.qt.io/design | The Best UI Design Software | Qt Designer | Qt](https://www.qt.io/design)

3.[(21条消息) Qt主线程阻塞导致消息队列中的uart动作处理不及时(处理耗时操作导致界面卡顿)_我金啊的博客-CSDN博客_qt主线程被阻塞](https://blog.csdn.net/qq_42243240/article/details/110951793)

