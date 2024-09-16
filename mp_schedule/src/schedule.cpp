/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include "schedule.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated courseID is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const string & filename){
    string strfile = file_to_string(filename);
    stringstream ss_strfile(strfile);
    vector<vector<string>> V2D; //dynamically allocated 2D vector of strings
    string row; //curr row
    while(getline(ss_strfile, row))
    {
        vector<string> temp; //temp string vector for all strings in each row
        vector<string> curr;
        split_string(row, ',', curr);
        for (const auto& currl : curr) 
        {
            temp.push_back(trim(currl));
        }
        V2D.push_back(temp); //add back to final V2D
    }
    return V2D;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D& cv, const V2D& student) {
    unordered_map<string, unordered_set<string>> studentToMap = V2DtoUnordered_Map(student); //convert contents of student into a map
    unordered_map<string, unordered_set<string>> cvToMap = V2DtoUnordered_Map(cv); //convert contents of cv into a map
    unordered_map<string, unordered_set<string>> courseRoster_unsorted; //finds similiarities between cvToMap entries and studentToMap entries
    for (const auto& id : cvToMap) 
    {
        const string& course = id.first;
        const unordered_set<string>& students = id.second;
        for (const string& student : students) 
        {
            auto studentMatch = studentToMap.find(student);
            if (studentMatch != studentToMap.end() && studentMatch->second.count(course) > 0) 
            {
                courseRoster_unsorted[course].insert(student);
            }
        }
    }
    vector<vector<string>> courseRoster_sorted;
    for (const auto& row : cv) 
    {
        const string& course = row[0];
        auto match = courseRoster_unsorted.find(course);
        if (match != courseRoster_unsorted.end()) 
        {
            vector<string> course_ID{ trim(course) };
            const unordered_set<string>& students = match->second;
            for (const auto& student : students)
            {
                course_ID.push_back(trim(student));
            }
            courseRoster_sorted.push_back(course_ID);
        }
    }
    vector<vector<string>> courseRoster_sorted_corrected;
    for(size_t i = 0; i < courseRoster_sorted.size(); i++)
    {
        vector<string> curr_course;
        curr_course.push_back(courseRoster_sorted[i][0]);
        curr_course.insert(curr_course.end(), courseRoster_sorted[i].begin()+1, courseRoster_sorted[i].end());
        courseRoster_sorted_corrected.push_back(curr_course);
    }
    return courseRoster_sorted_corrected;
}

unordered_map<string, unordered_set<string>> V2DtoUnordered_Map(const V2D &given) 
{
    unordered_map<string, unordered_set<string>> result;
    for (const auto& row : given) 
    {
        vector<string> entry;
        split_string(row[0], ' ', entry);
        const string& elem = trim(entry[0]);
        for (size_t i = 1; i < row.size(); i++) 
        {
            result[elem].insert(trim(row[i]));
        }
    }
    return result;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The schedule V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only courseID. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D& courses, const vector<string>& timeslots) 
{
    vector<vector<int>> matrix(courses.size(), vector<int>(courses.size(), 0)); //alloc space for a matrix based on 'courses' dims
    unordered_map<string, int> colors{{"", -1}}; //graph coloring
    for (size_t i = 0; i < courses.size(); i++) 
    {
        for (size_t j = i + 1; j < courses.size(); j++)
        {
            if (find_first_of(courses[i].begin() + 1, courses[i].end(), courses[j].begin() + 1, courses[j].end()) != courses[i].end())
            {
                matrix[i][j] = matrix[j][i] = 1;
            }
        }
    }
    if (!backtrackAlgo(courses, timeslots, colors, matrix, 0)) 
    {
        return vector<vector<string>>(1, vector<string>(1, "-1"));
    }
    vector<vector<string>> schedule(timeslots.size());
    for (const auto& course : courses) 
    {
        schedule[colors[course[0]]].push_back(course[0]);
    }
    for (size_t i = 0; i < timeslots.size(); i++) 
    {
        schedule[i].insert(schedule[i].begin(), timeslots[i]);
    }
    return schedule;
}

bool backtrackAlgo(const V2D& courses, const vector<string>& timeslots, unordered_map<string, int>& colors, const vector<vector<int>>& matrix, int curr) 
{
    if (curr == static_cast<int>(courses.size())) 
    {
        return true;
    }
    string currCourse = courses[curr][0];
    unordered_set<int> adjColors;
    for (int i = 0; i < curr; i++) 
    {
        if (matrix[curr][i] && colors[courses[i][0]] != -1) 
        {
            adjColors.insert(colors[courses[i][0]]);
        }
    }
    for (int i = 0; i < static_cast<int>(timeslots.size()); i++) 
    {
        if (adjColors.count(i) == 0) 
        {
            colors[currCourse] = i;
            if (backtrackAlgo(courses, timeslots, colors, matrix, curr+1)) 
            {
                return true;
            }
            colors[currCourse] = -1;
        }
    }
    return false;
}