#include "file.h"
#include <qfile.h>
#include <qdebug.h>

#include "globalDefine.h"


char readSN(void)
{
    char res=0;
    QFile f(SNDIR);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return res;
    }

    QTextStream txtInput(&f);
    QString lineStr;

    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();

        if(qMapSn.contains(lineStr)){

            //qDebug()<<"already exist"+lineStr;
        }
        else
        {
            //QMap<QString,QString>::iterator it = m_map.find("111"); //找到特定的“键-值”对
            //qDebug("find 111 , value is : " + it.data()); //获取map里对应的值


            qMapSn.insert(lineStr, 0);

            qDebug()<<lineStr;
            res=1;
        }

    }

    f.remove();
    f.close();

    return res;
}
/*
 *
 * void showMap()
    {
    if(!m_map.isEmpty()) return; //判断map是否为空
    m_map.insert("111", "aaa"); //向map里添加一对“键-值”
    if(!m_map.contains("222")) //判断map里是否已经包含某“键-值”
        m_map.insert("222", "bbb");
    m_map["333"] = "ccc"; //另一种添加的方式
    qDebug("map[333] , value is : " + m_map["333"]); //这种方式既可以用于添加，也可以用于获取，但是你必须知道它确实存在

    if(m_map.contains("111")){
            QMap<QString,QString>::iterator it = m_map.find("111"); //找到特定的“键-值”对
            qDebug("find 111 , value is : " + it.data()); //获取map里对应的值
    }
    cout<< endl;
    qDebug("size of this map is : %d", m_map.count()); //获取map包含的总数
    cout<< endl;
    QMap<QString,QString>::iterator it; //遍历map
    for ( it = m_map.begin(); it != m_map.end(); ++it ) {
            qDebug( "%s: %s", it.key().ascii(), it.data().ascii()); //用key()和data()分别获取“键”和“值”
        }

    m_map.clear(); //清空map
    }    */

/*
 *
 *
 *  //获取系统现在的时间并设置显示格式
 QDateTime current_date_time = QDateTime::currentDateTime();
 QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
 例：2013-05-24 13:09:10 周五

 //获取当前时间，范围：小时(0--23)、分钟(0--59)、秒(0--59)、毫秒(0--999)
 QTime current_time = QTime::currentTime();
 int hour = current_time.hour();
 int minute = current_time.minute();
 int second = current_time.second();
 int msec = current_time.msec();

 */
