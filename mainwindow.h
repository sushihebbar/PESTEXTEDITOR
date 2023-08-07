#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*They ensure that the contents of the header file are only included once.*/
#include <QMainWindow>
//Base class for main window

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
//indicates that the MainWindow class is defined elsewhere.
class LineNumberArea;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //    Q_OBJECT macro to enable the use of signals and slots.
    /* signals and slots are used for the communication between objects
     * A signal is emitted when a particular event occurs.(there are user defined signals as well)
     * A slot is a function that is called in response to a particular signal.
     * signal is emitted when an object changes its state.
     * slots, they can be invoked by any component, regardless of its access level, via a signal-slot connection*/

public:
    MainWindow(QWidget *parent = nullptr);
//    The QWidget class is the base class of all user interface objects.
    QString currentFilePath = "";
    QString currentFile = "";
    ~MainWindow();

private slots:
    //    QTextEdit *textEdit;
    //    QString currentFile;
    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionSave_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_actionFind_triggered();

    void on_actionReplace_triggered();

    void on_actionText_Font_triggered();

    void on_actionTasks_triggered();
//    void updateLineNumberAreaWidth();
//    void updateLineNumberArea(const QRect &rect, int dy);
//    void on_textEdit_blockCountChanged(int newBlockCount);
//    void on_textEdit_cursorPositionChanged();

    void on_actionFont_Color_triggered();

    void on_actiontask_triggered();

private:
    Ui::MainWindow *ui;
    // ui is a pointer to the Ui::MainWindow class, which represents the user interface created in Qt Designer.
//    LineNumberArea *lineNumberArea;

};

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(QWidget *parent = nullptr) : QWidget(parent) {}
//    LineNumberArea(Ui::MainWindow* ui);

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // MAINWINDOW_H

