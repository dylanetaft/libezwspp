#include <iostream>
#include <memory>

namespace libezwspp {
	/**
	* Interface for all WebSocket data and connection events
	* Inherit this class to process connection and data driven events
	*/
	class EventListener {
		public:
			virtual void onNewConnection() = 0;
			virtual void onCloseConnection() = 0;
	};
	/**
	* This class that will create a listening socket, and process all requests.  
	* Calling initialize() will lock your current thread until application shutdown.
	*/	
	class ConnectionMgr {
		public:
			void initialize(std::shared_ptr<EventListener> listener) {
				listener->onNewConnection();
				
			}
		
	};
}

class myapp: public libezwspp::EventListener {
	public:
		void onNewConnection() {
			std::cout << "Hello world 2.\n";
		}
		void onCloseConnection() {	
		}
	
};


int main() {
	auto app = std::make_shared<myapp>();
	libezwspp::ConnectionMgr mgr;
	mgr.initialize(app);
	
	return 0;

}