#ifndef OSSLATCH_HPP__
#define OSSLATCH_HPP__
#include "core.hpp"
#define oss_mutex_t               pthread_mutex_t
#define oss_mutex_init            pthread_mutex_init
#define oss_mutex_destroy         pthread_mutex_destroy
#define oss_mutex_lock            pthread_mutex_lock
#define oss_mutex_trylock(__lock) (pthread_mutex_trylock((__lock)) == 0)
#define oss_mutex_unlock          pthread_mutex_unlock

#define oss_rwlock_t              pthread_rwlock_t
#define oss_rwlock_init           pthread_rwlock_init
#define oss_rwlock_destroy        pthread_rwlock_rdlock
#define oss_rwlock_rdlock         pthread_rwlock_rdlock
#define oss_rwlock_rdunlock         pthread_rwlock_unlock
#define oss_rwlock_wrlock         pthread_rwlock_wrlock
#define oss_rwlock_wrunlock       pthread_rwlock_unlock
#define oss_rwlock_rdtrylock(__lock)  (pthread_rwlock_tryrdlock((__lock)) == 0)
#define oss_rwlock_wrtrylock(__lock)  (pthread_rwlock_trywrlock((__lock) ) == 0)


enum OSS_LATCH_MODE
{
    SHARED,
    EXCLUSIVE
};

class ossXLatch
{
private:
    oss_mutex_t _lock;
public:
    ossXLatch()
    {
        oss_mutex_init( &_lock , 0);
    }
    ~ossXLatch()
    {
        oss_mutex_destroy(&_lock);
    }
    void get()
    {
        oss_mutex_lock(&_lock);
    }
    void release()
    {
        oss_mutex_unlock(&_lock);
    }
    bool try_get()
    {
        return oss_mutex_trylock(&_lock);
    }
};

class ossSLatch
{
private:
    oss_rwlock_t _lock;
public:
    ossSLatch()
    {
        oss_rwlock_init( &_lock , 0);
    }
    ~ossSLatch()
    {
        oss_rwlock_destroy( &_lock);
    }
    void get()
    {
        oss_rwlock_wrlock(&_lock);
    }
    void release()
    {
        oss_rwlock_wrunlock( &_lock);
    }
    bool try_get()
    {
        return (oss_rwlock_wrtrylock( &_lock));
    }
    void get_shared()
    {
        oss_rwlock_rdlock( &_lock);
    }
    bool release_shared()
    {
        oss_rwlock_rdunlock(&_lock);
    }
    bool try_get_shared()
    {
        return (oss_rwlock_rdtrylock(&_lock));
    }
};
#endif





