# Philosophers

## Project overview

**Philosophers** is a project about solving the classic [Dining Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) problem in C. Originally formulated in 1965 by Edsger Dijkstra, the problem illustrate synchronization issues and requires the used of concurrent algorithm. Here is an overview of the problem:

- **Scenario**
    - There is X amount of philosophers seated at a round table.
    - They can either eat, think, or sleep.
- **Actions**
    - **Eating**: Requires two forks (one from the left and one from the right).
    - **Thinking**: Does not require forks.
    - **Sleeping**: Occurs after eating, and no forks are needed.
- **Rules and Constraints**
    - **Forks**: There are as many forks as there are philosophers. Each philosopher needs two forks to eat.
    - **Routine**: Philosophers alternate between eating, thinking, and sleeping. They cannot perform more than one activity at a time.
    - **Starvation**: The simulation ends if a philosopher dies of starvation. Therefore, it is crucial to ensure that each philosopher gets a chance to eat to prevent starvation.
- **Considerations and tips**
    - **Concurrency**: Since philosophers do not communicate with each other and do not know if another is starving, managing access to forks is critical to avoid deadlock (where no philosopher can eat because they are all waiting for forks).
    - **Synchronization mechanism**: mutexes are used to manage fork access.

This is actually a problem of operating system which deals with resource allocation: philosophers represent `processes` and the forks represent `resources` that has to be shared between processes in a synchronized manner without violating any rules.

**Table of contents**


## Installation

### What do I need to install the Philosophers?

To successfully install and run this project, you should have: 

- **Unix-like Operation System**, such as Linux or macOS.
- **C compiler** (e.g. gcc). You can install it using your package manager if not already available.
- **Make Utility**. Make sure `make` is installed to run the `Makefile` provided for compilation.

### How to get and compile the program?

1. **Clone the repository and navigate to the project directory:** First, you need to clone the repository to your local machine and change into the project directory:

```bash
git clone git@github.com:hlntzg/Philosophers.git && cd Philosophers/philo
```

2. **Compile the program:** `Makefile` is included and it automatically handle the compilation for you. After compiling, you will get the executable `<ProjectName>`. To compile the program, run:

```bash
make
```

3. **Clean and recompile:** 
- If you want to remove temporary files created during compilation, you can run: `make clean`
- If you want to clean up everything, including the executable and object files, please run: `make fclean`
- If you want to force a full recompilation by cleaning up everything and then recompiling, you can use: `make re`

## Operating instructions

### How can I execute the program?

Run `./philo` with the following arguments:

- `number_of_philosophers` - for the total number of philosophers (and forks!) of the simulation.
- `time_to_die` - for the time it takes for a philosopher to die if the philosopher didn’t start eating this amount of time in milliseconds since the beginning of their last meal or the beginning of the simulation.
- `time_to_eat` - for the time it takes for a philosopher to eat in milliseconds.
- `time_to_sleep` - for the time it takes for a philosopher to sleep in milliseconds.
- `number_of_meals` (optional) - for the meals each philosopher must have eaten for the end of the simulation.

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]   
```

This program accepts only positive integer values as arguments, with or without plus sign. In case of wrong number of arguments of format, the program return an error message specifying the issue. Any change of a philosopher’s status should display the following:

>
> timestamp_in_ms X has taken a fork
> timestamp_in_ms X is eating
> timestamp_in_ms X is sleeping
> timestamp_in_ms X is thinking
> timestamp_in_ms X died
> 

The simulation will stop when one philosopher died or the all the `number_of_philosophers` have eaten at least `number_of_meals` times. Otherwise, it will keep running until you interrupt this process. Use `Ctrl + C` to send an interrupt signal to the process.

### Examples:

```bash
./philo 4 310 200 200
```

## Project structure

Here is an overview of the project's directory structure. This project is updated.

## Project status

This project was submitted to peer-evaluations and completed with 100%. 

## General information

### Acknowledgments

- [Philosopher Visualizer](https://nafuka11.github.io/philosophers-visualizer/) - Used for visualizer the output. It’s a simple web visualizer for the program logs.

### Lessons learned from the project

- Basics of multithreading and synchronization in C using pthreads.
- Understanding of concurrent programming concepts such as mutexes, data races conditions, and deadlock prevention.

### Permissions and disclaimer

Feel free to use, modify, and share this code. Please provide appropriate attribution when using or modifying it. This project is for educational purposes only. It may contain bugs or incomplete features.

### License

This project is licensed under either the MIT License or License Personal (your choice). 

- Under the MIT License: see the [LICENSE-MIT](LICENSE-MIT) file for details.
- Under the Personal License: see the [LICENSE-PERSONAL](LICENSE-PERSONAL) file for details.

### Copyright and contact information

- Copyright (c) 2024 Helena Utzig.
- If you have any problems, questions, ideas or suggestions, please reach me out by helenautzig@gmail.com. For more contact options, see: https://github.com/hlntzg.
- Contact into the 42Network: https://profile.intra.42.fr/users/hutzig.
