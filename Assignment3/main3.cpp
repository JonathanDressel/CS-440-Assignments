/* This is a skeleton code for two-pass multi-way sorting, you can make modifications as long as you meet
   all question requirements*/
//Currently this program will just load the records in the buffers (main memory) and print them when filled up.
//And continue this process untill the full Emp.csv is read.

#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//defines how many buffers are available in the Main Memory
#define buffer_size 22

struct EmpRecord {
    int eid;
    string ename;
    int age;
    double salary;
};
EmpRecord buffers[buffer_size]; // this structure contains 22 buffers; available as your main memory.

// Grab a single block from the Emp.csv file, in theory if a block was larger than
// one tuple, this function would return an array of EmpRecords and the entire if
// and else statement would be wrapped in a loop for x times based on block size
EmpRecord Grab_Emp_Record(fstream &empin) {
    string line, word;
    EmpRecord  emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}

//Printing whatever is stored in the buffers of Main Memory
//Can come in handy to see if you've sorted the records in your main memory properly.
void Print_Buffers(int cur_size) {
    for (int i = 0; i < cur_size; i++)
    {
        cout << i << " " << buffers[i].eid << " " << buffers[i].ename << " " << buffers[i].age << " " << buffers[i].salary << endl;
    }
}

void swap(EmpRecord* node1, EmpRecord* node2) {
    EmpRecord tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
    return;
}

void write_to_file(fstream file) {
    return;
}

int file_index = 0;
//Sorting the buffers in main_memory based on 'eid' and storing the sorted records into a temporary file
//You can change return type and arguments as you want.
void Sort_in_Main_Memory(int cur_size, fstream &file_sort){
    int i = 1;
    //fstream file_sort;
    file_sort.open("tmp" + to_string(file_index) + ".csv", ios::out);
    file_index++;
    for(i; i < cur_size; i++) {
        EmpRecord tmp = buffers[i];
        int j = i - 1;

        while(j >= 0 && buffers[j].eid > tmp.eid) {
            buffers[j+1] = buffers[j];
            j--;
        }
        buffers[j+1] = tmp;
    }

    i = 0;
    for(i; i < cur_size; i++) {
        file_sort << buffers[i].eid << ",";
        file_sort << buffers[i].ename << ",";
        file_sort << buffers[i].age << ",";
        file_sort << buffers[i].salary << endl;
    }
    file_sort.close();
    return;
}

//You can use this function to merge your M-1 runs using the buffers in main memory and storing them in sorted file 'EmpSorted.csv'(Final Output File)
//You can change return type and arguments as you want.
void Merge_Runs_in_Main_Memory(char *emp_file){
    vector<string> tmp_files;
    ifstream *open_file[19];





    //store and open tmp files.
    for(int i = 0; i < 19; i++) {
        tmp_files.push_back("tmp" + to_string(i) + ".csv");

    }









    //close all tmp files.
    for(int i = 0; i < 19; i++) {
     //   open_file[i]->close();
    }






    return;
}

int main() {
  // open file streams to read and write
  fstream input_file;

  //array to hold all of the tmp*.csv files
  int tmp_size = 19;
  int tmp_index = 0;
  char emp_file[] = "Emp.csv";
  fstream *tmp_files = new fstream[tmp_size];


  input_file.open("Emp.csv", ios::in);

  // flags check when relations are done being read
  bool flag = true;
  int cur_size = 0;

  /*First Pass: The following loop will read each block put it into main_memory
    and sort them then will put them into a temporary file for 2nd pass */
  while (flag) {
      // FOR BLOCK IN RELATION EMP

      // grabs a block
      EmpRecord  single_EmpRecord  = Grab_Emp_Record(input_file);
      // checks if filestream is empty
      if (single_EmpRecord.eid == -1) {
          flag = false;
          Print_Buffers(cur_size); // The main_memory is not filled up but there are some leftover data that needs to be sorted.
      }
      if(cur_size + 1 <= buffer_size){
          //Memory is not full store current record into buffers.
          buffers[cur_size] = single_EmpRecord ;
          cur_size += 1;
      }
      else{
          //memory is full now. Sort the blocks in Main Memory and Store it in a temporary file (runs)
          cout << "Main Memory is full. Time to sort and store sorted blocks in a temporary file" << endl;
          Print_Buffers(buffer_size);
          //SortMain("Attributes You Want");
          Sort_in_Main_Memory(cur_size, tmp_files[tmp_index]);
          tmp_index++;
          //After sorting start again. Clearing memory and putting the current one into main memory.
          cur_size = 0;
          buffers[cur_size] = single_EmpRecord;
          cur_size += 1;
      }

  }
  Sort_in_Main_Memory(cur_size-1, tmp_files[tmp_index]);
//  input_file.close();

  /* Implement 2nd Pass: Read the temporary sorted files and utilize main_memory to store sorted runs into the EmpSorted.csv*/

  //Uncomment when you are ready to store the sorted relation
  //fstream sorted_file;
  //sorted_file.open("EmpSorted.csv", ios::out | ios::app);

  //Pseudocode
  bool flag_sorting_done = false;
  while(!flag_sorting_done){
      Merge_Runs_in_Main_Memory(emp_file);
      break;
  }

//  cout << "\n\n\n\n";
  //insertionSort(buffer_size);
  //Print_Buffers(buffer_size);

//  cout << "\n\n\n\n";
  //You can delete the temporary sorted files (runs) after you're done if you want. It's okay if you don't.

  return 0;
}
