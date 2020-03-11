/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Liam Brew, Robert Schaedler III
 * Date        : March 2nd, 2020
 * Description : Solves the water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

/*
    @Description
    Represents the state of the water in the jugs. 
        -The integer array jugs contains the contents of each jug. The array is indexed so that index 0 is jug A and 2 is jug C.
        -The string directions contains the directions for that state, e.g. "Pour n gallons from x to y". It is used in the display.
        -The parent pointer points to the previous state that generated this current one.
*/
struct State {
    int jugs[3];
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) : jugs{_a, _b, _c}, directions{_directions}, parent{nullptr} {}

    /*
        @Description
        Represents the contents of the state in tuple form.
    */
    string to_string() {
        ostringstream oss;
        oss << "(" << jugs[0] << ", " << jugs[1] << ", " << jugs[3] << ")";
        return oss.str();
    }

    /*
        @Description
        Determines if the contents of one state are equal to that of another.

        @Parameters
        const State &state: reference to the state that will be compared to the current one
    */
    bool is_equal(const State &state) const {
        for (int i = 0; i < 3; i++) {
            if (jugs[i] != state.jugs[i]) {
                return false;
            }
        }
        return true;
    }
};

// Data fields.
State ***matrix;
const State *jug_sizes;

/* 
    @Description
    Returns the resulting state from a given pour (updates matrix), *nullptr if resulting state already exists. 

    @Parameters
    State *current: the current state 
    char from: the jug that pours the water
    char to: the jug that recieves the water
*/
State *pour(State *current, char from, char to) {
    // Assignments.
    int fromCurr = current->jugs[from - 'A'];
    int toCurr = current->jugs[to - 'A'];
    int toCap = jug_sizes->jugs[to - 'A'];
    int delta;

    if (fromCurr >= toCap - toCurr) {
        // From will have excess after filling to.
        fromCurr = fromCurr - (toCap - toCurr);
        delta = toCap - toCurr;
        toCurr = toCap;
    } else {
        // From will be empty after filling to.
        toCurr = toCurr + fromCurr;
        delta = fromCurr;
        fromCurr = 0;
    }

    int a = current->jugs[0], b = current->jugs[1], c = current->jugs[2];

    // Determining 'from' jug.
    if (from == 'A') {
        a = fromCurr;
    } else if (from == 'B') {
        b = fromCurr;
    } else {
        c = fromCurr;
    }

    // Determining 'to' jug.
    if (to == 'A') {
        a = toCurr;
    } else if (to == 'B') {
        b = toCurr;
    } else {
        c = toCurr;
    }

    if (matrix[a][b] == nullptr) {
        char buff[100];
        if (delta > 1) {
            snprintf(buff, sizeof(buff), "Pour %d gallons from %c to %c. (%d, %d, %d)", delta, from, to, a, b, c);
        } else {
            snprintf(buff, sizeof(buff), "Pour %d gallon from %c to %c. (%d, %d, %d)", delta, from, to, a, b, c);
        }
        string str = buff;

        State *state = new State(a, b, c, str);
        state->parent = current;
        matrix[a][b] = state;
        return state;
    } else {
        return nullptr;
    }
}

/*
    @Description
    Performs a breadth-first search of all states to determine a series of steps that will result in the goal state. 
    Successive states are added to the state matrix to store their values. Makes use of a queue to organize steps. 

    @Parameters
    State *initial_state: pointer to the initial state entered by the user
    const State &goal: reference to the goal state 
*/
State *bfs(State *initial_state, const State &goal) {
    queue<State *> q;
    State *curr = initial_state;
    State *temp;
    q.push(initial_state);
    char from, to;
    while (!q.empty() && !curr->is_equal(goal)) {
        // While the queue is not empty and the current state is not the goal
        curr = q.front();
        q.pop();

        // Ensures that pours take place in the correct order as dictated by the assignment.
        for (int i = 0; i < 3; i++) {
            // C ordering.
            to = 'A' + i;
            for (int j = 2; j >= 0; j--) {
                // B ordering
                from = 'A' + j;
                if (from != to && (temp = pour(curr, from, to)) != nullptr) {
                    q.push(temp);
                    if (temp->is_equal(goal)) {
                        // If the goal has been reached return the new state.
                        return temp;
                    }
                }
            }
        }
    }
    return (q.empty()) ? nullptr : curr;
}

/*
    @Description
    Displays the list of steps taken to achieve the current state by referencing that state's parent until no parent exists.
    Basically backtracking up the state family tree.

    @Parameters
    State *state: pointer to the state who's instruction set will be displayed
*/
void display_path(State *state) {
    if (state->parent != nullptr) {
        display_path(state->parent);
    }
    cout << state->directions << endl;
}

/*
    @Description
    Cleans the state matrix to recycle memory.
*/
void clean_up() {
    for (int i = 0; i < jug_sizes->jugs[0] + 1; i++) {
        for (int j = 0; j < jug_sizes->jugs[1] + 1; j++) {
            if (matrix[i][j] != nullptr) {
                delete matrix[i][j];
            }
        }
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, char *const argv[]) {
    if (argc != 7) {
        printf("Usage: %s <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>\n", argv[0]);
        return 0;
    }

    int vals[6];
    istringstream iss;
    char jug;
    string error_type;

    for (int i = 0; i < 6; i++) {
        jug = 'A' + (i % 3);

        error_type = (i < 3) ? "capacity" : "goal";
        iss.str(argv[i + 1]);
        if (!(iss >> vals[i]) || vals[i] < 0 || (i == 2 && vals[2] == 0)) {
            fprintf(stderr, "Error: Invalid %s '%s' for jug %c.\n", error_type.c_str(), argv[i + 1], jug);
            return 1;
        }
        iss.clear();
    }

    for (int i = 0; i < 6; i++) {
        // Goal cannot exceed capacity of jug i
        jug = 'A' + (i % 3);
        if (i > 2 && vals[i] > vals[i - 3]) {
            fprintf(stderr, "Error: Goal cannot exceed capacity of jug %c.\n", jug);
            return 1;
        }
    }

    // Total gallons in goal state must be equal to the capacity of jug C.
    if (vals[3] + vals[4] + vals[5] != vals[2]) {
        fprintf(stderr, "Error: Total gallons in goal state must be equal to the capacity of jug C.\n");
        return 1;
    }

    State goal(vals[3], vals[4], vals[5], "goal");

    jug_sizes = new State(vals[0], vals[1], vals[2], "jug sizes");

    matrix = new State **[vals[0] + 1];
    for (int i = 0; i < vals[0] + 1; i++) {
        matrix[i] = new State *[vals[1] + 1];
        for (int j = 0; j < vals[1] + 1; j++) {
            matrix[i][j] = nullptr;
        }
    }

    char buff[100];
    snprintf(buff, sizeof(buff), "Initial state. (0, 0, %d)", vals[2]);
    string str = buff;

    State *initial_s = new State(0, 0, vals[2], str);
    State *solution = bfs(initial_s, goal);

    if (solution == nullptr) {
        printf("No solution.");
    } else {
        display_path(solution);
    }

    clean_up();

    delete initial_s;
    delete jug_sizes;

    return 0;
}
