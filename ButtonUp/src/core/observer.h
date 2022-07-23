#ifndef OBSERVER_H
#define OBSERVER_H

// Implementing virtual destructors is important in pure virtual classes since
// it allows the derived class to call its own destructor instead of the base
// class' destructor.
/**
 * Provides a virtual observer class meant to be subclassed. It is entirely
 * virtual and provides an interface for the Observer/Observable design pattern.
 */
class Observer {
public:
  /**
   * Update the observer, derived classes have to manage how the update happens.
   */
  virtual void update() = 0;

  /**
   * Default destructor.
   */
  virtual ~Observer() = default;
};

/**
 * Provides a virtual observable class meant to be subclassed. It is entirely
 * virtual and provides an interface for the Observer/Observable design pattern.
 */
class Observable {
public:
  /**
   * Subscribes to an observer. It is advised to pair this function with a
   * container holding the observers.
   * @param obs the observer to subscribe to.
   */
  virtual void subscribe(Observer &obs) = 0;

  /**
   * Unsubscribes an observer from the observable. The usual expected behavior
   * is to remove it from the container holding the various observers.
   * @param obs the observer to unsubscribe.
   */
  virtual void unsubscribe(Observer &obs) = 0;

  /**
   * Notifies all the observers.
   */
  virtual void notifyAll() = 0;

  /**
   * Default destructor.
   */
  virtual ~Observable() = default;
};

#endif
