//
// Created by Zeyad Osama on 12/7/19.
//

#ifndef _BITSTREAM_H
#define _BITSTREAM_H

typedef unsigned char byte;

class bitstream {
protected:
    byte *buffer;
    unsigned buffer_size; //inbytes
    unsigned bit_pos;     //inbits

    unsigned remainder;
    unsigned remainder_size;

    inline unsigned getBytePosition();

    inline unsigned getBitOffset();

    inline unsigned get_free_bits();

    int micropack(byte, unsigned);

    bool add_remainder(unsigned, unsigned);

public:
    bitstream(unsigned);

    ~bitstream();

    unsigned getOccupiedBytes();

    //packs data into buffer upto specified size
    //returns true if okay
    //returns false if the buffer has filled up
    //if pack is false, flush then reset buffer
    bool pack(unsigned, unsigned);

    //gives you a pointer to the buffer
    const byte *flush_buffer();

    //clears the buffer then packs remainder in
    int resetBuffer();
};

#endif
