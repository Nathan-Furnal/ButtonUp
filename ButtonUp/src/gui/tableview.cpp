#include "tableview.h"

TableView::TableView() {
  this->setSelectionBehavior(QTableView::SelectColumns);
  // view.setSelectionMode(QTableView::NoSelection);
  this->setFocusPolicy(Qt::NoFocus);
  delegate = new StyledItemDelegate;
  delegate->setParent(this);
  this->setItemDelegate(delegate);
}
