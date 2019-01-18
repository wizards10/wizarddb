#ifndef _EDB_HPP
#define _EDB_HPP
#include "core.hpp"
#include "osssocket.hpp"
#include "commandFactory.hpp"
const int CMD_BUFFER_SIZE    =    512;
class Edb
{
public:
    void start(void);
protected:
    void prompt(void);
private:
    void split(const std::string &text , char delim , std::vector<std::string>& result);
    char* readLine(char* p , int length);
    int readInput(const char* pPrompt , int numIndent);
private:
    _ossSocket          _sock;
    CommandFactory      _cmdFactory;
    char                _cmdBuffer[CMD_BUFFER_SIZE];
};
#endif
