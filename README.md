# Student dormitory management system
My first C project in Nanchang University
## Project introduction
This project is a student dormitory management system, in which users can input student information and sort it according to certain criteria. After sorting, the student’s other relevant information can be searched by the student’s dormitory information or vice versa.
## Functional requirements
### (1) Enter student information:
There are two ways to choose, from the keyboard or from the file specified by the system, but both ways need users to input the total number of students, the total number of bedrooms and the total number of classes from the keyboard.
### (2) Sort student information:
It can be sorted by bedroom and bed number order and by class and student number order. After sorting, you can choose whether to output information. If you want to output information, you can choose to output to the screen or a file specified by the system.
### (3) Search student information:
Users can search by bedroom number and the output is the information of the students in the entire bedroom in the order of bed numbers. Searching by class and the system prints out the information of students in the entire class to the screen in the order of student numbers. Search and output the student information by name or student number to screen.
## The key technical problems to be solved by this procedure
## (1) File input and output
## (2) Use of structure
## (3) "Nested" Sorting:
The number of students in each dormitory or class is not necessarily the same during the sorting process. So firstly, sort the dormitory number or class number, and then traverse the preliminary sorting information to record the number of students in each dormitory or class with an array. Then sort each dormitory or class internally, and then use an array to record the number of students to control the loop.
Because the bedroom number and class number are made up of three digits, in order not to waste space, the bedroom number or class number is not used as an array index. The array index is only a natural number that increases from 0. So when reading the number of students stored in the array, it is necessary to control the loop to make the structure array elements that store the target student information correspond to the array elements that store the number of students.
### (4) Search information by class or bedroom number:
Because the information of the entire class or dormitory need to be output, and the number of students in each class or each dormitory is not fixed, it is also necessary to use an array that records the number of students when sorting. And it also needs to control the loop to make the structure array elements storing student information correspond to the array elements that store the number of students.
