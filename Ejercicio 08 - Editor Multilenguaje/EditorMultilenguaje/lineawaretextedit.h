#ifndef LINEAWARETEXTEDIT_H
#define LINEAWARETEXTEDIT_H

#include <QRect>
#include <QPlainTextEdit>

class LineNumberArea;

class LineAwareTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit LineAwareTextEdit(QWidget *parent = nullptr);
    int lineNumberAreaWidth() const;
    void lineNumberAreaPaintEvent(QPaintEvent *event);

signals:
    void lineaAbandonada(int linea);
    void focoPerdidoEnLinea(int linea);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void focusOutEvent(QFocusEvent *e) override;

private slots:
    void onCursorChanged();
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    LineNumberArea *m_lineNumberArea = nullptr;
    int m_lastLine = 0;
};

#endif // LINEAWARETEXTEDIT_H
