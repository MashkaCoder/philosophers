# philosophers
[![Intro](https://img.shields.io/badge/Cursus-philosophers-success?style=for-the-badge&logo=42)](https://github.com/MashkaCoder/philosophers.git)<br>
This project is a solution to the classic diner philosophers problem. <br>

## Cloning <br>
```
git clone https://github.com/MashkaCoder/philosophers.git
cd philosophers
```
## Task 
N silent philosophers sit around a round table, with a plate of spaghetti in front of each philosopher. Forks lie on the table between each pair of nearest philosophers in the mandotary part or in the center of the table in the bonus part.

Every philosopher can either eat or think. Eating is not limited by the amount of spaghetti left - an infinite supply is implied. However, the philosopher can only eat when he is holding two forks - taken from the right and left (in the main part or 2 forks from the center of the table in the mandotary part)

Each philosopher can take the nearest fork (if one is available) or put it down if he is already holding one. Picking up each fork and returning it to the table are separate actions that must be performed one after the other.

The question of the task is to develop a behavior model (parallel algorithm) in which none of the philosophers will starve, that is, they will forever alternate between eating and thinking.

## Make commands

- `make` to compile program. <br>
- `make clean` to clean all object files. <br>
- `make fclean` to remove executable files. <br>
- `make re` to recompile this project.<br>

## Usage <br>

To launch the mandotary part (multithreading). 
```
cd philo
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
To launch the bonus part (multiprocessing).
```
cd philo_bonus
make 
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
## Accepted parameters
-  `number_of_philosophers` The number of philosophers and also the number of forks.
-  `time_to_die`  If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die (in milliseconds).
-  `time_to_eat` The time it takes for a philosopher to eat. During that time, they will need to hold two forks (in milliseconds).
-  `time_to_sleep` The time a philosopher will spend sleeping (in milliseconds).
-  `number_of_times_each_philosopher_must_eat` If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies (optional argument).

## Subject
For more detailed information about the projects, you can read the task
 > [subject](en.subject.pdf)

