


#include <mysql.h>
#include <stdio.h>
#include <datafarming.h>
#include <mysqld_error.h>
#include <errmsg.h>

connect() {
MYSQL *conn;

char *server = "localhost";
char *user = "root";
char *password = "PASSWORD"; /* set me first */
char *database = "Wetter";
conn = mysql_init(NULL);
/* Connect to database */
if (mysql_real_connect(conn, server,
user, password, database, 0, NULL, 0)) {
    if(mysql_error(conn)>0){
        fprintf(stderr, "%s\n", mysql_stat(conn));
        fprintf(stderr, "%s\n", mysql_errno(conn));
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
        }else{
            insertData();
        }
    mysql_auto_commit(1);
    }
mysql_close(conn);
}

insertData(){
    insertTemp(temp);
    insertWind();
    insertStatus();
    insertRain();
    return 0;

}
