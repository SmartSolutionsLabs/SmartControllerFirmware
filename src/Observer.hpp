#ifndef INC_SMART_OBSERVER
#define INC_SMART_OBSERVER

/**
 * This interface says any actuator must be observing changes to execute anything.
 */
class Observer {
	public:
		virtual void update() = 0;
};

#endif
