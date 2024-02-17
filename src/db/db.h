#pragma once

#include <pqxx/pqxx>
// Платформо-зависимые библиотеки лучше вынести в конкретную реализацию
// см. https://github.com/Larinenok/BigEye
// Только для теста!

namespace db {

void libraryTest() { auto test = pqxx::connection(); }

}  // namespace db