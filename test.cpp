#include <iostream>
#include <memory>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <uv.h>

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
	class ConnectionMgr { //TODO: Make singleton
		private:
			uv_loop_t *uvloop_;
			uv_tcp_t server_;
			
			static void AcceptConnection(uv_stream_t *server, int status) {
				std::cout << "Accept connection\n";
			};
			
			void listen(int port) {
					struct addrinfo hints;
					struct addrinfo *servinfo;
					int yes = 1;
					std::memset(&hints, 0, sizeof hints); //C sockets make more sense and work with libuv
					hints.ai_family = AF_UNSPEC;
					hints.ai_socktype = SOCK_STREAM;
					hints.ai_flags = AI_PASSIVE;
					getaddrinfo(NULL,"8080", &hints, &servinfo);
					for (struct addrinfo *p = servinfo;p != NULL;p = p->ai_next) { //loop through all addresses found for hints
						int sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
						setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
						bind(sockfd,p->ai_addr, p->ai_addrlen);
						uv_tcp_t *uvsock;
						uvsock = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
						uv_tcp_init(uv_default_loop(), uvsock);
						uv_tcp_open(uvsock,sockfd);
						uv_listen((uv_stream_t *)uvsock, 10, &ConnectionMgr::AcceptConnection);
						
						
					}
					freeaddrinfo(servinfo);
					uvloop_ = uv_default_loop();
					uv_run(uv_default_loop(),UV_RUN_DEFAULT);
					//uv_tcp_init(uvloop_, &serversocket);
					
			}
		public:
			void initialize(std::shared_ptr<EventListener> listener, int port) {
				listen(8080);
				
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
	mgr.initialize(app, 8080);
	
	return 0;

}