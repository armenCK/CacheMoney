//Armen Kasparian 
//Project 3 Cache Simulator
//Due date: 5-6-2020
#include "Set.cpp"
#include <iostream>
#include <cmath>

using namespace std;

class cache{
private:
    int size; //Cache Size in Bytes
    int placementType; //Cache Placement Type 1 = direct mapped, 2 = 2 way, 4 = 4 way, 0 = fully assoc
    int blockSize; //Block Size in Bytes
    bool writePolicy; //0 is write-through 1 is write-back
    int blockNum; //Number of blocks in set
    int numSets; //Number of sets
    int hits;
    int misses;
    int bMemCache;
    int bCacheMem;
    //set *setHolder; //Array of sets

    vector<set> setHolder;
    

public:
    cache();
    cache(const int size, const int type, const int bSize, const bool wb);
    ~cache();

    void writeThrough(int address, bool readWrite);
    
    //Return functions for getting values of private
    int returnCSize();
    int returnPType();
    int returnBSize();
    bool returnWP();
    int returnBNum();
};

cache::cache()
{
    size = 0;
    placementType = 0;
    blockSize = 0;
    writePolicy = 0;
    hits = 0;
    misses = 0;
    bMemCache = 0;
    bCacheMem = 0;

    vector<set> setHolder(numSets, set(blockNum));
}

cache::~cache()
{
}

cache::cache(const int csize, const int type, const int bSize, const bool wb)
{
    size = csize*1024; 
    placementType = type;
    blockSize = bSize;
    writePolicy = wb;
    hits = 0;
    misses = 0;
    bMemCache = 0;
    bCacheMem = 0;

    //Determining number of sets in cache
    if (placementType != 0)
    {
        numSets = (size/blockSize)/placementType;
        blockNum = type;
    }
    else 
    {
        numSets = 1;
        blockNum = size/blockSize;
    }
    
    vector<set> setHolder(numSets, set(blockNum));
}

void cache::writeThrough(int address, bool readWrite)
{
    //cout << "I think this is the old input address: " << address << endl;
    double addressD = static_cast<double>(address);
    int offsetsize = static_cast<int>(log2(blockSize));
    double newInputAddress = address >> offsetsize;
    //cout << "I think this is the new input address: " << static_cast<int>(newInputAddress) << endl;
    int setValue = static_cast<int>(newInputAddress)%numSets;
    //cout << "Set value: " << setValue <<endl;
    double setSize = log2(numSets);
    int tagValue = static_cast<int>(newInputAddress) >> static_cast<int>(setSize);
    //cout << "I think this is the setValue: " << setValue << endl;
    //cout << "I think this is the tagValue: " << tagValue << endl;

    if (readWrite == false) //reading
    {
        cout << "You are in the read" << endl;
        if(setHolder[setValue].TagChecker(tagValue, blockNum))
        {
            cout << "We HIT HIT HIT on a read" << endl;
            hits++;
        }
        else
        {
            cout << "We missed on a read" << endl;
            misses++;
            bMemCache++;
        }
    }
    else //writing
    {
        cout << "You are in the write" << endl;
        if(setHolder[setValue].TagChecker(tagValue, blockNum))
        {
            cout << "We HIT HIT HIT on a write" << endl;
            hits++;
        }
        else
        {
            cout << "We missed on a write" << endl;
            misses++;
            bCacheMem++;
            setHolder[setValue].SetTagWT(tagValue);
        }
    }
}

//Fucntions for returning private data values
int cache::returnCSize()
{
    return size;
}
int cache::returnPType()
{
    return placementType;
}
int cache::returnBSize()
{
    return blockSize;
}
bool cache::returnWP()
{
    return writePolicy;
}
int cache::returnBNum()
{
    return blockNum;
}