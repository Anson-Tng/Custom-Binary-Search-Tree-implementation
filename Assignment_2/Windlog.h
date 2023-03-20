// Windlog.h

//---------------------------------------------------------------------------------

#ifndef Windlog_h
#define Windlog_h


//---------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include "DATE.H"
#include "time.h"
#include "Bst.h"

//---------------------------------------------------------------------------------

/**
	 * @class Windlog
	 * @brief A class to handle the wind log variables and functions
	 *
	 *
	 * @author Anson Ting
	 * @version 01
	 * @date 27/05/2022 Anson Ting, Started
	 *
	 * @author Anson Ting
	 * @version 02
	 * @date 27/05/2022 Anson Ting, Implement without using vector, FAILED
	 *
	 * @author Anson Ting
	 * @version 03
	 * @date 27/05/2022 Anson Ting, Implemented with Vector.h
	 *
	 * @author Anson Ting
	 * @version 04
	 * @date 29/05/2022 Anson Ting, Remove the Vector.h and used STL::vector
	 *
	 * @author Anson Ting
	 * @version 04
	 * @date 02/06/2022 Anson Ting, Included the Menu #5 function.
	 *
	 * @todo This class is expected to work with function pointers
	 *
	 * @bug All bugs are fixed at the moment.
	 *
	 */

struct windLogStruct        /// Wind log struct
{
    Date nDate;             /// Date class
    Time nTime;             /// Time class
    float nSpeed;           /// Speed
    float nSolarRadiation;  /// Solar radiation
    float nTemperature;     /// Temperature

    windLogStruct() {}      /// Default constructor

    /// Constructor with parameter (Initialization)
    windLogStruct(const Date& date, const Time& time, const float& speed, const float& solarRadiation, const float& temperature):
        nDate(date), nTime(time), nSpeed(speed), nSolarRadiation(solarRadiation/6000), nTemperature(temperature) {}
};

class windlog
{
public:
    windlog() {} /// Default constructor of the class
    ~windlog() {} /// Destructor

    /**
     * @brief  readFiles function used for read a file
     *         that contains multiple file name
     *
     * sort the file names and call readfile() to read in
     * the data.
     *
     * @param  openFileName - Name of the file, const &
     * @return void
     */
    void readFiles(const std::string& openFileName);

    /**
     * @brief  This function used for retrieving data
     *         from the selected file and put into
     *         Vector then into BST.
     *
     *
     *
     * @param  fileName - Name of the file, const &
     * @return void
     */
    void readFile(const std::string& fileName);

    /**
     * @brief  A static void function made for retrieving the the given year and month wind speed data
     *         and store into a vector.
     *
     *
     *
     * @param
     * @return static void
     */
    static void getMonthSpeed(std::map<std::string,std::vector<windLogStruct>>& wlsMap);

    /**
     * @brief  A static void function made for retrieving the the given year and month temperature data
     *         and store into a vector.
     *
     *
     * @param
     * @return static void
     */
    static void getMonthTemp(std::map<std::string,std::vector<windLogStruct>>& wlsMap);

    /**
     * @brief  A static void function made for retrieving the the given year and month Solar radiation data
     *         and store into a vector.
     *
     *
     * @param
     * @return static void
     */
    static void getMonthSolar(std::map<std::string,std::vector<windLogStruct>>& wlsMap);

    /**
     * @brief Retrieve the given year and month Wind Speed data from Map Bst
     *        and calculate the average and standard deviation, then display
     *        the data.
     *
     *
     * @return void
     */
    void findMonthSpeed();

    /**
     * @brief Retrieve the given year temperature data from Map Bst
     *        and calculate the average and standard deviation, then display
     *        the data.
     *
     *
     * @return void
     */
    void findYearTemperature();

    /**
     * @brief Retrieve the given year solar radiation data from Map Bst
     *        and display the sum.
     *
     *
     *
     * @return void
     */
    void findYearSolar();

    /**
     * @brief Calculate all the average and standard deviation
     *        , then write the data into file.
     *
     *
     *
     * @return void
     */
    void printToFile();

    /**
     * @brief Delete the current data and reload the file
     *
     *
     * @return void
     */
    void reload();

    /**
     * @brief Calculate the standard deviation from
     *        the float vector.
     *
     *
     * @param dataList - A vector of float
     * @return float
     */
    float findSd(const std::vector<float>& dataList);

    /**
     * @brief  Convert the float number with only 2 decimal numbers
     *
     *
     * @param  f - a float number
     * @return float
     */
    float round(const float& f) const;
private:
    static std::string inputYearMonth;  /// To store the input data from user and use it for search (called in static void function)
    static std::string inputYear;       /// To store the input data from user and use it for search (called in static void function)
    static std::vector<float> avgS;     /// Store data that retrieved from static void function.
    static std::vector<float> avgSr;    /// Store data that retrieved from static void function.
    static std::vector<float> avgT;     /// Store data that retrieved from static void function.

    Bst<std::map<std::string,std::vector<windLogStruct>>> wlsBst; /// A Map Bst, the map contains the vector of windlogStruct.

    /**
     * @brief This function put as private to
     *        be only used for the internal
     *        use(to finding the position of
     *        wanted data)
     *
     *
     *
     * @param  vName - List(Vector) of header name, hName - The wanted name
     * @return int - the position of wanted name
     */
    int getHeaderIndex(const std::vector<std::string>& vName, const std::string& hName)const;

    /**
     * @brief Convert the number month to the word.
     *        Ex. 1 = January
     *           12 = December
     *
     *
     * @param month - a number month(1-12)
     * @return string
     */
    std::string stringToMonth(const int& month);

    /**
     * @brief   Convert the number month to same number month,
     *          but with the 0 in the front.
     *
     *
     *
     *
     * @param month - a number month(1-12)
     * @return string
     */
    std::string monthToString(const int& month);
};

#endif // Windlog_h
