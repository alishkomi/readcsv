/*
 * @author Alisher Komilov
 */
#include <fstream> //required for opening the file
#include <vector> //for proper vector initialization and use
#include <stdexcept> //for runtime error if no user specified file found
#include <iostream> //for output stream
#include <algorithm> //for sorting vectors to find median
using namespace std;

//Step 2.a
//Function used to find the sum of a vector.
double Sum(vector<double> j) {
	double sum = 0;
	for (int i = 0; i < j.size(); i++) {
		sum = j[i] + sum; //iterates through vector and adds each value to sum
	}
	return sum;
}

//Step 2.b
//Function used to find the mean of a vector.
double Mean(vector<double> k) {
	double mean = Sum(k) / k.size(); //uses sum function and size of vector to find mean
	return mean;
}

//Step 2.c
//Function to find the median of a vector.
double Median(vector<double> l) {
	double median = 0;
	sort(l.begin(), l.end()); //prepares vector by sorting values from lowest to highest

	if (l.size() % 2 != 0) {
		//in a vector with odd number of elements, median is the middle element
		median = l[l.size() / 2];
	}
	else {
		//in a vector with even number of elements, median is the average of two middle elements
		median = (l[(l.size() - 1) / 2] + l[l.size() / 2]) / 2; 
	}
	return median;
}

//Step 2.d
//Function to find the biggest value in a vector.
double Max(vector<double> m) {
	double max = *max_element(m.begin(), m.end()); //finds the largest element
	return max;
}

//Step 2.d
//Function to find the smallest value in a vector.
double Min(vector<double> m) {
	double min = *min_element(m.begin(), m.end()); //finds the smallest element
	return min;
}

//Step 2.e
//Function to calculate the covariance of two vectors.
double Covariance(vector<double> x, vector<double> y) {
	double product_sum = 0;
	vector<double> rm_cov;
	vector<double> medv_cov;

	for (int i = 0; i < x.size(); i++) {
		//the difference between current element and mean is stored in temporary vectors
		rm_cov.push_back(x[i]-Mean(x)); //for x values
		medv_cov.push_back(y[i] - Mean(y)); //for y values
		//while at it, each product of x and y deltas is added to the total sum
		product_sum = product_sum + (rm_cov[i] * medv_cov[i]); 
	}

	//final operation that divides sum by 1 less of number of elements in a vector
	double covar = product_sum / (rm_cov.size() - 1); 
	return covar;
}

//Step 2.f
//Function to calculate the standard deviation of a vector. Used in finding the correlation. 
double StandardDeviation(vector<double> n) {
	double sigma = 0;
	double std_dev = 0;
	//for loop used to find the sum of the squares of the difference between each element and vector mean.
	for (int i = 0; i < n.size(); i++) {
		sigma = sigma + pow((n[i] - Mean(n)), 2);
	}

	/*final operation to calculate the standard deviation of a given vector.
	Finds the square root of the result from dividing sum by 1 less of number of elements.*/
	std_dev = sqrt(sigma / (n.size() - 1)); 
	return std_dev;
}

//Step 2.f
//Function to calculate the correlation coefficient between two vectors.
double Correlation(vector<double> x, vector<double> y) {
	//covariance is divided by the product of standard deviations of two vectors.
	double correlation = Covariance(x, y) / (StandardDeviation(x) * StandardDeviation(y));
	return correlation;
}

//Main program
int main() {
	//Step 1
	string file = "data.csv"; //file name
	ifstream open(file); //opens file
	vector<double> rm; //vector for rm column
	vector<double> medv; //vector for medv column
	
	//if file exists
	if (open.is_open()) {
		double _rm;
		double _medv;
		char delimiter;
		open.ignore(100, '\n'); //ignore the header column
		
		//pass values to _rm and _medv
		while (open >> _rm >> delimiter >> _medv) {
			rm.push_back(_rm); //each value that is read is then pushed to vector rm
			medv.push_back(_medv); //pushed to vector medv
		}
	}
	
	//if file does not exist, throw an error indicating such.
	else throw runtime_error("Error reading file, please enter correct filename or check for it's existence.");

	//Step 3
	//Error checking: as long as the number of rows in columns match
	if (rm.size() == medv.size()) {
		cout << "Data for rm column of the Boston library:" << endl;
		cout << endl;
		cout << "Sum of all elements in rm column: " << Sum(rm) << endl;
		cout << "Mean of rm column: " << Mean(rm) << endl;
		cout << "Median of rm column: " << Median(rm) << endl;
		cout << "Range of rm column: " << "min: "<< Min(rm) << " max: "<< Max(rm) << endl;
		cout << endl;


		cout << "Data for medv column of the Boston library:" << endl;
		cout << endl;
		cout << "Sum of all elements in medv column: " << Sum(medv) << endl;
		cout << "Mean of medv column: " << Mean(medv) << endl;
		cout << "Median of medv column: " << Median(medv) << endl;
		cout << "Range of medv column: " << "min: " << Min(medv) << " max: " << Max(medv) << endl;
		cout << endl;

		cout << "Covariance of columns rm and medv: " << Covariance(rm, medv) << endl;
		cout << "Correlation of columns rm and medv: " << Correlation(rm, medv) << endl;
	}
	//Otherwise print an error message
	else cout << "Program could not be executed. Number of rows in columns are not same" << endl;
	open.close(); //end of program.
	return 0;
}
