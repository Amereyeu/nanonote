#ifndef INDENTEXTENSION_H
#define INDENTEXTENSION_H

#include "TextEdit.h"

#include <functional>

class IndentExtension : public TextEditExtension
{
public:
    explicit IndentExtension(TextEdit *textEdit);

    bool keyPress(QKeyEvent *event) override;

private:
    using ProcessSelectionCallback = std::function<void(QTextCursor&)>;
    bool canRemoveIndentation() const;
    void insertIndentation();
    void removeIndentation();
    void insertIndentedLine();
    void processSelection(ProcessSelectionCallback callback);
};

#endif // INDENTEXTENSION_H
