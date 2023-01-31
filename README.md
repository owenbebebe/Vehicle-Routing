<h1>Vehicle Routing</h1>

<h2>Description</h2>
This project is trying to solve the famous NP complete vehicle routing problem. Given every vehicle with its capacity and customers' x,y coordinate, and delivery facility x,y coordinate. Every vehicle starts at the delivery facility. The goal is to try to find the least traveling sitance for all of the vehicles to travel to complete its delivery. 
<br />
<h2> Algorithmn - Greedy </h2>
1. Starting from vehicle one, sort the vehicle location to each unvisited location in a 2x2 grid
<br/>
2. With in its capacity travel to the shortest location
<br/>
3. Repeat process one untill it reaches the vehicle capacity than move to the next vehicle
<br/>
4. Add the traveling lengths of each vehicle at the end
<br/>

<h2>Languages and Utilities Used</h2>

- <b>C++</b> 

<h2>Environments Used </h2>

- <b>Windows 10</b> (21H2)


