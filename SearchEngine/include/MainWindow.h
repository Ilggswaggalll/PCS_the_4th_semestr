#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QFrame>

#include "SearchEngine.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QLineEdit* input;
    QPushButton* button;
    QTextEdit* output;
    QCheckBox* fuzzyCheckbox;

    SearchEngine engine;

    void setupDarkTheme();
    QFrame* createCard();
    QPushButton* createStyledButton(const QString& text, const QString& color);

public:
    MainWindow();
};
