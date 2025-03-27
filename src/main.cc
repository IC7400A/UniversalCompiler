#include <iostream>
#include <fstream>  // ✅ Include this to fix the error
#include "code_processor.h"
#include "compiler.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
    return 1;
  }

  std::string source_file = argv[1];
  std::string base_name = source_file.substr(0, source_file.find_last_of("."));
  std::string output_file = base_name + ".cpp";
  std::string config_file = base_name + ".cfg.json";  // ✅ Config name updated

  if (!CodeProcessor::Process(source_file, output_file, config_file)) {
    return 1;
  }

  std::ifstream config_stream(config_file);  // ✅ Fix: Now std::ifstream is recognized
  if (!config_stream) {
    std::cerr << "Error: Cannot open config file: " << config_file << std::endl;
    return 1;
  }

  json config;
  config_stream >> config;
  config_stream.close();

  return Compiler::CompileAndRun(output_file, config) ? 0 : 1;
}
