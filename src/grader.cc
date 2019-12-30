#include <chrono>
#include "../hdr/argparser.hpp"
#include "../hdr/grader.hpp"



int countStudentLines(EvaluationData &e)
{
    std::streampos jump;
    jump = e.currentFilePosition();

    std::ifstream inFile(e.evaluationFile());
    inFile.seekg(jump);
    int numberOfLines = 0;
    std::string dummyLine("");

    if ( inFile.good() )
    {
        while ( std::getline( inFile, dummyLine ))
        {
            if (! ( dummyLine.empty()) ) { ++numberOfLines; }
        }
    }
    inFile.close();
    return numberOfLines;
}


/* NOTE: Documentation
 * Initialize main routine,
 * */
int main(int argc, char **argv)
{
    // auto start = std::chrono::system_clock::now();
    std::string inputFile("");
    std::string name("");
    ArgParse parser("-s");

    int numargsfilled = parser.parseArguments(argc, argv, inputFile, name);

    if (numargsfilled == 1)
    {
        EvaluationData eval(inputFile);
        eval.loadEvaluationData();
        int numStudents = countStudentLines(eval);
        std::cout << "Number of students: " << numStudents << std::endl;

        //auto end = std::chrono::system_clock::now();
        //std::chrono::duration<double> elapsed_seconds = end-start;
        //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        //std::cout << std::ctime(&end_time);

    }
    else if (numargsfilled == 2)
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "File: " << inputFile << std::endl;
    }
    else
    {
        std::cout << "numargsfilled: " << numargsfilled << std::endl;
        std::cerr << "Something happened" << std::endl;
    }

    exit(EXIT_SUCCESS);
}
