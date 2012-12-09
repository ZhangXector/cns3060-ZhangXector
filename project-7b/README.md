Project 7 - Scheduling Simulation
=================================

Cliff Kelley
------------

###Overview
For this project I found that out of each of the algorithms the quickest wait time and turnaround time were from the Shortest Job Remaining simulation. According to the example output provided, they got a score of 6.3ms and 14.3ms respectively. This could, however, just be a by-product of the source data. With more processes and/or longer processes the numbers could be very different. The highest score, not counting the Round-Robin algorithm with context-switch time, was First Come First Serve for average wait time and Round Robin for turnaround time.

###First Come First Serve
First Come First Serve was definitely the easiest to implement. It was simply iterating through each of the processes in-order to calculate the time that each would start and finish. Simply adding the complete times and subtracting from it to find the wait and complete times was easy to understand. I can see where there could easily be problems with this method, however. With longer processes all the shorter ones would need to wait. All processes run to completion which can be very long in some instances.

###Shortest Job First
While programming the logic for this algorithm, I found that there were some similarities in wait and turnaround time calculation with First Come First Serve. I found that if I simply use completion time sorting that I could pass the re-ordered list into the First Come First Serve function and get the wait/turnaround times. So First Come First Serve became a time calculation simulation for both First Come First Serve and for Shortest Job First. Shortest Job First is definitely faster than First Come First Serve. It allows the shorter processes to be computed first, but at the cost of some of the longer processes being left to wait.

###Shortest Job Remaining (Shortest Remaining Time Next)
This function was actually the one that took me the longest to figure out. Originally I thought I would be able to simply find the order of processes and send to the time calculation function, but then I realized that the processes would not always run to completion (pre-emptive). After figuring that part out, the next struggle was coming up with a way to simulate time without really using the time libraries. I decided to use a simple while loop that increments time, which seems to have given me the correct values. This function, which has the shortest time for this example data, seems very efficient to me. I can still see that there could be problems with starvation as it is still based on remaining time.

###Round Robin
After the design for Shortest Job Remaining was working properly, the Round Robin algorithm was much easier to understand. It came together much more quickly. I honestly expected this algorithm to be the most efficient as it was simply a pre-emptive version of the First Come First Serve. It was interesting to see that this had the same average wait time as the Shortest Job First method, and yet have a longer average turnaround time. It seems to me that the pre-emptive methods have such shorter wait time, but longer (in comparison) turnaround because of some processes not running to completion and being stretched out over several time slices. I can also see how aging comes into play, making those processes that come later wait until the newer processes are all done.

###Round Robin with Context Switch Time
At first I had a hard time understanding how the time was to be added to this function. I knew there would be a way to run the exact same code and use a boolean value to insert the context switch only if I wanted to. At first I was trying to add the time to the processes completion time, but soon realized that I was not getting the correct values. I then realized that I needed to add it to the cumulative time to get the results I was looking for, and after that the program gave me all the right answers immediately. I was unaware of how much of a difference adding context switching time would affect the outcome of this method. Even with only 0.4 milliseconds the result was higher numbers than the First Come First Serve function.

###Conclusion
In conclusion, I was able to experiment with the various methods of scheduling. I was able to understand better how multitasking is very important, and that there is a lot of thought that goes into designing these scheduling methods. I also saw through various research that there are many more ways than what I have done here to schedule processes. I have a better appreciation of how computers work. I was also very glad to have the opportunity to program this in Python, and to practice classes. It has been a very informative class and a great learning opportunity.
