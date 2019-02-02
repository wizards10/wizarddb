#ifndef PD_HPP__
#define PD_HPP__
#include "core.hpp"
#define PD_LOG_STRINGMAX 4096
#define PD_LOG(level,fmt,...)                                         \
   do {                                                               \
      if ( _curPDLevel >= level )                                     \
      {                                                               \
         pdLog ( level, __func__, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
      }                                                               \
   } while ( 0 )               
                                          
#define PD_CHECK(cond,retCode,gotoLabel,level,fmt,...)                \
        do                                                            \
        {                                                             \
            if(!(cond))                                               \
            {                                                         \
                rc = (retcode);                                         \
                PD_LOG((level),fmt , ##__VA_ARGS__);                    \
                goto gotoLabel;                                         \
            }                                                           \
        } while (0);                                      \

#define PD_RC_CHECK(rc , level , fmt ,...)                                 \
        do                                                                 \
        {                                                                  \
            PD_CHECK((EDB_OK == (rc) , (rc),error , (level), fmt , ##__VA_ARGS__); \
        } while (0);                                                        \

#define EDB_VALIDATE_GOTOERROR(cond,ret,str)                                \
        {if(!(cond)){pdLog(PDERROR,__func__,__FILE__,__LINE__,str);         \
        rc = ret;goto error; }}                                            
#define EDB_ASSERT(cond,str)          {if(cond){}}
#define EDB_CHECK(cond,str)           {if(cond){}}              
enum PDLEVEL
{
    PDSERVER = 0,
    PDERROR,
    PDEVENT,
    PDWARNING,
    PDINFO,
    PDDEBUG
};
extern PDLEVEL _curPDLevel;
const char *getPDLevelDesp(PDLEVEL level);
#define PD_DEF_DIAGLEVEL PDWARNING
void pdLog(PDLEVEL level , const char *func , const char *file,
            unsigned char line , const char* format,...);
void pdLog(PDLEVEL level , const char *func , const char* file,
            unsigned char line , std::string message);
#endif