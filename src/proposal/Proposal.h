#ifndef PROPOSAL_H
#define PROPOSAL_H
#include <iostream>
#include <string>
using namespace std;
//this is the proposal class, the staff propose the proposal
class Proposal{
public:
	//initial the proposal
	Proposal();
	Proposal(int _id , string _value);
	//define some methods to set and get information.
	int getId();
	void setId(int _id);
	string getAttackTime();
	void setAttackTime(string _attackTime);

private:
	int id;
	string attackTime;
};

#endif