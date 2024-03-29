# Cliff Kelley
# Project 7 - Scheduling Simulation

from __future__ import division
import sys
from copy import deepcopy

# "Constants"
TIME_SLICE = 4
CONTEXT_SWITCH = 0.4

#============================================================================================
# Process Class
#--------------------------------------------------------------------------------------------
class Process(object):
  # Constructor
	def __init__(self, _pid, _arrival, _complete):
		self.pid = _pid
		self.arrival = _arrival
		self.complete = _complete
		self.wait = 0
		self.turnaround = 0
		self.firstProcess = True
	# Overloaded string
	def __str__(self):
		return_string = "\nProcess " + str(self.pid) + ":\n  Arrival Time: " + str(self.arrival) +\
				" - Completion Time: " + str(self.complete) + " - Wait Time: {0:.4g}".format(self.wait) +\
				" - Turnaround: {0:.4g}".format(self.turnaround)
		return return_string
#============================================================================================


#============================================================================================
# Main Function
#--------------------------------------------------------------------------------------------
def main(inList):
	
	print "============================================================================",
	print "\nFirst Come First Serve",
	print "\n----------------------------------------------------------------------------",
	CalcTimes(inList)

	print "\n============================================================================",
	print "\nShortest Job First",
	print "\n----------------------------------------------------------------------------",

	CalcTimes(SJF_Sim(inList))
	
	print "\n============================================================================",
	print "\nShortest Job Remaining",
	print "\n----------------------------------------------------------------------------",

	SJR_Sim(inList)

	print "\n============================================================================",
	print "\nRound Robin",
	print "\n----------------------------------------------------------------------------",

	RR_Sim(inList, False)

	print "\n============================================================================",
	print "\nRound Robin with Context Switch Time",
	print "\n----------------------------------------------------------------------------",

	RR_Sim(inList, True)

#============================================================================================

#============================================================================================
# Calculate Wait and Turnaround Times
#--------------------------------------------------------------------------------------------
def CalcTimes(inList):
	avg_wait = 0
	avg_turn = 0
	total_time = 0
	i = 0
	
	# Calculate wait time and turnaround time for each process
	while i < len(inList):
		inList[i].wait = total_time - inList[i].arrival
		total_time += inList[i].complete
		inList[i].turnaround = total_time - inList[i].arrival
		avg_wait += inList[i].wait
		avg_turn += inList[i].turnaround
		i += 1
	
	# Calculate average wait and turnaround times
	avg_wait /= len(inList)
	avg_turn /= len(inList)

	# Sort list based on process ID
	inList.sort(key=lambda process: process.pid)

	# Print all process and averages
	for each in inList:
		print each,
	print "\n\nAverage Wait: {0:.4g} - Average Turnaround: {1:.4g}".format(avg_wait, avg_turn)
	print "============================================================================",
#============================================================================================

#============================================================================================
# Determine Order of Shortest Job First
#--------------------------------------------------------------------------------------------
def SJF_Sim(inList):
	# Create deep copy of input list
	procList = deepcopy(inList)

	procOrder = []
	readyList = []
	processing = None
	procTime = 0
	time = 0

	# While loop to visit all processes
	finished_all_procs = False
	while not finished_all_procs:
		for each in procList:
			if time >= each.arrival:
				# Move process to ready list when arrived
				readyList.append(each)
				procList.remove(each)
		if procTime == 0 and processing != None:
			# Move finished process to order list
			procOrder.append(processing)
			processing = None
		if processing == None:
			if len(readyList) == 0:
				pass
			else:
				# Find the shortest complete time and start processing it
				max_complete_time = 1000
				for those in readyList:
					if those.complete < max_complete_time:
						max_complete_time = those.complete
						processing = those
				procTime = processing.complete
				readyList.remove(processing)
		
		# Increment time
		time += 1
		# Decrement process complete time
		procTime -= 1

		# Detect if all processes have finished
		if len(procList) == 0 and len(readyList) == 0 and processing == None:
			finished_all_procs = True

	# Return order of processes
	return procOrder
#============================================================================================

