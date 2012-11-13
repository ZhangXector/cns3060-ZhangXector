Project 6 - Threads
===================

Cliff Kelley
------------

### Part A
----------
For the first part of the program, creating the threads and printing the count returns 0. I assumed this would happen, because we talked in class about having to wait for threads to finish. I saw that the threads were created, but then main() exited without waiting for them to finish their functions. Because of this, the count was not incremented.

### Part B
----------
Part B had me a little confused at first. I wasn't sure why the count was returning as 10. I figured that since I was waiting for the threads to finish before printing the count, that I would get the correct value of 40 back. I read a little further into the assignment to where the sleep command was to be commented out and figured I'd try it to see if it would help explain this phenomenon. I then realized that the sleep was happening before the increment could occur. I then deduced that each thread was being created simultaneously and getting the value of 0 from count before any of the other threads could increment as it was supposed to. Because of this, the count would be set as 10 each time a thread completed (after waking up).

### Part C
----------
Trying out part c helped me understand why part b was giving me back 10 as a value. Because the threads were being created almost simultaneously and then sleeping for a second, there was a malfunction in the incrementation of count. However without the sleep in the function being called by the threads, part c is returning 40. I can't see why this would be happening other than that the threads are *not* actually being created simultaneously, but that the sleep was making it seem as though they were. That means that they are created in order, but are finished so quickly that they are nearly indistinguishable as ordered processes.

### Part D
----------
Using a lock for part d was easier than I had anticipated. Unfortunately my computer is quite slow at creating threads and so running part d takes quite a while. With the locks in place the threads are correctly waiting until completion before allowing a new thread to be created (regardless of the sleep command being used in the thread function). This is correctly reading out as 40 in the terminal (albeit very slowly :D).
