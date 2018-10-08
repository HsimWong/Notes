class Mark:
	def __init__(self, name, result):
		self.name = name
		# self.course = course
		self.result = int(result)

time = int(input())
RecGroup = []
for i in range(time):
	str = input()
	key_char = ' '
	space_1st_ind = str.find(key_char, 0, len(str))
	space_fin_ind = str.find(key_char, len(str), 0)
	print(space_fin_ind)
	name = str[0:space_fin_ind];
	# course = str[space_1st_ind + 1:space_2nd_ind];
	result = str[space_fin_ind + 1: len(str)]

	print("name:%s, result:%s"%(name,result))
	rec = Mark(name,result)
	RecGroup.append(rec)
min_rec_res = 65535;
max_rec_res = 0
max_rec = RecGroup[0]
min_rec = RecGroup[0]


for rec in RecGroup:
	if min_rec_res > (rec.result):
		min_rec_res = rec.result
		min_rec = rec
	if max_rec_res < (rec.result):
		max_rec = rec.result
		max_rec = rec
print("%s"%(max_rec.name, max_rec.course))
print('%s'%(min_rec.name, min_rec.course),end = "")
