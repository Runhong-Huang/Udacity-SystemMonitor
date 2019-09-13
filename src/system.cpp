#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  
  vector<int> Pids {LinuxParser::Pids()} ;
  
  for (auto i: Pids){
    Process tmp(i);
    processes_.push_back(tmp);
  }
  
  std::sort(processes_.begin() , processes_.end());
  
  return processes_; 
}

// TODO: Return the system's kernel identifier (string)
//changed return value to Kernel();
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
// Modified Linux_Parser.cpp file 
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization();}

// TODO: Return the operating system name
//change the return value to OperatingSystem();
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
// return total running processes 
int System::RunningProcesses() {return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
//return total processes
int System::TotalProcesses() { return LinuxParser::TotalProcesses();}

// TODO: Return the number of seconds since the system started running
//return uptime
long int System::UpTime() { return LinuxParser::UpTime(); }
