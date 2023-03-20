# Custom Binary Search Tree implementation
Based on the requirements given, the program is expected to use at least a self-made Binary search tree (BST) and STL::Map to store and handle over a few hundred thousand wind log records that contain the date, time, wind speed, solar radiation, and temperature.

In order to fulfil the requirements and best optimise the processing sequences, the program has been implemented with BST of the map, and each map contains a maximum of 12 keys, each indicated as the month, from January to December. Every key comes with the element of the STL::vector includes a month of wind log data, which is around four thousand lines of data from each month. While loading the data, the algorithm includes the checking of no duplicated data and the ability to join the data from multiple files. (Ex. Join the 1/1/2011 0:00 to 9:00 from file 1 and the 1/1/2011 9:10 to 23:50 from file 2)

Compared to directly storing every wind log data into BST and causing it to be stored in a massive binary search tree, and only contains a short period of data. In contrast, this implemented design has the ability to store many years of maps and retrieve the data from each map more quickly.

The program is also expected to execute the calculations with the retrieved data, such as finding the sum of the month, the average of the month, the standard deviation of the month, and the function of writing data into a file and reloading data from the file.

# What's working in this program:
- Read data from multiple files

- Calculate the average and standard deviation of wind speed
 
- Calculate the average and standard deciation of ambient temperature
 
- Calcualte the total solar radidation in kWh/m2
 
- Display all processed data and write data to WindTempSolar.csv file
 
- Able to reload the met_index.txt file
 
- Able to display no data if user input the year and month that is not exist in the BST
 
- User input validation check (1-6)
 
- BST with function pointers is used in this program
 
- STL map is used in this program


# What's not working in this program:
- My custom made vector is not good as the STL::vector
 
- This program must implement with STL::vector
