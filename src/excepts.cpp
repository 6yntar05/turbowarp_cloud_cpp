#include "excepts.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::string;

namespace excepts {

error::error(const string msg, const string file, const string func, const string info)
    : msg(msg), file(file), func(func), info(info) {
    // Show error
    std::cerr << "Error:" << msg << std::endl;  // TODO: spdlog

    // Constructing what()
    this->what_string = "Raised excepts::error\n";

    if (!this->file.empty()) this->what_string.append("\t| In file: " + file + " |\n");
    if (!this->func.empty()) this->what_string.append("\t| In function: " + func + " |\n");
    if (!this->info.empty()) this->what_string.append("\t| " + info + " |\n");

    this->what_msg = this->what_string.data();

    // FIXME
}

const char* error::what() const throw() { return this->what_msg; }

}  // namespace excepts
