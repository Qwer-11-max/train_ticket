# train_ticket
软件工程课设

这是软件工程的课设，我们编写了一个火车订票系统，实现了以下功能

## 通用
登录功能，用户选择不同的登录界面从而进入不同的用户界面，分别为管理员界面和乘客界面。
PS.管理员账号为123456 密码为000000

## 乘客
购票 ： 登录后，乘客选择购票界面，在该界面中乘客选择出发地和目标地以及出发的时间，在确认以上信息之后，乘客即可点击购票按钮购票。
退票 ： 登陆后，乘客选择退票界面，在输入了票号后点击确认按钮即可退票。
改签 ： 登陆后，乘客选择改签界面，在选择要修改的出发时间后，再选择新的出发时间，最后点击确认即可修改出发时间。
返回 ： 点击后返回登录界面

## 管理员
添加 ：登录后，点击进入添加界面，管理员输入票务信息，即可在数据库中添加票务信息
删除 ：登陆后，点击进入删除界面，管理员输入票号，点击确认即可删除
修改 ：登陆后，点击进入修改界面，管理员可以直接在右边表格中修改，点击保存即可确认修改
PS.删除和修改都需要点击保存才能永久生效
统计 ：登陆后，点击进入修改界面，管理员选择日期后，点击统计按钮即可完成所选日期的统计

## 软件及其版本
开发软件 ：QT6.5
数据库 ： PostgreSQL 15.0
