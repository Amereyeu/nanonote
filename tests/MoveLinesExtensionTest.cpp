#include "MoveLinesExtension.h"

#include <QMainWindow>
#include <QTextCursor>
#include <QtTest>

#include <catch2/catch.hpp>

#include "TextUtils.h"

static constexpr Qt::KeyboardModifiers MODIFIERS = Qt::ShiftModifier | Qt::AltModifier;

SCENARIO("movelines") {
    QMainWindow window;
    TextEdit* edit = new TextEdit;
    window.setCentralWidget(edit);
    edit->addExtension(new MoveLinesExtension(edit));
    // Some tests won't work if the window is not visible (for example word-wrapping tests)
    window.show();
    GIVEN("A cursor at the beginning of a line") {
        setupTextEditContent(edit,
                             "1\n"
                             "|2\n"
                             "3\n");

        WHEN("I press modifiers+down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            THEN("The line is moved down") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("1\n"
                                   "3\n"
                                   "|2\n"));
            }
        }
        WHEN("I press modifiers+up") {
            QTest::keyClick(edit, Qt::Key_Up, MODIFIERS);
            THEN("The line is moved up") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("|2\n"
                                   "1\n"
                                   "3\n"));
            }
        }
    }
    GIVEN("A cursor at the beginning of a line and no final \\n in the document") {
        setupTextEditContent(edit,
                             "|1\n"
                             "2");

        WHEN("I press modifiers+down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            THEN("The line is moved down") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("2\n"
                                   "|1"));
            }
        }
    }
    GIVEN("A cursor in the middle of a line") {
        setupTextEditContent(edit,
                             "1\n"
                             "22|22\n"
                             "3\n");

        WHEN("I press modifiers+down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            THEN("The line is moved down") {
                REQUIRE(dumpTextEditContent(edit) == QString("1\n3\n22|22\n"));
            }
        }
        WHEN("I press modifiers+up") {
            QTest::keyClick(edit, Qt::Key_Up, MODIFIERS);
            THEN("The line is moved up") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("22|22\n"
                                   "1\n"
                                   "3\n"));
            }
        }
    }
    GIVEN("A multi-line selection") {
        setupTextEditContent(edit,
                             "1\n"
                             "22*22\n"
                             "333|3\n"
                             "4\n");
        WHEN("I press modifiers+down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            THEN("The selected lines are moved down") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("1\n"
                                   "4\n"
                                   "22*22\n"
                                   "333|3\n"));
            }
        }
        WHEN("I press modifiers+up") {
            QTest::keyClick(edit, Qt::Key_Up, MODIFIERS);
            THEN("The lines are moved up") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("22*22\n"
                                   "333|3\n"
                                   "1\n"
                                   "4\n"));
            }
        }
    }
    GIVEN("A reversed multi-line selection") {
        setupTextEditContent(edit,
                             "1\n"
                             "22|22\n"
                             "333*3\n"
                             "4\n");

        WHEN("I press modifiers+down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            THEN("The selected lines are moved down") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("1\n"
                                   "4\n"
                                   "22|22\n"
                                   "333*3\n"));
            }
        }
        WHEN("I press modifiers+up") {
            QTest::keyClick(edit, Qt::Key_Up, MODIFIERS);
            THEN("The lines are moved up") {
                REQUIRE(dumpTextEditContent(edit)
                        == QString("22|22\n"
                                   "333*3\n"
                                   "1\n"
                                   "4\n"));
            }
        }
    }
    GIVEN("A cursor on the 2nd line of 4") {
        QString initialContent = "1\n"
                                 "|2\n"
                                 "3\n"
                                 "4";
        setupTextEditContent(edit, initialContent);
        AND_GIVEN("I moved the line down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            WHEN("I undo the changes") {
                edit->undo();
                THEN("The text edit is back to its previous state") {
                    REQUIRE(dumpTextEditContent(edit) == initialContent);
                }
            }
        }
    }
    GIVEN("A text with wrapped lines") {
        constexpr int LINE_SIZE = 100;
        auto stringFill = [](char ch) {
            QString str;
            str.fill(ch, LINE_SIZE);
            return str;
        };
        auto initialContent =
            QString('|') + stringFill('a') + '\n' + stringFill('b') + '\n' + stringFill('c');
        setupTextEditContent(edit, initialContent);
        // TODO: Add a REQUIRE checking the first line is wrapped

        WHEN("I move the first line down") {
            QTest::keyClick(edit, Qt::Key_Down, MODIFIERS);
            THEN("The entire wrapped line is moved") {
                auto expectedContent =
                    stringFill('b') + "\n|" + stringFill('a') + '\n' + stringFill('c');
                REQUIRE(dumpTextEditContent(edit) == expectedContent);
                WHEN("I undo the changes") {
                    edit->undo();
                    THEN("The text edit is back to its previous state") {
                        REQUIRE(dumpTextEditContent(edit) == initialContent);
                    }
                }
            }
        }
    }
    GIVEN("A text with wrapped lines and the cursor is on the last line") {
        constexpr int LINE_SIZE = 100;
        auto stringFill = [](char ch) {
            QString str;
            str.fill(ch, LINE_SIZE);
            return str;
        };
        auto initialContent = stringFill('a') + '\n' + stringFill('b') + "\n|" + stringFill('c');
        setupTextEditContent(edit, initialContent);
        // TODO: Add a REQUIRE checking the first line is wrapped

        WHEN("I move the line up") {
            QTest::keyClick(edit, Qt::Key_Up, MODIFIERS);
            THEN("The entire wrapped line is moved") {
                auto expectedContent =
                    stringFill('a') + "\n|" + stringFill('c') + '\n' + stringFill('b');
                REQUIRE(dumpTextEditContent(edit) == expectedContent);
                WHEN("I undo the changes") {
                    edit->undo();
                    THEN("The text edit is back to its previous state") {
                        REQUIRE(dumpTextEditContent(edit) == initialContent);
                    }
                }
            }
        }
    }
}
