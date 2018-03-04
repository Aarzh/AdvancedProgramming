import sys
num = 1
n = int(sys.argv[1])#GETS THE NUMBER AS PARAMETER AND TRANSFORM IT TO INT

while n >= 1:
    num *= n
    n -= 1
sys.exit(num)#RETURN THE VALUE
