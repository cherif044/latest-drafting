#include <fstream>
#include <string>
#include "File.h"

using namespace std;

// Implementation of the readFile member function for the string data type of the file class.
// Returns nothing becuase file is an abstract class
template <>
string File<string>::readFile() const
{
    return "";
}

// Implementation of the getFile_x member function for the file class.
// Returns a reference to the file_x object.
template<typename T>
ifstream& File<T>::getFile_x()
{
    return file_x;
}

// Implementation of the getFile_y member function for the file class.
// Returns a reference to the file_y object.
template<typename T>
ifstream& File<T>::getFile_y()
{
    return file_y;
}

// Implementation of the setFile_x member function for the file class.
// Creates and opens the given fileName parameter with file_x object.
template<typename T>
void File<T>::setFile_x(string fileName)
{
    file_x.open(fileName);
}

// Implementation of the setFile_y member function for the file class.
// Creates and opens the given fileName parameter with file_y object.
template<typename T>
void File<T>::setFile_y(string fileName)
{
    file_y.open(fileName);
}
