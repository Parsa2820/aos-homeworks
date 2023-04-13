"""
Running 1.3 with 1 threads

 Performance counter stats for './1.3':

                53      page-faults:u                                                         
             6,313      cache-misses:u                                                        
               167      dTLB-load-misses:u               #    0.52% of all dTLB cache accesses
            31,950      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.000851952 seconds time elapsed

       0.000867000 seconds user
       0.000000000 seconds sys


-----------------
Running 1.3 with 2 threads

 Performance counter stats for './1.3':

                51      page-faults:u                                                         
             6,226      cache-misses:u                                                        
               159      dTLB-load-misses:u               #    0.50% of all dTLB cache accesses
            31,950      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.000786024 seconds time elapsed

       0.000811000 seconds user
       0.000000000 seconds sys


-----------------
Running 1.3 with 3 threads

 Performance counter stats for './1.3':

                53      page-faults:u                                                         
             5,643      cache-misses:u                                                        
               164      dTLB-load-misses:u               #    0.51% of all dTLB cache accesses
            31,950      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.000748116 seconds time elapsed

       0.000756000 seconds user
       0.000000000 seconds sys


-----------------
Running 1.3 with 4 threads

 Performance counter stats for './1.3':

                53      page-faults:u                                                         
             5,510      cache-misses:u                                                        
               157      dTLB-load-misses:u               #    0.49% of all dTLB cache accesses
            31,921      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.001029236 seconds time elapsed

       0.001070000 seconds user
       0.000000000 seconds sys


-----------------
Running 1.3 with 5 threads

 Performance counter stats for './1.3':

                52      page-faults:u                                                         
             5,868      cache-misses:u                                                        
               159      dTLB-load-misses:u               #    0.50% of all dTLB cache accesses
            31,950      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.000757058 seconds time elapsed

       0.000747000 seconds user
       0.000000000 seconds sys


-----------------
Running 1.3 with 6 threads

 Performance counter stats for './1.3':

                51      page-faults:u                                                         
             6,439      cache-misses:u                                                        
               162      dTLB-load-misses:u               #    0.51% of all dTLB cache accesses
            31,950      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.000781736 seconds time elapsed

       0.000827000 seconds user
       0.000000000 seconds sys


-----------------
Running 1.3 with 7 threads

 Performance counter stats for './1.3':

                52      page-faults:u                                                         
             3,688      cache-misses:u                                                        
               161      dTLB-load-misses:u               #    0.50% of all dTLB cache accesses
            31,950      dTLB-loads:u                                                          
            11,341      dTLB-stores:u                                                         

       0.000675503 seconds time elapsed

       0.000679000 seconds user
       0.000000000 seconds sys


-----------------
"""
import matplotlib.pyplot as plt

cores = [1, 2, 3, 4, 5, 6, 7]
page_faults = [53, 51, 53, 53, 52, 51, 52]
cache_misses = [6313, 6226, 5643, 5510, 5868, 6439, 3688]
dTLB_load_misses = [167, 159, 164, 157, 159, 162, 161]

plot = plt.figure()
plt.plot(cores, page_faults, label="Page Faults")
plt.plot(cores, cache_misses, label="Cache Misses")
plt.plot(cores, dTLB_load_misses, label="dTLB Load Misses")
plt.xlabel("Number of Cores")
plt.ylabel("Number of Events")
plt.legend()
plt.show()

time = [0.000851952, 0.000786024, 0.000748116, 0.001029236, 0.000757058, 0.000781736, 0.000675503]
user = [0.000867000, 0.000811000, 0.000756000, 0.001070000, 0.000747000, 0.000827000, 0.000679000]

plot = plt.figure()
plt.plot(cores, time, label="Time")
plt.plot(cores, user, label="User")
plt.xlabel("Number of Cores")
plt.ylabel("Time (s)")
plt.legend()
plt.show()
