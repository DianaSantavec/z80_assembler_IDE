#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent): QSyntaxHighlighter(parent){

    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bld\\b"), QStringLiteral("\\bLD\\b"),
        QStringLiteral("\\bnop\\b"), QStringLiteral("\\bNOP\\b"),
        QStringLiteral("\\binc\\b"), QStringLiteral("\\bINC\\b"),
        QStringLiteral("\\bdec\\b"), QStringLiteral("\\bDEC\\b"),
        QStringLiteral("\\brlca\\b"), QStringLiteral("\\bRLCA\\b"),
        QStringLiteral("\\bex\\b"), QStringLiteral("\\bEX\\b"),
        QStringLiteral("\\badd\\b"), QStringLiteral("\\bADD\\b"),
        QStringLiteral("\\brrca\\b"), QStringLiteral("\\bRRCA\\b"),
        QStringLiteral("\\bdjnz\\b"), QStringLiteral("\\bDJNZ\\b"),
        QStringLiteral("\\brla\\b"), QStringLiteral("\\bRLA\\b"),
        QStringLiteral("\\bjr\\b"), QStringLiteral("\\bJR\\b"),
        QStringLiteral("\\brra\\b"), QStringLiteral("\\bRRA\\b"),
        QStringLiteral("\\bcpl\\b"), QStringLiteral("\\bCPL\\b")
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegularExpression(QStringLiteral("#[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text){

    for (const HighlightingRule &rule : qAsConst(highlightingRules)){
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
}
