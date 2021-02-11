# mini-matricula-web
University project that simulates a system of an university that manages its students info. Written using C language, this project simulates an university management system that can make a CRUD of a student and make a a CRUD of this student's courses. It's also written in Portuguese.

### Initial menu:

  In the initial menu, we'll have these options:
  
  1. Register new student:  
  Option that registers a student, asking for its first and last name, its enrollment number and its email. After finishing the student's registration sucessfully, this students registration will have an index depending how many students there are in the system.
  
  
  2. List all the students:  
  Option that list all the students registered in this system by index.
  
  
  3. __Visualize a student__:   
  Option that search for a student by name, by index or by email. If the user wants to visualize a student using its name, the program will ask for the first name of the student, and the user can either put the whole first name or put a part of the name. If there are any matches, the user can use the index to choose the student he/she wants to visualize.
  
  
  4. Edit student register:  
  Option that can change any student registration info, after searching it by name, email or index. 
  
  
  5. Delete a student register:  
  Option that will erase a student's register, after searching it by name, email or index.
  
  
  6. Exit the program:  
  Option that closes the program.
  

### Student menu:   

  After finding the student using the visualize(third) option, the user is redirected into a new menu, in which he/she will make changes to this student's courses info. We'll have these options:

  1. Register new course:  
  Option that register a new course to the student's history. A course will have a name and a grade. According to the grade putted, the student will recieve a certain mention in this course.  
  If the student gets an/a:
  
  * 0.0 : SR mention.
  * 0.1 to 2.9 : II mention.
  * 3.0 to 4.9 : MI mention.
  * 5.0 to 6.9 : MM mention.
  * 7.0 to 8.4 : MS mention.
  * 8.5 to 10.0: SS mention.
  * -1 : TR mention. (which means that this student locked the course).
    
   Observation: The student will only be approved if he/she gets an MM >= mention.  
  
  
  2. List all courses:  
  Option that lists all the courses the student have participated and its grades on them.
  
  
  3. Edit a course:
  Option that can edit a course of the student, changing the name or the grade in it. The course can be found using its name or index.  
  
  
  4. Delete a course:  
  Option that deletes a course from the students record. The course can be found using its name or index.  
  
  
  5. Filter course by mention:  
  Option that will filter the courses that the student participated and put each of them in its respective mention. Also counts the quantity of each mention.  
  
  
  6. Full report of the student:
  Option that shows how many courses the student has been approved and reproved, and the quantity of the courses participated.
  
  7. Go back to the initial menu:
  Option that goes back to the main menu.
