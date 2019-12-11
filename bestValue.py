import math
profit = [92,57,49,68,60,43,67,84,87,72]
price =  [23,31,29,44,53,38,63,85,89,82]
money = 165
def avaliar(item):
	value = 0
	cost = 0
	for i in range(len(item)):
		value+= item[i]*profit[i]
		cost+= item[i]*price[i]

	if(cost>money):
		value = -1
	return value



def main():

	c = []
	pivot = 0
	for i in range(len(profit)):
		aux = 0
		while True:
			if aux*price[i]>money:
				break
			else:
				aux = aux +1
		c.append(aux-1)
		print(aux-1)


	baseNumeric = max(c)+1
	bestGuy = None
	bestValue = 0

	print(baseNumeric)


	for i in range(int(math.pow(baseNumeric,len(profit)))):

		value = i
		vet = []
		for k in range(len(profit)-1,-1,-1):
			num =  value//(baseNumeric**k)
			value = value%(baseNumeric**k)
			vet.append(num)

		if(bestGuy == None):
			print('foi')
			input()
			bestGuy = vet
			bestValue = avaliar(vet)
			print('foi')
			print(vet)
			print(bestValue)
			input()
		else:
			
			tempValue = avaliar(vet)
			if(tempValue>bestValue):
				bestValue = tempValue
				bestGuy = vet
				print(vet)
				print(bestValue)
				
	

	print(bestGuy)
	print(value)

main()
			


