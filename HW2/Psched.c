/*

Eugene Thomas
CPSC223
Homework 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// MAX AND MIN

/*
  minIndex:
  Finds minimum index of the array.
*/

int minIndex (int arr[], int len) {
  int index = 0; // index
  int currMin = arr[0]; // current minimum
  for (int ctr = 1; ctr < len; ctr++) { // for each of the other elements in the array
    if (currMin > arr[ctr]) { // if this element is less than the current minimum
      currMin = arr[ctr]; // change current min
      index = ctr; // change index
    }
  } // end for loop
  return index; // return the correct index
} // end minIndex

/*
  max:
  Finds maximum of the array.
*/

int max (int arr[], int len) {
  int currMax = arr[0]; // current max
  for (int ctr = 1; ctr < len; ctr++) { // for each of the other elements in
    if (currMax < arr[ctr]) { // if this element is more than the current max
      currMax = arr[ctr]; // change current max
    }
  } // end for loop
  return currMax; // return the max
} // end max

/*
  closestToMax: Finds the index i in array arr such that target-(arr[i]+num) is a minimum.
  Finds maximum of the array.
  Used in bw.
*/

int closestToMax (int arr[], int len, int num, int target) {
  int valid = 0; // returns 0 when there has yet to be a valid solution, 1 when there has been.
  int index; // begin with base index
  int diff; // target-arr[i]-num.
  for (int i = 0; i < len; i++) { // for each element in the array.
    if (arr[i] + num <= target) { // if the max does not change...
      if (valid == 0) { // if there no valid solutions...
        valid = 1; // make a valid solution
        index = i; // this is the first index
        diff = target-(arr[i]+num); // make this the initial difference
      }
      else { // if there exist valid solutions...
        if ((target-(arr[i]+num)) < diff) { // if this new difference is less than the old one...
          index = i; // this is the new index
          diff = target-(arr[i]+num); // this is the new difference
        }
      }
    } // end larger if
  } // end for
  return index; // return index that gives smallest difference.
} // end closestToMax

// MAX AND MIN END

/*
  SORTING METOD
*/

void sort (int arr[], int arr2[], int len) {
  for (int i = 0; i < len; i++) {
    arr2[i] = arr[i];
  }
  for (int ctr = 1; ctr < len; ctr++) {
    int currVal = arr2[ctr]; // current value
    int currIndex = ctr; // current index
    while (currIndex > 0) { // while x is in bounds
      if (currVal>arr2[currIndex-1])  {
        // swap currVal and arr[currIndex-1]:
        arr2[currIndex] = arr2[currIndex-1];
        arr2[currIndex-1] = currVal;
        currIndex--; // subtract one from current index
      }
      else {
        break; // end of this while loop
      }
    } // end while
  } // end for loop

  // here, we copied the first arr, now we are dumping all of the data into the second one:
} // end sort

// lower bound method
int lowerBound (int arr[], int len, int num) {
  int retSum = 0; // return sum
  for (int i = 0; i < len; i++) { // add all values in arr
    retSum += arr[i];
  }
  if (retSum%num == 0) { // return sum rounded up to nearest int
    return retSum/num;
  }
  else {
    return retSum/num + 1;
  }
}

/*
  lw:
  Use the Least-Workload heuristic:  Assign the tasks (i.e., the run-times) in
  the order in which they appear on the command line; andmassign each task to a
  processor that has the least workload at the time of the assignment.
*/

int lw (int num, int times[], int len) {
  // if an invalid input...
  if (num < 1) {
    return 0;
  }

  // if a valid input...
  else {
    int processors[num];
    for (int ctr = 0; ctr < num; ctr++) { // add zeroes to each of the processors
      processors[ctr] = 0;
    }
    for (int ctrT = 0; ctrT < len; ctrT++) { // add each of the time elements
      int index = minIndex(processors, num);
      processors[index] += times[ctrT];
    }
    return max(processors, num); // returns the maximum.
  }
} // end lw

/*
  lwd:
  Use the Least-Workload-Decreasing heuristic:  First sort the tasks in decreasing
  order of run-time and then assign them in that order using the Least-Workload heuristic.
*/

int lwd (int num, int times[], int len) {
  int timeHolder[len];
  sort(times, timeHolder, len);
  return lw(num,timeHolder,len); // return lw of the sorted array!
} // end lwd

/*
  bw:
  Use the Best-Workload heuristic:  Assign the tasks in the order in which their
  run-times appear on the command line; and assign each task to a processor that
  has the least current workload, unless this assignment would NOT increase the
  maximum current workload, in whichcase assign that task to the busiest processor
  with this property.
*/

