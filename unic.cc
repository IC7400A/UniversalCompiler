#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

// Function to read a file into a string
string read_file(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        exit(1);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Simple JSON parser for key-value pairs (Assumes valid JSON format)
unordered_map<string, string> parse_json(const string& json_text, string& output_language) {
    unordered_map<string, string> aliases;
    size_t lang_start = json_text.find("\"language\": \"");
    if (lang_start != string::npos) {
        size_t lang_end = json_text.find("\"", lang_start + 12);
        if (lang_end != string::npos) {
            output_language = json_text.substr(lang_start + 12, lang_end - (lang_start + 12));
        }
    }

    size_t start = json_text.find("\"aliases\": {");
    if (start == string::npos) return aliases;
    start += 11; // Move past `"aliases": {`

    size_t pos = start;
    while ((pos = json_text.find("\"", pos)) != string::npos) {
        size_t key_start = pos + 1;
        size_t key_end = json_text.find("\"", key_start);
        if (key_end == string::npos) break;
        
        string key = json_text.substr(key_start, key_end - key_start);

        size_t value_start = json_text.find("\"", key_end + 2);
        size_t value_end = json_text.find("\"", value_start + 1);
        if (value_start == string::npos || value_end == string::npos) break;

        string value = json_text.substr(value_start + 1, value_end - value_start - 1);
        aliases[key] = value;
        pos = value_end + 1;
    }
    return aliases;
}

// Function to replace aliases in the code
string replace_aliases(string code, const unordered_map<string, string>& aliases) {
    for (const auto& [alias, replacement] : aliases) {
        size_t pos = 0;
        while ((pos = code.find(alias, pos)) != string::npos) {
            code.replace(pos, alias.length(), replacement);
            pos += replacement.length();
        }
    }
    return code;
}

// Function to write output to a file
void write_file(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Cannot write to file " << filename << endl;
        exit(1);
    }
    file << content;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    string input_filename = argv[1];

    // Load JSON config
    string json_data = read_file("config.json");
    string output_language;
    unordered_map<string, string> aliases = parse_json(json_data, output_language);

    // Read input alias file
    string code = read_file(input_filename);

    // Replace aliases
    string converted_code = replace_aliases(code, aliases);

    // Generate output filename based on language
    string output_filename = "output." + (output_language.empty() ? "java" : output_language);
    write_file(output_filename, converted_code);

    cout << "Conversion complete. Output saved to " << output_filename << "\n";
    return 0;
}
