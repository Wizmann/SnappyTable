//
// Created by Wizmann on 15/7/26.
//

#include "SnappyTable.h"

void SnappyTable::init() {
    this->_uncompressed_size = 0;
    this->_compressed_size = 0;
    this->_buffer_offset = 0;
}

int SnappyTable::append(std::string& entry, uint32_t &entry_id) {
    if (this->_buffer_offset + entry.length() > CHUNK_SIZE) {
        do_packing();
    }
    return do_append(entry, entry_id);
}

int SnappyTable::do_append(std::string& entry, uint32_t &entry_id) {
    this->_nodes.push_back({
        static_cast<uint32_t>(this->_chunks.size()),
        static_cast<uint16_t>(this->_buffer_offset),
        static_cast<uint16_t>(entry.length())
    });
    _buffer += entry;
    _buffer_offset += entry.size();

    entry_id = static_cast<uint32_t>(this->_nodes.size() - 1);
    return 0;
}

int SnappyTable::do_packing() {
    std::string output;
    snappy::Compress(this->_buffer.c_str(), this->_buffer_offset, &output);
    this->_chunks.push_back(output);

    this->_uncompressed_size += this->_buffer.size();
    this->_compressed_size += output.size();

    this->_buffer.clear();
    this->_buffer_offset = 0;
    return 0;
}

int SnappyTable::query(uint32_t entry_id, std::string &resp) {
    if (entry_id >= this->_nodes.size()) {
        return -1;
    }
    auto desc = this->_nodes[entry_id];
    auto& chunk = this->_chunks[desc.chunk_nr];
    std::string output;
    snappy::Uncompress(chunk.c_str(), chunk.size(), &output);
    resp = std::string(output.substr(desc.offset, desc.size));
    return 0;
}
