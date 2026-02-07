#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /**
     * @brief Меню
     */
    void createmenu();
    /**
     * @brief Сигналы-слоты
     */
    void connections();

private slots:
    /**
     * @brief Создание соединения с БД
     */
    void createConnection();
    /**
     * @brief Закрыть соединения с БД
     */
    void closeConnection();
    /**
     * @brief Создать таблицу
     */
    void createTable();
    /**
     * @brief Удалить таблицу
     */
    void deleteTable();
    /**
     * @brief Добавить в таблицу
     */
    void insertInto();
    /**
     * @brief Добавить в таблицу в стиле Oracle
     */
    void insertIntoOracle();
    /**
     * @brief Добавить в таблицу в стиле ODBC  и addBindValue
     */
    void insertIntoODBC();
    /**
     * @brief Добавить в таблицу в стиле ODBC и bindValue
     */
    void insertIntoODBCbind();
    /**
     * @brief Распечатать таблицу
     */
    void printTable();
    /**
     * @brief Инициализировать модель
     */
    void initModel();
    /**
     * @brief выбрать Table
     */
    void selectTable();
    /**
     * @brief Добавляет строку в модель
     */
    void insertRows();
    /**
     * @brief Удаляет строку из модели
     */
    void removeRow();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QMenu          *menu_;
    QAction        *createConnection_;
    QAction        *closeConnection_;
    QAction        *createTable_;
    QAction        *insertInto_;
    QAction        *insertIntoOracle_;
    QAction        *insertIntoODBC_;
    QAction        *insertIntoODBCbind_;
    QAction        *printTable_;
    QAction        *dropTable_;
    QAction        *initTableModel_;
    QAction        *selectTable_;
    QAction        *insertRow_;
    QAction        *remoweRow_;
    QAction        *doQuery_;
    const QString  connectName_;
    QString        tableName_;
    QSqlTableModel *model_;

};

#endif // MAINWINDOW_H
