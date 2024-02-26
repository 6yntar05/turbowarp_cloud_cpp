#include <memory>
#include <spdlog/spdlog.h>

#include "db/db.hpp"
#include "db/backend/postgres.hpp"
#include "db/backend/sqlite.hpp"

namespace db {

void addr::fromRemoteHost(std::string string) {
    size_t colonPos = string.rfind(':');
    this->ip = string.substr(0, colonPos);
    this->port = string.substr(colonPos + 1);
}

credetials getDefaults(backends::available backend) {
    switch (backend) {
        case backends::postgres:
            return postgres::getDefaults();
            break;

        default:
            return {};
    }
}

db::db(backends::available backend, const std::string user, const std::string passwd,
       const std::string dbname, addr addr) {
    credetials defaults;
    switch (backend) {
        case backends::postgres:
            defaults = postgres::getDefaults();
            break;

        case backends::sqlite:
            sqlite::getDefaults();
            break;

        default:
            break;
    }

    this->login.backend = backend;
    this->login.user = (user.size()) ? user : defaults.user;
    this->login.passwd = (passwd.size()) ? passwd : defaults.passwd;
    this->login.dbname = (dbname.size()) ? dbname : defaults.dbname;
    this->login.address = addr;  // Later
}

void db::connect() {
    backends::available _backend = this->login.backend;

    switch (_backend) {
        case backends::sqlite:
            spdlog::critical("SQLite backend is not implemented");
            std::terminate();
            this->backend = std::make_shared<impl>();
            break;

        case backends::postgres: {
            this->backend = std::make_shared<postgres::impl>(
                this->login.user.size() ? this->login.user : postgres::default_user,
                this->login.passwd.size() ? this->login.passwd : postgres::default_passwd,
                this->login.dbname, this->login.address);
            break;
        }

        default:
            this->backend = std::make_shared<impl>();
    };
}

void db::disconnect() { this->backend->close(); }

void db::setup() { this->backend->setup(); }
size_t db::getRowsCount(std::string table) { return this->backend->getRowsCount(table); }

void db::set( const dataRows::turbowarp::row row ) {
    this->backend->set(std::move(row));
}
std::string db::get( const dataRows::turbowarp::row row ) {
    return this->backend->get(std::move(row));
}
void db::del( const dataRows::turbowarp::row row ) {
    this->backend->del(std::move(row));
}

std::string dataRows::genNamesVec(std::string source, bool ignoreFirst) {
    std::string ret = "(";

    bool waitForComma = false;
    for (size_t i = 0; i < source.size(); i++) {
        if (source.at(i) == ',') {
            waitForComma = false;
            if (!ignoreFirst) ret += ", ";
            ignoreFirst = false;
        } else if (source.at(i) == ' ') {
            if (!waitForComma) waitForComma = true;
        } else {
            if (!waitForComma && !ignoreFirst) ret += source.at(i);
        }
    }
    ret += ")";

    return ret;
};

}  // namespace db
