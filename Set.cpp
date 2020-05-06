//Armen Kasparian 
//Project 3 Cache Simulator
//Due date: 5-6-2020

#include <iostream>
#include <vector>

using std::vector;
using namespace std;

struct way {
  int tag = 0;
  bool dirty = 0;
};

class set{
private:
    int blocks;
    vector<int>tagBlocks;
    vector<int> LRU;

public:
    set();
    set(const int BlockNum);
    set(const int *BlockNumber);
    ~set();
    bool TagChecker(int tag, int blocknum);
    void SetTagWT(int tag);
    void movePos(int loc);

    int returnBlocks();
};

set::set()
{
    blocks = 0;
    vector<int> LRU;
    LRU.push_back(0);
    vector<int> tagBlocks(blocks, 0);
}

set::set(const int BlockNum)
{
    blocks = BlockNum;
    vector<int> LRU;
    for (int i = 0; i < blocks; i++)
    {
        LRU.push_back(i);
    }
    vector<int> tagBlocks(blocks, 0);
}

set::set(const int *BlockNumber)
{
    int BlockNum = *BlockNumber;
    blocks = BlockNum;
    vector<int> LRU;
    for (int i = 0; i < blocks; i++)
    {
        LRU.push_back(i);
    }

    vector<int> tagBlocks(blocks, 0);
}

set::~set()
{
}

void set::movePos(int loc)
{
    int temp = LRU[loc];
    LRU.erase (LRU.begin()+loc-1); //might not need the minus one
    LRU.push_back(temp);
}

bool set::TagChecker(int checktag, int blocknum)
{
    bool hitme = false;
    cout << "We have made it to the tag checker" << endl;
    cout << "This is the block num: " << blocknum << endl;
    for(int i = 0; i<blocknum;i++)
    {
        cout << "This is the check tag: " << checktag << endl;
        cout << "This is the tag in location: " << tagBlocks[0] << endl;
        if (tagBlocks[i] == checktag)
        {
            cout << "HIT HIT HIT HIT HIT HIT HIT HIT HIT HIT HIT" << endl;
            movePos(i);
            hitme = true;
            break;
        }
    }

    return hitme;
}

void set::SetTagWT(int newtag)
{
    cout << "This is the value of location: " << LRU[0] << endl; 
    int loc = LRU.front();
    cout << "This is the value of location: " << loc << endl; 
    //Process of moving front of vector to back
    vector<int>::iterator it; 
    it = LRU.begin(); 
    LRU.erase(it);
    LRU.push_back(loc);

    //Setting tag
    //ways[loc].tag = newtag;
}

int set::returnBlocks()
{
    return blocks;
}