#ifndef _ACTIVE_RECORD_TESTS_MODELS_H_
#define _ACTIVE_RECORD_TESTS_MODELS_H_

#include <active_record/types.h>
#include <active_record/base.h>

using namespace ActiveRecord;

class Person: public ActiveRecord::Base< Person > {
 public:
  AR_CONSTRUCTORS( Person )
  // Callback to set table_name and override any defaults
  static void table() {
    Table td;
    td.table_name = "people";
    td.fields.push_back( Field( "name",    ActiveRecord::text ) );
    td.fields.push_back( Field( "surname", ActiveRecord::text ) );
    td.fields.push_back( Field( "age",     ActiveRecord::integer ) );
    td.fields.push_back( Field( "height",  ActiveRecord::floating_point ) );
    //td.has_many("books");
    return td;
  }
};

#endif // ndef _ACTIVE_RECORD_TESTS_MODELS_H_
