# 🛠️ XML Editor and Visualizer Project

## 🌟 **Project Overview**
The **XML Editor and Visualizer** is a desktop application designed to efficiently process XML files. It offers two main operational modes:  
1️⃣ **Command Line Mode** for scripting and automation.  
2️⃣ **Graphical User Interface (GUI) Mode** for an intuitive and interactive experience.  

The XML files represent users in a social network with the following structure:  
- **Users**: Each user has a unique ID, name, posts, and followers.  
- **Posts**: Contain text and associated topics.

---

## ✨ **Features**
### 🔢 **1. Command Line Mode**
- Execute operations using simple commands:
  - 🛠️ `verify`: Checks XML file consistency.
    ```bash
    xml_editor verify -i input_file.xml
    ```
  - 📦 `compress`: Compresses XML files for optimized storage.
    ```bash
    xml_editor compress -i input_file.xml -o output_file.xml
    ```

### 🖥️ **2. Graphical User Interface (GUI) Mode**
- 📂 **Input File Handling**: Load XML files via a file browser or paste file contents.  
- 🔍 **Error Visualization**: Highlight XML structure inconsistencies.  
- 📜 **Output Display**: View results in a read-only text field.  
- 💾 **Save Outputs**: Specify save locations for corrected or compressed XML files.  
- 🖲️ **Operation Buttons**: Perform operations like validation and correction with a click.

### ✅ **3. XML Consistency Check**
- Detects issues such as:
  - ❌ Missing opening or closing tags.
  - 🔄 Mismatched tags.
- 🚀 Auto-corrects XML structure errors.

### 📁 **4. Output Management**
- Displays results in the GUI or saves them to an output file.
- Users can specify the output file location.
---
## 📋 **Technical Requirements**
- **Programming Languages**: C++ (cross-platform and efficient for performance).  
- **Libraries**:
  - 📰 `tinyxml2` or `pugiXML` for XML processing.
  - 🖼️ `Qt` or `GTK+` for the GUI.
  - 🧰 `Boost.Program_options` for command-line argument handling.
- **Supported Platforms**: Windows, macOS, Linux.

---


## 🚀 **Getting Started**
### 1️⃣ Clone the repository:
```bash
git clone [repository_url](https://github.com/shahed137003/XML-Social-Network-Visualizer.git
)

```

## 📖 **Usage Instructions**

### ⚡ **Command Line Mode**:
- Use predefined commands to process XML files.
- Results are displayed in the terminal or saved to an output file if specified.

### 🖼️ **GUI Mode**:
1. Open the application and load an XML file using the file browser.  
2. Select the desired operation using the available buttons.  
3. View the results in the output text field.  
4. Save the processed XML file if needed.


## 📅 **Project Roadmap**

### 🟢 **Level 1**:  
- XML validation and error correction.

### 🟡 **Level 2**:  
- Add XML compression.  
- Implement user-specific visualizations.

