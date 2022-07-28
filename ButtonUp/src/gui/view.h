#ifndef VIEW_H
#define VIEW_H

#include "qtmodel.h"
#include "tableview.h"
#include <QGridLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QWidget>
/**
 * @brief The View class, the workhorse of the GUI. Since Qt has signals and slots,
 * this View acts as a "controller" of sorts as well and interacts with both the user
 * and the model.
 */
class View : public QWidget {
  Q_OBJECT
public:
  explicit View(QWidget *parent = nullptr);
    /**
   * @brief connectToModel, connects all the relevant signals and slots
   * between the view and the model. A signal informs and a slot behaves in response.
   */
  void connectToModel();
  /**
   * @brief pickFirstPlayer, creates a user facing prompt to decide which one
   * of the players should go first.
   */
  void pickFirstPlayer();
  /**
   * @brief createLabel, utility function to create labels for elements (especially buttons).
   * @param str, the text of the label.
   * @return a new label with the text added.
   */
  QLabel *createLabel(const QString &str);

private:
  /**
   * @brief m_table, the underlying table view to represent to model in a tabular fashion.
   */
  TableView *m_table = nullptr;
    /**
   * @brief m_model, the underlying model wrapping the game.
   */
  QtModel *m_model = nullptr;
  /**
   * @brief layout, the layout of the view.
   */
  QGridLayout *layout;
  /**
   * @brief redVictoryPoints, a score display.
   */
  QLCDNumber *redVictoryPoints;
  /**
   * @brief blackVictoryPoints, a score display.
   */
  QLCDNumber *blackVictoryPoints;
  /**
   * @brief turns, the turn counter.
   */
  QLCDNumber *turns;
  /**
   * @brief gameState, the game state display.
   */
  QLabel *gameState = new QLabel("Pick a player!");

public slots:
  /**
   * @brief setGameState, reacts to actual game changes by updating the gameState display.
   */
  void setGameState(Game::GameState);
    /**
   * @brief tally, reacts to victory points changes (end of round) and updates them.
   */
  void tally(int, int);
  /**
   * @brief endGame, reacts to end of game data and information with a different
   * message box than other user interaction.
   */
  void endGame(int, int);

signals:
  /**
   * @brief replay, signals that the user asked for a new round informs
   * the model that the underlying data must be updated.
   */
  void replay();
};

#endif // VIEW_H
