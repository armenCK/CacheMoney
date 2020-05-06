//Armen Kasparian 
//Project 3 Cache Simulator
//Due date: 5-6-2020

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "Cache.cpp"

using namespace std;
using std::vector;

//Struct used to contain cache run data
struct cacheData{
    int cacheSize;
    int blockSize;
    string mappingType;
    string writePolicy;
    double hitrate;
    int totBytesMemCache;
    int totBytesCacheMem;
    int blockNum;
};

//Struct used to send instruction data efficiently
struct compInst {
  int instruct;
  bool rw;
};

//Function used to parse instructions
vector<compInst> inputInstructions(string document)
{
    int linenum = 0;
    string line;
    vector<string> lines;
    vector<compInst> compactI;
    //read in cache intructions into vector called lines
    ifstream trace;
    trace.open(document);
    if (!trace) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (trace >> line) {
        lines.push_back(line);
        //cout<<line<<endl;

        compInst temp;

        if (line == "read")
        {
            temp.rw = 0;
            //cout << "The RW (read) bit is set to: " << temp.rw << endl;
        }
        else if (line == "write")
        {
            temp.rw = 1;
            //cout << "The RW (write) bit is set to: " << temp.rw << endl;
        }
        else
        {
            int number = stoi(line,0,16);
            //cout<<"Hex Integer = " << number <<endl;
            
            temp.instruct = number;
            compactI.push_back(temp);
            temp.instruct = 0;
            temp.rw = 0;
        }
    }
    trace.close();

    //cout << "The length of compactI is = " << compactI.size() << endl;
    return compactI;
}

void sendit(cache* cCache, vector<compInst> compactI, vector<cacheData> &totalData)
{
    cacheData tempData;

    tempData.cacheSize = cCache->returnCSize(); //sets Cachesize in data

    switch (cCache->returnPType()) //Sets cache mapping type in data
    {
        case 1:
            tempData.mappingType = "DM";
            break;
        case 2:
            tempData.mappingType = "2W";
            break;
        case 4:
            tempData.mappingType = "4W";
            break;
        case 0:
            tempData.mappingType = "FA";
            break;
        default:
            break;
    }
    
    tempData.blockSize = cCache->returnBSize(); //sets blockSize in data

    if (cCache->returnWP() == 0) //sets writepolicy to data
    {
        tempData.writePolicy == "WT";
    }
    else
    {
        tempData.writePolicy == "WB";
    }

    tempData.blockNum = cCache->returnBNum();

    totalData.push_back(tempData);

    //loop testing all the instruction in specific cache form
    //for(int i = 0;i<compactI.size();i++)
    for(int i = 0;i<compactI.size();i++)
    {
        cout << "The instruction number running is: " << i << endl;
        cCache->writeThrough(compactI[i].instruct, compactI[i].rw);
    }
    
}

int main(int argc, const char * argv[])
{
    vector<int> CacheSize{1,4,64,128}; //In KB taken care of in cache
    vector<int> CacheType{1,2,4,0}; //Cache placement type following the layout in spec (0 is fully associative)
    vector<int> BlockSize{4,8,16,128}; //In Bytes
    //WritePolicy is handled in the loop below

    vector<cache*> cacheConfig;
    vector<cacheData> totalData;

    //Running under the assumption that the file name will be run as an argument
    vector<compInst> compactI = inputInstructions(argv[1]);


    int currentCache, currentType, currentSize;
    cache *cachePointer;

    //Loop running the tests
    for (int i = 0; i < CacheSize.size();i++)
    {
        currentCache = CacheSize[i];

        for (int j = 0; j < CacheType.size();j++)
        {
            currentType = CacheType[j];

            for (int k = 0; k < BlockSize.size();k++)
            {
                currentSize = BlockSize[k];    

                for (int m = 0; m <= 1;m++)
                {   
                    cachePointer = new cache(currentCache, currentType, currentSize, m);
                    cacheConfig.push_back(cachePointer);
                }   
            }
        }
    }
    //cacheConfig.size()
    for(int i = 0;i<1;i++)
    {
        /*cout << "~~~~~This is the cache: " << i << " ~~~~~" << endl;
        cout << "The size of the cache is: " << cacheConfig[i]->returnCSize() << endl;
        cout << "The block size is: " << cacheConfig[i]->returnBSize() << endl;
        cout << "The mapping type is: " << cacheConfig[i]->returnPType() << endl;
        cout << "The write policy is: " << cacheConfig[i]->returnWP() << endl;
        cout << "The Number of blocks is: " << cacheConfig[i]->returnBNum() << endl;*/
        sendit(cacheConfig[i], compactI, totalData);
    }

    return 0; 
}