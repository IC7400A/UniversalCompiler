# **Unic – A Universal Compiler** 🚀

Unic is a **universal compiler/interpreter** that reads a **custom syntax configuration file (`.cfg.json`)** and processes **.unic files**, converting them into Java or Python based on the user-defined rules.

## **📌 Features**
✅ **Customizable syntax** – Define language rules via `.cfg.json`.  
✅ **Compiles or interprets** based on config settings.  
✅ **Works from any directory** – Finds config in the source `.unic` file's directory.  
✅ **Cross-platform** – Works on **Linux, Windows, and macOS**.  

---

## **📂 Project File Structure**
```
unic/                      # Root directory
│── bin/                   # Compiled binary directory
│   └── unic               # Compiled executable
│── examples/              # Example test cases
│   ├── hello.unic         # Sample source file
│   ├── hello.cfg.json     # Config file for hello.unic
│── include/               # Header files
│   ├── config_parser.h    # Handles config file parsing
│   ├── code_processor.h   # Processes alias replacements
│   ├── executor.h         # Runs the output
│   ├── unic.h             # Main header file
│── obj/                   # Compiled object files
│── src/                   # Source files
│   ├── main.cc            # Main program
│   ├── config_parser.cc   # Reads JSON config
│   ├── code_processor.cc  # Processes the input code
│   ├── executor.cc        # Executes the converted output
│── Makefile               # Build script
│── README.md              # Project documentation
```

---

## **📥 Installation**
### **🔹 Clone the Repository**
```sh
git clone https://github.com/yourusername/unic.git
cd unic
```

### **🔹 Build the Compiler**
```sh
make
```

---

## **🚀 Usage**
### **🔹 Compiling a `.unic` File**
```sh
./bin/unic path/to/source.unic
```
> **Example:**  
```sh
./bin/unic examples/hello.unic
```
---

## **📖 Writing a `.unic` File**
A `.unic` file is a custom language script that uses **config-based aliasing**.

### **🔹 Example `hello.unic`**
```unic
print("Hello, World!");
```

### **🔹 Config File `hello.cfg.json`**
```json
{
  "aliases": {
    "print": "System.out.println"
  },
  "output_language": "java"
}
```

### **🛠 How It Works**
- The compiler reads **`hello.unic`**.
- It replaces **`print()`** with **`System.out.println()`** (Java syntax).
- It generates and runs **Java or Python** based on the config.

---

## **⚡ Example Outputs**
### **➡️ Java Mode (`output_language: "java"`)**
```java
System.out.println("Hello, World!");
```

### **➡️ Python Mode (`output_language: "python"`)**
```python
print("Hello, World!")
```

---

## **🧹 Cleaning the Project**
```sh
make clean
```

## **📜 License**
This project is licensed under the **MIT License**.
