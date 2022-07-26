#ifndef VIEW_H
#define VIEW_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <QTableView>
class View : public QTableView {
  Q_OBJECT
public:
  View();
};

// The absolute state of Qt:
// https://stackoverflow.com/questions/5587709/qtablewidget-selection-color
class StyledItemDelegate : public QStyledItemDelegate {
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
#endif // VIEW_H
