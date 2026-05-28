#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <QFrame>
#include <QPalette>
#include <QApplication>
#include <QScrollArea>
#include <QGraphicsDropShadowEffect>

#include <memory>

    // ======================
    // Цветовая схема
    // ======================

    const QString PRIMARY_COLOR   = "#6C63FF";
const QString PRIMARY_DARK    = "#5A52D6";

const QString BG_COLOR        = "#121426";
const QString SURFACE_COLOR   = "#1A1F38";

const QString TEXT_COLOR      = "#F3F4F6";
const QString SECONDARY_TEXT  = "#9CA3AF";

const QString CARD_COLOR      = "#0F3460";
const QString BORDER_COLOR    = "#2A2F4A";

const QString ACCENT_COLOR    = "#00B4D8";

// ======================
// Constructor
// ======================

MainWindow::MainWindow() {

    setWindowTitle("Поисковый движок");

    resize(1100, 780);
    setMinimumSize(900, 650);

    setupDarkTheme();

    // ======================
    // CENTRAL WIDGET
    // ======================

    QWidget* central = new QWidget();

    central->setObjectName("centralWidget");

    central->setStyleSheet(
        "#centralWidget {"
        "   background-color: " + BG_COLOR + ";"
                     "}"
        );

    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(18);

    // ======================
    // HEADER
    // ======================

    QLabel* title = new QLabel("Поисковый движок");

    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
        "font-size: 36px;"
        "font-weight: 800;"
        "color: " + TEXT_COLOR + ";"
                       "margin-bottom: 0px;"
        );

    mainLayout->addWidget(title);

    QLabel* subtitle = new QLabel("Индексация и поиск по текстовым файлам");

    subtitle->setAlignment(Qt::AlignCenter);

    subtitle->setStyleSheet(
        "font-size: 15px;"
        "color: " + SECONDARY_TEXT + ";"
                           "margin-bottom: 6px;"
        );

    mainLayout->addWidget(subtitle);

    // ======================
    // FOLDER CARD
    // ======================

    QFrame* folderCard = createCard();

    QVBoxLayout* folderCardLayout = new QVBoxLayout(folderCard);

    folderCardLayout->setContentsMargins(20, 20, 20, 20);
    folderCardLayout->setSpacing(16);

    QLabel* folderLabel = new QLabel("Выберите папку с файлами");

    folderLabel->setStyleSheet(
        "font-size: 18px;"
        "font-weight: 700;"
        "color: " + TEXT_COLOR + ";"
        );

    folderCardLayout->addWidget(folderLabel);

    QHBoxLayout* folderRow = new QHBoxLayout();

    QPushButton* folderButton =
        createStyledButton("📂 Обзор", PRIMARY_COLOR);

    folderButton->setFixedWidth(140);
    folderButton->setFixedHeight(48);

    QLabel* folderPathLabel = new QLabel("Папка не выбрана");

    folderPathLabel->setWordWrap(true);

    folderPathLabel->setStyleSheet(
        "color: " + SECONDARY_TEXT + ";"
                                     "padding: 12px 14px;"
                                     "background-color: " + CARD_COLOR + ";"
                       "border-radius: 12px;"
                       "font-size: 13px;"
        );

    folderRow->addWidget(folderButton);
    folderRow->addWidget(folderPathLabel, 1);

    folderCardLayout->addLayout(folderRow);

    mainLayout->addWidget(folderCard);

    // ======================
    // SEARCH CARD
    // ======================

    QFrame* searchCard = createCard();

    QVBoxLayout* searchCardLayout = new QVBoxLayout(searchCard);

    searchCardLayout->setContentsMargins(20, 20, 20, 20);
    searchCardLayout->setSpacing(16);

    QLabel* searchLabel = new QLabel("Поиск");

    searchLabel->setStyleSheet(
        "font-size: 18px;"
        "font-weight: 700;"
        "color: " + TEXT_COLOR + ";"
        );

    searchCardLayout->addWidget(searchLabel);

    // ======================
    // INPUT
    // ======================

    input = new QLineEdit();

    input->setPlaceholderText("Введите слово для поиска...");

    input->setMinimumHeight(54);

    input->setStyleSheet(

        "QLineEdit {"

        "   background-color: " + CARD_COLOR + ";"
                       "   color: " + TEXT_COLOR + ";"

                       "   border: 2px solid transparent;"
                       "   border-radius: 14px;"

                       "   padding: 14px 18px;"

                       "   font-size: 14px;"

                       "   selection-background-color: " + PRIMARY_COLOR + ";"

                          "}"

                          "QLineEdit:focus {"

                          "   border: 2px solid " + PRIMARY_COLOR + ";"

                          "}"

        );

    searchCardLayout->addWidget(input);

    // ======================
    // CHECKBOX
    // ======================

    fuzzyCheckbox = new QCheckBox(
        "Нестрогий поиск"
        );

    fuzzyCheckbox->setStyleSheet(

        "QCheckBox {"

        "   color: " + SECONDARY_TEXT + ";"
                           "   spacing: 10px;"
                           "   font-size: 13px;"
                           "background-color: transparent;"
                           "}"

                           "QCheckBox::indicator {"

                           "   width: 20px;"
                           "   height: 20px;"

                           "   border-radius: 6px;"

                           "   border: 2px solid " + BORDER_COLOR + ";"

                         "   background-color: " + CARD_COLOR + ";"

                       "}"

                       "QCheckBox::indicator:hover {"

                       "   border: 2px solid " + PRIMARY_COLOR + ";"

                          "}"

                          "QCheckBox::indicator:checked {"
                          "   background-color: " + PRIMARY_COLOR + ";"
                          "   border: 2px solid white;"
                          "}"

        );

    searchCardLayout->addWidget(fuzzyCheckbox);

    // ======================
    // SEARCH BUTTON
    // ======================

    button = createStyledButton("🔎 Найти", PRIMARY_COLOR);

    button->setFixedHeight(52);

    searchCardLayout->addWidget(button);

    mainLayout->addWidget(searchCard);

    // ======================
    // RESULTS CARD
    // ======================

    QFrame* resultsCard = createCard();

    QVBoxLayout* resultsLayout = new QVBoxLayout(resultsCard);

    resultsLayout->setContentsMargins(20, 20, 20, 20);

    QLabel* resultsTitle = new QLabel("Результаты поиска");

    resultsTitle->setStyleSheet(
        "font-size: 18px;"
        "font-weight: 700;"
        "color: " + TEXT_COLOR + ";"
                       "margin-bottom: 6px;"
        );

    resultsLayout->addWidget(resultsTitle);

    // ======================
    // OUTPUT
    // ======================

    output = new QTextEdit();

    output->setReadOnly(true);

    output->setMinimumHeight(320);

    output->setStyleSheet(

        "QTextEdit {"

        "   background-color: " + CARD_COLOR + ";"

                       "   color: " + TEXT_COLOR + ";"

                       "   border: none;"

                       "   border-radius: 16px;"

                       "   padding: 18px;"

                       "   font-size: 14px;"

                       "   font-family: 'Segoe UI';"

                       "   line-height: 1.6;"

                       "}"

        );

    resultsLayout->addWidget(output);

    mainLayout->addWidget(resultsCard, 1);

    // ======================
    // SCROLL AREA
    // ======================

    QScrollArea* scrollArea = new QScrollArea();

    scrollArea->setWidgetResizable(true);

    scrollArea->setFrameShape(QFrame::NoFrame);

    scrollArea->setWidget(central);

    setCentralWidget(scrollArea);

    // ======================
    // ENTER SEARCH
    // ======================

    connect(
        input,
        &QLineEdit::returnPressed,
        button,
        &QPushButton::click
        );

    // ======================
    // FOLDER BUTTON
    // ======================

    connect(folderButton, &QPushButton::clicked,

            [this, folderPathLabel]() {

                QString dirPath =
                    QFileDialog::getExistingDirectory(
                        this,
                        "Выберите папку с .txt файлами"
                        );

                if (!dirPath.isEmpty()) {

                    engine.loadFolder(dirPath.toStdString());

                    folderPathLabel->setText(dirPath);

                    output->append(
                        "<div style='margin-bottom:12px;'>"
                        "📁 <b>Индексация папки:</b><br>"
                        "<span style='color:#9CA3AF;'>"
                        + dirPath +
                        "</span></div>"
                        );

                    output->append(
                        "<div style='margin-bottom:20px;'>"
                        "📄 Загружено документов: <b>"
                        + QString::number(engine.getDocuments().size()) +
                        "</b></div>"
                        );
                }
            }

            );

    // ======================
    // SEARCH BUTTON
    // ======================

    connect(button, &QPushButton::clicked,

            [this]() {

                QString query = input->text().trimmed();

                if (query.isEmpty()) {

                    QMessageBox::warning(
                        this,
                        "Пустой запрос",
                        "Введите слово для поиска"
                        );

                    return;
                }

                // ======================
                // STRATEGY
                // ======================

                if (fuzzyCheckbox->isChecked()) {

                    engine.setStrategy(
                        std::make_unique<FuzzySearchStrategy>()
                        );

                } else {

                    engine.setStrategy(
                        std::make_unique<ExactSearchStrategy>()
                        );

                }

                auto results =
                    engine.search(query.toStdString(), 3);

                // ======================
                // OUTPUT
                // ======================

                output->clear();

                output->append(

                    "<div style='margin-bottom:20px;'>"

                    "<div style='font-size:18px;"
                    "font-weight:700;'>"

                    "🔍 Результаты поиска: \"" + query + "\""

                              "</div>"

                              "<div style='color:#9CA3AF;"
                              "margin-top:4px;'>"

                              "Режим: "

                    + QString(
                        fuzzyCheckbox->isChecked()
                            ? "Нестрогий"
                            : "Точный"
                        )

                    + "</div>"

                      "</div>"

                    );

                // ======================
                // EMPTY
                // ======================

                if (results.empty()) {

                    output->append(

                        "<div style='"
                        "background-color:#16213E;"
                        "padding:16px;"
                        "border-radius:14px;'>"

                        "😔 Ничего не найдено"

                        "</div>"

                        );

                }

                // ======================
                // RESULTS
                // ======================

                else {

                    output->append(

                        "<div style='margin-bottom:18px;'>"

                        "📊 Найдено документов: <b>"

                        + QString::number(results.size())

                        + "</b></div>"

                        );

                    for (int docId : results) {

                        std::string filePath =
                            engine.getDocumentPath(docId);

                        std::string fileName = filePath;

                        size_t lastSlash =
                            filePath.find_last_of("/\\");

                        if (lastSlash != std::string::npos) {

                            fileName =
                                filePath.substr(lastSlash + 1);

                        }

                        output->append(

                            "<div style='"

                            "background-color:#16213E;"

                            "padding:14px;"

                            "margin-bottom:12px;"

                            "border-radius:14px;"

                            "'>"

                            "<span style='"

                            "color:#6C63FF;"
                            "font-weight:700;"
                            "font-size:14px;'>"

                            + QString::fromStdString(fileName)

                            +

                            "</span>"

                            "</div>"

                            );

                    }

                }

            }

            );

}

