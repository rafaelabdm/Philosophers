<h1 align="center">
	✏️ Philosophers
</h1>

<p align="center"><br>
This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.<br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/rafaelabdm/Minishell?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/rafaelabdm/Minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/rafaelabdm/Minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/rafaelabdm/Minishell?color=green" />
</p>

---

<h2>🍝 About the project</h2>

> _I never thought philosophy would be so deadly_
<p>
We have N philos with N forks, but each philo must use 2 forks to eat, leaving their neighbors without forks. So they have to take turns
on eating, sleeping and thinking. Given the enough time, no one should die.<br>
In this project we discover how to handle threads and mutexes. Threads, unlike processes, share the same memory all the time. So
for a thread to access a variable and change it without messing with the other threads data, we use mutexes. Mutexes are guardians
for all variables that are visited by more than one thread. They only let one thread access it after the other thread is done. But
beware: they slow down the program. So use it wisely. 🤔
<br>
</p>

<p>
💭 <b>ARGUMENTS:</b><br>
◦ <b>number_of_philosophers</b>: The number of philosophers and also the number of forks.<br>
◦ <b>time_to_die (in milliseconds)</b>: If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last
meal or the beginning of the simulation, they die.<br>
◦ <b>time_to_eat (in milliseconds)</b>: The time it takes for a philosopher to eat. During that time, they will need to hold two forks.<br>
◦ <b>time_to_sleep (in milliseconds)</b>: The time a philosopher will spend sleeping.<br>
◦ <b>number_of_times_each_philosopher_must_eat (optional argument)</b>: If all philosophers have eaten at least
number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.<br>
</p>

<h2>💻 COMO USAR:</h2>
<p>
<TT> >$ make<br> </TT><br>
<TT> >$ ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]</TT><br>
<SUB>Do not test with more than 200 philosophers or times with less than 60 miliseconds.</SUB>
</p>
