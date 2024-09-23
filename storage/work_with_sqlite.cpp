//#include <iostream>
//#include <string>
//#include <sql.h>
//#include <sqlext.h>
//#include <sqlite3.h>
//
//int main()
//{
//	sqlite3 *db;
//	char *errMsg = nullptr;
//	int rc;
//
//	// Open a database connection
//	rc = sqlite3_open("example.db", &db);
//	if (rc)
//	{
//		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//		return rc;
//	}
//	else
//	{
//		std::cout << "Opened database successfully" << std::endl;
//	}
//
//	// Create a SQL table
////	const char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS PERSON("
////										  "ID INT PRIMARY KEY NOT NULL,"
////										  "NAME TEXT NOT NULL);";
//
//
// // Выполняем запрос
////    ret = SQLExecDirect(stmt, (SQLCHAR *)query, SQL_NTS);
////
////    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
////        // Обработка результатов запроса
////        while (SQLFetch(stmt) != SQL_NO_DATA) {
////            // Здесь можно получить данные из столбцов
////            // Например, выводим данные в консоль
////            char name[255];
////            // Предполагаем, что поле NAME - это строка
////            SQLGetData(stmt, 1, SQL_C_CHAR, name, sizeof(name), NULL); // 1 - индекс столбца
////
////            printf("Имя: %s\n", name);
////        }
////    } else {
////        printf("Ошибка при выполнении запроса.\n");
////    }
//
////	rc = sqlite3_exec(db, sqlCreateTable, nullptr, 0, &errMsg);
////	if (rc != SQLITE_OK)
////	{
////		std::cerr << "SQL error: " << errMsg << std::endl;
////		sqlite3_free(errMsg);
////	}
////	else
////	{
////		std::cout << "Table created successfully" << std::endl;
////	}
//
//
////    const char *sq = "SELECT 'в' LIKE 'В';
//    const char *query = "SELECT * FROM PERSON WHERE NAME LIKE '%а%'";
//
//    SQLHSTMT stmt;
//    SQLRETURN ret;
//
//    // Создаем оператор
//    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
//
//    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
//        std::cerr << "Ошибка при выделении оператора." << std::endl;
//        return;
//    }
//
//    // SQL запрос
//    const char *query = "SELECT * FROM PERSON WHERE NAME LIKE '%а%'";
//
//    // Выполняем запрос
//    ret = SQLExecDirect(stmt, (SQLCHAR *)query, SQL_NTS);
//
//    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
//        // Обработка результатов запроса
//        while (SQLFetch(stmt) != SQL_NO_DATA) {
//            // Предполагаем, что поле NAME - это строка
//            char name[255];
//            // Получаем данные из первого столбца (ID)
//            int id;
//            SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
//            // Получаем данные из второго столбца (NAME)
//            SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
//
//            std::cout << "ID: " << id << ", Имя: " << name << std::endl;
//        }
//    } else {
//        std::cerr << "Ошибка при выполнении запроса." << std::endl;
//    }
//
//    // Освобождаем ресурсы
//    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
//	// Close the database connection
//	sqlite3_close(dbc);
//
//
//	return 0;
//}


#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM PERSON WHERE NAME LIKE '%н%'";

    // Open the database
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Execute the SQL statement and fetch results
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
