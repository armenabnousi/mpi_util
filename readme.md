#Utility functions for working with MPI library</br>
</br>
This library provides functions that might be useful while writing programs using MPI. I write these functions as I find the need for them. They can be updated and/or appended with new utilites anytime. Most of these functions are `static` and can be used without instantiation of an object of this class.</br>
</br>
**allgatherv_string_container:**</br>
This is used to send the string container within each processor to all other processers.</br>
This function accepts a pointer reference to a container of strings (the container should have begin and end iterators, e.g. std::vector<std::string> or std::set<std::string>). It also accepts a pointer to a string container that will be used for outputing the gathered strings. The third parameter is an optional MPI_Comm communication group. If the third argument is not provided during a call to the function, MPI_COMM_WORLD is used instead.</br> 
The function concatenates the strings on each of the processors and uses a MPI_Allgather call to send all strings to all processors as a char array. Upon reception, each processor extracts the strings from the received char array, inserting them in the output contianer provided by the caller.</br>
```c++
std::vector<std::string> vec(2, "str"); //str, str
std::list<std::string> gathered_strings;
MpiUtil::gatherv_string_container(&vec, &gathered_strings);
```
**gatherv_string_container:**</br>
**This function works within the MPI_COMM_WORLD, it can easily be modified to work within any MPI_Comm as requested by an argument**</br>
This functions accepts a pointer reference to a container object of strings with begin and end iterators such as std::vector<std::string>, std::set<std::string>, etc. (but not containers with binary membership such as std::map, std::unordered_map) and a root processor number. It then sends the strings in the containers in each of the processors in the MPI_COMM_WORLD to the root processor where the gathered strings will be returned as an output argument that the user has provided a pointer reference to it in the function call.
```c++
std::vector<std::string> vec(2, "str"); //str, str
int root_proc_rank = 2;
std::list<std::string> gathered_strings;
MpiUtil::gatherv_string_container(&vec, root_proc_rank, &gathered_strings);
```
The root processor number should be smaller than the number of processors in `MPI_COMM_WORLD`.</br>
</br>
**broadcast_string_container:**</br>
**This function works within the MPI_COMM_WORLD, it can easily be modified to work within any MPI_Comm as requested by an argument**</br>
This function can be used to broadcast a container of strings (with begin and end iterators, such as std::vector(std::string), std::unordered_Set<std::string>, etc.) to all processors in MPI_COMM_WORLD.</br>
It accepts the root processor''s rank and a pointer to the input container as arguments, the broadcasted container can be accessed through the same pointer to the container (input/output argument).
```c++
int rank; 
int root = 0;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
std::vector<std::string> vec;
if (rank == root) vec.push_back("test_string");
MpiUtil::broadcast_string_container(&vec, root);
```
