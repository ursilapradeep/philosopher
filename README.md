*This project has been created as part of the 42 curriculum by uvadakku.*
# Philosophers

## Description
The Philosophers project is a multi-threaded implementation of the classic "Dining Philosophers Problem," a fundamental synchronization problem in concurrent programming. The project demonstrates thread management, mutual exclusion, and deadlock prevention using POSIX threads and mutexes in C.

### Goal
To create a simulation where multiple philosophers sit around a table with a limited number of forks. Each philosopher alternates between three states: thinking, eating, and sleeping. The challenge is to prevent deadlock and ensure no philosopher starves to death while maintaining thread safety.

### Overview
This implementation:
- Simulates N philosophers sharing N forks using mutexes for synchronization
- Tracks philosopher states and transitions with precise timing
- Prevents resource contention and deadlock through careful thread management
- Provides real-time logging of all philosopher activities
- Handles graceful termination when philosophers achieve their meal quotas or one dies

## Instructions

### Compilation

Build the project using make:

```bash
make
```
This compiles all source files with strict compiler flags (`-Wall -Wextra -Werror`).

### Cleaning

- **Remove object files only:**
  ```bash
  make clean
  ```
- **Remove all build artifacts (objects and executable):**
  ```bash
  make fclean
  ```
- **Rebuild from scratch:**
  ```bash
  make re
  ```
### Execution
Run the program with the following syntax:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

## Parameters
| Parameter | Type | Description |
|-----------|------|-------------|
| `number_of_philosophers` | integer | Number of philosophers and forks (1-200) |
| `time_to_die` | integer | Time in milliseconds before a philosopher dies without eating |
| `time_to_eat` | integer | Time in milliseconds it takes to eat |
| `time_to_sleep` | integer | Time in milliseconds a philosopher sleeps |
| `number_of_times_each_philosopher_must_eat` | integer (optional) | If set, simulation ends when all philosophers have eaten this many times |
## Examples
```bash
# Basic simulation: 5 philosophers, death after 800ms, 200ms to eat/sleep
./philo 5 800 200 200

# With meal requirement: each philosopher must eat at least 7 times
./philo 5 800 200 200 7

# Simpler scenario: 4 philosophers
./philo 4 410 200 200
```
### Output
The program outputs a timestamped log of all philosopher activities:
```
<timestamp_in_ms> <philosopher_id> <action>
```

## Resources

### Classic References

1. **Dining Philosophers Problem - Original Paper**
   - Edsger W. Dijkstra's seminal work on concurrent programming and synchronization
   - Foundational for understanding mutual exclusion and deadlock prevention

2. **POSIX Threads Documentation**
   - https://42-cursus.gitbook.io/guide/3-rank-03/philosophers
   - (https://man7.org/linux/man-pages/man3/pthread_create.3.html) - Thread creation
   - (https://man7.org/linux/man-pages/man3/pthread_mutex_init.3.html) - Mutex operations

3. **42 School Philosophers Project Specifications**
   - Official 42 project requirements and evaluation criteria
   - Provides context for implementation constraints and expectations

### AI Usage

**Note:** This project was created with AI assistance for documentation and guidance only. The actual C implementation was developed through the 42 curriculum learning process.

AI was used for:
- **Documentation & README creation**: Generating this README.md file with proper structure and formatting
- **Code explanation**: Explaining thread synchronization concepts and POSIX pthread API usage
- **Debugging assistance**: Identifying potential race conditions and mutex deadlock scenarios
- **Reference gathering**: Organizing classic resources and documentation links related to the dining philosophers problem

The actual implementation logic, including thread creation, mutex management, state synchronization, and the core philosopher simulation algorithm, was developed through hands-on coding and debugging according to 42 curriculum standards.

## Project Structure

```
Philosophers/
├── Makefile                  # Build configuration
├── README.md                 # This file
├── includes/
│   └── philo.h              # Main header with data structures
└── src/
    ├── main.c               # Program entry point and argument validation
    ├── prep_dining.c        # Table initialization and thread creation
    ├── routine.c            # Main philosopher thread loop
    ├── actions.c            # Philosopher actions (eat, sleep, think, take fork)
    ├── handle_args.c        # Command-line argument parsing
    ├── time.c               # Time utilities (gettimeofday wrapper)
    ├── cleanup.c            # Resource deallocation and thread joining
    └── utils.c              # Helper functions
```

## Key Implementation Details

### Thread Safety
- All shared resources (forks, philosopher state) are protected by mutexes
- Each fork is represented by a mutex to enforce mutual exclusion

### Deadlock Prevention
- Careful mutex acquisition order to prevent circular wait conditions
- Philosopher threads respect a consistent locking strategy
- Implementation may include timeout mechanisms to detect philosopher death

### Timing

- Millisecond precision using `gettimeofday()`
- Relative timestamps from program start
- Accurate state transition timing

## Memory Management

- All dynamically allocated memory is freed upon program termination
- No memory leaks (valgrind clean)
- Proper pthread cleanup with `pthread_join()` before exit