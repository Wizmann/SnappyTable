//
// Created by Wizmann on 15/7/26.
//

#ifndef SNAPPYTABLE_SNAPPYTABLE_H
#define SNAPPYTABLE_SNAPPYTABLE_H


#include <stddef.h>
#include <cstring>
#include <cinttypes>
#include <vector>

#include "logging.h"
#include "snappy.h"

using std::vector;

class SnappyTable {
    static const uint32_t CHUNK_SIZE = 32 * 1024; // 32kb

    // each chunk should not larger than 65536 Byte
    struct InternalNode {
        uint32_t chunk_nr;
        uint16_t offset;
        uint16_t size;
    };
public:
    void init();
    void append_done() {
        do_packing();
    }
    int append(std::string& entry, uint32_t &entry_id);
    int query(uint32_t entry_id, std::string& resp);
private:
    int do_append(std::string& entry, uint32_t &entry_id);
    virtual int do_packing();
private:
    vector<std::string> _chunks;
    vector<InternalNode> _nodes;
    std::string _buffer;
    uint16_t _buffer_offset;

public:
    uint64_t get_compressed_size() const {
        return _compressed_size;
    }

    uint64_t get_uncompressed_size() const {
        return _uncompressed_size;
    }

private:
    uint64_t _uncompressed_size;
    uint64_t _compressed_size;
};


#endif //SNAPPYTABLE_SNAPPYTABLE_H
