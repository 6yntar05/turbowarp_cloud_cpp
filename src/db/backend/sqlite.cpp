#include "db/backend/sqlite.hpp"

#include <string>

namespace db {

namespace sqlite {

credetials getDefaults() {
    credetials ret;
    ret.backend = backends::sqlite;
    ret.user = default_user;
    ret.passwd = default_passwd;
    ret.dbname = "";
    ret.address = {};
    return ret;
}

impl::impl(const std::string user, const std::string passwd, const std::string dbname, addr addr) {}

impl::~impl() {}

}  // namespace sqlite

}  // namespace db