/*
 * File:            pop\util\pubsub.h
 * Programmer:      Pearce
 * Copyright (c):   2000, all rights reserved.
 * 
 *  http://www.cs.sjsu.edu/~pearce/modules/patterns/events/pubsubimp.htm
 *
 */
#ifndef PUBSUB_H
#define PUBSUB_H
#include <list>  // for our subscriber list

using namespace std;

class Publisher; // forward reference

class Subscriber
{
	public:
  	virtual ~Subscriber() {}
  	virtual void update(Publisher * who, void * what = 0) = 0;
};

class Publisher
{
	public:
  	Publisher() { notifyEnabled = true; }
  	virtual ~Publisher() {}
  	void subscribe(Subscriber * s) { subscribers.push_back(s); }
  	void unsubscribe(Subscriber * s) { subscribers.remove(s); }
  	void notify(void * what = 0, Subscriber * s = 0);
  	void setNotifyEnabled(bool flag) { notifyEnabled = flag; }
  	bool getNotifyEnabled() const { return notifyEnabled; }

	private:
		list<Subscriber*> subscribers;
		bool notifyEnabled;
};

#endif
