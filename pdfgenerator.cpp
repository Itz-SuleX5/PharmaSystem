#include "pdfgenerator.h"
#include <QTextDocument>
#include <QTextTable>
#include <QSqlQuery>
#include <QSqlError>

bool PDFGenerator::generateInvoice(const Sale &sale, const QString &filePath)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    
    QPainter painter;
    if (!painter.begin(&printer)) {
        return false;
    }
    
    // Set up the document rectangle
    QRectF rect = printer.pageRect(QPrinter::DevicePixel);
    
    // Draw each section
    drawHeader(painter, rect);
    
    QRectF customerRect = rect;
    customerRect.setTop(rect.top() + 150);
    customerRect.setHeight(100);
    drawCustomerInfo(painter, customerRect, sale);
    
    QRectF itemsRect = rect;
    itemsRect.setTop(customerRect.bottom() + 50);
    itemsRect.setHeight(400);
    drawItems(painter, itemsRect, sale);
    
    QRectF footerRect = rect;
    footerRect.setTop(itemsRect.bottom() + 50);
    footerRect.setHeight(100);
    drawFooter(painter, footerRect, sale);
    
    painter.end();
    return true;
}

void PDFGenerator::drawHeader(QPainter &painter, const QRectF &rect)
{
    painter.save();
    
    // Company name
    QFont font = painter.font();
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    
    painter.drawText(rect.adjusted(0, 20, 0, 0),
                    Qt::AlignHCenter,
                    "PHARMACY MANAGEMENT SYSTEM");
    
    // Address and contact
    font.setPointSize(10);
    font.setBold(false);
    painter.setFont(font);
    
    QStringList contactInfo;
    contactInfo << "123 Main Street" << "City, State 12345" << "Phone: (123) 456-7890" << "Email: pharmacy@example.com";
    
    int y = 60;
    foreach (const QString &line, contactInfo) {
        painter.drawText(rect.adjusted(0, y, 0, 0),
                        Qt::AlignHCenter,
                        line);
        y += 20;
    }
    
    painter.restore();
}

void PDFGenerator::drawCustomerInfo(QPainter &painter, const QRectF &rect, const Sale &sale)
{
    painter.save();
    
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);
    
    // Invoice details
    QString invoiceText = QString("Invoice #: %1\nDate: %2")
                         .arg(sale.id)
                         .arg(sale.date.toString("yyyy-MM-dd hh:mm:ss"));
    
    painter.drawText(rect.adjusted(10, 0, -10, 0),
                    Qt::AlignLeft | Qt::TextWordWrap,
                    invoiceText);
    
    painter.restore();
}

void PDFGenerator::drawItems(QPainter &painter, const QRectF &rect, const Sale &sale)
{
    painter.save();
    
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);
    
    // Draw table headers
    QStringList headers;
    headers << "Product" << "Quantity" << "Price" << "Total";
    
    float columnWidth = rect.width() / headers.size();
    float y = rect.top();
    
    // Draw headers
    for (int i = 0; i < headers.size(); ++i) {
        QRectF headerRect(rect.left() + i * columnWidth, y, columnWidth, 30);
        painter.drawText(headerRect, Qt::AlignCenter, headers[i]);
    }
    
    y += 30;
    
    // Draw items
    QSqlQuery query;
    query.prepare("SELECT p.name, si.quantity, si.price "
                 "FROM sale_items si "
                 "JOIN products p ON p.id = si.product_id "
                 "WHERE si.sale_id = ?");
    query.addBindValue(sale.id);
    
    if (query.exec()) {
        while (query.next()) {
            QString name = query.value(0).toString();
            int quantity = query.value(1).toInt();
            float price = query.value(2).toFloat();
            float total = quantity * price;
            
            QStringList values;
            values << name
                  << QString::number(quantity)
                  << QString("$%1").arg(price, 0, 'f', 2)
                  << QString("$%1").arg(total, 0, 'f', 2);
            
            for (int i = 0; i < values.size(); ++i) {
                QRectF itemRect(rect.left() + i * columnWidth, y, columnWidth, 25);
                painter.drawText(itemRect, Qt::AlignCenter, values[i]);
            }
            
            y += 25;
        }
    }
    
    painter.restore();
}

void PDFGenerator::drawFooter(QPainter &painter, const QRectF &rect, const Sale &sale)
{
    painter.save();
    
    QFont font = painter.font();
    font.setPointSize(10);
    font.setBold(true);
    painter.setFont(font);
    
    // Draw total
    QString totalText = QString("Total: $%1").arg(sale.total, 0, 'f', 2);
    painter.drawText(rect.adjusted(rect.width() / 2, 0, -10, 0),
                    Qt::AlignRight,
                    totalText);
    
    // Draw thank you message
    font.setBold(false);
    painter.setFont(font);
    painter.drawText(rect.adjusted(10, 50, -10, 0),
                    Qt::AlignCenter,
                    "Thank you for your purchase!");
    
    painter.restore();
}
