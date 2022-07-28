#ifndef QTMODEL_H
#define QTMODEL_H
#include "game.h"
#include <QAbstractTableModel>
/**
 * @brief The QtModel class, A Qt model wrapping the game class to interact with a table view.
 */
class QtModel : public QAbstractTableModel {
  Q_OBJECT

public:
  /**
   * @brief QtModel, the model constructor.
   * @param parent, the parent object for Qt inheritance tree.
   */
  explicit QtModel(QObject *parent = nullptr);

  // Header data
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  /**
   * @brief setState, sets the state of the underlying game.
   */
  void setState(Game::GameState);
  ~QtModel();

public slots:
  /**
   * @brief moveStacksOnColumnClicked, reacts to a click action on a column of the table view.
   * If a column is clicked anywhere, it will trigger a move of the buttons (plays the move).
   * @param idx, the current index of the clicked cell.
   */
  void moveStacksOnColumnClicked(const QModelIndex &idx);
    /**
   * @brief replay, Manages the replay behavior by resetting the underlying data of the game.
   */
  void replay();

private:
  Game *m_game = nullptr;

signals:
  /**
   * @brief turnChanged, signals when the turn counter changes.
   * @param turns, the new value of the turn counter.
   */
  void turnChanged(int turns);
  /**
   * @brief stateChanged, signals that the game state changed.
   * @param gs, the new value of the state.
   */
  void stateChanged(Game::GameState gs);
  /**
   * @brief redTally, signals the new value of the red victory points.
   */
  void redTally(int);
  /**
   * @brief blackTally, signals the new value of the black victory points.
   */
  void blackTally(int);
  /**
   * @brief roundTally, signals the points value at the end of the round.
   */
  void roundTally(int, int);
  /**
   * @brief endGame, signals the points value at the end of the round with a different
   * behavior because this signal is used at the end of the *game*, not the end of the *round*.
   */
  void endGame(int, int);
};

#endif // QTMODEL_H
