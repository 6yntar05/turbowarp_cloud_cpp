#pragma once

#include <spdlog/spdlog.h>

#include <any>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace db {

namespace backends {
enum available { none, postgres, sqlite };
}

struct addr {
    std::string ip = "127.0.0.1";
    std::string port = "";

    std::string path = "";
    bool pathPrefered = false;

    void fromRemoteHost(std::string);
};

struct credetials {
    backends::available backend = backends::none;
    std::string user = "";
    std::string passwd = "";
    std::string dbname = "bigeye";
    addr address = {};
};

credetials getDefaults(backends::available backend);

namespace dataRows {

namespace turbowarp {
struct row {
    uint32_t id = 0;  // will be generated automaticly
    std::string_view user;
    std::string_view key;
    std::string_view value;
};
const std::string postgresString =
    "id int GENERATED ALWAYS AS IDENTITY,"
    "user varchar (32),"
    "key varchar (255),"
    "value varchar (10240)";

const std::string sqliteString = "; DROP TABLE *;";  // We do a little trolling...
}  // namespace turbowarp

std::string genNamesVec(std::string source, bool ignoreFirst = true);

}  // namespace dataRows

// Base class of backend-specific implementation
class impl {
public:
    virtual ~impl() = default;
    virtual void close(){};
    virtual void setup(){};
    virtual size_t getRowsCount(std::string table) { return {}; };

    /// TODO:
    // - table <project-id>:
    //  - columns (username:key:value)
    //   - row...
    //   - row...

    /// So, TODO methods:
    // projectTable GetTable()...
    //  > projectTable: set(user, key, value) / get / delete...

    /// Or temporary short view: ignore projectid:
    // set(user,key,value) / get / delete
    virtual void set( const dataRows::turbowarp::row row ) {};
    virtual std::string get( const dataRows::turbowarp::row row ) { return {}; };
    virtual void del( const dataRows::turbowarp::row row ) {};

    /// TODO 2:
    // - mutex on db
};

// Main interface
class db {
private:
    std::shared_ptr<impl> backend = std::make_shared<impl>();
    credetials login;

public:
    db(const backends::available backend = backends::none, const std::string user = "",
       const std::string passwd = "", const std::string dbname = "bigeye", addr addr = {});

    void connect();
    void disconnect();
    void setup();

    size_t getRowsCount(std::string table);

    void set( const dataRows::turbowarp::row row );
    std::string get( const dataRows::turbowarp::row row );
    void del( const dataRows::turbowarp::row row );
};

}  // namespace db
