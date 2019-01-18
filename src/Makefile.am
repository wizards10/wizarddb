AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=wizarddb edb
wizarddb_SOURCES=\
   pmd/pmdMain.cpp  pmd/pmdTcpListener.cpp \
   bson/src/bsonobj.cpp bson/src/util/json.cpp bson/src/oid.cpp \
   bson/src/lib/base64.cpp bson/src/lib/md5.cpp bson/src/lib/nonce.cpp \
   oss/osssocket.cpp

edb_SOURCES=\
   client/edb.cpp client/command.cpp client/commandFactory.cpp \
   bson/src/bsonobj.cpp bson/src/util/json.cpp bson/src/oid.cpp \
   bson/src/lib/base64.cpp bson/src/lib/md5.cpp bson/src/lib/nonce.cpp \
   oss/osssocket.cpp

wizarddb_CXXFLAGS=-I../boost/boost -Ibson/src -Iinclude -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0
wizarddb_LDADD=-lboost_system -lm -lboost_thread -lboost_program_options -lrt
wizarddb_LDFLAGS=-fPIC -rdynamic -L../boost/stage/lib -pthread

edb_CXXFLAGS=-I../boost -Ibson/src -Iinclude -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0
edb_LDADD=-lm -lboost_system -lboost_thread -lrt
edb_LDFLAGS=-fPIC -rdynamic -L../boost/stage/lib 
