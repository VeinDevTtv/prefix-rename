# Rename Folder Prefix

This program renames folders within a specified directory by changing their prefix. It supports recursive renaming, dry-run mode, case-insensitive prefix matching, and handles potential name collisions.

## Features

- **Recursive Renaming**: Renames folders in the specified directory and all its subdirectories.
- **Dry-Run Mode**: Use the `--dry-run` or `-n` flag to simulate the renaming process without making any changes.
- **Case-Insensitive Prefix Matching**: Use the `--ignore-case` or `-i` flag to ignore case differences when matching prefixes.
- **Name Collision Handling**: Checks if the target path already exists and skips renaming if it does, printing a warning message.

## Usage

```bash
rename_folder_prefix.exe <directory> <old_prefix> <new_prefix> [--dry-run|-n] [--ignore-case|-i]
```

### Parameters

- `<directory>`: The base directory where the renaming process will start.
- `<old_prefix>`: The prefix to be replaced.
- `<new_prefix>`: The new prefix to use.
- `--dry-run` or `-n`: Optional flag to enable dry-run mode.
- `--ignore-case` or `-i`: Optional flag to enable case-insensitive prefix matching.

### Examples

- Simulate renaming with dry-run:
  ```bash
  rename_folder_prefix.exe "C:\path\to\base_dir" "old_prefix" "new_prefix" --dry-run
  ```

- Perform renaming with case-insensitive matching:
  ```bash
  rename_folder_prefix.exe "C:\path\to\base_dir" "old_prefix" "new_prefix" --ignore-case
  ```

- Combine dry-run and case-insensitive matching:
  ```bash
  rename_folder_prefix.exe "C:\path\to\base_dir" "old_prefix" "new_prefix" --dry-run --ignore-case
  ```

## Summary

After execution, the program provides a summary of the total number of folders renamed and those skipped due to existing target paths.

## Error Handling

The program handles filesystem errors and general exceptions, providing descriptive error messages to the user. 