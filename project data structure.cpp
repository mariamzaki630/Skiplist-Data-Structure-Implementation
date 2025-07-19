#include <bits/stdc++.h>
using namespace std;
class Lnode // creat new class caled londe 
{
public:
	int num;
	Lnode **forward; //array to hold pointer to node of different level 
	Lnode(int, int);
};

Lnode::Lnode(int num, int level)
{
	this->num= num;
	forward = new Lnode*[level+1];
	memset(forward, 0, sizeof(Lnode*)*(level+1));
};

class SkipList // creat new class called skip list
 creat 3 variable , 1 pointer it's type lnode called head \\
{
	int Max_level;
	float fraction;
	int level;
	Lnode *head;
public:
SkipList(int Max_level, float fraction)
{
	this->Max_level= Max_level;
	this->fraction = fraction;
	level = 0;
	head = new Lnode(-1, Max_level);// creat header node and initialize key to -1
};
int randLevel()
{
	float randl = (float)rand()/RAND_MAX;
	int LEVEL = 0;
	while (randl < fraction &&  LEVEL < Max_level)
	{
            LEVEL++;
		randl = (float)rand()/RAND_MAX;
	}
	return  LEVEL;
};
Lnode* createNode(int num, int level)
{
	Lnode *newnode = new Lnode(num, level);
	return newnode;
};
void insert(int num)
{
	Lnode *insrt = head;
	Lnode *update[Max_level+1];
	memset(update, 0, sizeof(Lnode*)*(Max_level+1));
      for (int j = level; j >= 0; j--)// creat for loop
	{
     while (insrt->forward[j] != NULL &&
			insrt->forward[j]->num < num)
			insrt = insrt->forward[j];
		    update[j] = insrt;
	}

      if (insrt == NULL || insrt->num != num)// if insert equall null , num of insert not equall num
	{

		int Rlevel = randLevel();
		if (Rlevel > level)
		{
			for (int j=level+1;j<Rlevel+1;j++)
				update[j] = head;
			level = Rlevel;
		}
		Lnode* n = createNode(num, Rlevel);

		for (int j=0;j<=level;j++)
		{
			n->forward[j] = update[j]->forward[j];
			update[j]->forward[j] = n;
		}
		cout << " key is successfully inserted " << num << "\n";
		cout<<"____________________"<<endl;
	}
};
// boolean funcation to return true or false to know if deletion
bool Delete(int num)
{
    Lnode *insrt = head;
    Lnode *update[Max_level+1];
    memset(update, 0, sizeof(Lnode*)*(Max_level+1));
    for(int j = level; j >= 0; j--)
    {
        while(insrt->forward[j] != NULL  &&
              insrt->forward[j]->num < num)
             insrt = insrt->forward[j];
             update[j] = insrt;
    }
    insrt = insrt->forward[0];

    if(insrt != NULL and insrt->num == num)
    {

        for(int j=0;j<=level;j++)
        {
            if(update[j]->forward[j] != insrt)
                break;

            update[j]->forward[j] = insrt->forward[j];
        }

        while(level>0 &&
              head->forward[level] == 0)
            level--;
         cout<<" Key is successfully deleted "<<num<<"\n";
         cout<<" _____________________ "<<endl;
    }
    else{
        return false;
    }
};


bool search(int num)
{
    Lnode *insrt = head;

    for(int j = level; j >= 0; j--)
    {
        while(insrt->forward[j] &&insrt->forward[j]->num < num)
            {
            insrt = insrt->forward[j];
            }

    }

    insrt = insrt->forward[0];
    if(insrt and insrt->num == num)
        {
        cout<<"the target of "<< num <<"\t"<<"is existed in the skiplist:"<<endl;
        cout<<" _____________________ "<<endl;
        return true;
        }
        else{
          cout<<"the target of "<< num <<"\t"<<"is not existed in the skiplist:"<<endl;
          cout<<"____________________"<<endl;
             return false;
        }

};
// to printing all items
void displayList()
{
    cout<<"\n___SkipList_"<<"\n";
    for(int j=0;j<=level;j++)
    {
        Lnode *Lnode = head->forward[j];
        cout<<"Level "<<j<<": ";
        while(Lnode != NULL)
        {
            cout<<Lnode->num<<" ";
            Lnode = Lnode->forward[j];
        }
        cout<<"\n";
    }
};
};

int main()
{
	SkipList lst(3, 0.5);
	lst.insert(1);
	lst.insert(2);
	lst.insert(3);
	lst.search(0);
	lst.insert(4);
	lst.search(1);
	lst.Delete(0);
	lst.Delete(1);
	lst.search(1);
    lst.displayList();
}


//the output which appeared on vs console
 //key is successfully inserted 1
//____________________
 //key is successfully inserted 2
//____________________
// key is successfully inserted 3
//__________________
//the target of 0	is not existed in the skiplist:
