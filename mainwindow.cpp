#include <QtSql>
#include <QSqlDatabase>
#include <QModelIndex>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbfunctions.h"
#include "mydelegate.h"

//-------------------------------------------------------------------
//
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    menu_(new QMenu(this)),
    createConnection_(new QAction("Create connection", this)),
    closeConnection_(new QAction("Close connection", this)),
    createTable_(new QAction("Create table", this)),
    insertInto_(new QAction("Insert into", this)),
    insertIntoOracle_(new QAction("Oracle Insert into", this)),
    insertIntoODBC_(new QAction("ODBC addBindValue Insert into", this)),
    insertIntoODBCbind_(new QAction("ODBC bindValue Insert into", this)),
    printTable_(new QAction("Print table", this)),
    dropTable_(new QAction("Drop table", this)),
    initTableModel_(new QAction("Init tablemodel", this)),
    selectTable_(new QAction("Select table", this)),
    insertRow_(new QAction("Insert row", this)),
    remoweRow_(new QAction("Remove row", this)),
    doQuery_(new QAction("Do query", this)),
    connectName_("myConnection"),
    tableName_("rectangle")
{
    ui->setupUi(this);
    this->setMinimumWidth(1800);
    this->setMinimumHeight(1000);

    createmenu();
    connections();
}

//-------------------------------------------------------------------
//
MainWindow::~MainWindow()
{
    closeConnection();
    delete ui;
}

//-------------------------------------------------------------------
//
void MainWindow::createmenu()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    menu_ = menuBar()->addMenu("BD");
    menu_->addAction(createConnection_);
    menu_->addAction(closeConnection_);
    menu_->addAction(createTable_);
    menu_->addAction(insertInto_);
    menu_->addAction(insertIntoOracle_);
    menu_->addAction(insertIntoODBC_);
    menu_->addAction(insertIntoODBCbind_);
    menu_->addAction(printTable_);
    menu_->addAction(dropTable_);

    menu_ = menuBar()->addMenu("Model");
    menu_->addAction(initTableModel_);
    menu_->addAction(selectTable_);
    menu_->addAction(insertRow_);
    menu_->addAction(remoweRow_);

    menu_ = menuBar()->addMenu("Query");
    menu_->addAction(doQuery_);

}

//-------------------------------------------------------------------
//
void MainWindow::connections()
{
    connect(createConnection_, SIGNAL(triggered()), this, SLOT(createConnection()));
    connect(closeConnection_, SIGNAL(triggered()), this, SLOT(closeConnection()));
    connect(createTable_, SIGNAL(triggered()), this, SLOT(createTable()));
    connect(dropTable_, SIGNAL(triggered()), this, SLOT(deleteTable()));
    connect(insertInto_, SIGNAL(triggered()), this, SLOT(insertInto()));
    connect(insertIntoOracle_, SIGNAL(triggered()), this, SLOT(insertIntoOracle()));
    connect(insertIntoODBC_, SIGNAL(triggered()), this, SLOT(insertIntoODBC()));
    connect(insertIntoODBCbind_, SIGNAL(triggered()), this, SLOT(insertIntoODBCbind()));
    connect(printTable_, SIGNAL(triggered()), this, SLOT(printTable()));
    connect(initTableModel_, SIGNAL(triggered()), this, SLOT(initModel()));
    connect(selectTable_, SIGNAL(triggered()), this, SLOT(selectTable()));
    connect(insertRow_, SIGNAL(triggered()), this, SLOT(insertRows()));
    connect(remoweRow_, SIGNAL(triggered()), this, SLOT(removeRow()));

}

//-------------------------------------------------------------------
//
void MainWindow::createConnection()
{
    for (QString strDrv : QSqlDatabase::drivers())
        qDebug()<< strDrv;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectName_);
    db.isValid() ? qDebug()<<"Connected" : qDebug()<<db.lastError().isValid();

    db.setDatabaseName("rectangle_data.sqlite");

    if (!db.open())
        qDebug() << "Error to open";
    return;
}

