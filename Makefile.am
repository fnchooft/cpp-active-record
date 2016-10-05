bin_PROGRAMS = active_record_x86_64_test

active_record_x86_64_test_SOURCES  = test/attribute_test.cpp test/base_associations_test.cpp test/base_test.cpp 
active_record_x86_64_test_SOURCES += test/date_test.cpp test/exception_test.cpp test/field_test.cpp 
active_record_x86_64_test_SOURCES += test/query_test.cpp test/row_test.cpp  test/main.cpp
active_record_x86_64_test_SOURCES += test/table_set_test.cpp test/table_test.cpp test/test_helper.cpp

active_record_x86_64_test_CPPFLAGS = -Iinclude -Itest
active_record_x86_64_test_LDFLAGS  = -L.
active_record_x86_64_test_LDADD    = -lgtest -lactive_record_x86_64

libactive_record_x86_64_a_CPPFLAGS = -Iinclude

lib_LIBRARIES = libactive_record_x86_64.a

libactive_record_x86_64_a_SOURCES = src/active_record.cpp src/attribute.cpp src/connection.cpp src/exception.cpp 
libactive_record_x86_64_a_SOURCES += src/field.cpp src/row.cpp src/table.cpp src/table_set.cpp src/type.cpp


if POSTGRES_BACKEND
active_record_x86_64_test_SOURCES  += test/postgresql_attribute_test.cpp test/postgresql_connection_test.cpp 
active_record_x86_64_test_SOURCES  += test/postgresql_table_set_test.cpp
active_record_x86_64_test_CPPFLAGS += -Iinclude/postgresql -Iinclude/postgresql/server -DHAVE_POSTGRES
libactive_record_x86_64_a_CPPFLAGS += -Iinclude/postgresql -Iinclude/postgresql/server -DHAVE_POSTGRES
active_record_x86_64_test_LDADD    += -lpq
libactive_record_x86_64_a_SOURCES  += src/attribute/postgresql_attribute.cpp src/connection/postgresql_connection.cpp 
libactive_record_x86_64_a_SOURCES  += src/row/postgresql_row.cpp
endif

if SQLITE3_BACKEND
active_record_x86_64_test_SOURCES += test/sqlite3_connection_test.cpp 
active_record_x86_64_test_LDADD   += -lsqlite3
libactive_record_x86_64_a_SOURCES += src/attribute/sqlite3_attribute.cpp src/connection/sqlite3_connection.cpp 
libactive_record_x86_64_a_SOURCES += src/row/sqlite3_row.cpp src/table/sqlite3_table.cpp
endif

active_record_x86_64_test_LDADD  += -lpthread
