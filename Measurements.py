import numpy as np
measurements = {}

# if statement that checks if it's yellow blinking time
first_branch = [96,96,96,96,96,96,96,96,96,96,92,100,96,92,96,96,96,92,96,100,96,96,100,96,100,96,96,96,96,100,96,92,96,96,100,96,96,96,100,100,92,96,96,100,104,100,96,96,96,104,100,100,96,92,104,92,96,100,96,104,96,96,96,96,104,96,100,96,96,104,96,96,96,96,104,96,100,96,96,96,100,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,100,96,96,96,96,96,96,96,92,96,96,96,96,92,96,92,96,96,100,104,96,96,96,96,100,96,96,96,96,104,100,96,96,92,100,96,96,96,96,100,96,96,100,96,104,96,100,96,92,104,96,96,96,96,104,96,92,92,96,100,100,96,96,96,100,100,92,96,96,96,96,96,96,96,96,96,100,96,96,96,100,96,92,92,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,100,96,96,96,92,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,104,96,96,96,92,104,96,96,100,100,104,96,96,96,96,100,96,96,92,96,104,96,96,96,96,104,96,96,96,96,100,96,96,96,96,100,92,96,96,96,100,96,92,92,96,100,92,96,92,96,96,100,96,92,96,96,96,96,100,96,100,96,96,96,96,92,96,96,96,96,100,96,96,96,96,96,100,96,96,96,92,96,96,96,96,96,100,96,96,96,96,104,96,96,92,96,104,96,96,96,96,100,96,92,96,96,104,96,96,96,96,100,96,96,92,96,104,100,96,92,92,100,96,96,96,96,100,96,92,96,96,96,96,96,92,92,96,100,96,96,96,96,96,92,100,92,96,96,96,100,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,100,100,96,96,100,100,96,92,96,96,104,96,96,92,96,104,96,96,96,92,104,96,96,92,96,104,96,96,96,96,100,96,96,92,96,104,96,96,92,96,96,96,92,96,96,92,100,96,96,92,92,92,92,96,96,96,96,96,96,96,96,96,92,92,96,100,96,96,96,92,92,96,96,96,96,92,96,100,96,96,96,96,92,96,96,100,108,96,96,96,92,100,96,96,96,96,100,96,96,96,96,100,96,100,96,92,104,96,96,96,96,100,96,96,96,96,104,92,92,96,96,104,96,92,92,96,104,92,96,96,92,92,96,96,96,96,100,92,92,96,96,100,96,96,96,100,100,96,96,96,96,96,96,96,92,92,96,92,96,96,96,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,100,96,96,92,96,104,96,96,96,96,100,96,96,96,96,104,96,96,92,96,100,96,96,96,96,100,92,96,96,96,104,96,92,96,96,100,96,96,96,96,96,96,100,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,92,100,96,96,100,100,92,96,96,96,96,96,96,96,96,100,96,96,92,96,96,96,96,96,100,96,96,92,96,96,96,104,100,92,100,96,104,96,96,92,92,104,96,92,92,96,100,96,96,96,96,100,96,96,96,96,100,96,96,96,96,100,96,96,96,96,100,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96,92,96,96,100,96,96,96,92,96,92,96,92,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,96,100,96,96,92,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,92,100,92,92,96,96,100,92,96,96,96,104,96,96,96,100,104,96,96,92,96,100,96,92,92,96,100,96,96,96,96,104,92,96,96,96,104,96,96,96,96,96,92,96,96,100,96,92,92,96,100,96,96,92,96,96,96,96,96,96,96,96,100,96,96,92,96,96,96,96,96,96,96,92,96,96,96,100,96,96,96,96,96,96,96,96,92,100,92,96,96,96,104,96,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,96,92,100,96,96,100,96,100,96,96,96,92,104,96,96,100,96,104,96,96,96,96,104,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,100,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,92,96,96,96,96,100,96,96,96,96,96,96,96,96,96,104,96,96,96,96,100,96,92,96,96,100,96,96,96,96,104,96,96,96,92,100,92,96,96,96,104,96,96,92,100,104,96,96,100,96,100,96,96,92,96,100,92,96,96,96,96,96,96,96,96,96,96,92,96,96,96,92,96,96,96,96,96,96,100,96,96,92,92,96,92,96,96,96,96,96,96,96,92,96,92,92,96,96,96,96,92,96,96,92,96,96,100,96,96,96,96,100,92,96,96,96,104,96,96,100,96,100,96,96,96,96,104,92,100,96,96,104,100,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,96,96,96,96,96,96,96,92,96,96,100,96,96,96,96,92,92,96,96,92,96,96,96,92,96,96,96,96,100,96,92,96,96,96,96,96,96,92,96,92,96,96,96,96,96,96,96,92,100,96,96,96,96,104,96,100,100,96,104,96,96,96,96,100,96,92,96,96,100,96,96,96,96,100,92,96,96,96,104,96,96,96,96,104,96,96,100,100,100,96,96,96,96,100,96,100,96,96,96,96,96,96,96,96,96,100,100,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,100,96,96,92,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,104,92,92,96,96,100,92,96,96,96,104,96,96,96,100,104,96,100,96,96,100,96,96,96,96,100,96,96,96,96,104,96,96,92,92,100,96,96,92,92,96,96,96,96,96,96,96,96,96,96,92,96,92,96,92,92,96,92,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,92,92,96,96,96,100,96,96,96,96,104,96,96,96,96,104,96,96,96,96,100,96,96,92,96,104,92,100,96,96,100,92,96,96,92,100,96,96,96,96,100,92,96,96,96,100,96,92,96,96,104,100,96,96,100,104,96,96,92,96,104,96,96,96,96,92,100,96,96,100,96,96,96,96,96,96,100,100,96,96,92,96,96,96,96,92,96,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,96,96,96,108,92,96,96,100,100,96,96,92,92,100,96,96,96,96,104,96,96,96,96,100,96,96,96,96,104,92,96,96,96,100,96,96,96,96,100,96,96,96,92,100,92,96,96,96,104,96,96,96,96,100,96,96,96,96,92,96,96,96,96,100,96,96,96,92,96,96,96,96,92,100,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,100,96,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,92,92,104,96,96,96,96,104,92,96,96,96,104,100,96,96,96,104,92,92,96,96,104,92,96,96,96,100,92,96,96,96,92,96,96,96,100,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,92,96,96,96,96,100,96,92,96,96,96,96,96,96,92,96,92,96,96,96,96,96,92,96,96,96,96,96,100,96,96,96,100,104,96,96,96,96,104,96,96,96,96,100,96,96,96,96,100,96,96,96,96,104,96,92,96,96,104,96,96,96,96,100,96,92,100,96,104,92,92,96,96,104,96,96,96,96,96,100,100,96,100,96,92,96,96,96,96,96,96,96,96,96,92,92,96,92,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,100,96,96,100,96,96,96,96,96,96,96,96,96,92,92,96,104,96,96,92,96,100,96,96,96,92,100,92,96,96,96,100,96,96,96,96,104,96,96,100,96,100,96,100,96,96,100,96,96,92,96,100,92,96,96,96,100,96,92,96,96,96,96,96,96,96,92,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,92,96,96,96,96,92,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,104,92,100,96,92,100,96,96,96,96,104,96,96,96,96,100,100,96,96,92,100,96,96,96,96,104,96,96,96,100,100,96,96,96,92,100,96,96,100,96,104,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,100,96,96,100,92,96,96,96,96,96,96,96,96,96,96,96,96,96,100,96,92,96,96,96,96,100,96,96,96,96,96,96,96,96,104,96,96,100,96,100,92,92,100,96,104,100,96,96,92,104,96,92,96,96,104,96,96,96,96,104,96,96,96,96,104,96,96,96,96,100,96,96,96,96,100,96,96,96,96,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96]
#if statement that simulates an emergency vehicle is coming
second_branch = [96,96,92,108,96,96,96,100,100,96,96,96,96,100,96,96,96,96,92,100,96,96,96,96,96,100,96,96,96,96,96,96,96,92,92,96,96,96,92,96,100,96,96,96,100,92,96,96,96,96,96,96,96,96,96,96,92,96,100,96,96,96,96,96,96,96,96,100,96,96,100,100,96,96,104,100,96,96,96,100,96,92,96,96,104,100,96,96,92,100,92,92,96,96,100,96,92,92,96,100,92,96,96,96,104,96,96,96,96,100,96,96,96,92,100,96,96,96,92,96,96,96,96,96,100,96,96,96,96,96,96,92,96,92,96,92,96,96,96,96,96,96,96,100,96,92,96,96,92,96,92,96,96,96,96,96,96,92,96,96,92,92,92,92,96,92,96,96,96,96,104,96,92,96,96,100,96,96,96,96,104,96,96,96,96,100,96,96,96,96,100,96,96,100,96,104,96,96,96,96,100,92,96,100,96,108,96,96,100,100,104,96,96,96,96,104,92,96,96,96,100,96,92,96,96,92,96,96,96,92,100,92,96,92,96,100,96,96,92,96,96,96,96,92,100,96,96,100,96,96,92,96,96,92,92,92,96,96,96,96,96,96,96,96,96,96,92,92,96,96,92,100,92,96,96,96,104,96,100,96,100,100,96,96,96,96,100,96,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,92,96,104,96,96,96,92,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,100,96,96,96,96,96,96,100,96,96,96,96,100,96,96,96,96,96,92,96,96,104,96,96,96,96,104,96,96,96,100,100,96,96,96,96,100,92,96,96,92,104,96,96,96,100,100,92,96,96,96,104,96,96,96,92,92,96,96,96,100,92,92,92,96,96,92,96,96,96,96,92,96,96,92,96,96,96,96,96,96,96,96,96,92,92,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,100,96,96,92,92,100,96,96,96,96,104,96,92,96,96,104,96,96,96,92,100,96,96,100,96,100,96,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,96,92,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,92,96,96,96,92,92,96,96,92,92,96,96,96,96,96,96,96,96,96,100,96,96,96,96,104,96,96,96,100,100,92,92,92,92,100,92,92,92,92,104,96,96,96,96,100,96,96,100,96,104,96,96,92,96,104,96,96,96,96,96,92,96,96,96,100,92,92,96,96,96,96,96,96,96,96,96,96,96,96,96,92,92,96,92,96,96,92,96,96,92,92,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,104,96,92,96,92,100,96,96,96,96,100,96,96,96,100,104,92,92,96,96,100,96,96,96,96,104,92,92,96,96,104,100,92,96,96,104,96,96,96,96,100,100,96,96,96,104,96,96,96,100,96,96,96,96,96,96,96,92,92,96,92,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,104,96,100,96,96,100,96,96,92,96,104,96,96,100,96,100,96,96,92,96,100,92,92,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,96,92,100,96,96,96,96,96,92,96,96,92,96,96,100,96,96,96,96,96,92,92,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,92,96,92,96,96,104,96,100,96,100,100,96,96,96,96,104,92,96,96,96,100,96,96,96,96,104,96,96,92,96,104,100,92,96,96,100,96,96,96,96,100,96,96,96,92,100,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,92,96,92,92,96,96,96,92,96,96,92,92,96,96,96,96,96,96,96,96,92,96,104,96,96,96,96,100,96,96,96,96,104,92,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,96,100,100,92,92,96,96,104,96,96,96,92,92,96,96,96,96,96,100,92,96,96,100,96,96,96,96,96,96,96,100,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,92,96,96,100,96,96,96,96,96,96,96,96,96,92,96,96,96,92,92,96,96,92,100,96,96,100,100,104,96,96,96,96,104,96,96,96,92,100,96,92,96,92,104,96,100,96,96,104,96,96,96,96,100,96,96,96,100,100,92,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,96,100,96,100,92,92,96,96,96,96,96,96,96,92,96,96,96,96,92,96,92,92,96,96,92,96,96,96,96,96,92,96,96,96,104,96,92,96,96,104,96,96,96,100,100,96,100,96,100,104,100,92,96,96,100,92,96,96,92,104,96,96,96,92,104,96,100,92,96,104,96,96,100,96,100,96,96,96,96,104,92,96,96,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,96,92,96,96,96,96,92,92,96,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,104,96,92,96,96,104,96,92,92,92,100,96,96,96,96,100,96,96,96,92,104,96,92,92,96,104,96,96,96,96,104,96,96,96,100,104,96,96,96,96,100,92,96,100,96,96,96,96,96,96,92,100,96,96,96,100,96,100,92,96,100,96,96,96,92,92,96,96,96,100,96,96,92,92,96,96,96,96,96,96,96,92,96,96,96,96,96,96,100,96,96,96,96,96,96,92,96,92,96,96,96,104,96,96,96,96,104,100,96,96,96,104,96,96,96,96,100,96,96,96,96,104,96,96,96,92,100,100,92,96,92,100,96,96,96,96,104,96,96,92,96,104,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,92,92,92,96,96,96,100,96,96,96,92,96,96,96,92,96,100,96,96,92,96,96,96,96,92,96,96,96,96,96,100,96,96,96,96,104,96,92,100,96,104,96,96,96,92,104,96,92,96,96,104,96,92,100,96,100,92,96,92,92,100,92,96,96,96,100,96,96,96,96,100,92,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,92,96,92,96,96,96,92,96,96,96,96,96,96,100,96,92,96,96,96,92,96,96,96,92,96,96,96,92,92,92,96,100,96,96,96,96,92,100,96,96,96,96,104,96,92,92,96,100,96,96,96,96,100,96,96,100,96,100,96,96,96,96,100,92,96,92,96,100,96,96,96,96,104,100,96,96,96,96,96,96,96,96,96,92,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,92,96,96,92,96,96,96,96,96,96,96,92,96,100,96,100,96,96,96,92,92,96,96,96,96,92,92,96,100,96,96,96,92,100,96,96,96,96,100,96,96,96,96,104,96,96,96,96,104,96,92,92,96,100,96,96,96,96,104,92,92,96,96,104,92,96,96,100,100,92,96,96,96,96,96,96,96,96,96,96,96,96,100,96,96,92,96,96,96,96,96,96,96,92,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,92,96,96,104,96,96,96,96,100,96,96,96,96,100,96,100,96,96,104,100,96,96,100,100,96,96,96,92,100,96,92,92,92,104,96,96,96,92,100,96,96,96,96,96,96,96,96,96,96,96,96,96,96,100,100,96,96,96,96,96,96,96,96,100,96,96,96,96,96,96,96,96,92,96,96,92,96,96,96,96,96,96,96,92,92,96,96,96,96,96,96,96,96,96,100,96,96,96,96,100,96,96,96,100,100,92,96,96,96,100,96,92,96,96,100,92,96,92,96,104,96,96,96,96,100,92,92,96,96,104,96,96,96,96,100,96,96,96,96,96,96,96,96,96,96,96,92,92,96,92,96,96,96,96,96,96,96,96,96,96,100,96,96,96,100,96,92,96,96,96,96,96,96,96,92,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,100,96,96,96,96,104,96,92,92,96,104,96,100,96,92,100,92,96,96,96,104,92,96,96,92,100,96,96,96,100,100,96,96,96,96,100,96,100,96,96,100,96,96,96,96,104,96,96,96,96,96,96,96,96,100,92,96,92,96,96,96,96,92,96,92,96,96,96,92,92,92,100,96,100,96,96,96,96,96,96,92,96,96,96,96,96,92,96,96,96,96,96,96,96,92,96,100,96,96,96,96,100,96,96,96,92,104,100,96,96,96,104,96,96,96,96,100,96,96,92,96,100,92,96,96,96,104,96,92,96,96,100,96,96,96,100]
measurements["first_branch"] = np.sum(first_branch)/len(first_branch)
measurements["second_branch"] = np.sum(second_branch)/len(second_branch)

UpdateTimes = [999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 1000002, 999991, 999993, 999994, 999995, 999889 ]
HandleTransitionTimes = [173, 173, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139, 138, 138, 138, 139]
SwitchTime = [7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1]
measurements["UpdateTimes"] = 1000000- (np.sum(UpdateTimes)/len(UpdateTimes))
measurements["HandleTransitionTimes"] = np.sum(HandleTransitionTimes)/len(HandleTransitionTimes)
measurements["SwitchTime"] = np.sum(SwitchTime)/len(SwitchTime)
print(measurements)
