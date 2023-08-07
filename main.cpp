//Fun fact ->  The letter 'Q' was chosen as the class prefix because the letter looked beautiful
//    in Haavard's Emacs font. The 't' was added to stand for “toolkit”, inspired by Xt, the X Toolkit.

#include "mainwindow.h"

#include <QApplication>/* manages the GUI application's control flow eg: font, style, cursor*/
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PESTEXTEDITOR_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QIcon icon("D:/SUSHMITHA/C++ PROJECT SUMMER/peslogo.png");
    w.setWindowIcon(icon);
    w.setWindowTitle("PES TEXT EDITOR");
    w.show();
    return a.exec();
}
