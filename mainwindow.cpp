#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStyleFactory>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menu = new QMenu("Choice of style", this);
    oldPalette = new QPalette(QApplication::palette());
    ui->menubar->addMenu(menu);
    QDir buildDir(QCoreApplication::applicationDirPath());
    QString configFilePath = buildDir.filePath("config_style.json");
    QStringList styles = QStyleFactory::keys();
    //qDebug() << "Current Style:" << styles;

    int indexwindows = styles.indexOf("Windows");
    int indexmotif = styles.indexOf("motif");
    int indexcde = styles.indexOf("cde");
    int indexdark = styles.indexOf("kvantum-dark");
    // Insert a new style. Combination of properties of different topics Qt 5
    if (indexwindows != -1 && indexdark != -1) {
        styles.insert(indexwindows + 1, "Windows-dark");
    }
    if (indexmotif != -1 && indexdark != -1 ){
        styles.insert(indexmotif + 1, "motif-dark");
    }
    if (indexcde != -1 && indexdark != -1 ){
        styles.insert(indexcde + 1, "cde-dark");
    }
    qDebug() << "Current Style:" << styles;

    //Installing the first theme of a custom theme. Otherwise, transparency issues occur.
    if ( styles.indexOf("kvantum-dark") != -1 ) {
        QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
    } else {
        QApplication::setStyle(QStyleFactory::create("Adwaita-HighContrastInverse"));
    }

    // Add actions for each style
    for (const QString &style : styles) {
        QAction *action = menu->addAction(style);

        // Set up a slot to handle style selection
        connect(action, &QAction::triggered, [this, style, configFilePath]() {
            //Reset QPalette values ​​to default
            QApplication::setPalette(*oldPalette);
            QApplication::setStyle(QStyleFactory::create("Fusion"));
            //Disables QPalette from the system in Qt 5
            //white_QPalette();

            QFile file(configFilePath);
            if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QByteArray fileData = file.readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);

                QJsonObject jsonObj = jsonDoc.object();
                jsonObj["style"] = style;

                file.resize(0);
                QJsonDocument updatedDoc(jsonObj);
                file.write(updatedDoc.toJson());
                file.close();
            }else{
                QMessageBox::information(this, "Style .json", "Failed to create file: " + style);
            }
            //Combination of properties of different topics Qt 5
            if (style == "Windows-dark") {
                QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
                QApplication::setStyle(QStyleFactory::create("Windows"));
            } else if (style == "ukui-dark") {
                QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
                QApplication::setStyle(QStyleFactory::create("ukui"));
            } else if (style == "motif-dark") {
                QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
                QApplication::setStyle(QStyleFactory::create("motif"));
            } else if (style == "cde-dark") {
                QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
                QApplication::setStyle(QStyleFactory::create("cde"));
            } else {
                QApplication::setStyle(QStyleFactory::create(style));
            }

            QMessageBox::information(this, "Style changed", "Style changed to " + style);
        });
    }
}

MainWindow::~MainWindow()
{
    delete oldPalette;
    delete ui;
}

void MainWindow::history_QStyle()
{
    QDir buildDir(QCoreApplication::applicationDirPath());
    QString configFilePath = buildDir.filePath("config_style.json");
    QString configFile = "ukui";
    QFile file(configFilePath);

    if(!file.exists()){
        // Create and write to a file
        QFile configFile(configFilePath);
        if (configFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&configFile);
            out << R"({
                "style": "ukui"
            })";
            configFile.close();
            qDebug() << "File created:" << configFilePath;
        } else {
            qDebug() << "Failed to create file:" << configFilePath;
        }
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray fileData = file.readAll(); // Read the entire contents of the file
        file.close();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            configFile = jsonObj.value("style").toString();
        }
    }

    QApplication::setPalette(*oldPalette);
    //Disables QPalette from the system in Qt 5
    //white_QPalette();

    //Combination of properties of different topics Qt 5
    if (configFile == "Windows-dark") {
        QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
        QApplication::setStyle(QStyleFactory::create("Windows"));
    } else if (configFile == "ukui-dark") {
        QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
        QApplication::setStyle(QStyleFactory::create("ukui"));
    } else if (configFile == "motif-dark") {
        QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
        QApplication::setStyle(QStyleFactory::create("motif"));
    } else if (configFile == "cde-dark") {
        QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
        QApplication::setStyle(QStyleFactory::create("cde"));
    } else {
        QApplication::setStyle(QStyleFactory::create(configFile));
    }
}

//Disables QPalette from the system
void MainWindow::white_QPalette()
{
    QPalette Theme;

    // QPalette palette = QApplication::palette();
    // for (int role = 0; role < QPalette::NColorRoles; ++role) {
    //     qDebug() << "Role" << role << ":" << palette.color((QPalette::ColorRole)role);
    // }

    Theme.setColor(QPalette::WindowText, QColor::fromRgbF(0.137255, 0.14902, 0.160784, 1));
    Theme.setColor(QPalette::Button, QColor::fromRgbF(0.988235, 0.988235, 0.988235, 1));
    Theme.setColor(QPalette::Light, QColor::fromRgbF(1, 1, 1, 1));
    Theme.setColor(QPalette::Midlight, QColor::fromRgbF(1, 1, 1, 1));
    Theme.setColor(QPalette::Dark, QColor::fromRgbF(0.494118, 0.494118, 0.494118, 1));
    Theme.setColor(QPalette::Mid, QColor::fromRgbF(0.658824, 0.658824, 0.658824, 1));
    Theme.setColor(QPalette::Text, QColor::fromRgbF(0.137255, 0.14902, 0.160784, 1));
    Theme.setColor(QPalette::BrightText, QColor::fromRgbF(1, 1, 1, 1));
    Theme.setColor(QPalette::ButtonText, QColor::fromRgbF(0.137255, 0.14902, 0.160784, 1));
    Theme.setColor(QPalette::Base, QColor::fromRgbF(1, 1, 1, 1));
    Theme.setColor(QPalette::Window, QColor::fromRgbF(0.937255, 0.941176, 0.945098, 1));
    Theme.setColor(QPalette::Shadow, QColor::fromRgbF(0.462821, 0.462821, 0.462821, 1));
    Theme.setColor(QPalette::Highlight, QColor::fromRgbF(0.239216, 0.682353, 0.913725, 1));
    Theme.setColor(QPalette::HighlightedText, QColor::fromRgbF(1, 1, 1, 1));
    Theme.setColor(QPalette::Link, QColor::fromRgbF(0.160784, 0.501961, 0.72549, 1));
    Theme.setColor(QPalette::LinkVisited, QColor::fromRgbF(0.607843, 0.34902, 0.713726, 1));
    Theme.setColor(QPalette::AlternateBase, QColor::fromRgbF(0.968627, 0.968627, 0.968627, 1));
    Theme.setColor(QPalette::NoRole, QColor::fromRgbF(0, 0, 0, 1));
    Theme.setColor(QPalette::ToolTipBase, QColor::fromRgbF(0.968627, 0.968627, 0.968627, 1));
    Theme.setColor(QPalette::ToolTipText, QColor::fromRgbF(0.137255, 0.14902, 0.160784, 1));
    Theme.setColor(QPalette::PlaceholderText, QColor::fromRgbF(0, 0, 0, 0.501961));

    QApplication::setPalette(Theme);
}
