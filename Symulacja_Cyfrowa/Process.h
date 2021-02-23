#ifndef PROCESS_H_
#define PROCESS_H_
#include <cstdint>

class Process
{
public:
	Process();
	~Process();
	virtual void Execute() = 0;
	void Activate();

private:
	bool status_process;	// Defining state of proces true -> process was executed | false -> process was not yet executed
	uint32_t weak_up;    // Value with time when process should started
};
#endif PROCESS_H_

