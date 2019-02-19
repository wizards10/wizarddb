AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS=wizarddb edb 
wizarddb_SOURCES=\
   TcpConnect/buffer.cpp  TcpConnect/tcpConnect.cpp  \
   oss/ossPrimitiveFileOp.cpp pd/pd.cpp pmd/pmdMain.cpp pmd/pmdTcpListener.cpp pmd/pmdOptions.cpp \
   pmd/pmd.cpp  \
   bson/src/bsonobj.cpp bson/src/util/json.cpp bson/src/oid.cpp \
   bson/src/lib/base64.cpp bson/src/lib/md5.cpp bson/src/lib/nonce.cpp \
   oss/osssocket.cpp  

edb_SOURCES=\
   client/edb.cpp client/command.cpp client/commandFactory.cpp \
   bson/src/bsonobj.cpp bson/src/util/json.cpp bson/src/oid.cpp \
   bson/src/lib/base64.cpp bson/src/lib/md5.cpp bson/src/lib/nonce.cpp \
   oss/osssocket.cpp oss/ossPrimitiveFileOp.cpp                        \
   pd/pd.cpp 

wizarddb_CXXFLAGS=-I../boost/boost -Ibson/src -Iinclude -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0
wizarddb_LDADD=-lboost_system -lm -lboost_thread -lboost_program_options -lrt
wizarddb_LDFLAGS=-fPIC -rdynamic -L../boost/stage/lib -pthread

edb_CXXFLAGS=-I../boost/boost -Ibson/src -Iinclude -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0
edb_LDADD=-lboost_system -lm -lboost_thread -lboost_program_options -lrt
edb_LDFLAGS=-fPIC -rdynamic -L../boost/stage/lib -pthread
