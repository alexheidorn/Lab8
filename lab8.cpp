/*
* Alex Heidorn
* Created: 11-2-23
* CS2 Lab8
*  
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <vector>
using namespace std;

class HeapData {
public:
    int priority;
    int theData;
    // overaload equality operator or write a fuxtion that gives 2 heaps that returns
    //for making max heap

    /**/
    friend bool operator<(const HeapData& a, const HeapData& b){
        return a.priority < b.priority;
    }
    //for making min heap
    friend bool operator>(const HeapData& a, const HeapData& b){
        return a.priority > b.priority;
    }
    

    /*
    //help from Xander
    bool operator < (const HeapData& a) {
        return this->priority < a.priority;
    }

    bool operator > (const HeapData& b){
        return this->priority > b.priority;
    }
    */

    int getPriority(){ return priority; }
};

void showHeap(vector<HeapData>& data, int curr = 0, int level = 0) {
    if (curr < data.size()) {
        showHeap(data, curr*2+2,level+1);
        cout << setw(level*3) << " ";
        cout << data[curr].priority << "(" << 
                data[curr].theData << ")" << "\n";
        showHeap(data, curr*2+1,level+1);
    }
}

int RandInRange(int low, int high) {
    return (low + rand()%(high - low + 1));
}
int main() {
    srand(time(0));
    int pdata[] = {30, 50, 70, 20, 80, 90, 200, 15, 25, 30};
    HeapData hpdata[10];
    for (int i = 0; i < 10; i++) {
        hpdata[i].priority = pdata[i];
        hpdata[i].theData = i;
    }
    // TODO create initial heap named myHeap with data
    // from hpdata, 
    vector<HeapData> myHeap;
    for (int i = 0; i < 10; i++){
        myHeap.push_back(hpdata[i]);
    }
    cout << "myHeap:\n";
    for (auto& item : myHeap) {
        cout << item.getPriority() << " ";
    }
    cout << endl;




    // how do i compare based on priority w stl fxn??
    make_heap(myHeap.begin(), myHeap.end()); 
    //this fxn is working properly, but it's duplicating the values





    // online solution
    // make_heap(myHeap.begin(), myHeap.end(), HeapData());

    /* classmate's solution 
    make_heap(myHeap.begin(), myHeap.end(), 
        [](HeapData& a, HeapData& b) {
            return a.getPriority() < b.getPriority();
        }
    );
    */

    // Lambda body??
    //make_heap(myHeap.begin(), myHeap.end(), [])


    // and a second heap named myHeap2 with
    // the same data but where it is a min heap
    vector<HeapData> myHeap2;
    for (int i = 0; i < 10; i++){
        myHeap2.push_back(hpdata[i]);
    }

    //min heap not working
    make_heap(myHeap2.begin(), myHeap2.end(), [](HeapData& a, HeapData& b) {
            return a.getPriority() > b.getPriority();
        }
    );
    //make_heap(myHeap2.begin())

    // TODO show the heap data in myHeap and myHeap2
    cout << "myHeap (Max Heap):\n";
    showHeap(myHeap);
    
    for (auto& item : myHeap) {
        cout << item.getPriority() << " ";
    }
    cout << endl;
    

    cout << "myHeap2 (Min Heap):\n";
    showHeap(myHeap2);
    /*for (auto& item : myHeap2) {
        cout << item.getPriority() << " ";
    }
    cout << endl;
    */
   
    const int TESTSIZE = 1000;
    HeapData sdata[TESTSIZE];
    HeapData hdata1[TESTSIZE];
    HeapData hdata2[TESTSIZE];
    // TODO: Create an empty heap named heap1
    vector<HeapData> heap1;

    for (int i = 0; i < TESTSIZE; i++) {
        sdata[i].priority = RandInRange(0,TESTSIZE * 10);
        sdata[i].theData = i;
        // TODO: Insert data item sdata[i] into the heap
        heap1.push_back(sdata[i]);
        push_heap(heap1.begin(), heap1.end());
    }
    // TODO: check that heap1 is a heap
    is_heap(heap1.begin(), heap1.end()) 
        ? cout << "Heap1 is a heap." 
        : cout << "Heap1 is not a heap";
        cout << endl;

    // TODO: create a heap named heap2 from the data in
    //   sdata (read into a vector then make that a
    //   heap)
    vector<HeapData> heap2;
    for (int i = 0; i < TESTSIZE; i++){
        heap2.push_back(sdata[i]);
    }
    make_heap(heap2.begin(), heap2.end());


    for (int i = (TESTSIZE - 1); i >= 0; i--) {
        // TODO:  set hdata1[i] to insert top of heap1,
        //  then pop heap1
        hdata1[i] = heap1[0];
        pop_heap(heap1.begin(), heap1.end());
        heap1.pop_back();

        // TODO: set hdata2[i] to insert top of heap2,
        // then pop heap2
        hdata2[i] = heap2[0];
        pop_heap(heap2.begin(), heap2.end());
        heap2.pop_back();
    }

    sort(sdata,sdata + TESTSIZE);

    //this code should NOT run, if things were done correctly
    for (int i = 0; i < TESTSIZE; i++) {
        if (sdata[i].getPriority() != hdata1[i].getPriority()) {
            cout << "Heap 1 value at " << i << " = " << hdata1[i].getPriority() << " does not match " << sdata[i].getPriority() << "\n";
        }
        if (sdata[i].getPriority() != hdata2[i].getPriority()) {
            cout << "Heap 2 value at " << i << " = " << hdata2[i].getPriority() << " does not match " << sdata[i].getPriority() << "\n";
        }
    }

    return 0;
}