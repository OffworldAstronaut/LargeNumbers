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
        double interval[2];             // interval for the distribution
        string type = "uniform";        // type of distribution (default is uniform)
        int numValues = 1000;           // number of random values to generate (default is 1000)

        // Parameters for different distributions

        double lambda = 0.0;    // lambda for Poisson distribution
        double mean = 0.0;      // mean for Normal distribution
        double sigma = 0.0;     // standard deviation for Normal distribution

        /**
         * @brief Default constructor for a probability distribution -- uniform distribution
         * 
         * @param interval (Integer) interval that the distribution will cover
         * @param numValues (Integer) number of random values to generate
         */
        probDist(double interval[2], int numValues = 1000) {
            this->interval[0] = interval[0],
            this->interval[1] = interval[1];
            this->numValues = numValues;
        }

        /**
         * @brief Overloaded constructor for a probability distribution -- Poisson distribution
         * 
         * @param interval (Integer) interval that the distribution will cover
         * @param lambda The distribution's lambda parameter
         * @param numValues (Integer) number of random values to generate
         */
        probDist(double interval[2], double lambda, int numValues = 1000) {
            this->interval[0] = interval[0],
            this->interval[1] = interval[1];
            this->lambda = lambda;
            this->type = "poisson";
            this->numValues = numValues;
        }

        /**
         * @brief Overloaded constructor for a probability distribution -- Normal distribution
         * 
         * @param interval (Integer) interval that the distribution will cover
         * @param mean The distribution's mean (mu)
         * @param sigma The distribution's standard deviation (sigma)
         * @param numValues (Integer) number of random values to generate
         */
        probDist(double interval[2], double mean, double sigma, int numValues = 1000) {
            this->interval[0] = interval[0],
            this->interval[1] = interval[1];
            this->mean = mean;
            this->sigma = sigma;
            this->type = "normal";
            this->numValues = numValues;
        }

        void genValues()
        {
            // creates the file name
            string fileName;

            // checks the type of distribution and sets the file name accordingly
            if (this->type == "poisson")
            {
                fileName = format("poisson_lambda_{:.2f}.dat", this->lambda);
            }
            else if (this->type == "normal")
            {
                fileName = format("normal_mean_{:.2f}_sigma_{:.2f}.dat", this->mean, this->sigma);
            }
            else
            {
                fileName = format("uniform_min_{:.2f}_max_{:.2f}.dat", this->interval[0], this->interval[1]);
            }

            // opens the file for writing
            ofstream file(fileName);
            // creates an interface for random number generation
            random_device rd; 
            // seed the mersenne twister generator
            mt19937 gen(rd());

            // check the type of distribution and generate values accordingly
            if (this->type == "poisson")
            {
                // creates a poisson distribution generator
                poisson_distribution<> dis(lambda); // poisson distribution
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
                for (int i = 0; i < numValues; ++i)
                {
                    int value = dis(gen); // generate random value
                    file << value << endl; // write to file
                }
            }
            else
            {
                uniform_int_distribution<> dis(interval[0], interval[1]); // uniform distribution
                for (int i = 0; i < numValues; ++i)
                {
                    int value = dis(gen); // generate random value
                    file << value << endl; // write to file
                }
            }
            // write the expected value to the file and close the file
            file << returnAvg(); // write expected value to file
            file.close();
        }
};

/**
 * @brief Main function to demonstrate the Law of Large Numbers
 * 
 * @return int Exit status of the program
 */
int main(int argc, char *argv[]) {
    // define the interval for the distribution
    double interval[2] = {atof(argv[1]), atof(argv[2])};

    // checks the number of arguments -- the code will only work with the correct number
    if (argc < 4 || argc > 6)
    {
        cerr << "Usage: " << argv[0] << " <min> <max> <n_samples> <lambda/mu> <sigma>" << endl;
        return 1;
    }
    else
    {
        // conditions for distribution-type selection

        // if there's five arguments, it'll be generated a poisson
        if (argc == 5)
        {
            // Poisson distribution
            double lambda = atof(argv[3]);
            int numValues = atoi(argv[4]);
            probDist poissonDist(interval, numValues, lambda);
            poissonDist.genValues();
        }
        // if there's six instead, a normal will be created
        else if (argc == 6)
        {
            // Normal distribution
            double mean = atof(argv[3]);
            double sigma = atof(argv[4]);
            int numValues = atoi(argv[5]);
            probDist normalDist(interval, numValues, mean, sigma);
            normalDist.genValues();
        }
        // the default case, a uniform distribution
        else
        {
            // create a probability distribution object
            int numValues = atoi(argv[3]);
            probDist distribution(interval, numValues);
            // uniform distribution
            distribution.genValues();
        } 
    }
}