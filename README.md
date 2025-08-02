#  Hikio Shell

**Hikio** is a lightweight, Unix-like shell written in C, designed to provide essential shell functionality made only for learning purpose and to explore how shell works under the hood.

---

## ✨ Features

- ✅ **Built-in Commands**
  - `cd`, `pwd`, `clear`, `exit`, `help`
- ✅ **Piping**
  - Chaining commands with `|`
- ✅ **Redirection**
  - Input redirection: `<`
  - Output redirection (overwrite): `>`
  - Output redirection (append): `>>`
- ✅ **Tilde Expansion**
  - `~` expands to home directory
- ✅ **Environment Variable Expansion**
  - e.g., `$HOME`, `$USER`, `$PATH`
- ✅ **Command History**
  - Arrow keys to navigate previously entered commands
- ✅ **Autocompletion**
  - Press `Tab` to auto-complete files/commands from the current directory

---

## 📚 Built-in Commands

| Command | Description                      |
|---------|----------------------------------|
| `cd`    | Change current directory         |
| `pwd`   | Print current working directory  |
| `clear` | Clear the terminal screen        |
| `exit`  | Exit the shell                   |
| `help`  | Display help for built-ins       |

---

## 🔍 Examples

```bash
$ cd ~/Projects
# Navigate to ~/Projects using tilde expansion

$ echo $USER
# Expands environment variable

$ ls | grep ".c"
# Pipe output from ls to grep

$ sort < unsorted.txt > sorted.txt
# Redirect input and output

$ sleep 10 &
# Run sleep in the background

$ ./hikio
# Start the custom shell
```

---

## 🛠 Installation

### 📦 Requirements
- GCC
- GNU Make
- `readline` library
- Optional (for better IDE support): [`bear`](https://github.com/rizsotto/Bear)

1. Clone the repository:
   ```bash
   git clone https://github.com/saber-88/hikio.git
   cd hikio
   ```

2. Run the setup script:
   ```bash
   ./setup.sh
   ```


---

## 🧪 Development Mode

To just build for development (without installing system-wide):

```bash
make clean
bear -- make
./hikio
```

---

## 🧠 Under the Hood

Hikio uses:
- `fork()`, `execvp()`, `waitpid()` for process creation
- `readline` for history & input line editing
- `dup2()` for redirection
- `pipe()` to implement `|`
- `opendir()/readdir()` for autocompletion
- `getenv()` for variable/tilde expansion

---

## 📌 Note

- Icons and colorized output for files can be added in future enhancements.
- No external dependencies apart from GNU Readline.

---

## 📜 License

[GPL](LICENSE)

---

## 🤝 Contributing

Pull requests and issues are welcome. This shell is built for educational purposes and open for enhancements.

---

## 👤 Author

Developed by [Karmveer](https://github.com/saber-88)

---