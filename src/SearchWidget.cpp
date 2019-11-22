#include "SearchWidget.h"
#include "ui_SearchForm.h"

#include <iostream>

#include "TextEdit.h"

SearchWidget::SearchWidget(TextEdit* textEdit, QWidget* parent)
        : QWidget(parent), mUi(new Ui::SearchForm), mTextEdit(textEdit) {
    mUi->setupUi(this);
    layout()->setContentsMargins(0, 0, 0, 0);

    connect(mUi->nextButton, &QToolButton::clicked, this, &SearchWidget::onNextButtonClicked);
    connect(
        mUi->previousButton, &QToolButton::clicked, this, &SearchWidget::onPreviousButtonClicked);
    connect(mTextEdit, &TextEdit::textChanged, this, &SearchWidget::onDocumentChanged);
    connect(mUi->searchLine, &QLineEdit::textChanged, this, &SearchWidget::onSearchLineChanged);
    connect(mUi->closeButton, &QToolButton::clicked, this, &SearchWidget::closeClicked);
    connect(mUi->searchLine, &QLineEdit::returnPressed, this, &SearchWidget::onNextButtonClicked);
}

SearchWidget::~SearchWidget() {
}

void SearchWidget::initialize(const QString& text) {
    mSearchVisible = true;
    mUi->searchLine->setFocus();
    mUi->searchLine->setText(text);
    searchWord(true);
}

void SearchWidget::uninitialize() {
    mSearchVisible = false;
    removeHighlights();
}

void SearchWidget::searchWord(bool selectNext, QString searchValue) {
    if (searchValue.isEmpty()) {
        searchValue = mUi->searchLine->text();
    }
    mTextDocument = mTextEdit->toPlainText();
    mCurrentSelectedWord = -1;
    searchPositionsWordsInDocument(searchValue, selectNext);
}

void SearchWidget::onNextButtonClicked() {
    if (mPositionWords.empty()) {
        return;
    }
    if (mCurrentSelectedWord != ((int)mPositionWords.size() - 1)) {
        mCurrentSelectedWord++;
    } else {
        mCurrentSelectedWord = 0;
    }
    selectWord();
}

void SearchWidget::onPreviousButtonClicked() {
    if (mPositionWords.empty()) {
        return;
    }
    if (mCurrentSelectedWord != 0) {
        mCurrentSelectedWord--;
    } else {
        mCurrentSelectedWord = mPositionWords.size() - 1;
    }
    selectWord();
}

void SearchWidget::highlightWords() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    QColor highlightColor = Qt::yellow;
    for (int position : mPositionWords) {
        QTextCursor cursor = mTextEdit->textCursor();
        cursor.setPosition(position, QTextCursor::MoveAnchor);
        cursor.setPosition(position + mUi->searchLine->text().size(), QTextCursor::KeepAnchor);

        QTextEdit::ExtraSelection currentWord;
        currentWord.format.setBackground(highlightColor);
        currentWord.cursor = cursor;
        extraSelections.append(currentWord);
    }
    mTextEdit->setExtraSelections(extraSelections);
}

void SearchWidget::removeHighlights() {
    mTextEdit->setExtraSelections({});
}

void SearchWidget::onDocumentChanged() {
    if (!mSearchVisible) {
        return;
    }
    if (mTextDocument == mTextEdit->toPlainText()) {
        return;
    }
    searchWord(false);
}

void SearchWidget::onSearchLineChanged(const QString& value) {
    searchWord(true, value);
}

void SearchWidget::searchPositionsWordsInDocument(const QString& searchString, bool selectNext) {
    mPositionWords.clear();
    QTextDocument* document = mTextEdit->document();
    removeHighlights();
    QTextCursor highlightCursor(document);
    QTextCursor cursor(document);
    cursor.beginEditBlock();
    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
        highlightCursor = document->find(searchString, highlightCursor);
        if (!highlightCursor.isNull()) {
            mPositionWords.push_back(highlightCursor.selectionStart());
        }
    }
    highlightWords();
    cursor.endEditBlock();
    setCountAndCurrentPosition();
    if (selectNext) {
        onNextButtonClicked();
    }
}

void SearchWidget::selectWord() {
    QTextDocument* document = mTextEdit->document();
    QTextCursor cursor(document);
    cursor.beginEditBlock();
    int wordStartPosition = mPositionWords.at(mCurrentSelectedWord);
    cursor.setPosition(wordStartPosition, QTextCursor::MoveAnchor);
    cursor.setPosition(wordStartPosition + mUi->searchLine->text().size(), QTextCursor::KeepAnchor);
    mTextEdit->setTextCursor(cursor);
    cursor.endEditBlock();
    setCountAndCurrentPosition();
}

void SearchWidget::setCountAndCurrentPosition() {
    bool isEmpty = mPositionWords.empty();
    mUi->countLabel->setVisible(!isEmpty);
    QString str = QString("%1 / %2").arg(mCurrentSelectedWord + 1).arg(mPositionWords.size());
    mUi->countLabel->setText(str);
}
