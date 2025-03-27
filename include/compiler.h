#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include "nlohmann/json.hpp"

class Compiler {
 public:
  static bool CompileAndRun(const std::string& output_file, const nlohmann::json& config);
};

#endif  // COMPILER_H
