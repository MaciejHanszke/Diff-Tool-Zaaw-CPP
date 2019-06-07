#include <QtWidgets>
#include <iostream>
using namespace std;

#include "customtextedit.h"
#include <cmath>

//![constructor]



QColor CustomTextEdit::getColor(int relation){
    switch( relation )
    {
    case 1:
        return (QColor(158,255,158));

    case 2:
        return (QColor(255,158,158));

    case 3:
        return (QColor(158,158,255));

    default:
        return (QColor(255,255,255));
    }
}

std::map<int, std::pair<int, int> > CustomTextEdit::getRelationMap() const
{
    return relationMap;
}

void CustomTextEdit::setRelationMap(const std::map<int, std::pair<int, int> > &value)
{
    relationMap = value;
    QTextDocument * doc = this->document();
    //std::cout<<this->toPlainText().toStdString();
    std::map<int, std::pair<int, int> >::iterator it;
    biggestRelationNumber = 0;
    for (it = relationMap.begin(); it != relationMap.end(); it++)
        {
            QTextBlock block = doc->findBlockByNumber(it->first);
            if(block.blockNumber() != -1){
                QTextCursor cursor(block);
                QTextBlockFormat blockFormat = cursor.blockFormat();
                blockFormat.setBackground(getColor(it->second.first));
                cursor.setBlockFormat(blockFormat);
                if(it->second.second > biggestRelationNumber)
                {
                    biggestRelationNumber = it->second.second;
                }
            }
        }
    //repaint();
}

CustomTextEdit::CustomTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
}

//![constructor]

//![extraAreaWidth]

int CustomTextEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    digits = max == 0 ? 1 : log10(std::abs(max)) + 1;
    int space_from_beginning = 2;
    int one_letter_width = 6;

    int space = space_from_beginning + digits + (one_letter_width * digits);

    return space+getRelationAreaWidth();
}

int CustomTextEdit::getRelationAreaWidth(){
    int space_from_beginning = 2;
    int one_letter_width = 6;
    int digits = biggestRelationNumber == 0 ? 1 : log10(std::abs(biggestRelationNumber)) + 1;
    int relationSpace = space_from_beginning + digits + (one_letter_width * digits);
    return relationSpace;
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void CustomTextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void CustomTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

QLabel *CustomTextEdit::getCursorCurPos() const
{
    return cursorCurPos;
}

void CustomTextEdit::setCursorCurPos(QLabel *value)
{
    cursorCurPos = value;
}

//![slotUpdateRequest]

//![resizeEvent]

void CustomTextEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

//![resizeEvent]

//![cursorPositionChanged]

void CustomTextEdit::highlightCurrentLine()
{
    extraSelections.clear();
        if (!isReadOnly()) {
            QTextEdit::ExtraSelection selection;

            QColor lineColor = QColor(128,194,255);

            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = textCursor();
            //selection.cursor.clearSelection();
            extraSelections.append(selection);
            if(cursorCurPos!=NULL)
            {
                QString curPosText = "Ln: " + QString::number(selection.cursor.blockNumber()+1) + ", Col: " + QString::number(selection.cursor.columnNumber()+1) ;
                cursorCurPos->setText(curPosText);
            }
        }

        setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void CustomTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    int relationWidth = getRelationAreaWidth();
    painter.fillRect(event->rect().x(),event->rect().y(), event->rect().width(), event->rect().height(), Qt::black);
    painter.fillRect(event->rect().x(),event->rect().y(), event->rect().width()-relationWidth, event->rect().height(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width()-relationWidth, fontMetrics().height(),
                             Qt::AlignRight, number);

            auto pair = relationMap[blockNumber];
            if(pair.first != 0)
            {
                QString pairnumber = QString::number(pair.second + 1);
                painter.setPen(getColor(pair.first));
                painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                                 Qt::AlignRight, pairnumber);
            }
        }


        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;

    }
}
//![extraAreaPaintEvent_2]

