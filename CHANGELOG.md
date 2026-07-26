# Changelog

All notable changes to this project will be documented in this file.

The format is based on Keep a Changelog,
and this project adheres to Semantic Versioning.

## [1.1.0] - 2026-07-25

### Added

- Created a dedicated process group for executed commands.
- Send timeout signals (`SIGTERM` and `SIGKILL`) to the entire process group.

### Fixed

- Fixed compiler warnings reported by `-Wall -Wextra -Wpedantic`.
- Improved signal handling robustness.

## [1.0.0] - 2026-07-24

### Added

- Initial stable release.
- Execute commands with a configurable timeout.
- Forward the child process exit status.
- Help screen (`-h`, `--help`).
