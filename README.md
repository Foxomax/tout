# Tout

`tout` is a lightweight Unix utility that executes a command with a configurable timeout.

Unlike many simple timeout implementations, `tout` runs the target command in its own process group, ensuring that child processes are also terminated when the timeout expires.

## Features

- Execute any command with a timeout.
- Terminates the entire process tree on timeout.
- Lightweight and dependency-free.
- Simple command-line interface.
- POSIX compliant.

## Installation

Clone the repository and build it:

```bash
git clone https://github.com/<your-username>/tout.git
cd tout
make
```

The binary will be available in the project root.

## Usage

```bash
tout <timeout> <command> [arguments...]
```

### Examples

Run a command for at most 5 seconds:

```bash
tout 5 sleep 10
```

Run a Python script with a 30-second timeout:

```bash
tout 30 python script.py
```

Run Bazel formatting with a 2-second timeout:

```bash
tout 2 bazel run format
```

Display help:

```bash
tout --help
```

## Exit Status

- Returns the exit code of the executed command if it finishes before the timeout.
- Returns a non-zero exit status if the command fails.
- Returns after terminating the command when the timeout expires.

## Why another timeout utility?

`tout` was created as a small educational project to explore Unix process management, including:

- Process creation with `fork()`
- Program execution with `execvp()`
- Signal handling
- Process groups
- `waitpid()`
- Timeouts using `alarm()`

## License

This project is licensed under the MIT License.
