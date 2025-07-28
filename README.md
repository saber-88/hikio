# Hikio — A Minimal Linux Shell

`hikio` is a simple, custom-built Unix shell written in C, designed for learning and experimenting with core system-level programming concepts like process management, command parsing, and readline input.

## 🚀 Features

- Execute external commands (e.g., `ls`, `fastfetch`, `neofetch`)
- Built-in commands like:
  - `cd` – change directory
  - `clear` – clears and resets the terminal
  - `exit` – exit the shell
- Persistent command history (using `readline`)
- Minimal prompt with current working directory

## 🛠 Installation

### 📦 Requirements
- GCC
- GNU Make
- `readline` library
- Optional (for better IDE support): [`bear`](https://github.com/rizsotto/Bear)

### 🔧 Setup

Just run the setup script:

```bash
./setup.sh
```

This will:
- Build the shell using `make`
- Generate `compile_commands.json` (for development)
- Move the `hikio` binary to `/usr/local/bin`

> 💡 You may need `sudo` for installation.

---

## 🧪 Development Mode

To just build for development (without installing system-wide):

```bash
make clean
bear -- make
./hikio
```

---

## 📁 Project Structure

```
hikio/
├── include/         # Header files
├── src/             # Source code
├── Makefile         # Build rules
├── setup.sh         # Installation script
├── compile_commands.json  # Generated for IDEs
├── README.md
└── .gitignore
```

---

## ⚠️ Known Bugs

- Some graphical terminal programs (like `fastfetch` with PNG image) may not clear properly unless `tput reset` is used in the `clear` command.
- If you modify any `.c` or `.h` file, recompile using `make`.

---

## 📜 License

[MIT](LICENSE)

---

## 🤝 Contributing

Pull requests and issues are welcome. This shell is built for educational purposes and open for enhancements.

---
