#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QItemSelectionModel>
#include "dbfunctions.h"
#include "myrect.h"

//-------------------------------------------------------------------
//
bool bd::dbCreateTable(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

    QSqlQuery query(db);

    QString qstr = "CREATE TABLE " + table + " ( "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "pencolor VARCHAR, "
                   "penstyle INTEGER, "
                   "penwidth INTEGER, "
                   "left INTEGER, "
                   "top INTEGER, "
                   "width INTEGER, "
                   "height INTEGER );";

    bool b = query.exec(qstr);
    if (query.lastError().isValid())
    {
        qDebug()<<query.lastError();
    }
    return b;
}

//-------------------------------------------------------------------
//
bool bd::dbDeleteTable(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

    QStringList list = db.tables();
    if (list.contains(table))
    {
        QString qstr = "DROP TABLE " + table + " ;";

        QSqlQuery query(qstr, db);

        if (query.lastError().isValid())
        {
            qDebug()<<query.lastError();
            return false;
        }
        return true;
    }
    return false;
}

//-------------------------------------------------------------------
//
bool bd::dbInsertInto(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

     QSqlQuery query(db);

     QString qstr = "INSERT INTO " + table + " (pencolor, penstyle) "
                    "VALUES ('#ff0000', 1) ;";

     bool b = query.exec(qstr);
     if (query.lastError().isValid())
     {
         qDebug()<<query.lastError();
     }
     return b;
}

//-------------------------------------------------------------------
//
bool bd::dbInsertIntoOracle(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

     QSqlQuery query(db);

     QString qstr = "INSERT INTO " + table + " (left, top, width, height) "
                                             "VALUES (:left, :top, :width, :height) ;";
     query.prepare(qstr);

     query.bindValue(":left", 10);
     query.bindValue(":top", 100);
     query.bindValue(":width", 50);
     query.bindValue(":height", 500);

     bool b = query.exec();
     if (query.lastError().isValid())
     {
         qDebug()<<query.lastError();
     }
     return b;
}

//-------------------------------------------------------------------
//
bool bd::dbInsertIntoODBC(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

     QSqlQuery query(db);

     QString qstr = "INSERT INTO " + table + " (pencolor, penstyle, penwidth, left) "
                                             "VALUES (?, ?, ?, ?) ;";
     query.prepare(qstr);

     QVector<MyRect> rectVec = {MyRect(QRect(10,10,10,10), QPen(QColor("#00ff00"), 2, Qt::SolidLine)),
                                MyRect(QRect(0,0,200,100), QPen(QColor("#0000ff"), 1, Qt::DashLine))};


     bool b = false;
     for(const auto& val : rectVec)
     {
         query.addBindValue(val.color());
         query.addBindValue(static_cast<uint>(val.penStyle()));
         query.addBindValue(val.penWidth());
         query.addBindValue(val.rect().left());
         b = query.exec ();
         if (query.lastError().isValid())
         {
             qDebug()<<query.lastError();
             break;
         }
     }
     return b;
}

//-------------------------------------------------------------------
//
bool bd::dbInsertIntoODBCbind(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

     QSqlQuery query(db);

     QString qstr = "INSERT INTO " + table + " (pencolor, penstyle) "
                                             "VALUES (?, ?) ;";
     query.prepare(qstr);

     QVector<MyRect> rectVec = {MyRect(QRect(10,100,10,10), QPen(QColor("#0fff00"), 2, Qt::SolidLine)),
                                MyRect(QRect(10,0,200,100), QPen(QColor("#f000ff"), 1, Qt::DashLine))};


     bool b = false;
     for(const auto& val : rectVec)
     {
         query.bindValue(0, val.color());
         query.bindValue(1, static_cast<uint>(val.penStyle()));

         b = query.exec ();
         if (query.lastError().isValid())
         {
             qDebug()<<query.lastError();
             break;
         }
     }
     return b;
}

//-------------------------------------------------------------------
//
bool bd::dbPrintTable(const QString &connectName, const QString &table)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

     QSqlQuery query(db);

     QString qstr = "SELECT * FROM " + table + " ;";

     bool b = query.exec(qstr);
     if (query.lastError().isValid())
     {
         qDebug()<<query.lastError();
         return b;
     }

     while (query.next())
     {
         QSqlRecord rec = query.record();
         int id = query.value(rec.indexOf("id")).toInt();
         QVariant color = query.value(rec.indexOf("pencolor"));
         QVariant style = query.value(rec.indexOf("penstyle"));
         int pwidth = query.value(rec.indexOf("penwidth")).toInt();
         int left= query.value(rec.indexOf("left")).toInt();
         int top= query.value(rec.indexOf("top")).toInt();
         int width= query.value(rec.indexOf("width")).toInt();
         int height= query.value(rec.indexOf("height")).toInt();

         qDebug() << id << color.value<QColor>() << style.value<int>() << pwidth << left << top << width << height;
     }
     return b;

}

//-------------------------------------------------------------------
//
bool bd::dbSelectTable(const QString &connectName, const QString &table, QItemSelectionModel *selection)
{
    QSqlDatabase db = QSqlDatabase::database(connectName);
    if (!db.isValid()) return false;

    QSqlQuery query(db);

    QString qstr = "SELECT * FROM " + table + " ;";

    bool b = query.exec(qstr);
    if (query.lastError().isValid())
    {
        qDebug()<<query.lastError();
        return b;
    }

    do
    {
        QSqlRecord rec = query.record();
        int id = query.value(rec.indexOf("id")).toInt();
        QModelIndex index = selection->model()->index(id,0);
        QItemSelection sel;
        sel.select(index, index);
        if (index.isValid())
        selection->select(sel, QItemSelectionModel::Rows | QItemSelectionModel::Select);
    }
    while (query.next());

    return b;
}

