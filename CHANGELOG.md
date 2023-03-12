# Changelog

## 1.3.91 - 2023-03-12

### Added
- Add support for Markdown-style tasks in lists (Daniel Laidig)
- Add tips page (Aurelien Gateau)

### Changed
- Use Ctrl+G to open links and Ctrl+Enter for tasks (Daniel Laidig)

### Fixed
- Make sure standard actions like Copy or Paste are translated (Aurelien Gateau)
- Show keyboard shortcuts in context menus on macOS (Daniel Laidig)
- Do not change cursor to pointing-hand when not over a link (Aurelien Gateau)

### Internals
- CI: Bump Ubuntu to 20.04 and macOS to 11 (Aurelien Gateau)
- CI: Install clang-format from muttleyxd/clang-tools-static-binaries (Aurelien Gateau)
- Bump Qt to 5.15.2 on macOS and Windows (Aurelien Gateau)
- Update singleaplication to 3.3.4 (Aurelien Gateau)
- Update Catch2 to 3.3.0 (Aurelien Gateau)

## 1.3.0 - 2020-10-03

### Changed
- Update Spanish translation (Victorhck)

### Fixed
- Properly encode URL of the note path (Aurelien Gateau)
- Fix untranslated text in About tab on Linux (Aurelien Gateau)

## 1.2.91 - 2020-09-28

### Added
- You can now search inside your notes with the new search bar (Pavol Oresky)
- You can now move selected lines up and down with Alt+Shift+Up and Down (Aurelien Gateau)
- macOS dmg (Aurelien Gateau)
- Windows installer (Aurelien Gateau)

### Changed
- Reorganized context menu: added "Edit" and "View" submenus (Aurelien Gateau)

## 1.2.0 - 2019-05-11

### Added
- New German translation by Vinzenz Vietzke
- Allow changing the font size using Ctrl + mouse wheel (Daniel Laidig)
- Use the link color of the color theme instead of an hardcoded blue (Daniel Laidig)
- Added a way to reset the font size to the default value (Daniel Laidig)

### Fixed
- Added explanation of how to open URLs to the welcome text (Robert Barat)
- Allow '@' in URLs (Aurelien Gateau)
- Use QSaveFile for safer saving (Aurelien Gateau)

## 1.1.0 - 2019-02-04

### Added
- Pressing tab now indents the whole line when the cursor is at the beginning of a list item (Daniel Laidig).
- Pressing Enter on an empty list item now unindents, then removes the bullet (Aurelien Gateau).
- Added French and Spanish translations (Aurelien Gateau, Victorhck).

### Fixed
- Improved url detection: '+', '%' and '~' are now allowed in the middle of urls (Aurelien Gateau).
- Fixed wrong indentation behavior in upward selections (Aurelien Gateau).

## 1.0.1 - 2019-01-12

### Added
- Added unit-tests.
- Added Travis integration.
- Added rpm and deb packages generated using CPack.

### Fixed
- Fixed indentation and make it respect indentation columns.
- Made it possible to indent/unindent selected lines with Tab/Shift+Tab.
- Update welcome text to reflect current shortcuts.

## 1.0.0 - 2018-12-30

First release
