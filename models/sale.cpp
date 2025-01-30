#include "../sale.h"
#include <QPdfWriter>
#include <QPainter>

bool Sale::generatePDF(const QString &filePath) const
{
    QPdfWriter pdfWriter(filePath);
    QPainter painter(&pdfWriter);
    
    // Set font and margins
    QFont font("Arial", 12);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    
    // Draw header
    QFont headerFont = font;
    headerFont.setPointSize(16);
    headerFont.setBold(true);
    painter.setFont(headerFont);
    painter.drawText(QRect(100, 100, 400, 50), Qt::AlignCenter, "PHARMACY MANAGEMENT SYSTEM");
    
    // Draw company info
    painter.setFont(font);
    painter.drawText(QRect(100, 200, 400, 30), Qt::AlignCenter, "123 Main Street");
    painter.drawText(QRect(100, 230, 400, 30), Qt::AlignCenter, "City, State 12345");
    painter.drawText(QRect(100, 260, 400, 30), Qt::AlignCenter, "Phone: (123) 456-7890");
    
    // Draw invoice info
    painter.drawText(QRect(50, 350, 200, 30), Qt::AlignLeft, QString("Invoice #: %1").arg(id));
    painter.drawText(QRect(50, 380, 300, 30), Qt::AlignLeft, QString("Date: %1").arg(date.toString("yyyy-MM-dd hh:mm:ss")));
    
    // Draw items table header
    int y = 450;
    painter.drawText(QRect(50, y, 200, 30), Qt::AlignLeft, "Product");
    painter.drawText(QRect(250, y, 100, 30), Qt::AlignRight, "Quantity");
    painter.drawText(QRect(350, y, 100, 30), Qt::AlignRight, "Price");
    painter.drawText(QRect(450, y, 100, 30), Qt::AlignRight, "Total");
    
    y += 30;
    
    // Draw items
    for (const SaleItem &item : items) {
        painter.drawText(QRect(50, y, 200, 30), Qt::AlignLeft, item.productName);
        painter.drawText(QRect(250, y, 100, 30), Qt::AlignRight, QString::number(item.quantity));
        painter.drawText(QRect(350, y, 100, 30), Qt::AlignRight, QString("$%1").arg(item.price, 0, 'f', 2));
        painter.drawText(QRect(450, y, 100, 30), Qt::AlignRight, QString("$%1").arg(item.quantity * item.price, 0, 'f', 2));
        y += 30;
    }
    
    // Draw total
    y += 30;
    QFont totalFont = font;
    totalFont.setBold(true);
    painter.setFont(totalFont);
    painter.drawText(QRect(350, y, 200, 30), Qt::AlignRight, QString("Total: $%1").arg(total, 0, 'f', 2));
    
    // Draw footer
    y = pdfWriter.height() - 100;
    painter.setFont(font);
    painter.drawText(QRect(50, y, 500, 30), Qt::AlignCenter, "Thank you for your purchase!");
    
    return true;
}
