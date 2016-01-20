# CSCI 104 - HW06 Tests

##Step 1: Templated implementation of `set` (5%)

Modify following lines in the `gtest_myset_templated.cpp` file.

 - Change line [7](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw6_tests/gtest_myset_templated.cpp#L7) to include your `myset.h` file.

 - Modify the typedef on [17, 18](https://github.com/usc-csci104-fall2015/homework-resources/blob/master/hw6_tests/gtest_myset_templated.cpp#L17) with the tempalated class names that you may have used. 

 - Compile with following command:

```shell
$ g++ -g -Wall -std=c++0x gtest_myset_templated.cpp  <other_files_as_needed> \
-I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread \
-o myset_templated
```

##Step 2, 3: Using Configuration file and Web Crawler (5% + 30%)

There are 3 data sets for testing the configuration files and web crawler functionality.

  - Compile your crawler part of the program and run with the three data sets provided.
  - Perform an IN ORDER comparison between the output files and the solutions provided in the `crawler_solution` folder. 

##Step 4, 5: Page Rank (10% + 50%)

 + Following results are generated using alpha = 0.15 and 30 iterations.

 + Compile your program and run with the two data sets `data8` and `data9` provided below. You may want to create a config file for these data sets as required by your program.

 + `data8`: Search for single term `screaming` with `Pagerank` option, results should be within reasonable range (round to 3 significant digits) of following results:

 ```
  data8/p1.txt    0.239726
  data8/p4.txt    0.239726
  data8/p0.txt    0.212397
  data8/p3.txt    0.179547
  data8/p2.txt    0.128605
```
  + Sorting with `filename` option should give following results:

```
  data8/p0.txt
  data8/p1.txt
  data8/p2.txt
  data8/p3.txt
  data8/p4.txt
```

 + `data9`: Search for single term `Serpent` with `Pagerank`, results should be within reasonable range (round to 3 significant digits) of following results:

```
data9/p2.txt  0.0839074
data9/p41.txt 0.0746702
data9/p45.txt 0.0642404
data9/p32.txt 0.0606803
data9/p39.txt 0.059332
data9/p21.txt 0.0574563
data9/p20.txt 0.0528231
data9/p15.txt 0.0502092
data9/p47.txt 0.0435326
data9/p28.txt 0.0367697
data9/p13.txt 0.0302343
data9/p38.txt 0.0302343
data9/p0.txt  0.0276505
data9/p46.txt 0.0259734
data9/p5.txt  0.0238095
data9/p11.txt 0.0238095
data9/p48.txt 0.0238095
data9/p8.txt  0.0203867
data9/p9.txt  0.0162573
data9/p25.txt 0.0156164
data9/p12.txt 0.0149463
data9/p27.txt 0.0130132
data9/p42.txt 0.0115487
data9/p33.txt 0.0108926
data9/p44.txt 0.0105696
data9/p6.txt  0.00991284
data9/p29.txt 0.00965571
data9/p31.txt 0.00959211
data9/p36.txt 0.00958161
data9/p10.txt 0.0080214
data9/p49.txt 0.0078599
data9/p22.txt 0.00689207
data9/p17.txt 0.00661735
data9/p4.txt  0.00625882
data9/p1.txt  0.00621118
data9/p34.txt 0.00610032
data9/p14.txt 0.00600408
data9/p7.txt  0.00578731
data9/p3.txt  0.00575892
data9/p23.txt 0.00453515
data9/p24.txt 0.00453515
data9/p16.txt 0.00430293
```

 + With single search term `Serpent` with sorting based on `filename`, files should be sorted in ascedning order and following files won't be reachable: 18, 19, 26, 30, 37, 40, 43. 

 + Search `AND footmen frowning`, following pages won't be reachable:
11, 18, 19, 26, 30, 35, 37, 40, 43, 

