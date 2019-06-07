#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <map>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class CustomTextEdit : public QPlainTextEdit
{
    Q_OBJECT
    QList<QTextEdit::ExtraSelection> extraSelections;
    //potrzebne sa 3 wartosci: linia w której został dokonany edit, typ editu(add/delete), oraz numer relacji
    std::map<int, std::pair<int,int>>relationMap;
    int biggestRelationNumber = 0;
    bool isLeft = false;

public:
    CustomTextEdit(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();


    std::vector<std::tuple<int, int, int> > getRelations() const;
    void setRelations(const std::vector<std::tuple<int, int, int> > &value);

    QColor getColor(int relation);
    std::map<int, std::pair<int, int> > getRelationMap() const;
    void setRelationMap(const std::map<int, std::pair<int, int> > &value);

    int getRelationAreaWidth();
    QLabel *getCursorCurPos() const;
    void setCursorCurPos(QLabel *value);


    bool getIsLeft() const;
    void setIsLeft(bool value);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    QLabel * cursorCurPos = NULL;
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CustomTextEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CustomTextEdit *codeEditor;
};

//![extraarea]

#endif
