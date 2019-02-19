#include "buffer.hpp"
Buffer::Buffer(int bufsize)
{
    data_size = 0;
    buf_size = bufsize;
    m_buf = (char *) malloc(bufsize);
    m_data = m_buf;

}