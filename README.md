# Philosophers

## Overview
### The problem
* The problem involves a group of philosophers sitting at a round table.
* There is a large bowl of spaghetti in the middle of the table, and there are as many forks as philosophers.
* Philosophers alternate between eating, thinking, and sleeping. While eating, they cannot think or sleep; while thinking, they cannot eat or sleep; and while sleeping, they cannot eat or think.
* Philosophers take their right and left forks to eat, one in each hand.
* When a philosopher finishes eating, they put their forks back on the table and start sleeping. Once they wake up, they start thinking again.
* The simulation ends when a philosopher dies of starvation.
* Each philosopher needs to eat and should never starve.
* Philosophers cannot communicate with each other.
* Philosophers are not aware if another philosopher is about to die.

### The rules
* You need to write two programs: one for the mandatory part and another for the bonus part (if you decide to do it)
* Global variables are forbidden
* Both programs must take the following arguments:
    * number_of_philosophers: the number of philosophers and forks
    * time_to_die (in milliseconds): if a philosopher doesn't start eating within this time since their last meal or the start of the simulation, they die
    * time_to_eat (in milliseconds): the time it takes for a philosopher to eat (must hold two forks during this time)
    * time_to_sleep (in milliseconds): the time a philosopher spends sleeping
    * number_of_times_each_philosopher_must_eat (optional): if all philosophers have eaten this many times, the simulation stops; if not specified, the simulation stops when a philosopher dies
* Each philosopher is assigned a number ranging from 1 to number_of_philosophers, and philosopher 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1
* The logs of the program must include state changes of each philosopher formatted as follows:
    * timestamp_in_ms X has taken a fork
    * timestamp_in_ms X is eating
    * timestamp_in_ms X is sleeping
    * timestamp_in_ms X is thinking
    * timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.
* Each displayed state message should not be mixed up with another message
* A message announcing a philosopher's death should be displayed no more than 10 ms after the actual death
* Philosophers should avoid dying.

## Evaluation
#### First submission
30/03/2023  
125%  
