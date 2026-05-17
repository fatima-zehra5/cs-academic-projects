# University Timetable Conflict Detector
A C++ console application that detects scheduling conflicts
between university courses using graph theory and relational mathematics.

## Features
- Detects pairwise course clashes
- Builds clash matrix (Relation R)
- Checks symmetry of relation
- Detects 3-way clashes
- Suggests conflict-free timetable sorted by start time
- Input validation for 24-hour format

## How It Works
- User enters course names and time slots
- System builds adjacency/clash matrix
- Reports all clashing pairs and 3-way conflicts
- Verifies if relation is symmetric
- Outputs sorted conflict-free schedule

## Sample Output
====================== University Timetable Conflict Detection===================================================================
Enter number of courses: 3
Course 1: MTH101 9 11
Course 2: CS201 10 12
Course 3: ENG301 13 15
Result: CLASHES DETECTED
MTH101 and CS201 are clashing (overlapping time slots)

## Tech Stack
![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white)

## Concepts Applied
- Graph Theory
- Discrete Mathematics
- Relational Algebra
- Sorting Algorithms
- Input Validation

## Files
- University-Timetable-Conflict-Detector.cpp — Main source code
- University-Timetable-Conflict-Detector.exe — Compiled executable
- DS_PROJECT.pptx — Project presentation
