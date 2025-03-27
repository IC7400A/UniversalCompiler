#include "compiler.h"
#include <iostream>
#include <cstdlib>

bool Compiler::CompileAndRun(const std::string& output_file, const nlohmann::json& config) {
  std::string exe_file = output_file.substr(0, output_file.find_last_of(".")) + ".out";

  // 🔹 Use `.value()` to prevent exceptions if key is missing
  std::string compile_cmd = config.value("compile_command", "g++ {output_file} -o {exe_file}");
  std::string run_cmd = config.value("run_command", "./{exe_file}");

  // 🔹 Replace placeholders correctly
  for (auto& cmd : {&compile_cmd, &run_cmd}) {
    size_t pos;
    while ((pos = cmd->find("{output_file}")) != std::string::npos) {
      cmd->replace(pos, 13, output_file);
    }
    while ((pos = cmd->find("{exe_file}")) != std::string::npos) {
      cmd->replace(pos, 9, exe_file);
    }
  }

  // 🔹 Show and execute compile command
  std::cout << "Compiling with command: " << compile_cmd << std::endl;
  if (std::system(compile_cmd.c_str()) != 0) {
    std::cerr << "Compilation failed." << std::endl;
    return false;
  }

  // 🔹 Show and execute run command
  std::cout << "Running: " << run_cmd << std::endl;
  std::system(run_cmd.c_str());

  return true;
}
