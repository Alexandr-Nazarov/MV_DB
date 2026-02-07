#ifndef DBFUNCTIONS_H
#define DBFUNCTIONS_H
#include <QString>

namespace bd {
/**
 * @brief Создать таблицу
 * @param connectName
 * @return
 */
bool dbCreateTable(const QString& connectName, const QString &table);
/**
 * @brief Удалить таблицу
 * @param connectName
 * @return
 */
bool dbDeleteTable(const QString& connectName, const QString &table);
/**
 * @brief Добавление записей
 * @param connectName
 * @param table
 * @return
 */
bool dbInsertInto(const QString& connectName, const QString &table);
/**
 * @brief Добавление записей в стиле ORACLE
 * @param connectName
 * @param table
 * @return
 */
bool dbInsertIntoOracle(const QString& connectName, const QString &table);
/**
 * @brief Добавление записей в стиле ODBC и addBindValue
 * @param connectName
 * @param table
 * @return
 */
bool dbInsertIntoODBC(const QString& connectName, const QString &table);
/**
 * @brief Добавление записей в стиле ODBC и bindValue
 * @param connectName
 * @param table
 * @return
 */
bool dbInsertIntoODBCbind(const QString& connectName, const QString &table);
/**
 * @brief Распечатать таблицу
 * @param connectName
 * @param table
 * @return
 */
bool dbPrintTable(const QString& connectName, const QString &table);
/**
 * @brief Выбрать таблицу
 * @param connectName
 * @param table
 * @return
 */
bool dbSelectTable(const QString& connectName, const QString &table, QItemSelectionModel *selection);


}
#endif // DBFUNCTIONS_H
