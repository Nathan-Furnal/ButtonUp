#include "qtmodel.h"

#include <QBrush>
#include <QMessageBox>
#include <QModelIndex>

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
      return QBrush(QColorConstants::Svg::lightgray);
    case Button::RED:
      return QBrush(QColorConstants::Svg::orangered);
    case Button::BLACK:
      return QBrush(QColorConstants::Svg::black);
    case Button::WHITE:
      return QBrush(QColorConstants::Svg::ghostwhite);
    }
  }
  if (role == Qt::ToolTipRole) {
    Button dat = (*m_game)[col][ButtonStack::N_BUTTONS - row - 1];
    switch (dat) {
    case Button::EMPTY:
      return QString("Empty button");
    case Button::RED:
      return QString("Red button");
    case Button::BLACK:
      return QString("Black button");
    case Button::WHITE:
      return QString("White button");
    }
  }

  return QVariant();
}

void QtModel::setGame(Game *game) { m_game = game; }

void QtModel::moveStacksOnColumnClicked(const QModelIndex &idx) {
  if (idx.isValid()) {
    if ((*m_game)[idx.column()].hasWhite()) {
      m_game->moveStack(idx.column());
      emit dataChanged(index(0, 0),
                       index(ButtonStack::N_BUTTONS, m_game->N_STACKS));
    } else {
      QMessageBox msgBox;
      msgBox.setWindowTitle("Rule notification 🎮");
      msgBox.setText("Only stacks with white buttons can be moved.");
      msgBox.exec();
    }
  }
}