#============================================================================================
# Shortest Job Remaining Simulation
#--------------------------------------------------------------------------------------------
def SJR_Sim(inList):
	# Create deep copy of input list
	procList = deepcopy(inList)

	finishedList = []
	readyList = []
	waitList = []
	processing = None
	procTime = 0
	time = 0

	# While loop to visit all processes
	finished_all_procs = False
	while not finished_all_procs:
		for each in procList:
			if time >= each.arrival:
				# Move process to ready list when arrived
				readyList.append(each)
				procList.remove(each)
		if processing != None and procTime == 0:
			# Calculate process turnaround
			processing.turnaround = time - processing.arrival

			# Move finished process to finished list
			finishedList.append(processing)
			processing = None
		if processing == None:
			if len(readyList) == 0 and len(waitList) == 0:
				pass
			else:
				# Combine lists to check through all waiting processes
				checkList = readyList + waitList
				max_complete_time = 1000
				for those in checkList:
					# Find the shortest complete time and start processing it
					if those.complete < max_complete_time:
						max_complete_time = those.complete
						processing = those
				# Set the wait time on the first process cycle
				if processing.firstProcess:
					processing.wait = time - processing.arrival
					processing.firstProcess = False
				procTime = processing.complete
				# Remove the process from either the ready or wait list
				try:
					readyList.remove(processing)
				except:
					pass
				try:
					waitList.remove(processing)
				except:
					pass
		# Every time tick check if there is a shorter process waiting
		for each in readyList:
			if each.complete < processing.complete:
				# Put current process on wait list
				waitList.append(processing)
				processing = each
				# Set the wait time on the first process cycle
				if processing.firstProcess:
					processing.wait = time - processing.arrival
					processing.firstProcess = False
				procTime = processing.complete
				# Remove the process from the ready list
				readyList.remove(processing)

		# Increment time
		time += 1
		# Decrement process complete time
		procTime -= 1

		# Decrement process time if there is one processing
		if processing != None:
			processing.complete -= 1

		# Detect if all processes have finished
		if len(procList) == 0 and len(readyList) == 0 and len(waitList) == 0 and processing == None:
			finished_all_procs = True
	
	# Sort list based on process ID
	finishedList.sort(key=lambda process: process.pid)
	
	i = 0
	avg_wait = 0
	avg_turn = 0
	
	# Iterate through list
	while i < len(finishedList):
		# Calculate times
		avg_wait += finishedList[i].wait
		avg_turn += finishedList[i].turnaround
		# Reset complete time values to original
		finishedList[i].complete = inList[i].complete
		i += 1

	# Calculate averages
	avg_wait /= len(finishedList)
	avg_turn /= len(finishedList)
	
	# Print all process and averages
	for each in finishedList:
		print each,
	print "\n\nAverage Wait: {0:.4g} - Average Turnaround: {1:.4g}".format(avg_wait, avg_turn)
	print "============================================================================",
#============================================================================================

#============================================================================================
# Round Robin Simulation
#--------------------------------------------------------------------------------------------
def RR_Sim(inList, ContextSwitchTime):
	# Create deep copy of input list
	procList = deepcopy(inList)

	finishedList = []
	readyList = []
	processing = None
	procTime = 0
	time = 0

	# While loop to visit all processes
	finished_all_procs = False
	while not finished_all_procs:
		for each in procList:
			if time >= each.arrival:
				# Move process to ready list when arrived
				readyList.append(each)
				procList.remove(each)
		if processing != None and procTime == 0:
			if processing.complete > 0:
				readyList.append(processing)
			else:
				# Calculate process turnaround
				processing.turnaround = time - processing.arrival

				# Move finished process to finished list
				finishedList.append(processing)

			# Add context switch time if desired
			if ContextSwitchTime:
				time += CONTEXT_SWITCH
			processing = None
		if processing == None:
			if len(readyList) == 0:
				pass
			else:
				# Start processing the next item in the queue
				processing = readyList.pop(0)

				# Set the wait time on the first process cycle
				if processing.firstProcess:
					processing.wait = time - processing.arrival
					processing.firstProcess = False
				# Set processing time to the complete time for the process
				# unless the process complete time is greater than the time slice
				# 
				if processing.complete > TIME_SLICE:
					procTime = TIME_SLICE
				else:
					procTime = processing.complete

		# Increment time
		time += 1
		# Decrement process complete time
		procTime -= 1
		
		# Decrement process time if there is one processing
		if processing != None:
			processing.complete -= 1

		# Detect if all processes have finished
		if len(procList) == 0 and len(readyList) == 0 and processing == None:
			finished_all_procs = True
	
	# Sort list based on process ID
	finishedList.sort(key=lambda process: process.pid)
	
	i = 0
	avg_wait = 0
	avg_turn = 0
	
	# Iterate through list
	while i < len(finishedList):
		# Calculate times
		avg_wait += finishedList[i].wait
		avg_turn += finishedList[i].turnaround
		# Reset complete time values to original
		finishedList[i].complete = inList[i].complete
		i += 1

	# Calculate averages
	avg_wait /= len(finishedList)
	avg_turn /= len(finishedList)
	
	# Print all process and averages
	for each in finishedList:
		print each,
	print "\n\nAverage Wait: {0:.4g} - Average Turnaround: {1:.4g}".format(avg_wait, avg_turn)
	print "============================================================================",
#============================================================================================


#============================================================================================
# Terminal interaction and STDIN read
#--------------------------------------------------------------------------------------------
if __name__ == "__main__":
	# Inform user if paramters are used that they are not allowed
	if len(sys.argv) > 1:
		print "Parameters not allowed. Usage - python scheduling.py"
	else:
		# Read STDIN
		with sys.stdin as stdin:
			lines = stdin.readlines()
		
		# Bool to make sure we can continue with program
		canProceed = True
		
		# Parse string data
		processList = []
		for each in lines:
			valList = each.split();
			# Fail if there are not 3 values per line
			if len(valList) != 3:
				print "Incorrect data. Each entry must consist of 3 numbers."
				print "1 - Process ID, 2 - Arrival Time, 3 - Completion time."
				canProceed = False

			# Create Process objects based on input values
			processList.append(Process(int(valList[0]), int(valList[1]), int(valList[2])))

		# Fail if no processes are present
		if len(processList) == 0:
			canProceed = False

		# If all is well, you may protheed
		if canProceed:
			main(processList)
#============================================================================================
