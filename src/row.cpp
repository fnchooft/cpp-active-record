#include <iostream>
#include <active_record/row.h>

namespace ActiveRecord {

Row::Row(sqlite3_stmt *pStmt) {
  int count = sqlite3_column_count(pStmt);
  for(int i = 0; i < count; ++i) {
    string name = sqlite3_column_name(pStmt, i);
    const char * type = sqlite3_column_decltype(pStmt, i);
    if (strcmp(type, "INTEGER") == 0) {
      attributes_[name] = sqlite3_column_int(pStmt, i);
    } else if (strcmp(type, "FLOAT") == 0) {
      attributes_[name] = sqlite3_column_double(pStmt, i);
    } else if (strcmp(type, "TEXT") == 0) {
      const char * value = (const char *) sqlite3_column_text(pStmt, i);
      if (value != 0)
        attributes_[name] = value;
    }
    else
      cout << "ActiveRecord::Row: Unhandled data type: " << type << endl;
  }
}

string Row::get_text(const string &name) {
  return boost::get<string>(attributes_[name]);
}

int Row::get_integer(const string &name) {
  return boost::get<int>(attributes_[name]);
}

} // namespace ActiveRecord