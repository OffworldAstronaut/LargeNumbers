/**
 * @file main.cpp
 * @author Rafael Amorim (rafael.science.amorim@gmail.com)
 * @brief C++ program to aid in the demonstration of the Law of Large Numbers
 * @details This program is designed to illustrate the Law of Large Numbers by simulating a series
 *          of random events and calculating the average of the results. The program will generate
 *          a specified number of random numbers, compute their average and store in a file.
 * @version 0.1
 * @date 2025-07-05
 * 
 * @copyright Copyright (c) 2025 Rafael Amorim
 */

// libraries
#include <iostream>     // standard input/output stream library
#include <vector>       // vector library for dynamic array
#include <fstream>      // file stream library for file operations
#include <random>       // random number generation library
#include <string>       // string library for string manipulation
#include <format>       // format library for formatted output

using namespace std;

// class representing a probability distribution

class probDist {
    private:
        /**
         * @brief Returns the expected value of the distribution
         * 
         * @return The expected value of the distribution
         */
        double returnAvg()
        {
            if (this->type == "uniform")
            {
                return (this->interval[0] + this->interval[1]) / 2.0;
            }
            else if (this->type == "poisson")
            {
                return this->lambda;
            }
            else
            {
                return this->mean;
            }
        }
    public:
        int interval[2];            // interval for the distribution
        string type = "uniform";    // type of distribution (default is uniform)

        // Parameters for different distributions

        double lambda = 0.0;    // lambda for Poisson distribution
        double mean = 0.0;      // mean for Normal distribution
        double sigma = 0.0;     // standard deviation for Normal distribution

        /**
         * @brief Default constructor for a probability distribution -- uniform distribution
         * 
         * @param interval (Integer) interval that the distribution will cover
         */
        probDist(int interval[2]) {
            this->interval[0] = interval[0],
            this->interval[1] = interval[1];
        }

        /**
         * @brief Overloaded constructor for a probability distribution -- Poisson distribution
         * 
         * @param interval (Integer) interval that the distribution will cover
         * @param lambda The distribution's lambda parameter
         */
        probDist(int interval[2], double lambda) {
            this->interval[0] = interval[0],
            this->interval[1] = interval[1];
            this->lambda = lambda;
            this->type = "poisson";
        }

        /**
         * @brief Overloaded constructor for a probability distribution -- Normal distribution
         * 
         * @param interval (Integer) interval that the distribution will cover
         * @param mean The distribution's mean (mu)
         * @param sigma The distribution's standard deviation (sigma)
         */
        probDist(int interval[2], double mean, double sigma) {
            this->interval[0] = interval[0],
            this->interval[1] = interval[1];
            this->mean = mean;
            this->sigma = sigma;
            this->type = "normal";
        }

        void genValues()
        {
            // opens the file for writing
            ofstream file("random_values.dat");

            // creates an interface for random number generation
            random_device rd; 
            // seed the mersenne twister generator
            mt19937 gen(rd());

            // check the type of distribution and generate values accordingly
            if (this->type == "poisson")
            {
                // creates a poisson distribution generator
                poisson_distribution<> dis(lambda); // poisson distribution
                int numValues = 1000; // number of random values to generate
                for (int i = 0; i < numValues; ++i)
                {
                    int value = dis(gen); // generate random value
                    file << value << endl; // write to file
                }
            }
            else if (this->type == "normal")
            {
                // creates a normal distribution generator
                normal_distribution<> dis(mean, sigma); // normal distribution
                int numValues = 1000; // number of random values to generate
                for (int i = 0; i < numValues; ++i)
                {
                    int value = dis(gen); // generate random value
                    file << value << endl; // write to file
                }
            }
            else
            {
                uniform_int_distribution<> dis(interval[0], interval[1]); // uniform distribution
                int numValues = 1000; // number of random values to generate
                for (int i = 0; i < numValues; ++i)
                {
                    int value = dis(gen); // generate random value
                    file << value << endl; // write to file
                }
            }
            // write the expected value to the file and close the file
            file << format("Expected value: {:.2f}", returnAvg()); // write expected value to file
            file.close();
        }
};

/**
 * @brief Main function to demonstrate the Law of Large Numbers
 * 
 * @return int Exit status of the program
 */
int main() {
    // define the interval for the distribution
    int interval[2] = {0, 100};
    // create a probability distribution object
    probDist dist(interval);
    // generate random values based on the distribution
    dist.genValues();
    return 0;
}