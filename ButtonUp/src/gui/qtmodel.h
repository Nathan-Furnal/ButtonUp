#ifndef QTMODEL_H
#define QTMODEL_H
#include "game.h"
#include <QAbstractTableModel>

class QtModel : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit QtModel(QObject *parent = nullptr);

  // Header data

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void setGame(Game *game);

public slots:
  void moveStacksOnColumnClicked(const QModelIndex &idx);

private:
  Game *m_game = nullptr;
};

#endif // QTMODEL_H
