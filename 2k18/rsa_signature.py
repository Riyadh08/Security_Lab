# -*- coding: utf-8 -*-
"""
Created on Wed Apr 13 11:15:48 2022

@author: utshob
"""

from decimal import Decimal
import math

p=814858151398825303904126828528260745946003294370335581242491449329860832622112065181574501203723176064405833200874210247032350592132601679649356392179
q=811719930861659038479006929987614581543025692108336694178300058784499071521715274832894919182539431390296491066711161744176037402290778212554061049459

n = p*q
fi_n = (p-1)*(q-1)

message = 9876543210
print("message:"+str(message))

for i in range(2,fi_n):
    if(math.gcd(i, fi_n)==1):
        break

e = i
print(e)

for k in range (1,150):
    x = 1+k*fi_n 
    if(x%e == 0):
        d = x//e
        
signing = pow(message, d, n) #message^d mod n
print("signing:" +str(signing))

verification = pow(signing,e,n)  #signing^e mod n
print("verification:" +str(verification))
        
