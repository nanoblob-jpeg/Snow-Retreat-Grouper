#include "constants.h"

#ifndef SETUP
#define SETUP
int getNumberOfParticipants();

void getList(plist &people, int population);

void getCounselor(std::map<std::string, int> &counselorsPerCabin);

void setSpacesPerCabin(std::map<std::string, int> &spacesPerCabin, std::map<std::string, int> &counselorsPerCabin);
#endif