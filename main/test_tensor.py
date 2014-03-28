"""TENSOR TEST

To run:

    nosetests -vs test_tensor

"""

from build import run_cmd, str_eq, build_run

EXPECTED_OUTPUT = """       1 |        1
       2 |        2
       3 |        3
       4 |        4
       5 |        5

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |        0 |        2 |        4 | 
     1 |        1 |        3 |        5 | 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |        0 |        1 |        2 | 
     1 |        3 |        4 |        5 | 


tensor(:,:,0) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |        0 |        2 |        4 | 
     1 |        1 |        3 |        5 | 

tensor(:,:,1) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |        6 |        8 |       10 | 
     1 |        7 |        9 |       11 | 

tensor(:,:,2) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       12 |       14 |       16 | 
     1 |       13 |       15 |       17 | 

tensor(:,:,3) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       18 |       20 |       22 | 
     1 |       19 |       21 |       23 | 



tensor(0,:,:) = 

 r \ c |        0 |        1 |        2 |        3 | 
-------+----------+----------+----------+----------+
     0 |        0 |        1 |        2 |        3 | 
     1 |        4 |        5 |        6 |        7 | 
     2 |        8 |        9 |       10 |       11 | 

tensor(1,:,:) = 

 r \ c |        0 |        1 |        2 |        3 | 
-------+----------+----------+----------+----------+
     0 |       12 |       13 |       14 |       15 | 
     1 |       16 |       17 |       18 |       19 | 
     2 |       20 |       21 |       22 |       23 | 



tensor(:,:,0,0) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |        0 |        2 |        4 | 
     1 |        1 |        3 |        5 | 

tensor(:,:,1,0) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |        6 |        8 |       10 | 
     1 |        7 |        9 |       11 | 

tensor(:,:,2,0) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       12 |       14 |       16 | 
     1 |       13 |       15 |       17 | 

tensor(:,:,3,0) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       18 |       20 |       22 | 
     1 |       19 |       21 |       23 | 


tensor(:,:,0,1) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       24 |       26 |       28 | 
     1 |       25 |       27 |       29 | 

tensor(:,:,1,1) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       30 |       32 |       34 | 
     1 |       31 |       33 |       35 | 

tensor(:,:,2,1) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       36 |       38 |       40 | 
     1 |       37 |       39 |       41 | 

tensor(:,:,3,1) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       42 |       44 |       46 | 
     1 |       43 |       45 |       47 | 


tensor(:,:,0,2) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       48 |       50 |       52 | 
     1 |       49 |       51 |       53 | 

tensor(:,:,1,2) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       54 |       56 |       58 | 
     1 |       55 |       57 |       59 | 

tensor(:,:,2,2) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       60 |       62 |       64 | 
     1 |       61 |       63 |       65 | 

tensor(:,:,3,2) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       66 |       68 |       70 | 
     1 |       67 |       69 |       71 | 


tensor(:,:,0,3) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       72 |       74 |       76 | 
     1 |       73 |       75 |       77 | 

tensor(:,:,1,3) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       78 |       80 |       82 | 
     1 |       79 |       81 |       83 | 

tensor(:,:,2,3) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       84 |       86 |       88 | 
     1 |       85 |       87 |       89 | 

tensor(:,:,3,3) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       90 |       92 |       94 | 
     1 |       91 |       93 |       95 | 


tensor(:,:,0,4) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |       96 |       98 |      100 | 
     1 |       97 |       99 |      101 | 

tensor(:,:,1,4) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |      102 |      104 |      106 | 
     1 |      103 |      105 |      107 | 

tensor(:,:,2,4) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |      108 |      110 |      112 | 
     1 |      109 |      111 |      113 | 

tensor(:,:,3,4) = 

 r \ c |        0 |        1 |        2 | 
-------+----------+----------+----------+
     0 |      114 |      116 |      118 | 
     1 |      115 |      117 |      119 | 




tensor(0,0,:,:) = 

 r \ c |        0 |        1 |        2 |        3 |        4 | 
-------+----------+----------+----------+----------+----------+
     0 |        0 |        1 |        2 |        3 |        4 | 
     1 |        5 |        6 |        7 |        8 |        9 | 
     2 |       10 |       11 |       12 |       13 |       14 | 
     3 |       15 |       16 |       17 |       18 |       19 | 

tensor(0,1,:,:) = 

 r \ c |        0 |        1 |        2 |        3 |        4 | 
-------+----------+----------+----------+----------+----------+
     0 |       20 |       21 |       22 |       23 |       24 | 
     1 |       25 |       26 |       27 |       28 |       29 | 
     2 |       30 |       31 |       32 |       33 |       34 | 
     3 |       35 |       36 |       37 |       38 |       39 | 

tensor(0,2,:,:) = 

 r \ c |        0 |        1 |        2 |        3 |        4 | 
-------+----------+----------+----------+----------+----------+
     0 |       40 |       41 |       42 |       43 |       44 | 
     1 |       45 |       46 |       47 |       48 |       49 | 
     2 |       50 |       51 |       52 |       53 |       54 | 
     3 |       55 |       56 |       57 |       58 |       59 | 


tensor(1,0,:,:) = 

 r \ c |        0 |        1 |        2 |        3 |        4 | 
-------+----------+----------+----------+----------+----------+
     0 |       60 |       61 |       62 |       63 |       64 | 
     1 |       65 |       66 |       67 |       68 |       69 | 
     2 |       70 |       71 |       72 |       73 |       74 | 
     3 |       75 |       76 |       77 |       78 |       79 | 

tensor(1,1,:,:) = 

 r \ c |        0 |        1 |        2 |        3 |        4 | 
-------+----------+----------+----------+----------+----------+
     0 |       80 |       81 |       82 |       83 |       84 | 
     1 |       85 |       86 |       87 |       88 |       89 | 
     2 |       90 |       91 |       92 |       93 |       94 | 
     3 |       95 |       96 |       97 |       98 |       99 | 

tensor(1,2,:,:) = 

 r \ c |        0 |        1 |        2 |        3 |        4 | 
-------+----------+----------+----------+----------+----------+
     0 |      100 |      101 |      102 |      103 |      104 | 
     1 |      105 |      106 |      107 |      108 |      109 | 
     2 |      110 |      111 |      112 |      113 |      114 | 
     3 |      115 |      116 |      117 |      118 |      119 | 



"""

def test_static_tensor():
    """[CPP] static_tensor.cpp: """
    build_run("static_tensor", "", EXPECTED_OUTPUT)

def test_dynamic_tensor():
    """[CPP] dynamic_tensor.cpp: """
    build_run("dynamic_tensor", "", EXPECTED_OUTPUT)

