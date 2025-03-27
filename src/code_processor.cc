#include "code_processor.h"
#include <fstream>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

bool CodeProcessor::Process(const std::string& source_file, const std::string& output_file, const std::string& config_file) {
  std::ifstream config_stream(config_file);
  if (!config_stream) {
    std::cerr << "Error: Cannot open config file: " << config_file << std::endl;
    return false;
  }

  json config;
  config_stream >> config;
  config_stream.close();

  std::ifstream src_stream(source_file);
  if (!src_stream) {
    std::cerr << "Error: Cannot open source file: " << source_file << std::endl;
    return false;
  }

  std::ostringstream buffer;
  buffer << src_stream.rdbuf();
  std::string code = buffer.str();
  src_stream.close();

  std::unordered_map<std::string, std::string> aliases = LoadAliases(config);
  std::string processed_code = ReplaceAliases(code, aliases);

  std::ofstream out_stream(output_file);
  if (!out_stream) {
    std::cerr << "Error: Cannot create output file: " << output_file << std::endl;
    return false;
  }

  out_stream << processed_code;
  out_stream.close();
  return true;
}

std::unordered_map<std::string, std::string> CodeProcessor::LoadAliases(const json& config) {
  std::unordered_map<std::string, std::string> aliases;
  if (config.contains("aliases") && config["aliases"].is_object()) {
    for (auto& [key, value] : config["aliases"].items()) {
      aliases[key] = value;
    }
  }
  return aliases;
}

std::string CodeProcessor::ReplaceAliases(const std::string& code, const std::unordered_map<std::string, std::string>& aliases) {
  std::string modified_code = code;
  for (const auto& [key, value] : aliases) {
    size_t pos = 0;
    while ((pos = modified_code.find(key, pos)) != std::string::npos) {
      modified_code.replace(pos, key.length(), value);
      pos += value.length();
    }
  }
  return modified_code;
}
