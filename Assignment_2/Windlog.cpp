#include "Windlog.h"

std::string windlog::inputYearMonth = "";                   /// Private static from windlog.h
std::string windlog::inputYear = "";                        /// Private static from windlog.h
std::vector<float> windlog::avgS = std::vector<float>();    /// Private static from windlog.h
std::vector<float> windlog::avgSr = std::vector<float>();   /// Private static from windlog.h
std::vector<float> windlog::avgT = std::vector<float>();    /// Private static from windlog.h



inline operator < (const std::map<std::string,std::vector<windLogStruct>>& lhs, const std::map<std::string,std::vector<windLogStruct>>& rhs )
{
    /// Compare the first date that stored in the vector.
    int lint = stoi(lhs.begin()->first);
    int rint = stoi(rhs.begin()->first);
    return lint < rint;
}

inline operator == (const std::map<std::string,std::vector<windLogStruct>>& lhs, const std::map<std::string,std::vector<windLogStruct>>& rhs )
{
    size_t counter =0;
    for(auto i = lhs.begin(); i != lhs.end(); i++)
    {
        for(auto j = rhs.begin(); j !=rhs.end(); j++)
        {
            if(i->first == j->first)
            {
                counter++;
            }
        }
    }

    /// Only return true if the entire vector is the same to the right hand side(rhs).
    if(counter == rhs.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int windlog::getHeaderIndex(const std::vector<std::string>& vName, const std::string& hName)const
{
    /// Find the location of the header.
    int index = 0;
    for(size_t i=0; i<vName.size(); i++)
    {
        if(vName[i] == hName)
        {
            index = i;
        }
    }
    return index;
}

void windlog::readFiles(const std::string& openFileName)
{
    /// Reads multiple files
    const std::string folderName = "data/";
    std::string fileName;
    std::vector<std::string> fileNameList;
    std::ifstream openFile;
    openFile.open(openFileName);

    if(openFile.is_open())
    {
        while(openFile.good() && getline(openFile,fileName,'\n'))
        {
            fileNameList.push_back(folderName + fileName);
        }

        for(size_t i=0; i<fileNameList.size(); i++)
        {
            readFile(fileNameList[i]);
        }
    }
    else
    {
        std::cout << "FILE CAN'T BE READ";
    }
}

std::string windlog::monthToString(const int& month)
{
    /// Convert the month to string with 0 at front.
    switch(month)
    {
    case 1:
        return "01";
        break;
    case 2:
        return "02";
        break;
    case 3:
        return "03";
        break;
    case 4:
        return "04";
        break;
    case 5:
        return "05";
        break;
    case 6:
        return "06";
        break;
    case 7:
        return "07";
        break;
    case 8:
        return "08";
        break;
    case 9:
        return "09";
        break;
    case 10:
        return "10";
        break;
    case 11:
        return "11";
        break;
    case 12:
        return "12";
        break;
    }
    return "Fault";
}

std::string windlog::stringToMonth(const int& month)
{
    /// Convert the month to word.
    switch(month)
    {
    case 1:
        return "January";
        break;
    case 2:
        return "February";
        break;
    case 3:
        return "March";
        break;
    case 4:
        return "April";
        break;
    case 5:
        return "May";
        break;
    case 6:
        return "June";
        break;
    case 7:
        return "July";
        break;
    case 8:
        return "August";
        break;
    case 9:
        return "September";
        break;
    case 10:
        return "October";
        break;
    case 11:
        return "November";
        break;
    case 12:
        return "December";
        break;
    }
    return "Fault";
}

void windlog::readFile(const std::string& fileName)
{
    ///Read file
    std::cout << "Loaded file: "+ fileName + '\n';
    windLogStruct wls;
    Date d;
    Time t;
    Date currentDate;
    bool isFirst = true;

    std::string sDay, sMonth, sYear, sHour, sMinute, sSpeed, sSolar, sTemperature;
    std::string hder,headerList, holder;
    int day, month, year, hour, minute;
    float speed, solar, temperature;

    std::vector<std::string> header;
    std::vector<std::string> column;
    std::map<std::string,std::vector<windLogStruct>> wlsMap;
    std::vector<windLogStruct> wlsVec;

    std::ifstream newFile;
    newFile.open(fileName);
    if(newFile.is_open())
    {
        ///===============================================================
        /// Header list
        getline(newFile, headerList, '\n');

        std::istringstream headerStream(headerList);
        while(headerStream.good() && getline(headerStream,hder,','))
        {
            header.push_back(hder);
        }

        int wastPos = getHeaderIndex(header, "WAST");
        int sPos = getHeaderIndex(header, "S");
        int srPos = getHeaderIndex(header, "SR");
        int tPos = getHeaderIndex(header, "T");


        headerStream.clear();
        ///==================================================================

        while(newFile.good() && getline(newFile,holder, ','))
        {
            /// Put a column of data into vector
            column.push_back(holder);

            for(size_t i=0; i<header.size()-2; i++)
            {
                getline(newFile,holder,',');
                column.push_back(holder);
            }
            getline(newFile, holder, '\n');
            column.push_back(holder);

            std::string dateNtime = column[wastPos];
            std::istringstream dateNtimeStream(dateNtime);
            if(!dateNtimeStream.str().empty())
            {
                /// Split the data with getline
                getline(dateNtimeStream, sDay, '/');
                getline(dateNtimeStream, sMonth, '/');
                getline(dateNtimeStream, sYear, ' ');
                getline(dateNtimeStream, sHour, ':');
                getline(dateNtimeStream, sMinute, ',');

                /// String to int
                day = stoi(sDay);
                month = stoi(sMonth);
                year = stoi(sYear);
                hour = stoi(sHour);
                minute = stoi(sMinute);

                /// Speed to float
                if(column[sPos] == "" || column[sPos] == "N/A")
                {
                    speed = 0;
                }
                else
                {
                    speed = stof(column[sPos]);
                }

                /// Solar radiation to float
                if(column[srPos] == "" || column[srPos] == "N/A")
                {
                    solar = 0;
                }
                else
                {
                    solar = stof(column[srPos]);
                }

                /// temperature to float
                if(column[tPos] == "" || column[tPos] == "N/A")
                {
                    temperature = 0;
                }
                else
                {
                    temperature = stof(column[tPos]);
                }

                d = Date(day, month, year);

                if(isFirst)
                {
                    currentDate = d;
                    isFirst = false;
                }

                /// If still same year and month, add into current vector
                if(d.GetYear() == currentDate.GetYear() && d.GetMonth() == currentDate.GetMonth())
                {
                    t = Time(hour, minute);
                    wls = windLogStruct(d, t, speed, solar, temperature);
                    wlsVec.push_back(wls);
                }

                /// If entered to new month, insert current month to the stl::map and start over vector
                if(d.GetYear() == currentDate.GetYear() && d.GetMonth() != currentDate.GetMonth())
                {
                    wlsMap.insert(std::pair<std::string,std::vector<windLogStruct>>(std::to_string(currentDate.GetYear())+ monthToString(currentDate.GetMonth()), wlsVec));
                    wlsVec.clear();

                    currentDate = d;
                    t = Time(hour, minute);
                    wls = windLogStruct(d, t, speed, solar, temperature);

                    wlsVec.push_back(wls);
                }

                /// If entered to new year, insert the map into bst and start over the vector and map.
                if(d.GetYear() != currentDate.GetYear())
                {
                    wlsMap.insert(std::pair<std::string,std::vector<windLogStruct>>(std::to_string(currentDate.GetYear())+ monthToString(currentDate.GetMonth()), wlsVec));
                    wlsBst.Insert(wlsMap);
                    wlsVec.clear();
                    wlsMap.clear();

                    currentDate = d;
                    t = Time(hour, minute);
                    wls = windLogStruct(d, t, speed, solar, temperature);

                    wlsVec.push_back(wls);
                }
                dateNtimeStream.clear();
            }
            column.clear();
        }
        ///
        wlsMap.insert(std::pair<std::string,std::vector<windLogStruct>>(std::to_string(currentDate.GetYear())+ monthToString(currentDate.GetMonth()), wlsVec));
        wlsVec.clear();
        wlsBst.Insert(wlsMap);
    }
    else
    {
        std::cout << "\nSomething's wrong.\n";
    }
    newFile.close();
}

void windlog::getMonthSpeed(std::map<std::string,std::vector<windLogStruct>>& wlsMap)
{
    /// Retrieve all data with the year and month that user asked for to the vector
    if(wlsMap.count(inputYearMonth))
    {
        for(size_t i=0; i<wlsMap.find(inputYearMonth)->second.size(); i++)
        {
            avgS.push_back(wlsMap.find(inputYearMonth)->second[i].nSpeed);
        }
    }
}

void windlog::getMonthTemp(std::map<std::string,std::vector<windLogStruct>>& wlsMap)
{
    /// Retrieve all data with the year and month that user asked for to the vector
    if(wlsMap.count(inputYearMonth))
    {
        for(size_t i=0; i<wlsMap.find(inputYearMonth)->second.size(); i++)
        {
            avgT.push_back(wlsMap.find(inputYearMonth)->second[i].nTemperature);
        }
    }
}

void windlog::getMonthSolar(std::map<std::string,std::vector<windLogStruct>>& wlsMap)
{
    /// Retrieve all data with the year and month that user asked for to the vector
    if(wlsMap.count(inputYearMonth))
    {
        for(size_t i=0; i<wlsMap.find(inputYearMonth)->second.size(); i++)
        {
            avgSr.push_back(wlsMap.find(inputYearMonth)->second[i].nSolarRadiation);
        }
    }
}

float windlog::findSd(const std::vector<float>& dataList)
{
    /// Standard deviation calculation
    float mean, sum;

    for(size_t i=0; i<dataList.size(); i++)
    {
        mean += dataList[i];
    }
    mean = mean/dataList.size();

    for(size_t i=0; i<dataList.size(); i++)
    {
        sum += (dataList[i] - mean) * (dataList[i] - mean);
    }

    return round(sqrt (sum / (dataList.size()-1)));
}

float windlog::round(const float& f) const
{
    /// Put all the float numbers with 2 decimal numbers
    return ((float)((int)(f * 10 + 0.5))) / 10.0;
}

void windlog::findMonthSpeed()
{
    /// User input year and month, then display the wanted data.
    avgS.clear();
    int year, month;
    float sd, avg;
    std::cout << "\nPlease enter year:\n";
    std::cin >> year;
    std::cout << "\nPlease enter month:\n";
    std::cin >> month;
    inputYearMonth = std::to_string(year) + monthToString(month);
    wlsBst.inOrderTraversal(getMonthSpeed);
    for(size_t i=0; i<avgS.size(); i++)
    {
        avg += avgS[i];
    }

    avg = avg/avgS.size();
    sd = findSd(avgS);

    std::cout << std::endl;
    std::cout << stringToMonth(month) << ' ' << year << ":\n";
    if(sd != 0)
    {
        std::cout << "Average speed : " << round(avg) <<" km/h\n";
        std::cout << "Sample stdev  : " << sd;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No Data\n";
    }
}

void windlog::findYearTemperature()
{
    /// User input year and display every month of wanted year data.
    int year;
    std::cout << "\nPlease enter year:\n";
    std::cin >> year;
    std::cout << '\n' << year << '\n';
    for(int i=1; i<13; i++)
    {
        avgT.clear();
        float sd = 0, avg = 0;
        inputYearMonth = std::to_string(year)+monthToString(i);
        wlsBst.inOrderTraversal(getMonthTemp);

        for(size_t j=0; j<avgT.size(); j++)
        {
            avg+= avgT[j];
        }
        avg = avg/avgT.size();
        sd = findSd(avgT);


        if(sd !=0)
        {
            std::cout << stringToMonth(i) << ": average: " << round(avg)
                      << " degrees C, stdev: " << sd << '\n';
        }
        else
        {
            std::cout << stringToMonth(i) << ": No Data\n";
        }
    }
}

void windlog::findYearSolar()
{
    /// User input year and display every month of wanted year data.
    int year;
    std::cout << "\nPlease enter year:\n";
    std::cin >> year;
    std::cout << '\n' << year << '\n';
    for(int i=1; i<13; i++)
    {
        avgSr.clear();
        float total = 0;
        inputYearMonth = std::to_string(year)+monthToString(i);
        wlsBst.inOrderTraversal(getMonthSolar);

        for(size_t j=0; j<avgSr.size(); j++)
        {
            total+= avgSr[j];
        }

        if(total !=0)
        {
            std::cout << stringToMonth(i) << ": " << round(total)
                      << " kWh/m2"<< '\n';
        }
        else
        {
            std::cout << stringToMonth(i) << ": No Data\n";
        }
    }
}

void windlog::printToFile()
{
    int year;
    std::ofstream toFile("data/WindTempSolar.csv");
    std::cout << "\nPlease enter year:\n";
    std::cin >> year;
    std::cout << '\n' << year << '\n';
    toFile << year << '\n';
    for(int i=1; i<13; i++)
    {
        float avgSpeed = 0, sdSpeed = 0, avgTemp = 0, sdTemp = 0,srTotal = 0;
        inputYearMonth = std::to_string(year)+monthToString(i);



        /// Wind speed
        avgS.clear();
        wlsBst.inOrderTraversal(getMonthSpeed);
        for(size_t j=0; j<avgS.size(); j++)
        {
            avgSpeed += avgS[j];
        }
        avgSpeed = avgSpeed/avgS.size();
        sdSpeed = findSd(avgS);

        /// Temperature
        avgT.clear();
        wlsBst.inOrderTraversal(getMonthTemp);
        for(size_t j=0; j<avgT.size(); j++)
        {
            avgTemp += avgT[j];
        }
        std::cout << "\n";
        avgTemp = avgTemp/avgT.size();
        sdTemp = findSd(avgT);

        /// Solar radiation
        avgSr.clear();
        wlsBst.inOrderTraversal(getMonthSolar);
        for(size_t j=0; j<avgSr.size(); j++)
        {
            srTotal += avgSr[j];
        }

        /// write the data into WindTempSolar.csv file.
        std::cout << stringToMonth(i);
        toFile << stringToMonth(i) << ',';
        if(sdSpeed == 0)
        {
            toFile << ',';
        }
        else
        {
            std::cout << ',' << round(avgSpeed) << '(' << sdSpeed << ')' << ',';
            toFile << round(avgSpeed) << '(' << sdSpeed << ')' << ',';
        }
        if(sdTemp == 0)
        {
            toFile << ',';
        }
        else
        {
            std::cout << round(avgTemp) << '(' << sdTemp << ')' << ',';
            toFile << round(avgTemp) << '(' << sdTemp << ')' << ',';
        }
        if(srTotal != 0)
        {
            std::cout << round(srTotal) << '\n';
            toFile << round(srTotal) << '\n';
        }
        else
        {
            std::cout << '\n';
            toFile << '\n';
        }
    }
    std::cout << "\nSuccessfully write the data to data/WindTempSolar.csv.\n";
}

void windlog::reload()
{
    /// Reload function for Menu #5
    wlsBst.DeleteTree();
    readFiles("data/met_index.txt");
}


