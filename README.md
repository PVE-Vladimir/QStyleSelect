# QStyleSelect
 <div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A QWidget template for quickly and easily changing the design of an application with the ability to choose between styles.
Git describes a feature that even the Qt developers forgot about. This feature offers unique styling capabilities. Unlike QML and CSS, using QStyleFactory allows the user to choose a wide range of QStyle widget designs without spending time configuring QML and CSS. I've seen programmers spend countless hours customizing designs via QML and CSS, even though Qt 5 and Qt 6 have a database of ready-made designs that aren't available to the user as a choice. I think it's important to highlight this very convenient, even lazy, way of customizing designs.
</div>
<p align="center">
  <img width="1898" height="697" alt="fix_1" src="https://github.com/user-attachments/assets/c338fcb5-03b0-45be-b88d-8a5e22f45ad1" />
    <div align="center">
  Figure 1 - An example of available Qt 5 styles
    </div>
</p>
<p align="center">
  <img width="635" height="440" alt="TEST_viboor_frame_30" src="https://github.com/user-attachments/assets/b65e9578-b2a4-453f-9a66-5971d24382ce" />
    <div align="center">
  Figure 2 - Selecting styles from the menu
    </div>
</p>

<br>

  **Installation and Launch**
</br>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;QWidget template (QStyleSelect) for quick and easy app design changes with a choice of styles. Download, build, and run the example source code:
</div>

<pre>
<code>
git clone https://github.com/PVE-Vladimir/QStyleSelect.git
mkdir -p QStyleSelect/build
cd QStyleSelect/build
cmake ..
make
./QStyleSelect
</code>
</pre>

Installation of styles occurs through the standard package manager apt commands:
<pre>
<code>
apt search styl | grep "qt5" | awk -F'/' '{print $1}' | sed 's/Development.*//g' | xargs sudo apt install -y  

apt search styl | grep "qt6" | awk -F'/' '{print $1}' | sed 's/Development.*//g' | xargs sudo apt install -y
</code>
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Installation takes place in the /usr/lib/x86_64-linux-gnu/qt5/plugins/styles/ or /usr/lib/x86_64-linux-gnu/qt6/plugins/styles/ directory.
You can also install a style compiled from source code here. For example, I compiled and used this style in my local Qt profile: file:///usr/local/Qt-6.4.2/plugins/styles/k4oxygen.so
</div>

<br>

  **How QStyle (QStyleFactory) Technology Works**
</br>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Setting styles via QApplication isn't fully supported in Qt Creator. The Qt Creator manual states, "Note: Qt style sheets are currently not supported for custom QStyle subclasses. We plan to address this issue in a future release." However, this doesn't mean this functionality isn't available. As the manual states, you can call QApplication::setStyle() at any time, but calling it before the constructor ensures that user preferences set with -style are honored. Example usage:
</div>
<pre>
QApplication::setStyle(QStyleFactory::create("Fusion"));
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;QStyleFactory creates a QStyle object using the create() function and a key identifying the style. Styles are either built-in or dynamically loaded from a style plugin.
</div>
<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In short, as it turned out, CustomStyle's functionality is indeed not fully developed. However, I managed to implement it completely for Qt 5 and partially for Qt 6. I still consider this a good result.<br>
Qt 5, as the primary build tool, has a more extensive style repository than Qt 6.
</div>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Compiled Qt 5 styles found in the Ubuntu repository: breeze5.so libkvantum.so libqgtk2style.so libqplastiquestyle.so libukui-proxy-style.so qtcurve.so breeze.so libqcleanlooksstyle.so libqmotifstyle.so libqt5-style-ukui.so oxygen.so
</div>
<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Compiled Qt6 styles found in the Ubuntu repository: adwaita.so libqt6ct-style.so
</div>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;These styles contain several color palette variations, most often light and black themes. My example program doesn't remove duplicate style names. You can change the style list variable to your liking if necessary. There may be differences, but I simply didn't notice them. The style list in the code is generated using:
</div>
<pre>
 QStringList styles = QStyleFactory::keys();
