#!/usr/bin/env python3
# Code by Joseph Kim
# github.com/josephjdkim
import sys
import copy

class State():
    def __init__(self, board, goal, cost = 0):
        self.board = copy.deepcopy(board)
        self.cost = cost

        self.curr_position = [None] * 9
        self.goal_position = [None] * 9

        self.heuristic = self.calculateHeuristic(goal)
        self.total = self.cost + self.heuristic

    def calculateHeuristic(self, goal):
        h = 0
        # map locations of tiles for current state's board and goal state's board
        for i in range(0,3):
            for k in range(0,3):
                self.curr_position[self.board[i][k]] = (i, k)
                self.goal_position[goal[i][k]] = (i, k)
        # calculate manhattan distances for every tile and add it to heuristic val
        for pair in range(0,9):
            h += abs(self.curr_position[pair][0] - self.goal_position[pair][0])
            h += abs(self.curr_position[pair][1] - self.goal_position[pair][1])
        # update total cost: f(n) = g(n) + h(n)
        self.total = self.cost + h
        return h

    def generateMoves(self):
        m = []
        # generate possible moves for blank tile based on whether or not 0 is at edge
        if self.curr_position[0][0] != 0:
            m.append("U")
        if self.curr_position[0][0] != 2:
            m.append("D")
        if self.curr_position[0][1] != 0:
            m.append("L")
        if self.curr_position[0][1] != 2:
            m.append("R")
        # return array of possible moves
        return m

def executeMove(board, move):
    new_board = copy.deepcopy(board)
    zero_i = 0
    zero_k = 0
    swap_val = 0
    # finds location (indices) of 0 tile
    for i in range(0,3):
        for k in range(0,3):
            if board[i][k] == 0:
                zero_i = i
                zero_k = k
    # based on instruction, 0 tile is swapped with another tile, effectively
    # "moving" the tiles
    if move == "U":
        new_board[zero_i][zero_k], new_board[zero_i - 1][zero_k] = new_board[zero_i - 1][zero_k], 0
    elif move == "D":
        new_board[zero_i][zero_k], new_board[zero_i + 1][zero_k] = new_board[zero_i + 1][zero_k], 0
    elif move == "L":
        new_board[zero_i][zero_k], new_board[zero_i][zero_k - 1] = new_board[zero_i][zero_k - 1], 0
    elif move == "R":
        new_board[zero_i][zero_k], new_board[zero_i][zero_k + 1] = new_board[zero_i][zero_k + 1], 0
    return new_board

def aStarTiles(initial_state, goal_board):
    search_queue = [(initial_state, 0, "")]
    nodes_generated = [initial_state]

    while search_queue: # while the search queue still has nodes to search
        # current node/state to be explored is set
        curr_node = search_queue[0]
        curr_state = curr_node[0]
        new_nodes = []

        for move in curr_state.generateMoves():
            path = curr_node[2] + move
            child_board = executeMove(curr_state.board, move)

            # checks to see if board has already been generated
            duplicate = False
            for node in nodes_generated:
                if child_board == node.board:
                    duplicate = True
            if duplicate:
                continue
            # if it is not a duplicate, generate the node
            nn = State(child_board, goal_board, curr_state.cost + 1)
            # track all nodes generated
            nodes_generated.append(nn)

            if nn.board == goal_board: # if goal node is found, return solution
                return [nn.cost, len(nodes_generated), path]

            new_nodes.append((nn, nn.total, path))
        new_nodes.sort(key=lambda takeSecond: takeSecond[1]) # sort newly generated nodes
        search_queue.pop(0) # remove node that was just explored from queue
        # start inserting new nodes into queue based on their total costs
        insert_index = 0
        for n in new_nodes:
            while ((insert_index < len(search_queue)) and (n[1] >= search_queue[insert_index][1])):
                insert_index += 1
            search_queue.insert(insert_index, n)

def outputSolution(initial_board, goal_board, solution, output_name):
    output_file = open(output_name, "w")
    # writes initial board configuration
    for i in initial_board:
        output_file.write(" ".join(str(ii) for ii in i) + "\r\n")
    output_file.write("\n")
    # writes goal board
    for g in goal_board:
        output_file.write(" ".join(str(gg) for gg in g) + "\r\n")
    output_file.write("\n")
    # writes depth, nodes generated, and solution respectively
    output_file.write(str(solution[0]) + "\r\n")
    output_file.write(str(solution[1]) + "\r\n")
    output_file.write(" ".join(solution[2]))
    output_file.close()

def main():
    try:
        input_file = open(sys.argv[1], "r")
    except IndexError:
        print("Usage: ./a-star.py [input file] [optional: output file]")
        sys.exit(1)
    content = input_file.readlines()
    input_file.close()
    output_name = "output.txt"
    try:
        output_name = sys.argv[2]
    except IndexError:
        pass

    # parse input and create two 3x3 matrices (representing boards)
    content = [c.strip().replace(" ", "") for c in content]
    INITIAL, GOAL = [], []
    for i in range(0,3):
        INITIAL.append(list(content[i]))
        for ik in range(0,3):
            INITIAL[-1][ik] = int(INITIAL[-1][ik])
    for g in range(4,7):
        GOAL.append(list(content[g]))
        for gk in range(0,3):
            GOAL[-1][gk] = int(GOAL[-1][gk])

    # create initial and goal states
    INITIAL_STATE = State(INITIAL, GOAL)
    GOAL_STATE = State(GOAL, GOAL)

    solution = aStarTiles(INITIAL_STATE, GOAL)

    outputSolution(INITIAL, GOAL, solution, output_name)

if __name__ == "__main__":
    main()