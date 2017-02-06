/* 
 * File:   main.cpp
 * Author: Piotr Opielski
 *
 * Created on 16 września 2016, 18:33
 */
#include <fstream>
#include <iostream>
#include <cstdlib>



int main() {
    std::cout<<"\n\n\n\n";
    std::cout<<"Welcome in Text RPG Generator\n";
    std::cout<<"Make a game following instructions in README.md file\n";
    std::cout<<"Type in name of the file with game scenario and press ENTER\n";
    std::cout<<"If you still don't know how to do it, type in h and ENTER\n";
    std::string inputFirst;
    while(true){
        std::cin>>inputFirst;
        if(inputFirst=="h") {
            std::cout<<" Check out file example.txt, this is how it should look.\n";
        } else {
            std::ifstream myfile(inputFirst);
            if (myfile.is_open()){
                std::string line;
                bool isIfInLine = 0;
                bool ignoreNonCases = 0;
                int numberOfCases = 0;
                int numberOfCasesInCode = 0;
                int whereIsBracketInLine = 0;
                int whereIsCaseInLine = 0;
                int whereIsReversedBracketInLine = 0;
                int lineLength = 0;
                int whatCaseWeSearch = 0;
                int selectedCase = 0;
                short int answer=0;
                
                while ( getline(myfile,line) ){
                    lineLength = line.length();
                    
                    if(line.find("{") != std::string::npos) {
                        whereIsBracketInLine = line.find("{");
                    } else {
                        whereIsBracketInLine = -1;
                    }
                    if(line.find("case") != std::string::npos) {
                        whereIsCaseInLine = line.find("case");
                    } else {
                        whereIsCaseInLine = -1;
                    }
                    if(line.find("if") != std::string::npos) {
                        isIfInLine=1;
                    } else {
                        isIfInLine=0;
                    }
                    if(line.find("}") != std::string::npos) {
                        whereIsReversedBracketInLine = line.find("}");
                    } else {
                        whereIsReversedBracketInLine = -1;
                    }
                    
                    if(whereIsBracketInLine >= 0 && ignoreNonCases==0) {
                        std::cout<<line.substr(whereIsBracketInLine+1,lineLength-whereIsBracketInLine)<<std::endl;
                    }  
                    if (whereIsCaseInLine == -1 && isIfInLine == 0 && whereIsBracketInLine == -1 && ignoreNonCases==0) {
                        std::cout<<line<<std::endl;
                    }
                    if(whereIsCaseInLine >= 0 && isIfInLine == 0 && whereIsReversedBracketInLine == -1 && ignoreNonCases==0) {
                        std::cout<<line.substr(whereIsCaseInLine+7,lineLength-whereIsCaseInLine-7)<<std::endl;
                        numberOfCases++;
                    }
                    if(whereIsCaseInLine >= 0 && isIfInLine == 0) {
                        numberOfCasesInCode++;
                    }
                    if(whereIsReversedBracketInLine >= 0 && whereIsCaseInLine >= 0 && ignoreNonCases==0) {
                        numberOfCases++;
                        std::cout<<line.substr(whereIsCaseInLine+7,lineLength-whereIsCaseInLine-8)<<std::endl;
                        std::cout<<"Choose your answer"<<std::endl;
                        std::cin>>answer;
                        std::cout<<std::endl<<std::endl<<std::endl;
                        selectedCase = numberOfCasesInCode-numberOfCases+answer;   
                        numberOfCases=0;
                        ignoreNonCases = 1;
                    }
                    if (selectedCase != 0 && isIfInLine == 1 && whereIsCaseInLine >= 0){                        
                        std::string s = std::to_string(selectedCase);
                        if(line.substr(8,1) == s) {
                           std::cout<<line.substr(11, lineLength-9)<<std::endl; 
                           selectedCase = 0;
                           ignoreNonCases = 0;
                        }
                    } 
                    
                }
                std::cout<<"\nThe end.\n";
                break;

            } else {
                std::cout<<"Type name of real file.\n";
            }
        }
    }
    return 0;
}