</pre>

<div align="justify">
Next, for Qt5, I added logic to the code for processing the properties of existing styles for dark versions:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Adding styles to the list of dark versions:
</div>
<pre>
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
                                    </pre>
<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The logic behind creating dark versions of styles:
</div>
<pre>
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
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;As you can see from the code, it's possible to combine properties from multiple themes into one. This contradicts the Qt Creator online manual, but reality diverges from theory here. The problem is that some properties of custom styles are incompatible with regular Qt styles. Therefore, the QStyleSelect example code uses these kinds of tricks to make everything work.
</div>
<br>

  **QPalette Trick**
</br>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Some custom styles, for some reason, irreversibly modify QPalette. The QPalette class contains color groups for each widget state. Therefore, the code preserves the system color groups before applying the color.
</div>

<pre>
 oldPalette = new QPalette(QApplication::palette()); 
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Afterwards, before applying the new style, the color groups are reset and the Fusion style is set just in case. Fusion is the default Qt style.
</div>
<pre>
QApplication::setPalette(*oldPalette);
QApplication::setStyle(QStyleFactory::create("Fusion"));
//Disables QPalette from the system in Qt 5
//white_QPalette();
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The white_QPalette() method only works in Qt 5. For some unknown reason, in Qt 6, if you set the color using setColor, this parameter will override setStyle, while in Qt 5, there is a color setting sequence. The white_QPalette() method implements a different approach to resetting the color group. If you use the system palette, there is a chance that the system will have a black theme selected, and then some styles will use the black color group. To make the program system-independent, the white_QPalette() method was created, which sets the default light color group.
</div>

<pre>
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
</pre>

This loop outputs a sequence of all color groups. https://doc.qt.io/qt-6/qpalette.html
<pre>
   QPalette palette = QApplication::palette();
   for (int role = 0; role < QPalette::NColorRoles; ++role) {
        qDebug() << "Role" << role << ":" << palette.color((QPalette::ColorRole)role);
   }
</pre>

<br>

  **The QApplication::setStyle Trick**
</br>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;There's a problem with some styles using transparent windows. Therefore, they need to be initialized first in the class constructor, as recommended in the Qt manual. After that, you can install other styles in any order.
</div>
<pre>
    //Installing the first theme of a custom theme. Otherwise, transparency issues occur.
    if ( styles.indexOf("kvantum-dark") != -1 ) {
        QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
    } else {
        QApplication::setStyle(QStyleFactory::create("Adwaita-HighContrastInverse"));
    }
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;It is also possible in some cases to combine the properties of two styles into one example:
</div>
<pre>
QApplication::setStyle(QStyleFactory::create("kvantum-dark"));
QApplication::setStyle(QStyleFactory::create("Windows"));
</pre>

<br>

  **QStyleSelect algorithm**
</br>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In the main window class constructor, the initial theme "kvantum-dark" or "Adwaita-HighContrastInverse" is applied on first launch. If these are not present, the default theme is used. Then, after the MainWindow object is created, the history_QStyle() method is called, which creates the config_style.json history file if it does not exist. The config_style.json file is used to preserve the user's previously selected default theme after closing the program. The initial theme on first launch is ukui. If the theme does not exist, the setStyle method sets the default theme to "Fusion." If the file exists, the default theme will be set from config_style.json. The history_QStyle method also resets the color group.
</div>

<pre>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.history_QStyle();

    return a.exec();
}
</pre>

<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The style menu is generated from a QStringList of styles and added to the standard menubar using ui->menubar->addMenu(menu);<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Each style has its own slot created in the MainWindow class constructor:
</div>

<pre>
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
</pre>

  **Conclusion**
</br>
<div align="justify">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;This git, I believe, presents an interesting example of using QStyle (QStyleFactory). This QStyleSelect template, thanks to its style options, allows for advanced application styling. A significant advantage is that you don't need to spend time on QML and CSS, but can use ready-made styles.
</div>
