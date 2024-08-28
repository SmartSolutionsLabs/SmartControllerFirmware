#ifndef INC_SMART_PUBLISHER
#define INC_SMART_PUBLISHER

#include <vector>
#include "Observer.hpp"

class Publisher : public Module {
	private:
		std::vector<Observer*> observers;

	public:
		void addObserver(Observer* observer) {
			this->observers.push_back(observer);
		}

		void removeObserver(Observer* observer) {
			this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
		}

	protected:
		void notifyObservers() {
			for (Observer* observer : this->observers) {
				observer->update();
			}
		}
};

#endif
