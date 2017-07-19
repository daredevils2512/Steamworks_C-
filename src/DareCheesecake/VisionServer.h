/*
 * VisionServer.h
 *
 *  Created on: Jul 16, 2017
 *      Author: daredevils
 */

#ifndef SRC_DARECHEESECAKE_VISIONSERVER_H_
#define SRC_DARECHEESECAKE_VISIONSERVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include "AdbBridge.h"
#include <WPILib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

class VisionServer {

public:
	static const bool DEBUG_MODE=false;
	VisionServer();
	struct TargetInfo {
		double y;
		double z;
	};
	void resetVars();
	void setupServer();
	void setupCamera();
	bool isConnected();
	void reqAppRestart();
	void findCamera();
	void runServerRoutine();

	static void visionLoop();
	static void visionUpdater();


	std::vector<TargetInfo> targets;
	bool hasSetup;
	bool isActive;
	const int port = 8254; // Port. Defined by Team254. Not changing it rn.
private:
	int socketfd; // Socket instance ID, used in socket methods.
	int clientfd;
	bool pendingRestart;
	bool mIsConnected;
	double lastMessageReceivedTime;
	long lastReceived = 0;
	static int failConnectCount;
	template<typename Out>
	void splitr(const std::string &s, char delim, Out result);
	std::vector<std::string> split(const std::string &s, char delim);


};

#endif /* SRC_DARECHEESECAKE_VISIONSERVER_H_ */
