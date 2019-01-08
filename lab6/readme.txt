To make the program utilize multithreads, I took out the nested for
loops from main and made a new function to pass to the pthread_create.
I did this because that is where the program looped through each 
pixel and did the work, so that is where the threads would come in 
handy.
In making the new function, I had to make some of the variable that it
uses global so that they were accessible to both main and my new 
function.
Then, I made a new 3D array to store all the pixel numbers, to ensure 
that they would be in the correct order, since implementing the 
threads will compute them in a different order.
Because of this, I moved the print statement from the for loop into main.
Then in main, I made two for loops, one to create the threads and 
the other to join the threads. 

The first problem I ran into was the pixels were out of order because
I failed to make a 3D array at first.
The next problem was that no matter the amount of threads passed, it 
took the same amount of time. This was because i didnt modify the 
limits of the for loop. Once I changed the initial i to be the current
thread index, and incremented i by nthread, the timing was much faster 
for larger thread numbers.

The implementation of SRT improves performance with more and more threads,
as is evidenced by the time outputs:

real  0m41.721s
user  0m41.606s
sys   0m0.080s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real 0m20.987s
user 0m41.611s
sys  0m0.022s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real 0m11.180s
user 0m43.710s
sys  0m0.005s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real 0m5.766s
user 0m44.651s
sys  0m0.003s
mv 8-test.ppm.tmp 8-test.ppm

It goes from 41 s to 6 s. This is a dramatic improvement.
