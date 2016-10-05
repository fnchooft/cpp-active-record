#include <cstdlib>
#include <gtest/gtest.h>
#include <active_record/exception.h>

const char * pg_user;
const char * pg_port;

int main( int argc, char **argv ) {
  ::testing::InitGoogleTest( &argc, argv );

#ifdef HAVE_POSTGRES
  pg_user = std::getenv("PG_USER");
  pg_port = std::getenv("PG_PORT");

  if(!pg_user) {
    cout << "Please supply PG_USER as an environment variable (PG_PORT for port other than 5432)" << endl;
    exit(1);
  }
  if(!pg_port) {
    pg_port = "5432";
  }
#endif

  int result = -1;
  try {
    result = RUN_ALL_TESTS();
  }
  catch( ActiveRecord::ActiveRecordException e ) {
    cout << "Test raised an unexpected exception:" << endl;
    cout << e.to_string() << endl;
  }
  return result;
}
