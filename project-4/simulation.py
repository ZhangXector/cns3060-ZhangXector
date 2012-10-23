#!/usr/bin/python

import sys
COLUMN_WIDTH = 30

def main():

	# Current Track (Initially set to 15)
	current_track = 15
	
	# List of tracks
	all_tracks = []
	
	# Check that we don't have a negative number (while still allowing empty string)
	while current_track == '' or int(current_track) >= 0:
		# If it is an empty string, assume the user made a mistake, ask for number
		if current_track == '':
			print 'Please enter a number.'
		else:
			# Try to append the int value to the list
			try:
				all_tracks.append(int(current_track))
			# Break if value entered was not an int
			except:
				print 'Invalid track number: {0}'.format(current_track)
				break
		
		# Get user input
		current_track = raw_input()
	# Print the track number list
	print '\nTrack number list: {0}'.format(all_tracks)

	print '{:=<{width}}\n'.format('=', width = COLUMN_WIDTH * 2)
	
	FCFS(all_tracks)
	SSTF(all_tracks)
	SCAN(all_tracks)

def FCFS(tracks):
	total_tracks = 0
	traversals = []

	i = 0
	while i < len(tracks) - 1:
		traverse = abs(tracks[i] - (tracks[i + 1]))
		traversals.append((tracks[i], tracks[i + 1], traverse))
		total_tracks += traverse
		i += 1

	PrintTable('First Come First Served', traversals, total_tracks)
	
def SSTF(tracks):
	total_tracks = 0
	traversals = []

	# Call FindClosestRecursive with the first item (the current track) and the 
	# list with that first value removed (so as not to check) itself
	FindClosestRecursive(tracks[0], list(tracks[1:]), traversals)	
	
	# Calculate the total tracks as the sum of all the distances in traversals
	total_tracks = sum(list(z for (x, y, z) in traversals))

	PrintTable('Shortest Seek Time First', traversals, total_tracks)

def FindClosestRecursive(origin, tracks, traversals):
	# Variables for storing the closest number and min distance
	closest_num = 0
	min_distance = 1000

	# Iterate through each remaining track
	for each in tracks:
		# If the distance is lower than what's currently the lowest
		if abs(origin - each) < min_distance:
			# Set the min distance to that value
			min_distance = abs(origin - each)
			# Set the closest number to that track
			closest_num = each

	# Append the origin, closest track, and the distance between to traversals
	traversals.append((origin, closest_num, min_distance))

	# If there are still more values in tracks, call FindClosestRecursive with a new
	# list that removes the new closest track number
	if len(tracks) > 1:
		newList = list(x for x in tracks if x != closest_num)
		FindClosestRecursive(closest_num, newList, traversals)

def SCAN(tracks):
	total_tracks = 0
	traversals = []
	closest_num = 0
	min_distance = 1000

	for i in range(1, len(tracks)):
		if abs(tracks[0] - tracks[i]) < min_distance:
			min_distance = abs(tracks[0] - tracks[i])
			closest_num = tracks[i]
	sorted_tracks = sorted(tracks)
	if closest_num < tracks[0]:
		# Going down
		i = sorted_tracks.index(tracks[0])
		while i > 0:
			traversals.append((sorted_tracks[i], sorted_tracks[i - 1], abs(sorted_tracks[i] - sorted_tracks[i - 1])))
			i -= 1
		j = sorted_tracks.index(tracks[0]) + 1
		traversals.append((sorted_tracks[i], sorted_tracks[j], abs(sorted_tracks[i] - sorted_tracks[j])))
		while j < len(sorted_tracks) - 1:
			traversals.append((sorted_tracks[j], sorted_tracks[j + 1], abs(sorted_tracks[j] - sorted_tracks[j + 1])))
			j += 1
	else:
		# Going up
		j = sorted_tracks.index(tracks[0])
		while j < len(sorted_tracks) - 1:
			traversals.append((sorted_tracks[j], sorted_tracks[j + 1], abs(sorted_tracks[j] - sorted_tracks[j + 1])))	
			j += 1
		i = sorted_tracks.index(tracks[0]) - 1
		traversals.append((sorted_tracks[j], sorted_tracks[i], abs(sorted_tracks[j] - sorted_tracks[i])))
		while i > 0:
			traversals.append((sorted_tracks[i], sorted_tracks[i - 1], abs(sorted_tracks[i] - sorted_tracks[i - 1])))
			i -= 1
	
	# Calculate the total tracks as the sum of all the distances in traversals
	total_tracks = sum(list(z for (x, y, z) in traversals))

	PrintTable('Scan-Look (Elevator)', traversals, total_tracks)

def PrintTable(type, traversals, total_tracks):
	print type
	print '{0:{width}}{1:{width}}'.format('Head Movement', 'Tracks Traversed', width = COLUMN_WIDTH)
	
	for (x, y, z) in traversals:
		print '{0:<{width}}{1:<{width}}'.format('Tracks {0} - {1}'.format(x, y), z, width = COLUMN_WIDTH)

	print
	print '{0:{width}}{1:<{width}}\n'.format('Total Tracks Traversed', total_tracks, width = COLUMN_WIDTH)
	print '{:=<{width}}\n'.format('=', width = COLUMN_WIDTH * 2)

if __name__ == '__main__':
	if len(sys.argv) > 1:
		print 'Simulation takes no arguments. Usage: \'python simulation.py\''
	else:
		print 'Please enter track numbers to seek for starting from track 15. Follow each entry\nwith the <Enter> key. (Any negative number executes simulation): '
		main()
