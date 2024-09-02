# sqlite API

## Ⅰ BASE

### 1. open

```C

#include <sqlite.h>

void open()
{
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);
    if(rc)
    {
        fprintf(stderr, "can not open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_close(db);
}

```

### 2. simple execute statement

``` C

#include <sqlite3.h>

static int callback(void* unused, int argc, char** argv, char** col_name)
{
    for(int i = 0; i < argc; ++i)
    {
        printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }
}

void exec()
{
    sqlite3_exec(db, "SELECT * FROM TABLE_1", callback, 0, &err_msg);
}

```
