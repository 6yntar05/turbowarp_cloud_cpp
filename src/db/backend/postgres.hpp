#pragma once

#include <pqxx/pqxx>
#include <string>
#include <string_view>
#include <any>

#include "db/db.hpp"

namespace db {
namespace postgres {

const std::string default_user = "postgres";
const std::string default_passwd = "postgres";
const std::string default_port = "5432";

credetials getDefaults();

class impl : public ::db::impl {
private:
    std::unique_ptr<pqxx::connection> C;

public:
    ~impl();
    impl(const std::string user, const std::string passwd, const std::string dbname, addr addr);
    void close() override;
    void setup() override;
    size_t getRowsCount(std::string table) override;

    void set( const dataRows::turbowarp::row row ) override;
    std::string get( const dataRows::turbowarp::row row ) override;
    void del( const dataRows::turbowarp::row row ) override;
};

}  // namespace postgres
}  // namespace db