//-------------------------------------------------------------------
//
void MainWindow::closeConnection()
{
    {                                                                           // { ВАЖНО!
        QSqlDatabase db = QSqlDatabase::database(connectName_);
        if (!db.isOpen()) return;
        db.close();
    }                                                                           // } ВАЖНО!
    QSqlDatabase::removeDatabase(connectName_);
    qDebug() << "Close connection";
    model_->select();
}

//-------------------------------------------------------------------
//
void MainWindow::createTable()
{
    bool tmp = bd::dbCreateTable(connectName_, tableName_);
    qDebug() << "Create table: " << tmp;
}

//-------------------------------------------------------------------
//
void MainWindow::deleteTable()
{
    bool tmp = bd::dbDeleteTable(connectName_, tableName_);
    qDebug() << "Drop table: " << tmp;
    model_->select();
}

//-------------------------------------------------------------------
//
void MainWindow::insertInto()
{
    bool tmp = bd::dbInsertInto(connectName_, tableName_);
    qDebug() << "InsertInto: " << tmp;
    model_->select();
}

//-------------------------------------------------------------------
//
void MainWindow::insertIntoOracle()
{
    bool tmp = bd::dbInsertIntoOracle(connectName_, tableName_);
    qDebug() << "ORACLE_InsertInto: " << tmp;
    model_->select();
}

//-------------------------------------------------------------------
//
void MainWindow::insertIntoODBC()
{
    bool tmp = bd::dbInsertIntoODBC(connectName_, tableName_);
    qDebug() << "ODBC_addBindValue_InsertInto: " << tmp;
    model_->select();
}

//-------------------------------------------------------------------
//
void MainWindow::insertIntoODBCbind()
{
    bool tmp = bd::dbInsertIntoODBCbind(connectName_, tableName_);
    qDebug() << "ODBC_bindValue_InsertInto: " << tmp;
    model_->select();
}

//-------------------------------------------------------------------
//
void MainWindow::printTable()
{
    bool tmp = bd::dbPrintTable(connectName_, tableName_);
    qDebug() << "PrintTable: " << tmp;
}

//-------------------------------------------------------------------
//
void MainWindow::initModel()
{
    QSqlDatabase db = QSqlDatabase::database(connectName_);
    if (!db.isValid()) return ;

    model_ = new QSqlTableModel(this, db);
    model_->setTable(tableName_);
    model_->select();
    model_->setEditStrategy(QSqlTableModel::OnFieldChange);  //OnFieldChange 	0	Изменения модели применяются сразу к БД
                                                             //OnRowChange 	1 (умолч.)	Изменения строки применяются  при  выборе другой строки  или элемента
                                                             //OnManualSubmit 	2 	Изменения  кэшируются пока не будет вызвана submitAll()

    ui->tableView->setModel(model_);
    ui->tableView->hideColumn(0);

    QStringList headerData = {"Color", "Style", "Pen Width", "Left", "Top", "Width", "Height"};
    int i = 1;
    for (const auto & header : headerData)
    {
        model_->setHeaderData(i, Qt::Horizontal, header);
        i++;
    }

    MyDelegate *delegate = new MyDelegate(ui->tableView);
    ui->tableView->setItemDelegate(delegate);
}

//-------------------------------------------------------------------
//
void MainWindow::selectTable()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    bool tmp = bd::dbSelectTable(connectName_, tableName_, selection);
    qDebug() << "SelectTable: " << tmp;
}

//-------------------------------------------------------------------
//
void MainWindow::insertRows()
{
    int rows = model_->rowCount();
    qDebug() << "InsertRows: " << model_->insertRows(rows, 1);
}

//-------------------------------------------------------------------
//
void MainWindow::removeRow()
{
    QModelIndex index = ui->tableView->currentIndex();
    qDebug() << "DeleteRows: " << model_->removeRows(index.row(), 1);
    model_->select();
}
