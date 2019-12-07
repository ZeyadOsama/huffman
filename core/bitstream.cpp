//
// Created by Zeyad Osama on 12/7/19.
//

#include "bitstream.h"

bitstream::bitstream(unsigned buffersize) {
    buffer = new byte[buffersize];
    for (unsigned i = 0; i < buffersize; i++)
        buffer[i] = 0;
    buffer_size = buffersize;
    bit_pos = 0;
    remainder = 0;
    remainder_size = 0;
}

bitstream::~bitstream() {
    delete buffer;
}

const byte *bitstream::flush_buffer() {
    return buffer;
}

inline unsigned bitstream::getBytePosition() {
    return bit_pos / 8;
}

inline unsigned bitstream::get_free_bits() {
    return (buffer_size * 8) - bit_pos;
}

inline unsigned bitstream::getBitOffset() {
    return bit_pos % 8;
}

unsigned bitstream::getOccupiedBytes() {
    return getBytePosition() + (getBitOffset() > 0);
}

bool bitstream::add_remainder(unsigned data, unsigned size) {
    //notice no checks. Yea, I don't care if remainder overflows
    //because EVERY pack() has to if if(pack() > 0)d and flushed
    //then reset.
    //At least for now, that is. maybe I can code a lock mechanism
    //in place later
    remainder_size += size;
    remainder = (remainder << size) | (data & ~(0xffu << (size)));
    return true;
}

int bitstream::micropack(byte data, unsigned size) {
    if (!size)
        return 0; //needed for adding remainders w/pack(,)

    if (get_free_bits() >= size) {
        byte buff = buffer[getBytePosition()];       //copy last byte of buffer to modify
        data = data << (8 - size);                //move data so MSB is at 8th pos
        buff = buff | (data >> getBitOffset()); //pack input data's portion into buffer
        data = data << (8 - getBitOffset());    //pack the rest of data on the next byte

        buffer[getBytePosition()] = buff;     //flush the change
        buffer[getBytePosition() + 1] = data; //flush the change
        bit_pos += size;
        return 0; //no problems, sire.
    } else {
        unsigned r_size = size - get_free_bits();
        micropack(data >> (r_size), get_free_bits()); //micropack whatever fits
        bit_pos += get_free_bits();
        add_remainder(data, r_size);
        return r_size;
    }
}

bool bitstream::pack(unsigned data, unsigned bit_l) {
    if (bit_l > 32)
        return false;
    else { //time to chop unsigned to bytes
        int return_size = 0;
        unsigned no_of_bytes = bit_l / 8;
        unsigned unaligned_bits = bit_l % 8;
        byte buff[4] = {0, 0, 0, 0};

        for (unsigned i = 0; i < 4; i++) {
            data = data >> (i * 8);
            buff[i] = (byte) data;
        }

        micropack(buff[no_of_bytes], unaligned_bits); // first push the MSB side
        while (no_of_bytes) {
            micropack(buff[--no_of_bytes], 8);
        }
    }

    if (remainder_size)
        return false;
    return true;
}

int bitstream::resetBuffer() {
    for (int i = 0; i < buffer_size; i++) //This is not necessary, but it helps me debug.
    {
        buffer[i] = 0;
    }
    bit_pos = 0;
    pack(remainder, remainder_size);
    remainder = 0;
    remainder_size = 0;
    return true;
}
