#include "../sale.h"
#include <QPrinter>
#include <QPainter>
#include <QDateTime>
#include <QTextDocument>
#include <QTextTable>

bool Sale::generatePDF(const QString &filePath)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(30, 30, 30, 30), QPageLayout::Millimeter);

    QTextDocument doc;
    QString html = QString(
        "<html>"
        "<head>"
        "<style>"
        "body { font-size: 200pt; }"
        "h1 { "
        "   font-size: 400%; "
        "   margin-bottom: 30px; "
        "   font-weight: 900; "
        "   transform: scale(2.0); "
        "   line-height: 2.5em; "
        "}"
        "h3 { "
        "   font-size: 300%; "
        "   margin-top: 25px; "
        "   margin-bottom: 15px; "
        "   font-weight: 800; "
        "   transform: scale(1.5); "
        "   line-height: 2em; "
        "}"
        "table { width: 100%; border-collapse: collapse; margin: 25px 0; }"
        "th, td { padding: 15px; text-align: left; border-bottom: 2px solid #ddd; }"
        "th { background-color: #f2f2f2; font-size: 200pt; font-weight: bold; }"
        "td { font-size: 180pt; }"
        ".right { text-align: right; }"
        ".center { text-align: center; }"
        ".totales { font-size: 200pt; }"
        "</style>"
        "</head>"
        "<body>"
        "<p style='transform: scale(2.0); transform-origin: center; margin: 100px 0;' align='center'>Factura de Venta</p>"
        "<br><br><br>"
        "<p style='font-size: 100pt; transform-origin: left;'>Información de Venta</p>"
        "<p>Fecha: %1</p>"
        "<p>Cliente: %2</p>"
        "<br>"
        "<p style='font-size: 160pt; transform-origin: left;'>Productos</p>"
        "<table>"
        "<tr>"
        "<th>Producto</th>"
        "<th class='right'>Cantidad</th>"
        "<th class='right'>Precio</th>"
        "<th class='right'>Subtotal</th>"
        "</tr>"
    ).arg(date.toString("dd/MM/yyyy hh:mm:ss"), customerName);

    // Agregar productos
    for (const SaleItem &item : items) {
        html += QString(
            "<tr>"
            "<td>%1</td>"
            "<td class='right'>%2</td>"
            "<td class='right'>$%3</td>"
            "<td class='right'>$%4</td>"
            "</tr>"
        ).arg(
            item.productName,
            QString::number(item.quantity),
            QString::number(item.price, 'f', 2),
            QString::number(item.price * item.quantity, 'f', 2)
        );
    }

    html += "</table><br>";

    // Totales
    html += QString(
        "<table class='totales' style='width: 400px; float: right;'>"
        "<tr>"
        "<td><strong>Total:</strong></td>"
        "<td class='right'><strong>$%1</strong></td>"
        "</tr>"
        "<tr>"
        "<td>Pagado:</td>"
        "<td class='right'>$%2</td>"
        "</tr>"
        "<tr>"
        "<td>Cambio:</td>"
        "<td class='right'>$%3</td>"
        "</tr>"
        "</table>"
        "<div style='clear: both;'></div>"
        "<br><br><br>"
        "<p align='center' style='font-size: 160pt;'>¡Gracias por su compra!</p>"
        "</body>"
        "</html>"
    ).arg(
        QString::number(total, 'f', 2),
        QString::number(amountPaid, 'f', 2),
        QString::number(change, 'f', 2)
    );

    doc.setHtml(html);
    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);

    return true;
}
