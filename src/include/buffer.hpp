#ifndef BUFFER__
#define BUFFER__
#include "core.hpp"
class Buffer
{
public:
    Buffer(int size);
    Buffer()
    {}
private:
    char* m_buf;
    char* m_data;
    int   data_size;
    int   buf_size;
public:
    int total()const 
    {
        return buf_size;
    }
    bool empty()const
    {
        return data_size == 0;
    }
    char* getdata()const
    {
        return m_data;
    }
    int getDataSize()const
    {
        return data_size;
    }
    char* pointer()const
    {
        return m_data + data_size;
    }
    int spaceBufSize()const
    {
        return buf_size - (int)(m_data - m_buf) - data_size;
    }
    void incre(int  num)
    {
        data_size += num;
    }
    void decre(int num)
    {
        data_size -= num;
        m_data += num;
    }
};
#endif