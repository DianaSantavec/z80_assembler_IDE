#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Highlighter : public QSyntaxHighlighter{

    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);
    Highlighter *highlighter;

protected:
    void highlightBlock(const QString &text) override;

private:

    struct HighlightingRule{
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat quotationFormat;
};


#endif // HIGHLIGHTER_H
