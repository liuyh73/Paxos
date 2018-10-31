#include <iostream>
#include <sys/types.h>  
#include <pthread.h>
#include <semaphore.h> 
#include <cstring>
#include <cstdlib> 
#include <unistd.h>
#include "./general/General.h"
#include "./staff/Staff.h"
using namespace std;
//i define there there are 5 generals and 5 staffs.
const int GENERAL=7;
const int STAFF=5;
//define the mutex to synchronize the thread
static pthread_mutex_t prepareMutex = PTHREAD_MUTEX_INITIALIZER; 
static pthread_mutex_t commitMutex = PTHREAD_MUTEX_INITIALIZER; 

pthread_t pth[5];

void* work(void *_staff){
	Staff* staff=(Staff*)_staff;
	//wait for a while to analog prepare the proposal
	sleep(rand()%3);

	//lock
	pthread_mutex_lock(&prepareMutex);
	cout<<"The staff "<<staff->getId()<<" prepares to commit."<<endl;
	staff->prepareToCommit();
	cout<<"The staff "<<staff->getId()<<" has finished preparing to commit."<<endl;
	//unlock
	pthread_mutex_unlock(&prepareMutex);

	pthread_mutex_lock(&commitMutex);
	cout<<"The staff "<<staff->getId()<<" commits."<<endl;
	staff->commit();
	cout<<"The staff "<<staff->getId()<<" has finished committing."<<endl;
	pthread_mutex_unlock(&commitMutex);
}

int main(){
	srand(time(0));
	vector<General*>generals;
	Staff* staffs[5];

	for(int i=0;i<GENERAL;i++)
		generals.push_back(new General());
	//create 5 threads, analog 5 staffs
	cout<<"Every staff makes his decision: "<<endl;
	for(int i=0;i<STAFF;i++){
		string attackTime="tomorrow morning ";
		staffs[i]=new Staff(i+1, generals, STAFF, attackTime+char(rand()%7+'1')+" clock!");
		cout<<"Staff"<<staffs[i]->getId()<<": "<<staffs[i]->getProposal()->getAttackTime()<<endl;
	}
	sleep(1);
	for(int i=0;i<STAFF;i++)
		pthread_create(&pth[i], NULL, work, (void*)staffs[i]);
	//join the threads
	for(int i=0;i<STAFF;i++)
		pthread_join(pth[i], NULL);

	//release the space
	cout<<"\nThe final decision are as follows: "<<endl;
	for(int i=0;i<STAFF;i++){
		cout<<"Staff"<<staffs[i]->getId()<<": "<<staffs[i]->getProposal()->getAttackTime()<<endl;
		delete staffs[i];
	}

	for(int i=0;i<GENERAL;i++){
		delete generals[i];
	}

	//destroy the mutex
	pthread_mutex_destroy(&prepareMutex);
	pthread_mutex_destroy(&commitMutex);
	return 0;
}