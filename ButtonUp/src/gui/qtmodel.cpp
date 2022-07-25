#include "qtmodel.h"

#include <QBrush>

QtModel::QtModel(QObject *parent) : QAbstractTableModel(parent) {}

// See https://doc.qt.io/qt-6/modelview.html#2-1-a-read-only-table

QVariant QtModel::headerData(int section, Qt::Orientation orientation,
                             int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
    for (int i = 0; i < ButtonStack::N_BUTTONS; i++) {
      const std::string rowHeader = std::to_string(ButtonStack::N_BUTTONS - i);
      if (i == section) {
        return QString(rowHeader.c_str());
      }
    }
  }
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    for (int i = 0; i < ButtonStack::N_BUTTONS; i++) {
      const std::string colHeader = std::to_string(i + 1);
      if (i == section) {
        return QString(colHeader.c_str());
      }
    }
  }
  return QVariant();
}

int QtModel::rowCount(const QModelIndex & /*parent*/) const { return 9; }

int QtModel::columnCount(const QModelIndex & /*parent*/) const { return 9; }

QVariant QtModel::data(const QModelIndex &index, int role) const {
  int row = index.row();
  int col = index.column();
  if (role == Qt::BackgroundRole) {
    Button dat = (*m_game)[col][ButtonStack::N_BUTTONS - row - 1];
    switch (dat) {
    case Button::EMPTY:
      return QBrush(Qt::transparent);
    case Button::RED:
      return QBrush(Qt::red);
    case Button::BLACK:
      return QBrush(Qt::black);
    case Button::WHITE:
      return QBrush(Qt::white);
    }
  }

  return QVariant();
}

void QtModel::setGame(Game *game) { m_game = game; }