int bw (int num, int times[], int len) { // note: fix this for the additional heuristic....
  // if an invalid input...
  if (num < 1) {
    return 0;
  }

  // if a valid input...
  else {
    int processors[num];
    for (int ctr = 0; ctr < num; ctr++) { // add zeroes to each of the processors
      processors[ctr] = 0;
    }
    for (int ctrT = 0; ctrT < len; ctrT++) { // add each of the time elements
      int index = minIndex(processors, num);
      if (processors[index]+times[ctrT] > max(processors,num)) { // if this changes the maximum, continue.
        processors[index] += times[ctrT];
      }
      else { // if not, search for the closestToMax...
        index = closestToMax(processors, num, times[ctrT], max(processors,num));
        processors[index] += times[ctrT];
      }
    }
    return max(processors, num); // returns the maximum.
  }
} // end bw

/*
  bwd:
  Use the Best-Workload-Decreasing heuristic:  First sort the tasks in decreasing
  order of run-time and then assign them in that order using the Best-Workload heuristic.
*/

int bwd (int num, int times[], int len) {
  int timeHolder[len];
  sort(times, timeHolder, len);
  return bw(num,timeHolder,len); // return lw of the sorted array!
} // end bwd


/*
  opt:
  Use backtracking to find an assignment that minimizes the largest workload.
*/

int opt (int num, int times[], int len) {

  // Heuristic A: Sort the array
  int timeHolder[len];
  sort(times, timeHolder, len);

  // Heuristic B: lowerBound
  int low = lowerBound(timeHolder, len, num);
  printf("Lower bound: %d\n", low);
  // Heuristic C:
  int up = bwd(num, times, len);
  printf("Upper bound: %d\n", up);

  // Heuristic D:

  // Heuristic E:

  return low;
} // end opt


// THE MAIN METHOD

int main (int argc, char* argv[]) {

  // name of the program + diagnostic print statement
  // mainly used to examine how argv[] works, commented out
  // char* nameProgram = argv[0];
  //printf("%s\n", nameProgram);

  // number of processors + print statement
  int numProc = atoi(argv[1]);
  // printf("There are %d processors\n", numProc); // diagnostic print

  // instantiates an array to hold all of the times
  int times[argc-2];

  // instantiates an array to hold all of the heuristics
  char* heuristics[argc-2];

  // method to place all times into the time array

  int i = 2; // counter beginning at 2 for argument evaluation.
  int lenTimes = 0; // to find the length of the list of times
  int lenH = 0; // to find the length of the heuristics list.

  // WHILE LOOP...
  while (argv[i] != NULL) { // while there are arguments...
    if (argv[i][0] == '-') { // if this begins with a -
      // if it's a heuristic....
      if (strcmp(argv[i], "-opt")*strcmp(argv[i], "-lw")*strcmp(argv[i], "-lwd")*strcmp(argv[i], "-bw")*strcmp(argv[i], "-bwd") == 0) {
        heuristics[lenH] = argv[i]; // add to heuristics list...
        // printf("%s\n", heuristics[lenH]); // diagnostic print
        lenH++; // add to the length of the h list...
      }
      else {
        // printf("Invalid input! Exiting this code!\n");
        exit(0);
      }
    } // end if...

    else {
      times[lenTimes] = atoi(argv[i]); // returns 0 if invalid input, truncates any decimal
      // printf("%d\n", times[lenTimes]); // diagnostic print
      lenTimes++;
    }
    i++; // counter
  }
  // END WHILE LOOP

  // Returns an answer for each of the heuristics.
  for (int ctr = 0; ctr < lenH; ctr++) { // for each of the elements of the heuristics array

    // find the correct heuristic to work with, return the right heuristic..

    if (strcmp(heuristics[ctr], "-opt") == 0) {
      printf("-opt %d\n", opt(numProc, times, lenTimes));
    }
    else if (strcmp(heuristics[ctr], "-lw") == 0) {
      printf("-lw  %d\n", lw(numProc, times, lenTimes));
    }
    else if (strcmp(heuristics[ctr], "-lwd") == 0) {
      printf("-lwd %d\n", lwd(numProc, times, lenTimes));
    }
    else if (strcmp(heuristics[ctr], "-bw") == 0) {
      printf("-bw  %d\n", bw(numProc, times, lenTimes));
    }
    else { // strcmp(heuristics[ctr], "-bwd") == 0
      printf("-bwd %d\n", bwd(numProc, times, lenTimes));
    }

  } // end for loop

} // end main
