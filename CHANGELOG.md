# Changelog

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

### Fixed
- Fixed indentation and make it respect indentation columns.
- Made it possible to indent/unindent selected lines with Tab/Shift+Tab.
- Update welcome text to reflect current shortcuts.

### Added
- Added unit-tests.
- Added Travis integration.
- Added rpm and deb packages generated using CPack.

## 1.0.0 - 2018-12-30

First release
