#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QFileDialog>
#include <QTextCursor>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QSyntaxHighlighter>
#include <qfontdialog.h>
#include <QWidget>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include<QPaintEvent>
#include <QColorDialog>
//#include "ui_mainwindow.h"

//initializes an instance of the MainWindow class.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//      contains the code that sets up the user interface components defined in the .ui file.
/* to specify a parent-child relationship between widgets in Qt's widget hierarchy.
*/
{
    ui->setupUi(this);
//    lineNumberArea = new LineNumberArea(ui->textEdit);
//    QFontMetrics fontMetrics(ui->textEdit->font());
//    int lineNumberAreaWidth = fontMetrics.horizontalAdvance("00000") + 10; // Adjust the width as needed
////    ui->textEdit->setViewportMargins(lineNumberAreaWidth, 0, 0, 0);
//    connect(ui->textEdit->document(), &QTextDocument::blockCountChanged, this, &MainWindow::updateLineNumberAreaWidth);
////    connect(ui->textEdit, &QTextEdit::updateRequest, this, &MainWindow::updateLineNumberArea);
//    updateLineNumberAreaWidth();
//    connect(ui->lineEdit, &QLineEdit::textChanged, ui->formulaWidget, &FormulaWidget::setFormula);


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void LineNumberArea::paintEvent(QPaintEvent *event)
//{
//    QWidget::paintEvent(event);

//    QPainter painter(this);
////    painter.setFont(&ui->textEdit->font());
//    painter.setPen(Qt::darkGray);
//    painter.fillRect(rect(), Qt::lightGray);

//    QTextBlock block = ui->textEdit->document()->begin();
//    int blockNumber = 1;
//    int contentTop = ui->textEdit->blockBoundingGeometry(block).translated(ui->textEdit->viewport()->geometry().topLeft()).top();

//    while (block.isValid())
//    {
//        painter.drawText(0, contentTop, width(), ui->textEdit->fontMetrics().height(), Qt::AlignRight, QString::number(blockNumber));

//        contentTop += ui->textEdit->blockBoundingRect(block).height();
//        block = block.next();
//        ++blockNumber;
//    }
//}

//void MainWindow::updateLineNumberAreaWidth()
//{
//    QFontMetrics fontMetrics(ui->textEdit->font());
//    int lineNumberAreaWidth = fontMetrics.horizontalAdvance("00000") + 10; // Adjust the width as needed
////    ui->textEdit->setViewportMargins(lineNumberAreaWidth, 0, 0, 0);
//}

//void MainWindow::updateLineNumberArea(const QRect &rect, int dy)
//{
//    if (dy)
//        lineNumberArea->scroll(0, dy);
//    else
//        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

//    if (rect.contains(ui->textEdit->viewport()->rect()))
//        updateLineNumberAreaWidth();
//}

//void MainWindow::on_textEdit_cursorPositionChanged()
//{
//    QRect rect = ui->textEdit->viewport()->rect();
////    lineNumberArea->scroll(0, ui->textEdit->verticalScrollBar()->value());
//    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
//}

//void MainWindow::on_textEdit_blockCountChanged(int newBlockCount)
//{
//    Q_UNUSED(newBlockCount);
//    on_textEdit_cursorPositionChanged();
//}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "");
//    The 'this' pointer is used as the parent widget for the file dialog.
//    third parameter is the directory
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textEdit->setPlainText(file.readAll());
            file.close();

        }
    }

}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save As");
//     The this pointer is used as the parent widget for the file dialog.
    //second parameter is the title of the dialog
    if(fileName.isEmpty())
        return;

//    If the file name is empty (i.e., the user canceled the dialog or
// did not provide a file name), the function returns early.


    QFile file(fileName);
//    A QFile object is created using the selected file name.

    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
//The file is opened in write-only mode using QIODevice::WriteOnly flag and is treated as a text file using QIODevice::Text flag.
        return;
    QTextStream out(&file);
//    QTextStream object is created to write to the file
    out<<ui->textEdit->toPlainText()<<"\n";
}


void MainWindow::on_actionSave_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
       return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();

}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();

}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();

}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();

}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();

}


void MainWindow::on_actionNew_triggered()
{
//    QWidget *wdg = new QWidget;
//    //opens a new widget
//    wdg->show();
//    ui->textEdit;
////    hide();
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionExit_triggered()
{
    close();

}


void MainWindow::on_actionFind_triggered()
{
    QString searchString = QInputDialog ::getText(nullptr, "Search", "Enter search string");
    /*The nullptr parameter indicates that the parent widget is not set.
      The third parameter is the text prompt shown to the user*/


    //retrieve lines of the document
    QString documentText = ui->textEdit->toPlainText();

    if (!documentText.contains(searchString, Qt::CaseInsensitive))
//       The contains function returns a boolean value indicating whether the substring is found.
    {
       QMessageBox::information(this, "Search Result", "Search string not found!");
    }
    QTextDocument *document = ui->textEdit->document();
    QTextCursor cursor(document);
//     QTextCursor object to traverse the document.
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::yellow); // Setting the highlight color

    QTextCursor highlightCursor(document);
    QTextCursor tempCursor(document);
//    tempCursor-> created to track the current position for highlighting.

    // Clear previous formatting
    tempCursor.select(QTextCursor::Document);

    tempCursor.setCharFormat(QTextCharFormat());

    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) //for searching all occurances of the searchString
    {
        highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

        if (!highlightCursor.isNull()) //if an occurance is found
        {
            highlightCursor.mergeCharFormat(highlightFormat);
            highlightCursor = tempCursor = highlightCursor;
            tempCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
            tempCursor.mergeCharFormat(highlightFormat);
//            merging the highlightFormat with the cursor's current format.
        }
    }

}


void MainWindow::on_actionReplace_triggered()
{
    QString searchString = QInputDialog ::getText(nullptr, "Search", "Enter search string");

    QString newString = QInputDialog::getText(nullptr, "Replace", "Enter new string");
    QString documentText = ui->textEdit->toPlainText();

    if (!documentText.contains(searchString, Qt::CaseInsensitive))
    //The contains function returns a boolean value indicating whether the substring is found.
    {
        QMessageBox::information(this, "Search Result", "Search string not found!");
    }

    // Find and replace all occurrences
    ui->textEdit->moveCursor(QTextCursor::Start);
    while(ui->textEdit->find(searchString))
    {
        ui->textEdit->textCursor().insertText(newString);
    }
}


void MainWindow::on_actionText_Font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->font(), this);
/*   boolean variable ok will be set to 'true' if the user selects a font and clicks "OK",
 *    or false if the user cancels the dialog. */
    if (ok) {
        ui->textEdit->setFont(font); //applied to the text
    }
}

void MainWindow::on_actionTasks_triggered()
{

}


void MainWindow::on_actionFont_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "Select Color"); //initally red

    // Check if a valid color was selected
    if (color.isValid()) {
        // Get the current text cursor
        QTextCursor cursor = ui->textEdit->textCursor();


        // Apply the text color to the selected text or the text at the cursor position
        if (cursor.hasSelection()) {
//        the code checks if there is text selected in the ui->textEdit widget using cursor.hasSelection()
            QTextCharFormat format;
            format.setForeground(QBrush(color));
            cursor.mergeCharFormat(format);
        } else {
            QTextCharFormat format;
            format.setForeground(QBrush(color));
            cursor.insertText("Text with changed color", format);
//            If no text is selected, it creates a new QTextCharFormat with the
//            selected color and inserts the text "Text with changed color" at the
//            cursor position using cursor.insertText("Text with changed color", format).
        }
    }
}


void MainWindow::on_actiontask_triggered()
{

}

