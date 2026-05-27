

import serial as ps
import numpy as np
import matplotlib.pyplot as mp
ser = ps.Serial('/dev/cu.usbmodem14201',9600)
ser.reset_input_buffer()
flag = 998.0
t = []
T = []
Q = []

while flag != 999.0:
    
    data = ser.readline()
    data_list = data.split(b',')
    flag = float(data_list[0])
   # next_list = data_list[1].split(b',')=
    t_i = float(data_list[1])/60
   # next_list = next_list[1].split(b',')
    T_i = float(data_list[2])
   # next_list = next_list[1].split(b'\n')
    Q_i = float(data_list[3])
    
    if t_i*60 < 1:
        #sp_start = float(data_list[4])
        sp_end =   float(data_list[4])
        t_total = float(data_list[5])
        
    
    #time = np.linspace(0, t_total,t_total+1)/60
    sp_vector = (np.zeros(int(t_total+1)))
    sp_vector[0:9] = 70
    sp_vector[9:int(t_total+1)] = sp_end
    
    
    t.append(t_i)
    T.append(T_i)
    Q.append(Q_i)
    axis =   mp.subplot(2,1,1)
    mp.suptitle('PID Control')
    mp.plot(t, T, linestyle = '-', label = 'Temperature')
    if t_i*60 == t_total:
        mp.plot(t,sp_vector, linestyle = '--', label = 'Setpoint')
    mp.xlabel('Time (min)')
    mp.ylabel('Temperature (C)')
    mp.legend(loc = 4)
    axis = mp.subplot(2,1,2)
    mp.plot(t, Q, linestyle = '-')
    mp.xlabel('Time (min)')
    mp.ylabel('Heater Output (%)')
    mp.legend(loc = 4)
    mp.show()

    
data = np.vstack((t,Q,T)).T
np.savetxt('SOPDT.csv',data,delimiter=',',\
            header='Time,Q1,T1',comments='')   
    

            