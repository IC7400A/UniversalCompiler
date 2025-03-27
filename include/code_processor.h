#ifndef CODE_PROCESSOR_H
#define CODE_PROCESSOR_H

#include <string>
#include <unordered_map>
#include "nlohmann/json.hpp"

class CodeProcessor {
 public:
  static bool Process(const std::string& source_file, const std::string& output_file, const std::string& config_file);
 private:
  static std::unordered_map<std::string, std::string> LoadAliases(const nlohmann::json& config);
  static std::string ReplaceAliases(const std::string& code, const std::unordered_map<std::string, std::string>& aliases);
};

#endif  // CODE_PROCESSOR_H
