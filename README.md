# SetIntervals
A set of given positive integers is given.
Arrange these numbers in as few intervals as possible so that a and b can be in one
interval [a, b] if a, b, and all natural numbers between a and b are also in this interval.
Example:
The numbers are 4, 3, 8, 4, 5, 1, 9
The intervals are [1], [3, 5], [8, 9]
Write a C ++ program that reads integers from the keyboard, and
• If the integer is greater than 0, puts it in the set of previously scanned numbers and
prints the intervals.
• If the integer is less than 0, take its absolute value. If this was in the set of previously
scanned numbers, take it out of there. Prints the intervals.
• If the scanned number is 0, the program exits.
The program must store only the boundaries of intervals.
Sample run:
Enter a number: 4
[4]
Enter a number: 3
[3,4]
Enter a number: 8
[3,4], [8]
Enter a number: 4
[3,4], [8]
Enter a number: 5
[3,5], [8]
Enter a number: 1
[1], [3,5], [8]
Enter a number: 9
[1], [3,5], [8,9]