// ======================
// DARK THEME
// ======================

void MainWindow::setupDarkTheme() {

    qApp->setStyleSheet(

        "QWidget {"

        "   background-color: " + BG_COLOR + ";"

                     "   color: " + TEXT_COLOR + ";"

                       "}"

                       // ======================
                       // SCROLLBAR
                       // ======================

                       "QScrollBar:vertical {"

                       "   background-color: transparent;"

                       "   width: 10px;"

                       "   margin: 0px;"

                       "}"

                       "QScrollBar::handle:vertical {"

                       "   background-color: " + BORDER_COLOR + ";"

                         "   border-radius: 5px;"

                         "   min-height: 30px;"

                         "}"

                         "QScrollBar::handle:vertical:hover {"

                         "   background-color: " + PRIMARY_COLOR + ";"

                          "}"

                          "QScrollBar::add-line:vertical, "
                          "QScrollBar::sub-line:vertical {"

                          "   height: 0px;"

                          "}"

                          "QScrollBar::add-page:vertical, "
                          "QScrollBar::sub-page:vertical {"

                          "   background: none;"

                          "}"

        );

}

// ======================
// CARD
// ======================

QFrame* MainWindow::createCard() {

    QFrame* card = new QFrame();

    card->setFrameShape(QFrame::NoFrame);

    card->setStyleSheet(

        "QFrame {"

        "   background-color: " + SURFACE_COLOR + ";"

                          "   border-radius: 22px;"

                          "}"

        );

    // ======================
    // SHADOW
    // ======================

    QGraphicsDropShadowEffect* shadow =
        new QGraphicsDropShadowEffect();

    shadow->setBlurRadius(30);

    shadow->setOffset(0, 6);

    shadow->setColor(QColor(0, 0, 0, 80));

    card->setGraphicsEffect(shadow);

    return card;

}

// ======================
// BUTTON
// ======================

QPushButton* MainWindow::createStyledButton(
    const QString& text,
    const QString& color
    ) {

    QPushButton* btn = new QPushButton(text);

    btn->setCursor(Qt::PointingHandCursor);

    btn->setStyleSheet(

        "QPushButton {"

        "   background-color: " + color + ";"

                  "   color: white;"

                  "   border: none;"

                  "   border-radius: 14px;"

                  "   padding: 12px 20px;"

                  "   font-size: 14px;"

                  "   font-weight: 700;"

                  "}"

                  "QPushButton:hover {"

                  "   background-color: " + PRIMARY_DARK + ";"

                         "}"

                         "QPushButton:pressed {"

                         "   background-color: #4B43C9;"

                         "}"

        );

    return btn;

}
