#ifndef PDFGENERATOR_H
#define PDFGENERATOR_H

#include <QPrinter>
#include <QPainter>
#include <QDateTime>
#include "sale.h"

class PDFGenerator
{
public:
    static bool generateInvoice(const Sale &sale, const QString &filePath);

private:
    static void drawHeader(QPainter &painter, const QRectF &rect);
    static void drawCustomerInfo(QPainter &painter, const QRectF &rect, const Sale &sale);
    static void drawItems(QPainter &painter, const QRectF &rect, const Sale &sale);
    static void drawFooter(QPainter &painter, const QRectF &rect, const Sale &sale);
};

#endif // PDFGENERATOR_H
