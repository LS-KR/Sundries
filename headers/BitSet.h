
#ifndef H_BITSET
#define H_BITSET

class BitSet {
private:
    unsigned char* c = nullptr;
    unsigned long size;
    unsigned long length;
    unsigned char digitMap(unsigned char i);
public:
    BitSet(unsigned long size);
    ~BitSet();
    bool Set(unsigned long index, bool flag);
    bool Set(unsigned long index);
    bool Get(unsigned long index);
    unsigned char* Data();
protected:
};

#endif