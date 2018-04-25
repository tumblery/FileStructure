#Block-oriented Binary File I/O

##Requirment 1
==Read a text file in_student.txt==
***format**
N // number of student record
name,ID,score,age
* char name[20]
* unsigned ID
* float score
* int age

##Requirment 2
==Store it to a **binary file** out_student.dat==
***size of block is 4096**

##Requirment 3
== Given ID, search the student with this ID, print name of the student, and the block number containing this student record.==