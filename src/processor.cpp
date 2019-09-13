#include "processor.h"
#include <string>
#include <fstream>
#include <sstream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatFilename{"/stat"};
  std::string name, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice; 
  int total_cpu ,  total_idle;
  std::string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >>name >>user>> nice>> system >>idle >> iowait >> irq>> softirq>> steal>> guest>> guest_nice; 
      if ( name == "cpu"){
        total_cpu = stoi(user) +stoi(nice)+ stoi(system) + stoi(idle)+ stoi(iowait)+ stoi(irq) + stoi(softirq) + stoi(steal);
        total_idle = stoi(idle) + stoi( iowait);
        break;
      }
    }
  }
  
  float utilization;
  utilization = 1.0 - (float) total_idle /(float) total_cpu;
  
  return utilization; 
}