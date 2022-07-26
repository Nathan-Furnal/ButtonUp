#include "view.h"

View::View() {
  this->setSelectionBehavior(QTableView::SelectColumns);
  // view.setSelectionMode(QTableView::NoSelection);
  this->setFocusPolicy(Qt::NoFocus);
  this->setItemDelegate(new StyledItemDelegate);
}
