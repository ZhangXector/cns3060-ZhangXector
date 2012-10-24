Project 4 - Disk Scheduling
===========================

Cliff Kelley
------------

I decided to use Python for this project because I had the priveledge to take the Python class from Professor Allison over the summer, and I wanted to use my skills in python to avoid forgetting what I had learned. I feel like I have already forgotten some important principles, and ended up having to look up some things that should have been second nature. I was glad for the opportunity to practice with it again.

Before this project I was unaware of how hard-drives operated. It did not even dawn on me that hard-drives need to be able to store and receive data so quickly that they required a method of handling multiple requests. Now I feel like I better understand how they work, and why some methods are chosen over others.

###First Come First Serve###
The First come first serve algorithm was definitely the easiest to implement from this project. It was straightforward in execution, simply taking the input from the user and processing it in that exact order.

###Shortest Seek Time First###
While I was planning out how this algorithm was going to work, I was talking it out with my wife (sometimes it helps just to have someone to listen to you ramble while you figure out a problem). As I worked out how the function chooses numbers next in the sequence I realized that what I was doing looked an awful lot like recursion. I did a mock up with recursion and found that it was easier to see this one in my mind as a recursive function. I took a little work to get it to work how I wanted and return the values back up to the parent call, but it ended up being very clean this way. I like how it turned out

###Scan-Look (Elevator)###
This was the hardest of the 3 algorithms to figure out for me. I had a hard time trying to design how the head could move all the way to either end of the disk and then return and finish the remaining requested tracks. I feel like the way I did it may not be the most elegant way of performing the task. I first determine which is the closest to the current track, then move in the direction of the closest track. Then I sort the list, so that I can traverse the tracks in numerical order. My concern is that I have some duplicated code that I am not sure how to modularize. It does work, but only if more than 2 tracks are entered by the user.

One last problem I noticed is that occasionally when I tried to use ^C to stop the running simulation, Python would error. I am unsure of how to catch an exception thrown by an interrupt command like that, nor where I would put it in my code. If you have any insights into this it would be greatly appreciated. Overall I think I have been able to learn and stretch my skills from this project.
