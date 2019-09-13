#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
// return private member id 
int Process::Pid() { return id; }

// TODO: Return this process's CPU utilization
// return CPU utilization
float Process::CpuUtilization() const { 
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatFilename{"/stat"};
  const std::string kid {std::to_string(id)};
  std::string utime, stime, cutime, cstime, starttime; 
  long uptime {LinuxParser::UpTime()};
  
  std::string line;
  std::ifstream stream(kProcDirectory + kid + kStatFilename);
  string tmp;
  if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> tmp >>tmp >> tmp >>tmp >> tmp >> tmp >>tmp >> tmp >>tmp >> tmp >> tmp >>tmp >> tmp  >> utime >> stime >> cutime >> cstime >> tmp >>tmp >> tmp >>tmp >> starttime >> tmp; 
  }
  
  long hertz {sysconf(_SC_CLK_TCK)};
  float total_time, seconds;
  total_time = std::stof(utime) + std::stof(stime) + std::stof(cutime) + std::stof(cstime);
  seconds = uptime - std::stof(starttime) / hertz;
  
  float utilization;
  utilization =  ((total_time / hertz) / seconds);
  
  /*
  if ( id == 38 ){
  std::ofstream myfile;
  myfile.open ("example.txt");
  myfile << total_time << " " << hertz << " " << seconds << " "  << uptime<< " "  << starttime;
  myfile.close();
  }
  */
  
  return utilization; 
}

// TODO: Return the command that generated this process
//return cmdline
string Process::Command() { 
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatCmdline{"/cmdline"};
  const std::string kid {std::to_string(id)};
  
  std::string line;
  std::ifstream stream(kProcDirectory + kid + kStatCmdline);
  if (stream.is_open()) {
      std::getline(stream, line);
  }
  return line;
}

// TODO: Return this process's memory utilization
//return process memory
string Process::Ram() const { 
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatusFilename{"/status"};
  const std::string kid {std::to_string(id)};
  
  string line, key, value;
  std::ifstream stream(kProcDirectory + kid + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if ( key == "VmSize:") {
        break;
      }
    }
  };
  
  return std::to_string(std::stoi(value) / 1024);
}

// TODO: Return the user (name) that generated this process
//return user 
string Process::User() {
  
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatusFilename{"/status"};
  const std::string kid {std::to_string(id)};
  
  string line, key, value, uid;
  std::ifstream stream(kProcDirectory + kid + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if ( key == "Uid:") {
        uid = value;
        break;
      }
    }
  };
  
  string user_name, user_id , tmp, res;
  std::ifstream filestream("/etc/passwd");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user_name >> tmp >> user_id) {
        if (user_id == uid) {
          return user_name;
        }
      }
    }
  }
  return "unknown";
}

// TODO: Return the age of this process (in seconds)
//done
long int Process::UpTime() { 
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatFilename{"/stat"};
  const std::string kid {std::to_string(id)};
  std::string utime, stime, cutime, cstime, starttime; 
  
  std::string line;
  std::ifstream stream(kProcDirectory + kid + kStatFilename);
  string tmp;
  if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> tmp >>tmp >> tmp >>tmp >> tmp >> tmp >>tmp >> tmp >>tmp >> tmp >> tmp >>tmp >> tmp  >> utime >> stime >> cutime >> cstime >> tmp >>tmp >> tmp >>tmp >> starttime >> tmp; 
  }
  
  long hertz {sysconf(_SC_CLK_TCK)};
  return std::stoi(starttime) /hertz;                   
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a) const   { 
  
  return CpuUtilization() < a.CpuUtilization() ? true: false; 
  //return std::stoi(Ram()) < std::stoi(a.Ram()) ? true: false; 

}