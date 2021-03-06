#include<iostream>
#include<string>
#include<mysql/mysql.h>


struct connection_details{
    const char *server, *user, *password, *database;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL);

    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)){
        std::cout << "Connection Error:" << mysql_error(connection) << std::endl;
        exit(1);
    }
    return connection;
}

MYSQL_RES* mysql_execute_query(MYSQL *connection, const char *sql_query){
    if (mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error:" << mysql_error(connection) << std::endl;
        exit(1);
    }
return mysql_use_result(connection);
}


int main(int argc, char const *argv){

    MYSQL *con;
    MYSQL_RES *res;
    MYSQL_ROW row;

    struct connection_details mysqlD;

    mysqlD.server = "localhost";
    mysqlD.user = "root";
    mysqlD.password = std::getenv("SQL_CALENDAR2_PASSWORD");
    mysqlD.database = "calendar2";
    con = mysql_connection_setup(mysqlD);
    res = mysql_execute_query(con, "select * from calendar");

    std::cout << "Displaying database output:\n" << std::endl;

    while((row = mysql_fetch_row(res)) != NULL){
        std::cout << row[0] <<" | "<< row[1];
    }

    mysql_free_result(res);
    mysql_close(con);

    std::cout << "\n";    


    return 0;
}