# Snow-Retreat-Grouper

This project was built in part to improve my own programming skills and in part to help solve in interesting grouping problem my church deals with each year when we go on a retreat and have to put people into cabins. Thus, there are sections in this readMe that are typically not present like the "what I learned and what I can improve" sections.

This project is designed to split one large group into multiple small groups based on each individual's preferences. Because this was tailor made for our traditions and the campsite we go to every year, there are a few limitations:
### Limitations
- must split the groups between girls and boys
- each person must select three other people they want to be with
- cabins are hard coded in (sizes, rating)

### Installing
You should be able to clone this directory and then run the __sort.exe__ file that is precompiled. If that does work, you can try using my test executable __a.exe__.
However, if you feel the need to compile it yourself, use the command below for mingw or its equivalent for other compilers:
```
g++ -std=c++17 group.cpp main.cpp output.cpp person.cpp setup.cpp -o sort.exe
```

### Using the Program
First call the program from terminal by going to its directory and then using:
```
./sort.exe
```
or
```
./a.exe
```
depending on which build you're using.

It will prompt you for a nuber of participants. This is the number of people attending minus the counselors.
Next, it will go through a list of cabins and ask you for the number of counselors that are going to be in each cabin.

Then, copy paste a list of participants in the following format:
(FirstName LastName,Grade,Gender(M/F),FirstName LastName,FirstName LastName,FirstName LastName,FirstTime(Y/N))
```
John Smith,10,M,Tom Doe,Mike Senior,Alex Dumas,N
```
Please note that the first and last names need to match across references and persons or else the program will not create the link between the request and the person.

Wait a little bit and then the groups will be output to the output.txt file

### What I learned and description of algorithm
When I first coded this, I still did not know what graph theory was. As such, my program takes a while to run and I doubt it gets the optimal placements. Rather, I think the weights I set within the program over fit my only data set that I was using to test it. 
At the time, I implemented a naive depth-first search that terminated when I ran out of nodes I hadn't run into. I started each search starting with people in the highest grade level and as I entered each node, I added it to an array, creating two long lists of people; one of boys and one of girls. Then, since there might be spaces, I ran a O(n ^ (# of spaces)) algorithm in order to determine where empty spaces would result in the best grouping.

### What I can improve
I can change out the current dfs algorithm for a more efficient approach that uses dfs to identify strongly connected components. Then using greedy heuristics to select components to go into each cabin, using dfs to find maximum spanning trees within the strongly connected components if the groups are too big to fit inside of the cabin. I still don't know what to do for the spaces but I think packing cabins until the least rated one will maximize the score.
