#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <QTableView>

// The absolute state of Qt:
// https://stackoverflow.com/questions/5587709/qtablewidget-selection-color
/**
 * @brief The StyledItemDelegate class, implements diverse redrawing of the selection
 * of cells in a table view to make it clearer what is hovered over and what is selected
 * at any time. The default behavior hid the colors too strongly.
 */
class StyledItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit StyledItemDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const {
        // Fill the background before calling the base class paint
        // otherwise selected cells would have a white background
        QVariant background = index.data(Qt::BackgroundRole);
        if (background.canConvert<QBrush>())
            painter->fillRect(option.rect, background.value<QBrush>());
        if (option.state & QStyle::State_Selected) {
            painter->save();
            QPen pen(Qt::yellow, 2, Qt::SolidLine);
            int w = pen.width() / 2;
            painter->setPen(pen);
            painter->drawRect(option.rect.adjusted(w, w, -w, -w));
            painter->restore();
        }
        if (option.state & QStyle::State_MouseOver) {
            painter->save();
            QPen pen(QColorConstants::Svg::purple, 2, Qt::SolidLine);
            int w = pen.width() / 2;
            painter->setPen(pen);
            painter->drawRect(option.rect.adjusted(w, w, -w, -w));
            painter->restore();
        }
    }
};

/**
 * @brief The TableView class, the view part of the Model/View architecture, used to represent
 * the underlying table model.
 */
class TableView : public QTableView {
  Q_OBJECT
public:
  /**
   * @brief TableView, the table view constructor.
   */
  TableView();

  private:
  StyledItemDelegate* delegate;
};


#endif // TABLEVIEW_H
