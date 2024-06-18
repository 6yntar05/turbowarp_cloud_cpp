#include "db/backend/postgres.hpp"

#include <spdlog/spdlog.h>

#include <charconv>
#include <cstddef>
#include <db/db.hpp>
#include <pqxx/array>
#include <pqxx/binarystring>
#include <pqxx/blob>
#include <pqxx/field>
#include <pqxx/pqxx>
#include <pqxx/strconv.hxx>
#include <pqxx/strconv>
#include <pqxx/util>
#include <string>

namespace db {

namespace postgres {

credetials getDefaults() {
    credetials ret;
    ret.backend = backends::postgres;
    ret.user = default_user;
    ret.passwd = default_passwd;
    ret.dbname = "";
    ret.address = {"", default_port};
    return ret;
}

impl::impl(const std::string user, const std::string passwd, const std::string dbname, addr addr) {
    bool isInited = false;
    while (!isInited) {
        try {
            this->C = std::make_unique<pqxx::connection>("dbname = " + dbname + " user = " + user +
                                                        " password = " + passwd +
                                                        " host = " + addr.ip + " port = " + addr.port);
            if (!this->C->is_open()) {
                spdlog::error("Can't open database");
                return;
            }
            spdlog::info("Opened database successfully: " + static_cast<std::string>(this->C->dbname()));
            isInited = true;
        } catch (const std::exception& e) {
            spdlog::error("Exception: {}", e.what());
            spdlog::error("Retrying in 5 sec...");
            std::this_thread::sleep_for( std::chrono::seconds(5) );
        }
    }
}

impl::~impl() { this->C->close(); }

void impl::close() { this->C->close(); }

void impl::setup() {
    std::vector<std::pair<std::string, std::string>> iter = {
        {"turbowarp", dataRows::turbowarp::postgresString}
    };

    for (auto& i : iter) {
        pqxx::work W{*C};
        char ret = W.query_value<std::string>(
                        "SELECT EXISTS ("
                        "SELECT FROM pg_tables "
                        "WHERE schemaname = 'public' AND tablename = '" +
                        W.esc(i.first) + "')")
                       .at(0);
        if (ret == 'f') {
            // Table does ot exist; Create
            W.exec("CREATE TABLE " + i.first + " (" + i.second + ") ");
            W.commit();
        }
    }

    this->C->prepare("turbowarpWrite", "INSERT INTO turbowarp " +
                                         dataRows::genNamesVec(dataRows::turbowarp::postgresString) +
                                         " VALUES ($1, $2, $3);");
    this->C->prepare("turbowarpRead", "SELECT value FROM turbowarp WHERE user = $1 AND key = $2;");
    this->C->prepare("turbowarpDelete", "DELETE FROM turbowarp WHERE user = $1 AND key = $2;");
}

size_t impl::getRowsCount(std::string table) {
    pqxx::work W{*C};
    return static_cast<size_t>(W.query_value<size_t>("SELECT COUNT(*) FROM " + W.esc(table)));
}

using namespace dataRows;

void impl::set( const dataRows::turbowarp::row row ) {
    pqxx::work W{*this->C};
    W.exec_prepared("turbowarpWrite", row.user, row.key, row.value );
    W.commit();
}
std::string postgres::impl::get(const dataRows::turbowarp::row row) {
    pqxx::work W{*this->C};
    pqxx::result result = W.exec_prepared("turbowarpRead", row.user, row.key);

    if (!result.empty()) {
        return result[0]["value"].as<std::string>();
    }

    // If value not found
    return "";
}
void postgres::impl::del(const dataRows::turbowarp::row row) {
    pqxx::work W{*this->C};
    W.exec_prepared("turbowarpDelete", row.user, row.key);
    W.commit();
}

std::string hexToASCII(std::string hex) {
    std::string ascii = "";
    for (size_t i = 2; i < hex.length(); i += 2) {
        std::string part = hex.substr(i, 2);
        char ch = stoul(part, nullptr, 16);

        ascii += ch;
    }
    return ascii;
}

}  // namespace postgres

}  // namespace db