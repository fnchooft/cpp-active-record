#include <string>
#include <active_record/connection/sqlite3.h>

using namespace std;

namespace ActiveRecord {

extern TypeNameMap type_name;

string Table::primary_key(Sqlite3Connection *connection,
    const string &table_name) {
  string row_query = "PRAGMA table_info(\"" + table_name + "\");";
  RowSet rows = connection->select_all(row_query);
  for(RowSet::iterator it = rows.begin(); it != rows.end(); ++it) {
    // cid | name | type    | notnull | dflt_value | pk
    //   0 |  bar | INTEGER |       0 |            |  0
    Type::Type t = it->get_type("pk");
    string tn = type_name[t];
    int is_pk = atoi(it->get_text("pk").c_str());
    if(is_pk != 0) {
      string name = it->get_text("name");
      return name;
    }
  }
  return "";
}

/*
SQLite does not implement DROP COLUMN - needs some hoop jumping
void Table::remove_field( const Field &field ) {
  assert_connection();
  stringstream ss;
  ss << "ALTER TABLE " << table_name_;
  ss << " DROP " << field.name();
  ss << ";";
  connection_->execute( ss.str() );
}
*/

}
