#include "Proposal.h"

//default initialization
Proposal::Proposal(){
	id=-1;
	attackTime="";
}

Proposal::Proposal(int _id, string _attackTime):id(_id), attackTime(_attackTime){}

//getId
int Proposal::getId(){
	return id;
}
//setId
void Proposal::setId(int _id){
	id=_id;
}
//getValue
string Proposal::getAttackTime(){
	return attackTime;
}
//setValue
void Proposal::setAttackTime(string _attackTime){
	attackTime=_attackTime;
}
