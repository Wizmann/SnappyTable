#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

#include "logging.h"
#include "SnappyTable.h"

#define print(x) std::cout << x << std::endl
#define input(x) std::cin >> x
#define error(x) std::cerr << x << std::endl

int main() {
    int n;
    if (log_open("SnappyTable") != 0) {
        error("log4c open failed!");
        return -1;
    }
    LOG_NOTICE("Snappy Table demo version 0.1, made by Wizmann");

    SnappyTable* tbl = new(std::nothrow) SnappyTable();
    tbl->init();

    LOG_NOTICE("start reading and compressing entries...");

    input(n);
    std::string entry;
    while (n--) {
        input(entry);
        uint32_t entry_id;
        int res = tbl->append(
                entry, entry_id);

        if (res != 0) {
            LOG_ERROR("insert entry error!");
        }
    }
    tbl->append_done();
    LOG_NOTICE("reading and compressing finished...");

    LOG_NOTICE("start reading and retriving queries...");

    input(n);
    uint32_t entry_id;
    while (n--) {
        input(entry_id);
        uint32_t length = 0;
        int res = tbl->query(entry_id, entry);
        if (res != 0) {
            LOG_ERROR("retrieve query[%u] error!", entry_id);
        }
    }
    LOG_NOTICE("reading and retriving queries finished...");

    LOG_NOTICE("Snappy Table uncompressed size: %lu", tbl->get_uncompressed_size());
    LOG_NOTICE("Snappy Table compressed size: %lu", tbl->get_compressed_size());

    log_close();
    return 0;
}