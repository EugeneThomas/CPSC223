/*

Eugene Thomas
CPSC223
Homework 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ====================================== helpers ==============================================
/*
  equalTo:
  For an array arr, check if there are any elements before i such that arr[i] = arr[j].
  return 1 if true, return 0 if not.
*/

int equalTo (int arr[], int i) {
  for (int j = 0; j < i; j++) {
    if (arr[i] == arr[j]) {
      return 1;
    }
  }
  return 0;
}
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





// ================================= heuristics ==============================================
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





// =================================  backtracking ==============================================

int ps (int num, int processors[], int times[], int len, int posInTimes, int target) {

    // base case if statement
    if (posInTimes == len) { // if we've reached the end...
      if (max(processors, num) >= target) { // return the lower one
        return target;
      }
      else {
        return max(processors, num);
      }
    }

    // otherwise...
    for (int i = 0; i < num; i++) {  // for each processor
      processors[i] += times[posInTimes]; // add a time
      int nextBest = ps(num, processors, times, len, posInTimes+1, target); // call the next element
      if (nextBest < target) { // if this is a more viable option...
        target = nextBest; // change the target
      }
      processors[i] -= times[posInTimes]; // take out this element...
    }
    return target; // in the end, return the target.
} // end ps



/*
  opt:
  Use backtracking to find an assignment that minimizes the largest workload.
*/

int opt (int num, int processors[], int times[], int len, int posInTimes, int target, int posInProcessors) {

  int low = lowerBound(times, len, num);

  // base case if statement (taken directly from ps)
  if (posInTimes == len) { // if we've reached the end...
    if (max(processors, num) < target) { // return the lower one
      return max(processors, num);
    }
    else {
      return target;
    }
  }

  // taken directly from ps

  for (int i = posInProcessors; i < num; i++) {  // for each processor

    /*
    HEURSITIC B. Compute a lower bound on the maximum workload (by adding the run-times of
       the individual tasks, dividing by the number of processors, and rounding
       up to the nearest integer) and stop searching if a complete assignment
       with that workload is ever found.
    */
    if (target == low) {
      return target;
    }
    // HEURISTIC B ENDED


    /*
    HEURISTIC C. Keep track of the smallest maximum workload found previously (initially
       this is the workload for the -lwd assignment as noted above) and ignore
       any partial assignment that makes the workload for some processor at
       least this large.
    */
    if (max(processors, num) >= target) {
      return target;
    }
    // HEURISTIC C ENDED

    /*
    HEURISITC D. Do not assign a task to a processor with the same (current) workload as a
       lower-numbered processor.
    HEURISTIC E. Do not assign succeeding tasks with the same run-time to processors with
       lower numbers.
    */
    if (equalTo(processors, i) == 0) { // if it is not equalTo any of the elements that come before...
      if (times[posInTimes] == times[posInTimes+1]) {
        posInProcessors = i;
      }
      else {
        posInProcessors = 0;
      }
      processors[i] += times[posInTimes]; // add a time
      int nextBest = opt(num, processors, times, len, posInTimes+1, target, posInProcessors); // call the next element
      if (nextBest < target) { // if this is a more viable option...
        target = nextBest; // change the target
      }
      processors[i] -= times[posInTimes]; // take out this element...
    }
    // HEURISTIC D ENDED
    // HEURISTIC E ENDED
  }
  return target; // in the end, return the target.
} // end opt






// =================================  main method ==============================================

int main (int argc, char* argv[]) {

  // number of processors + print statement
  int numProc = atoi(argv[1]);

  // instantiates an array to hold all of the times
  int times[argc-2];

  // instantiates an array to hold all of the commands
  char* commands[argc-2];

  int i = 2; // counter beginning at 2 for argument evaluation.
  int lenTimes = 0; // to find the length of the list of times
  int lenC = 0; // to find the length of the commands list.

  // FOR STRESS TESTING -- HOLDS ALL VALUES and their states.
  int lwVal;
  int ifLw = 0;
  int bwVal;
  int ifBw = 0;
  int lwdVal;
  int ifLwd = 0;
  int bwdVal;
  int ifBwd = 0;
  int optVal;
  int ifOpt = 0;
  // FINISH ESTABLISHING VALUES AND STATES

  // WHILE LOOP...

  while (argv[i] != NULL) { // while there are arguments...
    if (argv[i][0] == '-') { // if this begins with a -
      // if it's a heuristic....
      if (strcmp(argv[i], "-opt")*strcmp(argv[i], "-lw")*strcmp(argv[i], "-lwd")*strcmp(argv[i], "-bw")*strcmp(argv[i], "-bwd") == 0) {
        commands[lenC] = argv[i]; // add to commands list...
        lenC++; // add to the length of the h list...
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


  // Returns an answer for each of the commands.

  for (int ctr = 0; ctr < lenC; ctr++) { // for each of the elements of the commands array

    // find the correct heuristic to work with, return the right heuristic...

    // OPT

    if (strcmp(commands[ctr], "-opt") == 0) {
      if (ifOpt == 0) {
        int processors[numProc];
        for (int ctr = 0; ctr < numProc; ctr++) { // add zeroes to each of the processors
          processors[ctr] = 0;
        }
        int timeSorted[lenTimes];
        sort(times, timeSorted, lenTimes);
        optVal = opt(numProc, processors, timeSorted, lenTimes, 0, lwd(numProc, times, lenTimes), 0);
        ifOpt = 1;
      }
      printf("-opt %d\n", optVal);
    }

    // LW

    else if (strcmp(commands[ctr], "-lw") == 0) {
      if (ifLw == 0) {
        lwVal = lw(numProc, times, lenTimes);
        ifLw = 1;
      }
      printf("-lw  %d\n", lwVal);
    }

    // LWD

    else if (strcmp(commands[ctr], "-lwd") == 0) {
      if (ifLwd == 0) {
        lwdVal = lwd(numProc, times, lenTimes);
        ifLwd = 1;
      }
      printf("-lwd %d\n", lwdVal);
    }

    // BW

    else if (strcmp(commands[ctr], "-bw") == 0) {
      if (ifBw == 0) {
        bwVal = bw(numProc, times, lenTimes);
        ifBw = 1;
      }
      printf("-bw  %d\n", bwVal);
    }

    // BWD

    else if (strcmp(commands[ctr], "-bwd") == 0) { // strcmp(commands[ctr], "-bwd") == 0
      if (ifBwd == 0) {
        bwdVal = bwd(numProc, times, lenTimes);
        ifBwd = 1;
      }
      printf("-bwd %d\n", bwdVal);
    }

  } // end for loop

} // end main
